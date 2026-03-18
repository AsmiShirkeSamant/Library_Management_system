#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct
{
    int id, copyno;
    char title[30], author[30];
} books;

typedef struct
{
    int sid, issueid;
    time_t issueDate, returnDate;
    char name[50], cl[5];
} student;

books b[100];
student s[100];
int bcount = 0, scount = 0, i, j, max = 100;

void edit()
{
    int c, btemp, flag = 0;
    while (1)
    {
        printf("What changes would you like to make to the list?\n 1: Add books\n 2: Remove books\n");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            if (bcount >= max)
            {
                printf("Library FULL!");
                return;
            }
            else //adding the book to the database fr
            {
                printf("Enter the Title of the book: ");
                scanf(" %[^\n]", b[bcount].title);
                printf("Enter the Author of the book: ");
                scanf(" %[^\n]", b[bcount].author);
                printf("Enter the ID of the book: ");
                scanf("%d", &b[bcount].id);
                printf("Enter the number of copies of the book: ");
                scanf("%d", &b[bcount].copyno);
                bcount++;
                printf("The entry has been added successfully!\n");
            }
            return;

        case 2:
            printf("Enter the ID of the book: ");
            scanf("%d", &btemp);
            for (i = 0; i < bcount; i++)
            {
                if (btemp == b[i].id)
                {
                    flag = 1;
                    for (j = i; j < bcount - 1; j++)
                    {
                        b[j] = b[j + 1];
                    }
                    bcount--;
                    break;
                }
            }

            if (flag == 1)
                printf("The entry has been erased.\n");
            else
                printf("Book not found...\n");
            return;

        default:
            printf("Invalid entry. Try a valid choice.\n");
        }
    }
}

void issue()
{
    int stemp, btemp;
    books *bk = NULL;
    student *st = NULL;

    printf("Enter the ID of the student: ");
    scanf("%d", &stemp);
    printf("Enter the ID of the book: ");
    scanf("%d", &btemp);

    //find student by id
    for (i = 0; i < scount; i++)
    {
        if (stemp == s[i].sid)
        {
            st = &s[i];
            break;
        }
    }
    if (st == NULL)
    {
        printf("Student not found...\n");
        return;
    } //in case student is not registered

    //find book by id
    for (i = 0; i < bcount; i++)
    {
        if (btemp == b[i].id)
        {
            bk = &b[i];
            break;
        }
    }

    if (bk == NULL)
    {
        printf("Book not found...\n");
        return;
    }

    if (bk->copyno < 1)
    {
        printf("Insufficient copies...\n");
        return;
    }

    //issue the book
    st->issueid = btemp;
    bk->copyno--;
    time(&st->issueDate);
    printf("The book was issued on:  %s", ctime(&st->issueDate));
}

void re()
{
    int stemp, btemp;
    double dayspast, fine;
    books *bk = NULL;
    student *st = NULL;
    printf("Enter the ID of the student: ");
    scanf("%d", &stemp);
    printf("Enter the ID of the book: ");
    scanf("%d", &btemp);

    for (i = 0; i < scount; i++) //checking if the student exists in database
    {
        if (stemp == s[i].sid)
        {
            st = &s[i];
            break;
        }
    }
    if (st == NULL)
    {
        printf("Student not found...\n");
        return;
    }

    for (i = 0; i < bcount; i++)
    {
        if (btemp == b[i].id)
        {
            bk = &b[i];
            break;
        }
    }
    if (st->issueid != btemp) //Checking if book was issued to student
    {
        printf("Book was not issued to this student...\n");
        return;
    }

    if (bk == NULL) //checking if book exists in database
    {
        printf("Book not found...\n");
        return;
    }

    //if book does exist and is returned by student
    bk->copyno++;
    time(&st->returnDate);
    printf("The book was returned on:  %s\n", ctime(&st->returnDate));
    dayspast = (difftime(st->returnDate, st->issueDate) / (60 * 60 * 24)) - 7;

    if (dayspast <= 0)
        printf("Thank you for returning the book on time!\nNo late fees to be paid.\n");
    else
    {
        fine = dayspast * 100;
        printf("You have passed the deadline by %0.2f, hence you have to pay: %0.2f\n", dayspast, fine);
    }
    st->issueid = 0;
    st->issueDate = 0;
    st->returnDate = 0;
}

void inventory() //Display all books in library
{
    printf("\nID | TITLE | AUTHOR | COPIES\n");
    for (i = 0; i < bcount; i++)
    {
        printf("%d | %s | %s | %d\n", b[i].id, b[i].title, b[i].author, b[i].copyno);
    }
}

void studentDatabase() //display students in database
{
    printf("\nID | NAME | CLASS | BOOK ID\n");
    for (i = 0; i < scount; i++)
    {
        printf("%d | %s | %s | ", s[i].sid, s[i].name, s[i].cl);
        if (s[i].issueid > 0)
            printf("%d\n", s[i].issueid);
        else
            printf("N/A\n");
    }
}

void addStud() //add student to database
{
    int flag = 0, stemp;
    printf("Enter the ID of the student: ");
    scanf("%d", &stemp);

    for (i = 0; i < scount; i++)
    {
        if (stemp == s[i].sid)
        {
            flag = 1;
        }
    }

    if (flag == 1)
    {
        printf("Student is already in database...\n");
        return;
    }

    s[scount].sid = stemp;
    printf("Enter the Name of the student: ");
    scanf(" %[^\n]", s[scount].name);
    printf("Enter the class of the student: ");
    scanf("%s", s[scount].cl);
    s[scount].issueid = 0;
    scount++; //student count goes up
    printf("The student was added successfully!\n");
}

int main()
{
    int choice = 0, c;
    printf("Welcome :D\n");
    printf("Enter the total max capacity of books: ");
    scanf("%d", &max);

    do
    {
        printf("\n1: Edit book list\n2: Student Database\n3: Check inventory\n4: Issue a book\n5: Return a book\n6: Add Student\n");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            edit();
            break;
        case 2:
            studentDatabase();
            break;
        case 3:
            inventory();
            break;
        case 4:
            issue();
            break;
        case 5:
            re();
            break;
        case 6:
            addStud();
            break;
        default:
            printf("Invalid entry. Try a valid choice.\n");
        }

        printf("Return to menu? 1: yes 0: no : ");
        scanf("%d", &choice);

    } while (choice == 1);

    printf("Thank you for using the system! :D\n");
    return 0;
}