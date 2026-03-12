#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <sys/socket.h>
#include <openssl/ssl.h>
#define MAX_REQUEST_SIZE (1024 * 1024)

enum encoding_type
{
    none,
    length,
    chunked
};

struct client_info
{
    socklen_t address_length;
    struct sockaddr_storage address;
    char address_buffer[128];
    int socket;
    SSL *ssl;
    char request[MAX_REQUEST_SIZE + 1];
    int received; // number of bytes received in request
    struct client_info *next;
    int remaining_bytes;
    enum encoding_type encoding;
};

extern struct client_info *client_list;

struct client_info *create_client_info(void);
int get_encoding_type(struct client_info *client);

#endif
