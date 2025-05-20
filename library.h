// library.h
#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 1000
#define MAX_USERS 500
#define MAX_NAME_LEN 100
#define MAX_TITLE_LEN 100
#define MAX_PASSWORD_LEN 30

typedef enum { ADMIN, USER } Role;

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_NAME_LEN];
    int available;
} Book;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char password[MAX_PASSWORD_LEN];
    Role role;
} User;

extern Book books[MAX_BOOKS];
extern User users[MAX_USERS];
extern int bookCount;
extern int userCount;

void loadBooks();
void saveBooks();
void loadUsers();
void saveUsers();

void adminMenu();
void userMenu(int userId);

void addBook();
void listBooks();
void searchBook();
void borrowBook(int userId);
void returnBook(int userId);

void registerUser();
int login();

#endif
