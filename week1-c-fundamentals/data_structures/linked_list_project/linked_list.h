// Header for linked list: struct definitions + function prototypes

// Header Guards
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>

// Add error handling
typedef enum{
    SENSOR_OK,              // 0
    SENSOR_ERROR_MEMORY,    // 1
    SENSOR_ERROR_NOT_FOUND  // 2

}sensor_status_t;

/*
Node structure: stores one sensor reading
next = pointer to next node

Visualization:

    Data              Pointer
[| timestamp   | next → next node ]
 | temperature |
 | humidity    |
 | sensor_id   |
 | status      |
*/
typedef struct node{
    uint32_t timestamp; // 4 Bytes (2^32)
    float temperature;
    float humidity;
    uint8_t sensor_id;  // 1 Byte (0-255)
    uint8_t status;     // bitfield for error states
    struct node* next;  // pointer to next node
} node;


// Functions prototypes
sensor_status_t add_sensor_reading(node** head, float temp, float hum, uint8_t id); // add new sensor data
sensor_status_t find_specific_reading(node** head, uint32_t time);
sensor_status_t delete_specific_reading(node** head, uint32_t time);
void print_all_readings(node** head);  // print all nodes in list
void clear_all_readings(node** head);  // free all memory of list

#endif // LINKED_LIST_H
