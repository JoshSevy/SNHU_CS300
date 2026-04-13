# CS 300 Project Two - ABCU Advising Assistance Program

## Overview
This project implements a command-line advising assistance program 
for ABC University (ABCU). The application allows academic advisors 
to load course data, view a sorted list of courses, and retrieve 
detailed information about individual courses and their prerequisites.

The program is built using a **Binary Search Tree (BST)**, 
which was selected based on prior analysis for its balance 
of efficient searching and natural in-order sorting.

---

## Features

- Load course data from a CSV file
- Store course data in a Binary Search Tree
- Print all courses in alphanumeric order
- Search for a specific course and display its details
- Validate user input and handle errors gracefully

---

## Menu Options

When the program runs, users are presented with the following menu:

```
1. Load Data Structure
2. Print Course List
3. Print Course
9. Exit
```

### Option 1: Load Data Structure
Prompts the user for a file name and loads course data into the BST.

### Option 2: Print Course List
Displays all courses in alphanumeric order using in-order traversal of the BST.

### Option 3: Print Course
Prompts the user for a course number and displays the course title and prerequisites.

### Option 9: Exit
Terminates the program.

---

## Example Output

```
Welcome to the course planner.
1. Load Data Structure.
2. Print Course List.
3. Print Course.
9. Exit
What would you like to do? 2
No courses loaded.
```

---

## Data Structure Choice

A Binary Search Tree was used because:

- It allows efficient search operations (average O(log n))
- It supports in-order traversal for naturally sorted output
- It meets both project requirements without additional sorting steps

---

## Current Status (Phase 1)

- BST structure implemented
- Menu system implemented
- Course lookup logic implemented
- File loading functionality (Phase 2) pending

---

## Next Steps

- Implement file parsing and validation
- Load course data into BST
- Validate prerequisites
- Test with provided dataset

---

## Author
Joshua Sevy