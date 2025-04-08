#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

long long int LoginID = 12345;
char LoginPass[] = "adminPass";
long long int AdminID;
char AdminPass[50];

void Adminlogin();
void AdminOperations();
void DisplayStudents();
void DeleteStudentData();

void LoadBookData();
void AddBook();
void DisplayBooks();
void DeleteBook();
void SaveBookData();

void LoadStudentData();
void StudentLogin();
void AddStudent();
void StudentOperations(int);
void BorrowBook(int);
void DisplayBook();
void DisplayBorrowedBook(int);
void ReturnBook(int);
void SaveStudentData();

// Define struct Book first, since it's used in Student
struct Book
{
    int bookID;
    char bookName[50];
    int bookCopy;
    char bookAuthor[50];
};

// Define struct Student
struct Student
{
    char StudentName[50];
    long long int StudentRollNo;
    char StudentCourse[50];
    char StudentYear[10];
    int StudentID;
    struct Book books[5]; // Array of books for each student
    int NoOfBookBorrowed;
};

// Define struct StudentUser
struct StudentUser
{
    struct Student Student[100]; // Array of 100 students
    int StudentNum;              // Number of students
} MyStudent;

// Define struct library
struct library
{
    struct Book books[100]; // Admin can add up to 100 books
    int BookNum;            // Number of books in the library
} Mylibrary;

int main()
{
    LoadBookData();
    LoadStudentData();
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
            Adminlogin();
            break;
        }
        else if (strcmp(User, "STUDENT") == 0 || strcmp(User, "student") == 0)
        {
            printf("Welcome Student\n");
            StudentLogin();
            break;
        }
        else
        {
            printf("Wrong input\n");
        }

        logincount += 1; // Increment after checking input
        printf("%d login left\n", 3 - logincount);
    }

    return 0;
}

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
            exit(0);
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

void LoadBookData()
{
    // Fetch the current number of books
    FILE *fp1;

    // Try to open the file for reading
    fp1 = fopen("bookNumber.txt", "r");

    if (fp1 == NULL)
    {
        // File doesn't exist — first run!
        //printf("File not found. Creating new file and initializing book number to 0...\n");

        // Set initial book number to 0
        Mylibrary.BookNum = 0;

        // Create the file and write 0 to it
        fp1 = fopen("bookNumber.txt", "w");
        if (fp1 != NULL)
        {
            fprintf(fp1, "%d", Mylibrary.BookNum);
            fclose(fp1);
        }
        else
        {
            printf("Failed to create file!\n");
        }
    }
    else
    {
        // File exists, read the current book number
        fscanf(fp1, "%d", &Mylibrary.BookNum);
        fclose(fp1);
    }

    FILE *fp2;

    fp2 = fopen("booksData.txt", "rb");
    if (fp2 != NULL)
    {
        fread(&Mylibrary, sizeof(struct library), 1, fp2); // Read the struct from the file
        fclose(fp2);
    }

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

    fp1 = fopen("bookNumber.txt", "w");
    fprintf(fp1, "%d", Mylibrary.BookNum);
    fclose(fp1);

    FILE *fp2;

    fp2 = fopen("booksData.txt", "wb");
    fwrite(&Mylibrary, sizeof(struct library), 1, fp2);
    fclose(fp2);

    return;
}

void LoadStudentData()
{
    // Fetch the current number of Students
    FILE *fp1;

    fp1 = fopen("studentNumber.txt", "r");
    if (fp1 == NULL)
    {
        // File doesn't exist — first run!
        //printf("File not found. Creating new file and initializing student number to 0...\n");

        // Set initial book number to 0
        MyStudent.StudentNum = 0;

        // Create the file and write 0 to it
        fp1 = fopen("studentNumber .txt", "w");
        if (fp1 != NULL)
        {
            fprintf(fp1, "%d", MyStudent.StudentNum);
            fclose(fp1);
        }
        else
        {
            printf("Failed to create file!\n");
        }
    }
    fscanf(fp1, "%d", &MyStudent.StudentNum);
    fclose(fp1);

    FILE *fp2;

    fp2 = fopen("studentsData.txt", "rb");
    if (fp2 != NULL)
    {
        fread(&MyStudent, sizeof(struct StudentUser), 1, fp2); // Read the struct from the file
        fclose(fp2);
    }

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
                MyStudent.Student[index].books[i] = MyStudent.Student[index].books[i + 1];

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

    fp1 = fopen("studentNumber.txt", "w");
    fprintf(fp1, "%d", MyStudent.StudentNum);
    fclose(fp1);

    FILE *fp2;

    fp2 = fopen("studentsData.txt", "wb");
    fwrite(&MyStudent, sizeof(struct StudentUser), 1, fp2);
    fclose(fp2);

    return;
}


