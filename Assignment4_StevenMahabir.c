#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_STUDENTS 75

// Define student information structure
typedef struct
{
    int st_id;
    char last_name[15];
    char first_name[15];
    int age;
    char course_code[10];
} StudentInfo;

// Define student grade structure
typedef struct
{
    int st_id;
    int course_01;
    int course_02;
    int course_03;
    int course_04;
    int total;
    float percentage;
} StudentGrade;

// Combined student record structure
typedef struct
{
    StudentInfo info;
    StudentGrade grade;
} StudentRecord;

// Binary Search Tree Node
typedef struct TreeNode
{
    StudentRecord data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Move calculateTotalAndPercentage function here
void calculateTotalAndPercentage(StudentRecord *student)
{
    student->grade.total = student->grade.course_01 + student->grade.course_02 +
                           student->grade.course_03 + student->grade.course_04;

    student->grade.percentage = (float)student->grade.total / 4.0;
}

// Move partition function here
int partition(StudentRecord records[], int low, int high, int *count_measu)
{
    // Using percentage as the sort key (descending order)
    float pivot = records[high].grade.percentage;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        (*count_measu)++; // Count comparison
        if (records[j].grade.percentage >= pivot)
        {
            i++;
            // Swap records[i] and records[j]
            StudentRecord temp = records[i];
            records[i] = records[j];
            records[j] = temp;
        }
    }

    // Swap records[i+1] and records[high]
    StudentRecord temp = records[i + 1];
    records[i + 1] = records[high];
    records[high] = temp;

    return i + 1;
}

// Function definitions
int getValidInt()
{
    int num;

    // Try to read an integer
    while (scanf("%d", &num) != 1)
    {
        // Clear input buffer until newline
        while (getchar() != '\n')
            ;
        printf("Invalid input. Enter an integer: ");
    }

    // Clear any remaining characters in the buffer
    while (getchar() != '\n')
        ;
    return num;
}

void getValidString(char *str, int size)
{
    char temp[256]; // Temporary buffer for all input types
    int valid_input = 0;

    while (!valid_input)
    {
        // Get input using fgets
        if (fgets(temp, sizeof(temp), stdin) == NULL)
        {
            str[0] = '\0';
            return;
        }

        // Remove newline character if present
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n')
        {
            temp[len - 1] = '\0';
            len--;
        }

        // Check if input is too long
        if (len >= size)
        {
            printf("Input too long. Maximum length is %d characters. Please try again: ", size - 1);
            // Don't need to clear buffer here as fgets already consumed the entire line
            continue;
        }

        // If we get here, input is valid
        strcpy(str, temp);
        valid_input = 1;
    }
}

int validateName(const char *name)
{
    if (strlen(name) == 0 || strlen(name) > 14)
        return 0;

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]))
        {
            return 0;
        }
    }
    return 1;
}

int validateCourseCode(const char *code)
{
    if (strlen(code) < 2)
        return 0;

    int has_letter = 0;
    int has_number = 0;
    int has_underscore = 0;

    for (int i = 0; code[i] != '\0'; i++)
    {
        if (isalpha(code[i]))
            has_letter = 1;
        else if (isdigit(code[i]))
            has_number = 1;
        else if (code[i] == '_')
            has_underscore = 1;
        else
            return 0; // Invalid character found
    }

    // Must have all three: letter, number, and underscore
    return (has_letter && has_number && has_underscore);
}

void displayMenu()
{
    printf("\n======= STUDENT DB SYSTEM =======\n");
    printf("1). Create a student information structure\n");
    printf("2). Read/Modify student information\n");
    printf("3). Marks Entry of each student (course 01-04)\n");
    printf("4). Calculate Total and Percentage\n");
    printf("5). Display student information in Sorted order (Linear algorithm)\n");
    printf("6). Display student percentage in descending order (Binary algorithm)\n");
    printf("7). Search student by ID using Binary Search Tree\n");
    printf("8). Quit\n");
    printf("---------------------------------------\n");
}

int validateStudentID(int id)
{
    return id > 0 && id <= 999999; // Assuming 6-digit ID (based on highschool ID size)
}

int validateAge(int age)
{
    return age >= 18 && age <= 60; // Age range for students
}

int validateMarks(int marks)
{
    return marks >= 0 && marks <= 100;
}

