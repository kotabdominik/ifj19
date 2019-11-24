/**
  * absTree.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: abstraktní strom pro uchování věcí
  *
  */

#include "token.h"
#include "absTree.h"
#include <stdio.h>
#include <stdlib.h>

ATLeaf *make_leaf(ATData data){
  ATLeaf *new_leaf = (ATLeaf *) malloc(sizeof(struct atleaf));
  if(new_leaf == NULL){
    fprintf(stderr, "%s\n", "yall maloc selhal");
  }

  new_leaf->data = data;
  new_leaf->left = NULL;
  new_leaf->right = NULL;

  return new_leaf;
}

ATLeaf *make_tree(ATLeaf *leaf_1, ATLeaf *leaf_2, ATData data){
  ATLeaf *new_tree = (ATLeaf *) malloc(sizeof(struct atleaf));
  if(new_tree == NULL){
    fprintf(stderr, "%s\n", COMPILER_MESSAGE);
  }

  new_tree->data = data;
  new_tree->left = leaf_1;
  new_tree->right = leaf_2;

  return new_tree;
}

void dispose_at(ATLeaf *leaf){
  if (leaf == NULL){
    }else{
      while (leaf != NULL){
        dispose_at(leaf->left);
        dispose_at(leaf->right);
        free(leaf);
        leaf = NULL;
      }
  }
}
