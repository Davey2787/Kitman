#include <iostream>
#include <unistd.h>
#include <pthread.h> /*POSIX threads*/

using namespace std;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // creates a mutex called lock
	
int global; // global variable 

void *thread_routine1(void *argl) // thread routine 1 increments the global variable by 1, 100 times  
{
	pthread_mutex_lock(&lock); // locks the mutex lock
	for(int i = 0; i < 100; i++)
	{
		global++;
		cout<<global<<"\n";
	} 
	pthread_mutex_unlock(&lock); // unlocks the mutex lock
	pthread_exit(NULL);
}

void *thread_routine2(void *argl) // thread routine 2 increments the global variable by 2, 100 times 
{
	pthread_mutex_lock(&lock); // locks the mutex lock
	
	for(int i = 0; i < 100; i++)
	{
		global = global + 2;
		cout<<global<<"\n";
	}
	pthread_mutex_unlock(&lock); // unlocks the mutex lock
	pthread_exit(NULL);
}

int main()
{

	pthread_t thread1;
	pthread_t thread2;

	int rc;
	
		rc = pthread_create(&thread1, NULL, thread_routine1, NULL); // creates thread 1
			if(rc == 1)
			{	
				cout<<"Thread creation 1 failed\n";
			}
	
		rc = pthread_create(&thread2, NULL, thread_routine2, NULL); // creates thread 2
			if(rc == 1)
			{
				cout<<"Thread creation 2 failed\n";
			}	
	pthread_exit(NULL);
	pthread_mutex_destroy (&lock); // destroys the mutex lock
}