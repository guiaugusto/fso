#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd1;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char name[50];

    printf("Insira seu nome para iniciar uma conversa: \n");
    scanf("%s", name);
    getchar();

    char str1[80], str2[80];

    while (1)
    {
        char final_message[130] = "";
        // First open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, str1, 80);

        // Print the read string and close
        printf("%s", str1);
        close(fd1);

        // Now open in write mode and write
        // string taken from user.
        printf("Você: ");
        fd1 = open(myfifo,O_WRONLY);
        fgets(str2, 80, stdin);

        strcat(final_message, name);
        strcat(final_message, ": ");
        strcat(final_message, str2);

        write(fd1, final_message, strlen(final_message)+1);
        close(fd1);

    }
    return 0;
}
