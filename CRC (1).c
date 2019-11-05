#include<stdio.h>
#include<stdlib.h>
int XOR(int x,int y){
  int out = (x & !y) | (!x & y);
  return out;
}
void printArr(int * arr,int n){
     for(int i= 0;i<n;i++){
          printf("%d ",arr[i]);
     }
}

/*
1. Create an index which points to the first one appearing in the dividend
     in each iteration.
2. XOR the degree-1 bits of the dividend with the divisor
3. Repeat until the last bit of the dividend is also used up.
*/

void crcDivide(int dividend[],int divisor[],int remainder[],int len1,int len2){
     //len1:dividend length len2:divisor length
     int i = 0;
     int * temp = (int*)malloc((len1+len2-1)*sizeof(int));
     for(int k = 0;k<len1+len2-1;k++){
          if(k<len1)
               temp[k] = dividend[k];
          else{
               temp[k] = 0;
          }
     }
     while(temp[i]!=1){
          i++;
     }
     while(i<len1){
          for(int j = 0;j<len2;j++){

               temp[i+j] = XOR(temp[i+j],divisor[j]);
          }
          while(temp[i]!=1){
               i++;
          }
     }
     for(int j = 0;j<len2-1;j++){
          remainder[j] = temp[i+j];
     }
}

void crcEncode(int * msg, int * rem,int * encodedMsg,int len1,int len2){
     //len1->length of msg ,len 2->length of remainder
     for(int i = 0;i<len1+len2;i++){
          if(i<len1){
               encodedMsg[i] = msg[i];
          }
          else{
               encodedMsg[i] = rem[i-len1];
          }
     }

}

/*int crcCheck(int * received_msg,int * divisor,int receivedLen,int divisorLen){
     int i = 0;
     int * temp = (int*)malloc((receivedLen)*sizeof(int));
     for(int k = 0;k<receivedLen;k++){
          temp[k] = received_msg[k];
     }
     while(temp[i]!=1){
          i++;
     }

     while(i<=receivedLen-divisorLen){
          for(int j = 0;j<divisorLen;j++){

               temp[i+j] = XOR(temp[i+j],divisor[j]);
          }
          while(temp[i]!=1 && i<=receivedLen-divisorLen){
               i++;
          }
     }
     for(int j = 0;j<divisorLen;j++){
          if(temp[i+j]==1)
               return 0;
     }
     return 1;

}*/



int main(){
     int len1,len2,i;
     int *s_msgBits,*polBits,*s_remBits,*encodedBits;
     printf("\nEnter the number of bits in the message:");
     scanf("%d",&len1);
     printf("\nEnter the number of bits in the generator polynomial:");
     scanf("%d",&len2);
     s_msgBits = (int*)malloc(len1*sizeof(int));
     polBits = (int*)malloc(len2*sizeof(int));
     s_remBits = (int*)malloc((len2-1)*sizeof(int));
     encodedBits = (int*)malloc((len1+len2-1)*sizeof(int));
     for(i = 0;i<len2-1;i++){
          s_remBits[i] = 0;
     }
     printf("\nEnter the message bits:");
     for(i = 0;i<len1;i++){
          scanf("%d",s_msgBits+i);
     }
     printf("\nEnter the polynomial bits:");
     for(i = 0;i<len2;i++){
          scanf("%d",polBits+i);
     }
     printf("\nMessage:");
     printArr(s_msgBits,len1);
     printf("\nPolynomial:");
     printArr(polBits,len2);

     crcDivide(s_msgBits,polBits,s_remBits,len1,len2);
     printf("\nRemainder:");
     printArr(s_remBits,len2-1);
     crcEncode(s_msgBits,s_remBits,encodedBits,len1,len2-1);
     printf("\nEncoded message:");
     printArr(encodedBits,len1+len2-1);


     return 0;
}
