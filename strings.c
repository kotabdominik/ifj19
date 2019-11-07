/**
  * strings.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: operations for strings
  *
  */

#include "error.h"
#include "strings.h"

void stringInit(smartString *str) {
  str->string = NULL;
  str->length = str->allocatedSize = 0;
}

void stringFree(smartString *str) {
  free(str->string);
  str->length = str->allocatedSize = 0;
}

void stringClear(smartString *str) {
  for(int i = 0; i < str->length; i++) {
    str->string[i] = '\0';
  }
  str->length = 0;
}

void stringAddChar(smartString *str, char c) {
  //dá nakonec stringu char, takhle se budou ty stringy creatovat
  return;
}

//ma toto byt tady??, zjisti, jestli string je keyword
int stringIsKeyword(smartString *str) {
  char *keywords[] = {"def\0", "else\0", "if\0", "None\0", "pass\0", "return\0", "while\0"};
  //testovani
  return 0; //je keyword?0/1
}
