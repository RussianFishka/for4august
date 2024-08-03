//
// Created by Марат on 22.07.2024.
//

#ifndef LAB2TA_DEFAST_H
#define LAB2TA_DEFAST_H
#pragma once
#include <iostream>
#include <unordered_map>
#include <memory>
#include <iterator>
#include <string>
#include <list>
struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    //Node* par = nullptr; // мб сделать рекурсию?
    char symbol;
    std::string capture_group_cbracketsnum; // наследование + динамическое связывание
    bool true_symbol = false; // специальный символ экранирован == true
    explicit Node(char _symbol) : symbol(_symbol){};
};
class Ast {
public:
    Node* root = nullptr;
    //std::unordered_map<std::string, std::shared_ptr<Node>> capture_groups;
    explicit Ast(const std::string& myregex);
    void ShowTree() const;
    ~Ast(){
        delete_tree(root);
    }
private:
    void PutTree(Node *ptr, int level) const;
    std::pair<std::list<Node *>::iterator,std::list<Node *>::iterator> find_first_and_last(std::list<Node *>::iterator begin, std::list<Node *>::iterator end);
    void del_escapes_properly(std::list<Node *> &mylist);
    void delete_tree(Node* tr);
};
#endif //LAB2TA_DEFAST_H
