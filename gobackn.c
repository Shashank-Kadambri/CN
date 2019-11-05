// Program 4: To simulate and implement the go back n sliding window protocol

#include<stdio.h>
#include<time.h>
#include<stdlib.h>


#define WINDOW_SIZE 4
#define MAX_TIME 5


struct frame{
    int frameNo;
    int data;
};

void initFrames(int data[],struct frame dataFrames[],int n){
    for(int i=0;i<n;i++){
        dataFrames[i].data = data[i];
        dataFrames[i].frameNo = i;
    }
}
void initWindow(struct frame window[],struct frame dataStream[]){
    for(int i=0;i<WINDOW_SIZE;i++){
        window[i] = dataStream[i];
    }
}
void slideWindow(struct frame window[],struct frame dataStream[],int * current){
    for(int i=0;i<WINDOW_SIZE;i++){
        window[i-1] = window[i];
    }
    window[WINDOW_SIZE-1]=dataStream[*current + WINDOW_SIZE];
    (*current)++;
}
void printArr(struct frame arr[],int n){
    for(int i = 0; i<n ;i++){
        printf("%d ",arr[i].data);
    }
}
int send(int window[]){
    return 0;
}
int main(){
    srand(time(NULL));
    int data_to_send[10] = {23,42,51,25,56,14,57,28,53,35};
    struct frame frames[10];
    int timers[WINDOW_SIZE]={MAX_TIME};
    struct frame window[WINDOW_SIZE];
    int expected_frame = 0;
    int expected_ack = 0;
    initFrames(data_to_send,frames,10);
    initWindow(window,frames);
    int current = 0;
    while(current<10){
        //send all frames in window
        for(int i = 0;i<WINDOW_SIZE && (current+i)<10;i++){
            printf("\nSent frame %d",window[i].frameNo);
        }
        int noFramesReceived = 0;

        //Check if sent frames are received
        for(int j = 0;j<WINDOW_SIZE && (current+j)<10;j++){
            int flag = rand()%4;
            if(flag){
                printf("\nReceived frame %d",window[j].frameNo);
                noFramesReceived++;
            }
            else{
                break;
            }
        }

        // Send acknowledgment for received data and slide window.
        for(int k=0;k<noFramesReceived;k++){
            printf("\nSent ack for frame %d",window[0].frameNo);
            slideWindow(window,frames,&current);
        }
        printf("\n");
    }

}
