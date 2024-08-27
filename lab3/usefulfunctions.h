//
// Created by Марат on 18.08.2024.
//

#ifndef LAB3TA_USEFULFUNCTIONS_H
#define LAB3TA_USEFULFUNCTIONS_H
#include <vector>
#include <string>
#include <stdexcept>
#include "myAst.h"
int getLinearIndex(const std::vector<int>& dimensions, const std::vector<int>& positions, std::vector<std::pair<int, std::string>> * mistakes, Node *exp);
#endif //LAB3TA_USEFULFUNCTIONS_H
