
#include <pthread.h> //Needed for thread functionality
#include <time.h> // Implicetely already included from pthread.h
#include <iostream> // Needed for cout/endl

//Use global variables for brevity
pthread_mutex_t* mutex;
pthread_cond_t* sec,min;
int ds,s,m;
//Function to be run on separate threads
// Must have single "void*" parameter and return "void*"
//Thread is stopped / detroyed when function exists
void* ds_timer(void* args) {

    while(true){

    //Create a struct for storing time
    timespec sleep_time;
    sleep_time.tv_sec = 0;
    sleep_time.tv_nsec = 100000000;


    //Sleep this thread for 1 decisec 
    // If we are interrupted we do not care
    nanosleep(&sleep_time, NULL);
    ds = ds+1;

    if (ds > 9) {
        pthread_cond_broadcast(sec);
        ds = 0;
    }

    std::cout << "\r" << s << " : " << ds << std::flush;
    }
}

void* s_timer(void* args) {

    while(true){
    //Create a struct for storing time
    timespec sleep_time;
    sleep_time.tv_sec = 1;
    sleep_time.tv_nsec = 0;


    //Sleep this thread for 1 decisec 
    // If we are interrupted we do not care
    nanosleep(&sleep_time, NULL);
    s = s+1;

    }
}



int main(int argc, char** argv){

    //create a new mutex
    mutex = new pthread_mutex_t();
    sec = new pthread_cond_t();

    //Create a thread object on the heap for demonstration
    pthread_t* ds_thread = new pthread_t();
    pthread_t* s_thread = new pthread_t();

    // Initialise the thread with the default attributes,
    // the "thread_routine" fuction, qnd no argumrnts
    pthread_create(ds_thread, NULL , ds_timer, mutex);
    pthread_create(s_thread, NULL , s_timer, mutex);

    // wait for the new thread to join, ignoring any return valuea
    pthread_join(*ds_thread, NULL);
    pthread_join(*s_thread, NULL);
}