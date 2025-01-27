#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "lib.h"

// Define the actual global instances
struct StudentUser MyStudent;

void LoadStudentData();
void StudentLogin();
void AddStudent(char *, int);
void DisplayStudents();
void StudentOperations();
void BorrowBook();
void ReturnBook();
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
    LoadStudentData();

    int key = 0;
    long long int Roll_no;
    char Name[50];
    printf("Enter your Name and RollNo\n");

    printf("Enter Name: ");
    fgets(Name, sizeof(Name), stdin);
    Name[strcspn(Name, "\n")] = 0;

    printf("Enter RollNo: ");
    scanf("%lld", &Roll_no);
    getchar();

    for (int i = 0; i < MyStudent.StudentNum; i++)
    {
        if (Roll_no == MyStudent.Student[i].StudentRollNo)
        {
            key = 1;
            break;
        }
    }

    if (MyStudent.StudentNum == 0)
    {
        AddStudent(Name, Roll_no);
        StudentOperations();
    }
    else if (key == 1)
    {
        StudentOperations();
    }
    else
    {
        AddStudent(Name, Roll_no);
        StudentOperations();
    }

    return;
}

void AddStudent(char *Name, int RollNo)
{
    printf("Welcome %s\n", Name);
    printf("New Student registration\n");

    struct Student *NewStudent = &MyStudent.Student[MyStudent.StudentNum];

    NewStudent->StudentID = MyStudent.StudentNum + 1;

    strcpy(NewStudent->StudentName, Name);

    printf("Enter Your Course: ");
    fgets(NewStudent->StudentCourse, sizeof(NewStudent->StudentCourse), stdin);
    NewStudent->StudentCourse[strcspn(NewStudent->StudentCourse, "\n")] = 0;

    printf("Enter Your Course Year ");
    scanf("%d", &NewStudent->StudentYear);
    getchar();

    NewStudent->StudentRollNo = RollNo;

    // Increment the Student count
    MyStudent.StudentNum += 1;

    printf("%s library registration complete\n\n", Name);

    return;
}

void DisplayStudents()
{
    printf("There are total %d Students\n", MyStudent.StudentNum);
    printf("Here is a list of current Students\n");

    printf("StudentID\tStudent Name\t\tStudent Course\t\tStudent year\tStudent Roll Number\n");
    for (int i = 0; i < MyStudent.StudentNum; i++)
        printf("%d\t%s\t\t%s\t\t%d\t%d", MyStudent.Student[i].StudentID, MyStudent.Student[i].StudentName, MyStudent.Student[i].StudentCourse, MyStudent.Student[i].StudentYear, MyStudent.Student[i].StudentRollNo);

    // printf("Book ID\t\tBook Name\t\tBook Author\t\tBook Copies\n");
    // for (int i = 0; i < Mylibrary.BookNum; i++)
    //     printf("%d\t\t%s\t\t\t%s\t\t\t%d\n", Mylibrary.books[i].bookID, Mylibrary.books[i].bookName, Mylibrary.books[i].bookAuthor, Mylibrary.books[i].bookCopy);

    getch();
    return;
}

void StudentOperations()
{
    int choice;

    while (1)
    {
        printf("Student Operations\n");
        printf("Press 1 for Borrowing Book\n");
        printf("press 2 for Displaying Books\n");
        printf("Press 3 for Returning Book\n");
        printf("Press 4 for Exit\n");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            BorrowBook();
            break;

        case 2:
        {
            // Fetch the current number of books
            FILE *fp1;

            fp1 = fopen("book number.txt", "r");
            fscanf(fp1, "%d", &Mylibrary.BookNum);
            fclose(fp1);

            FILE *fp2;

            fp2 = fopen("BooksData.txt", "rb");
            fread(&Mylibrary, sizeof(struct library), 1, fp2); // Read the struct from the file
            fclose(fp2);

            printf("There are total %d Books in the library\n", Mylibrary.BookNum);
            printf("Here is a list of currently available books\n");
            printf("Book ID\t\tBook Name\t\tBook Author\t\tBook Copies\n");
            for (int i = 0; i < Mylibrary.BookNum; i++)
                printf("%d\t\t%s\t\t\t%s\t\t\t%d\n", Mylibrary.books[i].bookID, Mylibrary.books[i].bookName, Mylibrary.books[i].bookAuthor, Mylibrary.books[i].bookCopy);
            getch();
        }
        break;

        case 3:
            ReturnBook();
            break;

        case 4:
        {
            SaveStudentData();
            exit(0);
        }

        break;

        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return;
}

void BorrowBook()
{
    return;
}

void ReturnBook()
{
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
