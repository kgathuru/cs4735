CFLAGS= -I/usr/X11R6/include -I/usr/local/include
LDFLAGS= -L/usr/X11R6/lib -L/usr/local/lib -lGL -lGLU -lm -lglut 

BINARIES=game

all: $(BINARIES)

clean:	
	-rm *.o $(BINARIES)

game : game.o 
	g++ $(LDFLAGS) $^ -o game 

game.o: game.cpp 
	g++ -c $(CFLAGS) game.cpp

depend:
	makedepend *.cpp
