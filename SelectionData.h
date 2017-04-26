#ifndef SelectionData_H
#define SelectionData_H

#include <iostream>
#include <vector>

// TODO: Creo que conviene que la seleccion este manejada por lineN y charN
// TODO: Pensar si la seleccion no deberia conocer al documento, para arreglar quilombos con los multiples
class SelectionData {

    public:
        SelectionData();

        void addSelection(int start, int end);
        void updateLastSelection(int start, int end);

        // TODO: Para cuando use multiples selecciones con teclado
        //       util para mover todas x caractes hacia un lado.
        //       Hay que tener en cuenta el no salirse del documento y cambios de linea, colisiones etc
        void moveSelectionsRight(int amount);
        void moveSelectionsLeft(int amount);

        void removeSelections();
        bool isSelected(int pos);

    private:
        struct Selection {
            int start;
            int end;

            Selection() : start(-1), end(-1) {}
            Selection(int start, int end) : start(start), end(end) {}

        };
        std::vector<Selection> selections;
        int lastSelectionIndex;

        bool validIndex(int index);

        void removeSelection(int index);
        void removeSelection(int start, int end);
        int getStart(int index);
        int getEnd(int index);
};

#endif
