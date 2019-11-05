#include <stdio.h>
#include <stdbool.h>

#ifndef FILEMANAGER
#define FILEMANAGER

#define FILE_OPEN(file, mode) fopen(file, mode)
#define FILE_CLOSE(file) fclose(file)
#define FILE_DELETE(file) remove(file)
#define FILE_COPY(source, destination) copyFile(source, destination)
#define FILE_MOVE(source, destination) FILE_COPY(source, destination) ? !FILE_DELETE(source) : false;
#define FILE_READ_CHAR(file) fgetc(file)
#define FILE_WRITE_CHAR(file, character) fputc(character, file)

/*
Copia il file source nel file destination.
source : path del file da copiare.
destination : path del file da creare.
*/
bool copyFile(char *source, char *destination){

    FILE *src, *dst;
    src = FILE_OPEN(source, "r+");
    
    if(src == NULL){
        return false;
    } 
    dst = FILE_OPEN(destination, "w+");
    if(dst == NULL){
        return false;
    }

    char ch;
    while( (ch = FILE_READ_CHAR(src)) != EOF )
        FILE_WRITE_CHAR(dst, ch);

    FILE_CLOSE(src);
    FILE_CLOSE(dst);
    return true;
}
#endif // !FILE
