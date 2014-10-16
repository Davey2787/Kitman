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

	struct sembuf Ssembuf, Wsembuf;
	int semid, i;

	semid = semget(SEMKEY, 1, 0777|IPC_CREAT);
	//semctl(semid, 0, SETVAL, 1);

	Wsembuf.sem_num = 0;
	Wsembuf.sem_op = -1;
	Wsembuf.sem_flg = SEM_UNDO;

	Ssembuf.sem_num = 0;
	Ssembuf.sem_op = 1;
	Ssembuf.sem_flg = SEM_UNDO;
 
	
	int shmid;
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
		semop(semid, &Wsembuf, 1);
		for(int i = 0; i < 256; i++)
		{
			cout<<*(ptr + i);
		}
		semop(semid, &Ssembuf, 1);
	}
}


