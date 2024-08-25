//
// Created by Марат on 15.08.2024.
//

#ifndef LAB3TA_MYAST_H
#define LAB3TA_MYAST_H
#include <map>
#include <string>
#include "cellandother.h"
#include <vector>
#include <variant>
#include <stack>
#include "myRobot.h"
typedef enum {
    vint,
    vbool,
    vcell,
    vname // 4 типа данных. 1 не установленный это когда единичная переменная определена
    //vnamemany //
} Vartype;

typedef enum{
    left,
    right,
    up,
    down,
    senddrones,
    getdrones
} Movetype;
enum NodeType {
    prog,//done!
    func,//works
    var,// not interesting
    val,// exp bool int cell
    add,//exp int
    sub,//exp int
    mul,//exp int
    minn,//exp int
    maxx,//exp int
    divv,//exp int
    eq,//exp bool
    nott,//exp int
    andd,//exp bool
    orr,//exp bool
    vardecnode,//done!
    vardec,//done!
    whilee,// in the process
    switchh, // надо потестить
    funccall,// done! need to test with variables
    assignn, // next
    move
};

typedef struct Node {
    NodeType type;
    int line;
} Node;
struct MoveNode : Node{
    Movetype movetype;
    Robot * myrobot;
    Node *expression = nullptr;
    std::string name;
    MoveNode(Movetype m, Robot *r, int linee, Node *e) : Node{move, linee}, movetype(m), myrobot(r), expression(e)  {}
    MoveNode(Movetype m, Robot *r, int linee, std::string st) : Node{move, linee}, movetype(m), myrobot(r), name(std::move(st))  {}
};
// Узел для значений (чисел и логических значений)
struct ValueNode : Node {
    Vartype vartype; // многомерные массивы складывать нельзя
    std::string name; // чтобы однозначно определить переменную по этим показателям
    std::vector<Node *> dimensions;
    union {
        int intval; // размер равен размеру максимального. Корректно работает при выборе любого
        bool boolval; // vartype = int; val.intval =
        CELL cellvall; // арифметика определена для int и bool
    } val;
    // Конструктор для int
    explicit ValueNode(int value, int linee) : Node{NodeType::val, linee}, vartype(vint) {
        val.intval = value;
    }
    // Конструктор для bool
    explicit ValueNode(bool value, int linee) : Node{NodeType::val, linee}, vartype(vbool) {
        val.boolval = value;
    }
    // Конструктор для CELL
    explicit ValueNode(CELL value, int linee) : Node{NodeType::val, linee}, vartype(vcell) {
        val.cellvall = value;
    }
    explicit ValueNode(std::string n, std::vector<Node *> v, int linee) : Node{NodeType::val, linee}, vartype(vname), name(std::move(n)), dimensions(std::move(v)) {}
};

// Узел для бинарных операций
struct BinaryOpNode : Node {
    Node *left; // value and binary or unary or multi
    Node *right;
    BinaryOpNode(Node *l, Node *r, NodeType o, int linee)
            : Node{o, linee}, left(l), right(r) {}
};

// Узел для унарных операций
struct UnaryOpNode : Node {
    Node *operand;
    UnaryOpNode(Node *operand, NodeType op, int linee)
            : Node{op, linee}, operand(operand) {}
};

// Узел для операций с несколькими аргументами
struct MultiOpNode : Node {
    std::vector<Node *> operands;
    MultiOpNode(std::vector<Node *> ops, NodeType o, int linee)
            : Node{o, linee}, operands(std::move(ops)) {}
};

// Узел для списка выражений
//struct ExpressionListNode{ // единственно для multiopNode
//    std::vector<Node *>  expressions; // по крайней мере 2
//    explicit ExpressionListNode(std::vector<Node *> exprs) : expressions(std::move(exprs)) {}
//};

struct Ast {
    Node *root;
    explicit Ast(Node *prog) : root(prog) {}
};

struct Vardecl : Node { // пока что в vardecnode хранятся разные приколы
    std::vector<Node *> vardecs;
    explicit Vardecl(std::vector<Node *> v, int linee) : Node{vardec, linee}, vardecs(std::move(v)) {}
};

struct VardecNode : Node {
    Vartype vartype;
    std::string name; // имя переменной
    bool isConst;
    std::vector<Node *> dimensions;
    std::vector<Node *> val;
    //Node *numofdims;
    explicit VardecNode(Vartype v, std::string n, bool isc, std::vector<Node *> d, std::vector<Node *> va, int linee)
            : Node{vardecnode, linee}, vartype(v), name(std::move(n)), isConst(isc), dimensions(std::move(d)), val(std::move(va)) {}
};

