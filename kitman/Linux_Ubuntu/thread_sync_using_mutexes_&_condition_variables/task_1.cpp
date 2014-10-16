#include <iostream>
#include <unistd.h>
#include <pthread.h> /*POSIX threads*/

using namespace std;

int global = 0; // global variable 

void *thread_routine1(void *argl) // thread routine 1 increments the global variable by 1, 100 times  
{
	
	for(int i = 0; i < 100; i++)
	{
		global++;
		cout<<global<<"\n";
	} 

	pthread_exit(NULL);
}

void *thread_routine2(void *argl) // thread routine 2 increments the global variable by 2, 100 times 
{
	for(int i = 0; i < 100; i++)
	{
		global = global + 2;
		cout<<global<<"\n";
	} 
	pthread_exit(NULL);
}

int main()
{
	
	pthread_t thread1;
	pthread_t thread2;

	/*create thread*/

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

	cout<<"main thread is finished\n";
	
	pthread_exit(NULL);
}
