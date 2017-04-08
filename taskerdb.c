#include "taskerdb.h"



sqlite3 *db;
char *sql;
char *err_msg = 0;

static int callback(void *data, int col_count, char **cell_data, char **col_name){
   int i;
   for(i=0; i<col_count; i++){
      printf("%s = %s\n", col_name[i], cell_data[i] ? cell_data[i] : "NULL");
   }
   printf("\n");
   return 0;
}
int intialize_tasks_table(){
    
    sql = "CREATE TABLE IF NOT EXISTS TASKS("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "TODO           TEXT    NOT NULL," \
         "CREATION_TIME  TEXT   NOT NULL," \
         "FINISHED_TIME  TEXT   ," \
         "REMINDER_TIME  TEXT   ," \
         "ARCHIVE        INT    default    0," \
         "HAS_REMINDER   INT    NOT NULL,"\
         "REMINDER_FREQ  INT    NOT NULL);";
    return sqlite3_exec(db, sql, callback, 0, &err_msg);
   
 

}

int intialize_db(char *name){
    int rc;
    rc = sqlite3_open(name,&db);
    if( rc )
        return -1;
    rc = intialize_tasks_table();
    if( rc != SQLITE_OK )
        sqlite3_free(err_msg);
    else
        return -1;
    return 0;
}

void close_db(){

    sqlite3_close(db);

}

