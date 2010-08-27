
rm=/bin/rm -f
CC= g++
VPATH = ./units ./graphics
DEFS= $(shell sdl-config --cflags)
PROGNAME= Yukkuri
INCLUDES=  -I. -Iunits -Igraphics
LIBS= $(shell sdl-config --libs) -lpng -lSDL_image -lGL -lfreetype -Llibs  -llua 


DEFINES= $(INCLUDES) $(DEFS) -DSYS_UNIX=1
CFLAGS= -g -Wall $(DEFINES)



UNITS =  unitmanager.cpp unit.cpp Animated.cpp Plant.cpp Corpse.cpp Dynamic.cpp Entity.cpp Player.cpp
GRAPHICS = Font.cpp Graphics.cpp Interface.cpp Widgets.cpp pngfuncs.c


SRCS =   main.cpp engine.cpp Lua.cpp Luaconfig.cpp Bindings.cpp Spawner.cpp\
         $(UNITS) \
         $(GRAPHICS) \
         Camera.cpp daytime.cpp

OBJ = $(SRCS:.cpp=.o)
OBJS = $(OBJ:.c=.o)

.cpp.o:
	$(rm) $@
	$(CC) $(CFLAGS) -c $^ -o $@


#$*.cpp

.PHONY: all clean

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS)  -o $(PROGNAME) $(OBJS) $(LIBS)

clean:
	$(rm) $(OBJS) $(PROGNAME)
