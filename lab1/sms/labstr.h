//
// Created by Марат on 30.06.2024.
//
/*#ifdef identifier
 код, находящийся здесь, компилируется, если identifier уже был определен для препроцессора в команде #define.
#endif*/
// оберточный класс
#ifndef SMS_LABSTR_H
#define SMS_LABSTR_H
#include <string>
#include <iostream>
#include <vector>
#include "labstr_sm.h"
#include "NumAnalitics.h"
#ifdef CRTP
class Labstr : public LabstrContext<Labstr>
#else
class Labstr
#endif
{
private:
#ifndef CRTP
    labstrContext _fsm;
#endif
    bool isAcceptable;
    std::string buffer;
    int count;
    int smscase;
    std::vector<std::string> bufnums;
    // If a string is acceptable, then this variable is set to true;
    // false, otherwise.
public:
    Labstr();
    // Default constructor.

    ~Labstr() {};
    // Destructor.

    bool CheckString(const std::string & thestr, proj::NumAnalitics & store);
    // Checks if the string is acceptable.
    //Когда функция объявлена как inline, она может быть определена в заголовочном файле (вместо отдельного файла с реализацией).
    //Это предотвращает проблемы с множественным включением заголовочных файлов и конфликтами имен при линковке.

     int getCount() const;
    void setCount(const int &valuecount){
        count = valuecount;
    } //  хеадер добавляется в cpp файлы. Они превращаются в объектные файлы с defined функциями в них. Получилось нарушение one definition rule inline исправляет это
    inline void Acceptable()
    { isAcceptable = true; };

    inline void Unacceptable()
    { isAcceptable = false; };
    void addsymbbuf(const char symb){
        buffer += symb;
        //std::cout << buffer << std::endl;
    }
    void cleanbuf(){
        buffer.clear();
        //std::cout << "cringe "<< std::endl;
    }
    void addnum(){
        bufnums.push_back(std::move(buffer));
    }
    bool isTelorFax();
    bool smsfor(){
        if(smscase){
            return true;
        }
        return false;
    }
    void setsmsflagzero(){
        smscase = 0;
    }
    bool isSms();
    // State map actions.
};

#endif

