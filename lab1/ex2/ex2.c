/*************************************
* Lab 1 Exercise 2
* Name:
* Student No:
* Lab Group:
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "function_pointers.h"

// the runner is empty now! Modify it to fulfill the requirements of the
// exercise. You can use ex1.c as a template

// macros
#define SUM_LIST 0
#define INSERT_FROM_HEAD_AT 1
#define INSERT_FROM_TAIL_AT 2
#define DELETE_FROM_HEAD_AT 3
#define DELETE_FROM_TAIL_AT 4
#define RESET_LIST 5
#define MAP 6

void run_instruction(list *lst, int instr);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: expecting 1 argument, %d found\n", argc - 1);
        exit(1);
    }

    // we read in the file name provided as argument
    char *fname = argv[1];
    // char readline[256];

    // updating the array of function pointers
    // do not remove this call 
    // (you may leave the function empty if you do not need it)
    update_functions();

    // initiate list
    list *lst = (list *)malloc(sizeof(list));
    lst->head = NULL;
    lst->tail = NULL;

    // open file
    FILE * file;
    file = fopen(fname, "r");

    if (file) {
        int instr;
        while(fscanf(file, "%d", &instr) == 1) {
            int index, data;
            printf("%d", instr);
            switch (instr)
            {
            case SUM_LIST:
                sum_list(lst);
                break;
            case INSERT_FROM_HEAD_AT:
                fscanf(file, "%d %d", &index, &data);
                insert_node_from_head_at(lst, index, data);
                break;
            case INSERT_FROM_TAIL_AT:
                fscanf(file, "%d %d", &index, &data);
                insert_node_from_tail_at(lst, index, data);
                break;
            case DELETE_FROM_HEAD_AT:
                fscanf(file, "%d", &index);
                delete_node_from_head_at(lst, index);
                break;
            case DELETE_FROM_TAIL_AT:
                fscanf(file, "%d", &index);
                delete_node_from_tail_at(lst, index);
                break;   
            case RESET_LIST:
                reset_list(lst);
                break;
            case MAP:
                fscanf(file, "%d", &instr);
                map(lst, func_list[instr]);
            }
        }
    } else {
        perror("Error: Unable to open file");
        exit(1);
    }

    fclose(file);
    return 0;
}
