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


symbolTable *tableG;// globalni promenna uchovavajici tabulku symbolu
tDLList *list; // globalni promenna uchovavajici seznam instrukci
token tokenAct;          // globalni promenna, ve ktere bude ulozen aktualni token
//smartString attr;        // globalni promenna, ve ktere bude ulozen atribut tokenu
int error = OK;

int counterVar = 1;
tStack *stack;
int doIndent = 0;

// generuje jedinecne nazvy identifikatoru
// nazev se sklada ze znaku $ nasledovanym cislem
// postupne se tu generuji prirozena cisla a do nazvu promenne se ukladaji
// v reverzovanem poradi - na funkcnost to nema vliv, ale je jednodussi implementace
void generateVariable(smartString *var) {
    stringClear(var);
    stringAddChar(var, '$');
    int i = counterVar; //counterVar je globalní proměnná, kdyžtak změnit na argument i guess
    while (i != 0) {
        stringAddChar(var, (char)(i % 10 + '0'));
        i = i / 10;
    }
    counterVar ++;
}

// vlozi novou instrukci do seznamu instrukci
tInstr *generateInstruction(int instType, void *addr1, void *addr2, void *addr3) {
    tInstr I;
    I.instType = instType;
    I.addr1 = addr1;
    I.addr2 = addr2;
    I.addr3 = addr3;

    return DLInsertLast(list, I);
}

// ==================================================================
// jednotlive funkce odpovidajici jednotlivym nonterminalum gramatiky
// ==================================================================

