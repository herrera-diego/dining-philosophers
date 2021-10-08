#ifndef CONSTANTS_H
#define CONSTANTS_H

// #ifdef __cplusplus
// extern "C" {
// #endif
#include <string>

namespace WaitingPhilosopher
{
    #define SEMKEYPATH "/tmp"          /* Path used on ftok for semget key  */        
    #define SHMKEYPATH  SEMKEYPATH      /* Path used on ftok for shmget key  */
    #define OUTPUTPATH "/tmp"   /* Path used on ftok for semget key  */  
              
    #define NUMSEMS 1
    #define SIZEOFSHMSEG 2048
}

#endif /* PHILOSOPHER_H_ */

// EOF