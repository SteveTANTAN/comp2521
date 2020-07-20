// COMP2521 20T2 Assignment 1
// Dict.c ... implementsation of Dictionary ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dict.h"
#include "WFreq.h"

typedef struct _DictNode *Link;

typedef struct  _DictNode {
   WFreq  *data;
   Link   left;
   Link   right;
   int   height;
} DictNode;

struct _DictRep {
   Link tree;
};

// create new empty Dictionary
Dict newDict()
{
   Dict new = malloc(sizeof(struct _DictRep));

   if (new == NULL) {

      fprintf(stderr, "Insufficient memory!\n");
      exit(EXIT_FAILURE);
   }
   new->tree = NULL;
   
   return new;
}

/////////////
Link newNode(char *w){
   
   

   WFreq *data = malloc(sizeof(struct _WFreq));
   if (data == NULL) {
      fprintf(stderr, "Insufficient memory!\n");
      exit(EXIT_FAILURE);
   }
   
   //copy the words
   data->word = malloc(sizeof(char)*(strlen(w) + 1));
   if (data->word == NULL) {
      fprintf(stderr, "Insufficient memory!\n");
      exit(EXIT_FAILURE);
   }
   strcpy(data->word, w);
   data->word[strlen(w)] = '\0';
   data->freq = 1;


   // creat a new link called n and , malloc for this 
   Link n = malloc(sizeof(struct _DictNode));
   if (n == NULL) {
      fprintf(stderr, "Insufficient memory!\n");
      exit(EXIT_FAILURE);
   }
   
   //connect data and n;
   n->data = data;
   
   n->left = NULL;
   n->right = NULL;
   n->height = 0;
  
   return n;
}

