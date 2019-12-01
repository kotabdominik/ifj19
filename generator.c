/**
  * generator.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: Generator of code
  *
  */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "symtable.h"
#include "scanner.h"
#include "expressions.h"
#include "list.h"



void degenerate(tDLList *list){
  fprintf(stdout, ".IFJcode19\n");
  generateBuiltInInstructions();
  generate(list);

};

//||======================================================||//
//||=============== Věstavené funkce start ===============||//
{
void generateInputs(){
/*    printf("JUMP _ALFA%d\n", 5); //tmp
    printf("LABEL _OMEGALABEL%p\n", list->First->Instruction->addr1);
    printf("PUSHFRAME\n");

    printf("DEFVAR LF@_RTVL%p\n",list->First->Instruction->addr1);
    printf("MOVE LF@_RTVL%p nil@nil\n",list->First->Instruction->addr1);
    printf("PUSHS LF@_RTVL%p\n",list->First->Instruction->addr1);
*/
    printf("READ LF@$VAR string\n");
    printf("PUSHS LF@$VAR\n");

/*    printf("POPS LF@_RTVL%p\n",list->First->Instruction->addr1);
    printf("POPFRAME\n");

    printf("RETURN\n");
    printf("LABEL _OMEGAJUMP%d\n", 5); //tmp
*/
}

void generateInputi(){
  //fprintf(stdout, "LABEL $BETA\n");
  //fprintf(stdout, "PUSHFRAME\n");

  fprintf(stdout, "READ LF@$VAR int\n");
  fprintf(stdout, "PUSHS LF@$VAR\n");

}

void generateInputf(){

  fprintf(stdout, "READ LF@$VAR float\n");
  fprintf(stdout, "PUSHS LF@$VAR\n");

}

void generatePrint(){

    fprintf(stdout, "LABEL $DELTA\n");
    fprintf(stdout, "DEFVAR $RETVAL\n ");
    while(stack of expressions is not empty)
    {
      fprintf(stdout, "WRITE LF@%s\n",expression);
    }
    fprintf(stdout, "MOVE $RETVAL  string@None\n");

}

void generateLen(){

      fprintf(stdout, "LABEL $LEN\n");
      fprintf(stdout, "DEFVAR LF$RETVAL\n");

      fprintf(stdout, "DEFVAR LF$LENSTR\n");
      //char* tmp = (void *)instrList->First->Instruction.addr1;
      fprintf(stdout, "MOVE LF$LENSTR string@%s\n", (void *)list->First->Instruction.addr1);

      ///podmienka ci je strings

      fprintf(stdout, "STRLEN LF@RETVAL LF@LENSTR\n");
      fprintf(stdout, "PUSHS LF@RETVAL\n");

}

void generateSubstr(){

}

void generateOrd(){

}

void generateChr(){

}
}
//||=============== Věstavené funkce konec ===============||//
//||======================================================||//

void generateVariable(){
    printf("DEFVAR LF@%p\n", );
}


void generateInstruction(tDLList*list){
    for (;list->First != NULL;list->First = list->rptr){
        switch(list->First->Instruction->instType){
            case(I_MOVE):
            case(I_CREATEFRAME):
            case(I_PUSHFRAME):
            case(I_POPFRAME):
            case(I_DEFVAR):
            case(I_CALL):
            case(I_RETURN):
            case(I_PUSHS):
            case(I_POPS):
            case(I_CLEARS):
            case(I_ADD):
            case(I_SUB):
            case(I_MUL):
            case(I_DIV):
            case(I_IDIV):
            case(I_ADDS):
            case(I_SUBS):
            case(I_MULS):
            case(I_DIVS):
            case(I_IDIVS):
            case(I_LT):
            case(I_GT):
            case(I_EQ):
            case(I_LTS):
            case(I_ETS):
            case(I_EQS):
            case(I_AND):
            case(I_OR):
            case(I_NOT):
            case(I_ANDS):
            case(I_ORS):
            case(I_NOTS):
            case(I_INT2FLOAT):
            case(I_FLOAT2INT):
            case(I_INT2CHAR):
            case(I_STRI2INT):
            case(I_INT2FLOATS):
            case(I_FLOAT2INTS):
            case(I_INT2CHARS):
            case(I_STRI2INTS):
            case(I_READ):
            case(I_WRITE):
            case(I_CONCAT):
            case(I_STRLEN):
            case(I_GETCHAR):
            case(I_SETCHAR):
            case(I_TYPE):
            case(I_LABEL):
            case(I_JUMP):
            case(I_JUMPIFEQ):
            case(I_JUMPIFNEQ):
            case(I_JUMPIFEQS):
            case(I_JUMPIFNEQS):
            case(I_EXIT):
            case(I_BREAK):
            case(I_DPRINT):

        }
    }
}

void generateIf(){
    printf("DEFVAR");
    printf("MOVE");
    printf("LABEL X");
    printf("JUMPIFNEQ");
    printf("JUMP");
    printf("LABEL");
}

void generateWhile(){
    printf("DEFVAR");
    printf("MOVE");
    printf("LABEL X");
    printf("JUMPIFEQ Y");
    GENERATE UWU OWO TO WORK ON
    printf("JUMP X");
    printf("LABEL Y");
}
