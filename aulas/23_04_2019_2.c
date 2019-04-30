#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>

#define GET_QUEUE "/get_queue"
#define RET_QUEUE "/ret_queue"
#define MAX_TICKETS 100

mqd_t get_queue;
mqd_t ret_queue;
int ticket = 0, msg;
int tickets[MAX_TICKETS];
struct mq_attr attr;

void open_queues(){
    if((get_queue = mq_open(GET_QUEUE, O_RDWR)) < 0){
        perror("get mq_open");
        exit(1);
    }

    if((ret_queue = mq_open(RET_QUEUE, O_RDWR|O_CREAT, 0666, &attr)) < 0){
        perror("ret mq_open");
        exit(1);
    }
}

int get_ticket(){
    int i;
    int t;
    for(i = 0; i < MAX_TICKETS; i++){
        if(tickets[i] == -1){
            t = i;
            break;
        }
    }

    if(i == MAX_TICKETS-1){
        t = -1;
    }

    return t;
}

void get_request(){
    int receive = mq_receive(get_queue, (void*) &msg, sizeof(msg), 0);
    if(receive < 0){
        perror("mq_receive:");
        exit(1);
    }
}

void send_ticket(){
    if (mq_send (ret_queue, (void *) &ticket, sizeof(ticket), 0) < 0){
        perror("mq_send");
        exit(1);
    }
}

int main(int argc, char *argv[]){

    memset(tickets, -1, sizeof(tickets));

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(ticket);
    attr.mq_flags = 0;

    open_queues();

    for(;;){
        get_request();
        printf("Um pedido foi solicitado!\n");

        ticket = get_ticket();
        printf("Ticket %d selecionado!\n", ticket);

        send_ticket(ticket);
        printf("Ticket %d foi enviado!\n", ticket);

        sleep(1);
    }
}
