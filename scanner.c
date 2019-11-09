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
        Token.attribute.string = s;

        Token.type = PLUS;
        break;

      case '-':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'-');
        Token.attribute.string = s;

        Token.type = MINUS;
        break;

      case '*':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'*');
        Token.attribute.string = s;

        Token.type = TIMES;
        break;

      case '(':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'(');
        Token.attribute.string = s;

        Token.type = LEFTBRACKET;
        break;

      case ')':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,')');
        Token.attribute.string = s;

        Token.type = RIGHTBRACKET;
        break;

      case ';':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,';');
        Token.attribute.string = s;

        Token.type = SEMICOLON;
        break;

      case ':':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,':');
        Token.attribute.string = s;

        Token.type = COLON;
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
          Token.attribute.string = s;

          Token.type = EQ;
          break;
        }
        else {
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'=');
          Token.attribute.string = s;

          Token.type = ASSIGN;
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
          Token.attribute.string = s;

          Token.type = GREATEREQ;
          break;
        }
        else {
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'>');
          Token.attribute.string = s;

          Token.type = GREATER;
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
            Token.attribute.string = s;

            Token.type = LESSEQ;
            break;
          }
          else {
            smartString *s = malloc(sizeof(smartString));
            if (s == NULL){
                return INTERN_ERR;
            }
            stringInit(s);
            stringAddChar(s,'<');
            Token.attribute.string = s;

            Token.type = LESS;
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
        Token.attribute.string = s;

        Token.type = NOTEQ;
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





      default:
      if (isalpha(c) || c == '_'){
        smartString *s = malloc(sizeof(smartString));
        stringInit(s);

        Token.attribute.string = STR;
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
