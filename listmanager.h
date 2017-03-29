#ifndef __LISTMANAGER__
#define __LISTMANAGER__

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
void add_task(const char *,size_t,struct tm,enum RemindFreq,uint8_t);
void print_all_tasks();
int remove_task_by_id(int);
int get_reminder_format(char *,struct tm *);
int get_frequent_reminder(char *,enum RemindFreq *);
#endif
