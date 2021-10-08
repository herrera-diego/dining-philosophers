#include "gtest/gtest.h"
#include <string>

#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "waiting-state/philosopher.h"
#include "waiting-state/chopstick.h"
#include "constants.h"

using namespace WaitingPhilosopher;
using namespace std;

void deleteSemaphore(int id)
{
    key_t semkey = ftok(SEMKEYPATH,id);
    if ( semkey == (key_t)-1 )
    {
        std::cerr << "ID: "<<id<<" ftok() for sem failed\n";
        //return -1;
    }

    int semid = semget( semkey, NUMSEMS, 0666);
    if ( semid == -1 )
    {
        std::cerr <<"ID: "<<id<<" semget() failed\n";
        // return -1;
    }

    int rc = semctl( semid, 1, IPC_RMID );
    if (rc==-1)
    {
        std::cerr <<"ID: "<<id<<" semctl() remove id failed\n";
    }

    
}

class WaitingPhilosopherTest : public testing::Test 
{
    public: 

    void SetUp() override {  }
    void TearDown() override {  }

    // Per-test-suite set-up.
    // Called before the first test in this test suite.
    // Can be omitted if not needed.
    static void SetUpTestSuite() 
    {

    }

    // Per-test-suite tear-down.
    // Called after the last test in this test suite.
    // Can be omitted if not needed.
    static void TearDownTestSuite() 
    {

    }
};


TEST_F(WaitingPhilosopherTest, evenPhilosophers) 
{
    int numPh = 5;
    Philosopher* philosophers =  (Philosopher*)malloc(sizeof(Philosopher) * numPh);
    Chopstick* chopsticks =  (Chopstick*)malloc(sizeof(Chopstick) * numPh);;
    pid_t pids[numPh];


    for (int i = 0; i < numPh; i++) 
    {
        philosophers[i] = Philosopher(i, numPh);  
        chopsticks[i] = Chopstick(i);   
    }


    for (int i = 0; i < numPh; i++) 
    {    
        if ((pids[i] = fork()) < 0) 
        {
            perror("fork");
            abort();
        } 
        else if (pids[i] == 0) 
        {
            philosophers[i].dine();
            exit(0);
        }
    }

    int status;
    pid_t pid;
    int n = numPh;
    while (n > 0) 
    {
        pid = wait(&status);
        printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
        --n;  // TODO(pts): Remove pid from the pids array.
    }

    for (int i = 0; i < numPh; i++) 
    {
        chopsticks[i].putAway();
    }
}

