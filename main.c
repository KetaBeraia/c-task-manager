#include <stdio.h> //including input output library
#include <stdlib.h> //including exit library 

void addtasks(){//adds task

}

void viewtasks(){//views tasks

}

void deletetasks(){//deletes tasks

}

int main() {  // <-- main function
    int choice;
    int running = 1;

    while(running){ 
        printf("\n -----Welcome to Task Manager------ \n");
        printf("1. Add Tasks \n");
        printf("2. View Tasks \n");
        printf("3. Delete Tasks \n");
        printf("4. Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice)
        {
            case 1: addtasks(); break;
            case 2: viewtasks(); break;
            case 3: deletetasks(); break;
            case 4: running = 0; break;
            default: printf("Invalid choice! \n");
        }
    }

    return 0; // main should return int
}
