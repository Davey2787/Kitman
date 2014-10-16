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

	//Declare Pointers
	int *in,*out;
	int *buffer;
	int *buffer_memory;

//Sets up names for semaphores
struct sembuf vsembuf, psembuf, v1sembuf, p1sembuf, v2sembuf, p2sembuf;

// create a 256 byte block of shared memory
// 0777 lets everybody read from it and everybody write from it and everybody can create it
// attch the process to the shared memory area
int shmid1 = shmget(SHM_KEY1, 8, 0777|IPC_CREAT); 
int shmid2 = shmget(SHM_KEY2, 1, 0777|IPC_CREAT);
int shmid3 = shmget(SHM_KEY3, 1, 0777|IPC_CREAT);
int shmid4 = shmget(SHM_KEY4, 1, 0777|IPC_CREAT);


//Sets all buffers pointing to the first location of there corresponding shared memory 
buffer=(int*)shmat(shmid1,0,0);
in=(int*)shmat(shmid2,0,0);
out=(int*)shmat(shmid3,0,0);
buffer_memory=(int*)shmat(shmid4,0,0);

int semid;
//Create 3 semaphore
semid=semget(SEMKEY,3,0777|IPC_CREAT);	

semctl(semid,0,SETVAL,1); // Free
semctl(semid,1,SETVAL,8); // Space
semctl(semid,2,SETVAL,0); // Data


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

	//Initialize in, out and buffer_memory to zero
	*in = 0;
	*out = 0;
	*buffer_memory=0;


//Initialize buffer to 8 bytes
buffer[8];



//Creats an variable to save the users input
int input;


while (1) // Sets the loop equal to true
{
	//If buffer_memory is equal to 8 then the producer will display a message saying its full
		if(*buffer_memory==8)
		{
			cout<<"\nThe buffer is full, The Producer is Blocked\n"<<endl;
		}
		//Performs wait on Space
		semop(semid,&p1sembuf,1); 
		//Asks the user to enter a number
		cout<<endl<<"Enter a number to be stored in the buffer \n";
		//Saves users number to input 
		cin>>input;
		//Performs a wait on free
		semop(semid,&psembuf,1);
		//The buffer is equal to *int which is ecout<<"\nPlease enter a non-zero number\n";
			//cin>>item;//equal to zero at the start. Input is stored in memory slot zero
		//*in is incremented by 1 and when the loop comes back around buffer is eaqual to 1 and input is saved in 
		//memory slot 1 etc.
		buffer[*in]=input;
		*in = *in+1;
		//when the buffer has all 8 bits filled it will go back to memory slot zero and start wrighting from the start agian
		if(*in>7)
		{
			*in=0;
		}
		//Performs Signal on Free
		semop(semid,&vsembuf,1); 
		//Increment buffer_memory
		*buffer_memory=*buffer_memory+1;
		//Performs Signal on Data
		semop(semid,&v2sembuf,1); 
	}	


	}


