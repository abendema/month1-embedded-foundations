// memory_tools.c
//===========================
// Embedded-safe dynamic memory management
// This file provides safe malloc/free wrappers with tracking, leak detection,
// and total memory statistics. Useful for embedded systems where raw malloc
// can be risky.
//===========================

#include "memory_tools.h"
#include <stdio.h>
#include <stdlib.h> // for malloc/free

#define MAX_ALLOCATIONS 50  // maximum number of memory blocks to track


//============================ allocation_t struct ================================
/*
Holds info about a single memory allocation.
Used for tracking, debugging, and leak detection.

NOTE: The struct is defined in the .c file to keep it private,
It is not exposed in the header. This prevents external code
from misusing allocation metadata.
*/
typedef struct {
    void* ptr;             // pointer to the allocated memory block
    size_t size;           // size of the allocated block in bytes
    const char* name;      // descriptive name for debugging (e.g., "sensor_readings")
    uint32_t timestamp;    // unique timestamp for order of allocation
} allocation_t;

//========================================
// Static variables (private to this file)
//========================================
static allocation_t allocations[MAX_ALLOCATIONS];   // stores metadata for each allocation
static int time_counter = 0;                        // Static counter simulating timestamps for each allocation since we don’t have a real hardware clock yet
static size_t allocation_count = 0;                 // number of active allocations
static size_t total_allocated = 0;                  // total bytes currently allocated

//========================= record_allocations =================================
/*
Record allocation metadata:
- Private function: only used inside this .c file
- Finds the first free slot in allocations[].
- Stores pointer, size, name, timestamp.
- Updates allocation count.
- Returns ERROR_FULL if all slots are used.
*/
static error_t record_allocations(void* p, const char* allocation_name, size_t size) {
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (allocations[i].ptr == NULL) { // empty slot found
            allocations[i].ptr = p;
            allocations[i].name = allocation_name;
            allocations[i].size = size;
            allocations[i].timestamp = time_counter++;
            allocation_count++;
            return OP_OK;
        }
    }
    return ERROR_FULL; // no free slots available
}

//========================= enter_safe_mode =================================
/*
Handle memory allocation failure:
- Private function: only used inside this .c file
- Prints an error message for now.
- Can be extended to trigger hardware-safe fallback mode.
*/
static error_t enter_safe_mode(void) {
    printf("Error: Memory allocation failed\n");
    return ERROR_NULL;
}

//========================= safe_malloc =================================
/*
Safe Allocation:
- Wraps malloc with tracking and error handling.
- If malloc fails, triggers "safe mode" instead of crashing.
- Records metadata for debugging/leak detection: pointer, size, name, timestamp.
- Updates running total of allocated bytes.
*/
void* safe_malloc(size_t size, const char* allocation_name) {
    void* p = malloc(size); // allocate memory
    error_t err;

    if (p == NULL) {
        // If allocation failed, handle gracefully
        err = enter_safe_mode();
        if (err != OP_OK) {
            return NULL; // cannot allocate memory
        }
    }

    // Record allocation metadata
    err = record_allocations(p, allocation_name, size);
    if (err != OP_OK) {
        printf("Warning: allocation metadata full, memory allocated but not tracked\n");
    } else {
        total_allocated += size; // keep track of total memory currently in use
    }

    return p;
}

//=========================== safe_free =====================================
/*
Safe Free:
- Frees memory safely and updates metadata.
- Subtracts memory size from total.
- Returns OP_OK if success, ERROR_NULL if pointer is NULL,
  ERROR_INVALID if pointer is not tracked.
*/
error_t safe_free(void* p) {
    if (p == NULL) {
        return ERROR_NULL;
    }

    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (allocations[i].ptr == p) {
            total_allocated -= allocations[i].size; // update total memory

            // clear metadata
            allocations[i].ptr = NULL;
            allocations[i].name = NULL;
            allocations[i].size = 0;
            allocations[i].timestamp = 0;

            allocation_count--; // decrement active allocation count
            free(p);            // release memory
            return OP_OK;
        }
    }

    return ERROR_INVALID; // pointer not found in tracking array
}

//=========================== report_leaks ==================================
/*
Report all active allocations (memory leaks):
- Loops through allocations[] and prints any pointers not freed.
- Shows pointer address, name, size, timestamp.
- Prints total leaks and total allocated bytes.
*/
void report_leaks(void) {
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (allocations[i].ptr != NULL) { // still allocated
            printf("Location: %p\nName: %s\nSize: %zu\nTimestamp: %u\n",
                   allocations[i].ptr, allocations[i].name,
                   allocations[i].size, allocations[i].timestamp);
        }
    }
    printf("Total leaks: %zu, Total bytes: %zu\n", get_allocation_count(), get_total_allocated());
}

//=========================== get_total_allocated ===========================
/*
Returns total bytes currently allocated (running total)
*/
size_t get_total_allocated(void) {
    return total_allocated;
}

//=========================== get_allocation_count ===========================
/*
Returns number of active allocations (running count)
*/
size_t get_allocation_count(void) {
    return allocation_count;
}
