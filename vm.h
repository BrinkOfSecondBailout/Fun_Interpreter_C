#ifndef vm_h
#define vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    Chunk *chunk;
    uint8_t *ip;
    Value stack[STACK_MAX];
    Value *stackTop;
} VM;

void initVm();
void freeVm();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif