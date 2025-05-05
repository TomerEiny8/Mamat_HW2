
#include <stdio.h>
#include <stdlib.h>

int match(char *line, char *reg_expr);
int match_here(char *text, char *reg_expr);
int match_star(char *text,char c, char *reg_expr);
void find_replace_str(char *str, char f, char r);


int main(int argc, char* argv[]) {
	FILE *input;
	char *reg_expr = argv[2], line[BUFSIZ];

	if (argv[1][0] == '-' && argv[1][1] == '\0') {
		input = stdin;
	} else {
		input = fopen(argv[1], "r");
		if (input == NULL) {
			fprintf(stderr, "Error occurred");
			return 1;
		}
	}

	while (fgets(line, BUFSIZ, input) != NULL) {
		find_replace_str(line, '\n', '\0');
		if(match(line, reg_expr)) {
			fprintf(stdout, "%s\n", line);
		}
	}

	if(input != stdin)
		fclose(input);

	return 0;
}


int match(char *line, char *reg_expr) {

	if (reg_expr[0] == '^') {
		return match_here(line, reg_expr + 1);
	}

	if (match_here(line, reg_expr)) {
		return 1;
	}

	while (*line != '\0') {
		line++;
		if (match_here(line, reg_expr)) {
			return 1;
		}

	}
	return 0;
}

/**
 * @brief checks if the reg_expr matches at the current location
 * @param text: the text we're testing for the regular expression
 * @param reg_expr: the regural expression we're searchin for
 * @returns 1 if a match was found, 0 otherwise
 */
int match_here(char *text, char *reg_expr) {
	if (reg_expr[0] == '\0') {
		return 1;
	}
	if (reg_expr[1] == '*') {
		return match_star(text, reg_expr[0], reg_expr+2);
	}
	if (reg_expr[0] == '$' && reg_expr[1] == '\0') {
		if (text[0] == '\0') {
			return 1;
		}
		return 0;
	}
	if (text[0] == reg_expr[0] || (reg_expr[0] == '.' && text[0] != '\0')) {
		return match_here(text + 1, reg_expr + 1);
	}
	return 0;
}


int match_star(char *text,char c, char *reg_expr) {
	while (*text != '\0' && (*text == c || c == '.')) {
		if (match_here(text, reg_expr))
			return 1;
		text++;
	}
	return match_here(text, reg_expr);
}

void find_replace_str(char *str, char f, char r) {
	while (*str != '\0') {
		if(*str == f) {
			*str = r;
		}
		str++;
	}
}

