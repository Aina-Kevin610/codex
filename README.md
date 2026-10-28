*This project has been created as part of the 42 curriculum by airandri.*

# Codexion

## Description

Codexion is a multithreaded C simulation of a shared coding environment in which several coders compete for a limited number of USB dongles to compile quantum code. Each coder is represented by a POSIX thread and alternates between compiling, debugging, and refactoring phases while respecting a burnout deadline.

The project models a classic synchronization problem: multiple workers must acquire multiple shared resources under strict timing constraints without causing deadlocks, starvation, or inconsistent state. The simulation supports two arbitration policies:

- `fifo`: requests are served in arrival order.
- `edf`: requests are served by the earliest deadline first, where the deadline is `last_compile_start + time_to_burnout`.

The program also enforces cooldown periods on each dongle after release, detects burnout with a dedicated monitor thread, and serializes log output so that each state transition is printed cleanly and deterministically.

## Project goal

The aim of this project is to design and implement a correct concurrent system that:

- prevents resource duplication and deadlocks,
- ensures fair access to shared dongles,
- respects deadlines and avoids burnout under feasible conditions,
- keeps the simulation coherent through precise synchronization,
- logs all state transitions in a thread-safe and readable way.

## Instructions

### Compilation

From the project root, run:

```bash
make
```

This builds the executable `codexion` with the required warnings and thread flags.

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Arguments:

- `number_of_coders`: number of coders and dongles
- `time_to_burnout`: maximum time before a coder must start compiling again
- `time_to_compile`: time required to compile
- `time_to_debug`: debug duration
- `time_to_refactor`: refactor duration
- `number_of_compiles_required`: termination target
- `dongle_cooldown`: cooldown period after a dongle is released
- `scheduler`: `fifo` or `edf`

Example:

```bash
./codexion 4 1500 200 200 200 10 100 fifo
```

### Example log format

```text
0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
402 2 has taken a dongle
403 2 has taken a dongle
403 2 is compiling
603 2 is debugging
803 2 is refactoring
1204 3 burned out
```

## Features

- One thread per coder
- One dongle per adjacent edge in the circular table layout
- Two-dongle acquisition requirement for compilation
- Dongle cooldown enforcement
- Deterministic scheduling with a custom heap-based queue
- Burnout detection and simulation stopping condition
- Serialized log output for reliable traces
- Full memory cleanup and safe thread shutdown

## Blocking cases handled

This project explicitly addresses the main concurrency hazards behind the Codexion simulation:

- Deadlock prevention: coders never hold a single dongle while waiting for another without a strict acquisition protocol, and the scheduler ensures requests are coordinated without circular waiting.
- Coffman conditions: the implementation avoids the conditions that lead to deadlock by controlling acquisition order, shared state updates, and resource release timing.
- Starvation prevention: FIFO and EDF scheduling provide bounded waiting and fairness when the parameters are feasible.
- Cooldown handling: after a dongle is released, it cannot be reclaimed before the cooldown time has elapsed, preventing rapid oscillation and duplicate ownership.
- Precise burnout detection: a dedicated monitor checks the last compile start time and raises the stop condition as soon as a deadline is missed.
- Log serialization: each message is emitted under a single mutex so two lines cannot interleave on one output buffer.
- Safe shutdown: the monitor and all coder threads coordinate on the global stop condition to terminate cleanly without races or dangling resources.
- Resource ownership safety: each dongle has its own mutex and condition variable, ensuring that no thread can observe or mutate a dongle state concurrently.

## Thread synchronization mechanisms

The implementation uses standard POSIX synchronization primitives to ensure that all shared structures remain consistent.

### `pthread_mutex_t`

A mutex protects access to critical shared state, including:

- dongle ownership and release state,
- the scheduler queue and heap structure,
- the global simulation stop flag,
- serialized log output.

This prevents data races when multiple coders concurrently request, release, or inspect the same dongle or shared monitor state.

### `pthread_cond_t`

Condition variables are used to wake threads when a resource becomes available or when the simulation ends. For example:

- a coder waits until its required dongles are free,
- the monitor waits until the simulation state changes or a burnout deadline is reached,
- the scheduler broadcasts state updates when the queue or resource availability changes.

This is the thread-safe communication channel between coders and the monitor: a coder does not spin in a busy loop waiting for a dongle; instead, it blocks efficiently until a condition is signaled.

### Event-style coordination

The project uses condition-variable signaling as a lightweight event mechanism. When a dongle is released or a deadline is reached, the corresponding threads are awakened, and they re-check their shared state under the lock before continuing. This avoids inconsistent reads and ensures that the action sequence remains valid.

### Concrete example

When a coder requests a dongle, it adds an entry to the per-dongle scheduler queue. The scheduler lock is acquired before modifying the heap, then the thread either gets the resource immediately or waits on that dongle's condition variable until the resource becomes available again. Because all queue operations and state transitions are guarded by the same mutex, a race condition between two coders trying to acquire the same dongle is impossible.

Similarly, the monitor thread checks burnout deadlines without interfering with the coders' state transitions because the deadline and compile timestamps are read and updated under the same global protection scheme.

## Resources

### Reference documents

- POSIX Threads programming: `pthread_create`, `pthread_mutex_t`, `pthread_cond_t`, `pthread_cond_wait`, `pthread_cond_signal`
- `gettimeofday()` and timing precision for millisecond timestamps
- Concurrency theory and synchronization basics: mutexes, condition variables, deadlock prevention, starvation, and fairness
- C standard library reference for memory management and string handling

### AI usage

AI tools were used as a support for:

- reviewing synchronization logic and edge cases,
- testing ideas for fair scheduling and deadline handling,
- checking edge conditions such as cooldown timing and burnout detection,
- suggesting ways to improve the clarity and robustness of the implementation.

All generated suggestions were validated manually against the project rules, the expected log format, and the actual behavior of the simulation before being kept in the final version.

## Technical notes

The implementation follows the project constraints by using a custom heap for FIFO and EDF scheduling, a dedicated monitor thread to validate burnout timing, and strict argument validation to reject invalid or unsafe inputs. Memory is managed explicitly, and all created resources are cleaned up before program termination.

## Summary

Codexion is a concurrency challenge centered on resource arbitration, fairness, and timing. The solution requires careful control of a shared environment where each coder must obtain two dongles at the same time, respect deadlines, and avoid deadlock, starvation, and state corruption while producing a reliable log of the simulation.
