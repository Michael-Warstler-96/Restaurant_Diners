/**
   @file barrier.cpp
   @author Michael Warstler 
   Create 4 threads representing people waiting at a restaurant. 
   Each thread is waiting until the final thread arrives.
*/

#include <pthread.h>
#include <iostream>
using namespace std;

pthread_mutex_t mutex   = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;

/** Total number of threads currently active */
int totalThreads = 0;
/** Task of a thread while waiting */
char taskWhileWaiting = 'A';

/** Function for threads to wait */
void waitForOthers();

/** Thread function */
void * Restaurant(void * param);

/**
   Creates 4 threads to wait at restaurant.
*/
int main(){
 
   // Initialize pthread parameters
   pthread_t hungryThd[4]; 
   pthread_attr_t attr; 
   pthread_attr_init(&attr); 
   
   // create threads
   for ( int i = 0; i < 4; i++ ) {
       pthread_create( &hungryThd[i], &attr, Restaurant, NULL );
   }
   
   // join threads
   for ( int j = 0; j < 4; j++ ) {
       pthread_join( hungryThd[j], NULL );
   }
   
   return 0;
}

/**
   Function for threads to perform while waiting.
*/
void waitForOthers(){

   // Lock the mutex so only 1 thread is active.
   pthread_mutex_lock( &mutex );
   
   // Critical section: Only 1 thread using at a single time.
   int threadNum = totalThreads + 1;
   printf( "I am thread %d, working on Task %c, and waiting to eat.\n", threadNum, taskWhileWaiting );
   taskWhileWaiting++;
   totalThreads++;
   
   // Mutex is unlocked for another thread to use.
   pthread_mutex_unlock( &mutex );
   
   // Threads or restaurant goers are waiting until all 4 people have "arrived".
   while ( totalThreads < 4 ) {
       /* Busy Wait */
   }
   printf( "I am thread %d and I am eating.\n", threadNum );
}

/**
   Function used by threads (restaurant goers) 
*/
void * Restaurant(void * param){

   // call wait function
   waitForOthers();
   pthread_exit(NULL);
}



















