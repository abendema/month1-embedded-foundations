// Header for linked list: struct definitions + function prototypes

// Header Guards
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>

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
    uint8_t status;     // 1 Byte (0-255)
    struct node* next;  // pointer to next node
} node;

// Functions prototypes
void add_sensor_reading(node** head, float temp, float hum, uint8_t id); // add new sensor data
void find_specific_reading(node** head, uint32_t time);
void delete_specific_reading(node** head, uint32_t time);
void print_all_readings(node** head);  // print all nodes in list
void clear_all_readings(node** head);  // free all memory of list

#endif // LINKED_LIST_H
