//
// Created by Марат on 31.07.2024.
//

#ifndef LAB2TA_MYDFA_H
#define LAB2TA_MYDFA_H
#include <vector>
#include <set>
#include <string>
#include <map>
#include "myNFA.h"
#include <memory>
#include <stack>
// ребро и state остаются без изменений
struct StateWMF : public State{
    bool finish = false; // true when is_finish = true
    explicit StateWMF(int ind) : State(ind){}
    StateWMF(int ind, bool fin) : State(ind), finish(fin){}
};
class DFA{ // коллизии имен надо проверить
public:
    int start;
    std::map<int, std::shared_ptr<StateWMF>> states; // по индексу состояния будем искать
    std::string name;
    std::map<std::shared_ptr<Transition> , std::shared_ptr<DFA>> capture_groups; // int - начальное состояние автомата сквозная нумерация
public:
    void Myprint();
    explicit DFA(const NFA & mynfa);
    //NFA(int s, std::string &pname);
    //NFA();
    //explicit NFA(int sstate);
private:
    std::set<std::shared_ptr<Transition>> find_all_capture_transitions_through_set(const std::set<int> &nfa_sts, const NFA &mynfa);
    std::set<int> get_states_through_other_transitions(const char ctype, char cur_char, const std::set<int> & nfa_sts, const NFA &mynfa);
    std::string find_all_char_transitions_in_nfa(const std::set<int> &nfa_sts, const NFA &mynfa);
    std::set<int> get_all_states_through_epsilon(const std::set<int> &dfastate, const NFA &mynfa);
};
void DFA::Myprint() {
    if(name.empty()){
        std::cout << "DFA AUTOMATE: " << std::endl;
    }
    else{
        std::cout << "name of the capture group: " << name <<  std::endl;
    }
    std::cout << "Start state: " << start << std::endl;
    std::cout << "All the states:" << std::endl;
    for (auto it = states.begin(); it != states.end(); ++it) {
        auto cur = it->second;
        std::cout << "State number: " << cur->index << std::endl;
        if(cur->finish){
            std::cout << "finish state " << std::endl;
        }
        std::cout << "Transitions: "<< std::endl;
        for (auto tr_it = cur->transitions.begin(); tr_it != cur->transitions.end(); ++tr_it) {
            if(tr_it->second->type == 's'){
                std::cout <<"\"" << tr_it->second->symbol <<"\"" <<" to " << tr_it->second->to << std::endl;
            }
            else if(tr_it->second->type == 'c'){
                std::cout << "capture transition " << " to " << tr_it->second->to << std::endl;
                std::shared_ptr<DFA> cpt_auto = this->capture_groups.find(tr_it->second)->second;
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
std::set<int> DFA::get_all_states_through_epsilon(const std::set<int> &dfastate, const NFA &mynfa) {
    std::stack<int> remnant_states;
    std::set<int> all_these_states;
    for (auto it = dfastate.begin(); it != dfastate.end(); ++it) {
        remnant_states.push(*it); // заталкиваем состояния
        all_these_states.insert(*it);
    }
    while (!remnant_states.empty()) {
        int cur_s_int = remnant_states.top();
        remnant_states.pop();
        auto cur_s = mynfa.states.find(cur_s_int)->second; // находим состояние по индексу
        auto range = cur_s->transitions.equal_range(std::make_pair('e', 'e')); // находит все элементы с этими ключами
        auto it = range.first; // первый элемент с этим ключом. Если таких нет, то он положит end()
        if (it != cur_s->transitions.end() && it->second->symbol == 'e' && it->second->type == 'e') {// если равны, то элементов с таким ключом нет
            do {
                if(all_these_states.find(it->second->to) == all_these_states.end()){ //  если элемент еще не добавлен это выполнится
                    remnant_states.push(it->second->to);
                    all_these_states.insert(it->second->to);
                }
                ++it;
            } while (it != range.second); // range.second - ключ, больший чем данный.( или end())
        }
    }
    return all_these_states;
}
std::string DFA::find_all_char_transitions_in_nfa(const std::set<int> &nfa_sts, const NFA &mynfa){
    std::string storage;
    for(auto it = nfa_sts.begin(); it != nfa_sts.end(); ++it){
        auto ptr_trans = mynfa.states.find(*it)->second->transitions.begin();
        auto trans_end  = mynfa.states.find(*it)->second->transitions.end();
        while(ptr_trans != trans_end){
            if(ptr_trans->second->type == 's' && storage.find(ptr_trans->second->symbol) == -1){
                storage += ptr_trans->second->symbol;
            }
            ptr_trans++;
        }
    }
    return  storage;
}
std::set<std::shared_ptr<Transition>> DFA::find_all_capture_transitions_through_set(const std::set<int> &nfa_sts, const NFA &mynfa){
    std::set<std::shared_ptr<Transition>> storage;
    for(auto it = nfa_sts.begin(); it != nfa_sts.end(); ++it){
        auto ptr_trans = mynfa.states.find(*it)->second->transitions.begin();
        auto trans_end  = mynfa.states.find(*it)->second->transitions.end();
        while(ptr_trans != trans_end){
            if(ptr_trans->second->type == 'c' ){
                storage.insert(ptr_trans->second);
            }
            ptr_trans++;
        }
    }
    return storage;
}
std::set<int> DFA::get_states_through_other_transitions(const char ctype, char cur_char, const std::set<int> & nfa_sts, const NFA &mynfa){ //
    std::set<int> put_here;
    for(auto it = nfa_sts.begin(); it != nfa_sts.end(); ++it){
        auto ptr_trans = mynfa.states.find(*it)->second->transitions.begin();
        auto trans_end  = mynfa.states.find(*it)->second->transitions.end();
        while(ptr_trans != trans_end){
            if(ptr_trans->second->type == ctype && ptr_trans->second->symbol == cur_char){
                put_here.insert(ptr_trans->second->to);
            }
            ptr_trans++;
        }
    }
    return  put_here;
}
DFA::DFA(const NFA &mynfa) {
    std::set<int> temp;
    temp.insert(mynfa.start);
    std::set<int> s_zero{std::move(get_all_states_through_epsilon(temp,mynfa))}; // эпсилон замыкание для стартового состояния
    int max_index_s = 0;
    std::map<std::set<int>, int> dfa_s_were_added;
    dfa_s_were_added.insert(std::make_pair(s_zero,max_index_s)); // первое состояние создали
    auto ptr1 = std::make_shared<StateWMF>(max_index_s);
    if(s_zero.find(mynfa.last) != s_zero.end()){ // проверка на конечное состояние
        ptr1->finish = true;
    }
    this->states.insert(std::make_pair(max_index_s,ptr1)); // это состояние имеет все, кроме ребер.
    std::stack<std::set<int>> dfa_s_were_n_proc;
    dfa_s_were_n_proc.push(s_zero);
    this->start = 0;
    while(! dfa_s_were_n_proc.empty()){ // пока есть необработанные состояния
        std::set<int> state_D = dfa_s_were_n_proc.top(); // достаём необработанное состояние. У него остались только символ-переходы и capture
        dfa_s_were_n_proc.pop();
        std::string a_symbols = std::move(find_all_char_transitions_in_nfa(state_D, mynfa)); // найдем все переходы по символам алфавита
        for(auto it = a_symbols.begin(); it != a_symbols.end(); ++it){
            std::set<int> state_for_transition_w_eps = std::move(get_states_through_other_transitions('s', *it, state_D, mynfa)); // находим состояния, в которые
            // попадаем по этому символ-переходу после эпсилон-замыкания
            std::set<int> state_for_transition = std::move(get_all_states_through_epsilon(state_for_transition_w_eps, mynfa));
            // есть ли уже такое состояние?
            if(dfa_s_were_added.find(state_for_transition) == dfa_s_were_added.end()){ // ключи в set упорядочены
                max_index_s++;
                dfa_s_were_added.insert(std::make_pair(state_for_transition,max_index_s)); // создаем новое состояние
                auto new_state = std::make_shared<StateWMF>(max_index_s);
                if(state_for_transition.find(mynfa.last) != state_for_transition.end()){ // проверка на конечное состояние
                    new_state->finish = true;
                }
                this->states.insert(std::make_pair(max_index_s,new_state)); // это состояние имеет все, кроме ребер.
                dfa_s_were_n_proc.push(state_for_transition); // добавляем как необработанное
            }
            // добавим ребро
            int next_ind = dfa_s_were_added.find(state_for_transition)->second;
            int d_ind = dfa_s_were_added.find(state_D)->second;
            this->states.find(d_ind)->second->transitions.insert(std::make_pair(std::make_pair('s', *it),
                                                                                std::make_shared<Transition>('s', *it,next_ind)));
        }
        auto capt_trans = std::move(find_all_capture_transitions_through_set(state_D,mynfa)); // в set не добавляются одинаковые ребра
        for(auto it = capt_trans.begin(); it != capt_trans.end(); ++it){ // как организовать переход по группе
            std::set<int> state_for_transition_w_eps;
            state_for_transition_w_eps.insert((*it)->to);
            std::set<int> state_for_transition = std::move(get_all_states_through_epsilon(state_for_transition_w_eps, mynfa));
            if(dfa_s_were_added.find(state_for_transition) == dfa_s_were_added.end()){ // ключи в set упорядочены
                max_index_s++;
                dfa_s_were_added.insert(std::make_pair(state_for_transition,max_index_s)); // создаем новое состояние
                auto new_state = std::make_shared<StateWMF>(max_index_s);
                if(state_for_transition.find(mynfa.last) != state_for_transition.end()){ // проверка на конечное состояние
                    new_state->finish = true;
                }
                this->states.insert(std::make_pair(max_index_s,new_state)); // это состояние имеет все, кроме ребер.
                dfa_s_were_n_proc.push(state_for_transition); // добавляем как необработанное
            }
            // добавим ребро
            int next_ind = dfa_s_were_added.find(state_for_transition)->second;
            int d_ind = dfa_s_were_added.find(state_D)->second;
            auto tr = std::make_shared<Transition>('c', 'c',next_ind);
            this->states.find(d_ind)->second->transitions.insert(std::make_pair(std::make_pair('c', 'c'),
                                                                                tr));
            // добавляем автомат
            std::shared_ptr<DFA> subdfa = std::make_shared<DFA>(*(mynfa.capture_groups.find(*it)->second));
            subdfa->name = mynfa.capture_groups.find(*it)->second->name;
            this->capture_groups.insert(std::make_pair(tr,subdfa));
        }
    }
}
#endif //LAB2TA_MYDFA_H
