#pragma once

#ifndef TextDocument_H
#define TextDocument_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

#include <algorithm>
#include <string>

#include "Enumeration.h"

using std::string;
using std::vector;

class TextDocument {
public:
    bool init(string& filename);
    bool saveFile(string& filename);
    bool hasChanged();

    sf::String getLine(int lineNumber);
    int charsInLine(int line) const;
    int getLineCount() const;

    void addTextToPos(sf::String text, int line, int charN);
    void removeTextFromPos(int amount, int line, int charN);
    sf::String getTextFromPos(int amount, int line, int charN);

    void swapLines(int lineA, int lineB);

    int charAmountContained(int startLineN, int startCharN, int endLineN, int endCharN);

private:
    bool initLinebuffer();
    sf::String buffer;
    int length;
    vector<int> lineBuffer;
    bool documentHasChanged;

    int getBufferPos(int line, int charN);

    void swapWithNextLine(int line);

    sf::String toUtf32(const std::string& inString);
};

#endif

class SelectionData {
private:
    struct Extremo {
        Extremo() : lineN(-1), charN(-1) {}
        Extremo(int lineN, int charN) : lineN(lineN), charN(charN) {};
        int lineN;
        int charN;

        bool operator<(const Extremo& ex) const {
            return lineN < ex.lineN || (lineN <= ex.lineN && charN < ex.charN);
        }
    };

public:
    SelectionData();

    struct Selection {
        Selection() : activa(false), ancla(), extremo() {}
        Selection(int anclaLine, int anclaChar) : activa(false), ancla(anclaLine, anclaChar), extremo() {}

        bool activa;
        SelectionData::Extremo ancla;
        SelectionData::Extremo extremo;
    };

    void createNewSelection(int anclaLine, int anclaChar);
    void updateLastSelection(int extremoLine, int extremoChar);

    void removeSelections();
    bool isSelected(int lineN, int charN) const;

    Selection getLastSelection();

    // TODO: Para cuando use multiples selecciones con teclado
    //       util para mover todas x caractes hacia un lado.
    //       Hay que tener en cuenta el no salirse del documento y cambios de linea, colisiones etc
    // TODO: Puede que cada seleccion se necesite mover de a saltos diferentes,
    //       por ejemplo cuando muevo con ctrl shift de a palabras, esto no serviria en ese caso
    //       tendria que hacer un "moveSelectionsToNextWord" o algo asi
    // TODO: Handlear que pasa cuando las selecciones chocan, ver el merge
    void moveSelectionsRight(int charAmount, const TextDocument& doc);
    void moveSelectionsLeft(int charAmount, const TextDocument& doc);

    static int getStartLineN(Selection& selection);
    static int getStartCharN(Selection& selection);
    static int getEndLineN(Selection& selection);
    static int getEndCharN(Selection& selection);

private:
    std::vector<Selection> selections;
    int lastSelectionIndex;

    int getLastAnclaLine();
    int getLastAnclaChar();
    int getLastIsActive();

    bool validIndex(int index);
    void removeSelection(int index);
};