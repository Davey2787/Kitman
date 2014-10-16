#include <iostream>
#include <unistd.h>
#include <pthread.h> /*POSIX threads*/
#include <string>

using namespace std;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // creates a mutex called lock
pthread_mutex_t finish = PTHREAD_MUTEX_INITIALIZER;// creates a mutex called finish
pthread_cond_t print = PTHREAD_COND_INITIALIZER; // creates a condition variable called print
pthread_cond_t  clean_up = PTHREAD_COND_INITIALIZER; // creates a condition variable called clean_up
int count; // creates a global interger varible count 
string message; // creates a global string called message

void *thread_routine1(void *argl) // thread routine 1 gets the users information from the keyboard input
{

	pthread_mutex_lock(&lock); // locks the mutex lock
	cout<<"\nEnter information\n\n";
	getline(cin, message);
	count++;
	if(count == 1)pthread_cond_signal(&print); // signals condition variable print 
	pthread_mutex_unlock(&lock); // unlocks the mutex lock	
	return NULL;
}

void *thread_routine2(void *argl) // thread routine 2 prints out information entered by user
{
	pthread_mutex_lock(&lock); // locks the mutex lock
	if(count == 0)pthread_cond_wait(&print, &lock); // waits for signal from condition variable print 
	cout<<"\n"<<message<<"\n";
	count++;
	if(count == 2)pthread_cond_signal(&clean_up); // signals condition variable clean_up
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

	pthread_mutex_lock(&finish);  // locks the mutex finish
	if(count != 2)pthread_cond_wait(&clean_up, &finish); // waits for signal from condition variable clean_up			 
	pthread_mutex_destroy(&lock); // destroys the mutex lock
	pthread_cond_destroy(&print); // destroys the condition variable print
	pthread_mutex_unlock(&finish);  // unlocks the mutex finish
	pthread_mutex_destroy(&finish); // destroys the mutex finish
	pthread_cond_destroy(&clean_up); // destroys the condition variable clean_up
	cout<<"\nmain thread is finished\n\n";
	pthread_exit(NULL);

}
