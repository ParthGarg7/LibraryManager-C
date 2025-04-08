#ifndef LIB_H
#define LIB_H

// Define struct Book first, since it's used in Student
struct Book
{
    int bookID;
    char bookName[50];
    int bookCopy;
    char bookAuthor[50];
};

// Define struct Student
struct Student
{
    char StudentName[50];
    long long int StudentRollNo;
    char StudentCourse[50];
    char StudentYear[10];
    int StudentID;
    struct Book books[5];  // Array of books for each student
    int NoOfBookBorrowed;
};

// Define struct StudentUser
struct StudentUser
{
    struct Student Student[100];  // Array of 100 students
    int StudentNum;  // Number of students
};

// Define struct library
struct library
{
    struct Book books[100];  // Admin can add up to 100 books
    int BookNum;  // Number of books in the library
};

// Declare a global instance of StudentUser and library, but do not define them here.
extern struct StudentUser MyStudent;
extern struct library Mylibrary;

#endif  // End of include guard
