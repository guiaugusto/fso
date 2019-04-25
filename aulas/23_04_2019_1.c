#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>

#define GET_QUEUE "/get_queue"
#define RET_QUEUE "/ret_queue"

mqd_t get_queue;
mqd_t ret_queue;

void request_ticket(){
    if((get_queue = mq_open(GET_QUEUE, O_RDWR|O_CREAT, 0666, &attr)) < 0){
        perror("get mq_open");
        exit(1);
    }
}

int receive_ticket(){

    int ticket;

    if(mq_receive(ret_queue, (void*) &ticket, sizeof(ticket), 0) < 0){
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

    struct mq_attr attr;
    int ticket, msg;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(msg);
    attr.mq_flags = 0;




    for(;;){

        if (mq_send (get_queue, (void *) &msg, sizeof(msg), 0) < 0){
            perror("mq_send");
            exit(1);
        }

        printf("Esperando envio de ticket\n");

        ticket = receive_ticket();
    }
}
