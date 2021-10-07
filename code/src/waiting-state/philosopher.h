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
            ~Philosopher();
            void think();
            void eat();
        protected:
            int m_index;
            int m_semid;
            int m_numPhilosophers;
            key_t m_semkey;  

            void waitNeighbor(int index);
            void semaphoreOperation(int index, short action);
    
    
        
    };
}

#endif /* PHILOSOPHER_H_ */

// EOF