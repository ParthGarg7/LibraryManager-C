#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "lib.h"

// Define the actual global instances
struct StudentUser MyStudent;

void LoadStudentData();
void StudentLogin();
void AddStudent();
void StudentOperations(int);
void BorrowBook(int);
void DisplayBook();
void DisplayBorrowedBook(int);
void ReturnBook(int);
void SaveStudentData();

void LoadStudentData()
{
    // Fetch the current number of Students
    FILE *fp1;

    fp1 = fopen("Student number.txt", "r");
    fscanf(fp1, "%d", &MyStudent.StudentNum);
    fclose(fp1);

    FILE *fp2;

    fp2 = fopen("StudentsData.txt", "rb");
    fread(&MyStudent, sizeof(struct StudentUser), 1, fp2); // Read the struct from the file
    fclose(fp2);

    return;
}

void StudentLogin()
{
    int RollNo;
    int key = 0;
    char choice;

    printf("Welcome to the Student Management System\n\n");
    printf("Options:\n");
    printf("  [N] New Student Registration\n");
    printf("  [L] Login (for already registered students)\n");
    scanf("%c", &choice);
    getchar();

    if (choice == 'N' || choice == 'n')
    {
        AddStudent();
    }
    else if (choice == 'L' || choice == 'l')
    {
        printf("Enter Your RollNo (unique for every student) ");
        scanf("%d", &RollNo);
        getchar();

        for (key = 0; key < MyStudent.StudentNum; key++)
        {
            if (MyStudent.Student[key].StudentRollNo == RollNo)
            {
                StudentOperations(RollNo);
                break;
            }
        }
        if (key == MyStudent.StudentNum)
        {
            printf("Your Roll Number is not registered in the library\n");
            StudentLogin();
        }
    }
    else
    {
        printf("Wrong Input\n");
        StudentLogin();
    }

    return;
}

void AddStudent()
{
    printf("New Student registration\n\n");

    int RollNo;
    printf("Enter Your RollNo (unique for every student) ");
    scanf("%d", &RollNo);
    getchar();

    for (int i = 0; i < MyStudent.StudentNum; i++)
    {
        if (MyStudent.Student[i].StudentRollNo == RollNo)
        {
            printf("Roll Number %d already exist \n");
            StudentLogin();
        }
    }

    struct Student *NewStudent = &MyStudent.Student[MyStudent.StudentNum];

    NewStudent->StudentID = MyStudent.StudentNum + 1;

    printf("Enter Your Name: ");
    fgets(NewStudent->StudentName, sizeof(NewStudent->StudentName), stdin);
    NewStudent->StudentName[strcspn(NewStudent->StudentName, "\n")] = 0;

    printf("Enter Your Course: ");
    fgets(NewStudent->StudentCourse, sizeof(NewStudent->StudentCourse), stdin);
    NewStudent->StudentCourse[strcspn(NewStudent->StudentCourse, "\n")] = 0;

    printf("Enter Your Course Year: ");
    fgets(NewStudent->StudentYear, sizeof(NewStudent->StudentYear), stdin);
    NewStudent->StudentYear[strcspn(NewStudent->StudentYear, "\n")] = 0;

    NewStudent->StudentRollNo = RollNo;

    NewStudent->NoOfBookBorrowed = 0;

    // Increment the Student count
    MyStudent.StudentNum += 1;

    printf("%s library registration complete\n\n", NewStudent->StudentName);

    StudentOperations(RollNo);

    return;
}

