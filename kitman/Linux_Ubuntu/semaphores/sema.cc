#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <iostream>

using namespace std;

#define SEMKEY 151

main()
{
	struct sembuf Ssembuf, Wsembuf;
	int semid, i;

	semid = semget(SEMKEY, 1, 0777|IPC_CREAT);
	semctl(semid, 0, SETVAL, 1);

	Wsembuf.sem_num = 0;
	Wsembuf.sem_op = -1;
	Wsembuf.sem_flg = SEM_UNDO;

	Ssembuf.sem_num = 0;
	Ssembuf.sem_op = 1;
	Ssembuf.sem_flg = SEM_UNDO;
 
	semop(semid, &Wsembuf, 1);
	cout<<"\nPlease enter a value\n";
	cin>>i;
	cout<<"\nYou have entered "<<i<<"\n";
	semop(semid, &Ssembuf, 1);
}
