#ifndef __TASKMANAGER__
#define __TASKMANAGER__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#define NOT_ARCHIVE 0
#define ARCHIVE 1



enum RemindFreq{
    ONCE,
    DAILY,
    WEEKLY,
    MONTHLY,
    YEARLY
};

typedef struct task{
    /*
     * the full but not used paramters of 
     * task structure
     */
    int id;
    char *todo;
    struct tm reminder_time;
    struct tm creation_time;
    struct tm finished_time;
    uint8_t archive;
    uint8_t has_reminder;
    enum RemindFreq remind_freq;    
    struct task *next;

}task;

void add_task(const char *,size_t,struct tm,enum RemindFreq,uint8_t);
void print_all_tasks();
int remove_task_by_id(int);
int get_reminder_format(char *,struct tm *);
int get_frequent_reminder(char *,enum RemindFreq *);
#endif
