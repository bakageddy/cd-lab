#ifndef __LEXER_H
#define __LEXER_H

#include <stddef.h>

typedef enum {
	RPAREN,
	LPAREN,
	IDENT,
	NUMBER,
	COMMA,
	PERIOD,
	SEMI,
	HASH,
	COLON,
	LT,
	GT,
	EQ,
	PLUS,
	MINUS,
	SLASH,
	PERCENT,
	RSLASH,
	DQUOTE,
	SQUOTE,
	BANG,
	LBRACE,
	RBRACE,
	LBRACKET,
	RBRACKET,
	AMPERSAND,
	PIPE,
	END,
} TokenType;

typedef struct {
	TokenType type;
	// Type == IDENT
	char* symbol;
	size_t len;
} Token;

typedef struct {
	char* contents;
	size_t len;
	size_t cursor;
	char curr;
} lexer_t;

lexer_t* init_lexer(char* contents, const size_t len);
char peek(lexer_t* lexer);
void consume(lexer_t* lexer);
void skip_whitespace(lexer_t* lexer);
int is_whitespace(char ch);

Token* token();
void token_append(Token* token, char ch);
Token* next_token(lexer_t* lexer);
void print_token(Token* token);

#endif // __LEXER_H
