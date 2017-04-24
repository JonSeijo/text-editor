#ifndef SelectionData_H
#define SelectionData_H

#include <iostream>
#include <vector>

class SelectionData {

    public:
        void addSelection(int start, int end);
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
        bool validIndex(int index);

        void removeSelection(int index);
        void removeSelection(int start, int end);
        int getStart(int index);
        int getEnd(int index);
};

#endif
