#ifndef FRIDAYC_H
#define FRIDAYC_H
/*
|-------------------------------------|
|                                     |
|             TYPE ALIASES            |
|                                     |
|-------------------------------------|
*/

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef unsigned char byte;


typedef enum Result Result;
typedef struct Entry Entry;
typedef struct HashTable HashTable;

/*
|-------------------------------------|
|                                     |
|          STRUCTS DEFINITIONS        |
|                                     |
|-------------------------------------|
*/

enum Result {
  RESULT_SUCCESS,
  RESULT_FAILURE,
};

#define HASH_TABLE_INITIAL_CAPACITY 4

/// @brief Entry struct for hash table
struct Entry {
  /// @brief Entry key
  const char* key;
  /// @brief Entry value
  void* value;
  /// @brief Next entry
  Entry* next;
};

/// @brief Hash Table struct
struct HashTable {
  /// @brief Buckets
  Entry** buckets;
  /// @brief Entry count
  u64 size;
  /// @brief Buckets capacity
  u64 capacity;
};

/// @brief Hash function for strings
/// @param key the string to hash
/// @return The hash value for the string
u64 hash(const char* key);

/// @brief Create an hash table
/// @return Empty initialized hash table with initial capacity
HashTable HashTableCreate();

/// @brief Get the value mapped with `key` or **NULL** if `key` is not mapped 
/// @param self the hash table
/// @param key the key
/// @return Entry mapped with the key or NULL
Entry* HashTableLookUp(HashTable* self, const char* key);

/// @brief Inserts an entry in the hash table or change the value mapped with `key` if it was already mapped
/// @param self the hash table
/// @param key the key
/// @param value the value
/// @return Entry to the new mapped entry or the existing entry
Entry* HashTableInsert(HashTable* self, const char* key, void* value);

/// @brief Remove the entry with the same key
/// @param self the hash table
/// @param key the key
void HashTableRemove(HashTable* self, const char* key);

/// @brief Lookup the hash table to find the given key
/// @param self the hash table
/// @param key the key
/// @return `true` if the key is mapped in the hash table
bool HashTableContains(HashTable* self, const char* key);

/// @brief Rehash the hash table (called when `size/capacity >= load factor`)
/// @param self the hash table
void HashTableRehash(HashTable* self);

/// @brief Destroy the hash table
/// @param self the hash table
void HashTableDestroy(HashTable* self);

#endif
