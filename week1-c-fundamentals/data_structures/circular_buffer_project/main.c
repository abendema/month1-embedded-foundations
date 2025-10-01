#include <stdio.h>
#include "circular_buffer.h"


// Helper function to enqueue a reading to avoid repeating code in main
void add_reading(circular_buffer_t* cb, float temp, float hum, uint8_t id){
    sensor_data_t db = create_sensor_data(temp, hum, id);
    cb_error_t err = cb_enqueue(cb, &db);
    if(err != CB_SUCCESS){
        printf("Error enqueueing data, error code: %d\n", err);
    }
}

// Helper function to force enqueue a reading to avoid repeating code in main
void add_reading_force(circular_buffer_t* cb, float temp, float hum, uint8_t id){
    sensor_data_t db = create_sensor_data(temp, hum, id);
    cb_error_t err = cb_enqueue_force(cb, &db);
    if(err != CB_SUCCESS){
        printf("Error enqueueing data, error code: %d\n", err);
    }
}


int main()
{
    //============================== SENSOR 1 ==============================
    printf("Sensor 1 readings:\n");

    circular_buffer_t cb1;
    cb_init(&cb1); // Initialize the circular buffer
    add_reading(&cb1, 25.5, 40, 1);
    add_reading(&cb1, 27.6, 45, 1);
    add_reading(&cb1, 28.6, 50, 1);
    add_reading(&cb1, 29.6, 55, 1);
    add_reading(&cb1, 30.6, 60, 1);

    // peek tail before overwriting
    sensor_data_t peek_tail;
    cb_error_t err = cb_peek(&cb1, &peek_tail);
    if(err != CB_SUCCESS){
        printf("Error peeking data, error code: %d\n", err);
    }
    printf("\nPeek tail:Temperature: %.2f | Humidity: %.2f%% | Sensor ID: %u | Status: %u | Timestamp: %u\n\n",
           peek_tail.temperature,
           peek_tail.humidity,
           peek_tail.sensor_id,
           peek_tail.status,
           peek_tail.timestamp);

    // sixth reading force enqueue new reading (overwrite oldest)
    add_reading_force(&cb1, 35.7, 65, 1);

    cb_print_all(&cb1);
    printf("\nIs empty? %s\n", cb_is_empty(&cb1) ? "Yes" : "No");
    printf("Is full? %s\n", cb_is_full(&cb1) ? "Yes" : "No");
    printf("Count: %zu\n", cb_count(&cb1));
    printf("------------------------------------------------------------\n");

    //============================== SENSOR 2 ==============================
    printf("Sensor 2 readings:\n\n");

    circular_buffer_t cb2;
    cb_init(&cb2);

    // First reading
    sensor_data_t db22 = create_sensor_data(30.6, 50, 2);
    cb_error_t err2 = cb_enqueue(&cb2, &db22);
    if(err2 != CB_SUCCESS){
        printf("Error enqueueing data, error code: %d\n", err2);
    }

    cb_print_all(&cb2);

    // Dequeue the oldest reading
    sensor_data_t dequeued_data;
    err2 = cb_dequeue(&cb2, &dequeued_data);
    if(err2 != CB_SUCCESS){
        printf("Error dequeueing data, error code: %d\n", err2);
    }

    printf("\nAfter dequeue:\n");
    printf("Is empty? %s\n", cb_is_empty(&cb2) ? "Yes" : "No");

    printf("\nDequeued data:\nTemperature: %.2f | Humidity: %.2f%% | Sensor ID: %u | Status: %u | Timestamp: %u\n",
           dequeued_data.temperature,
           dequeued_data.humidity,
           dequeued_data.sensor_id,
           dequeued_data.status,
           dequeued_data.timestamp);

    printf("------------------------------------------------------------\n");

    return 0;
}