//-----------------------------------------STATEMENT--------------------------------------
int statement(char *funName){
  int result;
  tInstr *jmp1, *jmp2;


  if(tokenAct.type == KEYWORD){
    if(tokenAct.attribute.keyword == IF){ // IF----------------------------------
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != INT && tokenAct.type != FLOAT && tokenAct.type != STR && tokenAct.type != LITERAL){
          fprintf(stderr, "Ocekaval se vyraz, ale prisel necekany token\n");
          return PARSING_ERR;
        }
        result = expression();
        if(result != OK) return result;
        jmp1 = generateInstruction(I_JUMP, NULL, NULL, NULL); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!2. NULL musi byt vysledek expression

        /*tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru*/
        if(tokenAct.type != COLON) return PARSING_ERR;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != EOL) return PARSING_ERR;

        doIndent = 1;
        tokenAct = nextToken(&error, stack, doIndent);
        doIndent = 0;
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != INDENT) return PARSING_ERR;

        //musi nasledovat statement/y
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru

        do{
            result = statement(funName);
            if(result != OK) return result;//kouknout jestli statement probehl bez erroru
            if(tokenAct.type == EOFTOKEN) return PARSING_ERR;
        } while(tokenAct.type != DEDENT); //&& tokenAct.type != EOFTOKEN
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru

        if(tokenAct.type != KEYWORD) return PARSING_ERR;
        if(tokenAct.attribute.keyword != ELSE) return PARSING_ERR;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != COLON) return PARSING_ERR;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != EOL) return PARSING_ERR;

        doIndent = 1;
        tokenAct = nextToken(&error, stack, doIndent);
        doIndent = 0;
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != INDENT) return PARSING_ERR;

        jmp2 = generateInstruction(I_JUMP, NULL, NULL, NULL); //???????????????????????????????????????????????????????????????
        generateInstruction(I_LABEL, NULL, NULL, NULL); //???????????????????????????????????????????????????????????????

        jmp1->addr1 = list->Last;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        do{
            result = statement(funName);
            if(result != OK) return result;//kouknout jestli statement probehl bez erroru
        } while(tokenAct.type != DEDENT && tokenAct.type != EOFTOKEN);

        doIndent = 1;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        //nesmi tady byt indent
        if(tokenAct.type == INDENT) return PARSING_ERR;
        doIndent = 0;
        //pokud je dedent, posleme ten token dal;
        if(tokenAct.type == DEDENT) return OK;
        //pokud neni ani indent ani dedent, tak vygenerujeme novy token ktery posleme dal
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return OK;

        generateInstruction(I_LABEL, NULL, NULL, NULL);
        jmp2->addr1 = list->Last;

        return OK;

        /*
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != EOL){
            return PARSING_ERR;
        }
        doIndent = 1;
        tokenAct = nextToken(&error, stack, doIndent);
        doIndent = 0;
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != DEDENT){
            return PARSING_ERR;
        }
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return OK;*/
    }
    else if(tokenAct.attribute.keyword == WHILE){ // WHILE ---------------------------------
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru

        jmp2 = generateInstruction(I_JUMP, NULL, NULL, NULL);
        generateInstruction(I_LABEL, NULL, NULL, NULL);
        jmp2->addr1 = list->Last;

        if(tokenAct.type != INT && tokenAct.type != FLOAT && tokenAct.type != STR && tokenAct.type != LITERAL){
          fprintf(stderr, "Ocekaval se vyraz, ale prisel necekany token\n");
          return PARSING_ERR;
        }
        result = expression();
        if(result != OK) return result;
        jmp1 = generateInstruction(I_JUMP, NULL, NULL, NULL); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!2. NULL musi byt vysledek expression

        /*tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru*/
        if(tokenAct.type != COLON) return PARSING_ERR;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != EOL) return PARSING_ERR;
        doIndent = 1;
        tokenAct = nextToken(&error, stack, doIndent);
        doIndent = 0;
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != INDENT) return PARSING_ERR;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        do{
            result = statement(funName);
            if(result != OK) return result;//kouknout jestli statement probehl bez erroru
        } while(tokenAct.type != DEDENT && tokenAct.type != EOFTOKEN);

        generateInstruction(jmp2->instType, jmp2->addr1, jmp2->addr2, jmp2->addr3);
        generateInstruction(I_LABEL, NULL, NULL, NULL);
        jmp1->addr1 = list->Last;

        doIndent = 1;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        //nesmi tady byt indent
        if(tokenAct.type == INDENT) return PARSING_ERR;
        doIndent = 0;
        //pokud je dedent, posleme ten token dal;
        if(tokenAct.type == DEDENT) return OK;
        //pokud neni ani indent ani dedent, tak vygenerujeme novy token ktery posleme dal
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return OK;


        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != DEDENT){
            return PARSING_ERR;
        }

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return OK;
    }
    else if(tokenAct.attribute.keyword == PASS){ // PASS --------------------------------------
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != EOL && tokenAct.type != EOFTOKEN) return PARSING_ERR;
        if(tokenAct.type == EOFTOKEN) return OK;

        doIndent = 1;
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        //nesmi tady byt indent
        if(tokenAct.type == INDENT) return PARSING_ERR;
        doIndent = 0;
        //pokud je dedent, posleme ten token dal;
        if(tokenAct.type == DEDENT) return OK;
        //pokud neni ani indent ani dedent, tak vygenerujeme novy token ktery posleme dal
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return OK;
    }
    else if(tokenAct.attribute.keyword == RETURN){ // RETURN -------------------------------------
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != INT && tokenAct.type != FLOAT && tokenAct.type != STR && tokenAct.type != LITERAL){
          fprintf(stderr, "Ocekaval se vyraz, ale prisel necekany token\n");
          return PARSING_ERR;
        }
        result = expression();
        if(result != OK) return result;

        generateInstruction(I_PUSHS, NULL, NULL, NULL); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1. NULL musi byt vysledek expression
        generateInstruction(I_RETURN, NULL, NULL, NULL);

        /*tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru*/
        if(tokenAct.type != EOL && tokenAct.type != EOFTOKEN) return PARSING_ERR;
        if(tokenAct.type == EOFTOKEN) return OK; // pokud je to konec filu, nezkoumame dalsi token

        doIndent = 1;
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        //nesmi tady byt indent
        if(tokenAct.type == INDENT) return PARSING_ERR;
        doIndent = 0;
        //pokud je dedent, posleme ten token dal;
        if(tokenAct.type == DEDENT) return OK;
        //pokud neni ani indent ani dedent, tak vygenerujeme novy token ktery posleme dal
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return OK;
    }
    else if(tokenAct.attribute.keyword == INPUTS ||
            tokenAct.attribute.keyword == INPUTF ||
            tokenAct.attribute.keyword == INPUTI ||
            tokenAct.attribute.keyword == PRINT  ||
            tokenAct.attribute.keyword == LEN    ||
            tokenAct.attribute.keyword == SUBSTR ){
              tokenAct = nextToken(&error, stack, doIndent);
              if(error != OK) return error; // zkoumani lexikalniho erroru
              if(tokenAct.type == LEFTBRACKET){
                fprintf(stderr, "za nazvem vestavene funkce musi nasledovat ( \n");
                return PARSING_ERR;
              }
              //callParams atd atd
    }
    else if(tokenAct.attribute.keyword == NONE){
      result = expression();
      if(result != OK) return result;

      if(tokenAct.type != EOL && tokenAct.type != EOFTOKEN) return PARSING_ERR;
      if(tokenAct.type == EOFTOKEN) return OK; // pokud je to konec filu, nezkoumame dalsi token

      doIndent = 1;
      tokenAct = nextToken(&error, stack, doIndent);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      //nesmi tady byt indent
      if(tokenAct.type == INDENT) return PARSING_ERR;
      doIndent = 0;
      //pokud je dedent, posleme ten token dal;
      if(tokenAct.type == DEDENT) return OK;
      //pokud neni ani indent ani dedent, tak vygenerujeme novy token ktery posleme dal
      tokenAct = nextToken(&error, stack, doIndent);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      return OK;
    }
    else{
      fprintf(stderr, "Ocekaval se prikaz, ale bohuzel prisel jiny token\n");
      return PARSING_ERR;
    }
  }
  else if(tokenAct.type == STR){
    token tmpToken = tokenAct;
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type == ASSIGN){
      if(strcmp(funName, "globalTable") == 0){
        //insertSymbolTable(tableG, tokenAct, FUNCTION); //vlozeni funkce do tabulky funkci
      } else {
        symtableItem *tmp = searchSymbolTableWithString(tableG, funName);
        insertSymbolTable(tmp->elementType.function->sT, tmpToken, VARIABLE);
        printf("%s\n", tableG->symtabList[hash(funName)]->elementType.function->sT->symtabList[hash(tmpToken.attribute.string->string)]->key);
      }

      assignment();
      /*probably jeste nejaky konce radku atd? mozna se to udela v assignment ... we'll have to see about it*/
      return OK;
    }
    else if(tokenAct.type == LEFTBRACKET){
      //call params i quess
    }
    else{
      fprintf(stderr, "ocekavalo se ze se do identifikatoru bude bud zapisovat, nebo se pomoci nej bude volat funkce.. nenastalo ani jedno\n");
      return PARSING_ERR;
    }
  }
  else if(tokenAct.type == INT || tokenAct.type == FLOAT || tokenAct.type == LITERAL || tokenAct.type == LEFTBRACKET){
    result = expression();
    if(result != OK) return result;

    if(tokenAct.type != EOL && tokenAct.type != EOFTOKEN) return PARSING_ERR;
    if(tokenAct.type == EOFTOKEN) return OK; // pokud je to konec filu, nezkoumame dalsi token

    doIndent = 1;
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    //nesmi tady byt indent
    if(tokenAct.type == INDENT) return PARSING_ERR;
    doIndent = 0;
    //pokud je dedent, posleme ten token dal;
    if(tokenAct.type == DEDENT) return OK;
    //pokud neni ani indent ani dedent, tak vygenerujeme novy token ktery posleme dal
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    return OK;
  }
  else{
    fprintf(stderr, "Ocekaval se prikaz, ale bohuzel prisel jiny token\n");
    return PARSING_ERR;
  }

  return OK;
}

