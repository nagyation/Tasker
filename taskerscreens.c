#include "taskerscreens.h"

/*
  This library handles screens processes and prints, just for more tidy code

 */

void welcome_screen(){
    printf(" Welcome to Tasker :) \n");
}

void help_screen(){
    printf("Use one of the next options \n");
    printf("    -t to add new task \n");
    printf("    -d to delete a task by id \n");
    printf("    -p to print all tasks \n");
    printf("    -h to show this screen \n");
    printf("    -q to close tasker \n");
}

long delete_screen(){
    printf("Enter id you want to delete\n");
    char *itxt = NULL;
    size_t itxt_size =0;
    getline(&itxt,&itxt_size,stdin);    
    long id;
    if (!sscanf(itxt,"%ld",&id))
    {   
	printf("Surely I was waiting for a number\n");
        
	return -1;
    }
    return id;
}
