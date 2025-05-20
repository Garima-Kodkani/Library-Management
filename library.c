// library.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

Book books[MAX_BOOKS];
User users[MAX_USERS];
int bookCount = 0;
int userCount = 0;

void loadBooks() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp) {
        fread(&bookCount, sizeof(int), 1, fp);
        fread(books, sizeof(Book), bookCount, fp);
        fclose(fp);
    }
}

void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");
    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

void loadUsers() {
    FILE *fp = fopen("users.dat", "rb");
    if (fp) {
        fread(&userCount, sizeof(int), 1, fp);
        fread(users, sizeof(User), userCount, fp);
        fclose(fp);
    }
}

void saveUsers() {
    FILE *fp = fopen("users.dat", "wb");
    fwrite(&userCount, sizeof(int), 1, fp);
    fwrite(users, sizeof(User), userCount, fp);
    fclose(fp);
}

void addBook() {
    Book b;
    b.id = bookCount + 1;
    printf("Enter title: ");
    getchar(); // clear newline
    fgets(b.title, MAX_TITLE_LEN, stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter author: ");
    fgets(b.author, MAX_NAME_LEN, stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    b.available = 1;

    books[bookCount++] = b;
    saveBooks();
    printf("Book added successfully.\n");
}

void listBooks() {
    printf("\n%-5s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
    for (int i = 0; i < bookCount; ++i) {
        printf("%-5d %-30s %-20s %-10s\n", books[i].id, books[i].title, books[i].author,
               books[i].available ? "Available" : "Issued");
    }
}

void searchBook() {
    char keyword[MAX_TITLE_LEN];
    printf("Enter keyword to search: ");
    getchar();
    fgets(keyword, MAX_TITLE_LEN, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("Results:\n");
    for (int i = 0; i < bookCount; ++i) {
        if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword)) {
            printf("ID: %d | Title: %s | Author: %s | %s\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].available ? "Available" : "Issued");
        }
    }
}

void borrowBook(int userId) {
    int id;
    listBooks();
    printf("Enter Book ID to borrow: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; ++i) {
        if (books[i].id == id) {
            if (books[i].available) {
                books[i].available = 0;
                saveBooks();
                printf("Book borrowed successfully.\n");
                return;
            } else {
                printf("Book is already issued.\n");
                return;
            }
        }
    }
    printf("Book not found.\n");
}

void returnBook(int userId) {
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; ++i) {
        if (books[i].id == id) {
            if (!books[i].available) {
                books[i].available = 1;
                saveBooks();
                printf("Book returned successfully.\n");
                return;
            } else {
                printf("Book is not issued.\n");
                return;
            }
        }
    }
    printf("Book not found.\n");
}

void registerUser() 
{
    char name[MAX_NAME_LEN];
    getchar();  // clear newline

    printf("Enter desired username: ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    // Check if user already exists
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            printf("Username already exists. Please login instead.\n");
            return;
        }
    }

    User u;
    u.id = userCount + 1;
    strcpy(u.name, name);

    printf("Enter password: ");
    fgets(u.password, MAX_PASSWORD_LEN, stdin);
    u.password[strcspn(u.password, "\n")] = 0;

    char roleChar;
    printf("Is this user admin? (y/n): ");
    scanf(" %c", &roleChar);
    u.role = (roleChar == 'y' || roleChar == 'Y') ? ADMIN : USER;

    users[userCount++] = u;
    saveUsers();
    printf("User registered successfully. Please login now.\n");
}

int login() {
    char name[MAX_NAME_LEN], password[MAX_PASSWORD_LEN];
    printf("Enter username: ");
    getchar();
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].name, name) == 0 && strcmp(users[i].password, password) == 0) {
            return users[i].id;
        }
    }
    return -1;
}

void adminMenu() {
    int choice;
    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Book\n2. List Books\n3. Search Book\n4. Register User\n5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addBook(); break;
            case 2: listBooks(); break;
            case 3: searchBook(); break;
            case 4: registerUser(); break;
        }
    } while (choice != 5);
}

void userMenu(int userId) {
    int choice;
    do {
        printf("\n--- User Menu ---\n");
        printf("1. List Books\n2. Search Book\n3. Borrow Book\n4. Return Book\n5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: listBooks(); break;
            case 2: searchBook(); break;
            case 3: borrowBook(userId); break;
            case 4: returnBook(userId); break;
        }
    } while (choice != 5);
}
