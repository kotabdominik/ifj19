/**
  * symboltable.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: implementation of operations above/on symbol table
  *
  */

/*
 * inicializace symbol table
 * table je implementovan pomoci binarniho stromu
 * = inicializuje se binarni strom
*/
void initSymbolTable(symbolTable *sT){
  /*strominit*/(&(sT->root));
}

/*
 * vlozeni dat o funkci do symbol table
 *
*/
void insertFunctionSymbolTable(symbolTable *sT, smartString string){

}


/* for full version go to https://github.com/DavidHribek/IFJ/blob/development/src/symtable.c */
