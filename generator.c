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

      fprintf(stdout, "LABEL $LENGTH\n");
      fprintf(stdout, "PUSHFRAME\n");
      fprintf(stdout, "DEFVAR LF$RETVAL\n");
      //fprintf(stdout, "MOVE LF$RETVAL int@0\n");  ///Check či je to potrebne
      //fprintf(stdout, "DEFVAR LF$LENSTR\n");
      //char* tmp = (void *)instrList->First->Instruction.addr1;
      ///no idea ale zjavne bude stačiť random LF premenna..?
      //fprintf(stdout, "MOVE LF$LENSTR string@%s\n", (void *)list->First->Instruction.addr1);

      ///podmienka ci je strings
      //podmienky tldr robi domino teda nie?
      //shoudda me keep checking em?

      fprintf(stdout, "STRLEN LF@RETVAL LF@%1\n"); ///premenne parametrov su MEME (zapis cislami)
      //fprintf(stdout, "PUSHS LF@RETVAL\n");
      fprintf(stdout, "POPFRAME\n");
      fprintf(stdout, "RETURN\n");
}
//substr(s,i,n)– Vrátí podřetězec s zadaného řetězce. Druhým parametrem i je dán začátek požadovaného podřetězce (počítáno od nuly)
//a třetí parametr n určuje délku podřetězce. Je-li index i mimo meze 0 až len(s)nebo n < 0, vrací funkce None.
//Je-li n > len(s)−𝑖, jsou jako řetězec vráceny od i-tého znaku všechny zbývající znaky řetězce.
void generateSubstr(){
  //INIT
  fprintf(stdout, "LABEL $SUBSTR\n");
  fprintf(stdout, "PUSHFRAME\n");
  fprintf(stdout, "DEFVAR LF@$RETVAL\n");
  fprintf(stdout, "MOVE LF@$RETVAL string@nil\n");/////check if this is possible, else get first char of string
  //ULOŽENIE PARAMETROV
  fprintf(stdout, "DEFVAR LF@$STRING_S\n");
  fprintf(stdout, "MOVE LF@$STRING LF@%1\n");/////check if string possibly
  fprintf(stdout, "DEFVAR LF@$POSIT_I\n");
  fprintf(stdout, "MOVE LF@$POSIT LF@%2\n");
  fprintf(stdout, "DEFVAR LF@$LENGTH_N\n");
  fprintf(stdout, "MOVE LF@$LENGTH_N LF@%3\n");

  fprintf(stdout, "DEFVAR LF@$TMPLEN\n");
  fprintf(stdout, "STRLEN LF@$TMPLEN LF@%1\n");
  //KONTROLA POZICIE
  fprintf(stdout, "DEFVAR LF@$BOOLCHECK\n");
  fprintf(stdout, "GT LF@$BOOLCHECK LF@%2 LF@$TMPLEN\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@$BOOLCHECK bool@true\n");
  fprintf(stdout, "LT LF@$BOOLCHECK LF@%2 int@-1\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@$BOOLCHECK bool@true\n");
  fprintf(stdout, "LT LF@$BOOLCHECK LF@%3 int@-1\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@$BOOLCHECK bool@true\n");
  //FUNKCIA
  //fprintf(stdout, "GETCHAR LF@$RETVAL LF@$STRING_S LF@$POSIT_I\n");
  //fprintf(stdout, "ADD LF@$POSIT_I LF@$POSIT_I int@1\n");//inkrementácia
  fprintf(stdout, "DEFVAR LF@$TMPSTR\n");
  fprintf(stdout, "ADD LF@$TMPLEN LF@$TMPLEN int@1\n");//podmienka na while loop
  //SMYČKA
  fprintf(stdout, "LABEL $WHILE_LOOP_B\n");
  fprintf(stdout, "JUMPIFEQ $WHILE_LOOP_E LF@$POSIT_I LF@$LENGTH_N\n");//skoč ak si dokončil
  fprintf(stdout, "JUMPIFEQ $WHILE_LOOP_E LF@$POSIT_I LF@$TMPLEN\n");//skoč ak je koniec stringu
  fprintf(stdout, "GETCHAR LF@$TMPSTR LF@$STRING_S LF@$POSIT_I\n");//getchar
  fprintf(stdout, "CONCAT LF@$RETVAL LF@$RETVAL LF@$TMPSTR\n");//concat stringy
  fprintf(stdout, "ADD LF@$POSIT_I LF@$POSIT_I int@1\n");//inkrementácia
  fprintf(stdout, "JUMP $WHILE_LOOP_B\n");
  //KONIEC SMYČKY
  fprintf(stdout, "LABEL $WHILE_LOOP_E\n");
  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");
  //ERROR
  fprintf(stdout, "LABEL $ERROR\n");
  fprintf(stdout, "MOVE LF@$RETVAL string@None\n");
  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");  
}
//ord(s,i)– Vrátí ordinální hodnotu (ASCII) znaku s na pozici i v řetězci. Je-lipozice mimo meze řetězce (0 ažlen(s)- 1), vrací None.
void generateOrd(){
  //INIT
  fprintf(stdout, "LABEL $ORD\n");
  fprintf(stdout, "PUSHFRAME\n");
  fprintf(stdout, "DEFVAR LF@$RETVAL\n");
  //ULOŽENIE PARAMETROV
  fprintf(stdout, "DEFVAR LF@$STRING\n");
  fprintf(stdout, "MOVE LF@$STRING LF@%1\n");/////check if string possibly
  fprintf(stdout, "DEFVAR LF@$POSIT\n");
  fprintf(stdout, "MOVE LF@$POSIT LF@%2\n");
  fprintf(stdout, "DEFVAR LF@$CHR2INT\n");
  fprintf(stdout, "DEFVAR LF@$TMPLEN\n");
  fprintf(stdout, "STRLEN LF@$TMPLEN LF@%1\n");
  //KONTROLA POZICIE
  fprintf(stdout, "DEFVAR LF@$BOOLCHECK\n");
  fprintf(stdout, "GT LF@$BOOLCHECK LF@%2 LF@$TMPLEN\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@$BOOLCHECK bool@true\n");
  fprintf(stdout, "LT LF@$BOOLCHECK LF@%2 int@0\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@$BOOLCHECK bool@true\n");
  //VÝPOČET A NÁVRAT
  fprintf(stdout, "STR2INT LF@$RETVAL LF@$STRING LF@$POSIT\n");
  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");
  //ERROR
  fprintf(stdout, "LABEL $ERROR\n");
  fprintf(stdout, "MOVE LF@$RETVAL string@None\n");
  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");

}
//chr(i)– Vrátí jednoznakový řetězec se znakem, jehož ASCII kód je zadán para-metrem𝑖. Případ, kdy je𝑖mimo interval[0; 255], vede na běhovou chybu při prácis řetězcem.
void generateChr(){
  //INIT
  fprintf(stdout, "LABEL $CHAR\n");
  fprintf(stdout, "PUSHFRAME\n");
  fprintf(stdout, "DEFVAR LF$RETVAL\n");
  //ULOŽENIE PARAMETRA
  fprintf(stdout, "DEFVAR LF@$ASC\n");
  fprintf(stdout, "MOVE LF@ASC LF@%1\n");
  //KONTROLA PARAMETRA #1
  fprintf(stdout, "DEFVAR LF@INTCHECK\n");
  fprintf(stdout, "TYPE LF@INTCHECK LF@%1\n");
  fprintf(stdout, "DEFVAR LF@INTCHECK\n");
  fprintf(stdout, "JUMPIFEQ $ERROR LF@INTCHECK string@nil\n");
  fprintf(stdout, "JUMPIFEQ $ERROR LF@INTCHECK string@string\n");
  fprintf(stdout, "JUMPIFEQ $CHARFUN LF@INTCHECK string@int\n");
  fprintf(stdout, "JUMPIFNEQ $CHARFUN LF@INTCHECK string@float\n");
  //KONVERT AK FLOAT
  fprintf(stdout, "FLOAT2INT LF@$1 LF@$1\n");
  //KONTROLA PARAMETRA #2
  fprintf(stdout, "LABEL $CHARFUN\n");
  fprintf(stdout, "DEFVAR LF@BOOLCHECK\n");
  fprintf(stdout, "LT LF@BOOLCHECK LF@%1 int@256\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@BOOLCHECK bool@false\n");
  fprintf(stdout, "GT LF@BOOLCHECK LF@%1 int@-1\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@BOOLCHECK bool@false\n");
  //VYKONANIE FUNKCIE A NÁVRAT
  fprintf(stdout, "INT2CHAR LF@RETVAL LF@%1\n");
  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");
  //CHYBA
  fprintf(stdout, "LABEL $ERROR\n");
  fprintf(stdout, "EXIT int@4\n");
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
