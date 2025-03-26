#ifndef table_h
#define table_h

#include "common.h"
#include "value.h"

typedef struct {
    ObjString *key;
    Value value;
} Entry;

typedef struct {
    Entry *entries;
    int count;
    int capacity;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
void tableSet(Table *table, ObjString *key, Value value);

#endif