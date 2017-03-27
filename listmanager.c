#include "listmanager.h"

typedef struct task{
char *todo;
int id;
struct task *next;
}task;

task *head = NULL;
task * current = NULL;
int tasks_counter = 1;


void add_task(const char *todo,size_t n){
    if(head == NULL)
    {  
         
        head = (task*) malloc(sizeof(task));
        head->todo = (char*) malloc(sizeof(char)*n);
        strcpy(head->todo, todo);
        head->id = tasks_counter++;
        head->next = NULL;
        current = head;
    }
    else{
        current->next = (task*)malloc(sizeof(task));
        current->next->todo= (char*) malloc(sizeof(char)*n);
        strcpy(current->next->todo,todo);
        current->next->id = tasks_counter++;
        current->next->next = NULL;
        current = current->next;
    
    }
    
}
void print_all_tasks(){
    task *p = head;
    while(p != NULL)
        {
            printf("****\n%s\n -ID %d\n****\n",p->todo,p->id);
            p = p->next;
        }

}
int remove_task_by_id(int id){
    task *p = head;
    if (p->id == id)
    {   head = head-> next;
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


