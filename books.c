#include <stdio.h>
#include <direct.h>

int BookNum();

struct Book
{
    int bookID;
    char bookName[50];
    int bookCopy;
    char bookAuthor[50];
};

struct library
{
    struct Book books[100]; // admin can add upto 100 books data
    int BookNum;
} Mylibrary;

int BookNum()
{
    int num;

    chdir("C:\\Users\\Garg Family\\3D Objects\\Programming\\Projects\\My C Projects\\Library managment system");
    FILE *fp1;

    fp1 = fopen("book number.txt", "r");

    fscanf(fp1, "%d", &num);

    fclose(fp1);

    return num;
}

void AddBook()
{
    // Fetch the current number of books
    Mylibrary.BookNum = BookNum();

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
    printf("Book added successfully! Total Books: %d\n", Mylibrary.BookNum);

    // Save the updated book count to the file
    FILE *fp1 = fopen("book number.txt", "w");
    if (fp1 != NULL)
    {
        fprintf(fp1, "%d", Mylibrary.BookNum);
        fclose(fp1);
    }

    SaveBook();

    return;
}

void SaveBook()
{
    FILE *fp2;
    fp2 = fopen("BooksData.txt", "wb");
    fwrite(&Mylibrary, sizeof(struct library), 1, fp2);
    fclose(fp2);
    return;
}