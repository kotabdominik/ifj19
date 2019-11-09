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

  char c,tmp;

  c = getchar()
  while((c = getchar() != EOF){
    smartString *s = malloc(sizeof(smartString)); //check
    if (smartString == NULL){

    }
    switch (c) {
                  // SINGULAR //
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

      case ':':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,':');
        testToken.attribute.string = s;

        testToken.type = COLON;
        break;
                  // MULTIPLE //
      case '=':

        c = getchar();
        if (c == '='){
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'=');
          stringAddChar(s,'=');
          testToken.attribute.string = s;

          testToken.type = EQ;
          break;
        }
        else {
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'=');
          testToken.attribute.string = s;

          testToken.type = ASSIGN;
          continue;
        }

      case '>':
        c = getchar();
        if (c == '='){
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'>');
          stringAddChar(s,'=');
          testToken.attribute.string = s;

          testToken.type = GREATEREQ;
          break;
        }
        else {
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'>');
          testToken.attribute.string = s;

          testToken.type = GREATER;
          continue;
        }

      case '<':
          c = getchar();
          if (c == '='){
            smartString *s = malloc(sizeof(smartString));
            if (s == NULL){
                return INTERN_ERR;
            }
            stringInit(s);
            stringAddChar(s,'<');
            stringAddChar(s,'=');
            testToken.attribute.string = s;

            testToken.type = LESSEQ;
            break;
          }
          else {
            smartString *s = malloc(sizeof(smartString));
            if (s == NULL){
                return INTERN_ERR;
            }
            stringInit(s);
            stringAddChar(s,'<');
            testToken.attribute.string = s;

            testToken.type = LESS;
            continue;
          }

      case '!':
      c = getchar();
      if (c == '='){
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'!');
        stringAddChar(s,'=');
        testToken.attribute.string = s;

        testToken.type = NOTEQ;
        break;
      }
      else {
        return LEXICAL_ERR;
      }

      case '"':
        if ((c = getchar) != '"')
          return LEXICAL_ERR;
        if ((c = getchar) != '"')
          return LEXICAL_ERR;
        while (1){
          c = getchar();
          if ((c = getchar) != '"')
            if ((c = getchar) != '"')
              if ((c = getchar) != '"')
                break;
        }
        break;

      case '#':
         while ((c = getchar()) != EOL || c = getchar()) != EOF)
          c = getchar();
         break;

      case EOL:
        c = getchar();
        continue;

      if (isalpha(c) || c == '_'){
        smartString *s = malloc(sizeof(smartString));
        stringInit(s);

        testToken.attribute.string = STR;
        if (s == NULL){
            return INTERN_ERR;
        }

        while(1){
          if ( !(isalpha(c)) || !(isalnum(c) || (c != '_') ){
            continue;
          }
          stringAddChar(s,c);
          c = getchar();
        }
      }




    }




  }

}