//---------------------------------------FUNCTION-------------------------------------------
int function(){
    int result;

    if(tokenAct.type != STR) return PARSING_ERR; //za def musi nasledovat identifikator
    smartString *s = tokenAct.attribute.string;
    //musi nasledovat '('
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != LEFTBRACKET){
      fprintf(stderr, "Za DEF ID musi nasledovat ( \n");
      return PARSING_ERR;
    }

    /*
    //musi nasledovat identifikator
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru

    if(tokenAct.type != STR && tokenAct.type != RIGHTBRACKET) return PARSING_ERR;

    if (tokenAct.type == STR) {
        tokenAct = nextToken(&error, stack, doIndent);
        if (error != OK) return error; // zkoumani lexikalniho erroru
        while (tokenAct.type != RIGHTBRACKET) {

            //dalsi token musi byt ','
            if (tokenAct.type != COMMA) return PARSING_ERR;

            //dalsi token musi byt identifikator
            tokenAct = nextToken(&error, stack, doIndent);
            if (error != OK) return error; // zkoumani lexikalniho erroru

            if (tokenAct.type != STR) return PARSING_ERR;

            tokenAct = nextToken(&error, stack, doIndent);
            if (error != OK) return error; // zkoumani lexikalniho erroru
        }
    }
*/
    result = defParams(s->string);
    if(result != OK) return result;

    generateInstruction(I_CLEARS, NULL, NULL, NULL);

    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != COLON){
      fprintf(stderr, "Za DEF ID ( pripadne argumenty ) musi nasledovat : \n");
      return PARSING_ERR;
    }
    //musi nasledovat EOL -> INDENT -> statement
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != EOL){
      fprintf(stderr, "Za DEF ID ( pripadne argumenty ): musi nasledovat konec radku \n");
      return PARSING_ERR;
    }

    doIndent = 1;
    tokenAct = nextToken(&error, stack, doIndent);
    doIndent = 0;
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != INDENT){
      fprintf(stderr, "Za DEF ID ( pripadne argumenty ) : EOL musi nasledovat indent \n");
      return PARSING_ERR;
    }
    //musi nasledovat statement/y
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru


    while(tokenAct.type != DEDENT && tokenAct.type != EOFTOKEN){
        result = statement(s->string);
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
    }


    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    return OK;
}

