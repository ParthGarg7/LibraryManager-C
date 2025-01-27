#include <stdio.h>
#include <conio.h>
#include <direct.h>
#include <stdlib.h>
#include "lib.h"

void LoadBookData();
void AddBook();
void DisplayBooks();
void DeleteBook();
void SaveBookData();

struct library Mylibrary;

void LoadBookData()
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

    return;
}

void AddBook()
{
    struct Book *NewBook = &Mylibrary.books[Mylibrary.BookNum];

    NewBook->bookID = Mylibrary.BookNum + 1;

    printf("Enter Book Name: ");
    fgets(NewBook->bookName, sizeof(NewBook->bookName), stdin);
    NewBook->bookName[strcspn(NewBook->bookName, "\n")] = 0;

    printf("Enter Book Author: ");
    fgets(NewBook->bookAuthor, sizeof(NewBook->bookAuthor), stdin);
    NewBook->bookAuthor[strcspn(NewBook->bookAuthor, "\n")] = 0;

    printf("Enter Number of Copies: ");
    scanf("%d", &NewBook->bookCopy);
    getchar();

    // Increment the book count
    Mylibrary.BookNum += 1;
    printf("Book added successfully!\n Total Books: %d\n", Mylibrary.BookNum);

    return;
}

void DisplayBooks()
{

    printf("There are total %d Books in the library\n", Mylibrary.BookNum);
    printf("Here is a list of currently available books\n");
    printf("Book ID\t\tBook Name\t\tBook Author\t\tBook Copies\n");
    for (int i = 0; i < Mylibrary.BookNum; i++)
        printf("%d\t\t%s\t\t\t%s\t\t\t%d\n", Mylibrary.books[i].bookID, Mylibrary.books[i].bookName, Mylibrary.books[i].bookAuthor, Mylibrary.books[i].bookCopy);
    getch();

    return;
}

void DeleteBook()
{
    int ID;

    if (Mylibrary.BookNum == 0)
    {
        printf("The library is empty.\n");
        return;
    }

    printf("There are total %d Books in the library\n", Mylibrary.BookNum);
    printf("Here is a list of currently available books\n");
    printf("Book ID\t\tBook Name\t\tBook Author\t\tBook Copies\n");
    for (int i = 0; i < Mylibrary.BookNum; i++)
        printf("%d\t\t%s\t\t\t%s\t\t\t%d\n\n", Mylibrary.books[i].bookID, Mylibrary.books[i].bookName, Mylibrary.books[i].bookAuthor, Mylibrary.books[i].bookCopy);

    printf("Enter the ID to delete the Book\n");
    scanf("%d", &ID);
    getchar();

    if (ID >= Mylibrary.BookNum)
    {
        printf("Wrong ID\n");
        return;
    }
    else
    {
        for (int i = ID; i < Mylibrary.BookNum; i++)
        {
            Mylibrary.books[i].bookID -= 1;
            Mylibrary.books[i - 1] = Mylibrary.books[i];
        }

        Mylibrary.BookNum -= 1;
        printf("Book Deleted successfully! \nTotal Books: %d\n", Mylibrary.BookNum);
        return;
    }
}

void SaveBookData()
{
    // Save the updated book count to the file
    FILE *fp1;

    fp1 = fopen("book number.txt", "w");
    fprintf(fp1, "%d", Mylibrary.BookNum);
    fclose(fp1);

    FILE *fp2;

    fp2 = fopen("BooksData.txt", "wb");
    fwrite(&Mylibrary, sizeof(struct library), 1, fp2);
    fclose(fp2);

    return;
}
