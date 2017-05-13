CPP=g++
FLAGS= -std=c++11
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: editor

# editor: Editor.cpp TextView.cpp TextViewContent.cpp TextDocument.cpp SelectionData.cpp Cursor.cpp
# 		@echo "** Building main"
# 		g++ $(FLAGS) -o editor Editor.cpp TextView.cpp TextViewContent.cpp SelectionData.cpp Cursor.cpp TextDocument.cpp $(LIBS)

editor: Editor.o TextView.o TextViewContent.o Cursor.o SelectionData.o TextDocument.o
	g++ $(FLAGS)  Editor.o TextView.o TextViewContent.o Cursor.o SelectionData.o TextDocument.o -o editor $(LIBS)

Editor.o: Editor.cpp TextView.cpp TextView.h TextDocument.cpp TextDocument.h
	g++ $(FLAGS) -c Editor.cpp TextView.cpp TextDocument.cpp

TextDocument.o: TextDocument.cpp TextDocument.h
	g++ $(FLAGS) -c TextDocument.cpp

TextView.o: TextView.cpp TextView.h TextViewContent.cpp TextViewContent.h Cursor.cpp Cursor.h
	g++ $(FLAGS) -c TextView.cpp TextViewContent.cpp Cursor.cpp

TextViewContent.o: TextViewContent.cpp TextViewContent.h TextDocument.cpp TextDocument.h SelectionData.cpp SelectionData.h
	g++ $(FLAGS) -c TextViewContent.cpp TextDocument.cpp SelectionData.cpp

Cursor.o: Cursor.h Cursor.cpp
	g++ $(FLAGS) -c Cursor.cpp

SelectionData.o: SelectionData.cpp SelectionData.h TextDocument.h TextDocument.cpp
	g++ $(FLAGS) -c SelectionData.cpp TextDocument.cpp

clean:
	rm -f editor *.o
