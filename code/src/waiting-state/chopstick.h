#ifndef CHOPSTICK_H_
#define CHOPSTICK_H_

// #ifdef __cplusplus
// extern "C" {
// #endif
#include <string>

namespace WaitingPhilosopher
{
    class Chopstick
    {    
        public:
            Chopstick(int index);
            void putAway();      
        protected:
            int m_index;
            int m_semid;
            key_t m_semkey;        
    };
}

#endif /* CHOPSTICK_H_ */

// EOF