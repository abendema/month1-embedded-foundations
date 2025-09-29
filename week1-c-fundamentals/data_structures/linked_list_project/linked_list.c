#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// Main Objective: store multiple sensor readings in a linked list


// Static counter simulating timestamps since we don’t have a real hardware clock yet
// Each new node gets an incremented value, ensuring unique, increasing "timestamps"
static uint32_t timestamp_counter = 0;

//================================================================//
/*
// OLD single-list version (uses global head)
// Only works for one list because head is global
node* head = NULL;

void add_sensor_reading(float temp, float hum, uint8_t id){
    node* new_node = malloc(sizeof(node));
    node* current; // traverse nodes

    new_node->timestamp = 0;
    new_node->temperature = temp;
    new_node->humidity = hum;
    new_node->sensor_id = id;
    new_node->status = 0;
    new_node->next = NULL; // very important

    if(head == NULL){ // first node
        head = new_node;
    }else{ // more nodes
        current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_node;
    }
}
*/
//================================================================//
// NEW version: supports multiple lists
// Pass head pointer by reference so main can have many lists
/*
node* list1 = NULL;
node* list2 = NULL;
add_sensor_reading(&list1, 22.5, 50.0, 1);
add_sensor_reading(&list2, 23.0, 55.0, 2);
*/
sensor_status_t add_sensor_reading(node** head, float temp, float hum, uint8_t id){
    node* new_node = malloc(sizeof(node)); // dynamic memory allocation in heap
    node* current; // temporary pointer to traverse the list

    if(new_node == NULL){
        return SENSOR_ERROR_MEMORY; // memory allocation failed
    }

    //Fill node with data
    new_node->timestamp = ++timestamp_counter;
    new_node->temperature = temp;
    new_node->humidity = hum;
    new_node->sensor_id = id;
    new_node->status = 0;
    new_node->next = NULL; // last node must point to NULL

    //Link the nodes into linked list.
    if(*head == NULL){ // if list is empty
        *head = new_node; // new node becomes first node
    }else{ // list already has nodes
        current = *head; // start from first node
        while(current->next != NULL){ // loop till last node
            current = current->next;
        }
        current->next = new_node; // add new node at end
    }

    return SENSOR_OK; //success
}
//================================================================//
void print_all_readings(node** head){
    node* current = *head; // temporary pointer to traverse the list
    if(*head == NULL){
        printf("Linked List is empty!\n");
        return;  // stop function, nothing to print
    }else{
        while(current != NULL){ // go through all nodes
            printf("Timestamp=%u | Temperature=%.2f | Humidity=%.2f%% | SensorID=%u | Status=%u\n",
                   current->timestamp,
                   current->temperature,
                   current->humidity,
                   current->sensor_id,
                   current->status);

            current = current->next; // move to next node
        }
    }
}
//================================================================//
// Delete a node from the linked list with a given timestamp value
sensor_status_t delete_specific_reading(node** head, uint32_t time){
    // If the list is empty
    if (*head == NULL){
        return SENSOR_ERROR_NOT_FOUND;
    }

    node* current = *head; // temporary pointer to traverse the list
    node* prev = NULL; // temporary pointer to keep track of the node before 'current'

    // Case 1: the node to delete is the first node (head)
    if(current->timestamp == time){
        *head = current->next; // move head to the next node

    }else{
        // Case 2: search for the node to delete (not the first one)
        while((current != NULL)&&(current->timestamp != time)){
            prev = current; // move prev one step forward
            current = current->next; // move current one step forward
        }

        // If we reached the end, timestamp not found -> return
        if (current == NULL) return SENSOR_ERROR_NOT_FOUND;

        // disconnect the node to be deleted from the list by linking prev->next to current->next
        prev->next = current->next;
    }

    // The node is no longer part of the list, but it still exists in memory
    // Use free to clean up the memory to prevent leaks
    free(current);

    return SENSOR_OK; //success
}
//================================================================//
// Find and print a specific sensor reading by its timestamp
sensor_status_t find_specific_reading(node** head, uint32_t time){
    // If the list is empty, nothing to search
    if (*head == NULL){
        return SENSOR_ERROR_NOT_FOUND;
    }
    node* current = *head; // temporary pointer to traverse the list

    // Traverse the list until we find the node with matching timestamp
    while((current != NULL)&&(current->timestamp != time)){
        current = current->next; // move current to the next node
    }

    // If we reached the end of the list, the timestamp was not found
    if(current == NULL){
        return SENSOR_ERROR_NOT_FOUND;
    }

    // Print all details of the found node
    printf("Timestamp=%u | Temperature=%.2f | Humidity=%.2f%% | SensorID=%u | Status=%u\n",
                   current->timestamp,
                   current->temperature,
                   current->humidity,
                   current->sensor_id,
                   current->status);

    return SENSOR_OK;
}
//================================================================//
// free all nodes in a list
void clear_all_readings(node** head){
    node* save_next = NULL; // to remember next node before freeing
    while(*head != NULL){ // while list not empty
        save_next = (*head)->next; // save next node before freeing
        free(*head);               // free current node
        *head = save_next;         // move head to next node
    }
}