//---------------------------------------------ASSIGNMENT-----------------------------------
int assignment(){
  tokenAct = nextToken(&error, stack, doIndent);
  if(error != OK) return error; // zkoumani lexikalniho erroru

  if(tokenAct.type == KEYWORD){
    if(tokenAct.attribute.keyword == INPUTS){
      tokenAct = nextToken(&error, stack, doIndent);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != LEFTBRACKET) return PARSING_ERR;
      // ?????????????????????????????????????????????????????????????????????????????????????????????
      //smartString *s = tokenAct.attribute.string;
      //callParams(funName);
      /*tokenAct = nextToken(&error, stack, doIndent);
      if(error != OK) return error; // zkoumani lexikalniho erroru
      if(tokenAct.type != RIGHTBRACKET) return PARSING_ERR;*/
      //generateInstruction
    }
    else if(tokenAct.attribute.keyword == INPUTI){

    }
    else if(tokenAct.attribute.keyword == INPUTF){

    }
    else if(tokenAct.attribute.keyword == PRINT){

    }
    else if(tokenAct.attribute.keyword == LEN){

    }
    else if(tokenAct.attribute.keyword == SUBSTR){

    }

  }
}

//---------------------------------------------PROGRAM-------------------------------------
int program(){
    int result = OK; ////Inicializacia v prípade že máš hned EOF (Ne/10:28)
    //prvni token
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru

    while(tokenAct.type != EOFTOKEN){ // prochazi se cely program
        // muze se jednat bud o funkci, statement
        if(tokenAct.type == KEYWORD && tokenAct.attribute.keyword == DEF){
            tokenAct = nextToken(&error, stack, doIndent);
            if(error != OK) return error; // zkoumani lexikalniho erroru
            result = function();
            if(result != OK) return result;
        }
        else{
            if(tokenAct.type == KEYWORD && tokenAct.attribute.keyword == RETURN){
              fprintf(stderr, "V tele programu se nesmi nachazet return\n");
              return PARSING_ERR;
            }
            result = statement("globalTable");
            if(result != OK) return result;
        }
    }
    return result;
}

