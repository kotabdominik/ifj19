#include <stdlib.h>
#include "absTree.h"
#include "list.h"
#include "stack.h"
#include "symtable.h"
#include "tokenStack.h"
#include "error.h"
#include "symtable.c"
#include "list.c"

#ifndef _SLAY_H_
#define _SLAY_H_

void slay(ATLeaf *leaf, tDLList *L, tStack* s, symbolTable *sT /*,tokenStack* s*/) {
  fprintf(stderr, "Invalid malloc." );
  //dispose_at(leaf); //IBA LIST
  DLDisposeList (L);
  stackDestroy (s);
  freeSymbolTable(sT);
  //tokenStackDestruct (s);
  exit (INTERN_ERR); //(INTERN_ERR)
}
int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}


#endif