void createStudentRecord(StudentRecord records[], int *count)
{
    if (*count >= MAX_STUDENTS)
    {
        printf("Maximum number of students reached.\n");
        return;
    }

    StudentRecord newStudent;

    printf("\n--- Creating new student record ---\n");

    int id;
    printf("Enter Student ID: ");
    id = getValidInt();

    while (!validateStudentID(id))
    {
        printf("Invalid ID. Please enter a valid numeric ID <= 999999: ");
        id = getValidInt();
    }

    // Check if ID already exists
    for (int i = 0; i < *count; i++)
    {
        if (records[i].info.st_id == id)
        {
            printf("Error: Student ID already exists. Please use a unique ID.\n");
            return;
        }
    }

    newStudent.info.st_id = id;
    newStudent.grade.st_id = id;

    printf("Enter Last Name (max 14 characters): ");
    getValidString(newStudent.info.last_name, 15);
    while (!validateName(newStudent.info.last_name))
    {
        printf("Invalid last name. Please enter 1-14 letters only: ");
        getValidString(newStudent.info.last_name, 15);
    }

    printf("Enter First Name (max 14 characters): ");
    getValidString(newStudent.info.first_name, 15);
    while (!validateName(newStudent.info.first_name))
    {
        printf("Invalid first name. Please enter 1-14 letters only: ");
        getValidString(newStudent.info.first_name, 15);
    }

    printf("Enter Age: ");
    newStudent.info.age = getValidInt();
    while (!validateAge(newStudent.info.age))
    {
        printf("Invalid age. Please enter a valid age (18-60): ");
        newStudent.info.age = getValidInt();
    }

    printf("Enter Course Code: ");
    getValidString(newStudent.info.course_code, 10);
    while (!validateCourseCode(newStudent.info.course_code))
    {
        printf("Invalid course code. Course code must contain at least one letter, one number, and one underscore.\n");
        printf("Enter Course Code: ");
        getValidString(newStudent.info.course_code, 10);
    }

    // Initialize grades to zero
    newStudent.grade.course_01 = 0;
    newStudent.grade.course_02 = 0;
    newStudent.grade.course_03 = 0;
    newStudent.grade.course_04 = 0;
    newStudent.grade.total = 0;
    newStudent.grade.percentage = 0.0;

    records[*count] = newStudent;
    (*count)++;
    printf("Student record created successfully!\n");
}

void studfunc(StudentRecord records[], int count)
{
    if (count == 0)
    {
        printf("No student records found. Please create records first.\n");
        return;
    }

    printf("Enter Student ID to read/modify: ");
    int id = getValidInt();

    for (int i = 0; i < count; i++)
    {
        if (records[i].info.st_id == id)
        {
            int choice;
            printf("\nCurrent Student Information:\n");
            printf("ID: %d\n", records[i].info.st_id);
            printf("Name: %s %s\n", records[i].info.first_name, records[i].info.last_name);
            printf("Age: %d\n", records[i].info.age);
            printf("Course Code: %s\n", records[i].info.course_code);

            printf("\nWould you like to: (1) Return to menu or (2) Modify information? ");
            choice = getValidInt();

            if (choice == 2)
            {
                char buffer[50];

                // Last Name validation
                do
                {
                    printf("Enter new Last Name (max 14 characters): ");
                    getValidString(buffer, 50);
                    if (!validateName(buffer))
                    {
                        printf("Invalid last name. Please enter 1-14 letters only.\n");
                    }
                } while (!validateName(buffer));
                strcpy(records[i].info.last_name, buffer);

                // First Name validation
                do
                {
                    printf("Enter new First Name (max 14 characters): ");
                    getValidString(buffer, 50);
                    if (!validateName(buffer))
                    {
                        printf("Invalid first name. Please enter 1-14 letters only.\n");
                    }
                } while (!validateName(buffer));
                strcpy(records[i].info.first_name, buffer);

                // Age validation
                int age;
                do
                {
                    printf("Enter new Age: ");
                    age = getValidInt();
                    if (!validateAge(age))
                    {
                        printf("Invalid age. Please enter a value between 18-60.\n");
                    }
                } while (!validateAge(age));
                records[i].info.age = age;

                // Course Code validation
                do
                {
                    printf("Enter new Course Code: ");
                    getValidString(buffer, 20);
                    if (!validateCourseCode(buffer))
                    {
                        printf("Invalid course code. Course code must contain at least one letter, one number, and one underscore.\n");
                    }
                } while (!validateCourseCode(buffer));
                strcpy(records[i].info.course_code, buffer);

                printf("Student information updated successfully!\n");
            }

            return;
        }
    }

    printf("Student ID not found.\n");
}

