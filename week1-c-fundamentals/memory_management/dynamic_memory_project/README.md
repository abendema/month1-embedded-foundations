# Dynamic Memory Project

## Description
Professional memory management utilities designed for **embedded systems** where using raw `malloc` and `free` can be risky.
Provides safe wrappers with tracking, leak detection, and bounded resource usage.

## Safety Features
- **Safe Allocation**: `safe_malloc()` checks for allocation failure and records metadata for debugging  
- **Validated Free**: `safe_free()` prevents double-free and invalid pointer errors  
- **Leak Detection**: `report_leaks()` automatically reports unfreed memory at shutdown
- **Memory Tracking**: `get_total_allocated()` and `get_allocation_count()` provide real-time statistics on total allocations and bytes used
- **Bounded Resources**: Fixed metadata storage (`MAX_ALLOCATIONS`) for embedded constraints


## Dependencies
- Requires `sensor_data.h` and `sensor_data.c` from the `sensor_data_project`
- Include these files in your project to compile and run memory_tools

## Notes
- Tested with GCC / standard C compiler
- Designed for embedded or memory-constrained systems
- `record_allocations` and `enter_safe_mode` are private and cannot be called outside `memory_tools.c`
