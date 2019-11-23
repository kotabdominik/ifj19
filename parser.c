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


  //symbolTable *tableVar;// globalni promenna uchovavajici tabulku symbolu
  //symbolTable *tableFunc;// globalni promenna uchovavajici tabulku funkci
  //tDLList *list; // globalni promenna uchovavajici seznam instrukci
  token tokenAct;          // globalni promenna, ve ktere bude ulozen aktualni token
  //smartString attr;        // globalni promenna, ve ktere bude ulozen atribut tokenu
  int error = OK;

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
     //DLInsertLast(list, I); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return result;
    }

    if(tokenAct.attribute.keyword == IF){ // IF----------------------------------
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      result = expression();

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != COLON){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      //musi nasledovat statement/y
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru

      do{
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      } while(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN);

      if(tokenAct.type != KEYWORD){
        return OK;
      }
      else if(tokenAct.attribute.keyword != ELSE){
          return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != COLON){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      do{
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      } while(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN);

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != DEDENT){
        return PARSING_ERR;
      }
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    else if(tokenAct.attribute.keyword == WHILE){ // WHILE ---------------------------------
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      result = expression();

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != COLON){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      do{
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      } while(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN);

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != DEDENT){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    else if(tokenAct.attribute.keyword == PASS){ // PASS --------------------------------------
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    else if(tokenAct.attribute.keyword == RETURN){ // RETURN -------------------------------------
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      result = expression();
      if(result != OK) return result;

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    /*else if(tokenAct.attribute.keyword == DEF){
      result = function();
      return result;
    }*/
    else{ //pokud jsou to jine keywordy, tak se nejspis jedna o expression, za kterou nasleduje eof nebo eol
      result = expression();
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type == EOFTOKEN){
        return result;
      }
      else if(tokenAct.type != EOL){
        return PARSING_ERR;
      }
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return result;
    }

    return OK;
  }

  int function(){
    int result;

    if(tokenAct.type != STR) { //za def musi nasledovat identifikator
        return PARSING_ERR;
      }

      //insertSymbolTable(tableFunc, tokenAct, FUNCTION); //vlozeni funkce do tabulky funkci

      //musi nasledovat '('
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru

      if(tokenAct.type != LEFTBRACKET){
        return PARSING_ERR;
      }

      //musi nasledovat identifikator
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru

      if(tokenAct.type != STR){
        return PARSING_ERR;
      }

      while(tokenAct.type != RIGHTBRACKET){
          //dalsi token musi byt ','
          tokenAct = nextToken(&error);
          if(error != OK) return error; // zkoumani lexikalniho erroru

          if(tokenAct.type != COMMA){
            return PARSING_ERR;
          }

          //dalsi token musi byt identifikator
          tokenAct = nextToken(&error);
          if(error != OK) return error; // zkoumani lexikalniho erroru

          if(tokenAct.type != STR){
            return PARSING_ERR;
          }
      }

      //musi nasledovat EOL -> INDENT -> statement
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != EOL){
        return PARSING_ERR;
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != INDENT){
        return PARSING_ERR;
      }

      //musi nasledovat statement/y
      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru

      while(tokenAct.type != DEDENT || tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
      }

      tokenAct = nextToken(&error);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
  }

  // neterminal pro cely program(library)
  int program(){
    int result;
    while(tokenAct.type != EOFTOKEN){ // prochazi se cely program
      // muze se jednat bud o funkci, statement
      if(tokenAct.type == STR && tokenAct.attribute.keyword == DEF){
        tokenAct = nextToken(&error);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        result = function();
      }
      else{
        result = statement();
      }
    }
    return result;
  }



  int parse(symbolTable *ST)
  {
    int result;
    //tableVar = ST;
    //list = instrList;
    tokenAct = nextToken(&error);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    else{
        result = program();
    }
    return result;
  }

  int expression(){
    return OK;
  }

  int main(){
      symbolTable *tableVar = initSymbolTable(MAX_SYMTABLE_SIZE);
      setFile("txt.txt");
      int result = parse(tableVar);
      printf("%d\n", result);
      return result;
  }


/* keywordy .. dedenty .. vkladani(search) do symtable*/
