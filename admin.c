#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "books.c"
#include "lib.h"

void Adminlogin();
void AdminOperations();

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

// no of book issued
// no of book remaining
void AdminOperations()
{
    LoadBookData();
    int choice;

    while (1)
    {
        printf("Admin Operations\n");
        printf("Press 1 for Adding Book\n");
        printf("press 2 for Displaying Books\n");
        printf("Press 3 for Deleting Book\n");
        printf("Press 4 for Displaying Students\n");
        printf("Press 5 for Exit\n");
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

            printf("There are total %d Students\n", MyStudent.StudentNum);
            printf("Here is a list of current Students\n");

            printf("StudentID\tStudent Name\t\tStudent Course\t\tStudent year\tStudent Roll Number\n");
            for (int i = 0; i < MyStudent.StudentNum; i++)
                printf("%d\t%s\t\t%s\t\t%d\t%d", MyStudent.Student[i].StudentID, MyStudent.Student[i].StudentName, MyStudent.Student[i].StudentCourse, MyStudent.Student[i].StudentYear, MyStudent.Student[i].StudentRollNo);
        }
        break;

        case 5:
        {
            SaveBookData();
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

// new or old student alag alag login karwana h
