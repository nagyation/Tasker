#include "taskerdb.h"

char *itxt = NULL;
size_t itxt_size =0;


int main(){

    while(1){
        ssize_t result = getline(&itxt,&itxt_size,stdin);
        if(result -1 < 2)
            continue;
        if( !strncmp(itxt,"-q",result-1))
            break;
        else if ( !strncmp(itxt,"-p",result-1))
            print_all_tasks();
        else if ( !strncmp(itxt,"-d",result-1))
        {   printf("Enter id you want to delete\n");
            getline(&itxt,&itxt_size,stdin);    
            int id;
            if (!sscanf(itxt,"%d",&id))
            {   
                printf("Surely I was waiting for a number\n");
        
                continue; 
            }
            remove_task_by_id(id);
            print_all_tasks();
        }
        else if(!strncmp(itxt,"-t",result-1)){
            printf("Make yourself home \n");    
            getline(&itxt,&itxt_size,stdin); 
            char *todo = (char*)malloc(sizeof(char) *itxt_size);
            strcpy(todo,itxt);
            int todo_size = itxt_size;
Set_Reminder:
            printf("Set a Reminder?\n yyyy mm dd hh mm or\n +N(m-H-D-W-M-Y) where N is a number larger than 0 \n");
           
            printf("no for no reminder\n");
            struct tm reminder_time;
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
            add_task(todo,todo_size,reminder_time,remind_freq,set_reminder);
            printf("Done ;) \n");
        }
    }
    
    free(itxt);
    printf("%s\n","Cya soon :)\n");

}


