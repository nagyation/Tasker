#include "taskerdb.h"
#include "taskerscreens.h"

#define GET_TASK  0
#define PRINT_TASKS 1
#define CMP_STR(A,B)  !strncmp(A,B,2)

	   
char *itxt = NULL;
size_t itxt_size =0;

static int callback(void *flag, int col_len, char **cell_data, char **col_name){
    if ( ! flag)
	return 0;
    switch(*(int*)flag)
    {
    case PRINT_TASKS:
	print_task_screen(cell_data);
	    break;
    case GET_TASK:
	break;
    }
    return 0;
}

int main(){
    welcome_screen();
    help_screen();
    intialize_db("tasker.db", callback);
    intialize_tasks_table();
    task *tsk;
    tsk =(task*)  malloc(sizeof(task));
    while(1){
	printf("-> ");
        ssize_t result = getline(&itxt,&itxt_size,stdin);
        if(result -1 != 2)
	{
	    printf("wrong argument\n -h to see possible ones\n");
            continue;
	}
        if(CMP_STR(itxt,"-q"))
            break;
	else if(CMP_STR(itxt, "-h"))
	    help_screen();
        else if (CMP_STR(itxt,"-p"))
            get_all_tasks();
        else if (CMP_STR(itxt,"-d"))
        {
	    long id;
	    id = delete_screen();
	    if(id == -1)
		continue;
            delete_task(id);
	    get_all_tasks();
	}
        else if(CMP_STR(itxt,"-t")){
	    
            char *todo = NULL;
            int todo_size = add_task_todo_screen(&todo);
	    struct tm reminder_time;
	    int set_reminder = -1;
	    enum RemindFreq remind_freq;

	    while(set_reminder == -1)
		set_reminder = add_task_reminder_screen(&remind_freq, &reminder_time);
	    
	    tsk= create_task(todo,todo_size,reminder_time,remind_freq,set_reminder);
	    insert_task(*tsk);
	    printf("Added :) \n");
        }
    }
    free(tsk);
    free(itxt);
    printf("Cya soon :)\n");

}


