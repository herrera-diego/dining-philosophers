#include "gtest/gtest.h"
#include <string>
#include "waiting-state/philosopher.h"
#include "waiting-state/fork.h"

using namespace WaitingPhilosopher;
using namespace std;

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
    int numPh = 6;
    Philosopher phs[numPh];
    Fork forks[numPh*2 -1];
    ASSERT_TRUE(forks[0].isBeingUsed());


}

