#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *input;
	
	// checking which type of input we have: file or string
	if(argv[1] == '-'){
		input = stdin;
	} else {
		input = fopen(argv[1], "r");
	}
	
	// initializing the histogram of the grades
	int numbers_histo[101];
	int num_of_numbers = 0;
	for(int i=0;i<101;i++){
		numbers_histo[i] = 0;
	}
	
	int line_number = 0;
	char buffer[5];
	
	while(fgets(buffer, sizeof(buffer), input)){
		line_number++;
		char *endptr;
		long val = strtol(buffer, &endptr, 10);
		
		if((*endptr !='\0' && *endptr != '\n') || (val < 0) || (val > 100)){
			fprintf(stderr, "Error at line %d: invalid input %s\n", line_number, buffer);
			if(input != stdin)
				fclose(input);
			return 1;
		}
		num_of_numbers++;
		numbers_histo[val]++;
	}
	int result_index = 0;
	for(int i=0; i<num_of_numbers/2;i++){
		while(numbers_histo[result_index] == 0){
			result_index++;
		}
		numbers_histo[result_index]--;
	}
	fprintf("%d", result_index);
	return 0;
}
