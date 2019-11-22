/**
  * parser.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: implementace parseru.. 2. cast celeho compileru
  *        vstupem jsou tokeny
  *
  */

  #include "parser.h"


  symbolTable *tableVar;// globalni promenna uchovavajici tabulku symbolu
  symbolTable *tableFunc;// globalni promenna uchovavajici tabulku funkci
  tDLList *list; // globalni promenna uchovavajici seznam instrukci
  token tokenAct;          // globalni promenna, ve ktere bude ulozen aktualni token
  smartString attr;        // globalni promenna, ve ktere bude ulozen atribut tokenu

  int counterVar = 1;

  void generateVariable(smartString *var)
  // generuje jedinecne nazvy identifikatoru
  // nazev se sklada ze znaku $ nasledovanym cislem
  // postupne se tu generuji prirozena cisla a do nazvu promenne se ukladaji
  // v reverzovanem poradi - na funkcnost to nema vliv, ale je jednodussi implementace

  {
    stringClear(var);
    stringAddChar(var, '$');
    int i;
    i = counterVar;
    while (i != 0)
    {
      stringAddChar(var, (char)(i % 10 + '0'));
      i = i / 10;
    }
    counterVar ++;
  }

  void generateInstruction(int instType, void *addr1, void *addr2, void *addr3)
  // vlozi novou instrukci do seznamu instrukci
  {
     tInstr I;
     I.instType = instType;
     I.addr1 = addr1;
     I.addr2 = addr2;
     I.addr3 = addr3;
     DLInsertLast(list, I);
  }

  // ==================================================================
  // jednotlive funkce odpovidajici jednotlivym nonterminalum gramatiky
  // ==================================================================

  // pomocna funkce na preskakovani prazdnych radku

  int statement(){
    int result;

    if(tokenAct.type != STR){
      result = expression();
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      return result;
    }

    if(tokenAct.attribute.keyword == IF){
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      result = expression();

      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      if(tokenAct.type != COLON){
        return PARSING_ERR;
      }

      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      //musi nasledovat statement/y
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru

      while(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      }

      if(tokenAct.type != KEYWORD){

      }
    }
    else if(tokenAct.attribute.keyword == WHILE){

    }
    else if(tokenAct.attribute.keyword == PASS){

    }
    else if(tokenAct.attribute.keyword == RETURN){

    }
    else{
      result = expression();
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      return result;
    }

    return OK;
  }

  int function(){
    int result;

    if(tokenAct.type == STRING) { //za def musi nasledovat identifikator
      if(tokenAct.attribute.keyword == DEF    ||
         tokenAct.attribute.keyword == ELSE   ||
         tokenAct.attribute.keyword == IF     ||
         tokenAct.attribute.keyword == NONE   ||
         tokenAct.attribute.keyword == PASS   ||
         tokenAct.attribute.keyword == RETURN ||
         tokenAct.attribute.keyword == WHILE  ){ //identifikator nesmi byt keyword
          return PARSING_ERR;
        }
      }
      else{
        return PARSING_ERR;
      }

      insertSymbolTable(tableFunc, tokenAct, FUNCTION); //vlozeni funkce do tabulky funkci

      //musi nasledovat '('
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru

      if(tokenAct.type != LEFTBRACKET){
        return PARSING_ERR;
      }

      //musi nasledovat identifikator
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru

      if(tokenAct.type != STR){
        return PARSING_ERR;
      }
      else if(tokenAct.attribute.keyword == DEF    ||
              tokenAct.attribute.keyword == ELSE   ||
              tokenAct.attribute.keyword == IF     ||
              tokenAct.attribute.keyword == NONE   ||
              tokenAct.attribute.keyword == PASS   ||
              tokenAct.attribute.keyword == RETURN ||
              tokenAct.attribute.keyword == WHILE  ){ //identifikator nesmi byt keyword
                return PARSING_ERR;
      }

      while(tokenAct != RIGHTBRACKET){
          //dalsi token musi byt ','
          tokenAct = getNextToken();
          if() return LEXICAL_ERR; // zkoumani lexikalniho erroru

          if(tokenAct != COMMA){
            return PARSING_ERR;
          }

          //dalsi token musi byt identifikator
          tokenAct = getNextToken();
          if() return LEXICAL_ERR; // zkoumani lexikalniho erroru

          if(tokenAct.type != STR){
            return PARSING_ERR;
          }
          else if(tokenAct.attribute.keyword == DEF    ||
                  tokenAct.attribute.keyword == ELSE   ||
                  tokenAct.attribute.keyword == IF     ||
                  tokenAct.attribute.keyword == NONE   ||
                  tokenAct.attribute.keyword == PASS   ||
                  tokenAct.attribute.keyword == RETURN ||
                  tokenAct.attribute.keyword == WHILE  ){ //identifikator nesmi byt keyword
                    return PARSING_ERR;
          }
      }

      //musi nasledovat EOL -> INDENT -> statement
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      //musi nasledovat statement/y
      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru

      while(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      }

      tokenAct = getNextToken();
      if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
  }

  // neterminal pro cely program(library)
  int program(){
    int result;
    while (token.type != EOFTOKEN) { // prochazi se cely program
      // muze se jednat bud o funkci, statement
      if(tokenAct.type == STR && token.attribute.keyword == DEF){
        tokenAct = getNextToken();
        if() return LEXICAL_ERR; // zkoumani lexikalniho erroru
        result = function();
      }
      else{
        result = statement();
      }
    }
  }



  int parse(symbolTable *ST, tDLList *instrList)
  {
    int result;
    table = ST;
    list = instrList;
    strInit(&attr);
    if ((tokenAct = getNextToken(&attr)) == LEX_ERROR)
       // nastala chyba jiz pri nacteni prvniho lexemu
       result = LEX_ERROR;
    else
       result = program();
    strFree(&attr);
    return result;
  }


/* keywordy .. dedenty .. vkladani(search) do symtable*/
