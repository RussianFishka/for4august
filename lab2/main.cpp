#include <iostream>
#include "AST/defast.h"
#include <string>
#include "AST/myNFA.h"
#include "AST/myDFA.h"
int main() {
    try {
        std::string b = "ca|(dsds){3}dd"; //
        std::string a = "f(<arr>sd(<a>sd)(<b>sd)d|ds)namc(<agx>sdsd|{3}dssd?)a"; //
        std::string m = "(c||as*|e{3})|(ab)"; //
        std::string zz = "((<name>c)c||as*|e{3})|(ab)"; //
        std::string s = "(<name>c||as|e)j{4}j(<sdf>c||as|e)|s";//
        std::string dd = "|a|sd";
        std::string hh = "(<name>c||as|e)j{4}j|a|(<name>c||as|e)";//sd";
        std::cout << "1" << std::endl;
        Ast myast{m}; // вставляй без пробела строку
        //std::cout << "2" << std::endl;
        myast.ShowTree();
        std::cout << "1" << std::endl;
        NFA myauto{myast};
        myauto.Myprint();
        DFA mydfa{myauto};
        mydfa.Myprint();
        std::cout << "1" << std::endl;
    }
    catch(...){
        std::cout << "error";
    }
    return 0;
}
