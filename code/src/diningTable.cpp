#include <string>
#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "diningTable.h"
#include "philosopher.h"
#include "chopstick.h"
#include "constants.h"

using namespace WaitingPhilosopher;
using namespace std;

void DiningTable::startDinner(int numberPhilosophers)
{
    Philosopher* philosophers =  (Philosopher*)malloc(sizeof(Philosopher) * numberPhilosophers);
    Chopstick* chopsticks =  (Chopstick*)malloc(sizeof(Chopstick) * numberPhilosophers);;
    pid_t pids[numberPhilosophers];

    printf("\n------  Dining Philosophers  ------\n\n\n");
    printf("%i philosophers dining\n\n", numberPhilosophers);
    for (int i = 0; i < numberPhilosophers; i++) 
    {
        philosophers[i] = Philosopher(i, numberPhilosophers);  
        chopsticks[i] = Chopstick(i);   
    }


    for (int i = 0; i < numberPhilosophers; i++) 
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
    int n = numberPhilosophers;
    while (n > 0) 
    {
        pid = wait(&status);
        //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
        --n;  // TODO(pts): Remove pid from the pids array.
    }

    for (int i = 0; i < numberPhilosophers; i++) 
    {
        chopsticks[i].putAway();
    }
    
    printf("\nFinished Diner\n");
}