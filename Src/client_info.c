#include "client_info.h"
#include <stdlib.h>
#include <string.h>

struct client_info *client_list = 0;

struct client_info *create_client_info()
{
    struct client_info *n = (struct client_info *)calloc(1, sizeof(struct client_info));

    n->address_length = sizeof(n->address);
    n->next = client_list;
    n->remaining_bytes = 0;
    n->encoding = none;
    client_list = n;

    return n;
}

int get_encoding_type(struct client_info *client)
{
    char *q = strstr(client->request, "Content-Length: ");
    if (q)
    {
        client->encoding = length;
        q = strchr(q, ' ');
        q += 1;
        client->remaining_bytes = strtol(q, 0, 10);
        return 1;
    }
    else
    {
        q = strstr(client->request, "Transfer-Encoding: chunked");
        if (q)
        {
            client->encoding = chunked;
            client->remaining_bytes = 0;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}
