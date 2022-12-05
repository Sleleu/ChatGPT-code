#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

struct Hasher {
    pthread_mutex_t lock;
    uint64_t hash;
};

void hasher_init(struct Hasher *hasher) {
    pthread_mutex_init(&hasher->lock, NULL);
    hasher->hash = 0;
}

void hasher_write(struct Hasher *hasher, const char *bytes, size_t len) {
    pthread_mutex_lock(&hasher->lock);
    for (size_t i = 0; i < len; i++) {
        hasher->hash = (hasher->hash * 31) + bytes[i];
    }
    pthread_mutex_unlock(&hasher->lock);
}

uint64_t hasher_finish(struct Hasher *hasher) {
    pthread_mutex_lock(&hasher->lock);
    uint64_t hash = hasher->hash;
    pthread_mutex_unlock(&hasher->lock);
    return hash;
}

uint64_t hash_password(const char *password) {
    struct Hasher hasher;
    hasher_init(&hasher);
    hasher_write(&hasher, password, strlen(password));
    return hasher_finish(&hasher);
}

int main(void) {
    char *users[2][2] = {
        { "secret", "johndoe" },
        { "password", "janedoe" },
    };

    for (size_t i = 0; i < 2; i++) {
        uint64_t hash = hash_password(users[i][0]);
        printf("Utilisateur %s : %lu\n", users[i][1], hash);
    }

    return 0;
}
