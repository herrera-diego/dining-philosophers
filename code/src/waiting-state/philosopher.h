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
            Philosopher();
            bool checkNeighbor();
            void wait();
            void eat();
        protected:
            bool waitingState = true;
    
        
    };
}

#endif /* PHILOSOPHER_H_ */

// EOF