#ifndef __TASKER_DB__
#define __TASKER_DB__

#include <stdio.h>
#include <sqlite3.h>
#include "taskmanager.h"

int intialize_db(char *,int (*callback_function) (void *, int , char **, char **));
int intialize_tasks_table();
int get_all_tasks();
int insert_task(task );
int edit_task(task);
int delete_task(long);
void close_db();

#endif
