#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
#define M 3
#define K 2
#define N 3
#define NUM_THREADS 9
pthread_t hThread[M][N];
int A [M] [K] = {{1,4},{2,5},{3,6}};
int B [K] [N] = {{8,7,6},{5,4,3}};
int C [M] [N]={0};

struct v
{
    int i;//row
    int j;//col
};

void ThreadProc(struct v *p)
{
     int k;
     int i=p->i;int j=p->j;
     for(k=0;k<2;k++)
       C[i][j]+=A[i][k]*B[k][j];
     printf("The thread is running!");
     pthread_exit(0);
}

int main()
{
    int i;int j;int ret;
    for(i=0;i<M;i++)
      for(j=0;j<N;j++)
        {
          struct v*data=(struct v*) malloc(sizeof(struct v));
          // struct v *data;
          data->i=i;
          data->j=j;
          ret=pthread_create(&hThread[i][j],NULL,(void*)ThreadProc,data);
          if(ret!=0){
            printf("Thread create error!!");
            return -1;
          }
         }
     for(i=0;i<M;i++)
       for(j=0;j<N;j++)
          pthread_join(hThread[i][j],NULL);
     printf("\n The result is:");
     for(i=0;i<M;i++)
     {
        for(j=0;j<N;j++)
        {
          printf("%d",C[i][j]);
        }
        printf("\n");
     }
     return 0;
}
