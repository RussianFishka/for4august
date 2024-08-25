//
// Created by Марат on 23.07.2024.
//
#include "defast.h"
#include <list>
#include <iostream>
#include <set>
std::pair<std::list<Node *>::iterator,std::list<Node *>::iterator> Ast::find_first_and_last(
        std::list<Node *>::iterator begin, std::list<Node *>::iterator end) {
    auto ptr = begin;
    auto current_first = begin;
    std::list<Node *>::iterator current_last;
    ptr++;
    do{
        if((*ptr)->symbol == ')' && !((*ptr)->true_symbol)){ // проверка экранирована ли
            current_last = ptr;
            break;
        }
        if((*ptr)->symbol == '(' && !((*ptr)->true_symbol)){
            current_first = ptr;
        }
        ptr++;
    }
    while(ptr != end);
    if(ptr == end){ // не нашлась вторая скобка
        throw std::logic_error("check your regular thing");
    }
    return std::pair<std::list<Node *>::iterator ,std::list<Node *>::iterator > {current_first,current_last};
}
void Ast::del_escapes_properly(std::list<Node *> &mylist){
    std::list<Node *>::iterator ptr = mylist.begin(); // отсюда включительно идет просмотр листьев и деревьев
    std::string operations = "*?|<>{}()";
    while(ptr != mylist.end()) {// удалим все символы экранирования
        if((*ptr)->symbol == '*'){ // добавил
            (*ptr)->true_symbol = true;
            ptr++;
            continue;
        }
        if((*ptr)->symbol == '&'){ // добавил
            (*ptr)->true_symbol = true;
            ptr++;
            continue;
        }
        if((*ptr)->symbol == '.'){
            auto next = ptr;
            next++;
            if(next != mylist.end() && (*next)->symbol == '.'){
                auto nextnext = next;
                nextnext++;
                if(nextnext != mylist.end() && (*nextnext)->symbol == '.'){
                    (*ptr)->symbol = '*';
                    (*ptr)->true_symbol = false;
                    ptr++;
                    delete (*ptr);
                    mylist.erase(ptr);
                    ptr++;
                    delete (*ptr);
                    mylist.erase(ptr);
                    ptr++;
                    continue;
                }
                else{
                    ptr++;
                    ptr++;
                    continue;
                }

            }
            else{
                ptr++;
                continue;
            }
        }
        if ((*ptr)->symbol == '%') {
            delete (*ptr);
            mylist.erase(ptr);
            ptr++;
            if(ptr != mylist.end()){
                // клини добавил
                if((*ptr)->symbol == '.'){
                    auto next = ptr;
                    next++; // на возможную 2 точку
                    if(next != mylist.end() && (*next)->symbol == '.'){
                        ptr++;
                        ptr++;
                        if(ptr != mylist.end() && (*ptr)->symbol == '.'){ // на 3 точку должны указывать
                        }
                        else{
                            throw std::logic_error("3-ья точка где?");
                        }
                    }// else - обычная ситуация одна точка экранирова
                }
                // если затем идет процент => экранирован процент
                else if (operations.find((*ptr)->symbol) != -1) { // если экранирован символ операции find возвращает -1, если символ не найден
                    (*ptr)->true_symbol = true;
                }
                ptr++; // третий символ анализируется
                if (ptr == mylist.end() || (*ptr)->symbol != '%'){ // cимвол экранируется с двух сторон. Это обязательно
                    throw std::logic_error("check your regular thing");
                }
                delete (*ptr);
                mylist.erase(ptr);
            }
            else{
                throw  std::logic_error("check your regular thing"); //не было второго символа экранирования
            }
            ptr++;
            continue;
        }
        if((*ptr)->symbol == '{' || (*ptr)->symbol == '<'){ // смысл в том что на внутренности экранирование не распространяется
            char bracket = (*ptr)->symbol;
            while(ptr != mylist.end()){ // будем знать, что их пары точно есть
                if(bracket == '{'){
                    if((*ptr)->symbol == '}'){
                        ptr++;
                        break;
                    }
                }
                if(bracket == '<'){
                    if((*ptr)->symbol == '>'){
                        ptr++;
                        break;
                    }
                }
                ptr++;
            }
            if(ptr == mylist.end()){
                 throw  std::logic_error("check your regular thing");// unpropername
            }
        }
        ptr++;
    }
}
Ast::Ast(const std::string &myregex) {
    std::set<std::string> c_added_names;
    std::list<Node *> mylist;
    mylist.push_back(new Node{'('});
    for(auto it = myregex.begin(); it != myregex.end(); ++it){
        mylist.push_back(new Node {*it});
    }
    mylist.push_back(new Node{')'}); // подготовка к алгоритму из регулярки в сд
    Ast::del_escapes_properly(mylist);
    //std::list<Node *>::iterator ptr10;
    while(mylist.size() != 1){
        auto set = Ast::find_first_and_last(mylist.begin(), mylist.end()); // будем работать только внутри этой пары скобок, которая вернется
        std::list<Node *>::iterator ptr = set.first;
        ptr++; // хотим установить указатель на место прохода
        Node * father = nullptr; // отец группы захвата.
        //std::cout << "My world" << std::endl;
        if((*ptr)->symbol == '<' && !((*ptr)->true_symbol) && (*ptr)->left == nullptr){ // проверка на группу захвата следующий после скобки символ это символ группы захвата?
            father = *ptr;// вся дальнейшая операция это группа захвата. Значит этот символ будет отцом имя будет удалено и вторая кавычка
            ptr++;
            //std::cout << "My world" << std::endl;
            while((*ptr)->symbol != '>'){
                father->capture_group_cbracketsnum += (*ptr)->symbol;
                //ptr10 = ptr;
                //ptr10++;
                delete (*ptr);
                //std::cout << "My world" << std::endl;
                mylist.erase(ptr);
                //std::cout << "My world" << std::endl;
                ptr++;
                //ptr = ptr10;
                //std::cout << "My world" << std::endl;
            }
            //std::cout << "My world" << std::endl;
            if( father->capture_group_cbracketsnum.empty()){
                throw std::logic_error(" нет имени в именованной группе захвата");
            }
            else{ // удаляем >
                delete (*ptr);
                mylist.erase(ptr);
            }
            if(c_added_names.find(father->capture_group_cbracketsnum) == c_added_names.end()){
                 c_added_names.insert(father->capture_group_cbracketsnum);
             }
            else{
                throw std::logic_error("Такое имя у группы захвата уже есть");
            }
            ptr++; // установили указатель на место, в котором допустим проход.
        } // весь дальнейший алгоритм как будто без существования группы захвата. В конце только надо будет присоединить ребенка к отцу.
        // если у символа операция нет детей, то ребенок - эпсилон
        //std::cout << "My world" << std::endl;
        std::list<Node *>::iterator prev_ptr = ptr;
        std::string repaunvailoper = "*?{|";
        while(ptr != set.second){// замыкание Клини и опциональный оператор and curly brackets
            if(((*ptr)->symbol == '*' || (*ptr)->symbol == '?' || (*ptr)->symbol == '{') && (*ptr)->true_symbol == false){ // настоящая операция Клини
                if(repaunvailoper.find((*prev_ptr)->symbol) == -1  ||  (*prev_ptr)->true_symbol == true){ // символ не операторский или был экранирован в противном
                    //случае eps ребенок, то остается nullptr, но при этом true_symbol == false ситуация вида *asfd тоже обработана
                    (*ptr)->left = *prev_ptr;
                    mylist.erase(prev_ptr);
                }
                if((*ptr)->symbol == '{'){
                    auto opening_curly = ptr;
                    ptr++;
                    while((*ptr)->symbol != '}' ){
                        if(!((*ptr)->symbol <= 9 && (*ptr)->symbol >= 0)){
                            //throw
                        }
                        (*opening_curly)->capture_group_cbracketsnum += (*ptr)->symbol; // прибавляем цифры
                        delete (*ptr);
                        mylist.erase(ptr);
                        ptr++;
                    }
                    delete (*ptr);
                    mylist.erase(ptr); // удаляем curly {
                    if((*opening_curly)->capture_group_cbracketsnum.size() == 0){
                        //throw curly пустые
                    }
                    prev_ptr = opening_curly;
                }
                else{
                    prev_ptr = ptr;
                }
            }
            else{
                prev_ptr = ptr;
            }
            ptr++;
        }
        //ptr = begin_iteration; не работает этот итератор перестает быть началом
        ptr = set.first;
        if(father){ // тут надо сдвинуться еще на одну позицию. Отсчет от итератора можно вести только, если он в контейнере
            ptr++;
        }
        ptr++;
        auto ptr_next = ptr;
        if(ptr_next != set.second){
            ptr_next++;
        }
        while(ptr_next != set.second){ //concatenation
            if(((*ptr)->symbol != '|' || (*ptr)->true_symbol || (*ptr)->left || (*ptr)->right) && ((*ptr_next)->symbol != '|' || (*ptr_next)->true_symbol || (*ptr_next)->left || (*ptr_next)->right)){ // операнды это не операция или
                auto concat = mylist.insert(ptr_next, new Node{'&'}); // этих узлов еще не было.
                (*concat)->left = *ptr;
                mylist.erase(ptr);
                (*concat)->right = *ptr_next;
                mylist.erase(ptr_next);
                ptr_next = concat; // дальше рассматриваются эта конкатенация и следующий за ней символ //a&b  &c
            }
            ptr = ptr_next;
            ptr_next++;
            //std::cout << (*ptr_next)->symbol;
        }
        ptr = set.first;
        if(father){
            ptr++;
        }
        ptr++;// первый нормальный символ после скобки
        ptr_next = ptr;
        //std::cout << "check";
        bool inarow = false; // проверяем случай |sdsd
        if((*ptr)->symbol == '|' && (*ptr)->true_symbol == false){
            inarow = true;
        }
        while(ptr != set.second){ //or у этой операции может быть 1 ребенок как слева так и справа
            ptr_next++;
            //std::cout << (*ptr)->symbol;
            //std::cout << "1";
            if((*ptr)->symbol == '|' && !((*ptr)->true_symbol)){ // настоящая операция //ошибка в пределах
                //std::cout << "1";
                if(!inarow){ // проверяем случай |sdsd
                    (*ptr)->left = *prev_ptr;
                    mylist.erase(prev_ptr);
                }
                if(ptr_next != set.second){ // если это ситуация f||a, то у первого будет эпсилон сын справа
                    //std::cout << "2";
                    if((*ptr_next)->symbol == '|' && (*ptr_next)->true_symbol == false && (*ptr_next)->left == nullptr && (*ptr_next)->right == nullptr){
                        // это лист или нет, если не лист, то как будто обычный символ
                        // лист мы сделаем нашим предком на следующей итерации а правое поддерево этого будет пустым
                        prev_ptr = ptr;
                        //std::cout << "3";
                    }
                    else{
                        //std::cout << "4";
                        (*ptr)->right = *ptr_next;
                        mylist.erase(ptr_next);
                        prev_ptr = ptr;//yes my friend!
                        //ptr = ptr_next; // когда 2 подряд | это не работает
                   }
                }
            }
            else{
                //prev_ptr++;
                prev_ptr = ptr;
            } // второй предел
            inarow = false;
            ptr++;//yes
            ptr_next = ptr;
        }
        if(father != nullptr){ // доработки группы захвата
            auto ftree = set.first; // скобка
            ftree++; // доступ к <
            ftree++; // дерево
            if(ftree != set.second){ // может быть эпсилон ребенок
                father->left = *ftree;
                mylist.erase(ftree);
            }
        }
        delete *set.first;
        mylist.erase(set.first);
        delete *set.second;
        mylist.erase(set.second); // ожидается, что внутри остался только 1 узел
    }
    root = mylist.front();
    //std::cout << "check";
}
void Ast::ShowTree() const {
    if(root){
        std::cout << "Tree: " << std::endl;
        PutTree(root, 0);
    }
    else{
        std::cout << "Nothing to show" << std::endl;
    }
}
void Ast::PutTree(Node *ptr, int level)const {
    int i = level;
    if(ptr){
        PutTree(ptr->right, level + 1);
        while(i-- > 0){
            std::cout<< "   ";
        }
        std::cout << ptr->symbol<< '\n';
        PutTree(ptr->left, level + 1);
    }
}
void Ast::delete_tree(Node* tr) {
    if (tr != nullptr) {
        delete_tree(tr->left);
        delete_tree(tr->right);
        delete tr;
        tr = nullptr;
    }
}
