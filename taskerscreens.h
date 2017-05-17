#ifndef __TASKER_SCREENS__
#define __TASKER_SCREENS__
#include <stdio.h>
#include <stdlib.h>
#include "taskmanager.h"

void welcome_screen();
void help_screen();
long delete_screen();
unsigned int add_task_todo_screen(char**);
int add_task_reminder_screen(enum RemindFreq *, struct tm*);

#endif
