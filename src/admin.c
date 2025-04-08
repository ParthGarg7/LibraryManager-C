#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "books.c"
#include "../include/lib.h"


void Adminlogin();
void AdminOperations();
void DisplayStudents();
void DeleteStudentData();

long long int LoginID = 7983655087;
char LoginPass[] = "7983655087";
long long int AdminID;
char AdminPass[50];

void Adminlogin()
{
    printf("Enter Admin ID and password\n");
    printf("Enter ID: ");
    scanf("%lld", &AdminID);
    getchar();
    printf("Enter Password: ");
    fgets(AdminPass, sizeof(AdminPass), stdin);
    AdminPass[strcspn(AdminPass, "\n")] = 0;

    if (LoginID == AdminID && strcmp(LoginPass, AdminPass) == 0)
    {
        printf("Admin login successful\n");
        AdminOperations();
    }
    else
    {
        printf("Admin login failed\n");
    }

    return;
}

void AdminOperations()
{

    int choice;

    while (1)
    {
        printf("Admin Operations\n");
        printf("Press 1 for Adding Book\n");
        printf("press 2 for Displaying Books\n");
        printf("Press 3 for Deleting Book\n");
        printf("Press 4 for Deleting Student Data\n");
        printf("Press 5 for Displaying Students\n");
        printf("Press 6 for Exit\n");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            AddBook();
            break;

        case 2:
            DisplayBooks();
            break;

        case 3:
            DeleteBook();
            break;

        case 4:
            DeleteStudentData();
            break;

        case 5:
            DisplayStudents();
            break;

        case 6:
            SaveBookData();
            return;

        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return;
}

void DisplayStudents()
{
    printf("There are total %d Students\n", MyStudent.StudentNum);
    printf("Here is a list of Current Students\n\n\n");

    for (int i = 0; i < MyStudent.StudentNum; i++)
    {
        printf("StudentID\tStudent Name\t\tStudent Course\t\tStudent year\tStudent Roll Number\n");
        printf("%-15d %-25s %-25s %-15s %-20lld\n", MyStudent.Student[i].StudentID,
               MyStudent.Student[i].StudentName, MyStudent.Student[i].StudentCourse,
               MyStudent.Student[i].StudentYear, MyStudent.Student[i].StudentRollNo);

        printf("\n\n%s have borrowed %d books\n\n", MyStudent.Student[i].StudentName, MyStudent.Student[i].NoOfBookBorrowed);
        if (MyStudent.Student[i].NoOfBookBorrowed > 0)
        {
            printf("Here is the list of the books %s have borrowed\n\n", MyStudent.Student[i].StudentName);

            printf("Book ID\t\tBook Name\t\tBook Author\t\tBook Copies\n");
            for (int j = 0; j < MyStudent.Student[i].NoOfBookBorrowed; j++)
                printf("%-15d %-25s %-25s %-15d\n", MyStudent.Student[i].books[j].bookID,
                       MyStudent.Student[i].books[j].bookName, MyStudent.Student[i].books[j].bookAuthor,
                       MyStudent.Student[i].books[j].bookCopy);
        }

        printf("----------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    return;
}

void DeleteStudentData()
{
    int ID, i;

    if (MyStudent.StudentNum == 0)
    {
        printf("There is no student.\n");
        return;
    }

    printf("There are total %d Students\n", MyStudent.StudentNum);
    printf("Here is a list of Current Students\n\n\n");

    printf("StudentID\tStudent Name\t\tStudent Course\t\tStudent year\tStudent Roll Number\n");
    for (int i = 0; i < MyStudent.StudentNum; i++)
    {

        printf("%-15d %-25s %-25s %-15s %-20lld\n", MyStudent.Student[i].StudentID,
               MyStudent.Student[i].StudentName, MyStudent.Student[i].StudentCourse,
               MyStudent.Student[i].StudentYear, MyStudent.Student[i].StudentRollNo);

        printf("\n\n");
    }

    printf("Enter the Student ID to delete the student data\n");
    scanf("%d", &ID);
    getchar();

    if (ID >= MyStudent.StudentNum)
    {
        printf("Wrong ID\n");
        return;
    }
    else
    {
        for (i = ID; i < MyStudent.StudentNum; i++)
        {
            MyStudent.Student[i].StudentID -= 1;
            MyStudent.Student[i - 1] = MyStudent.Student[i];
        }

        MyStudent.StudentNum -= 1;
        printf("Student Data Deleted successfully! \nTotal Students: %d\n", MyStudent.StudentNum);
        return;
    }

    return;
}