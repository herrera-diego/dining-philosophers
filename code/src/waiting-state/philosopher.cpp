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
    int rc= 0;
    m_index = index;
    m_numPhilosophers = numPhilosophers;

     /* Generate an IPC key for the semaphore set and the shared      */
    /* memory segment.  Typically, an application specific path and  */
    /* id would be used to generate the IPC key.                     */
    m_semkey = ftok(SEMKEYPATH,m_index);
    if ( m_semkey == (key_t)-1 )
    {
      std::string error = "ID: " + std::to_string(m_index) + " ftok() for sem failed\n";
      perror(error.c_str());
      abort();
    }


    /* Create a semaphore set using the IPC key.  The number of      */
    /* semaphores in the set is two.  If a semaphore set already     */
    /* exists for the key, return an error. The specified permissions*/
    /* give everyone read/write access to the semaphore set.         */

    m_semid = semget( m_semkey, NUMSEMS, 0666 | IPC_CREAT | IPC_EXCL );
    if ( m_semid == -1 )
      {
        std::string error = "ID: " + std::to_string(m_index) + " semget() failed\n";
        perror(error.c_str());
        abort();
      }

    /* Initialize the first semaphore in the set to 0 and the        */
    /* second semaphore in the set to 0.                             */
    /*                                                               */
    /* The first semaphore in the sem set means:                     */
    /*        '1' --  The shared memory segment is being used.       */
    /*        '0' --  The shared memory segment is freed.            */

    /* The '1' on this command is a no-op, because the SETALL command*/
    /* is used.                                                      */
    rc = semctl( m_semid, 0, SETVAL, 0);
    if(rc == -1)
      {
        std::string error = "ID: " + std::to_string(m_index) + " semctl() initialization failed\n";
        perror(error.c_str());
      
      }



}

Philosopher::~Philosopher()
{
    // int rc = semctl( m_semid, 1, IPC_RMID );
    // if (rc==-1)
    // {
    //     std::cerr <<"ID: "<<m_index<<" semctl() remove id failed\n";
    // }
}

void Philosopher::think()
{    
}


void Philosopher::eat()
{
    
    int neighbor1 = (m_index + 1) % m_numPhilosophers ;
    int neighbor2 = (m_index - 1 + m_numPhilosophers) % m_numPhilosophers;

    printf("ID: %i, N1: %i, N2: %i\n",m_index,neighbor1,neighbor2);

    waitNeighbor(neighbor1);
    waitNeighbor(neighbor2);

    semaphoreOperation(m_index, 1);

    printf("ID: %i - Eating\n",m_index);
    // std::cout<<"Me: "<<m_index<<" Eating"<<std::endl;

    usleep(500);
    semaphoreOperation(m_index, -1);
    printf("ID: %i - Done\n",m_index);
    // std::cout<<"Me: "<<m_index<<" Done"<<std::endl;
}

void Philosopher::waitNeighbor(int index)
{
    printf("ID: %i - Waiting for neighbor: %i\n",m_index,index);
    // std::cout<<"Me: "<<m_index<<"Waiting for neighbor: "<<index<<std::endl;
    semaphoreOperation(index, 0);
    
}

void Philosopher::semaphoreOperation(int index, short action)
{
    printf("ID: %i - Operation on semaphore: %i - OpCode: %i\n",m_index, index, action);
    // std::cout<<"Me: "<<m_index<<"Waiting for neighbor: "<<index<<std::endl;
    int semId;
    key_t semKey;
    struct sembuf operations = {.sem_num = 0, .sem_op = action, .sem_flg = 0};



    /* Generate an IPC key for the semaphore set and the shared      */
    /* memory segment.  Typically, an application specific path and  */
    /* id would be used to generate the IPC key.                     */
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

    printf("ID: %i - Comleted Operation on semaphore: %i - OpCode: %i\n",m_index, index, action);
    
}

