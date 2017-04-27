#include "SelectionData.h"

SelectionData::SelectionData() : lastSelectionIndex(-1) {}

void SelectionData::addSelection(int startLineN, int startCharN, int endLineN, int endCharN) {
    this->selections.push_back(Selection(startLineN, startCharN, endLineN, endCharN));
    this->lastSelectionIndex++;
}

// Extremos de una seleccion son inclusives a ambos lados
bool SelectionData::isSelected(int lineN, int charN) const{
    for (const Selection sel : this->selections) {
        // Si esta estrictamente entre las lineas puede estar seleccionado.
        if (sel.startLineN <= lineN && lineN <= sel.endLineN) {

            // Si la linea esta estrictamente contenida es porque esta seleccionada
            if (sel.startLineN < lineN && lineN < sel.endLineN) {
                return true;
            }

            // Si hay mas de una linea de seleccion y esta en el inicio
            if (sel.startLineN == lineN && lineN < sel.endLineN) {
                if (sel.startCharN <= charN) {
                    return true;
                }
            }

            // Si hay mas de una linea de seleccion y esta en el final
            if (sel.startLineN < lineN && lineN == sel.endLineN) {
                if (charN <= sel.endCharN) {
                    return true;
                }
            }

            // Si hay una unica linea de seleccion y está ahi
            if (sel.startLineN == lineN && lineN == sel.endLineN) {
                if (sel.startCharN <= charN && charN <= sel.endCharN) {
                    return true;
                }
            }

        }
    }
    return false;
}

void SelectionData::removeSelections() {
    int lastIndex = this->selections.size()-1;
    for (int i = lastIndex; i >= 0; i--) {
        this->removeSelection(i);
    }
}

void SelectionData::removeSelection(int index) {
    this->validIndex(index);
    this->selections.erase(this->selections.begin() + index);
    this->lastSelectionIndex--;
}

SelectionData::Selection SelectionData::getLastSelection() {
    if (this->validIndex(this->lastSelectionIndex)) {
        return this->selections[this->lastSelectionIndex];
    }
    return SelectionData::Selection();
}

bool SelectionData::validIndex(int index) {
    if (index < 0 || index >= (int)this->selections.size()) {
        std::cerr << "Index: " << index << " is not a valid index for Selections" << std::endl;
        return false;
    }
    return true;
}

void SelectionData::updateLastSelection(int startLineN, int startCharN, int endLineN, int endCharN) {
    this->selections[this->lastSelectionIndex].startLineN = startLineN;
    this->selections[this->lastSelectionIndex].startCharN = startCharN;
    this->selections[this->lastSelectionIndex].endLineN = endLineN;
    this->selections[this->lastSelectionIndex].endCharN = endCharN;
}
