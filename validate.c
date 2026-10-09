#include "main.h"


void print_status(int status, const char *info)
{
    switch (status)
    {
        case SUCCESS:
            break;
        case FILE_NOT_AVAILABLE:
            printf("Error: File '%s' does not exist.\n", info ? info : "");
            break;
        case FILE_EMPTY:
            printf("Error: File '%s' is empty.\n", info ? info : "");
            break;
        case FILE_DUPLICATE:
            printf("Info: File '%s' is already in the list/database.\n", info ? info : "");
            break;
        case DATA_NOT_FOUND:
            printf("Error: Search query '%s' not found in database.\n", info ? info : "");
            break;
        case REPEAT:
            printf("Info: Database has already been created.\n");
            break;
        case FAILURE:
        default:
            printf("Error: Operation failed for '%s'.\n", info ? info : "");
            break;
    }
}

int validate_file(char *fname)
{
    FILE *fp = fopen(fname,"r");
    if(!fp)
    {
        return FILE_NOT_AVAILABLE;
    }
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    if(size == 0)
    {
        return FILE_EMPTY;
    }
    return SUCCESS;

}
