#include "taskerdb.h"




char *itxt = NULL;
size_t itxt_size =0;

static int callback(void *flag, int col_len, char **cell_data, char **col_name){
    int i;
    switch(*(int*)flag)
    {
    case PRINT_TASKS:
	    for(i=0; i<col_len; i++){
		printf("%s = %s\n", col_name[i], cell_data[i] ? cell_data[i] : "NULL");
	    }
	    printf("\n");
	    break;
    case GET_TASK:
	break;
    }
    return 0;
}

int main(){
    printf("yaaay");
    intialize_db("tasker.db", callback);
    intialize_tasks_table();
    task *tsk;
    tsk =(task*)  malloc(sizeof(task));
    printf("yaaay");
    while(1){
        ssize_t result = getline(&itxt,&itxt_size,stdin);
        if(result -1 < 2)
            continue;
        if( !strncmp(itxt,"-q",result-1))
            break;
        else if ( !strncmp(itxt,"-p",result-1))
            get_all_tasks();
        else if ( !strncmp(itxt,"-d",result-1))
        {   printf("Enter id you want to delete\n");
            getline(&itxt,&itxt_size,stdin);    
            long id;
            if (!sscanf(itxt,"%ld",&id))
            {   
                printf("Surely I was waiting for a number\n");
        
                continue; 
            }
            delete_task(id);
	    get_all_tasks();
	}
        else if(!strncmp(itxt,"-t",result-1)){
            printf("Make yourself home \n");    
            getline(&itxt,&itxt_size,stdin); 
            char *todo = (char*)malloc(sizeof(char) *itxt_size);
            strcpy(todo,itxt);
            int todo_size = itxt_size;
	     struct tm reminder_time;
Set_Reminder:
            printf("Set a Reminder?\n yyyy mm dd hh mm or\n +N(m-H-D-W-M-Y) where N is a number larger than 0 \n");
           
            printf("no for no reminder\n");
            uint8_t set_reminder = 0;
            enum RemindFreq remind_freq =  ONCE;
            if(getline(&itxt,&itxt_size,stdin) -1 <= 2)
                goto Add_Task;
            
            if (get_reminder_format(itxt,&reminder_time)) //returned -1
            {   printf("Not a valid format\n");
                goto Set_Reminder;
            }
            set_reminder = 1;
            printf("Repeated? once-daily-weekly-monthly-yearly\n");
            getline(&itxt,&itxt_size,stdin);
            get_frequent_reminder(itxt,&remind_freq);
Add_Task:
	    tsk= create_task(todo,todo_size,reminder_time,remind_freq,set_reminder);
	    insert_task(*tsk);
	    printf("Done ;) \n");
        }
    }
    free(tsk);
    free(itxt);
    printf("%s\n","Cya soon :)\n");

}


