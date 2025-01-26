#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.c"

int main()
{
    int logincount = 0;
    char User[10];

    while (logincount < 3)
    {
        printf("Welcome to the library\n");
        printf("ADMIN OR STUDENT\n");

        fgets(User, sizeof(User), stdin);
        User[strcspn(User, "\n")] = 0; // Remove newline character

        if (strcmp(User, "ADMIN") == 0 || strcmp(User, "admin") == 0)
        {
            printf("Welcome Admin\n");
            break;
        }
        else if (strcmp(User, "STUDENT") == 0 || strcmp(User, "student") == 0)
        {
            printf("Welcome Student\n");
            break;
        }
        else
        {
            printf("Wrong input\n");
        }

        logincount += 1; // Increment after checking input
        printf("%d login left\n", 3 - logincount);
    }

    if (strcmp(User, "ADMIN") == 0 || strcmp(User, "admin") == 0)
    {
        Adminlogin();
    }

    return 0;
}
