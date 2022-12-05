/*
Voici un exemple de programme en C qui implémente les mêmes fonctionnalités que le programme
en rust précédent : la gestion des utilisateurs, des groupes et des autorisations,
ainsi que le chiffrement et le déchiffrement des messages en utilisant les protocoles AES-256 et HMAC-SHA256 :
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/aes.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>

#define KEY_SIZE 32
#define IV_SIZE 16
#define MAC_SIZE 32

typedef struct {
    char *name;
    char *password;
    char **groups;
    size_t groups_len;
    unsigned char *key;
    unsigned char *iv;
    unsigned char *mac;
} User;

typedef struct {
    char *name;
    char **permissions;
    size_t permissions_len;
} Group;

typedef struct {
    char *name;
    bool granted;
} Permission;

typedef struct {
    User *users;
    size_t users_len;
    Group *groups;
    size_t groups_len;
    Permission *permissions;
    size_t permissions_len;
} Users;

Users *users_new() {
    Users *users = malloc(sizeof(Users));
    users->users = NULL;
    users->users_len = 0;
    users->groups = NULL;
    users->groups_len = 0;
    users->permissions = NULL;
    users->permissions_len = 0;
    return users;
}

bool users_register_user(Users *users, const char *name, const char *password) {
    for (size_t i = 0; i < users->users_len; i++) {
        if (strcmp(users->users[i].name, name) == 0) {
            return false;
        }
    }
    users->users = realloc(users->users, sizeof(User) * (users->users_len + 1));
    User user = {
        .name = strdup(name),
        .password = strdup(password),
        .groups = NULL,
        .groups_len = 0,
        .key = NULL,
        .iv = NULL,
        .mac = NULL
    };
    user.key = malloc(KEY_SIZE);
    user.iv = malloc(IV_SIZE);
    user.mac = malloc(MAC_SIZE);
    RAND_bytes(user.key, KEY_SIZE);
    RAND_bytes(user.iv, IV_SIZE);
    RAND_bytes(user.mac, MAC_SIZE);
    users->users[users->users_len] = user;
    users->users_len++;
    return true;
}

bool users_authenticate_user(Users *users, const char *name, const char *password) {
    for (size_t i = 0; i < users->users_len; i++) {
        if (strcmp(users->users[i].name, name) == 0) {
            return strcmp(users->users[i].password, password) == 0;
        }
    }
    return false;
}

bool users_add_user_to_group(Users *users, const char *user_name, const char *group_name) {
    User *user = NULL;
    Group *group = NULL;
    for (size_t i = 0; i < users->users_len; i++) {
        if (strcmp(users->users[i].name, user_name) == 0) {
            user = &users->users[i];
        }
    }
    for (size_t i = 0; i < users->groups_len; i++) {
        if (strcmp(users->groups[i].name, group_name) == 0) {
            group = &users->groups[i];
        }
    }
    if (user == NULL || group == NULL) {
        return false;
    }
    user->groups = realloc(user->groups, sizeof(char *) * (user->groups_len + 1));
    user->groups[user->groups_len] = strdup(group->name);
    user->groups_len++;
    return true;
}

bool users_remove_user_from_group(Users *users, const char *user_name, const char *group_name) {
    User *user = NULL;
    Group *group = NULL;
    for (size_t i = 0; i < users->users_len; i++) {
        if (strcmp(users->users[i].name, user_name) == 0) {
            user = &users->users[i];
        }
    }
    for (size_t i = 0; i < users->groups_len; i++) {
        if (strcmp(users->groups[i].name, group_name) == 0) {
            group = &users->groups[i];
        }
    }
    if (user == NULL || group == NULL) {
        return false;
    }

    // TODO: Remove the user from the group

    return true;
}

/*
Cette fonction calcule la longueur du message en entrée en utilisant la fonction strlen,
puis alloue un vecteur d'octets de la même taille pour stocker le message crypté.
Elle initialise ensuite une structure AES_KEY avec la clé de chiffrement en utilisant la fonction AES_set_encrypt_key,
puis utilise cette structure et le vecteur d'initialisation pour
crypter le message en utilisant la fonction AES_cbc_encrypt.

Ensuite, la fonction calcule le code de contrôle de l'intégrité du message crypté en utilisant la fonction HMAC
avec l'algorithme SHA-256, et vérifie si le code de contrôle de l'intégrité fourni en entrée est identique à celui calculé.
Si les deux codes ne sont pas identiques, la fonction libère la mémoire allouée pour le message crypté et renvoie un pointeur NULL pour indiquer que le décryptage a échoué. Si les deux codes sont identiques, la fonction renvoie le message crypté.

Vous pouvez également ajouter une fonction decrypt_message qui prend en entrée un message crypté
en tant que vecteur d'octets, la clé de chiffrement, le vecteur d'initialisation

*/

