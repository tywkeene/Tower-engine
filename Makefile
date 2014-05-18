CC = gcc
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image
CFLAGS = -std=c99 -D_POSIX_SOURCE -g $(SDL_CFLAGS)
LINK = $(SDL_LDFLAGS) -lm
VPATH = src/
OUT = bin/
OBJ = obj/
SRCS = tower.c map.c player.c graphics.c

.PHONY: all clean
all: tower

include $(SRCS:.c=.d)

tower: $(SRCS:.c=.o)
	$(CC) $(CFLAGS) $(LINK) -o $(OUT)$@ $^ 

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean :
	rm -f *.o; \
	rm -f ./bin/tower