int height(Link n) {
    if (n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

int max (int num1, int num2) {
   return (num1>num2? num1:num2);
}


// Rotates  the  given  subtree left 
// and returns the root of the updated
// subtree.
Link rotateLeft(Link n) {
    
    if (n == NULL || n -> right == NULL) {

        return n;
    }
    Link n1 = n->right;
    
    n->right = n1->left;
    n1->left = n;
    // updata the height after rotate.
    n->height = 1 + max(height(n->left), height(n->right));
    n1->height = 1 + max(height(n1->left), height(n1->right));

    return n1;
}


// Rotates the given subtree right 
// and returns the root of  the  updated
// subtree.
Link rotateRight(Link n) {
    
   if (n == NULL || n -> left== NULL) {
      return n;
   }

   Link n1 = n->left;
    
   n->left = n1->right;
   n1->right = n;
   // updata the height after rotate.
   n->height = 1 + max(height(n->left), height(n->right));
   n1->height = 1 + max(height(n1->left), height(n1->right));
   return n1;
}


Link doInsert(Link n, char *w, WFreq *pair) {
   if (n == NULL) {
      n = newNode(w);
      pair = n->data;
   } else {
      // compare the diff word name, get its position.
      int cmp = strcmp(w, n->data->word);
      
      if (cmp < 0) {
         n->left = doInsert(n->left, w, pair);
         
      } else if (cmp > 0) {
         n->right = doInsert(n->right, w, pair);
         
      } else {
         //if this word is already here,
         //just increase its freq.
         n->data->freq++;
         pair = n->data;
         
      }

   }
   
   n->height = 1+ max(height(n->left), height(n->right));
   
   // after inseting, 
   // rebanlance the AVL tree.
   int LHeight  = height(n->left);
   int RHeight  = height(n->right);

   if ((LHeight - RHeight) >1) {

      if (strcmp(w, n->left->data->word) > 0) {
         n->left = rotateLeft(n->left);
      }
      n = rotateRight(n);

    } else if ((RHeight - LHeight) >1) {
      if (strcmp(w, n->right->data->word) < 0) {
         n->right = rotateRight(n->right);
      }
      n = rotateLeft(n);

    }

    return n;

}

///////////////my function closed/////////////////





// insert new word into Dictionary
// return pointer to the (word,freq) pair for that word
WFreq *DictInsert(Dict d, char *w)
{
   WFreq *pair = NULL;
   d->tree = doInsert(d->tree, w, pair);
   return pair;
}





///////////////my function  for DictFind///////////////////
WFreq *dodictfindng(Link node, char *w) {
   //if there is nothing inside
   WFreq * finding = NULL; 

   if (node != NULL){
      char *w2 = node->data->word;

      //compare the diff name,
      //get its position
      int cmp = strcmp(w, w2);
      if (cmp == 0) { 
         finding = node->data;
      } 
      
      if (cmp < 0) {
         return   dodictfindng(node->left, w);
      }  
      
      if(cmp > 0){
         return dodictfindng(node->right, w);
      } 

   }
   return finding;

}
///////////////my function closed/////////////////
// find Word in Dictionary
// return pointer to (word,freq) pair, if found
// otherwise return NULL






WFreq *DictFind(Dict d, char *w)
{  
   // if the dict is empty return null
   // or do dictfinding
   return (d == NULL? (WFreq *)NULL
            : dodictfindng(d->tree, w));
}





/////////////////My Fuction for TopN//////////////

// this fuction is used to check order
// if the w1's freq is less than w2, we return 1 for true.
// if w1 and w2 have the same freq,
// we check for the word names, if w1 has longer word name,
// or alpha (ASCII) larger, return 1, for ture.
int checkorder (WFreq w1, WFreq w2) {
   int temp = 0;
   if ((w1.freq < w2.freq)
   || (w1.freq == w2.freq 
      && strcmp(w1.word, w2.word) > 0)) {
         temp = 1;
         
      }

   return temp;
}

// using infix order to add the number into array
void dofindtop(Link node, WFreq *wfs, int max, int *num) {
   
   if (node != NULL) {
      
      dofindtop(node->left, wfs, max, num);
      //adding  the word into array;
      // if the array is not full;
      if (*num < max) {
         wfs[*num] = *(node->data);
         (*num)++;
      
      } else {
         // if the wfs is full, we check the words
         // inside the wfs, to compare their freqs and names.
         // using a better one to fresh it.

         int change = 0;
         WFreq changeword = wfs[0];
         for (int temp = 0; temp < max ; temp++) {
            if (checkorder(wfs[temp], wfs[change])){ 
                  changeword = wfs[temp];
                  change = temp; 
            } 
                   
         }

         // if the word we found is able to meet requirements
         // (this wfs[change] is smallest in whole array
         // and it is smaller than the node)
         if (node->data->freq > changeword.freq)
            wfs[change] = *(node->data);
      }
      
      dofindtop(node->right, wfs, max, num);
   }

}


// sort the final version of wfs, 
// from most freq to least
// for the same freq,
// sort from shortest word length to largest.
void SortPrintList(WFreq *wfs, int number) {
    for (int num1 = 0; num1 < number - 1; num1 ++) {
        for (int num2 = 0; num2 < (number - 1 - num1); num2++) {
            if (checkorder(wfs[num2], wfs[num2 + 1])) {          
               WFreq temp = wfs[num2];
               wfs[num2] = wfs[num2 + 1];
               wfs[num2 + 1] = temp;

            }
        }
    }
}
///////////////my function closed/////////////////





// find top N frequently occurring words in Dict
// input: Dictionary, array of WFreqs, size of array
// returns: #WFreqs in array, modified array
int findTopN(Dict d, WFreq *wfs, int n)
{
   int number = 0;
   
   dofindtop(d->tree, wfs, n, &number);

   SortPrintList(wfs, number);
   return number;
}






/////////////////my function////////
// using infix way to print out.
void printdictInfix(Link node) {
   if (node != NULL) {
      printdictInfix(node->left);
      printf("word: %s  freq: %d\n", node->data->word, node->data->freq);
      printdictInfix(node->right);
   }
}
///////////////my function closed/////////////////


// print a dictionary
void showDict(Dict d)
{
   printdictInfix(d->tree);
}

