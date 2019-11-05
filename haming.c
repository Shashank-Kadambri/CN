/*
# Program to implement haming code
# If we have a data with m bits then we add r redundant bits such that
                         2^r>=r+m+1
# We induce r parity bits at 2^i th positions where 0<i<r

*/
#include<stdio.h>

void rev(int * arr,int len){
     for(int i=0;i<len/2;i++){
          int temp = arr[i];
          arr[i] = arr[len-i-1];
          arr[len-i-1] = temp;
     }
     return;
}
void decToBin(int data,int * data_bits,int * data_len ){
     (*data_len) = 0;
     while(data != 0){
          data_bits[(*data_len)++] = data%2;
          data/=2;
     }

     rev(data_bits,*data_len);
}


void printArr(int * arr,int len){
     for(int i = 0;i<len;i++){
          printf("%d ",arr[i]);
     }

}

void setithparity(int i,int * code_bits,int total_bits){
     int sum=0;
     int exit_loops=0;
     for(int j=i;exit_loops==0;j+=2*i){
          for(int k=0;k<i;k++){
               if(j+k == i){
                    continue;
               }
               else if(j+k>total_bits){
                    exit_loops=1;
                    break;
               }
               else{
                    sum+=code_bits[j+k-1];
               }
          }
     }
     //Even parity
     if(sum%2 == 0){

          code_bits[i-1] = 0;
     }
     else
          code_bits[i-1] = 1;

}
int isPowerOf2(int n){
     int rem;
     while(n!=1){
          rem = n%2;
          if(rem == 1)
               return 0;
          n/=2;
     }
     return 1;

}
int calcPower(int a,int b){
     int prod = 1;
     for(int i = 0; i<b;i++){
          prod*=a;
     }
     return prod;
}
void setEncodeBits(int * code,int * data_bits,int m,int r){
     int j = 0;
     for(int i=0;i<m+r;i++){
          if(isPowerOf2(i+1)==1){
               code[i] = -1;
          }
          else{
               code[i] = data_bits[m-(j++)-1];
          }
     }
     for(int k = 0;k<r;k++){
          setithparity(calcPower(2,k),code,m+r);
     }
}

int set_r(int m){
     int r=0;
     while(calcPower(2,r)<r+m+1){
          r++;
     }
     return r;
}
int main(){
     int data_bits[25];
     int parity_bits[10];
     int code_bits[50];
     int m; //data bits length
     int r; //number of redundant bits

     // Input data to be sent(in decimal)
     int data;
     printf("\nEnter the data to be sent(integer):");
     scanf("%d",&data);

     // Convert the data into binary
     decToBin(data,data_bits,&m);
     printf("\nData Bits:");
     printArr(data_bits,m);

     // Set the number of redundant bits
     r = set_r(m);

     // Set the encoded message
     setEncodeBits(code_bits,data_bits,m,r);
     rev(code_bits,m+r);
     printf("\nData to be sent:");
     printArr(code_bits,m+r);

     

}
