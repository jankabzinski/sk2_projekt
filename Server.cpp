#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
    //pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    int gameNo;
    //int playerNo;
    //char color;
    char buf[200];
    long long fd;
    int fd2;
};
vector <Game> gra;

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

//wska�nik na funkcj� opisuj�c� zachowanie w�tku
void* ThreadBehavior(void* t_data)
{
    struct thread_data_t* th_data = (struct thread_data_t*)t_data;
    
    Game g;
    g.board.set();
    g.setGame();
    gra.push_back(g);
    string y;
    int m;
    memset(th_data->buf, 0, sizeof(th_data->buf));
    string x = gra[th_data->gameNo].board.boardToString();
    strcpy(th_data->buf, x.c_str());
    write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
    write((*th_data).fd2, (*th_data).buf, sizeof((*th_data).buf));

    while (1)
    {           
        m = 0;
        do
        {
            x= "";
            do
            {
            memset(th_data->buf, 0, sizeof(th_data->buf));
            if ((m = read(th_data->fd, th_data->buf, sizeof(th_data->buf)) )> 0)
            {
                x += convertToString(th_data->buf, m-1);
            }
            else
            {
                memset(th_data->buf, 0, sizeof(th_data->buf));
                y = "Zawodnik grajacy bialymi rozlaczyl sie, wygrales. Gratulacje, ale nie do konca"; 
                strcpy(th_data->buf, y.c_str());
                write((*th_data).fd2, (*th_data).buf, sizeof((*th_data).buf));
                goto out;
            }

            }while(x.size()!=0 && x[x.size()-1]== '\n');

            y = gra[th_data->gameNo].play(x);
            if(y == "Nieprawidlowy ruch. Sprobuj ponownie\n")
            {
                memset(th_data->buf, 0, sizeof(th_data->buf));
                strcpy(th_data->buf, y.c_str());
                write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
            }

        }while(y == "Nieprawidlowy ruch. Sprobuj ponownie\n" );

        memset(th_data->buf, 0, sizeof(th_data->buf));
        x = gra[th_data->gameNo].board.boardToString();
        strcpy(th_data->buf, x.c_str());
        write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
        write((*th_data).fd2, (*th_data).buf, sizeof((*th_data).buf));
        
        if(y != "")
        {
            memset(th_data->buf, 0, sizeof(th_data->buf));
            strcpy(th_data->buf, y.c_str());
            write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
            write((*th_data).fd2, (*th_data).buf, sizeof((*th_data).buf));
            break;
        }

        m = 0;
        do
        {
            x= "";
            do
            {
            memset(th_data->buf, 0, sizeof(th_data->buf));
            if ((m = read(th_data->fd2, th_data->buf, sizeof(th_data->buf)) )> 0)
            {
                x += convertToString(th_data->buf, m-1);
            }
            else
            {
                memset(th_data->buf, 0, sizeof(th_data->buf));
                y = "Zawodnik grajacy czarnymi rozlaczyl sie, wygrales. Gratulacje, ale nie do konca"; 
                strcpy(th_data->buf, y.c_str());
                write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
                goto out;
            }

            }while(x.size()!=0 && x[x.size()-1]== '\n');

            y = gra[th_data->gameNo].play(x);
            if(y == "Nieprawidlowy ruch. Sprobuj ponownie\n")
            {
                memset(th_data->buf, 0, sizeof(th_data->buf));
                strcpy(th_data->buf, y.c_str());
                write((*th_data).fd2, (*th_data).buf, sizeof((*th_data).buf));
            }

        }while(y == "Nieprawidlowy ruch. Sprobuj ponownie\n" );

        memset(th_data->buf, 0, sizeof(th_data->buf));
        x = gra[th_data->gameNo].board.boardToString();
        strcpy(th_data->buf, x.c_str());
        write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
        write((*th_data).fd2, (*th_data).buf, sizeof((*th_data).buf));
        
        if(y != "")
        {
            memset(th_data->buf, 0, sizeof(th_data->buf));
            strcpy(th_data->buf, y.c_str());
            write((*th_data).fd, (*th_data).buf, sizeof((*th_data).buf));
            write((*th_data).fd2, (*th_data).buf, sizeof((*th_data).buf));
            break;
        }
    }
    if(false)
    {
        out:
        ;
    }

    pthread_exit(NULL);
}


//funkcja obs�uguj�ca po��czenie z serwerem
void handleConnection(int connection_socket_descriptor, int connection_socket_descriptor2, int gamNo) {
    int create_result = 0;
    //uchwyt na w�tek
    pthread_t thread1;

    //dane, kt�re zostan� przekazane do w�tku
    struct thread_data_t t_data;
    t_data.fd = connection_socket_descriptor;
    t_data.fd2 = connection_socket_descriptor2;
    //t_data.playerNo = playerNo;
    //t_data.color = playerNo % 2 == 0 ? 'w' : 'b';
    t_data.gameNo = gamNo;
    create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void*)&t_data);
    if (create_result) {
        printf("B��d przy pr�bie utworzenia w�tku, kod b��du: %d\n", create_result);
        exit(-1);
    }
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
    server_address.sin_port = htons(1234); //htons(atoi(argv[2]));

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
    
    int counter = 0;
    int csd1=0;
    while (1)
    {
        connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if (connection_socket_descriptor < 0)
        {
            fprintf(stderr, "%s: B��d przy pr�bie utworzenia gniazda dla po��czenia.\n", argv[0]);
            exit(1);
        }
        if(counter % 2 == 1)
        {
            handleConnection(csd1, connection_socket_descriptor, counter/2);
        }
        else
        {
            csd1 = connection_socket_descriptor;
        }
        //cout << csd1 << " " <<connection_socket_descriptor << " d" <<endl;
        counter++;
    }
    close(server_socket_descriptor);
    return(0);
}
