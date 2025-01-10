# Process Scheduling

## Introduction
This project implements and explores advanced concepts of process management, including process priorities, scheduling algorithms, and context switching. It addresses the starvation problem in process scheduling by introducing two new scheduling policies.

## Features
- **Exponential Distribution Scheduler (`EXPDISTSCHED`)**: Selects the next process based on a random value following an exponential distribution. Ensures fairness by using round-robin scheduling for processes with identical priorities.
  
- **Linux-like Scheduler (`LINUXSCHED`)**: Emulates the Linux 2.2 kernel scheduler by dividing CPU time into epochs and allocating time quanta based on process priority. Utilizes goodness values to determine the next process to schedule.

## Implementation Details

### Exponential Distribution Scheduler (`EXPDISTSCHED`)
```c
double expdev(double lambda) {
    double dummy;
    do
        dummy= (double) rand() / RAND_MAX;
    while (dummy == 0.0);
    return -log(dummy) / lambda;
}
```
Implemented necessary mathematical functions (`log()`, `pow()`) in `math.c` due to the absence of a math library in Xinu. Updated the `Makefile` accordingly.

### Linux-like Scheduler (`LINUXSCHED`)
Manages quantum values and goodness calculations to ensure proper process scheduling and fairness. Processes that exhaust their quantum have a goodness value of 0, while runnable processes have a goodness value calculated as `goodness = counter + priority`. The scheduler selects the process with the highest goodness value, using round-robin if there are ties.

### Scheduling Class Management
```c
void setschedclass(int sched_class)
```
Sets the scheduling policy to either `EXPDISTSCHED` or `LINUXSCHED`. Policy switching is not required during runtime.

```c
int getschedclass()
```
Returns the current scheduling class, either `EXPDISTSCHED` or `LINUXSCHED`.
```c
#define EXPDISTSCHED 1
#define LINUXSCHED 2
```

## Installation
1. Navigate to the project directory:
    ```bash
    cd process-scheduling
    ```
2. Compile the project:
    ```bash
    make
    ```

## Usage
Run the scheduler with the desired scheduling class:
```bash
./scheduler --class EXPDISTSCHED
```
or
```bash
./scheduler --class LINUXSCHED
```

## Contributing
Contributions are welcome! Please open an issue or submit a pull request for any enhancements or bug fixes.

## License

This project is licensed under the MIT License.

## Acknowledgments
- Inspired by the Xinu operating system.
- Thanks to the open-source community for valuable resources and support.
- [Exponential Distribution](https://en.wikipedia.org/wiki/Exponential_distribution)
