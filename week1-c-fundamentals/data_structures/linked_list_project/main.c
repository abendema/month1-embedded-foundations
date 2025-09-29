#include <stdio.h>
#include "linked_list.h"


int main()
{
    node* list1 = NULL; // First linked list (sensor 1)
    node* list2 = NULL; // Second linked list (sensor 2)
    node* list3 = NULL; // Third linked list (sensor 3)

    printf("----------------------------Sensor 1 readings-----------------------------\n");
    // Case 1: ONLY one node in list1
    sensor_status_t list1_err = add_sensor_reading(&list1, 25.5, 50, 1);     // add 1 reading
    if(list1_err != SENSOR_OK){                                              // check if memory allocation or other error occurred
        printf("Error adding sensor reading: %d\n", list1_err);
    }
    print_all_readings(&list1);                                              // print list1
    clear_all_readings(&list1);                                              // free memory of list1
    printf("--------------------------------------------------------------------------\n\n"); // separator + blank line


    printf("----------------------------Sensor 2 readings-----------------------------\n");
    // Case 2: multiple readings for sensor 2 in list2
    sensor_status_t list2_err;

    // Add first reading and check for error
    list2_err = add_sensor_reading(&list2, 22.5, 50.0, 2); // 1st node
    if(list2_err != SENSOR_OK){
        printf("Error adding sensor reading: %d\n", list2_err);
    }

    // Add second reading and check for error
    list2_err = add_sensor_reading(&list2, 23.0, 55.0, 2); // 2nd node
    if(list2_err != SENSOR_OK){
        printf("Error adding sensor reading: %d\n", list2_err);
    }

    // Add third reading and check for error
    list2_err = add_sensor_reading(&list2, 24.0, 52.0, 2); // 3rd node
    if(list2_err != SENSOR_OK){
        printf("Error adding sensor reading: %d\n", list2_err);
    }
    print_all_readings(&list2);                // print list2

    // delete secific reading and check for error
    list2_err = delete_specific_reading(&list2, 3);
    if(list2_err != SENSOR_OK){
        printf("Error deleting sensor reading: %d\n", list2_err);
    }
    printf("\nList after Deletion: \n");
    print_all_readings(&list2);                            // print list2 after deletion
    clear_all_readings(&list2);                            // free memory of all nodes in list2
    printf("--------------------------------------------------------------------------\n\n");


    printf("----------------------------Sensor 3 readings-----------------------------\n");
    // Add sensor readings/nodes, Print list3, Find specific reading/node in list3.
    sensor_status_t list3_err;

    // Add first reading and check for error
    list3_err = add_sensor_reading(&list3, 20.5, 30.0, 3); // 1st node
    if(list3_err != SENSOR_OK){
        printf("Error adding sensor reading: %d\n", list3_err);
    }

    // Add second reading and check for error
    list3_err = add_sensor_reading(&list3, 19.0, 35.0, 3); // 2nd node
    if(list3_err != SENSOR_OK){
        printf("Error adding sensor reading: %d\n", list3_err);
    }

    print_all_readings(&list3);                // print list3


    printf("\nSpecific reading found:\n");
    list3_err = find_specific_reading(&list3, 5);          // find sepcific reading/node
    if(list3_err != SENSOR_OK){
        printf("Error sensor reading not found: %d\n", list3_err);
    }
    printf("--------------------------------------------------------------------------\n\n");

    return 0;
}
