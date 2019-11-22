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
  int *error = OK;

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

    //pokud nezacina statement keywordem, jedna se bud o chybu, nebo o expression
    if(tokenAct.type != KEYWORD){
      result = expression();
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      return result;
    }

    if(tokenAct.attribute.keyword == IF){ // IF----------------------------------
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      result = expression();

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != COLON){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      //musi nasledovat statement/y
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru

      do(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      } while;

      if(tokenAct.type != KEYWORD){
        return OK;
      }
      else if(tokenact.attribute.keyword != ELSE){
          return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != COLON){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      do(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      } while;

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != DEDENT){
        return PARSING_ERR;
      }
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    else if(tokenAct.attribute.keyword == WHILE){ // WHILE ---------------------------------
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      result = expression();

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != COLON){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      do(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      } while;

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != DEDENT){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    else if(tokenAct.attribute.keyword == PASS){ // PASS --------------------------------------
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    else if(tokenAct.attribute.keyword == RETURN){ // RETURN -------------------------------------
      
    }
    /*else if(tokenAct.attribute.keyword == DEF){
      result = function();
      return result;
    }*/
    else{ //pokud jsou to jine keywordy, tak se nejspis jedna o expression, za kterou nasleduje eof nebo eol
      result = expression();
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type == EOFTOKEN){
        return result;
      }
      else if(tokenAct.type != EOL){
        return PARSING_ERR;
      }
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      return result;
    }

    return OK;
  }

  int function(){
    int result;

    if(tokenAct.type != STRING) { //za def musi nasledovat identifikator
        return PARSING_ERR;
      }

      insertSymbolTable(tableFunc, tokenAct, FUNCTION); //vlozeni funkce do tabulky funkci

      //musi nasledovat '('
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru

      if(tokenAct.type != LEFTBRACKET){
        return PARSING_ERR;
      }

      //musi nasledovat identifikator
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru

      if(tokenAct.type != STR){
        return PARSING_ERR;
      }

      while(tokenAct != RIGHTBRACKET){
          //dalsi token musi byt ','
          tokenAct = getNextToken(error);
          if(*error != OK) return error; // zkoumani lexikalniho erroru

          if(tokenAct != COMMA){
            return PARSING_ERR;
          }

          //dalsi token musi byt identifikator
          tokenAct = getNextToken(error);
          if(*error != OK) return error; // zkoumani lexikalniho erroru

          if(tokenAct.type != STR){
            return PARSING_ERR;
          }
      }

      //musi nasledovat EOL -> INDENT -> statement
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      //musi nasledovat statement/y
      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru

      while(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      }

      tokenAct = getNextToken(error);
      if(*error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
  }

  // neterminal pro cely program(library)
  int program(){
    int result;
    while (token.type != EOFTOKEN) { // prochazi se cely program
      // muze se jednat bud o funkci, statement
      if(tokenAct.type == STR && token.attribute.keyword == DEF){
        tokenAct = getNextToken(error);
        if(*error != OK) return error; // zkoumani lexikalniho erroru
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
    if ((tokenAct = getNextToken(error)) == LEX_ERROR)
       // nastala chyba jiz pri nacteni prvniho lexemu
       result = LEX_ERROR;
    else
       result = program();
    strFree(&attr);
    return result;
  }


/* keywordy .. dedenty .. vkladani(search) do symtable*/
