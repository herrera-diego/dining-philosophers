#include "chopstick.h"
#include "constants.h"

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <iostream>

#include <unistd.h>

using namespace WaitingPhilosopher;

Chopstick::Chopstick(int index)
{
    int rc= 0;
    m_index = index;

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

    // Initialize the semaphore in the set to 0      
    rc = semctl( m_semid, 0, SETVAL, 0);
    if(rc == -1)
    {
    std::string error = "ID: " + std::to_string(m_index) + " semctl() initialization failed\n";
    perror(error.c_str());
    
    }
}

void Chopstick::putAway()
{
    int rc = semctl( m_semid, 1, IPC_RMID );
    if (rc==-1)
    {        
        std::string error = "ID: " + std::to_string(m_index) + " semctl() remove id failed\n";
        perror(error.c_str());
    }
}
