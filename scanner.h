/**
  * scanner.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: header for scanner and Lexical analyzer
  *
  */

  #ifndef _SCANNER_H_
  #define _SCANNER_H_

  #include "strings.h"

  typedef enum {
    DEF,
    ELSE,
    IF,
    NONE,
    PASS,
    RETURN,
    WHILE,
  } keyword;

  typedef enum {
    PLUS, //+
    MINUS, //-
    TIMES, //*
    INT, //integer
    FLOAT, //float
    STR, //string
    DIVFLOAT, //úplné dělení do floatu
    DIV, //celočíselné dělení, očekává dva int
    LESS, //<
    GREATER, //>
    LESSEQ, //<=
    GREATEREQ, //>=
    EQ, //==
    NOTEQ, //!=
    EOL, //konec radku
    EOFTOKEN, //konec souboru
    LEFTBRACKET, // (
    RIGHTBRACKET, // )
    COMMA, // ,
    SEMICOLON, // ;
  } tokenType;

  typedef struct {
  	tokenType type; //type
  	tokenAttribute attribute; //value
  } token;

  typedef union {
    smartString *string; //string value
    keyword keyword; //uhh not sure
  } tokenAttribute;

  ////*    Here may be other functions such as opening source file etc    *////


  // Proly na ziskavanie tokenov
  token nextToken();

//  Exemplar token insertion  //
/*
  * token testToken;
  * smartString *s = malloc(sizeof(smartString));
  * stringInit(s);
  * stringAddChar(s,'+');
  * testToken.attribute.string = s;
  * testToken.type = PLUS;
*/



#endif
