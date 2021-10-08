#ifndef PHILOSOPHER_H_
#define PHILOSOPHER_H_

// #ifdef __cplusplus
// extern "C" {
// #endif
#include <string>

namespace WaitingPhilosopher
{
    class Philosopher
    {    
        public:
            Philosopher(int index, int numPhilosophers);
            void dine();
            void think();
            void eat();
            void waitChopstick(int index);
            void pickupChopstick(int index);
            void putdownChopstick(int index);
        protected:
            int m_index;
            int m_semid;
            int m_numPhilosophers;
            key_t m_semkey;  
            void semaphoreOperation(int index, short action);
    
    
        
    };
}

#endif /* PHILOSOPHER_H_ */

// EOF