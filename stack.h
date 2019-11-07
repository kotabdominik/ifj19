/**
  * stack.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: header for stack which will be used in scanner
  *
  */

  #ifndef _STACK_H_
  #define _STACK_H_

  #include <stdio.h>

  extern int err_flag;                   /* Indikuje, zda operace volala chybu. */

                                          /* Chybové kódy pro funkci stackError */
  #define MAX_SERR    3                                   /* počet možných chyb */
  #define SERR_INIT   1                                  /* chyba při stackInit */
  #define SERR_PUSH   2                                  /* chyba při stackPush */
  #define SERR_TOP    3                                   /* chyba při stackTop */

                               /* ADT zásobník implementovaný ve statickém poli */
  typedef struct {
  	char arr[MAX_STACK];                             /* pole pro uložení hodnot */
  	int top;                                /* index prvku na vrcholu zásobníku */
  } tStack;

                                    /* Hlavičky funkcí pro práci se zásobníkem. */
  void stackError ( int error_code );
  void stackInit ( tStack* s );
  int stackEmpty ( const tStack* s );
  int stackFull ( const tStack* s );
  void stackTop ( const tStack* s, char* c );
  void stackPop ( tStack* s );
  void stackPush ( tStack* s, char c );

  #endif
