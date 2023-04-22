#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    struct flock fl;

    fork(); // creates 2 processes
    // Open the file for writing
    fd = open("myfile.txt", O_WRONLY | O_CREAT, 0666);
    if (fd == -1) {
        perror("error opening file...");
        exit(1);
    }

    // Set the file lock structure
    fl.l_type = F_WRLCK;  // Write lock
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;  // Lock the entire file
    printf("The file has been locked!\n");

    // Locking the file
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    // Write to the file
    write(fd, "Hello world!", 12);


    // Releasing the file lock
    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }
    printf("The file has been unlocked!\n");

    // Close the file
    close(fd);

    return 0;
}