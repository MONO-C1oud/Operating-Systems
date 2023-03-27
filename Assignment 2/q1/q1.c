#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_FILES 47

void* printing(char* filename) {
	char* f1 = (char*) (filename);
	printf("%s\n", f1);

	
	FILE *fp;
    char c;

    fp = fopen(filename, "r");

    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }

    fclose(fp);
    

    return NULL;
}

int main() {
	
	char* filenames[NUM_FILES];

    for (int i = 1; i <= NUM_FILES; i++) {
        char buffer[20];
        sprintf(buffer, "sam%d.txt", i);
        filenames[i-1] = strdup(buffer);
    }

    // Print the filenames for testing purposes
    for (int i = 0; i < NUM_FILES; i++) {
        printf("%s\n", filenames[i]);
    }
    printf("\n\n");
	

	//char* test = "sam1.txt";
	//printing(filenames[0]);

	
	
	//pthread_create(&t1, NULL, printing, filenames[0]);
	//pthread_join(t1, NULL);
	

	pthread_t t[NUM_FILES];

	for (int i = 0; i < NUM_FILES; i++) {
		pthread_create(&t[i], NULL, printing, filenames[i]);
	}


	for (int i = 0; i < NUM_FILES; i++) {
		pthread_join(t[i], NULL);
	}
	
	// Free memory used by the filenames array
    for (int i = 0; i < NUM_FILES; i++) {
        free(filenames[i]);
    }
   
	
	return 0;
}
