/**
  * scanner.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: scanner and Lexical analyzer
  *
  */

#include <malloc.h>
#include "scanner.h"
#include "stack.h"

#define STATE_START 100

#define STATE_F2 300      //Robíme číslo
#define STATE_F3 301      //Číslo bude float
#define STATE_F4 302      //Koniec čísla
#define STATE_P1 303      //Prechod pri '.' znaku floatu
#define STATE_P2 304      //Bolo použité e/E
#define STATE_P3 305      //Precho pri '+' a '-' znaku pri exp

#define STATE_F22 400     //Koncový stav literálu
#define STATE_P10 401     //Zápis charov
#define STATE_P11 402     //Možná escape sekvencia alebo hex hodnota
#define STATE_P12 403     //Potvrdenie hex hodnoty
#define STATE_P13 404     //Hex hodnota





FILE *f;

void setFile(char* sourceFile){
    f = fopen (sourceFile, "r");
}

void resetToken(){
  rewind(f);
}

token nextToken(int *error, tStack *stack, int doIndent) {

    token Token;

    int tmpNum = 0;
    int counter = 0;
    char hexvalue[3] = {0,};



    char c, tmp;



    smartString *s = malloc(sizeof(smartString));
    if (s == NULL) {
        *error = INTERN_ERR;
        return Token;
    }
    stringInit(s);
    //c = getc(f)

    int state = STATE_START;
    while (c = getc(f), c != EOF) {
/////////////check prepisovanie c s podmienkou while


        switch (c) {
            // SINGULAR //

            case ' ':
                continue;

            case '+':
                stringAddChar(s, '+');
                Token.attribute.string = s;
                Token.type = PLUS;
                return Token;

            case '-':
                stringAddChar(s, '-');
                Token.attribute.string = s;
                Token.type = MINUS;
                return Token;

            case '*':
                stringAddChar(s, '*');
                Token.attribute.string = s;
                Token.type = TIMES;
                return Token;

            case '(':
                stringAddChar(s, '(');
                Token.attribute.string = s;
                Token.type = LEFTBRACKET;
                return Token;

            case ')':
                stringAddChar(s, ')');
                Token.attribute.string = s;
                Token.type = RIGHTBRACKET;
                return Token;

            case ':':
                stringAddChar(s, ':');
                Token.attribute.string = s;
                Token.type = COLON;
                return Token;

            case ',':
                stringAddChar(s, ',');
                Token.attribute.string = s;
                Token.type = COMMA;
                return Token;
                // MULTIPLE //
            case '=':
                if (c = getc(f), c == '=') {
                    stringAddChar(s, '=');
                    stringAddChar(s, '=');
                    Token.attribute.string = s;
                    Token.type = EQ;
                    return Token;
                } else {
                    stringAddChar(s, '=');
                    Token.attribute.string = s;
                    Token.type = ASSIGN;
                    ungetc(c, f);
                }

            case '>':
                if (c = getc(f), c == '=') {
                    stringAddChar(s, '>');
                    stringAddChar(s, '=');
                    Token.attribute.string = s;
                    Token.type = GREATEREQ;
                    return Token;
                } else {
                    stringAddChar(s, '>');
                    Token.attribute.string = s;
                    Token.type = GREATER;
                    ungetc(c, f);
                    return Token;
                }

            case '<':
                if (c = getc(f), c == '=') {
                    stringAddChar(s, '<');
                    stringAddChar(s, '=');
                    Token.attribute.string = s;
                    Token.type = LESSEQ;
                    return Token;
                } else {
                    stringAddChar(s, '<');
                    Token.attribute.string = s;

                    Token.type = LESS;
                    ungetc(c, f);
                    return Token;
                }

            case '!':
                if (c = getc(f), c == '=') {
                    stringAddChar(s, '!');
                    stringAddChar(s, '=');
                    Token.attribute.string = s;
                    Token.type = NOTEQ;
                    return Token;
                } else {
                    *error = LEXICAL_ERR;
                    return Token;
                }

            case '"':
                if (c = getc(f), c != '"') {
                    *error = LEXICAL_ERR;
                    return Token;
                }

                if (c = getc(f), c != '"') {
                    *error = LEXICAL_ERR;
                    return Token;
                }
                Token.type = DOCCOM;

                while (c = getc(f)) {
                    if (c == '"') {
                        if (c = getc(f), c == '"') {
                            if (c = getc(f), c == '"') {
                                break;
                            } else {
                                stringAddChar(s, '"');
                                stringAddChar(s, '"');
                            }
                        } else {
                            stringAddChar(s, '"');
                        }
                    }
                    stringAddChar(s, c);
                }
                Token.attribute.string = s;
                return Token;

            case '#':
                while ((c = getc(f), c != '\n') || (c = getc(f), c != EOF))
                    c = getc(f);
                break;

            case '\n':

                if (doIndent == 0){
                    Token.type = EOL;
                    ungetc(c,f);
                    return Token;
                }

                tmpNum = 0, counter = 0;

                while (c = getc(f), c == ' ' || c == '\n' || c == EOF) {
                    counter++;
                    if (c == '\n') { //If the line is empty start again
                        counter = 0;
                    }
                    if (c == EOF) {
                        Token.type = EOFTOKEN;
                        return Token;
                    }

                }
               /* if (counter == 0){ //Prazdny indent čiže nič
                    Token.type = BROKEN;
                    ungetc(c ,f);
                    return Token;
                }*/

                ungetc(c, f); //Vrati znak buduceho tokenu

                if (stackEmpty(stack)) { //Creates Indent token on empty stack
                    stackPush(stack, counter);

                    Token.attribute.INT = counter;
                    Token.type = INDENT;

                    return Token;
                }

                stackTop(stack, &tmpNum);
                if (counter > tmpNum) { //Creates new Indent if counter is higher
                    stackPush(stack, counter);
                    Token.attribute.INT = counter;
                    Token.type = INDENT;
                    return Token;
                } else if (counter == tmpNum){  //Indents are same, returns broken token because has to return smth
                    Token.type = BROKEN;
                    return Token;
                }
                else {
                    while (counter < tmpNum) {
                        if (stackEmpty(stack)) {
                            *error = LEXICAL_ERR;
                            return Token;
                        }
                        stackPop(stack);
                        stackTop(stack, &tmpNum);
                        if (tmpNum < counter){
                            *error = LEXICAL_ERR;
                            return Token;
                        }
                    }
                    Token.attribute.INT = counter;  ////Consult this
                    Token.type = DEDENT;
                    stackPush(stack, counter); ////vrat c
                    return Token;
                }


            default:
                if (isalpha(c) || c == '_') { //Robíme basic string
                    Token.type = STR;

                    while (1) {
                        if (!(isalpha(c)) || !(isdigit(c) || (c != '_'))) {
                            break;
                        }
                        stringAddChar(s, c);
                        c = getc(f);
                    }

                    ungetc(c, f);
                    int i = 0;
                    if ((i = stringIsKeyword(s)) != -1) {
                        Token.attribute.keyword = i;
                        Token.type = KEYWORD;
                    } else
                        Token.attribute.string = s;

                    return Token;
                }

                if (isdigit(c)) { //Robíme číslo
                    stringAddChar(s, c);
                    int tmpNum = c - '0'; //lebo ascii hodnota
                    c = getc(f);
                    if (tmpNum == 0 && (c != '.' && c != 'e' && c != 'E' && isdigit(c))) { //Spravnost zaciatku cisla Nulou
                        *error = LEXICAL_ERR;
                        return Token;
                    }



                    state = STATE_F2;
                    int isINTorFLT = 0; //0 is for INT, 1 is for FLOAT
                    char *ptr; //pri prevode
                    while (1) {
                        switch (state) {
                            case (STATE_F2): //Začiatočný state čísla
                                if (c == '.') { //Bude float
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P1;
                                } else if (c == 'E' || c == 'e') { //Bude Exp
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P2;
                                } else if (isdigit(c)) { //Bude cislo
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_F2;
                                    break;
                                } else if (isspace(c) || c == '\n' || c == EOF) {
                                    Token.attribute.INT = strtod(s->string, &ptr);
                                    Token.type = INT;
                                    state = STATE_START;
                                    ungetc(c, f);
                                    return Token;
                                } else {
                                    ungetc(c, f);
                                    return Token;
                                }


                            case (STATE_P1): //Je float
                                if (isalnum(c)) { //Musí nasledovať číslo
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_F3;
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }
                                break;

                            case (STATE_F3): //Je float v tvare (example) 132.1_
                                isINTorFLT = 1; ///Kontrola že je TYP FLOATEXP
                                if (c == 'E' || c == 'e') { //Bude 132.1e
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P2;
                                } else if (isalnum(c)) { //Bude 132.12
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_F3; //Vráti sa tu
                                } else if (isspace(c) || c == '\n' || c == EOF) {
                                    Token.attribute.FLOAT = strtod(s->string, &ptr);
                                    Token.type = FLOAT;
                                    state = STATE_START;
                                    return Token; //Koniec float čísla
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }

                            case (STATE_P2):
                                if (isalnum(c)) {
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_F4;
                                } else if (c == '+' || c == '-') {
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P3;
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }
                                break;

                            case (STATE_P3):
                                if (isalnum(c)) {
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_F4;
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }
                                break;

                            case (STATE_F4):
                                if (isalnum(c)) {
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_F4;
                                } else {
                                    if (isINTorFLT == 1) {
                                        Token.attribute.FLOAT = strtod(s->string, &ptr);
                                        Token.type = FLOAT;
                                        isINTorFLT = 0;
                                        return Token; //Koniec float
                                    } else {
                                        Token.attribute.INT = strtod(s->string, &ptr);
                                        Token.type = INT;
                                        return Token; //Koniec integer
                                    }
                                    state = STATE_START;
                                }
                        }

                        //break; //Vraciam sa do switch (c)
                    }
                }

                if (c == '\'') { // Robíme literál
                    stringAddChar(s, c);
                    c = getc(f);
                    state = STATE_P10;

                    while (1) {
                        if (c == EOF) {
                            *error = LEXICAL_ERR;
                            return Token;
                        }
                        switch (state) {
                            case (STATE_P10):
                                if (c > 31 && c != 92 && c != 39) { // '\'' && '\\' && '\,' //normalny znak
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P10;
                                } else if (c == 39) { //Apostrof teda koniec stringu
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_F22;
                                } else if (c == 92) { // Backslash teda escape seq
                                    c = getc(f);
                                    state = STATE_P11;
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }
                                continue;

                            case (STATE_P11): //Riešime či escape alebo nah
                                if (c > 31 && c != 92 && c != 39 && c != 44 && c != 'n' && c != 't') {//nebola
                                    stringAddChar(s, '\\');
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P10;
                                } else if (c == 92 || c == 39 || c == 34) {//  _/_'_"_
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P10;
                                } else if (c == 'n') { // Spraví EOL
                                    stringAddChar(s, '\n'); /////////////////hmmm check?
                                    c = getc(f);
                                    state = STATE_P10;
                                } else if (c == 't') { // Spraví TAB
                                    stringAddChar(s, '\t'); /////////////////hmmm check?
                                    c = getc(f);
                                    state = STATE_P10;
                                } else if (c == 'x') { //Bude robiť HEX
                                    c = getc(f);
                                    state = STATE_P12;
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }
                                continue;

                            case (STATE_P12): //Riešime prvú hex val
                                if ((c >= 48 && c <= 57) || (c >= 65 && c <= 70) ||
                                    (c >= 97 && c >= 102)) { // 0..9 || A..F || a..f
                                    hexvalue[0] = c;
                                    c = getc(f);
                                    state = STATE_P13;
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }
                                continue;

                            case (STATE_P13): //Riešime druhú hex val
                                if ((c >= 48 && c <= 57) || (c >= 65 && c <= 70) ||
                                    (c >= 97 && c >= 102)) { // 0..9 || A..F || a..f
                                    hexvalue[1] = c;
                                    int decvalue = (int) strtol(hexvalue, NULL,
                                                                16); //convertne hexvalue na int v decimáloch
                                    char tmp[2];
                                    sprintf(tmp, "%c", decvalue); //convertnem decvalue na ASCII znak
                                    c = *tmp;
                                    stringAddChar(s, c);
                                    c = getc(f);
                                    state = STATE_P10;
                                } else {
                                    *error = LEXICAL_ERR;
                                    return Token;
                                }
                                continue;

                            case (STATE_F22): //Koniec
                                Token.attribute.string = s;
                                Token.type = LITERAL;
                                state = STATE_START;
                                //c = getc(f); //Idk prečo to tu bolo..?
                                return Token;
                                break;
                        }
                        break;
                    }
                }
        }
    }
    Token.type = EOFTOKEN;
    return Token;
}
