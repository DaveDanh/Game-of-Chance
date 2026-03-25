#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fatal(char *msg){
    char ErrorMessage[200];
    strcpy(ErrorMessage,"Fatal Error: ");
    strncat(ErrorMessage, msg, 187);
    perror(ErrorMessage);
    exit(-1);
}

void * CheckMalloc(unsigned int size){
    void *ptr;
    ptr = malloc(size);
    if (ptr == NULL){
        fatal("Error when performing memory allocation");
    }
    return ptr;
}