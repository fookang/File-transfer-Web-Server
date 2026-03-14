#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>

#include "cookie.h"

struct cookie *cookies = 0;

int load_cookies()
{
    FILE *file = fopen(COOKIE_FILE_PATH, "r");
    if (!file)
        return 0;

    while (1)
    {
        struct cookie *ck = (struct cookie *)calloc(1, sizeof(struct cookie));

        if (fscanf(file, "%63s %512s", ck->name, ck->value) == 2)
        {
            ck->next = cookies;
            cookies = ck;
        }
        else
        {
            free(ck);
            break;
        }
    }
    fclose(file);

    return 1;
}

void create_cookie(const char *username, char *cookie_value, size_t value_size)
{
    if (value_size < COOKIE_LEN + 1)
        return;

    unsigned char raw_cookie[RAW_COOKIE_LEN];

    if (RAND_bytes(raw_cookie, RAW_COOKIE_LEN) != 1)
    {
        fprintf(stderr, "Failed to generate salt.\n");
        return;
    }
    for (size_t i = 0; i < RAW_COOKIE_LEN; i++)
    {
        snprintf(&cookie_value[i * 2], 3, "%02x", raw_cookie[i]);
    }
    cookie_value[COOKIE_LEN] = 0;

    FILE *file = fopen(COOKIE_FILE_PATH, "a");
    if (file)
    {
        fprintf(file, "%s ", username);
        for (size_t i = 0; i < RAW_COOKIE_LEN; i++)
        {
            fprintf(file, "%02x", raw_cookie[i]);
        }
        fprintf(file, "\n");
        fclose(file);
    }
}

void reload_cookies()
{
    struct cookie *ck = cookies;
    while (ck)
    {
        struct cookie *next = ck->next;
        free(ck);
        ck = next;
    }
    cookies = NULL;
    load_cookies();
}

char *verify_cookie(const char *cookie_value)
{
    struct cookie *ck = cookies;
    while (ck)
    {
        if (strcmp(cookie_value, ck->value) == 0)
        {
            return ck->name;
        }

        ck = ck->next;
    }
    return NULL;
}

void free_cookies()
{
    struct cookie *current = cookies;
    while (current)
    {
        struct cookie *next = current->next;
        free(current);
        current = next;
    }
}
