//
// Created by Марат on 06.08.2024.
//

#ifndef LAB2TA_MYREGEX_H
#define LAB2TA_MYREGEX_H
#include <string>
#include <map>
#include <memory>
#include <forward_list>
#include "myDFA.h"
class Regex;
class Captures;
class Captures{
public:
    friend Regex;
    std::map<std::string, std::string>::iterator begin();
    std::map<std::string, std::string>::iterator end();
    std::string  operator [] (const std::string name);
    Captures() = default;
    explicit Captures(std::map<std::string, std::string> pairs) : groups{std::move(pairs)}{}
private: std::map<std::string, std::string> groups; // первое имя, а затем содержимое
};

std::map<std::string, std::string>::iterator Captures::begin(){
    return groups.begin();
}
std::map<std::string, std::string>::iterator Captures::end(){
    return groups.end();
}
std::string Captures::operator[](const std::string name) {
    auto it = groups.find(name);
    if(it != groups.end()){
        return it->second;
    }
    else{
        //std::cout << "This group was not captured in the process" << std::endl;
        return "";
    }
}
    class Regex{
public:
    //friend Regex;
    Regex difference(Regex & secondR);
    void PrintCompiled();
    Regex() = default;
    std::string create_regular_expression();
    void inversion(); // для скомпилированного автомата
    void inversion(const std::string& pattern);
    void compile(const std::string& regular_expression);
    bool search(const std::string& mytext, std::string &match, Captures & capts);
    bool search(const std::string& mytext, const std::string& pattern, std::string &match, Captures & capts);
    bool search(const std::string& mytext, std::string &match);
    bool search(const std::string& mytext, const std::string& pattern, std::string &match);
    //bool search(const std::string& mytext, std::string &match,);
    //bool search(const std::string& mytext, const std::string& pattern, std::string &match);
private:
    void difference_add_trans_nka(std::map<int, std::shared_ptr<State>> &states3, std::shared_ptr<NFA> nka);
    void difference_renumber(std::shared_ptr<NFA> mynfa, int * max_ind);
    void difference_build_transitions(std::shared_ptr<DFA> dfa, std::shared_ptr<StateWMF> c_state, std::shared_ptr<NFA> mynfa);
    std::shared_ptr<NFA> difference_create_nka_from_dka(std::shared_ptr<DFA> mydfa);
    bool search(const std::string& mytext, std::string &match, std::map<std::string, std::string> &groups);
    std::set<std::string> unite_finish_s(std::shared_ptr<DFA> dfa, int ind, std::map<std::shared_ptr<Transition>, std::string> true_trans);
    std::string create_regular_expression_using_auto(std::shared_ptr<DFA> dfa);
    std::shared_ptr<NFA> inversion_create_nka_from_dka(std::shared_ptr<DFA> mydfa);
    bool is_compiled = false;
    std::shared_ptr<DFA> automate;
    void inversion_build_transitions(std::shared_ptr<DFA> dfa, std::shared_ptr<StateWMF> c_state, std::shared_ptr<NFA> mynfa);
    std::forward_list<std::tuple<std::string::iterator,std::map<std::string, std::string>, int>> run_through_group(std::string::iterator first,
                                                       std::string::iterator second, std::shared_ptr<DFA> group, int next_state); // в next_state переходим в исходном автомате
};
std::shared_ptr<NFA> Regex::difference_create_nka_from_dka(std::shared_ptr<DFA> mydfa){
    std::shared_ptr<NFA> myNFA = std::make_shared<NFA>();// функция для преобразования в НКА
    std::set<int> f_states;
    for(auto it = mydfa->states.begin(); it != mydfa->states.end(); ++it){
        if(it->second->finish){
            f_states.insert(it->second->index);
        }
        auto ptr1 = std::make_shared<State>(it->second->index);
        myNFA->states.insert(std::make_pair(ptr1->index, ptr1)); // каждому номеру состояния в ДКА соответсвует номер состояния в НКА
    }
    difference_build_transitions(mydfa, mydfa->states.find(mydfa->start)->second, myNFA); // все ребра отсстроены
    auto ptr1 = std::make_shared<State>(myNFA->states.size()); //индекс нового состояния
    myNFA->states.insert(std::make_pair(ptr1->index, ptr1));
    myNFA->last = ptr1->index;
    myNFA->start = mydfa->start;
    for(auto it = f_states.begin(); it != f_states.end(); ++it){
        // eps переходы
        auto ptr2 = std::make_shared<Transition>('e', 'e', myNFA->last);
        myNFA->states.find(*it)->second->transitions.insert(std::make_pair(std::make_pair('e', 'e'), ptr2));
    }  // nka is ready to be dka
    return myNFA;
}

