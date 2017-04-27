#include "SelectionData.h"

SelectionData::SelectionData() : lastSelectionIndex(-1) {}

void SelectionData::addSelection(int startLineN, int startCharN, int endLineN, int endCharN) {
    this->selections.push_back(Selection(startLineN, startCharN, endLineN, endCharN));
    this->lastSelectionIndex++;
}

// Extremos de una seleccion son inclusives a ambos lados
bool SelectionData::isSelected(int lineN, int charN) const{
    for (const Selection sel : this->selections) {
        // Si esta estrictamente entre las lineas, esta seleccionado.
        if (sel.startLineN < lineN  && lineN < sel.endLineN) {
            return true;
        }
        // Si esta en la linea de start:
        //      esta seleccionado si startCharN <= charN
        if (sel.startLineN == lineN && sel.startCharN <= charN) {
            return true;
        }
        // Si esta en la linea de end:
        //      esta seleccionado si charN <= endCharN
        if (sel.endLineN == lineN && charN <= sel.startCharN) {
            return true;
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
