#include "usefulfunctions.h"
int getLinearIndex(const std::vector<int>& dimensions, const std::vector<int>& positions, std::vector<std::pair<int, std::string>> * mistakes, Node *exp) {
    int index = 0;
    int multiplier = 1;
    for (int i = dimensions.size() - 1; i >= 0; --i) {
        if (positions[i] > dimensions[i]) {
            auto str = std::string("Position out of range for the given dimension");
            auto pair = std::make_pair(exp->line, str);
            mistakes->push_back(pair);
            throw std::out_of_range("Position out of range for the given dimension");
        }
        index += positions[i] * multiplier;
        multiplier *= dimensions[i];
    }
    return index;
}

