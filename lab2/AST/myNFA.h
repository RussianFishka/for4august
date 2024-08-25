//
// Created by Марат on 26.07.2024.
//

#ifndef LAB2TA_MYNFA_H
#define LAB2TA_MYNFA_H
#include <vector>
#include <set>
#include <string>
#include <map>
#include "defast.h"
#include <memory>
//#include "myDFA.h"
// parent??
// имя у автомата будет
struct Transition{
    char type;
    char symbol;
    int to;
public:
    Transition(char t, char s, int _to) : type(t), symbol(s), to(_to){}
};
bool operator < (const  Transition& cur, const Transition& other) {
    if (cur.type != other.type) {
        return cur.type < other.type;
    }
    if (cur.symbol != other.symbol) {
        return cur.symbol < other.symbol;
    }
    return cur.to < other.to;
}
bool operator < (const  std::pair<char,char>& cur, const std::pair<char,char>& other) {
    if (cur.first != other.first) {
        return cur.first < other.first;
    }
    return cur.second < other.second;
}
struct State{
    int index; // номер состояния
    std::multimap<std::pair<char, char>,std::shared_ptr<Transition>> transitions; // первый символ e(ps)|s(ym)|c(ap) второй - символ
public:
    explicit State(int num) : index(num) {}
}; //  И номер состояния
class NFA{ // коллизии имен надо проверить
public:
    int start;
    int last;
    std::map<int, std::shared_ptr<State>> states; // по индексу состояния будем искать
    std::string name;
    std::map<std::shared_ptr<Transition> , std::shared_ptr<NFA>> capture_groups; // int - начальное состояние автомата сквозная нумерация
public:
    //NFA(std::shared_ptr<DFA>);
    void Myprint();
    explicit NFA(Ast & myast);
    NFA(int s, std::string &pname);
    NFA();
    explicit NFA(int sstate);
private:
    std::shared_ptr<NFA> NFA_Pars_Ast(Node *current, int * maxstate);
};
NFA::NFA() : start(0), last(0) {}
NFA::NFA(int sstate): start(sstate){}//
NFA::NFA(int s, std::string &pname) : start(s), last(s), name(pname) {} // для групп захвата
NFA::NFA(Ast &myast) {
    int zero = -1;
    std::shared_ptr<NFA> myNFA = NFA_Pars_Ast(myast.root, &zero);
    this->start = myNFA->start;
    this->last = myNFA->last;
    this->states= myNFA->states;
    this->capture_groups.swap(myNFA->capture_groups);
}
void NFA::Myprint() {
    if(name.empty()){
        std::cout << "NFA AUTOMATE: " << std::endl;
    }
    else{
        std::cout << "name of the capture group: " << name <<  std::endl;
    }
    std::cout << "Start state: " << start << std::endl;
    std::cout << "Last state: " << last << std::endl;
    std::cout << "All the states:" << std::endl;
    for (auto it = states.begin(); it != states.end(); ++it) {
        auto cur = it->second;
        std::cout << "State number: " << cur->index << std::endl;
        std::cout << "Transitions: "<< std::endl;
        for (auto tr_it = cur->transitions.begin(); tr_it != cur->transitions.end(); ++tr_it) {
            if(tr_it->second->type == 'e'){
                std::cout << " epsilon to " << tr_it->second->to << std::endl;
            }
            else if(tr_it->second->type == 's'){
                std::cout <<"\"" << tr_it->second->symbol <<"\"" <<" to " << tr_it->second->to << std::endl;
            }
            else if(tr_it->second->type == 'c'){
                std::cout << "capture transition " << " to " << tr_it->second->to << std::endl;
                std::shared_ptr<NFA> cpt_auto = this->capture_groups.find(tr_it->second)->second;
                cpt_auto->Myprint();
            }
            else{
                throw std::logic_error("A wrong transition");
            }
        }
    }
    if(!name.empty()){
        std::cout << "end of capture automate with name " << name << std::endl;
    }
}
// Метод Макнота-Ямада-Томпсон
std::shared_ptr<NFA> NFA::NFA_Pars_Ast(Node *current, int * maxstate){// сквозная нумерация int
    std::string operations = "*?&|<{";
    if(current == nullptr || operations.find(current->symbol) == -1 || current->true_symbol){ // e-leaf or a-leaf
        char fch;
        char sch;
        if(current == nullptr){
            fch = 'e';
            sch = 'e';
        }
        else{
            fch = 's';
            sch = current->symbol;
        }
        (*maxstate)++;
        std::shared_ptr<NFA> leaf = std::make_shared<NFA>(*maxstate); // автомат для листа
        auto ptr1 = std::make_shared<State>(*maxstate);
        (*maxstate)++;
        leaf->last = *maxstate;
        auto ptr2 = std::make_shared<State>(*maxstate);
        ptr1->transitions.insert(std::make_pair(std::make_pair(fch,sch), std::make_shared<Transition>(fch,sch,*maxstate))); // transition
        leaf->states.insert(std::make_pair(ptr1->index, ptr1)); // стартовое состояние
        leaf->states.insert(std::make_pair(ptr2->index, ptr2)); // конечное состояние
        return leaf;
    }
    else if(current->symbol == '&'){ // экранированные обработались на прошлой итерации
        std::shared_ptr<NFA> left_tree_auto = NFA_Pars_Ast(current->left,maxstate);
        std::shared_ptr<NFA> right_tree_auto = NFA_Pars_Ast(current->right,maxstate);
        // переходы из start второго передаем концу первого. Сливаем 2 состояния
        (left_tree_auto->states.find(left_tree_auto->last))->second->transitions.swap((right_tree_auto->states.find(right_tree_auto->start))->second->transitions);
        right_tree_auto->states.erase(right_tree_auto->start); // удаляем начальное состояние второго автомата
        left_tree_auto->last = right_tree_auto->last;
        //std::cout << "check";
        left_tree_auto->states.merge(right_tree_auto->states); // объединяем состояния
        left_tree_auto->capture_groups.merge(right_tree_auto->capture_groups);
        return left_tree_auto;
    }
    else if(current->symbol == '|' || current->symbol == '?'){
        std::shared_ptr<NFA> left_tree_auto = NFA_Pars_Ast(current->left,maxstate);
        std::shared_ptr<NFA> right_tree_auto = NFA_Pars_Ast(current->right,maxstate);
        (*maxstate)++;
        auto ptr1 = std::make_shared<State>(*maxstate); // E-state нужно будет вставить в автомат
        ptr1->transitions.insert(std::make_pair(std::make_pair('e', 'e'), std::make_shared<Transition>('e','e',left_tree_auto->start)));
        ptr1->transitions.insert(std::make_pair(std::make_pair('e', 'e'), std::make_shared<Transition>('e','e',right_tree_auto->start)));
        left_tree_auto->start = *maxstate; // E - Стартовое состояние. Merge позже.
        left_tree_auto->states.insert(std::make_pair(ptr1->index, ptr1)); // вставляем E в список состояний
        (*maxstate)++;
        auto ptr2 = std::make_shared<State>(*maxstate); // F-state
        (left_tree_auto->states.find(left_tree_auto->last))->second->transitions.insert(std::make_pair(std::make_pair('e', 'e')
        ,std::make_shared<Transition>('e','e',*maxstate))); // связь между B and F
        (right_tree_auto->states.find(right_tree_auto->last))->second->transitions.insert(std::make_pair(std::make_pair('e', 'e')
                ,std::make_shared<Transition>('e','e',*maxstate))); // связь между D and F
        left_tree_auto->last = *maxstate;
        left_tree_auto->states.insert(std::make_pair(ptr2->index, ptr2)); // вставляем E в список состояний
        left_tree_auto->states.merge(right_tree_auto->states); // объединяем состояния
        left_tree_auto->capture_groups.merge(right_tree_auto->capture_groups);
        return left_tree_auto;
    }
    else if(current->symbol == '*') { // Может быть eps в левом поддереве
        std::shared_ptr<NFA> left_tree_auto = NFA_Pars_Ast(current->left, maxstate);
        (*maxstate)++;
        auto ptr1 = std::make_shared<State>(*maxstate); // C-state нужно будет вставить в автомат
        ptr1->transitions.insert(std::make_pair(std::make_pair('e', 'e'),
                                                std::make_shared<Transition>('e', 'e', left_tree_auto->start))); // ребро между C and A
        // сделаем переход из B в A
        (left_tree_auto->states.find(left_tree_auto->last))->second->transitions.insert(std::make_pair(std::make_pair('e', 'e')
                ,std::make_shared<Transition>('e','e',left_tree_auto->start)));
        left_tree_auto->start = ptr1->index; // состояние A уже не нужно. Изменим начальное состояние.
        left_tree_auto->states.insert(std::make_pair(ptr1->index, ptr1)); // вставляем C в список состояний
        (*maxstate)++;
        auto ptr2 = std::make_shared<State>(*maxstate); // D-state
        // Из B в D
        (left_tree_auto->states.find(left_tree_auto->last))->second->transitions.insert(std::make_pair(std::make_pair('e', 'e')
                ,std::make_shared<Transition>('e','e',ptr2->index)));
        left_tree_auto->last = ptr2->index;
        // сделаем переход из C в D
        (left_tree_auto->states.find(left_tree_auto->start))->second->transitions.insert(std::make_pair(std::make_pair('e', 'e')
                ,std::make_shared<Transition>('e','e',left_tree_auto->last)));
        left_tree_auto->states.insert(std::make_pair(ptr2->index, ptr2)); // вставляем D в список состояний
        return left_tree_auto;
    }
    else if(current->symbol == '{') { // Может быть eps в левом поддереве
        int k = std::stoi(current->capture_group_cbracketsnum); // std::string в int
        if (k == 0) {
            return NFA_Pars_Ast(nullptr, maxstate);
        } else if (k == 1) {
            return NFA_Pars_Ast(current->left, maxstate);
        } else {
            std::shared_ptr<NFA> left_tree_auto = NFA_Pars_Ast(current->left, maxstate); // первое регулярное выражение
            for (int i = 1; i < k; i++) { // k -1  конкатенация.
                //std::cout << "check";
                std::shared_ptr<NFA> temp = NFA_Pars_Ast(current->left, maxstate);
                // переходы из start второго передаем концу первого. Сливаем 2 состояния
                (left_tree_auto->states.find(left_tree_auto->last))->second->transitions = (temp->states.find(
                        temp->start))->second->transitions;
                temp->states.erase(temp->start); // удаляем начальное состояние второго автомата
                left_tree_auto->last = temp->last;
                left_tree_auto->states.merge(temp->states); // объединяем состояния
            }
            // пока что без capture group
            return left_tree_auto;
        }
    }
    else if(current->symbol == '<'){
        int nzero = -1; // 2 состояния и одно capture rebro между ними далее отладка
        std::shared_ptr<NFA> myNFA = NFA_Pars_Ast(current->left, &nzero);
        myNFA->name = current->capture_group_cbracketsnum;
        (*maxstate)++;
        std::shared_ptr<NFA> op_auto = std::make_shared<NFA>(*maxstate); // автомат для оригинального автомата
        auto ptr1 = std::make_shared<State>(*maxstate);
        (*maxstate)++;
        op_auto->last = *maxstate;
        auto ptr2 = std::make_shared<State>(*maxstate);
        ptr1->transitions.insert(std::make_pair(std::make_pair('c','c'), std::make_shared<Transition>('c','c',*maxstate))); // transition
        op_auto->states.insert(std::make_pair(ptr1->index, ptr1)); // стартовое состояние
        op_auto->states.insert(std::make_pair(ptr2->index, ptr2)); // конечное состояние
        op_auto->capture_groups.insert(std::make_pair(ptr1->transitions.find(std::make_pair('c','c'))->second, myNFA));
        return op_auto;
    }
    throw std::logic_error("error");
}
#endif //LAB2TA_MYNFA_H