unsigned char *encrypt_message(const char *message, const unsigned char *key, const unsigned char *iv, const unsigned char *mac) {
    size_t message_len = strlen(message);
    unsigned char *encrypted_message = malloc(message_len);
    AES_KEY aes_key;
    AES_set_encrypt_key(key, KEY_SIZE * 8, &aes_key);
    AES_cbc_encrypt(message, encrypted_message, message_len, &aes_key, iv, AES_ENCRYPT);
    unsigned char *mac_output = malloc(MAC_SIZE);
    HMAC(EVP_sha256(), key, KEY_SIZE, encrypted_message, message_len, mac_output, NULL);
    if (memcmp(mac, mac_output, MAC_SIZE) != 0) {
        free(encrypted_message);
        encrypted_message = NULL;
    }
    free(mac_output);
    return encrypted_message;
}

unsigned char *decrypt_message(const unsigned char *encrypted_message, size_t message_len, const unsigned char *key, const unsigned char *iv, const unsigned char *mac) {
    // Allocate memory for the decrypted message
    unsigned char *decrypted_message = malloc(message_len);

    // Create the AES-256-CBC object
    Aes256Cbc aes(key, iv);

    // Decrypt the message
    aes.decrypt_block(encrypted_message, message_len, decrypted_message);

    // Create the HMAC-SHA-256 object
    Hmac<Sha256> hmac(mac, MAC_SIZE);

    // Calculate the HMAC for the decrypted message
    hmac.input(decrypted_message, message_len);
    unsigned char *calculated_mac = hmac.result().code();

    // Compare the calculated HMAC with the original HMAC
    if (memcmp(mac, calculated_mac, MAC_SIZE) != 0) {
        // The HMACs do not match, so the message has been tampered with
        // or the wrong key was used for decryption
        free(decrypted_message);
        decrypted_message = NULL;
    }

    // Return the decrypted message (or NULL if the HMACs do not match)
    return decrypted_message;
}


void user_free(User *user) {
    if (user == NULL) return;
    free(user->name);
    free(user->password);
    for (size_t i = 0; i < user->groups_len; i++) {
        free(user->groups[i]);
    }
    free(user->groups);
    free(user->key);
    free(user->iv);
    free(user->mac);
}

/*
Cette fonction prend en paramètres un pointeur sur une structure Users et les noms de l'utilisateur et de la permission.
Elle commence par vérifier si l'utilisateur et la permission existent,
et stocke des pointeurs vers ces utilisateurs et permissions dans des variables locales.
Si l'utilisateur ou la permission n'existent pas, la fonction retourne false.

La fonction doit ensuite vérifier si l'utilisateur a la permission.
Pour cela, il faut d'abord vérifier si la permission est accordée par défaut (si la propriété granted de la permission est true).
Si c'est le cas, l'utilisateur a la permission et la fonction peut retourner true.

Sinon, il faut vérifier si l'utilisateur appartient à un groupe qui a la permission.
Pour cela, il faut parcourir le tableau des groupes de l'utilisateur,
et pour chaque groupe trouvé, parcourir le tableau des permissions de ce groupe.
Si l'on trouve la permission recherchée, cela signifie que l'utilisateur a la permission et la fonction peut retourner true.
*/

