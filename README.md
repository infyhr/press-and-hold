### press-and-hold
In Windows 7 and up there is a 'pen action' when using a graphics tablet. If you hold a pen for some, anywhere, on the same spot, a righclick would happen [as shown on this screenshot](http://www.qrg.northwestern.edu/software/cogsketch/PressAndHold01.png).  

I wanted to have something like this in Linux as well, so I wrote this quick little tool which does something like that. It's not perfect but it does its job well with my tablet.  

I am using a Genius EasyPen i405X, so there might be some additional configuration needed in order to make it work with some other inputs like Wacom.

Also, this was built ontop of the `xinput` "driver", as opposed to something like `wizardpen`.

### requirements
* `X11/Xlib.h` (libx11 on Arch)
* `X11/extensions/XTest.h` (libxtst on Arch)

### config
* `TARGETFILE` = tablet's input file (`$ ls -la /dev/input` btw). 
* `DEBUG`      = if you want to see **every** event being printed out. 
* `THRESHOLD`  = how many seconds to wait before a right click occurs? In other words, how many seconds the pen needs to be pressed in order for the right click to be sent.
* `RADIUS`     = sensitivity, how many pixels are you allowed to move your pen before you lift it up from the tablet. I don't use the full tablet area so my cursor wiggles a bit.

Other stuff:
`ie.code` might not be `330` for your tablet, so such things are worth debugging (line 41).

### compile and run
run `make`. You will need superuser access to run it. Fork it in the bg or something.