void markfunc(StudentRecord records[], int count)
{
    if (count == 0)
    {
        printf("No student records found. Please create records first.\n");
        return;
    }

    printf("Enter Student ID for marks entry: ");
    int id = getValidInt();

    for (int i = 0; i < count; i++)
    {
        if (records[i].info.st_id == id)
        {
            printf("\nEntering marks for %s %s\n", records[i].info.first_name, records[i].info.last_name);

            printf("Enter marks for Course 1 (0-100): ");
            records[i].grade.course_01 = getValidInt();
            while (!validateMarks(records[i].grade.course_01))
            {
                printf("Invalid marks. Please enter value between 0-100: ");
                records[i].grade.course_01 = getValidInt();
            }

            printf("Enter marks for Course 2 (0-100): ");
            records[i].grade.course_02 = getValidInt();
            while (!validateMarks(records[i].grade.course_02))
            {
                printf("Invalid marks. Please enter value between 0-100: ");
                records[i].grade.course_02 = getValidInt();
            }

            printf("Enter marks for Course 3 (0-100): ");
            records[i].grade.course_03 = getValidInt();
            while (!validateMarks(records[i].grade.course_03))
            {
                printf("Invalid marks. Please enter value between 0-100: ");
                records[i].grade.course_03 = getValidInt();
            }

            printf("Enter marks for Course 4 (0-100): ");
            records[i].grade.course_04 = getValidInt();
            while (!validateMarks(records[i].grade.course_04))
            {
                printf("Invalid marks. Please enter value between 0-100: ");
                records[i].grade.course_04 = getValidInt();
            }

            calculateTotalAndPercentage(&records[i]);
            printf("Marks entered successfully!\n");
            return;
        }
    }

    printf("Student ID not found.\n");
}

void insertSort(StudentRecord records[], int count, int byId, int *count_measu)
{
    if (count == 0)
    {
        printf("No student records found. Please create records first.\n");
        return;
    }

    *count_measu = 0;

    // Linear insertion sort
    for (int i = 1; i < count; i++)
    {
        StudentRecord key = records[i];
        int j = i - 1;

        while (j >= 0)
        {
            (*count_measu)++; // Count comparison

            if (byId)
            {
                if (records[j].info.st_id > key.info.st_id)
                {
                    records[j + 1] = records[j];
                    j--;
                }
                else
                {
                    break;
                }
            }
            else
            { // Sort by age
                if (records[j].info.age > key.info.age)
                {
                    records[j + 1] = records[j];
                    j--;
                }
                else
                {
                    break;
                }
            }
        }

        records[j + 1] = key;
    }

    printf("\n==== Student Information (Sorted by %s) ====\n", byId ? "ID" : "Age");
    printf("%-10s %-15s %-15s %-5s %-12s\n", "ID", "Last Name", "First Name", "Age", "Course Code");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-10d %-15s %-15s %-5d %-12s\n",
               records[i].info.st_id,
               records[i].info.last_name,
               records[i].info.first_name,
               records[i].info.age,
               records[i].info.course_code);
    }

    printf("\nInsertion Sort Performance:\n");
    printf("Number of comparisons: %d\n", *count_measu);
}

void quickSort(StudentRecord records[], int low, int high, int *count_measu)
{
    if (low < high)
    {
        int pivot_index = partition(records, low, high, count_measu);
        quickSort(records, low, pivot_index - 1, count_measu);
        quickSort(records, pivot_index + 1, high, count_measu);
    }
}

void performQuickSort(StudentRecord records[], int count)
{
    if (count == 0)
    {
        printf("No student records found. Please create records first.\n");
        return;
    }

    // Create a copy to sort
    StudentRecord *sortedRecords = (StudentRecord *)malloc(count * sizeof(StudentRecord));
    if (sortedRecords == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    memcpy(sortedRecords, records, count * sizeof(StudentRecord));
    int count_measu = 0;

    quickSort(sortedRecords, 0, count - 1, &count_measu);

    printf("\n==== Student Info (Sort by Percent in Desc Order) ====\n");
    printf("%-10s %-15s %-8s %-8s %-8s %-8s %-8s %-10s\n",
           "ID", "Name", "Course1", "Course2", "Course3", "Course4", "Total", "Percentage");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        char full_name[100];
        sprintf(full_name, "%s %s", sortedRecords[i].info.first_name, sortedRecords[i].info.last_name);

        printf("%-10d %-15s %-8d %-8d %-8d %-8d %-8d %-10.2f\n",
               sortedRecords[i].info.st_id,
               full_name,
               sortedRecords[i].grade.course_01,
               sortedRecords[i].grade.course_02,
               sortedRecords[i].grade.course_03,
               sortedRecords[i].grade.course_04,
               sortedRecords[i].grade.total,
               sortedRecords[i].grade.percentage);
    }

    printf("\nQuick Sort Performance:\n");
    printf("Number of comparisons: %d\n", count_measu);

    free(sortedRecords);
}

TreeNode *createNode(StudentRecord record)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = record;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

