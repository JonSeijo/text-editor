CPP=g++
FLAGS= -std=c++11
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: editor

main.o: main.cpp
		g++ -c "main.cpp" -o main.o

editor: main.o
		@echo "** Building main"
		g++ -o editor main.o $(LIBS)

clean:
		@echo "** Cleaning..."
		rm -f editor *.o
