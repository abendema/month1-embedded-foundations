#include <stdio.h>
#include "sensor_data.h"

// Implement the function declared in the header file
void print_sensor_data(const sensor_data_t* data) {
    printf("--- Sensor Reading ---\n");
    printf("Sensor ID: %u\n", data->sensor_id);
    printf("Timestamp: %lu\n", data->timestamp);
    printf("Temperature: %.2f C\n", data->temperature);
    printf("Humidity: %.2f %%\n", data->humidity);
    printf("Status: 0x%02X\n", data->status);
}

// Implement the creation function
sensor_data_t create_sensor_data(float temp, float hum, uint8_t id) {
    sensor_data_t new_data;
    new_data.timestamp = 0; // Simple placeholder
    new_data.temperature = temp;
    new_data.humidity = hum;
    new_data.sensor_id = id;
    new_data.status = 0; // No errors
    return new_data;
}

int main() {
    printf("Day 1: Sensor Data Struct Demo\n\n");

    // Create sensor data using the function
    sensor_data_t my_sensor_data = create_sensor_data(23.5, 45.0, 1);

    // Print the data by passing its address (&) to the function
    print_sensor_data(&my_sensor_data);

    printf("\n--- Creating another sensor ---\n");
    // Create another sensor reading
    sensor_data_t another_sensor = create_sensor_data(19.8, 60.5, 2);
    print_sensor_data(&another_sensor);

    return 0;
}