//---------------------------------------------DEFPARAMS----------------------------------
int defParams(char* funName){
    int argc = 0;
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type == RIGHTBRACKET) return OK;
    else if(tokenAct.type == STR){
        //chybi pridat symbol do funkce ?
        functionData *item;
        item = (functionData *) malloc(sizeof(functionData));
        item->arguments = (symtableItem *) malloc(sizeof(symtableItem));
        item->arguments[argc].type = VARIABLE;
        (item->arguments[argc]).elementType.variable = (variableData *) malloc(sizeof(variableData));
        (item->arguments[argc]).elementType.variable->type = VARIABLE;
        (item->arguments[argc]).key = tokenAct.attribute.string->string;
        item->argCount = argc+1;

        symtableItem *tmpIT = searchSymbolTableWithString(tableG, funName);
        tmpIT->next = tableG->symtabList[hash(funName)]; //pokud je něco na stejným indexu =)
        tmpIT->elementType.function = item;
        tableG->symtabList[hash(funName)] = tmpIT;

        symtableItem *tmp = searchSymbolTable(tableG, tokenAct);
        if (tmp && tmp->type == FUNCTION){
          fprintf(stderr, "Snazite se definovat variable(jako argument funkce), ktery je stejny jako nejaky nazev funkce\n");
          return SEM_DEF_ERR;
        }
        generateInstruction(I_POPS, NULL, NULL, NULL); ////////////////////////////OPRAVIT///////////////////////////////////////////
        return defParamsN(funName, ++argc);
    }
    else {
      fprintf(stderr, "za DEF ID (  musi nasledovat bud ) nebo nejaky identifikator\n");
      return PARSING_ERR;
    }
}

//---------------------------------------------DEFPARAMSN----------------------------------
int defParamsN(char* funName, int argc){
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type == RIGHTBRACKET) return OK;
    if(tokenAct.type != COMMA){
      fprintf(stderr, "Za DEF ID ( ID  musi nasledovat bud ) nebo , \n");
      return PARSING_ERR;
    }
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != STR){
      fprintf(stderr, "Za DEF ID ( ID ,  musi nasledovat ID   ( ID , se mohlo pred timto opakovat nekolikrat)\n");
      return PARSING_ERR;
    }
    argc++;

    //chybi pridat symbol do tabulky funkce
    //checknout jestli se 2 parametry nejmenuji stejne
    symtableItem *tmpAAAAAA = searchSymbolTableWithString(tableG, funName); //hledáme nejen na indexu, ale i jestli někam neukazuje yk
    functionData *item = tmpAAAAAA->elementType.function;
    item->argCount = argc;
    item->arguments = realloc(item->arguments, argc*sizeof(symtableItem));
    item->arguments[argc-1].type = VARIABLE;
    (item->arguments[argc-1]).key = tokenAct.attribute.string->string;

    for (int i = 0; i < (argc-1); i++) {
      if(!strcmp((item->arguments[i]).key, (item->arguments[argc-1]).key)) return SEM_DEF_ERR;
    }

    symtableItem *tmp = searchSymbolTable(tableG, tokenAct);
    if (tmp && tmp->type == FUNCTION){
      fprintf(stderr, "Snazite se definovat variable(jako argument funkce), ktery je stejny jako nejaky nazev funkce\n");
      return SEM_DEF_ERR;
    }
    generateInstruction(I_POPS, NULL, NULL, NULL); ////////////////////////////OPRAVIT///////////////////////////////////////////
    return defParamsN(funName, argc);
}

