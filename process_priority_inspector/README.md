# Process Priority Inspector

## Overview

Process Priority Inspector is a tool designed to monitor and inspect processes based on their priority levels within the XINU operating system. It provides detailed information about each process, including stack base, stack size, stack limit, stack pointer, process name, process ID, and process priority. Additionally, it summarizes system call activities for each process.

## Features

- **Process Inspection:** Lists all processes with a priority higher than the specified parameter.
- **Stack Information:** Displays stack base, stack size, stack limit, and stack pointer for each relevant process.
- **Process Details:** Includes process name, process ID, and process priority.
- **System Call Summary:** Provides a summary of system call occurrences and average execution times per process.
- **Integration with XINU:** Seamlessly integrates with the XINU operating system for real-time monitoring.

## Installation

### Prerequisites

- XINU operating system source code.
- QEMU emulator.
- GNU Debugger (GDB).
- Make build system.

### Building XINU

To compile the XINU kernel, run `make` in the compile directory as follows:

```bash
make
```

This creates an OS image called `xinu.elf`.

### Running and Debugging XINU

The XINU image runs on the QEMU emulator machine. To boot up the image, type:

```bash
qemu-system-<options> -kernel xinu.elf
```

XINU should start running and print messages.

Typing `Ctrl-a` then `c` (not `Ctrl-c`, make sure you release the Ctrl key) will always bring you to the `(qemu)` prompt. From there, you can quit by typing `q`.

To debug XINU, run the image in debug mode by:

```bash
qemu-system-<options> -s -S -kernel xinu.elf
```

Then execute GDB in another SSH session:

```bash
gdb xinu.elf
```

In the `(gdb)` console, connect to the remote server by:

```gdb
(gdb) target remote localhost:1234
```

You can use many debugging features provided by GDB, e.g., adding a breakpoint at the main function:

```gdb
(gdb) break main
```

To run to the next breakpoint, type:

```gdb
(gdb) continue
```

The detailed document for GDB can be found [here](https://www.gnu.org/software/gdb/documentation/).

## Usage

- **Run the Program:** Execute the main program to start monitoring processes and system calls.
- **Specify Priority:** Provide a priority parameter to filter and display processes with higher priority.
- **View Output:** Observe the printed stack and process information, along with system call summaries.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## License

This project is licensed under the MIT License.