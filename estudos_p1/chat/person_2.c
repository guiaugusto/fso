#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);

    char name[50];

    printf("Insira seu nome para iniciar uma conversa: \n");
    scanf("%s", name);
    getchar();

    char arr1[80], arr2[80];
    while (1)
    {
        char final_message[130] = "";
        // Open FIFO for write only
        printf("Você: ");
        fd = open(myfifo, O_WRONLY);

        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(arr2, 80, stdin);

        strcat(final_message, name);
        strcat(final_message, ": ");
        strcat(final_message, arr2);

        // Write the input arr2ing on FIFO
        // and close it
        write(fd, final_message, strlen(final_message)+1);
        close(fd);

        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);

        // Read from FIFO
        read(fd, arr1, sizeof(arr1));

        // Print the read message
        printf("%s", arr1);
        close(fd);

    }
    return 0;
}
