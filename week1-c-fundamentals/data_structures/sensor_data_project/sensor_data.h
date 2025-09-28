// sensor_data.h


#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <stdint.h>

typedef struct {
    uint32_t timestamp;
    float temperature;
    float humidity;
    uint8_t sensor_id;
    uint8_t status;  // bitfield for error states
} sensor_data_t;

// Function prototypes
void print_sensor_data(const sensor_data_t* data);
sensor_data_t create_sensor_data(float temp, float hum, uint8_t id);

#endif
