#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "books.c"

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

// add book
// del book
// search book
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
        printf("press 2 for Display Books\n");
        printf("Press 3 for Deleting Book\n");
        printf("Press 4 for Exit\n");
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
