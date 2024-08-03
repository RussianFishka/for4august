//
// Created by Марат on 29.04.2024.
//
#include <iostream>
#include <regex>
#include "myregforta.h"
#include "NumAnalitics.h"
bool checkstring(std::string &str, proj::NumAnalitics &store){
    /*std::regex regular ("(sms|tel|fax).*");
    std::regex regulartelorfax ("(?:tel|fax)[\\s\\t](\\+[0-9]{11})(?:,(\\+[0-9]{11}))*");// non capturing group
    std::regex regularsms("sms[\\s\\t](\\+[0-9]{11})(?:,(\\+[0-9]{11}))*[\\s\\t][0-9a-zA-Z%.,!?]{1,64}");// или
    std::cmatch dettype;
    std::cmatch pars;
    if(regex_match(str.c_str(),dettype,regular)){
        //std::cout << dettype[1] << std::endl;
        if(dettype[1] == "sms") {
            if(regex_match(str.c_str(),pars,regularsms) != 1){
                return false;
            }
        }
        else{
            if(regex_match(str.c_str(),pars,regulartelorfax) != 1){
                return false;
            }
        }
        for(int i = 1; pars.size() > i; i++){
            //std::cout << pars.size();
            store.add(pars[i]);
        }
        return true;
    }
    return false; // непринимающее состояние*/
    std::regex regular ("(?:tel|fax)[\\s\\t](\\+[0-9]{11}(?:,\\+[0-9]{11})*)|sms[\\s\\t](\\+[0-9]{11}(?:,\\+[0-9]{11})*)(?:[\\s\\t][0-9a-zA-Z%.,!?]{1,64})?");
    std::regex num("\\+[0-9]{11}");
    std::smatch cut;
    std::smatch pars;
    if(regex_match(str,cut,regular)){
        int i = 1; // это часть может быть пустой
        if(cut[1].str() == ""){
            i = 2;
        }
        std::string a = cut[i].str(); // конвертация sub_match в std::string и передача
        while(regex_search(a,pars,num)){
            store.add(pars.str());
            a = pars.suffix().str(); // вовзвращает оставшуюся часть строки в виде sub_match после совпадаения а str конвертирует в string
        }
        std::cout << "the truth" << std::endl;
        return true;
    }
    std::cout << "false" << std::endl;
    return false; // непринимающее состояние
}