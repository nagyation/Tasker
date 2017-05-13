#include "taskmanager.h"

#define CMP_IF_ZERO(A,B) A? A:B


struct tm __get_localetime(){

/*
  Return: the current time
 */

    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    return time;
}


void get_formated_timestamp(char * buffer,struct tm timestamp){

/*

format tm to formated string that can be used with sqlite timestamp
@buffer: the string buffer to return the string in
@timestamp: the desired time to format

*/

    buffer = (char*) realloc(buffer, sizeof(char)*30);
    strftime(buffer, 30, "%Y-%m-%d %H:%M",&timestamp);

}



task * create_task(const char *todo,size_t n,struct tm reminder, enum RemindFreq remind_freq, uint8_t set_reminder){

    /*
      Return: pointer to the task created
     */
    
    task * p = (task*) malloc(sizeof(task));
    p->todo= (char*) malloc(sizeof(char)*n);
    strcpy(p->todo,todo);
    p->creation_time = __get_localetime();
    p->archive = NOT_ARCHIVE;
    if(set_reminder)
	p->reminder_time = reminder;
    p->has_reminder = set_reminder;
    p->remind_freq = remind_freq; 
    return p;

}


/*void print_all_tasks(){
    task *p = __head;
    while(p != NULL)
        {
            char buffer[30];
            printf("****\n%s\n -ID %d\n",p->todo,p->id);
            strftime(buffer, 30, "%Y-%m-%d %H:%M", &p->creation_time);
            printf("Created at %s \n",buffer);
            if(p->has_reminder)
            {
                 strftime(buffer, 30, "%Y-%m-%d %H:%M", &p->reminder_time);
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

*/


int get_reminder_format(char *ireminder,struct tm *reminder_time){
    /*
      *Takes the user input for reminder, and generate timestamp upon.
      *it searches for two formats:
      *--'+NF'  -- where N= duration, F= Unit (Month,Day,etc..)
      *-- 'YYYY MM DD HH mm' the exact time, what is not found in the timestamp is added as now
      *@ireminder : input string for reminder format
      *@reminder_time : processed and returned timestamp for reminder
      *@Returns: 0 for success and -1 if the format is wrong
      */
    
    *reminder_time = __get_localetime();
    if(ireminder[0] == '+') //+NF
    {
        char plus,param;
        int duration;
        sscanf(ireminder,"%c%d%c",&plus,&duration,&param);
        if(!duration)
            return -1;
        if(param =='\0')
            return -1;
       switch(param){
            case 'm':
                reminder_time->tm_min += duration;    
                break;
            case 'H':
                reminder_time->tm_hour += duration;
                break;
            case 'D':
                reminder_time->tm_mday += duration;
                break;
            case 'W':
                reminder_time->tm_mday += duration * 7;
                break;
            case 'M':
                reminder_time->tm_mon += duration;
                break;
            case 'Y':
                reminder_time->tm_year += duration;
                break;
            default:
                return -1;
       }
    }
   else{
        int year,month,day,hour,min;    
        sscanf(ireminder,"%d %d %d %d %d",&year,&month,&day,&hour,&min);
        if (!year && !month && !day && !hour && !min)
            return -1;
        reminder_time->tm_year = year ? year-1900:reminder_time->tm_year;
        reminder_time->tm_mon = month ? month-1 :reminder_time->tm_mon;
        reminder_time->tm_mday = CMP_IF_ZERO(day,reminder_time->tm_mday);
        reminder_time->tm_hour = CMP_IF_ZERO(hour,reminder_time->tm_hour);
   }
    mktime(reminder_time);
    return 0;
}




int get_frequent_reminder(char * iremind,enum RemindFreq *remind_freq){
    /*
      Sets the enum according the input of the user
      @iremind: input remind format to be processed
      @remind_freq: returned remind_freq 
      @Return: 0 for success , -1 for invalid format
    */

    int i;
    iremind [strlen(iremind) - 1] = 0; // removes /n character
    
    for(i=0; iremind[i] != '\0';i++)
        iremind[i] = tolower(iremind[i]);  //Lowering all characters to make it general
    
    if(!strcmp(iremind,"once")){
        *remind_freq = ONCE;
        return 0;
    }
    else if(!strcmp(iremind,"daily")){
        *remind_freq = DAILY;
        return 0;
    }
    else if(!strcmp(iremind,"weekly"))
    {
        *remind_freq = WEEKLY;
        return 0;
    }
    else if(!strcmp(iremind,"monthly")){
        *remind_freq = MONTHLY;
        return 0;
    }
    else if(!strcmp(iremind,"yearly")){
        *remind_freq = YEARLY;
        return 0;
    }
   return -1; 
}
