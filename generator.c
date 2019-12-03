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


///////Personal notes
//pushframe spravi z TF LF
//popframe prehlasi LF za TF
//za funckiou (return) MOVE GF@VYSLEDOK TF@RETVAL
//nemozno predefinovavat stejnu premennu
//whitespaces v stringoch su nahradene escape seqs, ' ' = \032 '\n' = \010
///////

//TODO
//urobit print -> cez pointre od tsundri nacitat globals do stacku pred zavolanim funkcie, ktory budem v print loope popovat

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "symtable.h"
#include "scanner.h"
#include "expressions.h"
#include "list.h"
#include "generator.h"



void degenerate(tDLList *list){
  fprintf(stdout, ".IFJcode19\n");
  fprintf(stdout, "JUMP $$MAIN\n");
  generateBuiltIn();
  generateInstructionREE(list);
};

//||======================================================||//
//||=============== Věstavené funkce start ===============||//

void generateInputs(){

  fprintf(stdout, "LABEL $ALFA\n");
  fprintf(stdout, "PUSHFRAME\n");
  fprintf(stdout, "DEFVAR LF$RETVAL\n");

  fprintf(stdout, "READ LF@$RETVAL string\n");
  fprintf(stdout, "PUSHS LF@$RETVAL\n");

  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");
}

void generateInputi(){
  fprintf(stdout, "LABEL $BETA\n");
  fprintf(stdout, "PUSHFRAME\n");
  fprintf(stdout, "DEFVAR LF$RETVAL\n");

  fprintf(stdout, "READ LF@$RETVAL int\n");
  fprintf(stdout, "PUSHS LF@$RETVAL\n");

  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");

}

void generateInputf(){

  fprintf(stdout, "LABEL $GAMA\n");
  fprintf(stdout, "PUSHFRAME\n");
  fprintf(stdout, "DEFVAR LF$RETVAL\n");

  fprintf(stdout, "READ LF@$RETVAL float\n");
  fprintf(stdout, "PUSHS LF@$RETVAL\n");

  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");

}

