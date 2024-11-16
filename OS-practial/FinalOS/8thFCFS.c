
#include<stdio.h> 
typedef struct { 

char data[20][2]; 
int end; 
}queue; 

void enqueue(queue *q,char data,int position); 
char dequeue(queue *q,int position); 
void fifo(char string[],int frameSize,int count); 


void main() { 

       int frameSize,count,cnt,ch; 
       char string[50]; 
       printf("Enter the string: "); 
       count=0; 
       do{ 
              scanf("%c",&string[count]); 
              count++; 

       }
       while(string[count-1]!='\n'); 
       count--;
       printf("\nEnter the size of the frame: "); 
       scanf("%d",&frameSize); 
       do{ 
              printf("\nMENU\n====\n1.FIFO\n2.Exit\n\nYour Choice:"); 
              scanf("%d",&ch); 
              switch(ch){ 
                     case 1:
                            fifo(string,frameSize,count); 
                            break;

                     case 2:
                     
                            //exit(0); 
                            break; 

                     default:
                            printf("\nInvalid choice! Please try again!"); 
                            continue; 

                     } 

              }
              while(ch!=2); 


       } 
       
       void enqueue(queue *q,char data,int position) { 

              q->data[position][0]=data; 

       } 
       char dequeue(queue *q,int position){ 
              char value; 
              value=q->data[position][0]; 
              return(value); 
       } 

       void fifo(char string[],int frameSize,int count) { 
              int cnt,cnt2,flag,faults=0; 
              queue q; 
              int firstin=-1; 
              q.end=0; 
              printf("\nData Requested\tFrame contents\t    Page Fault\n=============================================="); 
              for(cnt=0;cnt<count;cnt+=2)	{ 
                     printf("\n\n\t%c",string[cnt]); 
                     flag=0; 
                     for(cnt2=0;cnt2<q.end;cnt2++) { 
                            if(string[cnt]==q.data[cnt2][0]){ 
                                   flag=1; 
                                   break; 
                            } 

                     } 
                     if(flag==0){ 
                            faults++; 
                            if(q.end<frameSize) {	
                                   enqueue(&q,string[cnt],q.end); 
                                   q.end++; 

                            } 
                            else{ 
                           
                                   dequeue(&q,firstin); 
                                   firstin=(firstin+1)%(q.end); 
                                   enqueue(&q,string[cnt],firstin); 

                            } 
                            printf("\t  "); 
                            for(cnt2=0;cnt2<q.end;cnt2++) { 
                                   printf("%c   ",q.data[cnt2][0]); 

                            } 
                            printf("\t\tY"); 

                     } 
                     else{ 
                            printf("\t  "); 
                            for(cnt2=0;cnt2<q.end;cnt2++) { 
                            printf("%c   ",q.data[cnt2][0]); 
                     } 

                     printf("\t\tN"); 

              } 


       } 

       printf("\n\n==============================================\n"); 
       printf("\nTotal no. of Page Faults: %d\n\n",faults); 

} 
                     printf("\t\tY"); 

              } 

              else {	
                     printf("\t  "); 
                     for(cnt2=0;cnt2<q.end;cnt2++) { 
                            printf("%c   ",q.data[cnt2][0]); 
                     } 
                     printf("\t\tN"); 
              } 
       } 
       printf("\n\n==============================================\n"); 
       printf("\nTotal no. of Page Faults: %d\n\n",faults); 

} 
