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
  #include "ctype.h"


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
    DIVFLT, //dělení floatov
    DIVINT, //dělení integerov
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
    COLON, // :
    ASSIGN, // =
  } tokenType;

  typedef struct {
  	tokenType type; //type
  	tokenAttribute attribute; //value
  } token;

  typedef union {
    keyword keyword; //uhh not sure
    smartString *string; //string value
    int INT;
    double FLOAT;
  } tokenAttribute;

  ////*    Here may be other functions such as opening source file etc    *////


  // Proly na ziskavanie tokenov
  token nextToken();

//  Exemplar token insertion  //
/*
  * token Token;
  * smartString *s = malloc(sizeof(smartString));
  * stringInit(s);
  * stringAddChar(s,'+');
  * Token.attribute.string = s;
  * Token.type = PLUS;
*/



#endif