//---------------------------------------------CALLPARAMS----------------------------------
int callParams(char* funName){
  return 0;
}

//---------------------------------------------CALLPARAMSN----------------------------------
int callParamsN(char* funName){
  return 0;
}

/*projede cely soubor a najde tam definice funkci a tyto funkce vlozi do tabulky funkci*/
int initFunctions(){

    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error;

    while(tokenAct.type != EOFTOKEN){
        if(tokenAct.type == EOL){
            doIndent = 1;
            tokenAct = nextToken(&error, stack, doIndent);
            doIndent = 0;
        }
        if(tokenAct.type == KEYWORD && tokenAct.attribute.keyword == DEF){

            tokenAct = nextToken(&error, stack, doIndent);
            if(error != OK) return error; // zkoumani lexikalniho erroru

            if(tokenAct.type != STR){
              fprintf(stderr, "Za keywordem DEF musi nasledovat identifikator\n");
              return PARSING_ERR;
            }

            if(searchSymbolTable(tableG, tokenAct) != NULL){
              fprintf(stderr, "Chyba, kvuli snaze o redefinici funkce\n");
              return SEM_DEF_ERR;
            }
            insertSymbolTable(tableG, tokenAct, FUNCTION); //vlozeni funkce do tabulky funkci
        }

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error;
    }

    resetToken();
    return OK;
}

