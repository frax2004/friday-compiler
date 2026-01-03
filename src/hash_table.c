#include "fridayc.h"

u64 hash(const char* key) {
  u64 hash_value = 14695981039346656037ULL;
  
  for(; *key; ++key) {
    hash_value ^= (u64)(*key);
    hash_value *= 1099511628211ULL;
  }

  return hash_value;
}

HashTable HashTableCreate() {
  HashTable self;
  self.size = 0;
  self.capacity = HASH_TABLE_INITIAL_CAPACITY;
  self.buckets = (Entry**)calloc(self.capacity, sizeof(Entry*));
  return self;
}

void HashTableDestroy(HashTable* self) {
  for(u64 i = 0; i < self->capacity; ++i) {
    Entry* entry = self->buckets[i];
    while(entry != NULL) {
      Entry* temp = entry->next;
      free((void*)entry);
      entry = temp;
    }
  }
  free((void*)self->buckets);
  self->size = 0;
  self->capacity = 0;
  self->buckets = 0x0;
}

Entry* HashTableInsert(HashTable* self, const char* key, void* value) {
  if(self->size/(double)self->capacity >= .75) {
    HashTableRehash(self);
  }

  const u64 i = hash(key) % self->capacity;

  Entry** iter;
  for(
    iter = self->buckets + i;
    *iter != NULL && strcmp((*iter)->key, key) != 0;
    iter = &(*iter)->next
  );

  if(*iter == NULL) {
    *iter = (Entry*)malloc(sizeof(Entry));
    (*iter)->key = key;
    (*iter)->value = value;
    (*iter)->next = NULL;
    self->size += 1;
  } else (*iter)->value = value;

  return *iter;
}

bool HashTableContains(HashTable* self, const char* key) {
  const u64 i = hash(key) % self->capacity;
  
  Entry* entry;
  for(
    entry = self->buckets[i];
    entry != NULL && strcmp(key, entry->key) != 0;
    entry = entry->next
  );

  return entry != NULL;
}

Entry* HashTableLookUp(HashTable* self, const char* key) {
  const u64 i = hash(key) % self->capacity;
  
  Entry* entry;
  for(
    entry = self->buckets[i];
    entry != NULL && strcmp(key, entry->key) != 0;
    entry = entry->next
  );

  return entry;
}

void HashTableRemove(HashTable* self, const char* key) {

  const u64 i = hash(key) % self->capacity;

  Entry** iter;
  for(
    iter = self->buckets + i;
    *iter != NULL && strcmp((*iter)->key, key) != 0;
    iter = &(*iter)->next
  );

  if(*iter != NULL) {
    Entry* temp = (*iter)->next;
    free((void*)*iter);
    *iter = temp;
    self->size -= 1;
  }

}

void HashTableRehash(HashTable* self) {
  u64 capacity = (u64)(self->capacity * 2);
  Entry** buckets = (Entry**)calloc(capacity, sizeof(Entry*));

  for(u64 i = 0; i < self->capacity; ++i) {
    if(self->buckets[i] != NULL) {
      Entry* entry = self->buckets[i];
      while(entry != NULL) {
        Entry* temp = entry->next;
        
        u64 hash_value = hash(entry->key) % capacity;
        entry->next = buckets[hash_value];
        buckets[hash_value] = entry;

        entry = temp;
      }
    }
  }

  free((void*)self->buckets);
  self->buckets = buckets;
  self->capacity = capacity;
}

void HashTablePrint(FILE* file, HashTable* self) {
  fprintf(file, "{ \"size\": %llu, \"capacity\": %llu, \"load factor\": \"%lf\", \"buckets\": [", self->size, self->capacity, self->size/(double)self->capacity);
  fflush(file);

  bool first_bucket = true;
  for(u64 i = 0; i < self->capacity; ++i) {
    if(self->buckets[i] != NULL) {
      if(!first_bucket)
        fprintf(file, ", ");
      first_bucket = false;
      
      fprintf(
        file, 
        "{ \"hash\": %llu, \"entries\": [", 
        hash(self->buckets[i]->key) % self->capacity
      );
      fflush(file);
      for(Entry* entry = self->buckets[i]; entry != NULL; entry = entry->next) {
        fprintf(file, "{\"key\": \"%s\", \"value\": \"0x%x\"}%s", entry->key, entry->value, (entry->next != NULL ? ", " : ""));
        fflush(file);
      }
      fprintf(file, "]}");
      fflush(file);
    }
  }

  fprintf(file, "]}");
  fflush(file);
}
