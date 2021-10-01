#ifndef FORK_H_
#define FORK_H_

// #ifdef __cplusplus
// extern "C" {
// #endif
#include <string>

namespace WaitingPhilosopher
{
    class Fork
    {    
        public:
            Fork();
            bool isBeingUsed();
        protected:
            bool IsUsed = true;

    
        
    };
}

#endif /* FORK_H_ */

// EOF