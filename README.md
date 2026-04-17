*This project has been created as part of the 42 curriculum by mobenhab.*

# Codexion — Master the race for resources before the deadline masters you

---

## Description


**Codexion** is a concurrent programming project from the 42 curriculum. It simulates a resource-sharing problem between **coders** competing to acquire **dongles** (shared hardware licenses) in order to work — all while a **monitor** thread watches over them, enforcing rules and detecting burnout or starvation.

Each coder follows a strict lifecycle:
1. **Think** — decide to acquire resources
2. **Acquire dongles** — grab the required number of shared dongles
3. **Code** — work for a defined duration
4. **Release dongles** — free resources for others
5. **Rest** — cooldown before the next cycle

The challenge lies in ensuring that all coders make progress without deadlocking, starving, or burning out — under tight timing constraints and with a fully thread-safe logging system.

---

## Instructions

### Compilation

```bash
make
```

This produces the `codexion` binary at the root of the repository.

### Usage

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_code> <time_to_rest> <number_of_dongles> [max_cycles]
```

| Argument | Description |
|---|---|
| `number_of_coders` | Total number of coder threads |
| `time_to_burnout` | Time (ms) a coder can go without coding before dying |
| `time_to_code` | Duration (ms) of a coding session |
| `time_to_rest` | Duration (ms) of the rest phase |
| `number_of_dongles` | Total number of shared dongles available |
| `max_cycles` *(optional)* | Stop after each coder has coded this many times |

### Example

```bash
./codexion 5 800 200 150 3
./codexion 4 600 180 120 2 7
```

### Cleanup

```bash
make clean   # removes object files
make fclean  # removes object files and binary
make re      # fclean + compile
```

---

## Blocking Cases Handled

### Deadlock Prevention & Coffman's Conditions

Deadlock requires four conditions to hold simultaneously: mutual exclusion, hold-and-wait, no preemption, and circular wait. This implementation breaks **circular wait** by enforcing a **consistent global ordering** on dongle acquisition. All coders request dongles in the same deterministic order, making cyclic dependency impossible.

### Starvation Prevention

To prevent indefinite postponement, coders that have been waiting the longest are given **priority access** to available dongles. A combination of condition variables and a FIFO-style wait queue ensures that no coder is perpetually bypassed by others.

### Cooldown Handling

After each coding session, a coder enters a mandatory rest phase. This cooldown prevents a single coder from monopolizing dongles across consecutive cycles and gives other threads a fair window to acquire resources.

### Precise Burnout Detection

The monitor thread continuously tracks the **last time each coder successfully started coding**. Timestamps are recorded atomically under mutex protection. If the elapsed time since a coder's last coding session exceeds `time_to_burnout`, the monitor sets a global death flag and halts the simulation cleanly.

### Log Serialization

All state-change messages (thinking, acquiring, coding, resting, burnout) are printed through a **dedicated logging mutex**. This guarantees that log lines are never interleaved or corrupted, and that the timestamp prepended to each line reflects the actual moment the event occurred.

---

## Thread Synchronization Mechanisms

### `pthread_mutex_t` — Mutual Exclusion Locks

Mutexes are the backbone of the implementation. Several distinct mutexes are used:

- **Dongle mutexes** — one per dongle; a coder must hold all required dongle mutexes before entering its coding session.
- **Log mutex** — serializes all writes to stdout, ensuring atomic and ordered log output.
- **Monitor mutex** — protects shared state read and written by both coder threads and the monitor (e.g., last-meal timestamps, death flag).

**Race condition prevention example:** Without the monitor mutex, a coder thread could read `death = false`, get preempted, and the monitor could set `death = true` before the coder writes its log — resulting in a post-death log line. The mutex ensures these two operations are always atomic relative to each other.

### `pthread_cond_t` — Condition Variables

Condition variables are used to implement the **dongle wait queue**: when a coder cannot acquire the required dongles, it calls `pthread_cond_wait()` on a shared condition, atomically releasing the associated mutex and suspending itself. When a coder releases its dongles, it broadcasts via `pthread_cond_broadcast()` to wake all waiting coders, which then re-evaluate availability.

```c
pthread_mutex_lock(&state->dongle_lock);
while (!dongles_available(state, needed)) {
    pthread_cond_wait(&state->dongle_cond, &state->dongle_lock);
}
acquire_dongles(state, coder_id, needed);
pthread_mutex_unlock(&state->dongle_lock);
```

### Custom Event / Death Flag

A simple atomic flag (`volatile int dead`) serves as a lightweight event signal. It is written exclusively by the monitor thread and read by all coder threads at the start of each lifecycle phase. Access is always wrapped in the monitor mutex to prevent torn reads on multi-core systems.

### Thread-Safe Communication Between Coders and Monitor

The monitor runs as a dedicated thread, polling coder timestamps at a tight interval (~1 ms sleep). Communication flows in one direction: coders **update** their `last_coded_at` timestamp (under mutex), and the monitor **reads** all timestamps to check for burnout. The monitor never modifies coder state beyond setting the global death flag, which minimises contention and keeps critical sections short.

---

## Resources

### Documentation & References

- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [`pthread_mutex_t` man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [`pthread_cond_t` man page](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html)
- [Coffman Conditions — Wikipedia](https://en.wikipedia.org/wiki/Coffman_conditions)
- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- *The Art of Multiprocessor Programming* — Herlihy & Shavit

### AI Usage

**Claude (Anthropic)** was used during this project for the following tasks:

- **README generation** — structuring and writing this file based on project specifications and implementation details provided by the author.
- **Debugging assistance** — identifying potential race conditions and reviewing critical section logic during development.


The actual implementation, design decisions, and all submitted code were written by **mobenhab**.
