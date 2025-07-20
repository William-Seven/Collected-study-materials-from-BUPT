// type.h
#ifndef TYPEKIND_H
#define TYPEKIND_H

typedef enum {
    INTEGER,
    REAL,
    CHAR_,
    STRING_,
    BOOLEAN_,
    NULL_TYPE
} BasicType;

enum TypeKind {
    _BASIC,
    _ARRAY,
    _RECORD
};

#endif // TYPEKIND_H