#include <sys/types.h> // Required for mkfifo
#include <sys/stat.h>  // Required for mkfifo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

void count_and_write(const char *sentence) {
    int characters = 0, words = 0, lines = 0, inWord = 0;
    for (const char *p = sentence; *p; p++) {
        characters++;
        if (*p == ' ' || *p == '\n') {
            if (inWord) { words++; inWord = 0; }
            if (*p == '\n') lines++;
        } else {
            inWord = 1;
        }
    }
    if (inWord) words++;

    FILE *fp = fopen("output.txt", "w");
    if (fp) {
        fprintf(fp, "Characters: %d\nWords: %d\nLines: %d\n", characters, words, lines);
        fclose(fp);
    } else {
        perror("Failed to open file");
    }
}

void child_process() {
    char sentence[200];
    int fd1 = open(FIFO1, O_RDONLY);
    int fd2 = open(FIFO2, O_WRONLY);

    read(fd1, sentence, sizeof(sentence));
    count_and_write(sentence);

    FILE *fp = fopen("output.txt", "r");
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        write(fd2, &ch, sizeof(ch));
    }
    fclose(fp);
    close(fd1);
    close(fd2);
    exit(0);
}

void parent_process() {
    char sentence[200] = {0}, buffer[200];
    int fd1 = open(FIFO1, O_WRONLY);
    int fd2 = open(FIFO2, O_RDONLY);

    printf("Enter multiple lines of text (end input with a blank line):\n");
    while (fgets(buffer, sizeof(buffer), stdin), strcmp(buffer, "\n") != 0) {
        strcat(sentence, buffer);
    }

    write(fd1, sentence, strlen(sentence) + 1);
    close(fd1);
    wait(NULL);

    printf("\nResults received from child process:\n");
    char ch;
    while (read(fd2, &ch, sizeof(ch)) > 0) {
        putchar(ch);
    }
    close(fd2);
}

int main() {
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    if (fork() == 0) {
        child_process();
    } else {
        parent_process();
    }

    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}
