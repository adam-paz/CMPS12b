// $Id: hashset.c,v 1.9 2014-05-15 20:01:08-07 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

typedef struct hashnode hashnode;
struct hashnode {
   char *word;
   hashnode *link;
};

struct hashset {
   size_t size;
   size_t load;
   hashnode **chains;
};

hashset *new_hashset (void) {
   hashset *this = malloc (sizeof (struct hashset));
   assert (this != NULL);
   this->size = HASH_NEW_SIZE;
   this->load = 0;
   size_t sizeof_chains = this->size * sizeof (hashnode *);
   this->chains = malloc (sizeof_chains);
   assert (this->chains != NULL);
   memset (this->chains, 0, sizeof_chains);
   DEBUGF ('h', "%p -> struct hashset {size = %zd, chains=%p}\n",
                this, this->size, this->chains);
   return this;
}

  
void free_hashset (hashset *this){
      for (size_t count = 0; count < this->size; count++){
          hashnode *curr;
          while(this->chains[count] != NULL){
             curr = this->chains[count];
             this->chains[count] = this->chains[count]->link;
             free(curr);
          }
      }
         memset (this->chains, 0, this->size * sizeof (char*));
         free (this->chains);
         memset (this, 0, sizeof (struct hashset));
         free (this);
}
                  



void sizedup(hashset *this){
   size_t filled = this->size; //tracks oldi forloop
   size_t full  = (2 * this->size) +1;// changes size
   hashnode **array = malloc(full * sizeof (hashnode*));
   hashnode *point= malloc(sizeof(hashnode));
   hashnode *curr = malloc(sizeof(hashnode));
   hashnode *newpoint = malloc(sizeof(hashnode));
   hashnode *p2 = malloc(sizeof(hashnode));
   for(size_t fulli = 0; fulli < full; fulli++){
      array[fulli] = NULL;
   }
   
   for(size_t inc = 0; inc <filled ;inc++){
      while (this->chains[inc] != NULL) {
         assert(this->chains[inc] != NULL);
         size_t hash_ind = strhash(this->chains[inc]->word)%full;
         point = array[hash_ind];
         curr = this->chains[inc];
         if (array[hash_ind] == NULL) {
            array[hash_ind] = curr;
            this->chains[inc] = this->chains[inc]->link;
            array[hash_ind] ->link= NULL;
         } else {
             while (point->link !=NULL ){ //find insertion point
                point = point->link;
             }
             point->link = curr;
             newpoint = curr->link;
             curr->link = p2;
             this->chains[inc] = newpoint;
             curr->link = NULL;
            
          }
      }
   }
   this->size = full;
   this->chains = array;
}


void xbug(hashset *this, bool twox){
   int counter[10];
   size_t chaincount = 1;
   for(int new = 0; new < 10; new++) {//init all to 0
      counter[new] = 0;
   }
   for(size_t count = 0; count < this->size; count++){
      chaincount = 1;
      hashnode *curr = this->chains[count];
      if(curr != NULL){
         if (this->chains[count]->link == NULL){
            counter[chaincount] ++;
            if(twox)printf("array[%10zd] = %20lu \"%s\"\n",
                        count,strhash(curr->word),curr->word );
         } else { 
            if(twox) {
                printf("array[%10zd] = %20lu \"%s\"\n",
                    count ,strhash(curr->word) ,curr->word );
            }
            while(curr->link!= NULL){
                curr = curr->link;
                chaincount ++;
                if(twox) {
                   printf("%17s = %20lu \"%s\"\n", " ",
                     strhash(curr->word), curr->word);
                }  
           }
         counter[chaincount]++;
         }
      }
   }
   if(!twox){
      printf("%zd words in the hash set\n",this->load);
      printf("%zd size of the hash array\n", this->size);
      for(int inc = 0; inc < 10; inc++){
         if (counter[inc] != 0) 
            printf("%d chains of size %d\n", counter[inc], inc);
      }
   }
}

void put_hashset (hashset *this, const char *obj) {
   if( has_hashset (this, obj)) return;
   char *item = strdup(obj);
   size_t index = strhash(item)%this->size;
   hashnode *tmp = malloc (sizeof(hashnode));
   this->load++;
   tmp-> word = (char*)item;
   tmp->link = NULL;
   hashnode *curr = this->chains[index];
    if (this->chains[index] == NULL) {
       this->chains[index] = tmp;
   } else {
        for(;curr == NULL;){
              curr = curr->link;
        }
        curr->link = tmp;
   } 
   if(this->load *2 > this->size) 
      sizedup(this);
}

bool has_hashset (hashset *this, const char *item) {
   size_t hash_index = strhash (item) % this->size;
   hashnode *curr = this->chains[hash_index];
   while(curr!= NULL){
      int cmp = strcmp(curr->word, item);
      if (cmp == 0)  return true;
      curr = curr->link;
   }
   return false;
}

