CC = clang
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL_ttf
CFLAGS =  -std=c11 -Wall -g $(SDL_CFLAGS)
LINK = $(SDL_LDFLAGS)
VPATH = src/
OUT = bin/
OBJ = obj/
SRCS = tower.c map.c cursor.c graphics.c

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
	rm -f *.d
