/**
  * parser.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: header file for parser (heart of compiler (RIP))
  *
  */

#ifndef _PARSER_H_
#define _PARSER_H_

#include "scanner.h"
#include "symtable.h"

/*
 * structure for parser token that holds info needed in parser
 */
typedef struct
{
	Sym_table global_table;		/// Global symbol table
	Sym_table local_table;		/// Local symbol table

	token token;				/// Token

	TData* current_id;			/// ID of currently processed function
	TData* lhs_id;				/// ID of left-hand-side variable
	TData* rhs_id;				/// ID of right-hand-side function (expression?)

	unsigned param_index;		/// Index of currently checked param
	int label_index;			/// Index for generating unique labels.
	int label_deep;				/// Deep of labes.

	bool in_function;			/// Defines if the parser is in function
	bool in_declaration;		/// Defines if param rule should add or check it's params
	bool in_while_or_if;		/// Defines if the parser is in construction while, if or then
	bool non_declared_function;	/// Function that has been only defined
} parserToken;
/* needs to repair ... cuz its not completely mine */ // ---------------------------------

#endif