void Regex::difference_build_transitions(std::shared_ptr<DFA> dfa, std::shared_ptr<StateWMF> c_state, std::shared_ptr<NFA> mynfa){
    for(auto it = c_state->transitions.begin(); it != c_state->transitions.end(); ++it){
        auto checker = mynfa->states.find(c_state->index)->second->transitions.find(
                std::make_pair(it->second->type, it->second->symbol));
        if (checker != mynfa->states.find(c_state->index)->second->transitions.end()) {
            if (checker->second->type == 's' && checker->second->to == it->second->to) {
                continue;
            }
            if(checker->first == std::make_pair('c', 'c')){
                auto nsub_a = dfa->capture_groups.find(it->second)->second->name;
                for(auto fname = mynfa->capture_groups.begin(); fname != mynfa->capture_groups.end(); ++fname){
                    if(fname->second->name == nsub_a){
                        continue;
                    }
                }
            }
        }
        if(it->second->type == 's'){
            // c_state-> index on it->second->to
            auto ptr1 = std::make_shared<Transition>(it->second->type, it->second->symbol, it->second->to);
            mynfa->states.find(c_state->index)->second->transitions.insert(std::make_pair(std::make_pair('s', it->second->symbol), ptr1));
        }
        else{ // capture transition
            auto ptr1 = std::make_shared<Transition>(it->second->type, it->second->symbol, it->second->to);
            mynfa->states.find(c_state->index)->second->transitions.insert(std::make_pair(std::make_pair(it->second->type, it->second->symbol), ptr1));
            auto n_nka = difference_create_nka_from_dka(dfa->capture_groups.find(it->second)->second);
            n_nka->name = dfa->capture_groups.find(it->second)->second->name;
            mynfa->capture_groups.insert(std::make_pair(ptr1, n_nka));
        }
        difference_build_transitions(dfa, dfa->states.find(it->second->to)->second, mynfa);
    }
}
void Regex::difference_renumber(std::shared_ptr<NFA> mynfa, int * max_ind){
    std::map<int, std::shared_ptr<State>> states2;
    int start;
    int last;
    for(auto it = mynfa->states.begin(); it != mynfa->states.end(); ++it ){
        (*max_ind)++;
        if(mynfa->start == it->second->index){
            start = *max_ind;
        }
        if(mynfa->last == it->second->index){
            last = *max_ind;
        }
        // прохожусь по всем ребрам
        for(auto it_s = mynfa->states.begin(); it_s != mynfa->states.end(); ++it_s ){
            for(auto it_t = it_s->second->transitions.begin();  it_t != it_s->second->transitions.end(); ++it_t ){
                if(it_t->second->to == it->second->index){
                    it_t->second->to = *max_ind;
                }
            }
        }
        auto ptr1 = it->second;
        ptr1->index = *max_ind;
        states2.insert(std::make_pair(*max_ind, ptr1));
    }
    mynfa->start = start;
    mynfa->last = last;
    mynfa->states = states2; // необходимо поменять список состояний
    for(auto it = mynfa->capture_groups.begin(); it != mynfa->capture_groups.end(); ++it ){
        difference_renumber(it->second, max_ind);
    }
}
void Regex::difference_add_trans_nka(std::map<int, std::shared_ptr<State>> &states3, std::shared_ptr<NFA> nka) {// рекурсивная функция
    std::multimap<int,  std::multimap<std::pair<char, char>,std::shared_ptr<Transition>>::iterator> del;
    for(auto it_s = nka->states.begin(); it_s != nka->states.end(); ++it_s ){
        std::set<std::shared_ptr<Transition>> temp;
        for(auto it_t = it_s->second->transitions.begin();  it_t != it_s->second->transitions.end(); ++it_t ){
            if(nka->capture_groups.find(it_t->second) != nka->capture_groups.end()){
                //int last_sub =
                difference_add_trans_nka(states3, nka->capture_groups.find(it_t->second)->second);// рекурсивная функция
                // 2 ребра добавить, 1 удалить и удалить автомат
                auto ptr1 = std::make_shared<Transition>('e', 'e', nka->capture_groups.find(it_t->second)->second->start); // в start
                temp.insert(ptr1);
                auto ptr2 = std::make_shared<Transition>('e', 'e', it_t->second->to); // в start
                auto sub_auto = nka->capture_groups.find(it_t->second)->second;
                states3.find(sub_auto->last)->second->transitions.insert(std::make_pair(std::make_pair('e','e'), ptr2));
                del.insert(std::make_pair(it_s->second->index, it_t));
            }
        }
        for(auto cit = temp.begin(); cit != temp.end(); cit++){// в start
            it_s->second->transitions.insert(std::make_pair(std::make_pair('e','e'), *cit));
        }
    }
    for(auto it = del.begin(); it != del.end(); ++it ) {
        nka->capture_groups.erase(nka->capture_groups.find(it->second->second));
        nka->states.find(it->first)->second->transitions.erase(it->second); // удаляем capture ребро
    }
    states3.merge(nka->states);
}
Regex Regex::difference(Regex & secondR){
    // сделаем слияние автоматов и посмотрим есть ли одинаковые ребра - переходы.
    // аходим максимальный индекс
    if (!is_compiled) { // не был скомпилирован
        throw std::logic_error("Compile first!");
    }
    if(!secondR.is_compiled){
        throw std::logic_error("Compile first!");
    }
    auto nka = difference_create_nka_from_dka(automate);
    // теперь необходимо перенумеровать состояния
    int max_ind = nka->last; // исходя из того как организована предыдущая функция
    for(auto it = nka->capture_groups.begin(); it != nka->capture_groups.end(); ++it ){// во всех автоматах меняю индекс и to в ребрах
        difference_renumber(it->second, &max_ind);
    }
    //nka->Myprint();
    // необходимо слить автоматы.
    std::map<int, std::shared_ptr<State>> states3;
    difference_add_trans_nka(states3, nka);// рекурсивная функция
    nka->states = states3; // содержит абсолютно все состояния
    //automate = std::make_shared<DFA>(*nka);
    auto automate1 = std::make_shared<DFA>(*nka);
    //second


    auto nka1 = difference_create_nka_from_dka(secondR.automate);
    // теперь необходимо перенумеровать состояния
    int max_ind1 = nka1->last; // исходя из того как организована предыдущая функция
    for(auto it = nka1->capture_groups.begin(); it != nka1->capture_groups.end(); ++it ){// во всех автоматах меняю индекс и to в ребрах
        difference_renumber(it->second, &max_ind1);
    }
    std::map<int, std::shared_ptr<State>> states4;
    difference_add_trans_nka(states4, nka1);// рекурсивная функция
    nka1->states = states4; // содержит абсолютно все состояния
    auto automate2 = std::make_shared<DFA>(*nka1);
    //automate2->Myprint();
    //std::cout << "Check" << std::endl;
    // последняя часть - произведение
    auto res_auto = std::make_shared<DFA>();
    // Можно создать все состояния. В конце почистить безреберные.
    std::map<std::pair<int,int>, int> res_states;
    int max_num = -1;
    for(auto it_s_1 = automate1->states.begin(); it_s_1 != automate1->states.end(); ++it_s_1){ // создание состояний и пометка - старт или финиш
        for(auto it_s_2 = automate2->states.begin(); it_s_2 != automate2->states.end(); ++it_s_2){
            max_num++;
            auto ptr1 = std::make_shared<StateWMF>(max_num);
            if(it_s_1->first == automate1->start && it_s_2->first == automate2->start){
                res_auto->start = max_num;
            }
            if(it_s_1->second->finish && !it_s_2->second->finish){
                ptr1->finish = true;
            }
            res_auto->states.insert(std::make_pair(max_num,ptr1));
            res_states.insert(std::make_pair(std::make_pair(it_s_1->first, it_s_2->first), max_num));
        }
    }
    for(auto it_s_1 = automate1->states.begin(); it_s_1 != automate1->states.end(); ++it_s_1){
        for(auto it_t_1 = it_s_1->second->transitions.begin(); it_t_1 != it_s_1->second->transitions.end(); ++it_t_1){
            // если для каких-то состояний есть ребро по этому символу, мы идем
            std::map<int,std::shared_ptr<Transition>> trans_res;
            for(auto it_s_2 = automate2->states.begin(); it_s_2 != automate2->states.end(); ++it_s_2){
                for(auto it_t_2 = it_s_2->second->transitions.begin(); it_t_2 != it_s_2->second->transitions.end(); ++it_t_2){
                    if(it_t_2->second->symbol == it_t_1->second->symbol){
                        trans_res.insert(std::make_pair(it_s_2->first, it_t_2->second)); // по какому символу и куда
                    }
                }
            }
            for(auto it_add = trans_res.begin(); it_add != trans_res.end(); ++it_add){
                int from = res_states.find(std::make_pair(it_s_1->first, it_add->first))->second;
                int to = res_states.find(std::make_pair(it_t_1->second->to, it_add->second->to))->second;
                auto ptr1 = std::make_shared<Transition>('s', it_t_1->second->symbol, to);
                res_auto->states.find(from)->second->transitions.insert(std::make_pair(std::make_pair('s', it_t_1->second->symbol), ptr1));
            }
        }
    }
    Regex res{};
    res.automate = res_auto;
    res.is_compiled = true;
    return res;
}
void Regex::PrintCompiled() {
    if(is_compiled){
        automate->Myprint();
    }
    else{
        std::cout << "Is not compiled" << std::endl;
    }
}
std::set<std::string> Regex::unite_finish_s(std::shared_ptr<DFA> dfa,int ind, std::map<std::shared_ptr<Transition>, std::string> true_trans){
    //std::s
    // добавляется это выражение или оно + доп часть.
    std::set<std::string> res;
    res.insert("");
    for(auto it = dfa->states.find(ind)->second->transitions.begin(); it != dfa->states.find(ind)->second->transitions.end(); ++it){
        if(it->second->to != dfa->start && it->second->to != ind && dfa->states.find(it->second->to)->second->finish == true){
            //auto sub_str = unite_finish_s(dfa, )
            auto sub_str = true_trans.find(it->second)->second;
            res.insert(sub_str);
        }
    }
    return  res;
}
std::string Regex::create_regular_expression_using_auto(std::shared_ptr<DFA> dfa){
    std::map<std::shared_ptr<Transition>, std::string> true_trans; // в ребрах написано куда ведет оно.
    // с группами захвата решить вопрос
    std::string operations = "*?|<>{}()";
    for(auto it = dfa->states.begin(); it != dfa->states.end(); ++it){ // по переходу я могу знать какую подстроку несет этот переход
        for(auto it1 = it->second->transitions.begin(); it1 != it->second->transitions.end(); ++it1){
            std::string sub_str = "";
            if(it1->second->type == 's'){
                if (operations.find(it1->second->type) == -1){ // операция find возвращает -1, если символ не найден
                    sub_str += it1->second->symbol;
                }
                else{
                    sub_str += '%';
                    sub_str += it1->second->symbol;
                    sub_str += '%';
                }
            }
            else{// capture
                sub_str = "(<";
                sub_str += dfa->capture_groups.find(it1->second)->second->name;
                sub_str += '>';
                sub_str += create_regular_expression_using_auto(dfa->capture_groups.find(it1->second)->second);// строка не доработана (<name>...)
                sub_str += ')';
            }
            true_trans.insert(std::make_pair(it1->second, sub_str));
        }
    } // выделить состояния, которые буду удалять
    std::set<int> d_states;
    for(auto it = dfa->states.begin(); it != dfa->states.end(); ++it){
        if(!it->second->finish){
            d_states.insert(it->second->index);
        }
    }
    if(d_states.find(dfa->start) != d_states.end()){ // если верно, то надо удалить от сюда стартовое
        d_states.erase(d_states.find(dfa->start));
    }
    // начинаю удалять состояния
    // если удаляемое состояние будет вести в себя, появится клини, если размер регулярки перехода больше 1 еще и скобки добавятся
    for(auto it_d = d_states.begin(); it_d != d_states.end(); ++it_d){
        // находим состояния, ведущие в выбранное.
        // мне только нужны ребра
        std::map<std::shared_ptr<Transition>, int> from;
        for(auto it = dfa->states.begin(); it != dfa->states.end(); ++it) { // в каждом состояния
            for (auto it1 = it->second->transitions.begin(); it1 != it->second->transitions.end(); ++it1) { // все ребра
                if(it1->second->to == *it_d){ // переход в удаляемое состояние есть.
                    from.insert(std::make_pair(it1->second,it->second->index));
                }
            }
        }
        std::set<std::shared_ptr<Transition>> to; // переходы, идущие из удаляемого состояния
        std::string clini = "";
        for (auto it1 = dfa->states.find(*it_d)->second->transitions.begin(); it1 != dfa->states.find(*it_d)->second->transitions.end(); ++it1) { // все ребра
            if(it1->second->to == *it_d){ // клини
                if(true_trans.find(it1->second)->second.size() > 1) {
                    clini += '(';
                    clini += true_trans.find(it1->second)->second;
                    clini += ")...";
                }
                else{
                    clini += true_trans.find(it1->second)->second;
                    clini += "...";
                }
                dfa->states.find(*it_d)->second->transitions.erase(it1);// удаляем лишнее ребро
            }
            else {
                to.insert(it1->second);
            }
        }
        // мне нужен индекс элемента из которого исходит ребро
        // связывание
        for(auto it = from.begin(); it != from.end(); ++it){
            auto it_to =  to.begin(); // хоть 1 ребро то есть. Иначе финиш стэйт
            std::string prev = true_trans.find(it->first)->second;
            true_trans.find(it->first)->second += clini;
            true_trans.find(it->first)->second += true_trans.find(*it_to)->second;
            //std::cout << " " << true_trans.find(it->first)->second << " " << std::endl;
            it->first->to = (*it_to)->to;
            //true_trans.erase(*it_to);// удаляем ребро из map
            it_to++;
            for(; it_to != to.end(); ++it_to){ // надо создать столько связок, каков размер
                auto n_trans = std::make_shared<Transition>('s','s', (*it_to)->to);
                dfa->states.find(it->second)->second->transitions.insert(std::make_pair(std::make_pair('s', 's'),n_trans));
                true_trans.insert(std::make_pair(n_trans, prev));
                true_trans.find(n_trans)->second += clini;
                true_trans.find(n_trans)->second += true_trans.find(*it_to)->second;
                //std::cout << " " <<true_trans.find(n_trans)->second << " " << std::endl;
                //true_trans.erase(*it_to);// удаляем ребро из map
            }
            //dfa->states.find(it->second)->second->transitions.erase(it->first);
            //true_trans.erase(it->first); // заменили одно ребро целой кучей
        }
        dfa->states.erase(dfa->states.find(*it_d)); // чтобы быстрее работали алгоритмы
    }
    std::string result = "";
    std::string start_to_start = "";
    std::string finish_to_start;
    std::string finish_to_finish;
    // до сюда в целом работает
    // v| part
    for(auto it = dfa->states.find(dfa->start)->second->transitions.begin(); it != dfa->states.find(dfa->start)->second->transitions.end(); ++it){
        if(it->second->to == dfa->start){
            start_to_start += true_trans.find(it->second)->second;// необходимо удалить ребро из стартового состояния в себя
            dfa->states.find(dfa->start)->second->transitions.erase(it); // удаляем по итератору на пару
        }
    }
    //std::cout << dfa->states.size();
    if(dfa->states.find(dfa->start)->second->finish){ // стартовое - конечное
        //std::cout << "true";
        if(start_to_start.size() > 1){
            result += '(';
            result += start_to_start;
            result += ')';
        }
        else{
            result += start_to_start;
        }
        if(!start_to_start.empty()) {
            result += "..."; // клини это же 3 точки
        }
        result += '|';
    }
    // надо еще пары финишных объединить предварительно. Они станут или. Все таки из одного финишного я могу приходить в другое пример - строка a
    for(auto it = dfa->states.find(dfa->start)->second->transitions.begin(); it != dfa->states.find(dfa->start)->second->transitions.end(); ++it){
        std::string one_pair = "";
        finish_to_finish = "";
        finish_to_start = "";
        // finish to finish?
        for(auto it1 = dfa->states.find(it->second->to)->second->transitions.begin(); it1 != dfa->states.find(it->second->to)->second->transitions.end(); ++it1){
            if(it1->second->to == it->second->to){ // finish to finish
                finish_to_finish += true_trans.find(it1->second)->second;
                // клини сразу надро добавить
                if(finish_to_finish.size() > 1){
                    finish_to_finish.insert(finish_to_finish.cbegin(), '(');
                    finish_to_finish += ')';
                }
                if(!finish_to_finish.empty()) {
                    finish_to_finish += "..."; // клини это же 3 точки
                }
            }
            if(it1->second->to == dfa->start){// finifhs to start
                finish_to_start += true_trans.find(it1->second)->second;
                // а не надо ли тут ребро удалить?
            }
        }
        if(!start_to_start.empty() || !finish_to_finish.empty()) {
            //one_pair = '(';
            if (!start_to_start.empty()) {
                one_pair += start_to_start;
                if (!finish_to_finish.empty()) {
                    one_pair += '|';
                    one_pair += true_trans.find(it->second)->second; // s
                    one_pair += finish_to_finish;
                    one_pair += finish_to_start;
                }
            }
            else{ // без старта
                one_pair += true_trans.find(it->second)->second; // s
                one_pair += finish_to_finish;
                one_pair += finish_to_start;
            }
        }
        if(one_pair.size() > 1){
            one_pair.insert(one_pair.cbegin(), '(');
            one_pair += ')';
        }
        if(one_pair.size() >= 1) { // был цикл
            one_pair += "...";
        }
        one_pair += true_trans.find(it->second)->second; // s
        one_pair += finish_to_finish;// вот тут вызываю эту функцию
        auto res = unite_finish_s(dfa, it->second->to, true_trans);
        for (auto myit = res.begin(); myit != res.end() ; ++myit) {
            std::string substr = one_pair;
            substr += *myit;
            result += substr;
            result += '|';
        }
        //std::cout << one_pair;
        //result += one_pair;
        //result += '|';
    }
    result.pop_back(); // если из какого-то финишного могу попасть теперь в финишное, добавляю. Без этого очень плохо работает. Рекурсивно вызываю эту функцию Она возвращает
    // строку.
    return result;
    // в конце надо лишнее или удалить.
    // остались только конечные состояния и стартовое
}
std::string Regex::create_regular_expression(){
    auto res = create_regular_expression_using_auto(automate);
    is_compiled = false;
    return res;
}
std::shared_ptr<NFA> Regex::inversion_create_nka_from_dka(std::shared_ptr<DFA> mydfa){
    std::shared_ptr<NFA> myNFA = std::make_shared<NFA>();// функция для преобразования в НКА
    std::set<int> f_states;
    for(auto it = mydfa->states.begin(); it != mydfa->states.end(); ++it){
        if(it->second->finish){
            f_states.insert(it->second->index);
        }
        auto ptr1 = std::make_shared<State>(it->second->index);
        myNFA->states.insert(std::make_pair(ptr1->index, ptr1)); // каждому номеру состояния в ДКА соответсвует номер состояния в НКА
    }
    inversion_build_transitions(mydfa, mydfa->states.find(mydfa->start)->second, myNFA); // все ребра отсстроены
    auto ptr1 = std::make_shared<State>(myNFA->states.size()); //индекс нового состояния
    myNFA->states.insert(std::make_pair(ptr1->index, ptr1));
    myNFA->last = mydfa->start;
    myNFA->start = ptr1->index;
    for(auto it = f_states.begin(); it != f_states.end(); ++it){
        // eps переходы
        auto ptr2 = std::make_shared<Transition>('e', 'e', *it);
        myNFA->states.find(myNFA->start)->second->transitions.insert(std::make_pair(std::make_pair('e', 'e'), ptr2));
    }  // nka is ready to be dka
    return myNFA;
}

