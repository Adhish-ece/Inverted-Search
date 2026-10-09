#include "main.h"

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("Error: Please pass file names as command line arguments.\n");
        printf("Usage: %s <file1.txt> <file2.txt> ...\n", argv[0]);
        return 1;
    }
    FileList *file_head = NULL;
    for(int i = 1;i<argc;i++)
    {
        int res = validate_file(argv[i]);
        if(res == SUCCESS)
        {
            insert_file_list(&file_head,argv[i]);
        }
        else
        {
            print_status(res,argv[i]);
        }
    }

    if(file_head == NULL)
    {
        printf("Error: None of the provided files are valid.\n");
        return 1;
    }

    Wnode *hashtable[SIZE] = {NULL};
    int choice;
    char cont;
    int db_created = 0;

    do
    {
        printf("\nSelect your choice among following options:\n");
        printf("1. Create DATABASE\n");
        printf("2. Display Database\n");
        printf("3. Update DATABASE\n");
        printf("4. Search\n");
        printf("5. Save Database\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
     
        switch (choice)
        {
            case 1:
                if(!db_created)
                {
                    int res = create_database(file_head,hashtable);
                    if(res == SUCCESS)
                    {
                        print_status(res, "Database Creation");
                        db_created = 1;
                    }
                }
                else
                {
                    print_status(REPEAT, NULL);
                }
                break;
            
            case 2:
                display_database(hashtable);
                break;
            case 3:
            {
                char update_file[MAX_FILE_NAME];
                printf("Enter the File name to update data: ");
                scanf("%s", update_file);
                int res = update_database(hashtable, &file_head, update_file);
                if (res != SUCCESS) 
                {
                    print_status(res, update_file);
                }
            }
            break;
                
            case 4:
                char search_word[MAX_WORD_LEN];
                printf("Enter the word you want to search: ");
                scanf("%s", search_word);
                int res = search_db(hashtable,search_word);
                if(res !=  SUCCESS)
                {
                    print_status(res, search_word);
                }
                break;
            case 5:
                char save_file[MAX_FILE_NAME];
                printf("Enter the file name to save database: ");
                scanf("%s", save_file);
                res = save_database(hashtable, save_file);
                if (res != SUCCESS) print_status(res, save_file);
                break;
        }

        printf("\nDo you want to continue ?\n");
        printf("Enter y/Y to continue and n/N to discontinue: ");
        scanf(" %c", &cont);

    } while (cont == 'y' || cont == 'Y');

    return 0;
}