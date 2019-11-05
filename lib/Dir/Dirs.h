
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "DirList.h"

#ifndef DIRSMANAGER

#define DIRSMANAGER

//Return if [dir] is a directory
#define IS_DIR(dir) (opendir(dir) != NULL)

//Number of files in [dir]
#define DIR_FILES_COUNT(dir) get_dir_files_count(dir)

//Number of directories in [dir]
#define DIR_DIRS_COUNT(dir) get_dir_dirs_count(dir)

//Files in [dir]
#define DIR_FILES(dir) get_files_in_dir(dir)

//Diresctories in [dir]
#define DIR_DIRS(dir) get_dirs_in_dir(dir)

//All directories in [dir] and subdirectory.
#define ALL_DIRS(dir, count) get_all_dirs_in_dir(dir, count)

//All files in [dir] and subdirectories
#define ALL_FILES(dir, count) get_all_files_in_all_dirs(dir, count)

/*
Ritorna il numero di files contenuti in una determinata directory.
*/
int get_dir_files_count(char *dir){

    if(!IS_DIR(dir))
        return 0;
    
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(dir);
    
    while( (entry = readdir(folder)) ){
        int new_dimension = (strlen(dir) + 2 + strlen(entry->d_name));
        char *new_file = malloc(new_dimension * sizeof(char)); 
        memset(new_file, '\0', new_dimension);
        strcat(new_file, dir);
        strcat(new_file, "\\/");
        strcat(new_file, entry->d_name);
        if(!IS_DIR(new_file)) files++;
    }

    closedir(folder);
    return files; //tolgo il file '.' e '..'
}


/*
Ritorna il numero di directories contenuti in una determinata directory.
*/
int get_dir_dirs_count(char *dir){

    if(!IS_DIR(dir))
        return 0;
    
    DIR *folder;
    struct dirent *entry;
    int dirs = 0;

    folder = opendir(dir);
    
    while( (entry = readdir(folder)) ){
        char new_dir[strlen(dir) + 2 + strlen(entry->d_name)]; 
        memset(new_dir, '\0', strlen(dir) + 2 + strlen(entry->d_name));
        strcat(new_dir, dir); 
        strcat(new_dir, "\\/"); 
        strcat(new_dir, entry->d_name);
        if(IS_DIR(new_dir) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) dirs++;
    }
        

    closedir(folder);
    return dirs; 
}

/*
Ritorna un array con i nomi dei file nella direcotry.
*/
char ** get_files_in_dir(char *dir){

    if(!IS_DIR(dir))
        return NULL;

    DIR *folder;
    struct dirent *entry;
    int len = DIR_FILES_COUNT(dir);
    
    folder = opendir(dir);
    
    char ** list = malloc((len + 1) * sizeof(char*));
    int index = 0;
    

    while( (entry = readdir(folder)) ){
        int new_dimension = (strlen(dir) + 2 + strlen(entry->d_name));
        char *new_file = malloc(new_dimension * sizeof(char)); 
        memset(new_file, '\0', new_dimension);
        strcat(new_file, dir);
        strcat(new_file, "\\/");
        strcat(new_file, entry->d_name);
        if(!IS_DIR(new_file)){
            list[index] = malloc(strlen(new_file) * sizeof(char));
            strcpy(list[index++], new_file);            
        }
    }

    closedir(folder);
    return list;

}

/*
Ritorna un array di nomi di directories in una directoy.
*/
char ** get_dirs_in_dir(char *dir){

    if(!IS_DIR(dir))
        return NULL;

    DIR *folder;
    struct dirent *entry;
    int len = DIR_DIRS_COUNT(dir);
    
    folder = opendir(dir);
    
    char ** list = malloc((len + 1) * sizeof(char*));
    int index = 0;
    
    while( (entry = readdir(folder)) ){
        int new_dimension = (strlen(dir) + 2 + strlen(entry->d_name));
        char *new_dir = malloc(new_dimension * sizeof(char)); 
        memset(new_dir, '\0', new_dimension);
        strcat(new_dir, dir);
        strcat(new_dir, "\\/");
        strcat(new_dir, entry->d_name);
        if(IS_DIR(new_dir) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){            
            list[index] = malloc(strlen(new_dir) * sizeof(char));
            strcpy(list[index++], new_dir);

        }
    }

    list[index] = NULL;

    closedir(folder);
    return list;

}

/*
Scansione ricorsivamente le directories a pratire da quella
passata e aggiunge ogni nuova directory alla lista passata
come parametro.
*/
void recursive_dirs_search(char *dir, DIRLIST *list){

    char ** dirs = DIR_DIRS(dir);
    int n = DIR_DIRS_COUNT(dir);
    for(int i = 0; i < n; i++){
        list->insert(list, dirs[i]);
    }   

    for(int i = 0; i < n; i++){
        recursive_dirs_search(dirs[i], list);
    }
    
    return;
}

/*
Ritorna un array contenente il nome di tutte le directories
a partire da quella passata.
Inoltra assegna la lunghezza dell'array al parametro count.
*/
char ** get_all_dirs_in_dir(char *dir, int *count){
    
    if(!IS_DIR(dir)){
        *count = 0;
        return NULL;
    }

    DIRLIST *res = malloc(sizeof(DIRLIST));
    *res = DirList();  
    res->insert(res, dir); 
    recursive_dirs_search(dir, res);

    int len = res->count(res); //1 = dir base passata.
    char ** results = malloc((len) * sizeof(char*));
    int index = 0;

    DIRLISTELEMENT *x = res->head;
    while(x != NULL){
        results[index] = malloc(strlen(x->key) * sizeof(char));
        strcpy(results[index++], x->key);
        x = x->next;
    }
    

    *count = len;
    return results;    
}

/*
Ritorna un array contenente il nome di tutti i file nelle directories
a partire da quella passata.
Inoltra assegna la lunghezza dell'array al parametro count.
*/
char ** get_all_files_in_all_dirs(char *dir, int *count){
    
    if(!IS_DIR(dir)){
        *count = 0;
        return NULL;
    }

    int num = 0;
    char ** directories = ALL_DIRS(dir, &num);
    int conta = 0;

    //DA OTTIMIZZARE DI BRUTTO
    for (size_t i = 0; i < num; i++)
        conta += DIR_FILES_COUNT(directories[i]);
    
    char ** files = malloc((conta) * sizeof(char*));
    int counter_files = 0;
    for (size_t i = 0; i < num; i++){
        char **dirfiles = DIR_FILES(directories[i]);
        for(int j = 0; j < DIR_FILES_COUNT(directories[i]); j++){
            char *arr = dirfiles[j];
            int len = strlen(dirfiles[j]);
            files[counter_files] = malloc(len * sizeof(char));
            strcpy(files[counter_files++], dirfiles[j]);
        }        
    }     
    
    *count = conta;
    return files;

}

#endif // !DIRS