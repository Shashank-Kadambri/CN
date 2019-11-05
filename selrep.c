// Program 5: To simulate and implement selective repeat sliding window protocoll

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
void slideWindow(struct frame window[],struct frame dataStream[],int * current,int noOfElements){
    for(int i=0;i<WINDOW_SIZE;i++){
        window[i] = dataStream[*(current)+i+noOfElements];
    }
    (*current)+=noOfElements;
}

int main(){
    srand(time(NULL));
    struct frame frame1;
    int data_to_send[10] = {23,42,51,25,56,14,57,28,53,35};
    struct frame frames[10];
    //int timers[WINDOW_SIZE]={MAX_TIME};
    struct frame window[WINDOW_SIZE];
    initFrames(data_to_send,frames,10);
    initWindow(window,frames);
    int current = 0;
    while(current<10){
        int noFramesReceived = 0;
        int nackFrames[WINDOW_SIZE];
        for(int j=0;j<WINDOW_SIZE;j++){
            nackFrames[j] = 1;
        }

        // Loop until all the frames in the current window are not received
        while(noFramesReceived < WINDOW_SIZE && noFramesReceived+current<10){
            for(int i=0;i<WINDOW_SIZE && i+current<10;i++){
                if(nackFrames[i]){
                    printf("\nSent frame %d",window[i].frameNo);
                }
            }

            //Check whether frame is received intact. If not then send negative acknowledgment
            for(int j = 0;j<WINDOW_SIZE && (current+j)<10;j++){
                if(nackFrames[j]==1){
                    int flag = rand()%3;
                    if(flag){
                        printf("\nReceived frame %d",window[j].frameNo);
                        printf("\nAcknowledgment sent for frame %d",window[j].frameNo);
                        noFramesReceived++;
                        nackFrames[j] = 0;
                    }
                    else{
                        printf("\nSending negative ack for frame %d",window[j].frameNo);
                        nackFrames[j] = 1;
                    }
                }
            }
        }
        slideWindow(window,frames,&current,WINDOW_SIZE);

        printf("\n");
    }

}
