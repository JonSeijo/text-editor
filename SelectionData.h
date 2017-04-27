#ifndef SelectionData_H
#define SelectionData_H

#include "TextDocument.h"
#include <iostream>
#include <vector>

// TODO: Pensar si la seleccion no deberia conocer al documento, para arreglar quilombos con los multiples
class SelectionData {

    public:
        SelectionData();

        void addSelection(int startLineN, int startCharN, int endLineN, int endCharN);
        void updateLastSelection(int startLineN, int startCharN, int endLineN, int endCharN);


        // TODO: Para cuando use multiples selecciones con teclado
        //       util para mover todas x caractes hacia un lado.
        //       Hay que tener en cuenta el no salirse del documento y cambios de linea, colisiones etc
        void moveSelectionsRight(int charAmount, const TextDocument &doc);
        void moveSelectionsLeft(int charAmount, const TextDocument &doc);

        void removeSelections();
        bool isSelected(int lineN, int charN) const;

        struct Selection {
            int startLineN;
            int startCharN;
            int endLineN;
            int endCharN;

            Selection() : startLineN(-1), startCharN(-1), endLineN(-1), endCharN(-1) {}
            Selection(int startLineN, int startCharN, int endLineN, int endCharN) :
                 startLineN(startLineN), startCharN(startCharN), endLineN(endLineN), endCharN(endCharN) {}

        };

        Selection getLastSelection();

    private:

        std::vector<Selection> selections;
        int lastSelectionIndex;

        bool validIndex(int index);
        void removeSelection(int index);
};

#endif
