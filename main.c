#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int Prime = 53;

struct Node
{
    struct Node *next;
    char *key;
    int value;
};

struct Table
{
    size_t size;
    long long prime;
    struct Node **buckets;
};

size_t Hash(const char *key, const size_t size, const long long prime_local);
struct Table *create_table(const size_t size, const long long new_prime);
void write_table(const struct Table *table);
struct Node* list_add(struct Node* inz, const char *key, const int value);
void add_element(struct Table *table, const char *key, const int value);
int *find_element(struct Table *table, const char *key);
void remove_element(struct Table *table, const char *key);


int main()
{
    //printf("%d", Hash("123",99999, Prime));
    struct Table *my_table;
    my_table = create_table(10, Prime);

    add_element(my_table, "AKOC", 1000);
    add_element(my_table, "bd", 1020);
    add_element(my_table, "COKA", 10004);
    add_element(my_table, "A", 10003);
    add_element(my_table, "mipt", 102200);

    write_table(my_table);
    remove_element(my_table, "A");
    printf("Elemetn has been removed.");
    write_table(my_table);

    add_element(my_table, "Tuple", 10002);

    write_table(my_table);

    add_element(my_table, "Lol", 102);
    add_element(my_table, "123", 10009);

    write_table(my_table);

    int *rez = find_element(my_table, "F");

    printf("%d\n", (rez == NULL)? -1 : (*rez));

    return 0;
}

size_t Hash(const char *key, const size_t size, const long long prime_local)
{
    long long current_hash = 0, pow = 1;

    for (; *key != '\0'; ++key)
    {
        current_hash = (current_hash + ((long long) *key) * pow) % size;
        pow = (pow * prime_local) % size;
    }

    return current_hash;
}

struct Table *create_table(const size_t size, const long long new_prime)
{
    struct Table* new_table = malloc(size * sizeof(struct Table*));
    (*new_table).size = size;
    (*new_table).prime = new_prime;
    (*new_table).buckets = malloc(size * sizeof(struct Node));

    for (size_t i = 0; i < size; ++i)
    {
        (*new_table).buckets[i] = NULL;
    }

    return new_table;
}

void write_table(const struct Table *table)
{
    for (size_t i = 0; i < (*table).size; ++i)
    {
        struct Node *current_node = (*table).buckets[i];
        while (current_node != NULL)
        {
            printf("%s ", (*current_node).key);
            current_node = (*current_node).next;
        }
        printf(" NULL\n");
    }
    printf("\n");
}

struct Node* list_add(struct Node* inz, const char *key, const int value)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    (*new_node).next = inz;
    (*new_node).key = key;
    (*new_node).value = value;

    return new_node;
}

void add_element(struct Table *table, const char *key, const int value)
{
    size_t hash_key = Hash(key, table->size, table->prime);
    struct Node *inz = table->buckets[hash_key];
    table->buckets[hash_key] = list_add(inz, key, value);
}

int *find_element(struct Table *table, const char *key)
{
    size_t hash_key = Hash(key,(*table).size, (*table).prime);
    struct Node *inz = (*table).buckets[hash_key];

    while ((inz != NULL) && (strcmp(inz->key, key) != 0))
        inz = (*inz).next;

    return (inz == NULL)? NULL : &(inz->value);
}

void remove_element(struct Table *table, const char *key)
{
    size_t hash_key = Hash(key,(*table).size, (*table).prime);
    struct Node *inz = table->buckets[hash_key];

    if (inz == NULL)
        return;

    if (strcmp(inz->key, key) == 0)
    {
        struct Node *temp = inz->next;
        free(inz);
        table->buckets[hash_key] = temp;
        return;
    }


    while ((inz->next != NULL) && (strcmp(inz->next->key, key) != 0))
        inz = (*inz).next;

    if ((inz->next != NULL) && (strcmp(inz->next->key, key) == 0))
    {
        struct Node *temp = inz->next->next;
        free(inz->next);
        inz->next = temp;
    }

}

