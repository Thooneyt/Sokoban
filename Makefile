CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = Sokoban.hpp SpriteSheet.hpp
# Your compiled .o files
OBJECTS = Sokoban.o SpriteSheet.o
# The name of your program
PROGRAM = Sokoban

.PHONY: all clean lint 

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
		$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o Sokoban.a
		$(CC) $(CFLAGS) -o $@ $^ $(LIB) 

Sokoban.a: $(OBJECTS)
		ar rcs Sokoban.a Sokoban.o SpriteSheet.o

clean:
		rm *.o *.a $(PROGRAM)

lint:
		cpplint *.hpp *.cpp
