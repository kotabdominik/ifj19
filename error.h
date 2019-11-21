/**
  * error.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: header for errors
  *
  */

  #ifndef _ERROR_H_
  #define _ERROR_H_

  #define OK 0
  #define LEXICAL_ERR 1 //chyba v programu v rámci lexikální analýzy
  #define PARSING_ERR 2 //chyba v programu v rámci syntaktické analýzy
  #define SEM_DEF_ERR 3 //sémantická chyba v programu – nedefinovaná funkce/proměnná, pokus o redefinici funkce/proměnné, atp.
  #define SEM_RUN_ERR 4 //sémantická/běhová chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech
  #define SEM_PAR_ERR 5 //sémantická chyba v programu – špatný počet parametrů u volání funkce.
  #define SEM_MISC_ERR 6 //ostatní sémantické chyby
  #define DIVISION_BY_ZERO 9 //běhová chyba dělení nulou.
  #define INTERN_ERR 99 //interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti, atd.).

  #define ARGS_ERR 50 // chybny vstup na prikazove radce
  #define ANAL_ERR 51 // chyba při analýze (lexikální, syntaktická) vstupního kódu v IFJcode19
  #define SEM_ERR  52 // chyba při sémantických kontrolách vstupního kódu v IFJcode19
  #define RUN_SEM_ERR 53 //běhová chyba interpretace – špatné typy operandů
  #define RUN_ACC_ERR 54 // běhová chyba interpretace – přístup k neexistující proměnné (rámec existuje)
  #define RUN_FRAME_ERR 55 // běhová chyba interpretace – rámec neexistuje (např. čtení z prázdného zásobníkurámců
  #define RUN_MISVAL_ERR 56 // běhová chyba interpretace – chybějící hodnota (v proměnné, na datovém zásob-níku, nebo v zásobníku volání)
  #define RUN_BAD_VAL_ERR 57 // běhová chyba interpretace – špatná hodnota operandu (např. dělení nulou, špatnánávratová hodnota instrukce EXIT)
  #define RUN_STRING_ERR 58// běhová chyba interpretace – chybná práce s řetězcem
  #define INTERN_INTER 60// interní chyba interpretu tj. neovlivněná vstupním programem (např. chyba alo-kace paměti, chyba při otvírání souboru s řídicím programem atd.)

#endif
