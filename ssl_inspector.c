#include <stdio.h>
#include <stdint.h>
#include "ssl_locl.h"

typedef unsigned char u8;

typedef struct {
    u8* client_random;
    size_t client_random_size;
    u8* master_key;
    size_t master_key_size;
} private_keys;

__declspec(noinline)
extern
void ssl_read_pk_data(struct ssl_st* ssl, private_keys* output) {
    if (ssl == NULL || output == NULL) {
        return;
    }
    struct ssl_session_st* session = ssl->session;
    output->client_random = ssl->s3->client_random;
    output->client_random_size = SSL3_RANDOM_SIZE;
    if (session == NULL) {
        return;
    }
    output->master_key = session->master_key;
    output->master_key_size = session->master_key_length;
}

__declspec(noinline)
extern
void* ssl_get_ssl_connect(struct ssl_st* ssl) {
    if (ssl == NULL) {
        return 0;
    }
    return ssl->method->ssl_connect;
}
