#include <iostream>
#include "AST/defast.h"
#include <string>
#include "AST/myNFA.h"
#include "AST/myDFA.h"
#include "AST/myRegex.h"
int main() {
    try {
        std::string b = "ca|(dsds){3}dd"; //
        std::string a = "f(<arr>sdsd(<b>sd)d|ds)nam|c(<agx>sdsd|{3}dssd?)a"; //
        std::string m = "(c||d...as...|e{3})|.(ab)";
        std::string pk = "(c||d...as|e{3})|.(ab)";
        std::string pk1 = "(c|m|(da)...as|e{3})|.(ab)";
        std::string zz = "((<name>c)c||as|(esdd){3})|(ab)"; //
        std::string s = "(<name>c||as|e)j{4}j(<sdf>c||as|e)|s";//
        std::string dd =  "(abz|cc(<name>kbz)d|acb)";
        std::string hhp = "(namec{3}as?e)j{4}ja|(ame...cas|e?)";
        std::string hh = "(namec{3}as?e)j{4}ja|(ame...cas|e?)";//sd";
        std::string as = "(absdc|a)a(fb)?|ab{2}"; // хорошо минимизацию видно
        std::string asz = "((<name1>abz)|(<name>abzpk)|ab)";//
        std::string asp = "((<name1>abz)|(<name>a(bz)...pk)|ab|)";
        std::string aspp = "(<name1>abz)|(namea(bz)...pk)";
        std::string ak = "(abz|(<name>abz)d|ab)"; //
        //std::string df = "abcd";
        //auto it = df.begin();
        //auto it2 = it;
        //std::string nestr{it,it2}; второй итератор не включительно
        //std::cout << nestr;
        //std::cout << "1" << std::endl;
    // тесты для search - iter + captures
    /*
        std::string put_here;
        Regex myregex1{};
        myregex1.compile(dd);
        //myregex1.PrintCompiled();
        if(myregex1.search("bcsdg", put_here)) {
            std::cout << put_here << std::endl;
        }
        if(myregex1.search("afsdsdsddnaml",a, put_here)){
            std::cout << put_here << std::endl;
        }
        Captures capt1{};
        if(myregex1.search("afsdsdsddnaml",a, put_here, capt1)){ // перегрузка по индексации
            std::cout << put_here << std::endl;
            std::cout << capt1[std::string{"arr"}] << std::endl;
            std::cout << capt1[std::string{"b"}] << std::endl;
            std::cout << capt1[std::string{"c"}] << std::endl;
            for(auto it = capt1.begin(); it != capt1.end(); ++it){
                std::cout << " Name of group " <<it->first << " result " << it->second << std::endl;
            }
        }
        if(myregex1.search("aacckbzd",dd, put_here, capt1)){
            std::cout << put_here << std::endl;
            std::cout << capt1[std::string{"name"}] << std::endl;
        }
        if(myregex1.search("aacckkffkbzd",dd, put_here, capt1)){
            std::cout << put_here << std::endl;
            std::cout << capt1[std::string{"name"}] << std::endl;
        }
        if(myregex1.search("aaaaadadaaser",pk1, put_here)){
            std::cout << put_here << std::endl;
        }
        if(myregex1.search("aaaaadadaaser",pk, put_here)){
            std::cout << "1" << std::endl;
            std::cout << put_here << std::endl;
        } */
        //
    // тесты инверсия
    /*    std::string put_here;
        Regex myregex3{};
        myregex3.compile(asz);
        myregex3.inversion();
        //myregex3.PrintCompiled();
        std::cout << myregex3.create_regular_expression() << std::endl;
        myregex3.inversion(as);
        //myregex3.PrintCompiled();
        std::cout << myregex3.create_regular_expression() << std::endl;
        myregex3.inversion(dd);
        //myregex3.PrintCompiled();
        std::cout << myregex3.create_regular_expression() << std::endl;
        myregex3.inversion(aspp);
        std::cout << myregex3.create_regular_expression() << std::endl;*/
     //
     //тесты восстановление регулярного выражения
        Regex myregex4{};
        myregex4.compile(hh);
        //myregex4.PrintCompiled();
        std::cout << myregex4.create_regular_expression() << std::endl;
        myregex4.compile(pk); //
        std::cout << myregex4.create_regular_expression() << std::endl;
        myregex4.compile(dd);
        std::cout << myregex4.create_regular_expression() << std::endl;
        myregex4.compile(s);
        std::cout << myregex4.create_regular_expression() << std::endl;
        myregex4.compile(aspp);
        //myregex4.PrintCompiled();
        std::cout << myregex4.create_regular_expression() << std::endl;
     //
     // тесты dfa /nka /ast/ minimization
     // Ast myast{asz}; // вставляй без пробела строку
        //myast.ShowTree();
        //std::cout << "1" << std::endl;
        //NFA myauto{myast};
        //myauto.Myprint();
        //DFA mydfa{myauto};
        //mydfa.Myprint();
    //
    // тесты разность
        //Ast myast{asp}; // вставляй без пробела строку
        //NFA myauto{myast};
        //auto tester = std::make_shared<DFA>(myauto);
    /*    std::string test1 = "ab|b|cc";
        std::string test2 = "abc|ccd";
        Regex myregex4{};
        myregex4.compile(test1);
        Regex myregex5{};
        myregex5.compile(test2);
        auto myregex6 = myregex4.difference(myregex5);
        //myregex6.PrintCompiled();
        std::string test3 = "(<name1>ab)|dd";
        std::string test4 = "(<name2>a(<name3>b))c|dda";
        Regex myregex7{};
        myregex7.compile(test3);
        Regex myregex8{};
        myregex8.compile(test4);
        auto myregex9 = myregex7.difference(myregex8);
        //myregex9.PrintCompiled();

        std::string test5 = "(<name1>aaa)|dd";
        std::string test6 = "(<name2>a...)";
        Regex myregex10{};
        myregex10.compile(test5);
        Regex myregex11{};
        myregex11.compile(test6);
        auto myregex12 = myregex10.difference(myregex11);
        //myregex12.PrintCompiled();*/
        //
        //Regex myregex{};
        //myregex.compile(hh);
        //myregex.PrintCompiled();
        //myregex.inversion();//
        //myregex.PrintCompiled();
        //std::cout << myregex.create_regular_expression(); // asz прочекай
        //std::map<std::string , std::string> mmap;
        //std::string res = "";
        //myregex.search("adafcdssdabzdkkcsdsdazdf", mmap,res);
        //std::cout << res << std::endl;
    }
    catch(...){
        std::cout << "error";
    }
    return 0;
}
