#include <stdio.h>
#include "sensor_data.h"


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
