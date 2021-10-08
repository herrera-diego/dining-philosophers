#include "philosopher.h"
#include "constants.h"

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <iostream>

#include <unistd.h>

using namespace WaitingPhilosopher;

Philosopher::Philosopher(int index, int numPhilosophers)
{
  m_index = index;
  m_numPhilosophers = numPhilosophers;
}


void Philosopher::think()
{   
  printf("ID: %i - Thinking\n",m_index); 
}

void Philosopher::eat()
{
  printf("ID: %i - Eating\n",m_index);
  usleep(500);
  printf("ID: %i - Done eating\n",m_index);
}

void Philosopher::dine()
{
    
  int chopstick1 = m_index;
  int chopstick2 = (m_index + 1) % m_numPhilosophers ;

  printf("ID: %i - Right Chopstick: %i, Left Chopstick: %i\n",m_index,chopstick1,chopstick2);

  think();

  waitChopstick(chopstick1);
  pickupChopstick(chopstick1);
  waitChopstick(chopstick2);
  pickupChopstick(chopstick2);
  
  eat();
  
  putdownChopstick(chopstick1);
  putdownChopstick(chopstick2);
  

  printf("ID: %i - Done\n",m_index);
    // std::cout<<"Me: "<<m_index<<" Done"<<std::endl;
}

void Philosopher::waitChopstick(int index)
{
    printf("ID: %i - Waiting for chopstick: %i\n",m_index,index);
    // std::cout<<"Me: "<<m_index<<"Waiting for chopstick: "<<index<<std::endl;
    semaphoreOperation(index, 0);
    
}

void Philosopher::pickupChopstick(int index)
{
    printf("ID: %i - pickup chopstick: %i\n",m_index,index);
    // std::cout<<"Me: "<<m_index<<"Waiting for chopstick: "<<index<<std::endl;
    semaphoreOperation(index, 1);
    
}

void Philosopher::putdownChopstick(int index)
{
    printf("ID: %i - putdown chopstick: %i\n",m_index,index);
    // std::cout<<"Me: "<<m_index<<"Waiting for chopstick: "<<index<<std::endl;
    semaphoreOperation(index, -1);
    
}

void Philosopher::semaphoreOperation(int index, short action)
{
    // printf("ID: %i - Operation on semaphore: %i - OpCode: %i\n",m_index, index, action);
    // std::cout<<"Me: "<<m_index<<"Waiting for chopstick: "<<index<<std::endl;
    int semId;
    key_t semKey;
    struct sembuf operations = {.sem_num = 0, .sem_op = action, .sem_flg = 0};

    // Generate an IPC key for the semaphore set
    semKey = ftok(SEMKEYPATH,index);
    if ( m_semkey == (key_t)-1 )
    {
        std::string error = "ID: " + std::to_string(m_index) + " ftok() for sem failed\n";
        perror(error.c_str());
        //return -1;
    }

    /* Get the already created semaphore ID associated with key.     */
    /* If the semaphore set does not exist, then it will not be      */
    /* created, and an error will occur.                             */
    semId = semget( semKey, NUMSEMS, 0666);
    if ( semId == -1 )
    {
        std::string error = "ID: " + std::to_string(m_index) + " semget() failed\n";
        perror(error.c_str());
        // return -1;
    }

    // operations[0].sem_num = 0;         /* Operate on the first sem      */
    // operations[0].sem_op =  action;         /* Wait for the value to be=0    */
    // operations[0].sem_flg = 0;         /* Allow a wait to occur         */

    int rc = semop( semId, &operations, 1 );
    if (rc == -1)
    {
        std::string error = "ID: " + std::to_string(m_index) + "  semop() failed\n";    
        perror(error.c_str());    
    }

    // printf("ID: %i - Comleted Operation on semaphore: %i - OpCode: %i\n",m_index, index, action);
    
}


