CC=gcc
CCFLAGS=-Wall
HEADERS=
LDFLAGS=-Lsrc -lX11 -lXtst
LDLIBS=

SRCS=$(wildcard src/*.c)
OBJS=$(subst src,obj,$(subst .c,.o,$(SRCS)))

.PHONY: all clean distclean

all: bin/press_and_hold

bin/press_and_hold: $(OBJS)
		mkdir -p bin
		$(CC) $(CCFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $(OBJS)

obj/%.o: src/%.c
		mkdir -p obj
		$(CC) $(CCFLAGS) $(LDFLAGS) $(HEADERS) -o $@ -c $<

clean:
		rm -rf bin obj

distclean: clean
