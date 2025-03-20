#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    // Write code
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;

    // Write line
    if (chunk->lineCount == 0 || chunk->lines[chunk->lineCount - 1].line != line) {
        // New line
        if (chunk->lineCapacity < chunk->lineCount + 1) {
            int oldCapacity = chunk->lineCapacity;
            chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
            chunk->lines = GROW_ARRAY(struct LineRun, chunk->lines, oldCapacity, chunk->lineCapacity);
        }
        chunk->lines[chunk->lineCount].line = line;
        chunk->lines[chunk->lineCount].runLength = 1;
        chunk->lineCount++;
    } else {
        // Extend existing line run
        chunk->lines[chunk->lineCount - 1].runLength++;
    }
}

int getLine(Chunk *chunk, int offset) {
    int currentIndex = 0;
    for (int i = 0; i < chunk->lineCount; i++) {
        currentIndex += chunk->lines[i].runLength;
        if (offset < currentIndex) {
            return chunk->lines[i].line;
        }
    }
    return -1;
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(struct LineRun, chunk->lines, chunk->lineCapacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}