#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.c"
#include "student.c"


void Developer();

int main()
{
    LoadStudentData();
    LoadBookData();

    char User[10];

    while (1)
    {
        printf("Welcome to the library\n");
        printf("ADMIN OR STUDENT OR DEVELOPER\n");

        fgets(User, sizeof(User), stdin);
        User[strcspn(User, "\n")] = 0; // Remove newline character

        if (strcmp(User, "ADMIN") == 0 || strcmp(User, "admin") == 0)
        {
            printf("Welcome Admin\n");
            Adminlogin();
            break;
        }
        else if (strcmp(User, "STUDENT") == 0 || strcmp(User, "student") == 0)
        {
            printf("Welcome Student\n");
            StudentLogin();
            break;
        }
        else if (strcmp(User, "D") == 0 || strcmp(User, "d") == 0)
        {
            Developer();
        }
        else
        {
            printf("Wrong input\n");
        }

    }

    return 0;
}

void Developer()
{
    int key;
    printf("Welcome Developer\n");

    printf("Press 1 for admin operation\nPress 2 for student operations\nPress 3 for exit\n");
    scanf("%d", &key);
    getchar();
    if (key == 1)
    {
        AdminOperations();
    }
    else if (key == 2)
    {
        StudentLogin();
    }
    else
    {
        exit(0);
    }
    return;
}