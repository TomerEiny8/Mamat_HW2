#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *input;
	
	// checking which type of input we have: file or string
	if(argv[1][0] == '-'){
		input = stdin;
	} else {
		input = fopen(argv[1], "r");
	}
	
	// initializing the histogram of the grades
	int numbers_histo[101];
	int num_of_numbers = 0;
	for(int i=0; i<101; i++){
		numbers_histo[i] = 0;
	}
	
	int line_number = 0; // line counter for error messege
	char buffer[5];

	//filing up the histogram, going over the file an adding grades from each line
	while(fgets(buffer, sizeof(buffer), input)){
		line_number++;
		char *endptr;
		long val = strtol(buffer, &endptr, 10); //taking the string and making it long, in decimal base

		// if the grade is not in the range or the input is incorrect, printing error messege to stderr
		if((*endptr !='\0' && *endptr != '\n') || (val < 0) || (val > 100)){ 
			fprintf(stderr, "Error at line %d: invalid input %s\n", line_number, buffer);
			if(input != stdin)
				fclose(input);
			return 1;
		}
		num_of_numbers++;
		numbers_histo[val]++;
	}
	if(input != stdin)
		fclose(input);

	int result_index = 0;
	// going over the histogram and checking the median grade
	for(int i=0; i<(num_of_numbers-1)/2;i++){
		while(numbers_histo[result_index] == 0){
			result_index++;
		}
		numbers_histo[result_index]--;
	}
	while(numbers_histo[result_index] == 0)
		result_index++;

	// printing te result
	fprintf(stdout, "%d\n", result_index);
	return 0;
}
