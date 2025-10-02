#include "memory_tools.h"
#include <stdio.h>

int main()
{
    // ===========================
    // Allocate memory for a sensor_data_t struct
    // safe_malloc tracks this allocation and gives a unique name for debugging
    // ===========================
    sensor_data_t* p = safe_malloc(sizeof(sensor_data_t), "Sensor Readings");

    // ===========================
    // Initialize the struct with test values
    // create_sensor_data returns a sensor_data_t, which we assign to the allocated memory
    // ===========================
    *p = create_sensor_data(23.5, 45.0, 1);

    // ===========================
    // Print the sensor data to verify values
    // ===========================
    print_sensor_data(p);

    // ===========================
    // Free the memory safely using safe_free
    // Checks for errors in case pointer is NULL or not tracked
    // ===========================
    error_t err = safe_free(p);
    if(err != OP_OK){
        printf("Error freeing memory, error code: %d\n", err);
    }

    // ===========================
    // Report any memory leaks
    // Should show zero leaks if safe_free worked correctly
    // ===========================
    report_leaks();

    return 0;
}