TreeNode *insertNode(TreeNode *root, StudentRecord record)
{
    if (root == NULL)
    {
        return createNode(record);
    }

    if (record.info.st_id < root->data.info.st_id)
    {
        root->left = insertNode(root->left, record);
    }
    else if (record.info.st_id > root->data.info.st_id)
    {
        root->right = insertNode(root->right, record);
    }

    return root;
}

TreeNode *searchStudent(TreeNode *root, int st_id, int *count_measu)
{
    if (root == NULL || root->data.info.st_id == st_id)
    {
        (*count_measu)++;
        return root;
    }

    (*count_measu)++;
    if (st_id < root->data.info.st_id)
    {
        return searchStudent(root->left, st_id, count_measu);
    }
    else
    {
        return searchStudent(root->right, st_id, count_measu);
    }
}

void displayStudentDetails(const StudentRecord *student)
{
    printf("\n==== Student Details ====\n");
    printf("ID: %d\n", student->info.st_id);
    printf("Name: %s %s\n", student->info.first_name, student->info.last_name);
    printf("Age: %d\n", student->info.age);
    printf("Course Code: %s\n", student->info.course_code);
    printf("\nGrades:\n");
    printf("Course 1: %d\n", student->grade.course_01);
    printf("Course 2: %d\n", student->grade.course_02);
    printf("Course 3: %d\n", student->grade.course_03);
    printf("Course 4: %d\n", student->grade.course_04);
    printf("Total: %d\n", student->grade.total);
    printf("Percentage: %.2f%%\n", student->grade.percentage);
}

void inOrderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("ID: %d, Name: %s %s\n",
               root->data.info.st_id,
               root->data.info.first_name,
               root->data.info.last_name);
        inOrderTraversal(root->right);
    }
}

void performBinarySearch(TreeNode *root)
{
    if (root == NULL)
    {
        printf("No student records found in the binary search tree.\n");
        return;
    }

    printf("Enter Student ID to search: ");
    int st_id = getValidInt();

    int count_measu = 0;
    TreeNode *result = searchStudent(root, st_id, &count_measu);

    if (result != NULL)
    {
        displayStudentDetails(&result->data);
        printf("\nBinary Search Performance:\n");
        printf("Number of comparisons: %d\n", count_measu);
    }
    else
    {
        printf("\nStudent ID %d not found.\n", st_id);
        printf("\nBinary Search Performance:\n");
        printf("Number of comparisons: %d\n", count_measu);
        return; // Return without showing tree contents
    }

    // Only show tree contents if user wants to see them
    char choice;
    printf("\nWould you like to see all student records? (y/n): ");
    scanf(" %c", &choice);
    while (getchar() != '\n')
        ; // Clear input buffer

    if (choice == 'y' || choice == 'Y')
    {
        printf("\n==== All Student Records (In-Order Traversal) ===\n");
        inOrderTraversal(root);
    }
}

void freeTree(TreeNode *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    StudentRecord students[MAX_STUDENTS];
    TreeNode *root = NULL;
    int count = 0;
    int choice;

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        choice = getValidInt();

        switch (choice)
        {
        case 1:
            createStudentRecord(students, &count);
            break;
        case 2:
            studfunc(students, count);
            break;
        case 3:
            markfunc(students, count);
            break;
        case 4:
            printf("\n==== Student Totals and Percentages ===\n");
            printf("%-10s %-20s %-8s %-12s\n", "ID", "Name", "Total", "Percentage");
            printf("-------------------------------------------------\n");
            for (int i = 0; i < count; i++)
            {
                calculateTotalAndPercentage(&students[i]);
                printf("%-10d %-20s %-8d %-12.2f%%\n",
                       students[i].info.st_id,
                       students[i].info.first_name,
                       students[i].grade.total,
                       students[i].grade.percentage);
            }
            printf("\nTotal and percentage calculated for all students.\n");
            break;
        case 5:
        {
            int sortChoice;
            do
            {
                printf("Sort by: (1) ID or (2) Age? ");
                sortChoice = getValidInt();
                if (sortChoice != 1 && sortChoice != 2)
                {
                    printf("Invalid choice. Please enter 1 for ID or 2 for Age.\n");
                }
            } while (sortChoice != 1 && sortChoice != 2);

            int count_measu = 0;
            insertSort(students, count, sortChoice == 1, &count_measu);
            break;
        }
        case 6:
            performQuickSort(students, count);
            break;
        case 7:
            // Create BST for binary search
            freeTree(root); // Free any existing tree
            root = NULL;
            for (int i = 0; i < count; i++)
            {
                root = insertNode(root, students[i]);
            }
            performBinarySearch(root);
            break;
        case 8:
            printf("Exiting program. Bye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    freeTree(root);

    return 0;
}