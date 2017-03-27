#ifndef __MEMTASKER__
#define __MEMTASKER__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
enum RemindFreq{
    ONCE,
    DAILY,
    WEEKLY,
    MONTHLY,
    YEARLY
};
void add_task(const char *,size_t );
void print_all_tasks();
int remove_task_by_id(int );

#endif
