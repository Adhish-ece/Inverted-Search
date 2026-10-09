#include "main.h"
int is_file_duplicate(FileList *head,char *fname)
{
    while(head)
    {
        if(strcmp(fname,head->file_name)==0)
        {
            return FILE_DUPLICATE;
        }
        head = head->link;
    }
    return SUCCESS;
}
int insert_file_list(FileList **head,char*fname)
{
    if(is_file_duplicate(*head,fname)==FILE_DUPLICATE)
    {
        return FILE_DUPLICATE;
    }
    FileList *new_node = malloc(sizeof(FileList));
    if(!new_node)
    {
        return FAILURE;
    }
    strcpy(new_node->file_name,fname);
    new_node->link = NULL;
    if(*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        FileList *temp = *head;
        while(temp->link)
        {
            temp = temp->link;
        }
        temp->link = new_node;
    }

    printf("Successful: inserting file name: %s into file linked list\n", fname);
    return SUCCESS;
}