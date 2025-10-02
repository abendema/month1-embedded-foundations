// memory_tools.h
//===========================
// Header for embedded-safe dynamic memory management
// Contains error codes, and function prototypes
// for safe malloc/free, leak detection, and memory tracking.
//===========================

#ifndef MEMORY_TOOLS_H
#define MEMORY_TOOLS_H

#include "../../data_structures/sensor_data_project/sensor_data.h"
#include <stdint.h>   // for uint32_t
#include <stddef.h>   // for size_t

//================================= Error Codes ==============================//
typedef enum {
    OP_OK,            // operation succeeded
    ERROR_NULL,       // malloc returned NULL or pointer is NULL
    ERROR_INVALID,    // pointer not found in tracking array during free
    ERROR_FULL        // allocation metadata array is full
} error_t;

//============================ Function Prototypes =================================

// Safe allocation: wraps malloc and tracks allocation metadata
void* safe_malloc(size_t size, const char* allocation_name);

// Safe free: frees memory and clears metadata
// Returns OP_OK on success, ERROR_NULL if ptr is NULL, ERROR_INVALID if ptr not tracked
error_t safe_free(void* ptr);

// Reports all memory leaks (allocations that were never freed)
void report_leaks(void);

// Returns total bytes currently allocated
size_t get_total_allocated(void);

// Returns the number of active allocations
size_t get_allocation_count(void);


#endif // MEMORY_TOOLS_H
