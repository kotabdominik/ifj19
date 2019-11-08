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

#include "scanner.h"





 FILE *SourceFile;
 //smartString *s = malloc(sizeof(smartString));


token nextToken() {
  token Token;

  char c;

  while(){
    smartString *s = malloc(sizeof(smartString));
    if (smartString == NULL){

    }
    c = getchar()
    switch (c) {

      //TODO
      case ',':
        break;

      case '+':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'+');
        testToken.attribute.string = s;

        testToken.type = PLUS;
        break;

      case '-':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'-');
        testToken.attribute.string = s;

        testToken.type = MINUS;
        break;

      case '*':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'*');
        testToken.attribute.string = s;

        testToken.type = TIMES;
        break;

      case '/':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'/');
        testToken.attribute.string = s;

        testToken.type = DIV;
        break;
      //TODO
/*      case '<':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'<');
        testToken.attribute.string = s;

        testToken.type = LESS;
        break;
      //TODO
      case '>':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'>');
        testToken.attribute.string = s;

        testToken.type = GREATER;
        break;*/

      case '(':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'(');
        testToken.attribute.string = s;

        testToken.type = LEFTBRACKET;
        break;

      case ')':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,')');
        testToken.attribute.string = s;

        testToken.type = RIGHTBRACKET;
        break;

      case ';':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,';');
        testToken.attribute.string = s;

        testToken.type = SEMICOLON;
        break;
    }

      
  }

}
