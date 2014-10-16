#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<iostream>
#include<unistd.h>
#include<pthread.h> /* POSIX threads */
#include<stdio.h>
#define NUM_THREADS
#include<string.h>
using namespace std;
#define SEMKEY 152
#define SHM_KEY1 9866
#define SHM_KEY2 9867
#define SHM_KEY3 9868
#define SHM_KEY4 9869

main()
{
	//Declare pointers
	int *in,*out;
	int *buffer;
	int *buffer_memory;

//Sets up names for semaphores
struct sembuf vsembuf, psembuf, v1sembuf, p1sembuf, v2sembuf, p2sembuf;
	
// create a 256 byte block of shared memory
// 0777 lets everybody read from it and everybody write from it and everybody can create it
// attch the process to the shared memory area
int shmid1=shmget(SHM_KEY1,8,0777|IPC_CREAT);
int shmid2=shmget(SHM_KEY2,1,0777|IPC_CREAT);
int shmid3=shmget(SHM_KEY3,1,0777|IPC_CREAT);
int shmid4=shmget(SHM_KEY4,1,0777|IPC_CREAT);

//Sets all buffers pointing to the first location of there corresponding shared memory 
buffer=(int*)shmat(shmid1,0,0);
in=(int*)shmat(shmid2,0,0);
out=(int*)shmat(shmid3,0,0);
buffer_memory=(int*)shmat(shmid4,0,0);


int semid;	
semid=semget(SEMKEY,3,0777|IPC_CREAT);	

psembuf.sem_num=0;
psembuf.sem_op=-1;	//Free Wait
psembuf.sem_flg=SEM_UNDO;

vsembuf.sem_num=0;
vsembuf.sem_op=1;	//Free Signal
vsembuf.sem_flg=SEM_UNDO;

p1sembuf.sem_num=1;
p1sembuf.sem_op=-1;	//Space Wait
p1sembuf.sem_flg=SEM_UNDO;

v1sembuf.sem_num=1;
v1sembuf.sem_op=1;	//Space Signal
v1sembuf.sem_flg=SEM_UNDO;

p2sembuf.sem_num=2;
p2sembuf.sem_op=-1;	//Data Wait
p2sembuf.sem_flg=SEM_UNDO;

v2sembuf.sem_num=2;
v2sembuf.sem_op=1;	//Data Signal
v2sembuf.sem_flg=SEM_UNDO;


	 
	while(1) // Sets the loop equal to true
	{	
		//If buffer_memory is equal to 0 then the Consumer will display a message saying its empty
		if(*buffer_memory==0)
		{
			cout<<"\nThe buffer is empty, The Consumer is blocked\n"<<endl;
		}	
		
		// Performs a Wait on Data
		semop(semid,&p2sembuf,1); 

		*buffer_memory=*buffer_memory-1;
		
		// Performs a Wait on Free
		semop(semid,&psembuf,1); 

		//The buffer is equal to *out which is equal to zero at the start. Consumer is looking in memory slot zero
		//*out is incremented by 1 and when the loop comes back around buffer is eaqual to 1 and Consumer looks in 
		//memory slot 1 etc.
		cout<<endl<<"The output of the buffer is "<<buffer[*out]<<endl;
		*out = *out+1;
		//when the buffer has read all 8 bits it will go back to memory slot zero and start reading from the start agian
		if(*out>7)
		{
			*out=0;
		}
		
		// Signals Free
		semop(semid,&vsembuf,1); 


		


		// Signals Space
		semop(semid,&v1sembuf,1); 
	}	
}


