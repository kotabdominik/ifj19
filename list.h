/**
  * list.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: ial c206.h
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

#ifndef _LIST_H_
#define _LIST_H_

typedef struct tDLElem {                 /* prvek dvousměrně vázaného seznamu */
        char *tokenPointer;              /* ukazatel na token */
        struct tDLElem *lptr;          /* ukazatel na předchozí prvek seznamu */
        struct tDLElem *rptr;        /* ukazatel na následující prvek seznamu */
} *tDLElemPtr;

typedef struct {                                  /* dvousměrně vázaný seznam */
    tDLElemPtr First;                      /* ukazatel na první prvek seznamu */
    tDLElemPtr Act;                     /* ukazatel na aktuální prvek seznamu */
    tDLElemPtr Last;                    /* ukazatel na posledni prvek seznamu */
} tDLList;

void DLInitList (tDLList *);
void DLDisposeList (tDLList *);
void DLInsertFirst (tDLList *, token);
void DLInsertLast(tDLList *, token);
void DLDeleteFirst (tDLList *);
void DLDeleteLast (tDLList *);
void DLPostInsert (tDLList *, token);
void DLSucc (tDLList *);

#endif
