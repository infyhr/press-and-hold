#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <linux/input.h>
#include <fcntl.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#define TABLETFILE "/dev/input/by-id/usb-Genius_EasyPen_i405X-event-mouse"
#define DEBUG 0
#define THRESHOLD 2
#define RADIUS 10

int ack(Display *);
int main(int argc, char **argv) {
    int fd;
    struct input_event ie; // Input events
    Display *dpy; // The opened display
    Window root, child; // Windows
    int rootX, rootY, winX, winY, current_x, current_y; // Coordinates
    unsigned int mask; // ???
    unsigned int now;

    dpy = XOpenDisplay(NULL);
    XQueryPointer(dpy, DefaultRootWindow(dpy), &root, &child, &rootX, &rootY, &winX, &winY, &mask); // Query the display

    // Try to read the event
    if((fd = open(TABLETFILE, O_RDONLY)) == -1) {
        perror("Failed to open the device: ");
        return -1;
    }

    while(read(fd, &ie, sizeof(struct input_event))) {
            if(ie.code == 0) { rootX = ie.value; }
            if(ie.code == 1) { rootY = ie.value; }
        #if DEBUG
            printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
            printf("X position: %d\tY position: %d", rootX, rootY);
        #endif
        if(ie.type == 1 && ie.code == 330) {
            if(ie.value == 1) { // pen tip pressed
                now = (unsigned)time(NULL); // Grab the current time
                // Grab coordinates
                current_x = rootX;
                current_y = rootY;
            }
            if(ie.value == 0) { // pen tip released
                // Subtract and check
                if(((unsigned)time(NULL) - now) >= THRESHOLD) {
                    // Check if we got any oscilation going on
                    if(rootX - current_x <= RADIUS && rootY - current_y <= RADIUS) {
                        #if DEBUG
                            printf("rootX = %d, current_x = %d\nrootY = %d, current_y = %d\n\n", rootX, current_x, rootY, current_y);
                        #endif
                        ack(dpy);
                    }
                }
            }
        }
    }

    return 0;
}

int ack(Display *dpy) {
    // XTest.h easymode
    XTestFakeButtonEvent(dpy, 3, True,  CurrentTime);
    XTestFakeButtonEvent(dpy, 3, False, CurrentTime);
    XFlush(dpy);
    return 0;
}
