#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

static void expression() {

}

static void consume() {
    
}

static void advance() {

}

bool compile(const char *source, Chunk *chunk) {
    initScanner(source);
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");
}