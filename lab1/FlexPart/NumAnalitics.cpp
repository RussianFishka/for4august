//
// Created by Марат on 06.05.2024.
//

#include "NumAnalitics.h"
#include <iostream>
#include <algorithm>
namespace proj{
    void NumAnalitics::add(std::string serstr){
        auto iter = std::find_if(pairs.begin(), pairs.end(),[serstr ](const std::pair<std::string, int>& p) {
            return p.first == serstr;
        });
        if(iter != pairs.end()) {
            (*iter).second = (*iter).second + 1;
        }
        else{
            pairs.push_back(std::make_pair(serstr,1));
        }
    }
    void NumAnalitics::print(){
        for(auto it = pairs.begin(); it != pairs.end(); it++){
            std::cout <<  ((*it).first.c_str()) << " times - " << ((*it).second) << std::endl;
        }
    }
}