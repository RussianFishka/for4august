//
// Created by Марат on 06.05.2024.
//
#include <vector>
#include <string>
#ifndef FLEXPART_NUMANALITICS_H
#define FLEXPART_NUMANALITICS_H
namespace proj{
    class NumAnalitics{
    private:
        std::vector<std::pair<std::string,int>> pairs;

    public:
        void add(std::string a);
        void print();
        NumAnalitics() = default;
    };
    void checkstringf(const char * argv, proj::NumAnalitics & store);
}
#endif //FLEXPART_NUMANALITICS_H
