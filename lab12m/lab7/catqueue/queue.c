// $Id: queue.c,v 1.33 2015-02-26 12:37:44-08 - - $
//Adam Paz
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"


typedef struct queue_node queue_node;
struct queue_node {
   queue_item_t item;
   queue_node *link;
};

struct queue {
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
    queue *this = malloc (sizeof(queue));
    assert (this != NULL);
    this->front = NULL;
    this->rear = NULL;
    return this;
}

void free_queue (queue *this) {
   assert (isempty_queue (this));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
    queue_node *node = malloc (sizeof(queue));
    node->item = item;    
    if (this->front == NULL){
        this->front = node;
   } else this->rear->link = node;
    this->rear = node;
    }

queue_item_t remove_queue (queue *this) {
   queue_item_t removed =  this->front->item; 
   queue_node *tmp = this->front;
   this->front = this->front->link;
   free(tmp);
   return removed;
}

bool isempty_queue (queue *this) {
   return this->front == NULL;
}

