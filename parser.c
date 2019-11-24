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
void generateInstruction(int instType, void *addr1, void *addr2, void *addr3) {
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


int statement(){
    int result;

    //pokud nezacina statement keywordem, jedna se bud o chybu, nebo o expression
    if(tokenAct.type != KEYWORD){
        result = expression();
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return result;
    }

    if(tokenAct.attribute.keyword == IF){ // IF----------------------------------
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        result = expression();
        if(result != OK) return result;

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

        //musi nasledovat statement/y
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru

        do{
            result = statement();
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

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        do{
            result = statement();
            if(result != OK) return result;//kouknout jestli statement probehl bez erroru
        } while(tokenAct.type != DEDENT && tokenAct.type != EOFTOKEN);

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
        result = expression();

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

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        do{
            result = statement();
            if(result != OK) return result;//kouknout jestli statement probehl bez erroru
        } while(tokenAct.type != DEDENT && tokenAct.type != EOFTOKEN);

        return OK;

        /*
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type != DEDENT){
            return PARSING_ERR;
        }

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return OK;*/
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
        result = expression();
        if(result != OK) return result;

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
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
        /*else if(tokenAct.attribute.keyword == DEF){
          result = function();
          return result;
        }*/
    else{ //pokud jsou to jine keywordy, tak se nejspis jedna o expression, za kterou nasleduje eof nebo eol
        result = expression();
        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error; // zkoumani lexikalniho erroru
        if(tokenAct.type == EOFTOKEN) return result;
        else if(tokenAct.type != EOL) return PARSING_ERR;

        doIndent = 1;
        tokenAct = nextToken(&error, stack, doIndent);
        doIndent = 0;
        if(error != OK) return error; // zkoumani lexikalniho erroru
        return result;
    }

    return OK;
}


//---------------------------------------FUNCTION-------------------------------------------
int function(){
    int result;

    if(tokenAct.type != STR) return PARSING_ERR; //za def musi nasledovat identifikator

    //musi nasledovat '('
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != LEFTBRACKET) return PARSING_ERR;

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
    result = defParams();
    if(result != OK) return result;

    generateInstruction(I_CLEARS, NULL, NULL, NULL);

    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != COLON) return PARSING_ERR;

    //musi nasledovat EOL -> INDENT -> statement
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


    while(tokenAct.type != DEDENT && tokenAct.type != EOFTOKEN){
        result = statement();
        if(result != OK) return result;//kouknout jestli statement probehl bez erroru
    }


    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    return OK;
}

//---------------------------------------------ASSIGNMENT-----------------------------------
int assignment(){
  
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
            result = statement();
            if(result != OK) return result;
        }
    }
    return result;
}

int defParams(){
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type == RIGHTBRACKET) return OK;
    else if(tokenAct.type == STR){
        //chybi pridat symbol do funkce ?
        if(searchSymbolTable(tableFunc, tokenAct) != NULL) return SEM_DEF_ERR;
        generateInstruction(I_POPS, NULL, NULL, NULL); ////////////////////////////OPRAVIT///////////////////////////////////////////
        return defParamsN();
    }
    else return PARSING_ERR;
}

int defParamsN(){
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type == RIGHTBRACKET) return OK;
    if(tokenAct.type != COMMA) return PARSING_ERR;
    tokenAct = nextToken(&error, stack, doIndent);
    if(error != OK) return error; // zkoumani lexikalniho erroru
    if(tokenAct.type != STR) return PARSING_ERR;
    //chybi pridat symbol do funkce ?
    //checknout jestli se 2 parametry nejmenuji stejne
    if(searchSymbolTable(tableFunc, tokenAct) != NULL) return SEM_DEF_ERR;
    generateInstruction(I_POPS, NULL, NULL, NULL); ////////////////////////////OPRAVIT///////////////////////////////////////////
    return defParamsN();
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

            if(tokenAct.type != STR) return PARSING_ERR;

            if(searchSymbolTable(tableFunc, tokenAct) != NULL) return SEM_DEF_ERR;
            insertSymbolTable(tableFunc, tokenAct, FUNCTION); //vlozeni funkce do tabulky funkci
        }

        tokenAct = nextToken(&error, stack, doIndent);
        if(error != OK) return error;
    }

    resetToken();
    return OK;
}


int parse(symbolTable *STV, symbolTable *STF, tDLList *instrList)
{
    int result; //to co budeme vracet (bud error, nebo OK)
    tableVar = STV; // globalni promenna pro globalni promenne
    tableFunc = STF; //globalni promenna pro funkce
    list = instrList; //list do ktereho se budou davat instrukce

    result = initFunctions();
    if(result != OK) return result;

    result = program();

    return result;
}


//for the MEMES
int expression(){
    return OK;
}










// DEBUGGING
int main(){
    stack = malloc(sizeof(tStack));
    stackInit(stack);
    stackPush(stack, 0);

    tDLList *instrList = malloc(sizeof(tDLList));
    DLInitList(instrList);
    symbolTable *tableVar = initSymbolTable(MAX_SYMTABLE_SIZE);
    symbolTable *tableFunc = initSymbolTable(MAX_SYMTABLE_SIZE);

    setFile("txt.txt");
    int result = parse(tableVar, tableFunc, instrList);

    printf("%d\n", result);
    return result;
}


/* keywordy .. dedenty .. vkladani(search) do symtable*/
