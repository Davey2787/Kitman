#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/sem.h>


using namespace std; 

#define SHM_KEY 9876
#define SEMKEY 151

main()
{

	struct sembuf vsembuf, psembuf, v1sembuf, p1sembuf, v2sembuf, p2sembuf;
	int semid, i;

	semid = semget(SEMKEY, 3, 0777|IPC_CREAT); // Creates semaphore array

	psembuf.sem_num = 0; // space
	psembuf.sem_op = -1;
	psembuf.sem_flg = SEM_UNDO;

	vsembuf.sem_num = 0;
	vsembuf.sem_op = 1;
	vsembuf.sem_flg = SEM_UNDO;
 
	p1sembuf.sem_num = 1; // data
	p1sembuf.sem_op = -1;
	p1sembuf.sem_flg = SEM_UNDO;

	v1sembuf.sem_num = 1;
	v1sembuf.sem_op = 1;
	v1sembuf.sem_flg = SEM_UNDO;
	
	p2sembuf.sem_num = 2; // free
	p2sembuf.sem_op = -1;
	p2sembuf.sem_flg = SEM_UNDO;

	v2sembuf.sem_num = 2;
	v2sembuf.sem_op = 1;
	v2sembuf.sem_flg = SEM_UNDO;

	int shmid;
	int producer_buff_num;
	int consumer_buff_num;
	int item;
	int buff;
	// declare a pointer that will point to a
	// location in the memory that holds an integer
	int* ptr;  
	
	// create a 256 byte block of shared memory 
	// that can be read, writtten and accessed by any user
	shmid = shmget(SHM_KEY, 256, 0777|IPC_CREAT);
	

	// attach the process to the shared memory area 
	// pointer points at the first memory location
	// in the shared memory 
	
	ptr = (int *) shmat(shmid, 0, 0);	
	
	while(1)
	{	
			semop(semid, &p1sembuf, 1); // wait data
			semop(semid, &p2sembuf, 1); // wait free	
				producer_buff_num = *ptr;	// holds the next place in the buffer the producer is to add to next 
				consumer_buff_num = *(ptr + 1); // holds the next place in the buffer the consumer is to take from next 
				buff = consumer_buff_num;
				item = *(ptr + consumer_buff_num); // consumes item from buffer
				if(consumer_buff_num != 0)consumer_buff_num--; 
				producer_buff_num--;
				*ptr = producer_buff_num; // updates the next place in the buffer the producer is to add to next 
				*(ptr + 1) = consumer_buff_num; // updates the next place in the buffer the consumer is to take from next
			semop(semid, &v2sembuf, 1); // signal free
			semop(semid, &vsembuf, 1); // signal space
			cout<<"\nNumber stored in buffer number "<<buff;
			cout<<"\n"<<item;
	}
}


