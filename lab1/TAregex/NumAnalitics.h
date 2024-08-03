//
// Created by Марат on 04.05.2024.
//
#include <vector>
#include <string>
#ifndef TAREGEX_NUMANALITICS_H
#define TAREGEX_NUMANALITICS_H

namespace proj{
    class NumAnalitics{
    private:
        std::vector<std::pair<std::string,int>> pairs;

    public:
        void add(std::string a);
        void print();
        NumAnalitics() = default;
    };
}
#endif //TAREGEX_NUMANALITICS_H
