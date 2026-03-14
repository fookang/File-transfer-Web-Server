#ifndef COOKIE_H
#define COOKIE_H

#include <stdlib.h>

#define COOKIE_FILE_PATH "Data/cookies.txt"
#define RAW_COOKIE_LEN 256
#define COOKIE_LEN (RAW_COOKIE_LEN * 2)

struct cookie
{
    char name[64];
    char value[COOKIE_LEN + 1];
    struct cookie *next;
};

extern struct cookie *cookies;

int load_cookies();

void create_cookie(const char *username, char *cookie_value, size_t value_size);

void reload_cookies(struct cookie **cookies);

char *verify_cookie(const char *cookie_value);

void free_cookies();

#endif
