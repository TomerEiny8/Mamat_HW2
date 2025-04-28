#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
	FILE *src, *dest;
	
	if( argv[1][0] == '-' && argv[1][1] == '\0') {
		src = stdin;
	} else {
		src = fopen(argv[1] , "rb");
		if(src == NULL)
		{
			fprintf(sterr, "Error occured\n");
			return 1;
		}
	}

	if( argv[2][0] == '-' && argv[2][1] == '\0') {
                dest = stdout;
        } else {
                dest = fopen(argv[2] , "wb");
                if(dest == NULL)
                {
                        fprintf(sterr, "Error occured\n");
                        if(src != stdin)
				fclose(src);
			return 1;
                }
        }

	char buffer[BUFFER_SIZE];
	size_t bytes;

	while((bytes = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
		if(fwrite(buffer, 1, bytes, dest) != bytes) {
			fprintf(sterr, "Error occured\n");
			if(src != stdin) 
				fclose(src);
			if(dest != stdout)
				fclose(dest);
			return 1;
		}
	}

	if(ferror(src)) {
		fprintf(sterr, "Error occured\n");
		if(src != stdin)
			fclose(src);
                if(dest != stdout)
                        fclose(dest);
                return 1;
	}

	if(src != stdin)                                
                fclose(src);
        if(dest != stdout)
		fclose(dest);
        return 0;

}
