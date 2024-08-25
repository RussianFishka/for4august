//
// Created by Марат on 18.08.2024.
//
#include <iostream>
#include "myAst.h"
#include <string>
#include <stdexcept>
#include <stack>
#include <algorithm>
#include "usefulfunctions.h"
void ProgramNodePerf(ProgramNode * pn){
    // обработается ошибка в случае отсутствия main
    std::vector<std::pair<int, std::string>>  mistakes;
    std::stack<std::map<std::string, VarNode *> *> your_scope;
    std::map<std::string, VarNode *>  program_scope;
    your_scope.push(&program_scope);
    try {
        std::cout << "The beginning of the program !" << std::endl;;
        for (auto it = pn->declarations.begin(); it != pn->declarations.end(); ++it) {
            if ((*it)->type == func) {
                auto f = (FunctionNode *) *it;
                //f->program = pn;
                auto cname = pn->functions.find(f->name);
                if (cname != pn->functions.end()) {
                    auto str = std::string("Conflicting names of functions");
                    auto pair = std::make_pair(pn->line, str);
                    mistakes.push_back(pair);
                    throw std::domain_error("Conflicting names of functions");
                } else {
                    pn->functions.insert(std::make_pair(f->name, f));
                }
            }
            //if ((*it)->type == vardec) {
            else{ //vardecl
                auto f = (Vardecl *) *it;
                PerformVardecl(f, your_scope, &mistakes);
            }
        }
        if(pn->functions.find("main") == pn->functions.end()){
            auto str = std::string("There must be main");
            auto pair = std::make_pair(pn->line, str);
            mistakes.push_back(pair);
            throw std::domain_error("There must be main");
        }
        //std::stack<std::map<std::string, VarNode *> *> st;
        //st.push()
        PerformFunction(pn->functions.find("main")->second, your_scope, &mistakes, pn); // function call
        freevars(your_scope.top());
        PerformDelete(pn);
        std::cout << "The end of the program !" << std::endl;
    }
    catch(...){
        std::cout << "mistakes" << std::endl;
        for(auto it = mistakes.begin(); it != mistakes.end(); ++it){
            //std::cout << "Mistake /*at line*/ " << it->first << it->second << std::endl;
            std::cout << "Mistake  "<< it->second << std::endl;
        }
        freevars(your_scope.top());
        PerformDelete(pn);
        // PRINTMISTAKES
        //delAST();
    }
}
void PerformDelete(Node *thing) {
    if (!thing) return;

    switch (thing->type) {
        case prog: {
            auto node = (ProgramNode*)thing;
            for (size_t i = 0; i < node->declarations.size(); ++i) {
                PerformDelete(node->declarations[i]);
            }
            delete node;
            break;
        }
        case func: {
            auto node = (FunctionNode*)thing;
            for (size_t i = 0; i < node->body.size(); ++i) {
                PerformDelete(node->body[i]);
            }
            delete node;
            break;
        }
        //case var: {
        //    auto node = (VarNode*)thing;
        //    break;
        //}
        case val: {
            auto node = (ValueNode*)thing;
            for (size_t i = 0; i < node->dimensions.size(); ++i) {
                PerformDelete(node->dimensions[i]);
            }
            delete node;
            break;
        }
        case sub:
        case divv:{
            auto node = (BinaryOpNode*)thing;
            PerformDelete(node->left);
            PerformDelete(node->right);
            delete node;
            break;
        }
        case maxx:
        case minn:
        case mul:
        case add:
        case eq:
        case andd:
        case orr: {
            auto node = (MultiOpNode*)thing;
            for (size_t i = 0; i < node->operands.size(); ++i) {
                PerformDelete(node->operands[i]);
            }
            delete node;
            break;
        }
        case nott: {
            auto node = (UnaryOpNode*)thing;
            PerformDelete(node->operand);
            delete node;
            break;
        }
        case vardecnode: {
            auto node = (VardecNode*)thing;
            for (size_t i = 0; i < node->dimensions.size(); ++i) {
                PerformDelete(node->dimensions[i]);
            }
            for (size_t i = 0; i < node->val.size(); ++i) {
                PerformDelete(node->val[i]);
            }
            delete node;
            break;
        }
        case vardec: {
            auto node = (Vardecl*)thing;
            for (size_t i = 0; i < node->vardecs.size(); ++i) {
                PerformDelete(node->vardecs[i]);
            }
            delete node;
            break;
        }
        case whilee: {
            auto node = (WhileNode*)thing;
            PerformDelete(node->expression);
            for (size_t i = 0; i < node->statements.size(); ++i) {
                PerformDelete(node->statements[i]);
            }
            delete node;
            break;
        }
        case switchh: {
            auto node = (SwitchNode*)thing;
            for (size_t i = 0; i < node->expressions.size(); ++i) {
                PerformDelete(node->expressions[i]);
            }
            for (size_t i = 0; i < node->groups_statements.size(); ++i) {
                for (size_t j = 0; j < node->groups_statements[i].size(); ++j) {
                    PerformDelete(node->groups_statements[i][j]);
                }
            }
            delete node;
            break;
        }
        case funccall: {
            auto node = (FunctionCNode*)thing;
            delete node;
            break;
        }
        case assignn: {
            auto node = (AssignNode*)thing;
            PerformDelete(node->expression);
            for (size_t i = 0; i < node->to.size(); ++i) {
                PerformDelete(node->to[i]);
            }
            delete node;
            break;
        }
        case move: {
            auto node = (MoveNode*)thing;
            PerformDelete(node->expression);
            delete node;
            break;
        }
        default:
            break;
    }
}
void PerformMove(MoveNode *movenode,  std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn){
    ReturnExpValue rv{};
    if(movenode->movetype != getdrones) {
        rv = PerformExpression(movenode->expression, mistakes, your_scope);
    }
    if(rv.vartype == vcell){
        auto str = std::string(" cell? Here?");
        auto pair = std::make_pair(movenode->expression->line, str);
        mistakes->push_back(pair);
        throw std::domain_error("cell? Here?");
    }
    else if(rv.vartype == vbool){
        rv.ival = rv.bval;
    }
    if(movenode->movetype == left){
        for(int i = 0; i < rv.ival; i++){
            movenode->myrobot->moveLeft();
        }
    }
    else if(movenode->movetype == right){
        for(int i = 0; i < rv.ival; i++){
            movenode->myrobot->moveRight();
        }
    }
    else if(movenode->movetype == up){
        for(int i = 0; i < rv.ival; i++){
            movenode->myrobot->moveUp();
        }
    }
    else if(movenode->movetype == down){
        for(int i = 0; i < rv.ival; i++){
            movenode->myrobot->moveDown();
        }
    }
    else if(movenode->movetype == senddrones){
        movenode->myrobot->sendDrones(rv.ival);
    }
    else if(movenode->movetype == getdrones){
        Node *node = new ValueNode(movenode->myrobot->getcurDrones(), movenode->line);
        Node *nodevar = new ValueNode(movenode->name,std::vector<Node *>{}, movenode->line);
        auto asnode = new AssignNode(node, std::vector<Node *>{nodevar}, movenode->line );
        PerformAssign(asnode, your_scope, mistakes, pn);
        delete node;
        delete nodevar;
        delete asnode;
    }
}
bool isExp(Node *node){
    if(node->type == val || node->type == add || node->type == sub || node->type == mul || node->type == minn || node->type == maxx || node->type == divv || node->type == eq
    || node->type == nott || node->type == andd || node->type == orr) {
        return true;
    }
    return false;
}
void freevars(std::map<std::string, VarNode *> * vars){
    for(auto it = vars->begin(); it != vars->end(); ++it){
        if(it->second->vartype == vint){
            delete std::get<std::vector<int>*>(it->second->val);
        }
        else if(it->second->vartype == vbool){
            delete std::get<std::vector<bool>*>(it->second->val);
        }
        else if(it->second->vartype == vcell){
            delete std::get<std::vector<CELL>*>(it->second->val);
        }
        delete it->second;
    }
}
// последний параметр нужен для вызова функций
void PerformFunction(FunctionNode *funcdata, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn){ // функцию можно везде вызвать
    //try catch
    std::cout << "The beginning of the function with the name " << funcdata->name << std::endl;
    FunctionNode cfunc{funcdata->line};
    std::map<std::string, VarNode *> funcscope;
    your_scope.push(&funcscope);
    try {
        for (auto itbody = funcdata->body.begin(); itbody != funcdata->body.end(); ++itbody) {
            if (isExp(*itbody)) {
                PerformExpression(*itbody, mistakes, your_scope);
            } else if ((*itbody)->type == vardec) {
                PerformVardecl((Vardecl *) (*itbody), your_scope, mistakes);
            } else if ((*itbody)->type == funccall) {
                PerformFuncCall((FunctionCNode *) (*itbody), your_scope, mistakes, pn);
            } else if ((*itbody)->type == whilee) {
                PerformWhile((WhileNode *) (*itbody), your_scope, mistakes, pn);
            } else if ((*itbody)->type == switchh) {
                PerformSwitch((SwitchNode *) (*itbody), your_scope, mistakes, pn);
            } else if ((*itbody)->type == assignn) {
                PerformAssign((AssignNode *) (*itbody), your_scope, mistakes, pn);
            } else if ((*itbody)->type == move) {
                PerformMove((MoveNode *) (*itbody), your_scope, mistakes, pn);
            }
        }
        freevars(your_scope.top());
        your_scope.pop(); // область видимости исчезает
        std::cout << "The end of the function with the name " << funcdata->name << std::endl;
    }
    catch(...){
        freevars(your_scope.top());
        your_scope.pop(); // область видимости исчезает
        auto str = std::string("mistake at function with the name ");
        str += funcdata->name;
        auto pair = std::make_pair(funcdata->line, str);
        mistakes->push_back(pair);
        throw std::invalid_argument(str);
    }
}
void PerformFuncCall(FunctionCNode * cnode, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn){
    if(pn->functions.find(cnode->name) == pn->functions.end()){
        auto str = std::string("There is no function with this name");
        auto pair = std::make_pair(cnode->line, str);
        mistakes->push_back(pair);
        throw std::domain_error("There is no function with this name");
    }
    PerformFunction(pn->functions.find(cnode->name)->second, your_scope, mistakes, pn); // function call
}
void PerformSwitch(SwitchNode * node, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn){
    std::cout << "The beginning of the switch " << std::endl;
    std::map<std::string, VarNode *> switchscope;
    your_scope.push(&switchscope);
    try {
        int index = 0;
        for (auto itexp = node->expressions.begin(); itexp != node->expressions.end(); ++itexp, ++index) {
            bool exp = turnNodeintoBool(*itexp, mistakes, your_scope);
            if (exp) {
                std::cout << "This is the " << index << " expression in switch" << std::endl;
                for (auto itst = node->groups_statements[index].begin();
                     itst != node->groups_statements[index].end(); ++itst) {
                    if (isExp(*itst)) {
                        PerformExpression(*itst, mistakes, your_scope);
                    } else if ((*itst)->type == vardec) {
                        PerformVardecl((Vardecl *) (*itst), your_scope, mistakes);
                    } else if ((*itst)->type == funccall) {
                        PerformFuncCall((FunctionCNode *) (*itst), your_scope, mistakes, pn);
                    } else if ((*itst)->type == whilee) {
                        PerformWhile((WhileNode *) (*itst), your_scope, mistakes, pn);
                    } else if ((*itst)->type == switchh) {
                        PerformSwitch((SwitchNode *) (*itst), your_scope, mistakes, pn);
                    } else if ((*itst)->type == assignn) {
                        PerformAssign((AssignNode *) (*itst), your_scope, mistakes, pn);
                    } else if ((*itst)->type == move) {
                        PerformMove((MoveNode *) (*itst), your_scope, mistakes, pn);
                    }
                }
                break;
            }
        }
        freevars(your_scope.top());
        your_scope.pop(); // область видимости исчезает
        std::cout << "The end of the switch " << std::endl;
    }
    catch(...){
        freevars(your_scope.top());
        your_scope.pop(); // область видимости исчезает
        auto str = std::string("mistake at switch ");
        auto pair = std::make_pair(node->line, str);
        mistakes->push_back(pair);
        throw std::invalid_argument("mistake at switch ");
    }
}
int PerformAssign(AssignNode * node, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn){
    // многомерный случай
    std::cout << "The beginning of the assign " << std::endl;
    if (node->expression->type == val) { // задали массив и его надо присвоить
        auto ytnode = (ValueNode *) node->expression;
        if (ytnode->vartype == vname) {
            auto varfrom = stackdiving(ytnode->name, your_scope);
            if (varfrom == nullptr) {
                auto str = std::string("There is not a single variable with this name!");
                auto pair = std::make_pair(node->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("There is not a single variable with this name!!");
            }
            if (varfrom->dimensions.size() != 0 && ytnode->dimensions.size() == 0) { // написали ничего, а в базе размерности есть
                for(auto itvars = node->to.begin(); itvars != node->to.end(); ++itvars){
                    auto nameanddims = (ValueNode *)(*itvars);
                    auto var = stackdiving(nameanddims->name,your_scope);
                    if(var == nullptr){
                        auto str = std::string("There is not a single variable with this name!");
                        auto pair = std::make_pair(nameanddims->line, str);
                        mistakes->push_back(pair);
                        throw std::invalid_argument("There is not a single variable with this name!!");
                    }
                    if(varfrom->vartype != var->vartype && (varfrom->vartype == vcell || var->vartype == vcell)){
                        auto str = std::string("Assign should have same types or at least bool and int");
                        auto pair = std::make_pair(var->line, str);
                        mistakes->push_back(pair);
                        throw std::invalid_argument("Assign should have same types or at least bool and int");
                    }
                    if(var->dimensions.size() != varfrom->dimensions.size()){
                        auto str = std::string("Correct indexes!");
                        auto pair = std::make_pair(nameanddims->line, str);
                        mistakes->push_back(pair);
                        throw std::invalid_argument("Correct indexes!");
                    }
                    // каждая размерность должна совпасть
                    auto it2 = varfrom->dimensions.begin();
                    for(auto it1 = var->dimensions.begin(); it1 != var->dimensions.end(); ++it1, ++it2 ){
                        if(*it1 != *it2){
                            auto str = std::string("Размерности должны быть одинаковыми");
                            auto pair = std::make_pair(nameanddims->line, str);
                            mistakes->push_back(pair);
                            throw std::invalid_argument("Размерности должны быть одинаковыми");
                        }
                    }
                    if(var->vartype == vint){
                        auto vec1 = std::get<std::vector<int>*>(var->val);
                        auto vec2 = std::get<std::vector<int>*>(varfrom->val);
                        *vec1 = *vec2;
                    }
                    else if(var->vartype == vbool){
                        auto vec1 = std::get<std::vector<bool>*>(var->val);
                        auto vec2 = std::get<std::vector<bool>*>(varfrom->val);
                        *vec1 = *vec2;
                    }
                    else if(var->vartype == vcell){
                        auto vec1 = std::get<std::vector<CELL>*>(var->val);
                        auto vec2 = std::get<std::vector<CELL>*>(varfrom->val);
                        *vec1 = *vec2;
                    }
                }
                std::cout << "The end of the assign " << std::endl;
                return 2; // все сделано
            }
        }
    }
        ReturnExpValue value = PerformExpression(node->expression, mistakes, your_scope);
        for (auto itvars = node->to.begin(); itvars != node->to.end(); ++itvars) {
            auto nameanddims = (ValueNode *) (*itvars);
            //std::cout << "dive" << std::endl;
            auto var = stackdiving(nameanddims->name, your_scope);
            //std::cout << "dive" << std::endl;
            if (var == nullptr) {
                auto str = std::string("There is not a single variable with this name!");
                auto pair = std::make_pair(nameanddims->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("There is not a single variable with this name!!");
            }
            if (value.vartype != var->vartype && (value.vartype == vcell || var->vartype == vcell)) {
                auto str = std::string("Assign should have same types or at least bool and int");
                auto pair = std::make_pair(var->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Assign should have same types or at least bool and int");
            }
            if (var->dimensions.size() != nameanddims->dimensions.size()) {
                auto str = std::string("Correct indexes!");
                auto pair = std::make_pair(nameanddims->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Correct indexes!");
            }
            //std::cout << "dive" << std::endl;
            if (var->isConst) {
                auto str = std::string("Константная переменная");
                auto pair = std::make_pair(var->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Константная переменная");
            }
            int index;
            if (var->dimensions.empty()) {
                index = 0;
            } else {
                //std::cout << "dove" << std::endl;
                auto positions = std::move(turnNodesintoInts(nameanddims->dimensions, mistakes, your_scope));
                index = getLinearIndex(var->dimensions, positions, mistakes, nameanddims);
            }
            //std::cout << "dive" << std::endl;
            if (var->vartype == vint) {
                auto vec = std::get<std::vector<int> *>(var->val);
                if((index == 0) && (*vec).empty()){
                    (*vec).push_back(0); // Если тут был не инициализирован массив?
                }
                (*vec)[index] = value.ival;
            } else if (var->vartype == vbool) {
                auto vec = std::get<std::vector<bool> *>(var->val);
                if((index == 0) && (*vec).empty()){
                    (*vec).push_back(true);
                }
                (*vec)[index] = value.bval;
            } else if (var->vartype == vcell) {
                auto vec = std::get<std::vector<CELL> *>(var->val);
                if((index == 0) && (*vec).empty()){
                    (*vec).push_back(WALL);
                }
                (*vec)[index] = value.cvall;
            }
        }
        std::cout << "The end of the assign " << std::endl;
        return 2;
}
void PerformWhile(WhileNode * node, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes, ProgramNode * pn){
    bool exp = turnNodeintoBool(node->expression, mistakes, your_scope);
    std::map<std::string, VarNode *> whilescope;
    your_scope.push(&whilescope);
    std::cout << "The beginning of the while " << std::endl;
    //std::cout << node->statements.size();
    try {
        while (exp) {
            for (auto itst = node->statements.begin(); itst != node->statements.end(); ++itst) {
                if (isExp(*itst)) {
                    PerformExpression(*itst, mistakes, your_scope);
                } else if ((*itst)->type == vardec) {
                    PerformVardecl((Vardecl *) (*itst), your_scope, mistakes);
                } else if ((*itst)->type == funccall) {
                    PerformFuncCall((FunctionCNode *) (*itst), your_scope, mistakes, pn);
                } else if ((*itst)->type == whilee) {
                    PerformWhile((WhileNode *) (*itst), your_scope, mistakes, pn);
                } else if ((*itst)->type == switchh) {
                    PerformSwitch((SwitchNode *) (*itst), your_scope, mistakes, pn);
                } else if ((*itst)->type == assignn) {
                    PerformAssign((AssignNode *) (*itst), your_scope, mistakes, pn);
                } else if ((*itst)->type == move) {
                    PerformMove((MoveNode *) (*itst), your_scope, mistakes, pn);
                }
            }
            exp = turnNodeintoBool(node->expression, mistakes, your_scope);
        }
        std::cout << "The end of the while " << std::endl;
        freevars(your_scope.top());
        your_scope.pop(); // область видимости исчезает
    }
    catch(...){
        freevars(your_scope.top());
        your_scope.pop(); // область видимости исчезает
        auto str = std::string("mistake at while ");
        auto pair = std::make_pair(node->line, str);
        mistakes->push_back(pair);
        throw std::invalid_argument("mistake at while");
    }
}
void PerformVardecl(Vardecl * vardecl, std::stack<std::map<std::string, VarNode *> *> &your_scope, std::vector<std::pair<int, std::string>> * mistakes){
// переменные кладутся в вершину стека
    auto here = your_scope.top();
    std::cout << "The beginning of declaration block" << std::endl;
    for(auto iteachvar = vardecl->vardecs.begin(); iteachvar != vardecl->vardecs.end(); ++iteachvar){
        auto curvar = (VardecNode *)(*iteachvar);
        auto checkname = stackdiving(curvar->name,your_scope);
        if(checkname != nullptr){ // переменная с таким именем уже есть
            auto str = std::string("There is a variable that has been already added with the name ");
            str += checkname->name;
            auto pair = std::make_pair(curvar->line, str);
            mistakes->push_back(pair);
            //throw std::invalid_argument("There is a variable with the name ");
        }
        std::vector<int> dims = std::move(turnNodesintoInts(curvar->dimensions, mistakes, your_scope));
        std::vector<ReturnExpValue> values;
        if(!curvar->val.empty()){ // инициализированная переменная
            auto itdims = dims.begin(); // размерности должны совпадать. Сейчас это проверим
            int s_of_dims = 0;
            if(itdims != dims.end()){
                s_of_dims = *dims.begin();
                itdims++;
                for(; itdims != dims.end(); ++itdims){
                    s_of_dims *= *itdims;
                }
            }
            if( !(curvar->val.size() == 1 && dims.empty()) && curvar->val.size() != s_of_dims){ // та самая ошибка
                auto str = std::string("Размерность dims должна совпадать с values при объявлении, если values есть");
                auto pair = std::make_pair(curvar->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Размерность dims должна совпадать с values при объявлении, если values есть");
            }
            bool toint = false; // в спорной ситуации, когда будут и int и false в values
            if(curvar->vartype == vint){
                toint = true;
            }
            values = turnNodesintoValues(curvar->val, mistakes, your_scope, toint);
            // проверка на то, когда в values оказался не тот тип данных. CELL вместо int и наооборот
            if(values.begin()->vartype != curvar->vartype){
                auto str = std::string("Не тот тип данных подсовываешь");
                auto pair = std::make_pair(curvar->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Не тот тип данных подсовываешь");
            }
            // надо в функции добавить флаг, показывающий к какому типу приводим
            //values
        }
        // теперь, когда все готово создается новая переменная
        // необходимо из values сделать один нормальный вектор. Я знаю, что это вектор данных с одним типом и приведен
        VarNode *new_var;
        if(curvar->vartype == vint){
            std::vector<int> vec;
            for(auto itt = values.begin(); itt != values.end(); ++itt){
                vec.push_back(itt->ival);
            }
            auto vecptr = new std::vector<int>(vec);
            new_var = new VarNode(curvar->name,curvar->isConst,vint,dims,vecptr,curvar->line);
        }
        else if(curvar->vartype == vbool){
            std::vector<bool> vec;
            for(auto itt = values.begin(); itt != values.end(); ++itt){
                vec.push_back(itt->bval);
            }
            auto vecptr = new std::vector<bool>(vec);
            new_var = new VarNode(curvar->name,curvar->isConst,vbool,dims,vecptr,curvar->line);
        }
        else{// vcell
            std::vector<CELL> vec;
            for(auto itt = values.begin(); itt != values.end(); ++itt){
                vec.push_back(itt->cvall);
            }
            auto vecptr = new std::vector<CELL>(vec);
            new_var = new VarNode(curvar->name,curvar->isConst, vcell, dims,vecptr, curvar->line);
        }
        printVarNode(new_var);
        here->insert(std::make_pair(new_var->name, new_var));
    }
    std::cout << "The end of declaration block" << std::endl;
}
void printVarNode(VarNode *varnode){
    std::cout << "New variable with the name " << varnode->name << std::endl;
    std::cout << "const " << varnode->isConst <<  std::endl;
    if(!varnode->dimensions.empty()) {
        std::cout << "dimensions ";
        for (auto it = varnode->dimensions.begin(); it != varnode->dimensions.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

    }
    if(varnode->vartype == vint){
        std::vector<int> values = *std::get<std::vector<int> *>(varnode->val);
        std::cout << "Type int" << std::endl;
        if(!values.empty()){
            std::cout << "values ";
        }
        for (auto value = values.begin(); value != values.end(); ++value) {
            std::cout << *value << " ";
        }
        std::cout << std::endl;
    }
    else if(varnode->vartype == vbool){
        std::vector<bool> values = *std::get<std::vector<bool> *>(varnode->val);
        std::cout << "Type bool" << std::endl;
        if(!values.empty()){
            std::cout << "values ";
        }
        for (auto value = values.begin(); value != values.end(); ++value) {
            std::cout << *value << " ";
        }
        std::cout << std::endl;
    }
    else{// vcell
        std::vector<CELL> values = *std::get<std::vector<CELL>*>(varnode->val);
        std::cout << "Type CELL" << std::endl;
        if(!values.empty()){
            std::cout << "values ";
        }
        for (auto value = values.begin(); value != values.end(); ++value) {
            //if(*value == EMPTY){
            //    std::cout << "EMPTY" <<
            //}
            std::cout << *value << " ";
        }
        std::cout << std::endl;
    }
}
VarNode *stackdiving(std::string &name, std::stack<std::map<std::string, VarNode *> *> &your_scope){ // возвращает переменную
    std::stack<std::map<std::string, VarNode *> *> put_here;
    while(!your_scope.empty()){
        auto top = your_scope.top();
        auto it = top->find(name);
        if(it != top->end()){
            //std::cout << "message" << std::endl;
            while(!put_here.empty()){
                your_scope.push(put_here.top());
                put_here.pop();
            }
            return it->second;
        }
        put_here.push(your_scope.top());
        your_scope.pop();
    }
    while(!put_here.empty()){
        your_scope.push(put_here.top());
        put_here.pop();
    }
    return nullptr;
}
std::vector<int> turnNodesintoInts(std::vector<Node *> nodes, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope ){
    std::vector<int> here;
    for(auto it = nodes.begin(); it != nodes.end(); ++it){
        ReturnExpValue temp = PerformExpression(*it, mistakes, your_scope);
        if(temp.vartype == vcell){
            auto str = std::string("You said that it is int or bool!!!!!");
            auto pair = std::make_pair((*it)->line, str);
            mistakes->push_back(pair);
            throw std::invalid_argument("You said that it is int or bool!!!!!");
        }
        else if(temp.vartype == vbool){
            here.push_back(temp.bval);
        }
        else {
            here.push_back(temp.ival);
        }
    }
    return here;
}
std::vector<bool> turnNodesintoBools(std::vector<Node *> nodes, std::vector<std::pair<int, std::string>> *mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope) {
    std::vector<bool> here;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        ReturnExpValue temp = PerformExpression(*it, mistakes, your_scope);
        if (temp.vartype == vcell) {
            auto str = std::string("You said that it is int or bool!!!!!");
            auto pair = std::make_pair((*it)->line, str);
            mistakes->push_back(pair);
            throw std::invalid_argument("You said that it is int or bool!!!!!");
        } else if (temp.vartype == vbool) {
            here.push_back(temp.bval);
        } else {
            here.push_back(temp.ival);
        }
    }
    return here;
}
std::vector<ReturnExpValue> turnNodesintoValues(std::vector<Node *> nodes, std::vector<std::pair<int, std::string>> *mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope, bool toint = false) { // надо написать тип, к которому приводим
    std::vector<ReturnExpValue> here;
    int a,b,c;
    a = b = c = 0;
    Node * node;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        ReturnExpValue temp = PerformExpression(*it, mistakes, your_scope);
        if (temp.vartype == vcell) {
            node = *it;
            a++;
            ReturnExpValue rv{};
            rv.vartype = vcell;
            rv.cvall = temp.cvall;
            here.push_back(rv);
        } else if (temp.vartype == vbool) {
            ReturnExpValue rv{};
            rv.vartype = vbool;
            rv.bval = temp.bval;
            here.push_back(rv);
        } else {
            c++;
            ReturnExpValue rv{};
            rv.vartype = vint;
            rv.ival = temp.ival;
            here.push_back(rv);
        }
    }
    if(a*c != 0 || b*c != 0){ // есть неприводимые типы
        auto str = std::string("Here semantic error cell cannot be converted");
        auto pair = std::make_pair(node->line, str);
        mistakes->push_back(pair);
        throw std::invalid_argument("Here semantic error cell cannot be converted");
    }
    if(a*b != 0){ // к bool
        if(!toint) {
            for (auto it = here.begin(); it != here.end(); ++it) {
                if (it->vartype == vint) {
                    it->bval = it->ival;
                    it->vartype = vbool;
                }
            }
        }
        else{ // to int
            for (auto it = here.begin(); it != here.end(); ++it) {
                if (it->vartype == vbool) {
                    it->ival = it->bval;
                    it->vartype = vint;
                }
            }
        }
    }
    return here;
}
std::pair<int,int> turnTwoNodesintoInts(Node *first, Node *second, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope ){
    int l,r;
    ReturnExpValue templ = PerformExpression(first, mistakes, your_scope);
    if(templ.vartype == vcell){
        auto str = std::string("You said that it is int or bool!!!!!");
        auto pair = std::make_pair(first->line, str);
        mistakes->push_back(pair);
        throw std::invalid_argument("You said that it is int or bool!!!!!");
    }
    else if(templ.vartype == vbool){
        l = templ.bval;
    }
    else {
        l = templ.ival;
    }
    ReturnExpValue tempr = PerformExpression(second, mistakes, your_scope);
    if(tempr.vartype == vcell){
        auto str = std::string("You said that it is int or bool!!!!!");
        auto pair = std::make_pair(second->line, str);
        mistakes->push_back(pair);
        throw std::invalid_argument("You said that it is int or bool!!!!!");
    }
    else if(tempr.vartype == vbool){
        r = tempr.bval;
    }
    else {
        r = tempr.ival;
    }
    return std::make_pair(l,r);
}
bool turnNodeintoBool(Node *first, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope ){
    bool f;
    ReturnExpValue templ = PerformExpression(first, mistakes, your_scope);
    if(templ.vartype == vcell){
        auto str = std::string("You said that it is int or bool!!!!!");
        auto pair = std::make_pair(first->line, str);
        mistakes->push_back(pair);
        throw std::invalid_argument("You said that it is int or bool!!!!!");
    }
    else if(templ.vartype == vbool){
        f = templ.bval;
    }
    else {
        f = templ.ival;
    }
    return f;
}
ReturnExpValue PerformExpression(Node *exp, std::vector<std::pair<int, std::string>> * mistakes, std::stack<std::map<std::string, VarNode *> *> &your_scope){
    try {
        //std::cout << "expression perform" << std::endl;
        ReturnExpValue rv{};
        if (exp->type == val) { // что возвращает? varNode, ValNode - временную переменную создаем
            auto ytnode = (ValueNode *)exp;
            if(ytnode->vartype == vname){
                auto var = stackdiving(ytnode->name, your_scope);
                if(var == nullptr){
                    auto str = std::string("There is not a single variable with this name!");
                    auto pair = std::make_pair(exp->line, str);
                    mistakes->push_back(pair);
                    throw std::invalid_argument("There is not a single variable with this name!!");
                }
                if(var->dimensions.size() != ytnode->dimensions.size()){
                    auto str = std::string("Correct indexes!");
                    auto pair = std::make_pair(exp->line, str);
                    mistakes->push_back(pair);
                    throw std::invalid_argument("Correct indexes!");
                }
                rv.vartype = var->vartype;
                if(var->dimensions.empty()){
                    if(var->vartype == vint){
                        auto vec = *std::get<std::vector<int>*>(var->val);
                        rv.ival = vec.front();
                    }
                    else if(var->vartype == vbool){
                        auto vec = *std::get<std::vector<bool>*>(var->val);
                        rv.bval = vec.front();
                    }
                    else if(var->vartype == vcell){
                        auto vec = *std::get<std::vector<CELL>*>(var->val);
                        rv.cvall = vec.front();
                    }
                }
                else{
                    auto positions = std::move(turnNodesintoInts(ytnode->dimensions,mistakes,your_scope));
                    int index = getLinearIndex(var->dimensions, positions, mistakes, exp);
                    if(var->vartype == vint){
                        auto vec = *std::get<std::vector<int>*>(var->val);
                        rv.ival = vec[index];
                    }
                    else if(var->vartype == vbool){
                        auto vec = *std::get<std::vector<bool>*>(var->val);
                        rv.bval = vec[index];
                    }
                    else if(var->vartype == vcell){
                        auto vec = *std::get<std::vector<CELL>*>(var->val);
                        rv.cvall = vec[index];
                    }
                }
            }
            else if(ytnode->vartype == vcell){
                rv.vartype = vcell;
                rv.cvall = ytnode->val.cellvall;
            }
            else if(ytnode->vartype == vint){
                rv.vartype = vint;
                rv.ival = ytnode->val.intval;
            }
            else{//vbool
                rv.vartype = vbool;
                rv.bval = ytnode->val.boolval;
            }
            //PerformValue // как понять какой тип возвращается? std::pair VarType + union проверка только тогда, когда vname
            // среди глобальных переменных и среди std::stack
            //while()
        } // похоже assign в бизоне надо слегка переделать
        else if(exp->type == add){ // если мы суммируем false мы получаем int
            rv.vartype = vint;
            auto ytnode = (MultiOpNode *)exp;
            auto values = std::move(turnNodesintoInts(ytnode->operands,mistakes,your_scope));
            int res = 0;
            if(values.size() < 2){
                auto str = std::string("Here should be 2 or more arguments!");
                auto pair = std::make_pair(exp->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Here should be 2 or more arguments!!!");
            }
            for(auto itadd = values.begin(); itadd != values.end(); ++itadd){
                res += *itadd;
            }
            std::cout << "Addition with " << values.size() << " elements" << std::endl;
            for(auto showit = values.begin(); showit != values.end(); ++showit){
                std::cout << *showit <<" ";
            }
            std::cout << "result " << res << std::endl;
            rv.ival = res;
        }
        else if(exp->type == mul){ // если мы суммируем false мы получаем int
            rv.vartype = vint;
            auto ytnode = (MultiOpNode *)exp;
            auto values = std::move(turnNodesintoInts(ytnode->operands,mistakes,your_scope));
            if(values.size() < 2){
                auto str = std::string("Here should be 2 or more arguments!");
                auto pair = std::make_pair(exp->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Here should be 2 or more arguments!!!");
            }
            auto itmul = values.begin();
            int res = *itmul;
            itmul++;
            for(; itmul != values.end(); ++itmul){
                res *= *itmul;
            }
            std::cout << "Mul with " << values.size() << " elements" << std::endl;
            for(auto showit = values.begin(); showit != values.end(); ++showit){
                std::cout << *showit <<" ";
            }
            std::cout << "result " << res << std::endl;
            rv.ival = res;
        }
        else if(exp->type == sub){
            rv.vartype = vint;
            auto ytnode = (BinaryOpNode *)exp;
            auto values = std::move(turnTwoNodesintoInts(ytnode->left, ytnode->right,mistakes,your_scope));
            int res = values.first - values.second;
            std::cout << "Sub " << std::endl;
            std::cout << values.first << " " << values.second << " ";
            std::cout << "result " << res << std::endl;
            rv.ival = res;
        }
        else if(exp->type == divv){
            rv.vartype = vint;
            auto ytnode = (BinaryOpNode *)exp;
            auto values = std::move(turnTwoNodesintoInts(ytnode->left, ytnode->right,mistakes,your_scope));
            int res = values.first / values.second;
            std::cout << "Div " << std::endl;
            std::cout << values.first << " " << values.second << " ";
            std::cout << "result " << res << std::endl;
            rv.ival = res;
        }
        else if(exp->type == minn){
            rv.vartype = vint;
            auto ytnode = (MultiOpNode *)exp;
            auto values = std::move(turnNodesintoInts(ytnode->operands,mistakes,your_scope));
            if(values.size() < 1){
                auto str = std::string("Here should be 1 or more arguments!");
                auto pair = std::make_pair(exp->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Here should be 1 or more arguments!!!");
            }
            auto min_it = std::min_element(values.begin(), values.end());
            std::cout << "Min with " << values.size() << " elements" << std::endl;
            for(auto showit = values.begin(); showit != values.end(); ++showit){
                std::cout << *showit <<" ";
            }
            std::cout << "result " << *min_it << std::endl;
            rv.ival = *min_it;
        }
        else if(exp->type == maxx){
            rv.vartype = vint;
            auto ytnode = (MultiOpNode *)exp;
            auto values = std::move(turnNodesintoInts(ytnode->operands,mistakes,your_scope));
            if(values.size() < 1){
                auto str = std::string("Here should be 1 or more arguments!");
                auto pair = std::make_pair(exp->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Here should be 1 or more arguments!!!");
            }
            auto max_it = std::max_element(values.begin(), values.end());
            std::cout << "Max with " << values.size() << " elements" << std::endl;
            for(auto showit = values.begin(); showit != values.end(); ++showit){
                std::cout << *showit <<" ";
            }
            std::cout << "result " << *max_it << std::endl;
            rv.ival = *max_it;
        }
        else if(exp->type == orr){
            rv.vartype = vbool;
            auto ytnode = (MultiOpNode *)exp;
            auto values = std::move(turnNodesintoBools(ytnode->operands,mistakes,your_scope));
            if(values.size() < 2){
                auto str = std::string("Here should be 2 or more arguments!");
                auto pair = std::make_pair(exp->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Here should be 2 or more arguments!!!");
            }
            auto itadd = values.begin();
            bool res = *itadd;
            itadd++;
            for(; itadd != values.end(); ++itadd){
                res = res || *itadd;
            }
            std::cout << "Or with " << values.size() << " elements" << std::endl;
            for(auto showit = values.begin(); showit != values.end(); ++showit){
                std::cout << *showit <<" ";
            }
            std::cout << "result " << res << std::endl;
            //bool k = false | true;
            rv.bval = res;
        }
        else if(exp->type == andd){
            rv.vartype = vbool;
            auto ytnode = (MultiOpNode *)exp;
            auto values = std::move(turnNodesintoBools(ytnode->operands,mistakes,your_scope));
            if(values.size() < 2){
                auto str = std::string("Here should be 2 or more arguments!");
                auto pair = std::make_pair(exp->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Here should be 2 or more arguments!!!");
            }
            auto itadd = values.begin();
            bool res = *itadd;
            itadd++;
            for(; itadd != values.end(); ++itadd){
                res = res && *itadd;
            }
            std::cout << "And with " << values.size() << " elements" << std::endl;
            for(auto showit = values.begin(); showit != values.end(); ++showit){
                std::cout << *showit <<" ";
            }
            std::cout << "result " << res << std::endl;
            rv.bval = res;
        }
        else if(exp->type == nott){
            rv.vartype = vbool;
            auto ytnode = (UnaryOpNode *)exp;
            auto value = turnNodeintoBool(ytnode->operand,mistakes,your_scope);
            rv.bval = !value;
        }
        else{ //eq
            rv.vartype = vbool;
            auto ytnode = (MultiOpNode *)exp;
            auto values = std::move(turnNodesintoValues(ytnode->operands,mistakes,your_scope, false));
            if(values.size() < 2){
                auto str = std::string("Here should be 2 or more arguments!");
                auto pair = std::make_pair(exp->line, str);
                mistakes->push_back(pair);
                throw std::invalid_argument("Here should be 2 or more arguments!!!");
            }
            // все типы одинаковые
            auto itadd = values.begin();
            bool res = true;
            if(itadd->vartype == vint){
                int temp;
                temp = itadd->ival;
                itadd++;
                for(; itadd != values.end(); ++itadd){
                    if(temp != itadd->ival){
                        res = false;
                        break;
                    }
                }
            }
            else if(itadd->vartype == vbool){
                bool temp;
                temp = itadd->bval;
                itadd++;
                for(; itadd != values.end(); ++itadd){
                    if(temp != itadd->bval){
                        res = false;
                        break;
                    }
                }
            }
            else{// vcell
                CELL temp;
                temp = itadd->cvall;
                itadd++;
                for(; itadd != values.end(); ++itadd){
                    if(temp != itadd->cvall){
                        res = false;
                        break;
                    }
                }
            }
            std::cout << "Eq with " << values.size() << " elements" << std::endl;
            std::cout << "result " << res << std::endl;
            rv.bval = res;
        }
        return rv;
    }
    catch(...){
        throw;
    }
}
