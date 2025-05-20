// main.c
#include <stdio.h>
#include "library.h"

int main() {
    loadBooks();
    loadUsers();

    printf("==== Library Management System ====\n");

    while (1) 
    {
        printf("\n1. Login\n2. Register\n3. Exit\nChoose option: ");
        int opt;
        scanf("%d", &opt);

        if (opt == 1) {
            int userId = login();
            if (userId == -1) {
                printf("Invalid login.\n");
            } else {
                Role role = users[userId - 1].role;
                if (role == ADMIN)
                    adminMenu();
                else
                    userMenu(userId);
            }
        } else if (opt == 2) {
            registerUser();
        } else if (opt == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
