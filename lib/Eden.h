#include <string.h>
#include <time.h>

#include "Dir/Dirs.h"
#include "File/File.h"

#define RANDOM(min, max) (int)(min + (rand() + time(NULL)) % (max - min + 1))
#define RANDOM_STRING(length) randomString(length)
#define EDEN struct Eden
#define EDENIZE(eden, caoslevel) Edenize(eden, caoslevel)


char * randomString(int length){
    char *charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int setlen = strlen(charset);

    char *output = malloc((length + 1) * sizeof(char));
    memset(output, '\0', length + 1);
    for(int i = 0; i < length; i++){
        int n = RANDOM(0, setlen - 1);
        char ch = charset[n];        
        output[i] = ch;
    }
    
    return output;
}

struct Eden{
    char *basedir;

    char **files;
    int filecount;

    char **dirs;
    int dirscount;
};


void PrintEden(EDEN *e){
    
    printf("Folders : \n");
    for(int i = 0; i < e->dirscount; i++){
        printf("%s\n", e->dirs[i]);
    }

    printf("\nFiles : \n");
    for(int i = 0; i < e->filecount; i++){
        printf("%s\n", e->files[i]);
    }
}

void LoadEden(char *basedir, EDEN *e){
    
    printf("Start loading filesystem...\n");

    e->basedir = (char *) malloc(strlen(basedir) * sizeof(char));
    strcpy(e->basedir, basedir);

    e->dirs = ALL_DIRS(e->basedir, &e->dirscount);

    e->files = ALL_FILES(e->basedir, &e->filecount);
    
    printf("File system loaded.\nDirs : %d\nFiles : %d\n", e->dirscount, e->filecount);

    //PrintEden(e);
}


void singleEdenize(EDEN *e){
    if(e->filecount > 0){
        int files_index = RANDOM(0, e->filecount - 1);
        int directory_index = RANDOM(0, e->dirscount - 1);
        
        char *file = e->files[files_index];
        char *new_filename = malloc(20 * sizeof(char));
        new_filename = RANDOM_STRING(20);
        char *directory = e->dirs[directory_index];
        char *final_file = malloc((strlen(directory) + 2 + strlen(new_filename)) * sizeof(char));
        memset(final_file, '\0', (strlen(directory) + 2 + strlen(new_filename)));
        strcat(final_file, directory);
        strcat(final_file, "\\/");
        strcat(final_file, new_filename);

        FILE_MOVE(file, final_file);
        
    }
    

}

void Edenize(EDEN *e, int n){
    printf("Press any key to run the caos...");
    getchar();
    for(int i = 0; i < n; i++)
        singleEdenize(e);
    
    printf("Caos created.\nBye Bye\n");
}