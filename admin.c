#include <stdio.h>
#include <string.h>
#include <conio.h>

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
    }
    else
    {
        printf("Admin login failed\n");
    }
}
