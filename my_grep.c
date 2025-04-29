#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *input;

	if(argv[1][0] == '-')
		input = stdin;
	else
		input = fopen(argv[1], "r");
	
	
}
