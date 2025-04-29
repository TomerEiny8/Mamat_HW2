#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
	FILE *src, *dest;

	// Open source file or use stdin if '-' is provided
	if( argv[1][0] == '-' && argv[1][1] == '\0') {
		src = stdin;
	} else {
		src = fopen(argv[1] , "rb"); // open source file in binary read mode
		if(src == NULL)
		{
			fprintf(stderr, "Error occurred\n"); // Print error messege to stderr
			return 1;
		}
	}

	// Open destination file or use stdout if '-' is provided
	if( argv[2][0] == '-' && argv[2][1] == '\0') {
                dest = stdout;
        } else {
                dest = fopen(argv[2] , "wb"); // Open destination file in binary write mode
                if(dest == NULL)
                {
                        fprintf(stderr, "Error occurred\n"); // Print error messege to stderr
                        if(src != stdin)
				fclose(src);
			return 1;
                }
        }

	char buffer[BUFFER_SIZE];  // Buffer to hold data chunks
	size_t bytes;

	// Read from source and write to destination using the buffer
	while((bytes = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
		if(fwrite(buffer, 1, bytes, dest) != bytes) {
			fprintf(stderr, "Error occurred\n"); // Print error messege to stderr
			if(src != stdin) 
				fclose(src);
			if(dest != stdout)
				fclose(dest);
			return 1;
		}
	}

	// Check if reading from source encountered an error
	if(ferror(src)) {
		fprintf(stderr, "Error occurred\n"); // Print error messege to stderr
		if(src != stdin)
			fclose(src);
                if(dest != stdout)
                        fclose(dest);
                return 1;
	}

	// Close source and destination files if they are not stdin or stdout
	if(src != stdin)                                
                fclose(src);
        if(dest != stdout)
		fclose(dest);
        return 0; // Successful execution

}
