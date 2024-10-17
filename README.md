# Philosophers - 42 Project

The **Philosophers** project is a classic problem in computer science, also known as the **Dining Philosophers Problem**, which demonstrates challenges in concurrency, particularly deadlock, race conditions, and resource sharing. This project helps build an understanding of threading, synchronization, and mutexes (mutual exclusion).

## Table of Contents

1. [About](#about)
2. [Project Structure](#project-structure)
3. [Problem Description](#problem-description)
4. [How to Use](#how-to-use)
5. [Compilation](#compilation)
6. [Testing](#testing)

## About

In the **Philosophers** project, several philosophers sit around a table, alternating between eating, thinking, and sleeping. There are as many forks as there are philosophers, but each philosopher needs two forks to eat, leading to potential conflicts and deadlocks. The goal is to simulate this scenario, ensuring that the philosophers can eat without falling into a deadlock or race condition while minimizing the complexity of resource contention.

This project focuses on understanding multithreading and synchronization, using pthreads, mutexes, and semaphores to manage shared resources (forks) between the threads (philosophers).

## Project Structure

- `philosophers.h`: Header file containing function prototypes, macros, and necessary includes.
- `philosophers.c`: The main file containing the simulation logic.
- `utils.c`: Utility functions for time management, error handling, and logging.
- `Makefile`: Compilation rules to build the program.

## Problem Description

The philosophers’ routine is as follows:

- **Thinking**: The philosopher is thinking but not interacting with forks.
- **Eating**: The philosopher must pick up two forks (one from their left and one from their right) to eat. This action must be synchronized to prevent two philosophers from picking up the same fork simultaneously.
- **Sleeping**: After eating, the philosopher puts the forks down and sleeps for a while before thinking again.

The program ensures that:

- No philosopher can access a fork that another philosopher is already using.
- Philosophers do not die from starvation, which occurs if they cannot eat within a specific time limit.
- The simulation ends either when a philosopher dies or after a given number of meals.

### Input Parameters

The program takes the following command-line arguments:

- **number_of_philosophers**: The number of philosophers (and forks).
- **time_to_die**: Time (in milliseconds) a philosopher can survive without eating.
- **time_to_eat**: Time (in milliseconds) it takes for a philosopher to eat.
- **time_to_sleep**: Time (in milliseconds) a philosopher spends sleeping.
- **number_of_times_each_philosopher_must_eat** (optional): The simulation stops when each philosopher has eaten this many times. If not provided, the simulation runs until a philosopher dies.

### Example:

```bash
./philosophers 5 800 200 200
```
## How to Use

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/username/philosophers.git
    cd philosophers
    ```

2. Compile the program using `make`:

    ```bash
    make
    ```

3. Run the program with the required parameters:

    ```bash
    ./philosophers 5 800 200 200
    ```

4. Observe the philosophers' behavior in the terminal. Each philosopher will be printed out as they take turns eating, thinking, and sleeping.

## Compilation

- `make`: Compiles the philosophers program.
- `make clean`: Deletes object files.
- `make fclean`: Deletes object files and the compiled binary.
- `make re`: Cleans and recompiles the program.

## Testing

### Basic Testing

Run the program with different values for the number of philosophers, `time_to_die`, `time_to_eat`, and `time_to_sleep`:

```bash
./philosophers 4 400 100 100
```
