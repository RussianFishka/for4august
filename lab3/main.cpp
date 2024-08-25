#include <stdio.h>
//#include "lexer.h"
#include "bisonpart.tab.h"
//#include "lexer.h"

extern FILE *yyin;

int main(int argc, char **argv) {
    //printf("start!!");
    fflush(stdout);
    if (argc > 1) {
        //printf("start!!");
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
        //printf("start!!");
    }
    yyparse();
    return 0;
}
/*int main(int argc, char **argv) {
    typedef void* yyscan_t;
    yyscan_t scanner;
    yylex_init(&scanner);

    // Открытие файла для чтения
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("fopen");
        return 1;
    }
    yyset_in(input, scanner);

    // Вызов yyparse с параметром scanner
    int result = yyparse(scanner);

    // Освобождение ресурсов
    yylex_destroy(scanner);
    fclose(input);

    return result;
}*/
/*
int main(int argc, char **argv) {
    yyscan_t scanner;
    yylex_init(&scanner);

    // Открытие файла для чтения
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("fopen");
        return 1;
    }
    yyset_in(input, scanner);

    // Вызов yyparse с параметрами
    int result = yyparse(scanner);

    // Освобождение ресурсов
    yylex_destroy(scanner);
    fclose(input);

    return result;
}*/