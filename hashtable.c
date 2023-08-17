#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum size of the hash table
#define TABLE_SIZE 100

// Define a structure for key-value pairs
struct KeyValuePair {
    char* key;
    char* value;
    struct KeyValuePair* next;
};

// Define the hash table structure
struct HashTable {
    struct KeyValuePair* table[TABLE_SIZE];
};

// Hash function
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    for (size_t i = 0; i < strlen(key); i++) {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}

// Initialize a new hash table
struct HashTable* initHashTable() {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Insert a key-value pair into the hash table
void insert(struct HashTable* hashTable, const char* key, const char* value) {
    struct KeyValuePair* kvp = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
    kvp->key = strdup(key);
    kvp->value = strdup(value);
    kvp->next = NULL;
    
    unsigned int index = hash(key);
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = kvp;
    } else {
        // Handle collisions using linked list approach
        struct KeyValuePair* current = hashTable->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = kvp;
    }
}

// Retrieve a value based on a key
const char* get(struct HashTable* hashTable, const char* key) {
    unsigned int index = hash(key);
    struct KeyValuePair* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    
    return NULL;
}

// Remove a key-value pair from the hash table
void removeKey(struct HashTable* hashTable, const char* key) {
    unsigned int index = hash(key);
    struct KeyValuePair* current = hashTable->table[index];
    struct KeyValuePair* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hashTable->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int main() {
    struct HashTable* hashTable = initHashTable();
    
    insert(hashTable, "name", "John");
    insert(hashTable, "age", "25");
    insert(hashTable, "country", "USA");
    
    printf("Name: %s\n", get(hashTable, "name"));       // Output: John
    printf("Age: %s\n", get(hashTable, "age"));         // Output: 25
    printf("Country: %s\n", get(hashTable, "country")); // Output: USA
    
    removeKey(hashTable, "age");
    printf("Age: %s\n", get(hashTable, "age"));         // Output: (null)
    
    return 0;
}

