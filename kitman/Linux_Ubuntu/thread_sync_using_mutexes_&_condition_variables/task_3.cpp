#include <iostream>
#include <unistd.h>
#include <pthread.h> /*POSIX threads*/
#include <string>

using namespace std;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // creates a mutex called lock
string message; // creates a global string called message

void *thread_routine1(void *argl) // thread routine 1 gets the users information from the keyboard input  
{

	pthread_mutex_lock(&lock); // locks the mutex lock
	cout<<"\nEnter information\n";
	getline(cin, message);
	pthread_mutex_unlock(&lock); // unlocks the mutex lock
	return NULL;
}

void *thread_routine2(void *argl) // thread routine 2 prints out information entered by user
{
	pthread_mutex_lock(&lock); // locks the mutex lock
	cout<<message<<"\n"; 
	pthread_mutex_unlock(&lock); // unlocks the mutex lock
	return NULL;
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
	pthread_mutex_destroy (&lock);	// destroys mutex lock
	pthread_exit(NULL);

}
