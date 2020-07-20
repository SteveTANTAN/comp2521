// COMP2521 20T2 Assignment 1
// tw.c ... compute top N most frequent words in file F
// Usage: ./tw [Nwords] File
// steve Tan.
// z5237560
// final version


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "Dict.h"
#include "WFreq.h"
#include "stemmer.h"

#define STOPWORDS "stopwords"
#define MAXLINE 1000
#define MAXWORD 100

#define STARTING "*** START OF"
#define ENDING   "*** END OF"

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')


//////my function/////////
void insertword(Dict wfreqs, Dict stopwords, char *word) ;


int main( int argc, char *argv[])
{
   // TODO ... add any variables you need

   FILE  *in;         // currently open file
   Dict   stopwords;  // dictionary of stopwords
   Dict   wfreqs;     // dictionary of words from book
   WFreq *results;    // array of top N (word,freq) pairs
                      // (dynamically allocated)

   char *fileName;    // name of file containing book text
   int   nWords;      // number of top frequency words to show

   char   line[MAXLINE];  // current input line
   char   word[MAXWORD];  // current word

   // process command-line args
   switch (argc) {
   case 2:
      nWords = 10;
      fileName = argv[1];
      break;
   case 3:
      nWords = atoi(argv[1]);
      if (nWords < 10) nWords = 10;
      fileName = argv[2];
      break;
   default:
      fprintf(stderr,"Usage: %s [Nwords] File\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   
   // build stopword dictionary
   
   in = fopen("stopwords", "r");
   stopwords = newDict();
   
   
   if ( in != NULL) {
      while (fgets(line,MAXLINE,in) != NULL) {

         line[strlen(line) - 1] = '\0';       
         DictInsert(stopwords, line);
         
      }    
   } else {
      
      fprintf(stderr, "Can't open stopwords\n");
      exit(EXIT_FAILURE);
   }
   fclose(in);
   

   
   // scan File, up to start of text
   in = fopen(fileName, "r");
   wfreqs = newDict();
   if ( in != NULL) {
      bool readyread = false;
      
      while (fgets(line,MAXLINE,in) != NULL) {
         line[strlen(line)-1] ='\0';
         
         //if the line is the starting line
         //skip it and run the reading and inserting.
         if (strncmp(line, STARTING, strlen(STARTING)) == 0) {
            readyread = true;
            continue;
         }
         // if the ending line, just exit the loop.
         if (strncmp(line, ENDING, strlen(ENDING)) == 0) {
            break;
         }
         
         // scan File reading words and accumualting counts
         // adding the word into dic
         if (readyread == true) {
            int length = strlen(line);
            int num = 0;
            word[0] = '\0';
            for (int temp = 0; temp < length; temp++) {
               // if it is the wordchar we start to record it
               // then transfor to lower.
               if (isWordChar(line[temp])) {
                  word[num] = tolower(line[temp]);
                  num++;
                  word[num] = '\0';
               
               }else {
                  insertword(wfreqs, stopwords, word);
                  word[0] = '\0';
                  num = 0;
               }
            }
            insertword(wfreqs, stopwords, word); 
         }
      }


      // if we did not read the the "start line" at the end of 
      // loop, do exiting.
      if (readyread == false) {
         fprintf(stderr, "Not a Project Gutenberg book\n");
         exit(EXIT_FAILURE);
      }

   // if in == NULL, means the file is not be opened,
   // do exiting.   
   } else {
      fprintf(stderr, "Can't open %s\n",fileName);
      exit(EXIT_FAILURE);
   }
   fclose(in);



   // compute and display the top N words
   results = malloc(sizeof(WFreq) * nWords);
   int number = findTopN(wfreqs, results, nWords);

   for (int temp = 0; temp < number; temp++) {
      printf("%7d %s\n", results[temp].freq, results[temp].word);
   }
   // done
   free(results);
   return EXIT_SUCCESS;
}

////////////////////////////////
//        Help fuction        //
////////////////////////////////
void insertword(Dict wfreqs, Dict stopwords, char *word) {
   //first time, if it is the only short signs, just ignored it.
    if (strcmp(word, "'") == 0 
    || strcmp(word, "-") == 0 || isdigit(word[0])) {
       return;             
   } 

   // then we check if it is in the stopnwords
   // and using stem to transfor it 
   if (DictFind(stopwords, word) == NULL && strlen(word) > 0) {
      word[stem(word, 0, (strlen(word) - 1)) + 1] = '\0';
      DictInsert(wfreqs, word);  
   }
}