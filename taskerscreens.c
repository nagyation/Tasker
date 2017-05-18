#include "taskerscreens.h"


#define ESC 27
#define clear_screen() printf("\033[H\033[J")
/*
  This library handles screens processes and prints, just for more tidy code

 */

unsigned int read_line(char **text){
    int max = 100;
    int counter = 0;
    *text = (char*)  realloc(*text,sizeof(char)*max);
    char ch;
    while ( (ch = getchar() )!= ESC)
    {
	*(*text+counter) = ch;
	counter ++;
	if(counter == max)
	{
	    max = max * 2;
	    *text = (char*)  realloc(*text,sizeof(char)*max);
	}
    }
    getchar(); // gets enter key from stdin to avoid wrong actions
    *(*text+counter)  = 0;
    return counter;
}

void welcome_screen(){
    clear_screen();
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
    printf("->");
    char *itxt = NULL;
    size_t itxt_size =0;
    getline(&itxt,&itxt_size,stdin);    
    long id;
    if (!sscanf(itxt,"%ld",&id))
    {   
	printf("Surely I was waiting for a number\n");
        
	return -1;
    }
    clear_screen();
    return id;
}

unsigned int add_task_todo_screen(char **todo){
    clear_screen();
    printf("Make yourself home \n");
    printf("Write the Todo or Task you want to remember \n");
    printf("Press ESC then Enter to apply\n");
    printf("->");
    size_t txt_size=read_line(&*todo);    
    return txt_size;
}


int add_task_reminder_screen(enum RemindFreq *remind_freq,struct tm *reminder_time ){
    /*
      @Returns 0 for has no reminder, and 1 for has reminder, -1 for wrong format
     */
    printf("Would you like to set a reminder?\n");
    printf("Use following formats :\n");
    printf("--    yyyy mm dd hh mm \n");
    printf("--    +N(m-H-D-W-M-Y) where N is a number larger than 0 \n");
    printf("Or no for continue without reminder \n");

    *remind_freq =  ONCE;
    char * itxt = NULL;
    size_t itxt_size = 0;
    getline(&itxt,&itxt_size,stdin);
    if(!strncmp(itxt,"no",2) || !strncmp(itxt,"No",2))
	return 0;
    else if (get_reminder_format(itxt,reminder_time)) //returned -1
    {
	printf("Not a valid format\n");
	return -1;
    }
    printf("How much is to be repeated? \n");
    printf("----    once-daily-weekly-monthly-yearly\n");
    getline(&itxt,&itxt_size,stdin);
    get_frequent_reminder(itxt,remind_freq);
    return 1;
}

void print_task_screen(char **cell_data)
{

    printf("---------------------------------------------------------\n");
    printf("Todo:\n");
    printf("--   %s\n\n",cell_data[TODO_COL]);
    printf("Created At:\n");
    printf("--   %s\n",cell_data[CREATION_TIME_COL]);
    printf("Remind at:\n");
    printf("--    %s\n",cell_data[REMINDER_TIME_COL] ? cell_data[REMINDER_TIME_COL]  : "No Reminder for this task");
    printf("--    Repeated  %s\n",REMINDER_FREQ_STR[atoi(cell_data[REMINDER_FREQ])]);
    printf("** Finished at:  %s\n",cell_data[FINISHED_TIME_COL]? cell_data[FINISHED_TIME_COL] : "Not yet");
    printf("TASK ID %s\n", cell_data[ID_COL]);
    printf("---------------------------------------------------------\n");

}
