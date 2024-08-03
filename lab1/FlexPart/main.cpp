#include <iostream>
#include "NumAnalitics.h"
#include <string>
#include <fstream>
#include <chrono>
#include <random>
int main(int argc, char * argv[]) {
    std::string str;
    proj::NumAnalitics store{};
    //std::getline(std::cin,str);
    proj::checkstringf(argv[1],store);
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
    // generator + time
    // надо записать инфу в файл а потом его скормить
    std::mt19937 eng;
    char digit;
    char u = '1';
    unsigned int mod;
    std::string genstr = "sms ";
    for (int i = 0; 10000 > i; i++) {
        genstr += '+';
        for (int k = 0; k < 11; k++) {
            mod = eng();
            digit = u + (mod % 9);
            genstr += digit;
        }
        genstr += ',';
    }
    genstr.erase(genstr.size() - 1);
    genstr += " ssd";
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
    std::ofstream file("output.txt");

    if (file.is_open()) {
        file << genstr;
        file << genstr2;
        file << genstr3;
        file.close();
        std::cout << "String successfully written to file." << std::endl;
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }
    std::chrono::time_point start = std::chrono::steady_clock::now();
    const char *text = "output.txt";
    proj::checkstringf(text,store);
    std::chrono::time_point end =  std::chrono::steady_clock::now();
    std::cout  << "flex time " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    return 0;
}