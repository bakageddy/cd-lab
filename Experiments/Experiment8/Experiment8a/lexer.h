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
	STRING,
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

#ifdef LEXER_IMPL
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

const char* token_names[] = {
	[RPAREN] = "RPAREN",
	[LPAREN] = "LPAREN",
	[IDENT] = "IDENT",
	[NUMBER] = "NUMBER",
	[COMMA] = "COMMA",
	[PERIOD] = "PERIOD",
	[SEMI] = "SEMI",
	[HASH] = "HASH",
	[COLON] = "COLON",
	[LT] = "LT",
	[GT] = "GT",
	[EQ] = "EQ",
	[PLUS] = "PLUS",
	[MINUS] = "MINUS",
	[PERCENT] = "PERCENT",
	[SLASH] = "SLASH",
	[RSLASH] = "RSLASH",
	[STRING] = "STRING",
	[SQUOTE] = "SQUOTE",
	[BANG] = "BANG",
	[LBRACE] = "LBRACE",
	[RBRACE] = "RBRACE",
	[LBRACKET] = "LBRACKET",
	[RBRACKET] = "RBRACKET",
	[AMPERSAND] = "AMPERSAND",
	[PIPE] = "PIPE",
	[END] = "END",
};

void print_token(Token* token) {
	printf("Token Type: %s, Identifer: %s, Length: %zu\n", token_names[token -> type], token -> symbol, token -> len);
}

lexer_t* init_lexer(char* contents, const size_t len) {
	lexer_t* lexer = NULL;
	lexer = (lexer_t*) malloc(sizeof(lexer_t));

	assert(lexer != NULL);

	lexer -> contents = contents;
	lexer -> len = len;
	lexer -> cursor = 0;
	lexer -> curr = lexer -> contents[lexer -> cursor];
	return lexer;
}

char peek(lexer_t* lexer) {
	if (lexer -> cursor == lexer -> len - 1) {
		return EOF;
	} else {
		return lexer -> contents[lexer -> cursor];
	}
}

void consume(lexer_t* lexer) {
	lexer -> cursor += 1;
	lexer -> curr = lexer -> contents[lexer -> cursor];
}

void skip_whitespace(lexer_t* lexer) {
	while (is_whitespace(lexer -> curr)) {
		consume(lexer);
	}
}

int is_whitespace(char ch) {
	return (ch == ' ') || (ch == '\n') || (ch == EOF) || (ch == '\t');
}

Token* token(void) {
	Token* tok = malloc(sizeof(Token));
	assert(tok != NULL);
	tok -> len = 0;
	tok -> symbol = NULL;
	return tok;
}

Token* next_token(lexer_t* lexer) {
	skip_whitespace(lexer);
	if (isalpha(lexer -> curr) || lexer -> curr == '_') {
		Token* tok = token();
		tok -> type = IDENT;
		do {
			token_append(tok, lexer -> curr);
			consume(lexer);
		} while (isalnum(lexer -> curr) || lexer -> curr == '_');
		return tok;
	}
	if (isdigit(lexer -> curr)) {
		Token* tok = token();
		tok -> type = NUMBER;
		do {
			token_append(tok, lexer -> curr);
			consume(lexer);
		} while (isdigit(lexer -> curr));
		return tok;
	}

	if (lexer -> curr == '"') {
		Token* tok = token();
		tok -> type = STRING;
		consume(lexer);
		do {
			token_append(tok, lexer -> curr);
			consume(lexer);
		} while (lexer -> curr != '"');
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '(') {
		Token* tok = token();
		tok -> type = LPAREN;
		consume(lexer);
		return tok;
	}
	
	if (lexer -> curr == ')') {
		Token* tok = token();
		tok -> type = RPAREN;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == ',') {
		Token* tok = token();
		tok -> type = COMMA;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '.') {
		Token* tok = token();
		tok -> type = PERIOD;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == ':') {
		Token* tok = token();
		tok -> type = COLON;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == ';') {
		Token* tok = token();
		tok -> type = COLON;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '<') {
		Token* tok = token();
		tok -> type = LT;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '>') {
		Token* tok = token();
		tok -> type = GT;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '=') {
		Token* tok = token();
		tok -> type = EQ;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '!') {
		Token* tok = token();
		tok -> type = BANG;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '{') {
		Token* tok = token();
		tok -> type = LBRACE;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '}') {
		Token* tok = token();
		tok -> type = RBRACE;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '[') {
		Token* tok = token();
		tok -> type = LBRACKET;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == ']') {
		Token* tok = token();
		tok -> type = RBRACKET;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '+') {
		Token* tok = token();
		tok -> type = PLUS;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '-') {
		Token* tok = token();
		tok -> type = MINUS;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '%') {
		Token* tok = token();
		tok -> type = PERCENT;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '/') {
		Token* tok = token();
		tok -> type = SLASH;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '\\') {
		Token* tok = token();
		tok -> type = RSLASH;
		consume(lexer);
		return tok;
	}

	
	if (lexer -> curr == '\'') {
		Token* tok = token();
		tok -> type = SQUOTE;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '&') {
		Token* tok = token();
		tok -> type = AMPERSAND;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '|') {
		Token* tok = token();
		tok -> type = PIPE;
		consume(lexer);
		return tok;
	}

	if (lexer -> curr == '#') {
		Token* tok = token();
		tok -> type = HASH;
		consume(lexer);
		return tok;
	} else {
		Token* tok = token();
		consume(lexer);
		tok -> type = END;
		return tok;
	}
}

void token_append(Token* token, char ch) {
	token -> symbol = realloc(token -> symbol, sizeof(char) * (token -> len + 1));
	assert(token -> symbol != NULL);
	token -> len += 1;
	token -> symbol[token -> len - 1] = ch;
	token -> symbol[token -> len] = '\0';
}
#endif

#endif // __LEXER_H
