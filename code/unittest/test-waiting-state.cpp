#include "gtest/gtest.h"
#include <string>

#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "waiting-state/philosopher.h"
#include "waiting-state/chopstick.h"
#include "waiting-state/diningTable.h"
#include "constants.h"

using namespace WaitingPhilosopher;
using namespace std;


union semun
{
  int val;                        /* value for SETVAL */
  struct semid_ds *buf;                /* buffer for IPC_STAT & IPC_SET */
  unsigned short int *array;        /* array for GETALL & SETALL */
  struct seminfo *__buf;        /* buffer for IPC_INFO */
};

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

TEST_F(WaitingPhilosopherTest, chopstickCreation) 
{
    int id = 17;
    key_t semKey;
    int semId;

    semKey = ftok(SEMKEYPATH,id);
    ASSERT_FALSE( semKey == (key_t)-1 );

    semId = semget( semKey, NUMSEMS, 0666);
    ASSERT_TRUE ( semId == -1 );

    Chopstick testChopstick = Chopstick(id);

    semKey = ftok(SEMKEYPATH,id);
    ASSERT_FALSE( semKey == (key_t)-1 );

    semId = semget( semKey, NUMSEMS, 0666);
    ASSERT_FALSE ( semId == -1 );

    testChopstick.putAway();

    semKey = ftok(SEMKEYPATH,id);
    ASSERT_FALSE( semKey == (key_t)-1 );

    semId = semget( semKey, NUMSEMS, 0666);
    ASSERT_TRUE ( semId == -1 );
}

TEST_F(WaitingPhilosopherTest, chopstickOperations) 
{
    int id = 17;
    key_t semKey;
    int semId;
    struct sembuf sempar;
    int semval;
    union semun arg;

    Chopstick testChopstick = Chopstick(id);
    Philosopher aristotle = Philosopher(id, id+1);

    semKey = ftok(SEMKEYPATH,id);
    ASSERT_FALSE( semKey == (key_t)-1 );

    semId = semget( semKey, NUMSEMS, 0666);
    ASSERT_FALSE ( semId == -1 );

    semval = semctl( semId, 0, GETVAL , arg );
    ASSERT_EQ ( semval, 0 );

    aristotle.pickupChopstick(id);

    semval = semctl( semId, 0, GETVAL , arg );
    ASSERT_EQ ( semval, 1 );

    aristotle.pickupChopstick(id);

    semval = semctl( semId, 0, GETVAL , arg );
    ASSERT_EQ ( semval, 2 );

    aristotle.putdownChopstick(id);

    semval = semctl( semId, 0, GETVAL , arg );
    ASSERT_EQ ( semval, 1 );


    testChopstick.putAway();

    semKey = ftok(SEMKEYPATH,id);
    ASSERT_FALSE( semKey == (key_t)-1 );

    semId = semget( semKey, NUMSEMS, 0666);
    ASSERT_TRUE ( semId == -1 );
}


TEST_F(WaitingPhilosopherTest, DISABLED_evenPhilosophers) 
{
    DiningTable::startDinner(6);
}

TEST_F(WaitingPhilosopherTest, DISABLED_oddPhilosophers) 
{
    DiningTable::startDinner(5);
}

