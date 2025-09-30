# StudentSort - Advanced Database Management with Algorithm Analysis

A C-based student database management system that implements and analyzes multiple sorting and searching algorithms for academic record management.

## 📋 Overview

This program manages student records for an educational institution, featuring advanced data structure implementations including arrays, linked structures, and binary search trees. The system provides complete CRUD operations with performance analysis of different algorithms.

## ✨ Key Features

### Core Functionality
- **Student Record Management**: Complete student information and grade tracking
- **Multi-Algorithm Sorting**: Linear insertion sort and binary quicksort implementations
- **Advanced Searching**: Binary search tree with in-order traversal
- **Performance Analysis**: Real-time algorithm efficiency measurement
- **Data Validation**: Comprehensive input validation and error handling

### Algorithm Implementations
- **Insertion Sort** (Linear): Sort by student ID or age with comparison counting
- **Quick Sort** (Binary): Sort by percentage in descending order
- **Binary Search Tree**: Efficient student lookup with traversal options
- **Performance Metrics**: Detailed comparison and operation counting


## 🗃️ Data Structures

### Student Information
```c
typedef struct {
    int st_id;              // Student ID (up to 6 digits)
    char last_name[15];     // Student surname
    char first_name[15];    // Student first name
    int age;                // Student age (18-60)
    char course_code[10];   // Course code (format: letters_numbers)
} StudentInfo;
```

### Student Grades
```c
typedef struct {
    int st_id;              // Matching student ID
    int course_01;          // Course 1 grade (0-100)
    int course_02;          // Course 2 grade (0-100)
    int course_03;          // Course 3 grade (0-100)
    int course_04;          // Course 4 grade (0-100)
    int total;              // Sum of all courses
    float percentage;       // Average percentage
} StudentGrade;
```

### Binary Search Tree Node
```c
typedef struct TreeNode {
    StudentRecord data;     // Combined student record
    struct TreeNode *left;  // Left child pointer
    struct TreeNode *right; // Right child pointer
} TreeNode;
```

## 💡 Usage Guide

The program provides a comprehensive menu-driven interface:

### Main Menu Options
1. **Create Student Record** - Add new student with validation
2. **Read/Modify Student Info** - View and update student details
3. **Enter Grades** - Input course grades (4 courses per student)
4. **Calculate Totals** - Compute total scores and percentages
5. **Linear Sort Display** - Insertion sort by ID or Age with performance metrics
6. **Binary Sort Display** - QuickSort by percentage (descending) with metrics
7. **Binary Search Tree** - Search students with BST and traversal options
8. **Quit** - Exit with memory cleanup

### Sample Data Format
```
Student Information:
St_ID  Last_Name   First_Name  Age  Course_code
99172  Abram       James       22   CS_572
99568  King        Leons       19   CS_932

Student Grades:
St_ID  Course_01  Course_02  Course_03  Course_04  Total  Percentage
99172  70         80         65         90         305    76.25%
99568  82         60         55         50         247    61.75%
```

## 🔍 Algorithm Analysis

### Performance Measurement
The system includes built-in performance counters that track:
- **Comparison Operations**: Number of comparisons during sorting/searching
- **Time Complexity Analysis**: Real-time algorithm efficiency measurement
- **Space Complexity**: Memory usage optimization

### Algorithm Comparison
| Algorithm | Time Complexity | Use Case | Performance Counter |
|-----------|----------------|----------|-------------------|
| Insertion Sort | O(n²) | Small datasets, nearly sorted data | Comparison count |
| Quick Sort | O(n log n) avg | Large datasets, random data | Partition operations |
| Binary Search | O(log n) | Sorted tree search | Tree traversals |

## 🛠️ Technical Features

### Input Validation
- **Student ID**: 6-digit numeric validation with uniqueness check
- **Names**: 1-14 alphabetic characters only
- **Age**: Range validation (18-60 years)
- **Course Codes**: Format validation (letters + numbers + underscore)
- **Grades**: Range validation (0-100)

### Memory Management
- **Dynamic Allocation**: BST nodes with proper cleanup
- **Array Management**: Fixed-size array with bounds checking
- **Memory Leak Prevention**: Comprehensive memory deallocation

### Error Handling
- **Input Buffer Management**: Prevents buffer overflow
- **Data Type Validation**: Robust type checking
- **Boundary Checks**: Array and tree bounds validation
- **Graceful Degradation**: Continues operation on non-fatal errors

  *See word document for all error handling screenshots*

## 📊 Algorithm Performance Analysis

### Insertion Sort Performance
- **Best Case**: O(n) - Already sorted data
- **Worst Case**: O(n²) - Reverse sorted data
- **Space Complexity**: O(1) - In-place sorting
- **Stability**: Stable sort maintains relative order

### Quick Sort Performance
- **Average Case**: O(n log n) - Random data
- **Worst Case**: O(n²) - Already sorted data
- **Space Complexity**: O(log n) - Recursive stack
- **Optimization**: Descending order for percentage sorting

### Binary Search Tree Performance
- **Search Time**: O(log n) average, O(n) worst case
- **Insertion Time**: O(log n) average
- **Space Complexity**: O(n) for tree storage
- **Traversal**: In-order provides sorted output

## 🎓 Academic Context

### Core Concepts
- **Algorithm Analysis**: Practical implementation and performance measurement
- **Data Structure Design**: Efficient storage and retrieval mechanisms
- **Complexity Analysis**: Time and space complexity evaluation
- **Code Optimization**: Performance-conscious programming practices

### Learning Objectives
- Compare sorting algorithm efficiencies
- Implement binary search trees for fast lookups
- Analyze algorithm performance with real metrics
- Design robust input validation systems

## 📈 Performance Metrics Example

```
Insertion Sort Performance:
Number of comparisons: 45
Time complexity: O(n²)

Quick Sort Performance:
Number of comparisons: 23
Time complexity: O(n log n)

Binary Search Performance:
Number of comparisons: 3
Time complexity: O(log n)
```

## 📝 Future Enhancements

- **File I/O**: Save/load student records from files
- **Advanced Analytics**: GPA calculations and statistical analysis
- **GUI Interface**: Graphical user interface implementation
- **Database Integration**: SQL database backend support
- **Network Features**: Multi-user access capabilities

## 👤 Author

Steven Mahabir

---

*This implementation showcases advanced algorithm analysis techniques and provides practical experience with algorithm performance measurement in real-world applications.*
