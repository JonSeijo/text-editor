#ifndef SelectionData_H
#define SelectionData_H

#include "TextDocument.h"
#include <iostream>
#include <vector>

// TODO: Pensar si la seleccion no deberia conocer al documento, para arreglar quilombos con los multiples
// TODO: CAMBIAR TODO. Idea de puntos de anclaje
class SelectionData {

    public:
        SelectionData();

        struct Selection {
            Extremo ancla;
            Extremo extremo;
            bool activa;

            Selection() : ancla(), activa(false), extremo() {}
            Selection(int anclaLine, int anclaChar) : ancla(anclaLine, anclaChar), activa(false), extremo() {}
        }

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
        void moveSelectionsRight(int charAmount, const TextDocument &doc);
        void moveSelectionsLeft(int charAmount, const TextDocument &doc);

    private:
        struct Extremo {
            int lineN;
            int charN;
            Extremo() : lineN(-1), charN(-1) {}
            Extremo(int lineN, int charN) : lineN(lineN), charN(charN) {};

            bool operator<(const Extremo& ex) const {
                return lineN < ex.lineN || (lineN <= ex.lineN && charN < ex.charN);
            }
        }

        std::vector<Selection> selections;
        int lastSelectionIndex;

        int getLastAnclaLine();
        int getLastAnclaChar();
        int getLastIsActive();

        bool validIndex(int index);
        void removeSelection(int index);
};

#endif