void Regex::inversion_build_transitions(std::shared_ptr<DFA> dfa, std::shared_ptr<StateWMF> c_state, std::shared_ptr<NFA> mynfa){
        for (auto it = c_state->transitions.begin(); it != c_state->transitions.end(); ++it) {
            auto checker = mynfa->states.find(it->second->to)->second->transitions.find(
                    std::make_pair(it->second->type, it->second->symbol));
            if (checker != mynfa->states.find(it->second->to)->second->transitions.end()) {
                if (checker->second->type == 's' && checker->second->to == c_state->index) {
                    continue;
                }
                if(checker->first == std::make_pair('c', 'c')){
                    auto nsub_a = dfa->capture_groups.find(it->second)->second->name;
                    for(auto fname = mynfa->capture_groups.begin(); fname != mynfa->capture_groups.end(); ++fname){
                        if(fname->second->name == nsub_a){
                            continue;
                        }
                    }
                }
            }
            if (it->second->type == 's') {
                auto ptr1 = std::make_shared<Transition>(it->second->type, it->second->symbol, c_state->index);
                mynfa->states.find(it->second->to)->second->transitions.insert(
                        std::make_pair(std::make_pair('s', it->second->symbol), ptr1));
            } else { // capture transition
                auto ptr1 = std::make_shared<Transition>(it->second->type, it->second->symbol, c_state->index);
                mynfa->states.find(it->second->to)->second->transitions.insert(
                        std::make_pair(std::make_pair(it->second->type, it->second->symbol), ptr1));
                auto n_nka = inversion_create_nka_from_dka(dfa->capture_groups.find(it->second)->second);
                n_nka->name = dfa->capture_groups.find(it->second)->second->name;
                mynfa->capture_groups.insert(std::make_pair(ptr1, n_nka));
            }
            inversion_build_transitions(dfa, dfa->states.find(it->second->to)->second, mynfa);
            //if(it->second->to != c_state->index){
            // если ребро уже было добавлено, мы тут не проходим
            //if(mynfa->states.find(c_state->index)->second->transitions.find(std::make_pair()->second->to) == mynfa->states.find(c_state->index)->second->transitions.end())
            //    inversion_build_transitions(dfa, dfa->states.find(it->second->to)->second, mynfa);
            //}

            //inversion_build_transitions(dfa, dfa->states.find(it->second->to)->second, mynfa);
        }
}
void Regex::inversion() { // когда нахожу capture ребро, тогда перехожу к параллельному автомату. Рекурсивная функция по преобразованию ребра
    if (!is_compiled) { // не был скомпилирован
        throw std::logic_error("Compile first!");
    }
    auto nka = inversion_create_nka_from_dka(automate); // она еще и объединит finish states в одно старт
    automate = std::make_shared<DFA>(*nka);
    //automate->Myprint();
    // функция create shared<nka> from dka. Она вставит
    // Предлагается пройтись рекурсивно по всем ребрам ДКА добавляя инверсные в НКА. В конце работы функции
    // вызовется эта функция рекурсивна для всех подавтоматов
    // сначала надо сделать NFA
    // поиск финишных состояний он вернет список.

}
void Regex::inversion(const std::string& pattern) {
    compile(pattern);
    inversion();
}
// общий случай.
std::forward_list<std::tuple<std::string::iterator,std::map<std::string, std::string>, int>> Regex::run_through_group(std::string::iterator first,
                                                           std::string::iterator second, std::shared_ptr<DFA> group, int next_state){
    // second для всех один
    // есть first итератор, текущий на финишное состояние. Из них я выделю подстроку и запишу к группам захвата.
    std::forward_list<std::tuple<std::string::iterator,std::map<std::string, std::string>, int>> list_exit; // если list пуст, по выходу из функции, то не было подходящих вариантов тут.
    std::forward_list<std::tuple<std::string::iterator,std::map<std::string, std::string>, int>> list_here;
    list_here.emplace_front(first, std::map<std::string, std::string>{}, group->start); // изначально нет групп захвата. На выходе сформирую текущую
    while(!list_here.empty()) {
        auto cur_tuple = list_here.front(); // доступ к первому элементу forward_list
        list_here.pop_front(); // удаление элемента из версий, ожидающих обработки
        auto c_state = group->states.find(std::get<2>(cur_tuple))->second; // начинаем с этого состояния. По выходу из группы надо iterator перевести на 1
        if(c_state->finish){ // был автомат или эпсилон
            std::get<1>(cur_tuple).insert(std::make_pair(group->name, std::string{first,  std::get<0>(cur_tuple)})); // добавили текущую группу захвата
           list_exit.emplace_front( std::get<0>(cur_tuple),std::get<1>(cur_tuple), next_state);
            // здесь name надо вытащить из контейнера. Чтобы в продолжении можно было использовать
            std::get<1>(cur_tuple).erase(std::get<1>(cur_tuple).find(group->name));
        }
        for (auto it = std::get<0>(cur_tuple); it != second; ++it) { // остановились на этой позиции строки.
            //std::cout << *it;
            bool is_cont = false;
            if (c_state->transitions.find(std::make_pair('c', 'c')) !=
                c_state->transitions.end()) { // тогда ребро - группа захвата
                auto range = c_state->transitions.equal_range(std::make_pair('c', 'c')); // находит все элементы с этими ключами
                auto iter = range.first; // Первый элемент с этим ключом.
                do {
                    //std::cout << "check";
                    auto nproc = run_through_group(it, second,group->capture_groups.find(iter->second)->second, iter->second->to );
                    list_here.merge(nproc); // пустой вроде тоже можно
                    ++iter;
                } while (iter != range.second); // range.second - ключ, больший чем данный.( или end())
            }
            if (c_state->transitions.find(std::make_pair('s', *it)) !=
                c_state->transitions.end()) { // есть такой переход
                //std::cout << " sign";
                int ind = c_state->transitions.find(std::make_pair('s', *it))->second->to; // переходим в это состояние
                c_state = group->states.find(ind)->second; // если конечно, формируем выходную ситуацию.
                if (c_state->finish) { // finish state? Можем выйти.
                    // перешли по этому символу. Передаем наверх первый нетронутый символ
                    std::get<1>(cur_tuple).insert(std::make_pair(group->name, std::string{first, it + 1})); // добавили текущую группу захвата
                    list_exit.emplace_front(it + 1,std::get<1>(cur_tuple), next_state);
                    // здесь name надо вытащить из контейнера. Чтобы в продолжении можно было использовать
                    std::get<1>(cur_tuple).erase(std::get<1>(cur_tuple).find(group->name));
                    //std::cout << "check2";
                }
                is_cont = true;
            }
            if(!is_cont){
                break;
            }
        }
    }
    return list_exit;
}
bool Regex::search(const std::string& mytext,std::string &match, std::map<std::string, std::string> & groups) {
    //std::regex re(pattern);
    std::string text = mytext; // std::move
    if (!is_compiled) { // не был скомпилирован
        throw std::logic_error("Compile first!");
    }
    unsigned first = 0;// итератор на первый элемент
    bool result = false;
    std::string::iterator f_pos = text.begin();
    while (first < text.size()) {
        auto all_variants = run_through_group(f_pos, text.end(), this->automate, this->automate->start);
        if (all_variants.empty()) { // не нашлось
            first++;
            f_pos++;
            continue;
        }
        auto final = all_variants.begin();
        std::string final_str{f_pos,std::get<0>(*all_variants.begin())};
        //std::cout << *f_pos;
        for (auto check_it = all_variants.begin(); check_it != all_variants.end(); ++check_it) {
            std::string cur_str{f_pos,std::get<0>(*check_it)};
            //std::cout <<"\\" <<cur_str;
            if (cur_str.size() > final_str.size()) {
                final = check_it;
                final_str = std::move(cur_str);
            }
            //std::cout << "check";
        }
        match = std::move(final_str);
        groups = std::move(std::get<1>(*final));
        groups.erase(groups.find("")); // строка будет храниться в отдельной переменной. Хотя может быть и по пустой строке найдена, если тут переделать
        return true;
    }
    return false;
}
bool Regex::search(const std::string& mytext, const std::string& pattern, std::string &match, Captures & capts) {
    compile(pattern);
    bool res;
    std::map<std::string, std::string> groups;
    res = search(mytext,match,groups);
    capts.groups = groups;
    return res;
}
bool Regex::search(const std::string& mytext, std::string &match, Captures & capts) {
    bool res;
    std::map<std::string, std::string> groups;
    res = search(mytext,match,groups);
    capts.groups = groups;
    return res;
}
bool Regex::search(const std::string& mytext, std::string &match){
    std::map<std::string, std::string> groups;
    return search(mytext,match,groups);
}
bool Regex::search(const std::string& mytext, const std::string& pattern, std::string &match){
    compile(pattern);
    std::map<std::string, std::string> groups;
    return search(mytext,match,groups);
}
// Перегрузка для поиска с доступом к группам захвата через оператор индексации
std::string search(const std::string& text, const std::string& pattern, std::string groupName, std::string to) {
    // возвращает по индексу name of group строку и еще один параметр это то
    // куда кладу
    //std::regex re(pattern);
    //std::smatch matches;
    //if (std::regex_search(text, matches, re) && groupIndex < matches.size()) {
    //return matches[groupIndex];
    //}
    return "";
}
std::string search(const std::string& text, std::string groupName, std::string to) { // уже скомпилирован
    // возвращает по индексу name of group строку и еще один параметр это то
    // куда кладу
    //std::regex re(pattern);
    //std::smatch matches;
    // if (std::regex_search(text, matches, re) && groupIndex < matches.size()) {
    //     return matches[groupIndex];
    // }
    return "";
}
void Regex::compile(const std::string &regular_expression) {
    Ast MyAst{regular_expression};
    NFA MyNFA{MyAst};
    //DFA MyDFA{MyNFA};
    //automate = std::move(MyDFA);
    automate = std::make_shared<DFA>(MyNFA);
    automate->name = "";
    is_compiled = true;
}
#endif //LAB2TA_MYREGEX_H
