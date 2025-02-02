#ifndef USER_DATA_H
#define USER_DATA_H
#include <wchar.h>
#include <locale.h>

struct user_data {
    char user_name[100];
    char user_password[100];
    char user_email[100];
};

extern struct user_data user;
#endif
