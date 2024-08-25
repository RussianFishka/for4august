//
// Created by Марат on 22.07.2024.
//

#ifndef LAB2TA_DIFNODES_H
#define LAB2TA_DIFNODES_H
#pragma once
#include <string>
#include <memory> // Используется для умных указателей

class Node {
public:
    virtual ~Node() = default;
    virtual char get_value() const = 0; // виртуальная функция без определения
};
class SymbolNode : public Node {
    char literal;

    explicit SymbolNode(char lit) : literal(lit) {}
    char get_value() const override {
        return literal;
    }
};
class UNode : public Node {
public:
    std::shared_ptr<Node> child;
    explicit UNode(std::shared_ptr<Node> child) : child(std::move(child)) {}

};
class BNode : public Node {
public:
    std::shared_ptr<Node> first_child;
    std::shared_ptr<Node> second_child;

    explicit BNode(std::shared_ptr<Node> first, std::shared_ptr<Node> second)
            : first_child(std::move(first)), second_child(std::move(second)) {}
};
class OrNode : public BNode {
    explicit OrNode(std::shared_ptr<Node> left_child, std::shared_ptr<Node> right_child)
            : BNode(std::move(left_child), std::move(right_child)) {}

    char get_value() const override {
        return '|';
    }
};

class ConcNode : public BNode { // вместо точки по центру
    explicit ConcNode(std::shared_ptr<Node> left_child, std::shared_ptr<Node> right_child)
            : BNode(std::move(left_child), std::move(right_child)) {}

    char get_value() const override {
        return '&'; // в моей библиотеке конкатенацию можно двумя способами писать
    }
};
class RepeatNode : public UNode {
protected:
    int min; // количество вхождений от 0
    int max;// max 10000
public:
    explicit RepeatNode(std::shared_ptr<Node> child) : UNode(std::move(child)) {}

    char get_value() const override {
        return '*';
    }
};

class CaptureGroupNode : public UNode {
    std::string name; // имя группы захвата
    explicit CaptureGroupNode(std::string name, std::shared_ptr<Node> child = nullptr) : name(std::move(name)), UNode(std::move(child)) {}
    char get_value() const override {
        return '<';
    }
};

#endif //LAB2TA_DIFNODES_H
