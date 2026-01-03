#include <stdio.h>   // Standard Input/Output library
#include <stdlib.h>  // Standard library, needed for exit, malloc (not used yet), etc.
#include <string.h>



#define FILENAME "tasks.txt"        // The file where tasks are stored
#define MAX_INPUT_LENGTH 256        // Maximum number of characters a task can have

// this function is for adding tasks
int addtasks() {
    FILE *fp;                        // File pointer, used to open and write to the file
    char input[MAX_INPUT_LENGTH];     // Buffer to store user input from keyboard

    
    printf("Enter your task here: ");

    // Read input from user. fgets reads until newline or MAX_INPUT_LENGTH-1
    if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
        perror("ERROR OCCURRED while reading input"); 
        return 1; // Return error code
    }

    // Open the file in append mode ("a") to add new tasks without erasing old ones
    fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        perror("ERROR OCCURRED while opening file");
        return 1; 
    }


    if (fprintf(fp, "%s", input) < 0) {
        perror("ERROR OCCURRED while writing to file");
        fclose(fp); // Close file
        return 1;
    }

    fclose(fp); 
    printf("Task added successfully!\n");
    return 0; //success
}


int viewtasks() {
    FILE *fptr;// File pointer to read from tasks file
    char buffer[MAX_INPUT_LENGTH];// Buffer to store each line/task from file
    int taskNumber = 1;// Counter to number tasks
    char choice;

    // Open the file in read mode ("r")
    fptr = fopen(FILENAME, "r");
    if (fptr == NULL) {
        // If file doesn't exist or can't be opened
        printf("Error: Could not open file.\n");
        return 1;
    }

    printf("\n--- Your Tasks ---\n");

    // Check if file is empty by trying to read first line
    if (fgets(buffer, MAX_INPUT_LENGTH, fptr) == NULL) {
        printf("No tasks found.\n"); // File is empty
        fclose(fptr);                // Close file
        printf("------------------\n");
        printf("Press Enter to go back to homepage...");
        getchar(); // Wait for user to press Enter
        return 0;
    }

    
    rewind(fptr);

    
    while (fgets(buffer, MAX_INPUT_LENGTH, fptr) != NULL) {
        // Print task number and content
        printf("%d. %s", taskNumber++, buffer);

        // Optional: pause every 10 tasks to avoid flooding the screen
        if (taskNumber % 10 == 1) {
            printf("\nPress Enter to continue or 'q' to return to homepage: ");
            choice = getchar(); // Get user input

            // If user wants to quit reading, break loop
            if (choice == 'q' || choice == 'Q') {
                break;
            }

            // If user pressed Enter, consume leftover newline to avoid skipping lines
            if (choice != '\n') getchar();
        }
    }

    fclose(fptr); 
    printf("\n--- End of Tasks ---\n");
    printf("Press Enter to go back to homepage...");
    getchar(); 
    return 0; 
}


void deletetasks() {
    char line[MAX_INPUT_LENGTH];
    char tasks[100][MAX_INPUT_LENGTH]; // store up to 100 tasks
    int count = 0;

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No tasks found.\n");
        return;
    }

    while (fgets(line, sizeof(line), file) && count < 100) {
        line[strcspn(line, "\n")] = 0; // remove newline
        strcpy(tasks[count], line);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No tasks to delete.\n");
        return;
    }

    printf("\n--- Tasks ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, tasks[i]);
    }

    int del;
    printf("Enter task number to delete: ");
    if (scanf("%d", &del) != 1 || del < 1 || del > count) {
        printf("Invalid task number.\n");
        while(getchar() != '\n'); // clear input
        return;
    }
    getchar(); // consume leftover newline

    file = fopen(FILENAME, "w"); // overwrite file
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (i != del - 1) {
            fprintf(file, "%s\n", tasks[i]);
        }
    }
    fclose(file);

    printf("Task deleted successfully!\n");
    printf("Press Enter to go back to homepage...");
    getchar();
}


//maiin
int main() {
    int choice;       // Stores user menu choice
    int running = 1;  // Flag to keep program running

    while (running) { // Loop until user chooses to exit
        // Print menu options
        printf("\n----- Welcome to Task Manager -----\n");
        printf("1. Add Tasks\n");
        printf("2. View Tasks\n");
        printf("3. Delete Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice); // Read user menu choice
        getchar();            // Consume leftover newline from Enter key

        // Execute action based on user choice
        switch (choice) {
            case 1: addtasks(); break;  // Call add task function
            case 2: viewtasks(); break; // Call view task function
            case 3: deletetasks(); break; // Call delete task function
            case 4: running = 0; break; // Exit loop → program ends
            default: printf("Invalid choice! Please try again.\n"); // Handle invalid input
        }
    }

    return 0; // Program finished successfully
}