struct VarNode : Node { // не инициализирована = лежит пустой контейнер
    Vartype vartype;
    std::string name;
    bool isConst;
    std::variant<std::vector<int> *, std::vector<bool> *, std::vector<CELL> *> val;
    std::vector<int> dimensions;
    explicit VarNode(std::string n, bool c, Vartype t, std::vector<int> d, std::vector<int> *v , int linee)
            : Node{var, linee}, name(std::move(n)), isConst(c), vartype(t), dimensions(std::move(d)), val(std::move(v)) {}
    VarNode(std::string n, bool c, Vartype t, std::vector<int> d, std::vector<bool> *v, int linee)
            : Node{var, linee}, name(std::move(n)), isConst(c), vartype(t), dimensions(std::move(d)), val(std::move(v)) {}
    VarNode(std::string n, bool c, Vartype t, std::vector<int> d, std::vector<CELL> *v, int linee)
            : Node{var, linee}, name(std::move(n)), isConst(c), vartype(t), dimensions(std::move(d)), val(std::move(v)) {}
};

struct ReturnExpValue { // идейно сюда могли засунуть многоразмерную переменную и она попала в add ...
    Vartype vartype;
    int ival;
    bool bval;
    CELL cvall; // в eq эта переменная имеет смысл
};

struct AssignNode : Node {
    Node *expression;
    std::vector<Node *> to; // valueNodes
    AssignNode(Node *e, std::vector<Node *> t, int linee)
            : Node{assignn, linee}, expression(e), to(std::move(t)) {}
};

struct WhileNode : Node { // express + statements
    Node *expression;
    std::vector<Node *> statements;
    WhileNode(Node *e, std::vector<Node *> s, int linee)
            : Node{whilee, linee}, expression(e), statements(std::move(s)) {}
};

struct SwitchNode : Node {
    std::vector<Node *> expressions;
    std::vector<std::vector<Node *>> groups_statements;
    explicit SwitchNode(int linee) : Node{switchh, linee} {}
    //SwitchNode(std::vector<Node *> e, std::vector<std::vector<Node *>> g) : expressions(std::move(e)), groups_statements(std::move(g)) {}
};

struct FunctionCNode : Node {
    std::string name;
    explicit FunctionCNode(std::string n, int linee) : Node{funccall, linee}, name(std::move(n)) {}
};

// Узел для программ
struct FunctionNode;
struct ProgramNode : Node {
    std::map<std::string, FunctionNode *> functions; // в том числе main
    std::map<std::string, VarNode *> global_vars; // это можно оставить
    std::vector<Node *> declarations; // глобальные переменные и функции изначально будут здесь 24 байта на всю программу
    explicit ProgramNode(int linee) : Node{prog, linee} {}
};

// Узел для функций
struct FunctionNode : Node { // встречаю call. Создаю новую структуру, беру тело от нее FunctionNode
    //ProgramNode *program; // для доступа к глобальным переменным и вызова других функций.
    std::string name;
    //std::map<std::string, VarNode *> variables;
    std::vector<Node *> body;
    explicit FunctionNode(int linee) : Node{func, linee} {}
    FunctionNode(std::string n, std::vector<Node *> b, int linee) : Node{func, linee}, name(std::move(n)), body(std::move(b)) {}
};
void PerformDelete(Node *thing);
void PerformMove(MoveNode *movenode,  std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn);
void freevars(std::map<std::string, VarNode *> * vars);
void PerformSwitch(SwitchNode * node, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn);
int PerformAssign(AssignNode * node, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn);
void PerformWhile(WhileNode * node, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn);
void PerformFuncCall(FunctionCNode * cnode, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn);
void printVarNode(VarNode *varnode);
std::vector<ReturnExpValue> turnNodesintoValues(std::vector<Node *> nodes, std::vector<std::pair<int, std::string>> *mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope, bool toint);
void PerformVardecl(Vardecl * vardecl, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes);
ReturnExpValue PerformExpression(Node *exp, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope);
void ProgramNodePerf(ProgramNode * pn);
VarNode *stackdiving(std::string &name, std::stack<std::map<std::string, VarNode *> *> &your_scope);
std::vector<int> turnNodesintoInts(std::vector<Node *> nodes, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *>*> &your_scope );
std::pair<int,int> turnTwoNodesintoInts(Node *first, Node *second, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *>*> &your_scope );
std::vector<bool> turnNodesintoBools(std::vector<Node *> nodes, std::vector<std::pair<int, std::string>> *mistakes, std::stack<std::map<std::string, VarNode *>*> &your_scope);
bool turnNodeintoBool(Node *first, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *>*> &your_scope );
void PerformFunction(FunctionNode *funcdata, std::stack<std::map<std::string, VarNode *>*> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn);
bool isExp(Node *node);
#endif //LAB3TA_MYAST_H