/*prida vestavene funkce do symtable*/
void addBuildInFunc(){
  //--------------------INPUTS
  token tmpToken;
  smartString *tmpString = malloc(sizeof(smartString));
  stringInit(tmpString);
  stringAddChar(tmpString,'i');
  stringAddChar(tmpString,'n');
  stringAddChar(tmpString,'p');
  stringAddChar(tmpString,'u');
  stringAddChar(tmpString,'t');
  stringAddChar(tmpString,'s');

  tmpToken.attribute.string = tmpString;
  tmpToken.type = KEYWORD;
  insertSymbolTable(tableG, tmpToken, FUNCTION); //vlozeni funkce do tabulky funkci

  //-------------------------INPUTI
  smartString *tmpString0 = malloc(sizeof(smartString));
  stringInit(tmpString0);
  stringAddChar(tmpString0,'i');
  stringAddChar(tmpString0,'n');
  stringAddChar(tmpString0,'p');
  stringAddChar(tmpString0,'u');
  stringAddChar(tmpString0,'t');
  stringAddChar(tmpString0,'i');

  tmpToken.attribute.string = tmpString0;
  tmpToken.type = KEYWORD;
  insertSymbolTable(tableG, tmpToken, FUNCTION); //vlozeni funkce do tabulky funkci

  //----------------------INPUTF
  smartString *tmpString1 = malloc(sizeof(smartString));
  stringInit(tmpString1);
  stringAddChar(tmpString1,'i');
  stringAddChar(tmpString1,'n');
  stringAddChar(tmpString1,'p');
  stringAddChar(tmpString1,'u');
  stringAddChar(tmpString1,'t');
  stringAddChar(tmpString1,'f');

  tmpToken.attribute.string = tmpString1;
  tmpToken.type = KEYWORD;
  insertSymbolTable(tableG, tmpToken, FUNCTION); //vlozeni funkce do tabulky funkci

  //-------------------PRINT
  smartString *tmpString2 = malloc(sizeof(smartString));
  stringInit(tmpString2);
  stringAddChar(tmpString2,'p');
  stringAddChar(tmpString2,'r');
  stringAddChar(tmpString2,'i');
  stringAddChar(tmpString2,'n');
  stringAddChar(tmpString2,'t');

  tmpToken.attribute.string = tmpString2;
  tmpToken.type = KEYWORD;
  insertSymbolTable(tableG, tmpToken, FUNCTION); //vlozeni funkce do tabulky funkci

  functionData *item0;
  item0 = (functionData *) malloc(sizeof(functionData));
  item0->argCount = -1;
  tableG->symtabList[hash("print")]->elementType.function = item0;


  //-------------------LEN
  smartString *tmpString3 = malloc(sizeof(smartString));
  stringInit(tmpString3);
  stringAddChar(tmpString3,'l');
  stringAddChar(tmpString3,'e');
  stringAddChar(tmpString3,'n');

  tmpToken.attribute.string = tmpString3;
  tmpToken.type = KEYWORD;
  insertSymbolTable(tableG, tmpToken, FUNCTION); //vlozeni funkce do tabulky funkci

  functionData *item1;
  item1 = (functionData *) malloc(sizeof(functionData));
  /*item1->arguments = (symtableItem *) malloc(sizeof(symtableItem));
  item1->arguments[0].type = VARIABLE;
  (item1->arguments[0]).elementType.variable = (variableData *) malloc(sizeof(variableData));
  (item1->arguments[0]).elementType.variable->type = VARIABLE;
  (item1->arguments[0]).key = "s";*/  //????????????????????????????????????????????????????????? maybe? kdyztak dodelat i u substr
  item1->argCount = 1;
  tableG->symtabList[hash("len")]->elementType.function = item1;

  //-------------------SUBSTR
  smartString *tmpString4 = malloc(sizeof(smartString));
  stringInit(tmpString4);
  stringAddChar(tmpString4,'s');
  stringAddChar(tmpString4,'u');
  stringAddChar(tmpString4,'b');
  stringAddChar(tmpString4,'s');
  stringAddChar(tmpString4,'t');
  stringAddChar(tmpString4,'r');

  tmpToken.attribute.string = tmpString4;
  tmpToken.type = KEYWORD;
  insertSymbolTable(tableG, tmpToken, FUNCTION); //vlozeni funkce do tabulky funkci

  functionData *item2;
  item2 = (functionData *) malloc(sizeof(functionData));
  item2->argCount = -1;
  tableG->symtabList[hash("substr")]->elementType.function = item2;
}

// hlavni funkce ktera udela parse :]]]
int parse(symbolTable *ST,  tDLList *instrList){
    int result; //to co budeme vracet (bud error, nebo OK)
    tableG = ST; // globalni promenna pro globalni promenne
    list = instrList; //list do ktereho se budou davat instrukce

    addBuildInFunc();

    result = initFunctions();
    if(result != OK) return result;

    result = program();

    return result;
}


//for the MEMES
int expression(){
  tokenAct = nextToken(&error, stack, doIndent);
  if(error != OK) return error; // zkoumani lexikalniho erroru
  return OK;
}










// DEBUGGING
int main(){
    stack = malloc(sizeof(tStack));
    stackInit(stack);
    stackPush(stack, 0);

    tDLList *instrList = malloc(sizeof(tDLList));
    DLInitList(instrList);
    symbolTable *tableGG = initSymbolTable(MAX_SYMTABLE_SIZE);

    setFile("txt.txt");
    int result = parse(tableGG, instrList);

    printf("%d\n", result);
    return result;
}


// expression ... predpoklada se, ze do expression prijde rovnou novy token ktery se ma rozparsovat
//                a ze z expression jeden token vyjde


// DODELAT 269, 281, 285, callParams, assignment
// 269 = keywordy, ktere jsou vestavene funkce
// 281 = kdyz je string a pak assign
// 285 = kdyz je string a pak leva zavorka (volani funkce)
