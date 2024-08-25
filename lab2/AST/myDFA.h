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
    explicit DFA(DFA && dfa) noexcept;
    DFA& operator = (DFA &&dfa) noexcept;
    DFA() = default;
private:
    void  minimization_create_states(std::set<std::set<int>> all_groups);
    const std::set<int>* minimization_find_group(std::set<std::set<int>> &all_groups_old, int targetValue, std::pair<char,char> key_trans, std::string cname);
    void minimization();
    std::set<std::shared_ptr<Transition>> find_all_capture_transitions_through_set(const std::set<int> &nfa_sts, const NFA &mynfa);
    std::set<int> get_states_through_other_transitions(char ctype, char cur_char, const std::set<int> & nfa_sts, const NFA &mynfa);
    std::string find_all_char_transitions_in_nfa(const std::set<int> &nfa_sts, const NFA &mynfa);
    std::set<int> get_all_states_through_epsilon(const std::set<int> &dfastate, const NFA &mynfa);
    std::set<std::shared_ptr<Transition>> find_all_char_transitions_in_dfa(const std::set<int> &dfa_sts);
    std::set<std::shared_ptr<Transition>> find_all_capture_transitions_through_set(const std::set<int> &dfa_sts);
};
DFA& DFA::operator = (DFA &&dfa) noexcept{
    this->start = dfa.start;
    this->states = std::move(dfa.states);
    this->name = std::move(dfa.name);
    this->capture_groups = std::move(dfa.capture_groups);
    return *this;
}
DFA::DFA(DFA && dfa)noexcept{
    this->start = dfa.start;
    this->states = std::move(dfa.states);
    this->name = std::move(dfa.name);
    this->capture_groups = std::move(dfa.capture_groups);
}
void  DFA::minimization_create_states(std::set<std::set<int>> all_groups){
    //int i =0;
    //std::cout << std::endl;
    //for(auto itf = all_groups.begin(); itf != all_groups.end(); ++itf, ++i){
    //    std::cout << i;
    //    for(auto its = (*itf).begin(); its != (*itf).end(); ++its ){
    //        std::cout << *its << " ";
    //    }
    //    std::cout << std::endl;
    //}
    std::map<std::set<int>, int> dfa_s_were_added;
    std::stack<std::set<int>> dfa_s_were_n_proc;
    std::map<int, std::shared_ptr<StateWMF>> nstates;
    int max_index_s = -1;
    for(auto it = all_groups.begin(); it != all_groups.end(); ++it){ // определяем группу в которой лежит стартовое состояние
        auto it_targ = (*it).find(this->start);
        if (it_targ != (*it).end()){
            max_index_s++;
            auto new_state = std::make_shared<StateWMF>(max_index_s);

            if(     this->states.find(*(*it).begin())->second->finish    ){ // проверка на конечное состояние, если любое состояние конечно, то и это
                new_state->finish = true;
            }
            nstates.insert(std::make_pair(max_index_s, new_state));
            dfa_s_were_added.insert(std::make_pair(*it,max_index_s));
            dfa_s_were_n_proc.push(*it);
        } // добавили стартовое состояние оно имеет индекс 0
    }
    while(!dfa_s_were_n_proc.empty()) {
        auto d_states = dfa_s_were_n_proc.top();
        dfa_s_were_n_proc.pop();
        int random_state = *(d_states.begin());
        int index_in_minimized = dfa_s_were_added.find(d_states)->second;
        // добавляем все ребра
        //std::cout << "index " << index_in_minimized;
        //for(auto itt = d_states.begin(); itt != d_states.end(); ++itt){
        //    std::cout << "state" << *itt << std::endl;
       // }
       for(auto itera = this->states.find(random_state)->second->transitions.begin(); itera != this->states.find(random_state)->second->transitions.end(); ++itera){
           auto pair = *itera;
           nstates.find(index_in_minimized)->second->transitions.insert(pair);
       }
        //nstates.find(index_in_minimized)->second->transitions = std::move(
        //        this->states.find(random_state)->second->transitions); // потом to надо будет поменять
        for (auto trans = nstates.find(index_in_minimized)->second->transitions.begin();
             trans != nstates.find(index_in_minimized)->second->transitions.end(); ++trans) {
            // добавляем новые состояния, если их еще не было. Для состояний, в которые переходим необходимо определить группу
            for (auto it = all_groups.begin(); it != all_groups.end(); ++it) { // для каждого состояния в которое переходим создаем состояние в минимизированном
                auto it_targ = (*it).find(trans->second->to); // представитель группы найден?
                if (it_targ != (*it).end()) {
                    if (dfa_s_were_added.find(*it) == dfa_s_were_added.end()) { // такое состояние было уже добавлено в минимизированный?
                        // создаем новое состояние
                        max_index_s++;
                        auto new_state = std::make_shared<StateWMF>(max_index_s);
                        if (this->states.find(*(*it).begin())->second->finish) { // проверка на конечное состояние, если любое состояние конечно, то и это
                            new_state->finish = true;
                            //for(auto itt = it->begin(); itt != it->end(); ++itt){
                            //    std::cout << "check " << *itt;
                            //}
                            //std::cout << max_index_s;
                        }
                        nstates.insert(std::make_pair(max_index_s, new_state));
                        dfa_s_were_added.insert(std::make_pair(*it, max_index_s));
                        dfa_s_were_n_proc.push(*it);
                        //std::cout << dfa_s_were_added.find(*it)->second;
                    }
                    trans->second->to = dfa_s_were_added.find(*it)->second;
                    // добавляем ребро и меняем to
                    break;
                }
            }
        }
        //std::cout << "index " << index_in_minimized;
        //for(auto itt = d_states.begin(); itt != d_states.end(); ++itt){
        //    std::cout << "state" << *itt << std::endl;
        // }
    }
    this->states = std::move(nstates);
    // в capture groups остались элементы, которые не будут использоваться?
}
const std::set<int>* DFA::minimization_find_group(std::set<std::set<int>> &all_groups_old, int targetValue, std::pair<char,char> key_trans, std::string cname = ""){
    // сначала надо понять есть ли вообще такое ребро
    auto iter = this->states.find(targetValue)->second->transitions.find(key_trans);
    if(iter == this->states.find(targetValue)->second->transitions.end()){
        return nullptr; // такого ребра нет
    }
    int here = iter->second->to;
    if(key_trans == std::make_pair('c','c')){ // такое ребро точно есть
        auto range = this->states.find(targetValue)->second->transitions.equal_range(key_trans); // находит все элементы с этими ключами
        auto it = range.first; // Первый элемент с этим ключом. Если таких нет, то он положит end(). Хоть 1 то есть.
        do {
            if(this->capture_groups.find(it->second)->second->name == cname){ // Ребро есть. Надо найти группу, в которой int находится
                for(auto iters = all_groups_old.begin(); iters != all_groups_old.end(); ++iters){
                    auto it_targ = (*iters).find(here);
                    if (it_targ != (*iters).end()){
                        const std::set<int> *ptr = &(*iters);
                        return ptr;
                    }
                }
            }
            ++it;
        } while (it != range.second); // range.second - ключ, больший чем данный.( или end())
        return nullptr; // ребра в нужный автомат нет
    }
    for(auto it = all_groups_old.begin(); it != all_groups_old.end(); ++it){
        auto it_targ = (*it).find(here);
        if (it_targ != (*it).end()){
            const std::set<int> *ptr = &(*it);
            return ptr;
        }
    }
    return nullptr;
}
 void DFA::minimization(){
     std::set<std::set<int>> all_groups_old;
     std::set<int> f_states;
     std::set<int> unf_states; // очень долго сравнить таблицы, потому по количеству элементов будем смотреть прибавились ли группы
     unsigned long long size_new,size_old;
     for(auto it = this->states.begin(); it != this->states.end(); ++it){
         if(it->second->finish ){
             f_states.insert(it->first);
         }
         else{
             unf_states.insert(it->first);
         }
     } // создали 2 первые группы
     all_groups_old.insert(std::move(f_states));
     all_groups_old.insert(std::move(unf_states));
     do{ // пункт 3
         std::set<std::set<int>> all_groups_new;// все распиленные группы будут здесь
         for(auto it = all_groups_old.begin(); it != all_groups_old.end(); ++it){ // it это set<int>. Тут проходим по каждой группе
            std::set<std::set<int>> division_of_group_old; // временное хранилище нарезаний одной группы total division
            division_of_group_old.insert(*it); // это для  all_groups_new он будет обновляться после каждого перехода по символу какому-то или capture- переходу
            // if группа состоит из одного элемента может оптимизировать работу?
            auto a_symbols = std::move(find_all_char_transitions_in_dfa(*it)); // найдем все переходы по символам алфавита и на том же уровне capture transitions
            auto c_transitions = std::move(find_all_capture_transitions_through_set(*it)); // может еще не быть данного ребра это точно надо учесть
            a_symbols.merge(c_transitions);
            //std::cout << a_symbols.size();
            for(auto it_c = a_symbols.begin(); it_c != a_symbols.end(); ++it_c) { // деление по всем этим переходам будет
                std::set<std::set<int>> division_of_group_new; // этот контейнер хранит разрезы, сделанные внутри второго Bпереди стоящего for
                for (auto it_div = division_of_group_old.begin(); it_div !=
                        division_of_group_old.end(); ++it_div) { // для каждой группы division надо сделать проверку на разделение
                    // find group(int) в которое ведет ребро. Это будет возвращать ссылку или указатель на эту группу
                    std::map<const std::set <int> *, std::set<int>> div_bec_trans; // ключ - указатель на элемент  all_groups_old
                    for(auto divison_divided_it = it_div->begin(); divison_divided_it != it_div->end(); ++divison_divided_it ){
                        std::string cname;
                        if(this->capture_groups.find(*it_c) != this->capture_groups.end()){ // если это capture ребро, то
                            cname = this->capture_groups.find(*it_c)->second->name;
                        }
                        else{
                            cname = "";
                        }
                        auto ptr = minimization_find_group(all_groups_old, *divison_divided_it, std::make_pair((*it_c)->type, (*it_c )->symbol), cname);
                        if(div_bec_trans.find(ptr) == div_bec_trans.end()){ // для этого состояния дка еще не было создано группы
                            div_bec_trans.insert(std::make_pair(ptr,std::set<int>{*divison_divided_it}));
                        }
                        else{
                            div_bec_trans.find(ptr)->second.insert(*divison_divided_it); // мини группка создана
                        }
                    }
                    //std::cout << div_bec_trans.size();
                    for(auto c_it =  div_bec_trans.begin(); c_it != div_bec_trans.end(); ++c_it){
                        division_of_group_new.insert(c_it->second);
                    }
                    // членит одну группу на целую кучу ввиду обрабатываемого перехода. Одна группа может расчлениться на 10 переход/ нет перехода/ переход в 4 разные группы
                }
                division_of_group_old = std::move(division_of_group_new); // new уничтожиться
            }
            all_groups_new.merge(division_of_group_old); // правильно
         }
         //std::cout << "check";
         size_old = all_groups_old.size();
         size_new = all_groups_new.size();
         all_groups_old = std::move(all_groups_new); // swaps
         //std::cout << size_new << size_old;
     }
     while(size_old != size_new);
     // создание состояний
     /*unsigned long long size = 0;
     std::cout << all_groups_old.size();
     for(auto it = all_groups_old.begin(); it != all_groups_old.end(); ++it){
         size += (*it).size();
     }
     std::cout << size;*/
     minimization_create_states(all_groups_old);
 }
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
std::set<std::shared_ptr<Transition>> DFA::find_all_char_transitions_in_dfa(const std::set<int> &dfa_sts){
    std::set<std::shared_ptr<Transition>> storage;
    std::string storage_syms;
    for(auto it = dfa_sts.begin(); it != dfa_sts.end(); ++it){
        auto ptr_trans = this->states.find(*it)->second->transitions.begin();
        auto trans_end  = this->states.find(*it)->second->transitions.end();
        while(ptr_trans != trans_end){
            if(ptr_trans->second->type == 's' && storage_syms.find(ptr_trans->second->symbol) == -1){
                storage_syms += ptr_trans->second->symbol;
                storage.insert(ptr_trans->second);
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
std::set<std::shared_ptr<Transition>> DFA::find_all_capture_transitions_through_set(const std::set<int> &dfa_sts){
    std::set<std::shared_ptr<Transition>> storage;
    for(auto it = dfa_sts.begin(); it != dfa_sts.end(); ++it){
        auto ptr_trans = this->states.find(*it)->second->transitions.begin();
        auto trans_end  = this->states.find(*it)->second->transitions.end();
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
    minimization();
}
#endif //LAB2TA_MYDFA_H
