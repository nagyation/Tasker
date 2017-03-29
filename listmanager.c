#include "listmanager.h"

#define CMP_IF_ZERO(A,B) A? A:B

typedef struct task{
    /*
     * the full but not used paramters of 
     * task structure
     */
    int id;
    char *todo;
    struct tm tasks_reminder_time;
    struct tm task_creation_time;
    struct tm task_done_time;
    uint8_t archive;
    uint8_t has_reminder;
    enum RemindFreq remind_freq;    
    struct task *next;

}task;

task *__head = NULL;
task *__current = NULL;
int __tasks_counter = 1;

struct tm __get_localetime(){
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    return time;
}
void __init_task(task *p,const char *todo,size_t n,struct tm reminder, enum RemindFreq remind_freq, uint8_t set_reminder){
        p->todo= (char*) malloc(sizeof(char)*n);
        strcpy(p->todo,todo);
        p->task_creation_time = __get_localetime();
        p->archive = NOT_ARCHIVE;
        if(set_reminder)
            p->tasks_reminder_time = reminder;
        p->has_reminder = set_reminder;
        p->remind_freq = remind_freq; 
        p->id = __tasks_counter++;
        p->next = NULL;

}
void add_task(const char *todo,size_t n,struct tm reminder, enum RemindFreq remind_freq,uint8_t set_reminder) {
    if(__head == NULL)
    {  
         
        __head = (task*) malloc(sizeof(task));
       __init_task(__head,todo,n,reminder,remind_freq,set_reminder); 
        __current = __head;
    }
    else
    {
        
        __current->next = (task*)malloc(sizeof(task));
        __init_task(__current->next,todo,n,reminder,remind_freq,set_reminder);    
        __current = __current->next;
    
    }
    
}
void print_all_tasks(){
    task *p = __head;
    while(p != NULL)
        {
            char buffer[30];
            printf("****\n%s\n -ID %d\n",p->todo,p->id);
            strftime(buffer, 30, "%Y-%m-%d %H:%M", &p->task_creation_time);
            printf("Created at %s \n",buffer);
            if(p->has_reminder)
            {
                 strftime(buffer, 30, "%Y-%m-%d %H:%M", &p->tasks_reminder_time);
                 printf("Reminder  at %s \n",buffer); 
            }
            switch(p->remind_freq)
            {   
                case ONCE:
                    strcpy(buffer, "Once");
                    break;
                case DAILY:
                    strcpy(buffer,"Daily");
                    break;
                case WEEKLY:
                    strcpy(buffer,"Weekly");
                    break;
                case MONTHLY:
                    strcpy(buffer, "Monthly");
                    break;
                case YEARLY:
                    strcpy(buffer, "Yearly");
                    break;
            }
            printf("Repeated: %s\n",buffer);
            printf("****\n");
            p = p->next;
        }

}
int remove_task_by_id(int id){
    task *p = __head;
    if (p->id == id)
    {   __head = __head-> next;
        free(p);
        return 0;
    }
    else{
        while(p->next)
    {
        if(p->next->id == id)
        {
            task *t = p->next;
            p->next = p->next->next;
            free(t);
            return 0;
        }
        p = p->next;
    }
    }
return -1;
}

int get_reminder_format(char *r,struct tm *t){
   *t = __get_localetime();
    if(r[0] == '+') //+NF
    {
        char plus,param;
        int duration;
        sscanf(r,"%c%d%c",&plus,&duration,&param);
        if(!duration)
            return -1;
        if(param =='\0')
            return -1;
       switch(param){
            case 'm':
                t->tm_min += duration;    
                break;
            case 'H':
                t->tm_hour += duration;
                break;
            case 'D':
                t->tm_mday += duration;
                break;
            case 'W':
                t->tm_mday += duration * 7;
                break;
            case 'M':
                t->tm_mon += duration;
                break;
            case 'Y':
                t->tm_year += duration;
                break;
            default:
                return -1;
       }
    }
   else{
        int year,month,day,hour,min;    
        sscanf(r,"%d %d %d %d %d",&year,&month,&day,&hour,&min);
        if (!year && !month && !day && !hour && !min)
            return -1;
        t->tm_year = year ? year-1900:t->tm_year;
        t->tm_mon = month ? month-1 :t->tm_mon;
        t->tm_mday = CMP_IF_ZERO(day,t->tm_mday);
        t->tm_hour = CMP_IF_ZERO(hour,t->tm_hour);
   }
    mktime(t);
    return 0;
}

int get_frequent_reminder(char * f,enum RemindFreq *r){
    int i;
    for(i=0; f[i] != '\0';i++)
        f[i] = tolower(f[i]);
    if(!strcmp(f,"once\n")){
        *r = ONCE;
        return 0;
    }
    else if(!strcmp(f,"daily\n")){
        *r = DAILY;
        return 0;
    }
    else if(!strcmp(f,"weekly\n"))
    {
        *r = WEEKLY;
        return 0;
    }
    else if(!strcmp(f,"monthly\n")){
        *r = MONTHLY;
        return 0;
    }
    else if(!strcmp(f,"yearly\n")){
        *r = YEARLY;
        return 0;
    }
   return -1; 
}
