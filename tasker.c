#include "listmanager.h"
int main(){

    while(1){
        char *todo = NULL;
        size_t todo_size =0;
        ssize_t result = getline(&todo,&todo_size,stdin);
        if( !strncmp(todo,"-q",result-1))
            break;
        else if ( !strncmp(todo,"-p",result-1))
            print_all_tasks();
        else if ( !strncmp(todo,"-d",result-1))
        {   printf("Enter id you want to delete\n");
            free(todo);
            todo = NULL;
            todo_size = 0;
            getline(&todo,&todo_size,stdin);
            int id;
            if (!sscanf(todo,"%d",&id))
            {   
                printf("Surely I was waiting for a number\n");
        
                continue; 
            }
            remove_task_by_id(id);
            print_all_tasks();
        }
        else
            add_task(todo,todo_size);
        free(todo);
    }
    printf("%s\n","Cya soon :)\n");

}


