*This project has been created as part of the 42 curriculum by mesalman.*

## Description

Philosophers is a concurrency project that simulates the classic Dining Philosophers problem. A given number of philosophers sit around a round table. Each philosopher alternates between eating, sleeping, and thinking. To eat, a philosopher needs two forks — one on their left and one on their right. Since there are exactly as many forks as philosophers, they must share. The simulation ends when a philosopher dies of starvation, or when all philosophers have eaten a specified number of times.

The main challenge is avoiding three concurrent programming hazards: **deadlock** (all philosophers grab one fork and wait forever), **data races** (two threads reading/writing shared data without protection), and **starvation** (a philosopher never gets to eat).

Each philosopher runs as a separate thread. Each fork is protected by a mutex. A dedicated monitor thread watches for deaths and meal completion.

## Instructions

**Compile:**
```
make
```

**Run:**
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]
```

- `number_of_philosophers` — how many philosophers (and forks) at the table
- `time_to_die` (ms) — a philosopher dies if they haven't started eating within this time since their last meal
- `time_to_eat` (ms) — how long eating takes (requires holding two forks)
- `time_to_sleep` (ms) — how long a philosopher sleeps after eating
- `meals` (optional) — simulation stops once every philosopher has eaten this many times

**Test cases from subject:**
```
./philo 1 800 200 200       # philosopher should die
./philo 5 800 200 200       # no philosopher should die
./philo 5 800 200 200 7     # stops after everyone eats 7 times
./philo 4 410 200 200       # no philosopher should die
./philo 4 310 200 100       # one philosopher should die
```

## Resources

- [POSIX Threads Programming — Blaise Barney, LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [The Little Book of Semaphores — Allen B. Downey](https://greenteapress.com/semaphores/)
- Andrew S. Tanenbaum — *Modern Operating Systems* (Chapter 2: Processes and Threads — covers mutexes, deadlock, and the dining philosophers problem directly)
- Abraham Silberschatz, Peter Galvin, Greg Gagne — *Operating System Concepts* (Chapter 7: Synchronization Examples — dining philosophers as a classic synchronization case study)
- `man pthread_create`, `man pthread_mutex_init`, `man gettimeofday`
- [Dining Philosophers — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

**AI usage in this project:**

AI (Claude) was used as a debugging and review tool throughout the project. Specifically:

- Identifying a missing `pthread_mutex_unlock` in the single-philosopher case (the fork was locked but never released before `pthread_mutex_destroy`)
- Reviewing the overall struct design and suggesting a `t_fork` struct with `id` and `mutex` fields to make fork ownership explicit in the philosopher struct via `left_fork` and `right_fork` pointers
- Verifying that the argument validation logic correctly handles edge cases like `meal_limit = 0`

All code was written, read, and understood by the student. AI suggestions were reviewed, tested, and explained before being accepted.
