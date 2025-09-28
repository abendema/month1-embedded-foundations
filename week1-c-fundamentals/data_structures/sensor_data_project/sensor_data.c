// sensor_data.c - IMPLEMENTATION file (the actual code)

#include <stdio.h>        // For printf() function
#include "sensor_data.h"  // Our own header file

// Function to print sensor data to the screen
void print_sensor_data(const sensor_data_t* data) {
    // 'const' means we won't modify the data
    // '*' means we're using a POINTER to the data (faster than copying)

    printf("=== Sensor Reading ===\n");
    printf("Sensor ID: %u\n", data->sensor_id);       // '->' accesses struct through pointer
    printf("Timestamp: %lu\n", data->timestamp);      // %lu for unsigned long (uint32_t)
    printf("Temperature: %.2f C\n", data->temperature); // %.2f = float with 2 decimal places
    printf("Humidity: %.2f %%\n", data->humidity);      // %% prints a real %
    printf("Status: 0x%02X\n", data->status);         // %02X = hex with 2 digits (padded with 0)
    printf("======================\n");
}

// Function to create and initialize a new sensor data structure
sensor_data_t create_sensor_data(float temp, float hum, uint8_t id) {
    sensor_data_t new_data;   // Create a new struct variable on the stack

    // Initialize each field of the struct
    new_data.timestamp = 0;   // Set to 0 for now (we’ll add real time later)
    new_data.temperature = temp;
    new_data.humidity = hum;
    new_data.sensor_id = id;
    new_data.status = 0;      // 0 means no errors

    return new_data;          // Return the complete struct (copied by value)
}
