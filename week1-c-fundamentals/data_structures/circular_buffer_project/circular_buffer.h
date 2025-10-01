// circular_buffer.h
// Header file for circular buffer: struct definitions + function prototypes

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include "../sensor_data_project/sensor_data.h"

// Maximum number of items in the circular buffer
#define BUFFER_SIZE 5

//================================= Struct Definition ==============================//
// Circular buffer structure
typedef struct {
    sensor_data_t buffer[BUFFER_SIZE]; // Array to store sensor readings
    size_t head;     // Index for the next write (enqueue)
    size_t tail;     // Index for the next read (dequeue)
    size_t count;    // Number of items currently in the buffer
    size_t capacity; // Maximum number of items (BUFFER_SIZE)
} circular_buffer_t;

/*
Example of buffer contents:

buffer[0] → [timestamp, temperature, humidity, sensor_id, status]  <-- first reading
buffer[1] → [timestamp, temperature, humidity, sensor_id, status]  <-- second reading
...
*/

//================================= Error Codes ==============================//
typedef enum {
    CB_SUCCESS,    // Operation succeeded
    CB_ERROR_FULL, // Buffer is full, cannot enqueue
    CB_ERROR_EMPTY,// Buffer is empty, cannot dequeue
    CB_ERROR_NULL  // Provided pointer is NULL
} cb_error_t;

//================================= Function Prototypes =======================//
// Initialize the circular buffer
void cb_init(circular_buffer_t* cb);

// Core operations
cb_error_t cb_enqueue(circular_buffer_t* cb, const sensor_data_t* data);
cb_error_t cb_dequeue(circular_buffer_t* cb, sensor_data_t* out_item);
cb_error_t cb_enqueue_force(circular_buffer_t* cb, const sensor_data_t* data);
cb_error_t cb_peek(const circular_buffer_t* cb, sensor_data_t* out_item);


// Status checks
bool cb_is_empty(const circular_buffer_t* cb);
bool cb_is_full(const circular_buffer_t* cb);
size_t cb_count(const circular_buffer_t* cb);

// Utility function to print all current buffer items
void cb_print_all(const circular_buffer_t* cb);


#endif // CIRCULAR_BUFFER_H
