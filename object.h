#ifndef object_h
#define object_h

#include "common.h"
#include "chunk.h"
#include "value.h"


#define OBJ_TYPE(value)         (AS_OBJ(value)->type)

#define IS_CLOSURE(value)      isObjType(value, OBJ_CLOSURE)
#define IS_NATIVE(value)        isObjType(value, OBJ_NATIVE)
#define IS_FUNCTION(value)      isObjType(value, OBJ_FUNCTION)
#define IS_STRING(value)        isObjType(value, OBJ_STRING)

#define AS_CLOSURE(value)      ((ObjClosure*)AS_OBJ(value))
#define AS_NATIVE(value) \
        (((ObjNative*)AS_OBJ(value))->function)
#define AS_FUNCTION(value)      ((ObjFunction*)AS_OBJ(value))
#define AS_STRING(value)        ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)       (((ObjString*)AS_OBJ(value))->chars)


typedef enum {
    OBJ_FUNCTION,
    OBJ_CLOSURE,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE,
} ObjType;

struct Obj {
    ObjType type;
    struct Obj *next;
    bool isMarked;
};

typedef struct {
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk chunk;
    ObjString *name;
} ObjFunction;

typedef Value (*NativeFn)(int argCount, Value* args);

typedef struct {
    Obj obj;
    NativeFn function;
} ObjNative;

struct ObjString {
    Obj obj;
    int length;
    char *chars;
    uint32_t hash;
};

typedef struct ObjUpvalue {
    Obj obj;
    Value* location;
    struct ObjUpvalue* next;
    Value closed;
} ObjUpvalue;

typedef struct {
    Obj obj;
    ObjFunction *function;
    ObjUpvalue** upvalues;
    int upvalueCount;
} ObjClosure;

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

ObjClosure* newClosure(ObjFunction* function);
ObjString *copyString(const char *chars, int length);
ObjUpvalue* newUpvalue(Value* slot);
ObjString *takeString(char *chars, int length);
void printObject(Value value);
ObjFunction *newFunction();
ObjNative* newNative(NativeFn function);

#endif