void StudentOperations(int RollNo)
{
    int index;
    int choice;

    for (int i = 0; i < MyStudent.StudentNum; i++)
    {
        if (MyStudent.Student[i].StudentRollNo == RollNo)
            index = i;
    }

    while (1)
    {

        printf("Welcome %s\n", MyStudent.Student[index].StudentName);
        printf("Student Operations\n");
        printf("Press 1 for Borrowing Book\n");
        printf("press 2 for Displaying Books\n");
        printf("Press 3 for checking for borrowed book list\n");
        printf("Press 4 for Returning Book\n");
        printf("Press 5 for Exit\n");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            BorrowBook(index);
            break;

        case 2:
            DisplayBook();
            break;

        case 3:
            DisplayBorrowedBook(index);
            break;

        case 4:
            ReturnBook(index);
            break;

        case 5:
        {
            SaveStudentData();
            SaveBookData();
            return;
        }

        break;

        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return;
}

void BorrowBook(int index)
{
    int ID, key;

    printf("You have %d Borrowed books\n", MyStudent.Student[index].NoOfBookBorrowed);

    // To check if the student can borrow book or not
    if (MyStudent.Student[index].NoOfBookBorrowed >= 5)
    {
        printf("You can not borrow more than 5 books\n");
        getch();
        return;
    }
    else
    {
        DisplayBook();
        printf("Enter the ID of the book you want to borrow\n");
        scanf("%d", &ID);
        getchar();

        // For searching the book in the library
        for (key = 0; key < Mylibrary.BookNum; key++)
        {
            if (ID == Mylibrary.books[key].bookID)
            {
                // To check if the book can be rented or not
                if (Mylibrary.books[key].bookCopy > 0)
                {
                    Mylibrary.books[key].bookCopy -= 1;

                    strcpy(MyStudent.Student[index].books[MyStudent.Student[index].NoOfBookBorrowed].bookAuthor, Mylibrary.books[key].bookAuthor);
                    strcpy(MyStudent.Student[index].books[MyStudent.Student[index].NoOfBookBorrowed].bookName, Mylibrary.books[key].bookName);
                    MyStudent.Student[index].books[MyStudent.Student[index].NoOfBookBorrowed].bookID = Mylibrary.books[key].bookID;
                    MyStudent.Student[index].books[MyStudent.Student[index].NoOfBookBorrowed].bookCopy = 1;

                    MyStudent.Student[index].NoOfBookBorrowed += 1;
                    printf("Book Borrowed Successfully\n");
                    getch();
                    return;
                }
                else
                {
                    printf("Sorry, the Book you want to borrow is not available at the time\n");
                    getch();
                    return;
                }
            }
        }
        if (key == Mylibrary.BookNum)
        {
            printf("Invalid Book ID\n");
            getch();
            return;
        }
    }

    return;
}

void DisplayBook()
{
    printf("There are total %d Books in the library\n", Mylibrary.BookNum);
    printf("Here is a list of currently available books\n");
    printf("Book ID\t\tBook Name\t\tBook Author\t\tBook Copies\n");
    for (int i = 0; i < Mylibrary.BookNum; i++)
        printf("%-15d %-25s %-25s %-15d\n", Mylibrary.books[i].bookID,
               Mylibrary.books[i].bookName, Mylibrary.books[i].bookAuthor,
               Mylibrary.books[i].bookCopy);

    return;
}

void DisplayBorrowedBook(int index)
{
    printf("You have %d Borrowed books\n", MyStudent.Student[index].NoOfBookBorrowed);
    printf("Here is the list of the books you have borrowed\n\n");

    printf("Book ID\t\tBook Name\t\tBook Author\t\tBook Copies\n");
    for (int j = 0; j < MyStudent.Student[index].NoOfBookBorrowed; j++)
        printf("%-15d %-25s %-25s %-15d\n", MyStudent.Student[index].books[j].bookID,
               MyStudent.Student[index].books[j].bookName, MyStudent.Student[index].books[j].bookAuthor,
               MyStudent.Student[index].books[j].bookCopy);

    return;
}

void ReturnBook(int index)
{

    int ID, key;

    printf("You have %d Borrowed books\n", MyStudent.Student[index].NoOfBookBorrowed);

    if (MyStudent.Student[index].NoOfBookBorrowed == 0)
    {
        printf("You have no books to return\n");
        getch();
        return;
    }
    else if (MyStudent.Student[index].NoOfBookBorrowed > 0)
    {
        DisplayBorrowedBook(index);
    }

    printf("\nEnter the ID of the Book you want to return\n");
    scanf("%d", &ID);
    getchar();
    for (key = 0; key < MyStudent.Student[index].NoOfBookBorrowed; key++)
    {
        if (MyStudent.Student[index].books[key].bookID == ID)
        {

            for (int i = key; i < MyStudent.Student[index].NoOfBookBorrowed; i++)
                MyStudent.Student[index].books[i] = MyStudent.Student[index].books[i+1];

            MyStudent.Student[index].NoOfBookBorrowed -= 1;
            Mylibrary.books[ID - 1].bookCopy += 1;
            printf("Book returned successfully\n");
            return;
        }
    }
    if (key == MyStudent.Student[index].NoOfBookBorrowed)
    {
        printf("You do not have a Book of this ID\n");
        getch();
        return;
    }

    return;
}

void SaveStudentData()
{
    // Save the updated Student count to the file
    FILE *fp1;

    fp1 = fopen("Student number.txt", "w");
    fprintf(fp1, "%d", MyStudent.StudentNum);
    fclose(fp1);

    FILE *fp2;

    fp2 = fopen("StudentsData.txt", "wb");
    fwrite(&MyStudent, sizeof(struct StudentUser), 1, fp2);
    fclose(fp2);

    return;
}
