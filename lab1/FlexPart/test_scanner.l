%option c++
%option noyywrap
%x SMS TELORFAX EATSTR FPARS
%{
#include <sstream>
#include <fstream>
#include <iostream>
#include "NumAnalitics.h"
//<<EOF>> return 0;
int flag = 0;
%}
%%

<INITIAL>{
^((?:tel|fax)[" "\t]) {BEGIN(TELORFAX); return 1;}
^(sms[" "\t]) {BEGIN(SMS); return 1;}
. {BEGIN(EATSTR);}
}
<TELORFAX>{
<<EOF>> {BEGIN(INITIAL); return 0;}
\+[0-9]{11} { flag = 1; return 1; }
,/\+
. {flag = 0; BEGIN(EATSTR);}
}
<SMS>{
<<EOF>> {BEGIN(INITIAL); return 0;}
\+[0-9]{11} { flag = 1; return 1; }
,/\+
[" "\t][0-9a-zA-Z%.,!?]{1,64} { flag = 1; BEGIN(EATSTR);}
. {flag = 0; BEGIN(EATSTR);}
}
<EATSTR>{
<<EOF>> { BEGIN(INITIAL); return 0;}
. { flag = 0;}
}
%%
// вверху был использован прогностический оператор
// якорь конца почему-то не работает
namespace proj{
void checkstringf(const char *str, proj::NumAnalitics &store){
	int token = 0;
	std::ifstream file(str);
	if (!file.is_open()){
         std::cout << "Не удалось открыть файлы" << std::endl;
    }
    std::vector<std::string> bufstr;
    std::string line;
    std::stringstream ss;
    yyFlexLexer ftp;
    ftp.switch_streams(ss, std::cout);
    while(std::getline(file, line)){
         if (file.eof()) {
         } else {
             line.erase(line.size() - 1);// удаляем /n
         }
         ss << line;
	    if(ftp.yylex()){
            do{
                    token = ftp.yylex();
                    if (token == 1) {
                            bufstr.push_back(ftp.YYText());
                    }
            }while(token);
            if(flag == 1){
                std::cout << "the truth" << std::endl;
                while(bufstr.size()){
                    store.add(bufstr.back());
                    bufstr.pop_back();
                }
            }
            else{
                std::cout << "the falsehood" << std::endl;
                while(bufstr.size()){
                     bufstr.pop_back();
                }
            }
        }
        else{
            std::cout << "the falsehood" << std::endl;
        }
    }
    file.close();
}
}