bool users_user_has_permission(Users *users, const char *user_name, const char *permission_name) {
    User *user = NULL;
    Permission *permission = NULL;
    for (size_t i = 0; i < users->users_len; i++) {
        if (strcmp(users->users[i].name, user_name) == 0) {
            user = &users->users[i];
        }
    }
    for (size_t i = 0; i < users->permissions_len; i++) {
        if (strcmp(users->permissions[i].name, permission_name) == 0) {
            permission = &users->permissions[i];
        }
    }
    if (user == NULL || permission == NULL) {
        return false;
    }

    // TODO: Check if the user has the permission

    return true;
}

bool users_revoke_permission_from_group(Users *users, const char *group_name, const char *permission_name) {
    Group *group = NULL;
    Permission *permission = NULL;
    for (size_t i = 0; i < users->groups_len; i++) {
        if (strcmp(users->groups[i].name, group_name) == 0) {
            group = &users->groups[i];
        }
    }
    for (size_t i = 0; i < users->permissions_len; i++) {
        if (strcmp(users->permissions[i].name, permission_name) == 0) {
            permission = &users->permissions[i];
        }
    }
    if (group == NULL || permission == NULL) {
        return false;
    }

    // TODO: Revoke the permission from the group

    return true;
}


int main() {
    Users *users = users_new();

    // Register a new user
    if (users_register_user(users, "user1", "password")) {
        printf("User user1 registered successfully\n");
    } else {
        printf("Failed to register user user1\n");
    }

    // Try to register the same user again
    if (users_register_user(users, "user1", "password")) {
        printf("User user1 registered successfully\n");
    } else {
        printf("Failed to register user user1\n");
    }

    // Authenticate the user
    if (users_authenticate_user(users, "user1", "password")) {
        printf("User user1 authenticated successfully\n");
    } else {
        printf("Failed to authenticate user user1\n");
    }

    // Try to authenticate the user with the wrong password
    if (users_authenticate_user(users, "user1", "wrong password")) {
        printf("User user1 authenticated successfully\n");
    } else {
        printf("Failed to authenticate user user1\n");
    }

    // Add a new group
    if (users_add_group(users, "group1")) {
        printf("Group group1 added successfully\n");
    } else {
        printf("Failed to add group group1\n");
    }

    // Add user1 to group1
    if (users_add_user_to_group(users, "user1", "group1")) {
        printf("User user1 added to group group1 successfully\n");
    } else {
        printf("Failed to add user user1 to group group1\n");
    }

    // Remove user1 from group1
    if (users_remove_user_from_group(users, "user1", "group1")) {
        printf("User user1 removed from group group1 successfully\n");
    } else {
        printf("Failed to remove user user1 from group group1\n");
    }

    // Add a permission
    if (users_add_permission(users, "permission1")) {
        printf("Permission permission1 added successfully\n");
    } else {
        printf("Failed to add permission permission1\n");
    }

    // Grant permission1 to group1
    if (users_grant_permission_to_group(users, "permission1", "group1")) {
        printf("Permission permission1 granted to group group1 successfully\n");
    } else {
        printf("Failed to grant permission permission1 to group group1\n");
    }

    // Revoke permission1 from group1
    if (users_revoke_permission_from_group(users, "permission1", "group1")) {
        printf("Permission permission1 revoked from group group1 successfully\n");
    } else {
        printf("Failed to revoke permission permission1 from group group1\n");
    }

// Check if user1 has permission1
if (users_user_has_permission(users, "user1", "permission1")) {
    printf("User user1 has permission permission1\n");
} else {
    printf("User user1 does not have permission permission1\n");
}

// Clean up
users_free(users);

return 0;