void generatePrint(int parCounter){

    fprintf(stdout, "LABEL $DELTA\n");
    fprintf(stdout, "DEFVAR LF$RETVAL\n ");
    fprintf(stdout, "DEFVAR LF$TMPVAL\n ");
    for (int i = 0; i < parCounter; i++)
    {
      fprintf(stdout, "POPS LF@$TMPVAL\n ");
      fprintf(stdout, "WRITE LF@$TMPVAL\n");
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

      fprintf(stdout, "STRLEN LF@$RETVAL LF@$1\n"); ///premenne parametrov su MEME (zapis cislami)
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
  fprintf(stdout, "MOVE LF@$RETVAL string@\n");/////this shoudda be var into string init, by example_while.src
  //ULOŽENIE PARAMETROV
  fprintf(stdout, "DEFVAR LF@$STRING_S\n");
  fprintf(stdout, "MOVE LF@$STRING LF@$1\n");/////check if string possibly
  fprintf(stdout, "DEFVAR LF@$POSIT_I\n");
  fprintf(stdout, "MOVE LF@$POSIT LF@$2\n");
  fprintf(stdout, "DEFVAR LF@$LENGTH_N\n");
  fprintf(stdout, "MOVE LF@$LENGTH_N LF@$3\n");

  fprintf(stdout, "DEFVAR LF@$TMPLEN\n");
  fprintf(stdout, "STRLEN LF@$TMPLEN LF@$1\n");
  //KONTROLA POZICIE
  fprintf(stdout, "DEFVAR LF@$BOOLCHECK\n");
  fprintf(stdout, "GT LF@$BOOLCHECK LF@$2 LF@$TMPLEN\n");
  fprintf(stdout, "JUMPIFEQ $ERROR LF@$BOOLCHECK bool@true\n");
  fprintf(stdout, "LT LF@$BOOLCHECK LF@$2 int@-1\n");
  fprintf(stdout, "JUMPIFEQ $ERROR LF@$BOOLCHECK bool@true\n");
  fprintf(stdout, "LT LF@$BOOLCHECK LF@$3 int@-1\n");
  fprintf(stdout, "JUMPIFEQ $ERROR LF@$BOOLCHECK bool@true\n");
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
  fprintf(stdout, "MOVE LF@$STRING LF@$1\n");/////check if string possibly
  fprintf(stdout, "DEFVAR LF@$POSIT\n");
  fprintf(stdout, "MOVE LF@$POSIT LF@$2\n");
  fprintf(stdout, "DEFVAR LF@$CHR2INT\n");
  fprintf(stdout, "DEFVAR LF@$TMPLEN\n");
  fprintf(stdout, "STRLEN LF@$TMPLEN LF@$1\n");
  //KONTROLA POZICIE
  fprintf(stdout, "DEFVAR LF@$BOOLCHECK\n");
  fprintf(stdout, "GT LF@$BOOLCHECK LF@$2 LF@$TMPLEN\n");
  fprintf(stdout, "JUMPIFEQ $ERROR LF@$BOOLCHECK bool@true\n");
  fprintf(stdout, "LT LF@$BOOLCHECK LF@$2 int@0\n");
  fprintf(stdout, "JUMPIFEQ $ERROR LF@$BOOLCHECK bool@true\n");
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
  fprintf(stdout, "MOVE LF@ASC LF@$1\n");
  //KONTROLA PARAMETRA #1
  fprintf(stdout, "DEFVAR LF@INTCHECK\n");
  fprintf(stdout, "TYPE LF@INTCHECK LF@$1\n");
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
  fprintf(stdout, "LT LF@BOOLCHECK LF@$1 int@256\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@BOOLCHECK bool@false\n");
  fprintf(stdout, "GT LF@BOOLCHECK LF@$1 int@-1\n");
  fprintf(stdout, "JUMPIFEQ $ERROR $LF@BOOLCHECK bool@false\n");
  //VYKONANIE FUNKCIE A NÁVRAT
  fprintf(stdout, "INT2CHAR LF@RETVAL LF@$1\n");
  fprintf(stdout, "POPFRAME\n");
  fprintf(stdout, "RETURN\n");
  //CHYBA
  fprintf(stdout, "LABEL $ERROR\n");
  fprintf(stdout, "EXIT int@4\n");
}

//||=============== Věstavené funkce konec ===============||//
//||======================================================||//

void generateBuiltIn(){
  void generateInputs();
  void generateInputi();
  void generateInputf();
  void generateLen();
  void generateSubstr();
  void generateOrd();
  void generateChr();
}

///potrebujem info k typom
//nedeklarujem, len priradujem

/*
void generateAssign(tDLList*list){
  if(list->First->Instruction.addr2 == INT){
    fprintf(stdout, "PUSHS int@%d\n", list->First->Instruction.addr1 );
  }
  else if (list->First->Instruction.addr2 == FLOAT){
    fprintf(stdout, "PUSHS float@%a\n", list->First->Instruction.addr1 );
  }
  else if (list->First->Instruction.addr2 == LITERAL){
    fprintf(stdout, "PUSHS string@%s\n", list->First->Instruction.addr1 );
  }
}

*/

/*void generateGFVariable(tDLList*list){
  printf("DEFVAR LF@$VAR%p\n",list->First->Instruction.addr1);
}*/


void generateInstructionREE(tDLList*list){
    int *parCounter;
    for (;list->First != NULL;list->First = list->First->rptr){
        switch(list->First->Instruction.instType){
          case(I_INPUTS):
            generateInputs();
            fprintf(stdout, "MOVE LF@$VAR%p TF@RETVAL\n",list->First->Instruction.addr1);
            break;
          case(I_INPUTI):
            generateInputi();
            fprintf(stdout, "MOVE LF@$VAR%p TF@RETVAL\n",list->First->Instruction.addr1);
            break;
          case(I_INPUTF):
            generateInputf();
            fprintf(stdout, "MOVE LF@$VAR%p TF@RETVAL\n",list->First->Instruction.addr1);
            break;
          case(I_LEN):
            generateLen();
            fprintf(stdout, "MOVE LF@$VAR%p TF@RETVAL\n",list->First->Instruction.addr1);
            break;
          case(I_SUBSTR):
            generateSubstr();
            fprintf(stdout, "MOVE LF@$VAR%p TF@RETVAL\n",list->First->Instruction.addr1);
            break;
          case(I_ORD):
            generateOrd();
            fprintf(stdout, "MOVE LF@$VAR%p TF@RETVAL\n",list->First->Instruction.addr1);
            break;
          case(I_CHR):
            generateChr();
            fprintf(stdout, "MOVE LF@$VAR%p TF@RETVAL\n",list->First->Instruction.addr1);
            break;
          case(I_PRINT):
            parCounter = list->First->Instruction.addr2;  ////////////////////////dohodni sa s jindrom
            for (int i = 0; i < *parCounter; i++){
              fprintf(stdout, "PUSHS string@%s\n", list->First->Instruction.addr3[i]->elementType.variable->value.string);
            }
            generatePrint(*parCounter);
            break;
          case(I_IF):

            break;
          case(I_WHILE):

            break;
        }
    }
}

/*
void generateAdd(){
  printf("MOVE GF@$VAR%p\n",list->First->Instruction.addr1);
}


///na IF potrebujem nejako vediet indent že dokedy vykonavat funckie vo vnutri, alebo
///potrebujem vediet prechody, teda Zaciatok IF , ELSE , Koniec IF a to niekde pocitat v pripade vnutornych IFov
///nasledne mozem volat generateInstruction rekurzivne...? Asi ano..
void generateIf(){

  //zistit condition

  fprintf(stdout, "JMPIFNEQ ELSE%p PODMIENKA\n",Nejaka adresa pointera);
  generateInstruction(); //dokym nenajdem rovnaky indent
  fprintf(stdout, "JUMP END%p\n",Ta ista adresa pointera);
  fprintf(stdout, "LABEL ELSE%p \n",Ta ista adresa pointera);
  generateInstruction(); //dokym nenajdem rovnaky indent
  fprintf(stdout, "LABEL END%p \n",Ta ista adresa pointera);

}

void generateWhile(){

  fprintf(stdout, "LABEL WHILE$BEGIN$%p\n", nejake origi uniq meme);
  fprintf(stdout, "CREATEFRAME\n"); ////pre nove var memecka

  for (int i = 0; i < count; i++) { ///daky loop na vars
    printf("DEFVAR TF@$VAR%p\n",dake id meme);
    printf("MOVE TF@$VAR%p LF@$VAR%p\n",cez dake to id, vsetky by mali byt rovnake);
  }
  fprintf(stdout, "PUSHFRAME\n");

  //tu dako zistit condition do loopu
  //XXXX

  fprintf(stdout, "JUMPIFEQ WHILE$END$%p bool@true ?!?!?!\n", nejake origi uniq meme);

  generateInstruction(); //dokym nenajdem dedent

  fprintf(stdout, "POPFRAME\n");
  //Pred jumpom vratit vars ako premenne
  for (int i = 0; i < count; i++) { ///daky loop na vars
    printf("MOVE LF@$VAR%p TF@$VAR%p\n",cez dake to id, vsetky by mali byt rovnake);
  }
  //
  fprintf(stdout, "JUMP WHILE$BEGIN$%p\n", nejake origi uniq meme);
  fprintf(stdout, "LABEL WHILE$END$%p\n", nejake origi uniq meme (moze byt rovnake v instancii) );

  fprintf(stdout, "POPFRAME\n");
}*/
