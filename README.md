*This project has been created as part of the 42 curriculum by airandri.*

# Codexion

## Description

Codexion is a C concurrency simulation in which each coder is represented by a
POSIX thread and competes for two shared USB dongles. The project implements
FIFO and EDF arbitration, dongle cooldowns, burnout detection, and serialized
logging.

## Instructions

Compile with:

```bash
make
```

Run with:

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

The scheduler must be `fifo` or `edf`.

## Resources

- POSIX threads documentation (`pthread_create`, mutexes and condition variables).
- `gettimeofday()` documentation for millisecond timestamps.
- 42 Codexion subject and peer-evaluation requirements.

AI was used to review concurrency logic, identify synchronization issues, and
suggest corrections. The final implementation was reviewed and tested manually.

## Blocking cases handled

- Deadlock prevention by using one scheduler mutex for shared dongle/request state.
- FIFO request ordering.
- EDF ordering with coder-id tie breaking.
- Dongle cooldown handling.
- Burnout detection by a dedicated monitor thread.
- Serialized output through a dedicated logging mutex.
- Broadcast wake-up when dongles become available or the simulation stops.
- Cleanup of dynamically allocated requests and synchronization primitives.

## Thread synchronization mechanisms

`pthread_mutex_t` protects shared scheduler state and serialized output.
`pthread_cond_t` is used to wake coders when dongles become available and to
wake the monitor when the simulation state changes. The scheduler state is
protected by `gle_lock`, preventing races while requests and dongle ownership
are updated.
