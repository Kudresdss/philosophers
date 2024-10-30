# philosophers
philosophers project for 42 cursus

Currently works only on macOS and linux systems.

Classic philosophers (uses threads as philosophers and mutexes as forks):
This project simulates the classic dining philosophers problem.
N philosophers are seated around a circular table with one fork between each pair of philosophers. A philosopher may eat if he can pick up the two forks adjacent to him. One fork may be picked up by any one of its adjacent followers but not both. Each time a philosopher finish eating, they will drop drop their forks and start sleeping. Once they have finished sleeping, the will start thinking and waiting to eat. Every philosopher needs to eat and they should never starve. Simulation stops when a philosopher dies or they all eat a certain number of times. Philosophers do not speak with each other.

Bonus project (uses processes as philosophers and semaphores as forks):
For the most part, it's the same as the classic problem, except all the forks are piled in the center of table.

Usage \
```./philo [N PHILOS] [DIE TIME] [EAT TIME] [SLEEP TIME] (OPT)[PHILO EAT N TIMES]``` \
(all TIME parameters are set in milliseconds)

Compilation (run this command in project's main or bonus directory):
- run "make"

Clean object files:
- run "make clean"

Full clean object and library files:
- run "make fclean"

Recompilation:
- run "make re"
