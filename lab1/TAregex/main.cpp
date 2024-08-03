#include <iostream>
#include "myregforta.h"
#include <string>
#include <chrono>
#include <random>
int main() {
    std::string str;
    proj::NumAnalitics store{};
    std::getline(std::cin,str);
    checkstring(str,store);
    store.print();
    //std::getline(std::cin,str);
   // checkstring(str,store);
  //  std::getline(std::cin,str);
 //   checkstring(str,store);
 //   std::getline(std::cin,str);
 //   checkstring(str,store);
 //   std::getline(std::cin,str);
 //   checkstring(str,store);
 //   std::getline(std::cin,str);
 //   checkstring(str,store);
    std::mt19937 eng;
    char digit;
    char u = '1';
    unsigned int mod;
    std::string genstr1 = "sms "; // с концовкой
    for (int i = 0; 5000 > i; i++) {
        genstr1 += '+';
        for (int k = 0; k < 11; k++) {
            mod = eng();
            digit = u + (mod % 9);
            genstr1 += digit;
        }
        genstr1 += ',';
    }
    genstr1.erase(genstr1.size() - 1);
    genstr1 += " sdd";
    std::string genstr2 = "sms "; // без концовки
    for (int i = 0; 5000 > i; i++) {
        genstr2 += '+';
        for (int k = 0; k < 11; k++) {
            mod = eng();
            digit = u + (mod % 9);
            genstr2 += digit;
        }
        genstr2 += ',';
    }
    genstr2.erase(genstr2.size() - 1);
    std::string genstr3 = "tel "; // с поломкой в середине
    for (int i = 0; 2500 > i; i++) {
        genstr3 += '+';
        for (int k = 0; k < 11; k++) {
            mod = eng();
            digit = u + (mod % 9);
            genstr3 += digit;
        }
        genstr3 += ',';
    }
    genstr3 += "sddsffd";
    for (int i = 0; 2500 > i; i++) {
        genstr3 += '+';
        for (int k = 0; k < 11; k++) {
            mod = eng();
            digit = u + (mod % 9);
            genstr3 += digit;
        }
        genstr3 += ',';
    }
    genstr3.erase(genstr3.size() - 1);
    std::chrono::time_point start = std::chrono::steady_clock::now();
    checkstring(genstr1,store);
    checkstring(genstr2,store);
    checkstring(genstr3,store);
    std::chrono::time_point end =  std::chrono::steady_clock::now();
    std::cout  << "regex time " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    return 0;
}
