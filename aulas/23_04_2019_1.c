#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>

#define GET_QUEUE "/get_queue"
#define RET_QUEUE "/ret_queue"

mqd_t get_queue;
mqd_t ret_queue;

struct mq_attr attr;
int ticket, msg = 1;
int request_valid = 0;

void open_queues(){
    if((get_queue = mq_open(GET_QUEUE, O_RDWR|O_CREAT, 0666, &attr)) < 0){
        perror("get mq_open");
        exit(1);
    }

    if((ret_queue = mq_open(RET_QUEUE, O_RDWR|O_CREAT)) < 0){
        perror("ret mq_open");
        exit(1);
    }
}

int request_ticket(){
    int send = mq_send (get_queue, (void *) &msg, sizeof(msg), 0);
    if (send < 0){
        perror("mq_send");
        exit(1);
    }else{
        return 1;
    }
}

int receive_ticket(int ticket){

    int receive = mq_receive(ret_queue, (void*) &ticket, sizeof(ticket), 0);
    if(receive < 0){
        perror("mq_receive:");
        exit(1);
    }

    return ticket;
}

void give_back_ticket(int ticket){
    if((ret_queue = mq_open(RET_QUEUE, O_RDWR)) < 0){
        perror("ret mq_open");
        exit(1);
    }
}

int main(){

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(ticket)*2;
    attr.mq_flags = 0;

    open_queues();

    for(;;){

        msg = 1;

        printf("Solicitando ticket!\n");

        request_ticket();
        printf("Ticket solicitado!\n");

        receive_ticket(ticket);
        printf("Ticket recebido: %d\n", ticket);
    }
}
