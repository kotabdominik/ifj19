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

//typy instrukci
#define I_MOVE 0
#define I_CREATEFRAME 1
#define I_PUSHFRAME 2
#define I_POPFRAME 3
#define I_DEFVAR 4
#define I_CALL 5
#define I_RETURN 6
#define I_PUSHS 7
#define I_POPS 8
#define I_CLEARS 9
#define I_ADD 10
#define I_SUB 11
#define I_MUL 12
#define I_DIV 13
#define I_IDIV 14
#define I_ADDS 15
#define I_SUBS 16
#define I_MULS 17
#define I_DIVS 18
#define I_IDIVS 19
#define I_LT
#define I_GT
#define I_EQ
#define I_LTS
#define I_ETS
#define I_EQS
#define I_AND
#define I_OR
#define I_NOT
#define I_ANDS
#define I_ORS
#define I_NOTS
#define I_INT2FLOAT
#define I_FLOAT2INT
#define I_INT2CHAR
#define I_STRI2INT
/*#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_
#define I_*/



typedef struct
{
  int instType;  // typ instrukce
  void *addr1; // adresa 1
  void *addr2; // adresa 2
  void *addr3; // adresa 3
} tInstr;

typedef struct tDLElem {                 /* prvek dvousměrně vázaného seznamu */
        tInstr Instruction;            /* ukazatel na token */
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
void DLInsertFirst (tDLList *, tInstr);
void DLInsertLast(tDLList *, tInstr);
void DLDeleteFirst (tDLList *);
void DLDeleteLast (tDLList *);
void DLPostInsert (tDLList *, tInstr);
void DLSucc (tDLList *);

#endif
