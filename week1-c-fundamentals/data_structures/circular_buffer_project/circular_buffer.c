// Functions implementation

#include "circular_buffer.h"
#include <stdio.h>

//================================ cb_init =================================
// Initialize the circular buffer
void cb_init(circular_buffer_t* cb){
    cb->capacity = BUFFER_SIZE;  // Maximum number of items buffer can hold
    cb->count = 0;               // Current number of items
    cb->head = 0;                // Next write position
    cb->tail = 0;                // Next read position
}

//================================ cb_enqueue ==============================
// Add a new sensor reading to the buffer
// 'data' is marked const to prevent modification inside this function
cb_error_t cb_enqueue(circular_buffer_t* cb, const sensor_data_t* data){

    if((cb == NULL) || (data == NULL)) return CB_ERROR_NULL; // Validate pointers

    if(cb_is_full(cb)) return CB_ERROR_FULL; // Prevent writing if buffer is full

    cb->buffer[cb->head] = *data; // Copy new sensor reading to current head position

    cb->head = (cb->head + 1) % cb->capacity; // Move head forward, wrap to 0 if end reached
    cb->count++; // Increase count of items in the buffer

    return CB_SUCCESS; // Operation successful
}
//============================ cb_enqueue_force ============================
// Force enqueue: overwrite the oldest data if buffer is full
cb_error_t cb_enqueue_force(circular_buffer_t* cb, const sensor_data_t* data){

    if((cb == NULL) || (data == NULL)) return CB_ERROR_NULL; // Validate pointers

    if(cb_is_full(cb)){
        /*
        When buffer is full, moving tail discards the oldest item.
        This keeps the logical order consistent: tail always points
        to the true oldest element after overwrite.
        */
        cb->tail = (cb->tail + 1) % cb->capacity;
        // Count stays the same, because we overwrite instead of growing
    } else {
        cb->count++; // Only increase count if it wasn't full
    }

    cb->buffer[cb->head] = *data; // Copy new sensor reading to head

    cb->head = (cb->head + 1) % cb->capacity; // Move head forward, wrap if needed

    return CB_SUCCESS;
}
//================================ cb_dequeue ==============================
// Remove the oldest sensor reading from the buffer
// The removed item is copied into 'out_item'
cb_error_t cb_dequeue(circular_buffer_t* cb, sensor_data_t* out_item){

    if((cb == NULL) || (out_item == NULL)) return CB_ERROR_NULL; // Validate pointers

    if(cb_is_empty(cb)) return CB_ERROR_EMPTY; // Prevent reading if buffer is empty

    *out_item = cb->buffer[cb->tail]; // Copy oldest item to caller's variable

    cb->tail = (cb->tail + 1) % cb->capacity; // Move tail forward, wrap to 0 if end reached
    cb->count--; // Decrease count of items in the buffer

    return CB_SUCCESS; // Operation successful
}
//=============================== cb_peek =============================
// Look at oldest item without dequeuing
cb_error_t cb_peek(const circular_buffer_t* cb, sensor_data_t* out_item){

    if((cb == NULL) || (out_item == NULL)) return CB_ERROR_NULL; // Validate pointers
    if (cb_is_empty(cb)) return CB_ERROR_EMPTY; // Prevent reading when empty

    *out_item = cb->buffer[cb->tail]; // Copy oldest item to caller

    return CB_SUCCESS;
}
//=============================== cb_is_empty =============================
// Check if the buffer is empty
bool cb_is_empty(const circular_buffer_t* cb){
    return cb->count == 0; // True if empty, false otherwise
}

//=============================== cb_is_full ==============================
// Check if the buffer is full
bool cb_is_full(const circular_buffer_t* cb){
    return cb->count == cb->capacity; // True if full, false otherwise
}

//================================ cb_count ================================
// Return the current number of items in the buffer
size_t cb_count(const circular_buffer_t* cb){
    return cb->count;
}

//============================== cb_print_all =============================
// Print all items currently in the buffer without modifying it
void cb_print_all(const circular_buffer_t* cb){

    if((cb == NULL) || (cb_is_empty(cb))){
        printf("Circular buffer is empty!\n");
        return;
    }

    size_t index = cb->tail; // Start from the oldest item (tail)
    for(size_t i = 0; i < cb->count; i++){ // Loop from tail (oldest) through all items currently in the buffer
        printf("Index %zu = ", index);
        printf("Temperature: %.2f | Humidity: %.2f%% | Sensor ID: %u | Status: %u | Timestamp: %u\n",
               cb->buffer[index].temperature,
               cb->buffer[index].humidity,
               cb->buffer[index].sensor_id,
               cb->buffer[index].status,
               cb->buffer[index].timestamp);

        index = (index + 1) % cb->capacity; // Move to next item, wrap if needed
    }
}
