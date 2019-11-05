//Sender
#include<stdio.h>
#define MAX_FRAMES 10
#define TIMER_MAX 5
int wait_for_ack=0,timer,currentFrame=0,data_in_channel,ackFrameNo=0,ack_sent=0,data_sent=0,ack_received=0;
int send(int data){

    // Check for acknowledgment if data is sent
    if(data_sent){
        if(ack_sent && !ack_received){
            data_sent = 0;
            ack_received=1;
            currentFrame++;
            return 2;
        }
        else
            return -1;
    }

    // Send data if not sent
    data_in_channel = data;
    timer = TIMER_MAX;
    ack_received = 0;
    ack_sent = 0;
    data_sent = 1;
    return 1;

}
int receive(int * received_data){
    // Receive data and send ackowledgment
    if(data_sent && !ack_sent){
        *received_data = data_in_channel;
        ack_sent = 1;
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    int data_to_send[MAX_FRAMES] = {23,42,51,25,56,14,57,28,53,35};
    int n;
    printf("\nEnter the number of frames to send:");
    scanf("%d",&n);
    printf("\nEnter the data to send:");
    for(int i=0;i<n;i++){
        int data ;
        scanf("%d",&data);
        data_to_send[i] = data;
    }
    while(currentFrame<n){
        printf("\n1)Sender\n2)Receiver\n3)Exit\n");
        int choice;
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                int status = send(data_to_send[currentFrame]);
                if(status==1){
                    printf("\nData Sent. Timer started.");
                }
                else if(status ==-1){
                    timer--;
                    printf("\nWaiting for ack.Timer=%d",timer);
                }
                else{
                    printf("\nAcknowledgment received.");
                    data_sent=0;
                    ack_received=1;
                }
                if(timer == 0){
                    printf("Acknowledgement not received. Resending...");
                    data_sent = 0;
                    send(data_to_send[currentFrame]);
                }
                break;
            }
            case 2:
            {
                int receivedData;
                if(receive(&receivedData)){
                    printf("\nReceived Data:%d",receivedData);
                }
                else{
                    printf("\nWaiting for data");
                }
                break;
            }
        }
    }

}
