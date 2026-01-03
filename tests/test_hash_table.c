#include "fridayc.h"
#include "ctest.h"

void TestHash();
void TestHashTableCreate();
void TestHashTableLookUp();
void TestHashTableInsert();
void TestHashTableRemove();
void TestHashTableContains();
void TestHashTableRehash();
void TestHashTableDestroy();
void TestSuite();


i32 main() {
  TestSuite();
}

void TestHash() {
  const char* s1 = "testfoo";
  const char* s2 = "testbar";

  u64 h1 = hash(s1);
  u64 h2 = hash(s2);

  assertNotEquals(h1, h2);
  
  h1 = hash(s1);
  h2 = hash(s1);

  assertEquals(h1, h2);
}

void TestHashTableCreate() {
  HashTable table = HashTableCreate();

  assertEquals(0, table.size);
  assertEquals(HASH_TABLE_INITIAL_CAPACITY, table.capacity);
  assertNotEquals(NULL, table.buckets);
  assertEquals(HASH_TABLE_INITIAL_CAPACITY * sizeof(*table.buckets), _msize(table.buckets));
  
  HashTableDestroy(&table);
}

void TestHashTableInsert() {
  HashTable table = HashTableCreate();
  const char* key = "testfoobar";
  i32 value = 777;
  u64 h = hash(key) % table.capacity;

  Entry* e1 = HashTableInsert(&table, key, (void*)&value);
  assertNotEquals(NULL, e1);
  assertEquals(0, strcmp(key, e1->key));
  assertEquals(value, *((i32*)e1->value));
  assertEquals(NULL, e1->next);
  assertEquals(1, table.size);
  assertEquals(e1, table.buckets[h]);

  Entry* e2 = HashTableInsert(&table, key, NULL);
  assertEquals(e1, e2);
  assertEquals(NULL, e2->value);

  HashTableDestroy(&table);
}

void TestHashTableLookUp() {
  HashTable table = HashTableCreate();
  const char* key = "testfoobar";
  void* value = NULL;

  Entry* entry = HashTableLookUp(&table, key);
  assertEquals(NULL, entry);

  HashTableInsert(&table, key, value);
  entry = HashTableLookUp(&table, key);

  assertNotEquals(NULL, entry);
  assertEquals(0, strcmp(key, entry->key));
  assertEquals(value, entry->value);

  HashTableDestroy(&table);
}

void TestHashTableRemove() {

}

void TestHashTableContains() {
  HashTable table = HashTableCreate();
  const char* key = "testfoobar";
  void* value = NULL;

  bool result = HashTableContains(&table, key);
  assertFalse(result);

  Entry* entry = HashTableInsert(&table, key, value);
  result = HashTableContains(&table, key);

  assertTrue(result);
}

void TestHashTableRehash() {
  
}

void TestHashTableDestroy() {
  HashTable table = HashTableCreate();

  HashTableDestroy(&table);

  assertEquals(0, table.size);
  assertEquals(0, table.capacity);
  assertEquals(NULL, table.buckets);
}


void TestSuite() {
  TestHash();
  TestHashTableCreate();
  TestHashTableRehash();
  TestHashTableLookUp();
  TestHashTableInsert();
  TestHashTableRemove();
  TestHashTableContains();
  TestHashTableDestroy();
}
