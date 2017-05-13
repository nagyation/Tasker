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
   
    long id;
    char *todo;
    struct tm reminder_time;
    struct tm creation_time;
    struct tm finished_time;
    uint8_t archive;
    uint8_t has_reminder;
    enum RemindFreq remind_freq;
    
}task;

task * create_task(const char *todo,size_t n,struct tm reminder, enum RemindFreq remind_freq, uint8_t set_reminder);
int get_reminder_format(char *,struct tm *);
int get_frequent_reminder(char *,enum RemindFreq *);
char * get_formated_timestamp(struct tm *);

#endif
