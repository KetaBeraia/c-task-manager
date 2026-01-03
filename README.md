# c-task-manager

A simple **file-based task manager written in C**.  
Tasks are stored line-by-line in a text file and managed through a terminal menu.

## Features
- Add tasks (saved to a file)
- View all saved tasks with numbering
- Delete a selected task
- Persistent storage using `tasks.txt`

## How It Works
- Each task is stored as one line in `tasks.txt`
- Tasks are read using a buffer and printed with numbers
- Deleting a task rewrites the file without the selected entry

## Requirements
- GCC or any C compiler
- Terminal / command line

