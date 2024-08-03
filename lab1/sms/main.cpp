#include <iostream>
#include <fstream>
#include "labstr.h"
#include "NumAnalitics.h"
#include <chrono>
#include <random>
// бибилиотека statemap должна быть в кавычках

// не работает со множеством строк
using namespace std;
using namespace statemap;
int main(int argc, char *argv[]) {
    Labstr thisContext;
    int retcode = 0;
    if (argc < 2) {
        cerr << "No strings to check." << endl;
        retcode = 2;
    } else if (argc > 2) {
        cerr << "Only one argument is accepted." << endl;
        retcode = 3;
    } else {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файлы" << std::endl;
            return 1;
        }
        std::string line;
        proj::NumAnalitics store{};
        //std::string a = "fax +79018175070,+79018175070,+79018175071";
        while (std::getline(file, line)) {
            if (file.eof()) {
            } else {
                line.erase(line.size() - 1);// удаляем /n
            }
            std::cout << line << std::endl;
            try {
                if (thisContext.CheckString(line, store) == false) {
                    cout << "not acceptable." << endl;
                    retcode = 1;
                } else {
                    cout << "acceptable." << endl;
                }
            }
            catch (const SmcException &smcex) {

                cout << "not acceptable - "
                     << smcex.what()
                     << '.'
                     << endl;

                retcode = 1;
            }
        }
        //std::string a = "fax +79018175070,+79018175070,+79018175071";
        //thisContext.CheckString(a, store);
        // вставка для измерения времени
        std::mt19937 eng;
        char digit;
        char u = '1';
        unsigned int mod;
        std::string genstr = "fax ";
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
        std::chrono::time_point start = std::chrono::steady_clock::now();
        thisContext.CheckString(genstr, store);
        thisContext.CheckString(genstr2, store);
        thisContext.CheckString(genstr3, store);
        std::chrono::time_point end =  std::chrono::steady_clock::now();
        std::cout  << "sms time " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

        //
        //store.print();
        file.close();
    }
    return retcode;
}

/*
std::chrono::time_point start = std::chrono::steady_clock::now();
TheNearestExcursionMa(table, ad, ad.getDate());
std::chrono::time_point end =  std::chrono::steady_clock::now();
std::cout  << " Function with many threads took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
std::chrono::time_point sstart = std::chrono::steady_clock::now();
TheNearestExcursion(table, ad, ad.getDate());
std::chrono::time_point eend =  std::chrono::steady_clock::now();
std::cout  << " Function with 1 thread took " << std::chrono::duration_cast<std::chrono::milliseconds>(eend - sstart).count() << std::endl;
*/
