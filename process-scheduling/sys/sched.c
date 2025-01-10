#include <sched.h>
#include <math.h>

int sched_class;

void setschedclass(int scheduler_type) {
    sched_class = scheduler_type;
}

int getschedclass() {
    return sched_class;
}