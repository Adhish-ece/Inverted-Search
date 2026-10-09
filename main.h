#ifndef MAIN_H
#define MAIN_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


#define SIZE 27
#define MAX_WORD_LEN 50
#define MAX_FILE_NAME 100


#define SUCCESS            0
#define FAILURE           -1
#define FILE_EMPTY        -2
#define FILE_NOT_AVAILABLE -3
#define FILE_DUPLICATE    -4
#define DATA_NOT_FOUND    -5
#define REPEAT            -6

typedef struct Lnode
{
    int word_count;
    char file_name[MAX_FILE_NAME];
    struct Lnode *link;
}Lnode;

typedef struct Wnode
{
    int file_count;
    char word[MAX_WORD_LEN];
    Lnode *slink;
    struct Wnode *link;
}Wnode;

typedef struct FileList
{
    char file_name[MAX_FILE_NAME];
    struct FileList *link;
}FileList;

int validate_file(char *fname);
void print_status(int status, const char *info);
int insert_file_list(FileList **head,char*fname);

int create_database(FileList *file_head, Wnode **hashtable);
int insert_to_db(Wnode **hastable,char *word, char *fname);
int get_index(char *word);
void display_database(Wnode **hastable);
int update_database(Wnode **hastable,FileList **filehead,char *fname);
int save_database(Wnode **hashtable,char *fname);

int search_db(Wnode **hastable,char *word);


#endif