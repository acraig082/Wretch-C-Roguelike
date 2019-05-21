#include "rogue.h"
#include <stdio.h>
#include <stdlib.h>

/// Code below is credited to: https://www.geeksforgeeks.org/priority-queue-using-linked-list/
//    C code to implement Priority Queue using Linked List


PQNode* PQNode_new(Node* d, double p)
{
    PQNode* temp = (PQNode*)malloc(sizeof(PQNode));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
    return temp;
}

// Return the value at head
Node* peek(PQNode** head)
{
    return (*head)->data;
}

// Removes the element with the
// highest priority form the list
void pop(PQNode** head)
{
    PQNode* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

// Function to push according to priority
void push(PQNode** head, Node* d, double p)
{
    PQNode* start = (*head);

    // Create new Node
    PQNode* temp = PQNode_new(d, p);


    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {

        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
               start->next->priority < p) {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}

// Function to check is list is empty
int isEmpty(PQNode** head)
{
    return (*head) == NULL;
}
