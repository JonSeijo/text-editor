#include "SelectionData.h"

void SelectionData::addSelection(int start, int end) {
    this->selections.push_back(Selection(start, end));
}

void SelectionData::removeSelection(int index) {
    this->validIndex(index);
    this->selections.erase(this->selections.begin() + index);
}

void SelectionData::removeSelection(int start, int end) {
    for (int i = 0; i < (int)this->selections.size(); i++) {
        if (this->selections[i].start == start && this->selections[i].end == end) {
            this->removeSelection(i);
            return;
        }
    }
    std::cerr << "Start: " << start << "  end: " << end << " is not a valid range for Selections" << std::endl;
}

int SelectionData::getStart(int index) {
    this->validIndex(index);
    return this->selections[index].start;
}

int SelectionData::getEnd(int index) {
    this->validIndex(index);
    return this->selections[index].end;
}

bool SelectionData::validIndex(int index) {
    if (index < 0 || index >= (int)this->selections.size()) {
        std::cerr << "Index: " << index << " is not a valid index for Selections" << std::endl;
        return false;
    }
    return true;
}

