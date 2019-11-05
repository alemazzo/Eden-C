#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifndef DIRLISTMANAGER

#define DIRLISTMANAGER

#define DIRLIST struct DirList
#define DIRLISTELEMENT struct DirListElement


struct DirList{
    //variabili
    DIRLISTELEMENT *head;
    DIRLISTELEMENT *coda;

    //funzioni
    void (*insert)(DIRLIST *l,char * key);
    void (*delete) (DIRLIST *l,char * key);
    void (*print) (DIRLIST *l);
    int (*indexof) (DIRLIST *l,char * key);
    int (*count) (DIRLIST *l);
    void (*update) (DIRLIST *l, char *prev, char *next);

};


struct DirListElement{
    DIRLISTELEMENT *prev;
    char * key;
    DIRLISTELEMENT *next;
};

DIRLIST DirList();
void List_insert(DIRLIST *l,char * key);
void List_delete(DIRLIST *l,char * key);
int List_indexof(DIRLIST *l,char * key);
void List_print(DIRLIST *l);
int List_count(DIRLIST *l);
void List_update(DIRLIST *l, char *prev, char *next);


DIRLIST DirList(){
    DIRLIST *l = malloc(sizeof(DIRLIST));
    l->coda = NULL;
    l->head = NULL;

    l->insert = List_insert;
    l->delete = List_delete;
    l->print = List_print;
    l->indexof = List_indexof;
    l->count = List_count;
    l->update = List_update;
    return *l;
};

void List_insert(DIRLIST *l, char *key){

    DIRLISTELEMENT *element = malloc(sizeof(DIRLISTELEMENT *));
    element->key = malloc(strlen(key) * sizeof(char));
    strcpy(element->key, key);
    element->prev = l->coda;
    element->next = NULL;

    if(l->head == NULL) l->head = element;

    if(l->coda != NULL){
        l->coda->next = element;
    }

    l->coda = element;
    


};

void List_update(DIRLIST *l, char *prev, char *next){
    DIRLISTELEMENT *x = l->head;
    
    while(x != NULL && x->key != prev){
        x = x->next;
    }
    if(x != NULL){
        x->key = realloc(x->key, strlen(next) * sizeof(char));
        strcpy(x->key, next);
    }

}

void List_delete(DIRLIST *l,char * key){
    DIRLISTELEMENT *x = l->head;
    while(x != NULL && x->key != key) x = x->next;
    if(x != NULL){
        if(x->next != NULL) x->next->prev = x->prev;
        x->prev->next = x->next;
    }
    free(x);

};

int List_indexof(DIRLIST *l,char * key){
    DIRLISTELEMENT *x = l->head;
    int count = 0;
    while(x != NULL && x->key != key){
        x = x->next;
        count++;
    }
    if(x == NULL) return -1;
    else return count;

};

void List_print(DIRLIST *l){
    DIRLISTELEMENT *x = l->head;
    while(x != NULL){
        printf("%s \n", x->key);
        x = x->next;
    }
};

int List_count(DIRLIST *l){
    DIRLISTELEMENT *x = l->head;
    int i = 0;
    while(x != NULL){
        i++;
        x = x->next;
    }
    return i;
};


#endif
