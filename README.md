# Lift Simulation System

A C-based elevator simulation system with support for both single and multiple lift operations. The project demonstrates intelligent lift allocation algorithms and path optimization.

## Table of Contents
- [Overview](#overview)
- [Project Structure](#project-structure)
- [Features](#features)
- [Compilation and Execution](#compilation-and-execution)
- [Usage](#usage)
- [Architecture](#architecture)
- [Algorithms](#algorithms)

## Overview

This project implements a lift (elevator) simulation with two operational modes:
1. **Single Lift Mode** - Simulates a single elevator system
2. **Multi Lift Mode** - Manages multiple elevators with smart allocation

The system includes intelligent features like:
- Smart lift allocation (nearest lift assignment)
- Path optimization (sorting destinations for efficient travel)
- Duplicate destination removal

## Project Structure

```
lift/
├── single_lift_main.c      # Single lift simulation entry point
├── multi_lift_main.c       # Multi lift simulation entry point
├── lift_sub_functions.c    # Shared utility functions and algorithms
├── single_lift_main        # Compiled executable (single lift)
└── multi_lift_main         # Compiled executable (multi lift)
```

## Features

### Single Lift Mode
- Single elevator management
- User input for number of passengers, current floor, and destinations
- Door open/close status display
- Ordinal floor numbering (Ground, 1st, 2nd, 3rd, etc.)
- Real-time lift position updates

### Multi Lift Mode
- Multiple elevator management (3 lifts: A, B, C)
- Smart lift allocation algorithm
- Automatic selection of nearest available lift
- Console output showing lift movement
- Real-time display of:
  - Lift movement (UP/DOWN)
  - Floor transitions
  - Door operations (Opening/Open/Closing/Closed)

### Shared Sub-Functions
- `smart_lift_allocation()` - Allocates the nearest lift to user
- `smart_managing()` - Optimizes and sorts destination paths
- `clear_lines()` - Console animation support
- `endth()` - Returns ordinal suffix for floor numbers
- `lift_name()` - Returns lift identifier (A, B, C, D)

## Compilation and Execution

### Prerequisites
- GCC compiler
- Linux/Unix system (uses `sleep()` function)
- Terminal with support for ANSI escape sequences

### Compilation

```bash
# Compile Single Lift
gcc single_lift_main.c -o single_lift_main

# Compile Multi Lift
gcc multi_lift_main.c -o multi_lift_main
```

### Execution

```bash
# Run Single Lift Simulation
./single_lift_main

# Run Multi Lift Simulation
./multi_lift_main
```

## Usage

### Input Format

1. **Number of people** (1-10): Enter the number of passengers
2. **Current floor**: Enter the floor where passengers are waiting
3. **Destination floors**: Enter destination floors for each passenger

### Example Session (Multi Lift)

```
Enter No of people : 2

Enter the current Floor : 0

Enter destination floor's : 3 5

    LIFT SMART PATH :  3  5

    Lift Allocated  -> A

    [Lift moves from floor 0 to 3]
    [Doors status at floor 3]
    [Lift moves from floor 3 to 5]
    [Doors status at floor 5]
```

## Architecture

### Data Structures

```c
typedef struct {
    int id;              // Lift identifier
    int status;          // FREE, BUZY, WAIT_LOW, WAIT_HIGH
    int current_pos;     // Current floor position
} LIFT;
```

### Constants

| Constant | Value | Description |
|----------|-------|-------------|
| `TOTAL_LIFTs` | 3 | Number of lifts in multi-lift mode |
| `FREE` | 1/0 | Lift availability status |
| `BUZY` | 0 | Lift busy status |
| `WAIT_LOW` | 2 | Short delay (milliseconds/seconds) |
| `WAIT_HIGH` | 3/4 | Long delay for door operations |
| `MOVING_UP` | 1 | Lift moving upward |
| `MOVING_DOWN` | 0 | Lift moving downward |
| `MOVING_NONE` | -1 | Lift stationary |

## Algorithms

### Smart Lift Allocation

The system uses a proximity-based algorithm to allocate the nearest lift:

```c
int smart_lift_allocation(int* lift_cur_pos, int TOTAL_LIFTs, int usr_current_pos) {
    int allocated = 0;
    for(int i = 0; i < TOTAL_LIFTs; i++) {
        if(abs(usr_current_pos - lift_cur_pos[i]) < 
           abs(lift_cur_pos[allocated] - usr_current_pos))
            allocated = i;
    }
    return allocated;
}
```

**Time Complexity**: O(n) where n is the number of lifts

### Smart Path Management

Optimizes destination routes by:
1. Removing duplicate destinations
2. Sorting destinations by proximity to current position

```c
int smart_managing(int *user_destination_paths, int lift_current_position, 
                   int total_destination_paths) {
    // Removes duplicates and optimizes path
    // Sorts destinations by distance from current position
}
```

**Time Complexity**: O(m²) where m is the number of destinations

## Floor Numbering

The system uses proper ordinal suffixes:
- 0 → Ground (G)
- 1 → 1st
- 2 → 2nd
- 3 → 3rd
- 4+ → 4th, 5th, etc.

## Dependencies

Standard C libraries:
- `<stdio.h>` - Input/output operations
- `<unistd.h>` - POSIX API (sleep)
- `<stdlib.h>` - Standard library (abs function)

## Future Enhancements

- Add request queuing system
- Implement elevator scheduling algorithms (SCAN, C-SCAN)
- Add passenger weight consideration
- Implement emergency stop functionality
- Add lift maintenance scheduling
- Support for more floors and lifts
- GUI-based interface option

## License

This project is part of C programming practice and learning exercises.

## Author

Created as a C programming exercise demonstrating:
- Data structures
- Algorithms
- System programming
- User interface design

