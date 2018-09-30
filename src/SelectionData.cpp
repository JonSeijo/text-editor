#include "SelectionData.h"

SelectionData::SelectionData() : lastSelectionIndex(-1) {}

// Inactiva por defecto pues solo inicializo el ancla
void SelectionData::createNewSelection(int anclaLine, int anclaChar) {
    this->selections.push_back(Selection(anclaLine, anclaChar));
    this->lastSelectionIndex++;
}

void SelectionData::updateLastSelection(int extremoLine, int extremoChar) {
    if (this->lastSelectionIndex < 0) {
        return;
    }

    int anclaLine = this->getLastAnclaLine();
    int anclaChar = this->getLastAnclaChar();

    bool nuevaActiva = (anclaLine != extremoLine) || (anclaChar != extremoChar);
    this->selections[this->lastSelectionIndex].activa = nuevaActiva;

    this->selections[this->lastSelectionIndex].extremo.lineN = extremoLine;
    this->selections[this->lastSelectionIndex].extremo.charN = extremoChar;
}

// Extremos de una seleccion son inclusives a ambos lados
bool SelectionData::isSelected(int lineN, int charN) const {
    for (const Selection sel : this->selections) {
        if (!sel.activa) {
            continue;
        }

        SelectionData::Extremo start;
        SelectionData::Extremo end;

        if (sel.ancla < sel.extremo) {
            start = sel.ancla;
            end = sel.extremo;
        } else {
            start = sel.extremo;
            end = sel.ancla;
        }

        // Si esta estrictamente entre las lineas puede estar seleccionado.
        if (start.lineN <= lineN && lineN <= end.lineN) {
            // Si la linea esta estrictamente contenida es porque esta seleccionada
            if (start.lineN < lineN && lineN < end.lineN) {
                return true;
            }

            // Si hay mas de una linea de seleccion y esta en el inicio
            else if (start.lineN == lineN && lineN < end.lineN) {
                if (start.charN <= charN) {
                    return true;
                }
            }

            // Si hay mas de una linea de seleccion y esta en el final
            else if (start.lineN < lineN && lineN == end.lineN) {
                if (charN < end.charN) {
                    return true;
                }
            }

            // Si hay una unica linea de seleccion y está ahi
            else if (start.lineN == lineN && lineN == end.lineN) {
                if (start.charN <= charN && charN < end.charN) {
                    return true;
                }
            }
        }
    }
    return false;
}

void SelectionData::removeSelections() {
    int lastIndex = this->selections.size() - 1;
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

int SelectionData::getStartLineN(Selection &selection) {
    auto extremoStart = selection.ancla < selection.extremo ? selection.ancla : selection.extremo;
    return extremoStart.lineN;
}

int SelectionData::getStartCharN(Selection &selection) {
    auto extremoStart = selection.ancla < selection.extremo ? selection.ancla : selection.extremo;
    return extremoStart.charN;
}

int SelectionData::getEndLineN(Selection &selection) {
    auto extremoEnd = selection.ancla < selection.extremo ? selection.extremo : selection.ancla;
    return extremoEnd.lineN;
}

int SelectionData::getEndCharN(Selection &selection) {
    auto extremoEnd = selection.ancla < selection.extremo ? selection.extremo : selection.ancla;
    return extremoEnd.charN;
}

bool SelectionData::validIndex(int index) {
    if (index < 0 || index >= (int)this->selections.size()) {
        // std::cerr << "Index: " << index << " is not a valid index for Selections" << std::endl;
        return false;
    }
    return true;
}

int SelectionData::getLastAnclaLine() {
    return this->selections[this->lastSelectionIndex].ancla.lineN;
}

int SelectionData::getLastAnclaChar() {
    return this->selections[this->lastSelectionIndex].ancla.charN;
}

int SelectionData::getLastIsActive() {
    return this->selections[this->lastSelectionIndex].activa;
}
