// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  if (!mylist) return NULL;
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  if (!l) return;
  node_t *cur = l->head;
  while (cur) {
    node_t *next = cur->next;
    free(cur);
    cur = next;
  }
  l->head = NULL;
  free(l);
}

void list_print(list_t *l) {
  if (!l) {
    printf("NULL\n"); return;}
  node_t *cur = l->head;
  while (cur) {
    printf("%d->",cur->value);
    cur = cur->next;
  }
  printf("NULL\n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  buf[0] = '\0';
  char tbuf[20];

  if (!l) {
  strcat(buf, "NULL");
  return buf;
  }

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  if (!l) return 0;
  int n=0;
  node_t *cur;
  for (cur = l->head; cur; cur = cur->next) {
    n++;
  }
  return n;  
  }

void list_add_to_back(list_t *l, elem value) {
  if (!l) return;
  node_t *n = getNode(value);
  if (!l->head) {l->head = n; return;}
  node_t *cur = l->head;
  while (cur->next) cur = cur->next;
  cur->next = n;
}

void list_add_to_front(list_t *l, elem value) {
     node_t *cur_node = (node_t *) getNode(value);

     /* Insert to front */
     node_t *head = l->head;  // get head of list

     cur_node->next = head;
     l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (!l) return;
  if (index <= 1) { list_add_to_front(l, value); return;}

  int pos = 1;
  node_t *prev = l->head;
  while(prev && pos < index -1) {prev = prev->next; pos++;}
  
  if (!prev) return;

  node_t *n = getNode(value);
  n->next = prev->next;
  prev->next =n;
}

elem list_remove_from_back(list_t *l) {
  if (!l || !l->head) return -1;
  if (!l->head->next) {
    elem v = l->head->value;
    free(l->head);
    l->head = NULL;
    return v;
  }
  node_t *prev = l->head;
  while (prev->next && prev->next->next) prev = prev->next;
  elem v = prev->next->value;
  free(prev->next);
  prev->next = NULL;
  return v;
}
elem list_remove_from_front(list_t *l) { 
  if (!l || !l->head) return -1;
  node_t *old = l->head;
  elem v = old->value;
  l->head = old->next;
  free(old);
  return v;
}
elem list_remove_at_index(list_t *l, int index) {
  if (!l || !l->head) return -1;
  if (index == 1) return list_remove_from_front(l);

  int pos = 1;
  node_t *prev = l->head;
  while (prev && pos < index -1) { prev = prev->next; pos;}
  if (!prev || !prev->next) return -1;

  node_t *target = prev->next;
  elem v = target->value;
  prev->next = target->next;
  free(target);
  return v;
}

bool list_is_in(list_t *l, elem value) {
  if (!l) return false;
  node_t *cur = l->head;
  while (cur) {
    if(cur->value == value) return true;
    cur = cur->next;
  }  
  return false;
}
elem list_get_elem_at(list_t *l, int index) {
  if (!l || index < 1) return -1; 
  int i = 1;
  node_t *cur =l->head;
  while (cur) {
    if (i == index) return cur->value;
    cur = cur->next;
    i++;
  }
  return -1;
}
int list_get_index_of(list_t *l, elem value) {
  if (!l) return -1;
  int i = 1;
  node_t *cur = l->head;
  while (cur) {
    if (cur->value == value) return i;
    cur = cur->next;
    i++;
  }
  return -1;
}

