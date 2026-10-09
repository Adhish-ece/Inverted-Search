#include "main.h"

int get_index(char *word)
{
    if(isalpha(word[0]))
    {
        return tolower(word[0]) - 'a';
    }
    return 26;
}

int create_database(FileList *file_head, Wnode **hashtable)
{
    if(file_head == NULL)
    {
        return FAILURE;
    }
    char word[MAX_WORD_LEN];
    while(file_head)
    {
        FILE *fp = fopen(file_head->file_name,"r");
        if(!fp)
        {
            print_status(FILE_NOT_AVAILABLE, file_head->file_name);
            file_head = file_head->link;
            continue;
        }
        while(fscanf(fp,"%49s",word)==1)
        {
            insert_to_db(hashtable,word,file_head->file_name);
        }
        fclose(fp);
        printf("Successful: Creation of DATABASE for file: %s\n", file_head->file_name);
        file_head= file_head->link;
    }
    return SUCCESS;
}

int insert_to_db(Wnode **hastable,char *word, char *fname)
{
    int index = get_index(word);
    Wnode *wtemp = hastable[index];
    Wnode *wprev = NULL;

    while(wtemp != NULL)
    {
        if(strcmp(wtemp->word,word) == 0)
        {
            Lnode *ltemp = wtemp->slink;
            Lnode *lprev = NULL;
            while (ltemp != NULL)
            {
                if(strcmp(ltemp->file_name,fname)==0)
                {
                    ltemp->word_count++;
                    return SUCCESS;
                }
                lprev = ltemp;
                ltemp = ltemp->link;
            } 
        
            Lnode *new_node = malloc(sizeof(Lnode));
            if(!new_node)
            {
                return FAILURE;
            }
            new_node->word_count = 1;
            strcpy(new_node->file_name,fname);
            new_node->link = NULL;
            lprev->link = new_node;
            wtemp->file_count++;
            return SUCCESS;
        }

        wprev = wtemp;
        wtemp=wtemp->link;

    }
    Wnode *new_wnode = malloc(sizeof(Wnode));
    Lnode *new_lnode = malloc(sizeof(Lnode));
    if(!new_lnode || !new_wnode)
    {
        return FAILURE;
    }
    strcpy(new_wnode->word,word);
    new_wnode->file_count = 1;
    new_wnode->link = NULL;

    new_lnode->word_count = 1;
    strcpy(new_lnode->file_name,fname);
    new_lnode->link = NULL;

    new_wnode->slink = new_lnode;
    if(hastable[index] == NULL)
    {
        hastable[index] = new_wnode;
    }
    else
    {
        wprev->link = new_wnode;
    }
    return SUCCESS;
}

void display_database(Wnode **hastable)
{
    printf("\n[Index]  [word]        file count  files\n");
    printf("---------------------------------------------------\n");
    int empty = 1;
    for(int i=0;i<SIZE;i++)
    {
        if(hastable[i] != NULL)
        {
            empty = 0;
            Wnode *wtemp = hastable[i];
            while(wtemp != NULL)
            {
                printf("[%d]    [%-10s]  %d files: ", i, wtemp->word, wtemp->file_count);
                Lnode *ltemp = wtemp->slink;
                while(ltemp!=NULL)
                {
                    printf("File: %s %d  ", ltemp->file_name, ltemp->word_count);
                    ltemp = ltemp->link;
                }
                printf("\n");
                wtemp = wtemp->link;
            }
        }
    }
    if(empty)
    {
        printf("Database is empty.\n");
    }
}

int update_database(Wnode **hastable,FileList **filehead,char *fname)
{
    int status = validate_file(fname);
    if(status !=SUCCESS)
    {
        return status;
    }
    FILE *fp = fopen(fname,"r");
    if(!fp)
    {
        return FILE_NOT_AVAILABLE;
    }
    char first_char = fgetc(fp);
    fclose(fp);

    if(first_char == '#')
    {
        fp = fopen(fname,"r");
        char line[500];
        while(fgets(line,sizeof(line),fp))
        {
            if(line[0]=='#')
            continue;
            char *token = strtok(line,":\n");
            if(!token)
            {
                continue;
            }
            char word[MAX_WORD_LEN];
            strcpy(word,token);

            token = strtok(NULL,":\n");
            if(!token)
            {
                continue;
            }

            int file_count = atoi(token);
            for(int i=0;i<file_count;i++)
            {
                char filename[MAX_FILE_NAME];
                token = strtok(NULL,":\n");
                if(!token || strcmp(token,"#")==0)
                {
                    break;
                }
                strcpy(filename,token);
                token = strtok(NULL,":\n");
                if(!token || strcmp(token,"#")==0)
                {
                    break;
                }
                int count = atoi(token);
                insert_file_list(filehead,filename);
                for(int c =0;c<count;c++)
                {
                    insert_to_db(hastable,word,filename);
                }
            }
        }
        fclose(fp);
        printf("Successful: Database updated from backup file %s\n", fname);
        return SUCCESS;
    }
    else
    {
        insert_file_list(filehead,fname);
        fp = fopen(fname,"r");
        char word[MAX_WORD_LEN];
        while(fscanf(fp,"%49s",word)==1)
        {
            insert_to_db(hastable,word,fname);
        }
        fclose(fp);
        printf("Successful: Creation of DATABASE for file: %s\n", fname);
        return SUCCESS;
    }
    
}

int search_db(Wnode **hastable,char *word)
{
    int index = get_index(word);
    Wnode *wtemp = hastable[index];
    while(wtemp)
    {
        if(strcmp(wtemp->word,word)==0)
        {
            printf("Word %s is present in %d files\n", word, wtemp->file_count);
            Lnode *ltemp = wtemp->slink;
            while(ltemp)
            {
                printf("In file: %s %d time/s\n", ltemp->file_name, ltemp->word_count);
                ltemp = ltemp->link;
            }
            return SUCCESS;
        }
        
        wtemp = wtemp->link;
    }
    return DATA_NOT_FOUND;
    
    
}


int save_database(Wnode **hashtable,char *fname)
{
    FILE *fp = fopen(fname,"w");
    if(!fp)
    {
        return FAILURE;
    }
    for(int i=0;i<SIZE;i++)
    {
        if(hashtable[i] != NULL)
        {
            fprintf(fp,"#:%d\n",i);
            Wnode *wtemp = hashtable[i];
            while(wtemp)
            {
                fprintf(fp,"%s:%d",wtemp->word,wtemp->file_count);
                Lnode *ltemp = wtemp->slink;
                while(ltemp != NULL)
                {
                    fprintf(fp,":%s:%d",ltemp->file_name,ltemp->word_count);
                    ltemp = ltemp->link;
                }
                fprintf(fp, ":#\n");
                wtemp = wtemp->link;
            }
            
        }
    }
    fclose(fp);
    printf("Database is saved\n");
    return SUCCESS;
}

