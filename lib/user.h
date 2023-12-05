#ifndef USER_DOT_H
#define USER_DOT_H

struct user {
    char username[255];
    char password[255];
    char role[255];
};

int login(char *username);
void showUser();
void removeUser(char cuser[100]);
void addNewUser(char cuser[100]);


#endif
