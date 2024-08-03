//
// Created by Марат on 13.07.2024.
//

#ifndef SMS_NUMANALITICS_H
#define SMS_NUMANALITICS_H
//
// Created by Марат on 06.05.2024.
//
#include <vector>
#include <string>
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
#endif //SMS_NUMANALITICS_H
