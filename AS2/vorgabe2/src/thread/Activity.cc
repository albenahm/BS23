#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

Activity:: Activity(){
    this->zustand = ZOMBIE;
    this->activitat=0;
    scheduler.start(this);
}

Activity:: Activity(void* tos){
    this->zustand = BLOCKED;
    this->activitat=0;
    this->Coroutine=tos;
}

Activity:: ~Activity(){
    scheduler.kill(this);
}


