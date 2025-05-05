#include <stdio.h>
#include <stdlib.h>

int match(char* text, char* regexp) {
	if(regexp[0] == '^')
		return matchhere(text, regexp+1);
	if(matchhere(text, regexp) 
		return 1;
	return 0;
}

int matchhere(char* text, char* regexp) {
	if(regexp[0] == '\0')
		return 1;
	if(regexp[1] == '*')
		return matchstar(text, regexp[0], regexp+2);
	if(regexp[0] == '$' && regexp[1] == '\0') {
		if(text[0] == '\0')
			return 1;
		return 0;
	}
	if(regexp[0] == '.' || regexp[0] == text[0])
		return matchhere(text+1, regexp+1);
	return 0;
}

int matchstar(char* text, char c, char* regexp) {
	while(*text != '\0' && (*text == c || c == '.')) {
		if(matchhere(text, regexp))
			return 1;
		text++;
	}	
	return 0;
}

int main(int argc, char *argv[]) {
	FILE *input;

	if(argv[1][0] == '-')
		input = stdin;
	else
		input = fopen(argv[1], "r");
	
		
}
