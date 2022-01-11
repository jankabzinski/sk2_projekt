#include <iostream>
#include <vector>
#include <string>
#include "Game.cpp"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define QUEUE_SIZE 1024
struct thread_data_t
{
    char buf[100];
    int fd;
    //TODO
};

//wska�nik na funkcj� opisuj�c� zachowanie w�tku
void* ThreadBehavior(void* t_data)
{
    struct thread_data_t* th_data = (struct thread_data_t*)t_data;
    //dost�p do p�l struktury: (*th_data).pole
    //TODO (przy zadaniu 1) klawiatura -> wysy�anie albo odbieranie -> wy�wietlanie

    while (1)
    {
        memset(th_data->buf, 0, sizeof(th_data->buf));
        fgets((*th_data).buf, sizeof((*th_data).buf), stdin);
        write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
    }
    pthread_exit(NULL);
}


//funkcja obs�uguj�ca po��czenie z serwerem
void handleConnection(int connection_socket_descriptor) {
    //wynik funkcji tworz�cej w�tek
    int create_result = 0;
    char buf2[100];
    //uchwyt na w�tek
    pthread_t thread1;

    //dane, kt�re zostan� przekazane do w�tku
    struct thread_data_t t_data;
    t_data.fd = connection_socket_descriptor;

    create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void*)&t_data);
    if (create_result) {
        printf("B��d przy pr�bie utworzenia w�tku, kod b��du: %d\n", create_result);
        exit(-1);
    }

    /*while (read(t_data.fd, buf2, sizeof(buf2)) > 0)
    {
        printf("%s", buf2);
        memset(buf2, 0, sizeof(buf2));
    }*/
}
int main(int argc, char* argv[])
{
    int server_socket_descriptor;
    int connection_socket_descriptor;
    int bind_result;
    int listen_result;
    char reuse_addr_val = 1;
    struct sockaddr_in server_address;

    //inicjalizacja gniazda serwera

    memset(&server_address, 0, sizeof(struct sockaddr));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_descriptor < 0)
    {
        fprintf(stderr, "%s: B��d przy pr�bie utworzenia gniazda..\n", argv[0]);
        exit(1);
    }
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));

    bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    if (bind_result < 0)
    {
        fprintf(stderr, "%s: B��d przy pr�bie dowi�zania adresu IP i numeru portu do gniazda.\n", argv[0]);
        exit(1);
    }

    listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
    if (listen_result < 0) {
        fprintf(stderr, "%s: B��d przy pr�bie ustawienia wielko�ci kolejki.\n", argv[0]);
        exit(1);
    }

    while (1)
    {
        connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if (connection_socket_descriptor < 0)
        {
            fprintf(stderr, "%s: B��d przy pr�bie utworzenia gniazda dla po��czenia.\n", argv[0]);
            exit(1);
        }

        handleConnection(connection_socket_descriptor);
    }
    close(server_socket_descriptor);
    return(0);
}