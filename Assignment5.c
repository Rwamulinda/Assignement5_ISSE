/*
 * clist.c
 * 
 * Linked list implementation for ISSE Assignment 5
 *
 * Author: <your name here>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "clist.h"

#define DEBUG

struct _cl_node {
    CListElementType element;
    struct _cl_node *next;
};

struct _clist {
    struct _cl_node *head;
    int length;
};

// Create (malloc) a new _cl_node and populate it with the supplied values
static struct _cl_node* _CL_new_node(CListElementType element, struct _cl_node *next) {
    struct _cl_node* new_node = (struct _cl_node*) malloc(sizeof(struct _cl_node));
    assert(new_node);

    new_node->element = element;
    new_node->next = next;

    return new_node;
}

// Documented in .h file
CList CL_new() {
    CList list = (CList) malloc(sizeof(struct _clist));
    assert(list);

    list->head = NULL;
    list->length = 0;

    return list;
}

// Documented in .h file
// Documented in .h file
void CL_free(CList list) {
    assert(list);
    
    struct _cl_node *current = list->head;
    struct _cl_node *next_node;

    // Free all nodes
    while (current != NULL) {
        next_node = current->next; // Store next node
        // Do not free current->element if it is not dynamically allocated
        free(current);
        current = next_node; // Move to the next node
    }

    free(list); // Free the list structure
}


// Documented in .h file
int CL_length(CList list) {
    assert(list);
#ifdef DEBUG
    int len = 0;
    for (struct _cl_node *node = list->head; node != NULL; node = node->next) {
        len++;
    }
    assert(len == list->length); // Ensure length is accurate
#endif // DEBUG

    return list->length;
}

// Documented in .h file
void CL_print(CList list) {
    assert(list);

    int num = 0;
    for (struct _cl_node *node = list->head; node != NULL; node = node->next) {
        printf("  [%d]: %s\n", num++, node->element);
    }
}

// Documented in .h file
void CL_push(CList list, CListElementType element) {
    assert(list);
    list->head = _CL_new_node(element, list->head);
    list->length++;
}

// Documented in .h file
CListElementType CL_pop(CList list) {
    assert(list);

    if (list->head == NULL) return INVALID_RETURN; // Check if empty

    struct _cl_node *popped_node = list->head;
    CListElementType ret = popped_node->element;

    list->head = popped_node->next;
    free(popped_node);
    list->length--;

    return ret;
}

// Documented in .h file
void CL_append(CList list, CListElementType element) {
    assert(list);

    struct _cl_node *new_node = _CL_new_node(element, NULL);
    if (list->head == NULL) {
        list->head = new_node; // List was empty
    } else {
        struct _cl_node *current = list->head;
        while (current->next != NULL) {
            current = current->next; // Traverse to the end
        }
        current->next = new_node; // Append at the end
    }
    list->length++;
}

// Documented in .h file
// Function to get the nth element of a circular linked list
CListElementType CL_nth(CList list, int pos) {
    assert(list);  // Ensure the list is not NULL

    // Check if the list is empty
    if (list->head == NULL) {
        return NULL;  // List is empty
    }

    // Adjust negative position for circular indexing
    if (pos < 0) {
        pos = list->length + pos; // Convert negative index to positive
    }

    // Check for out of bounds position
    if (pos < 0 || pos >= list->length) {
        return NULL;  // Out of bounds
    }

    // Declare the current pointer to traverse the list
    struct _cl_node* current = list->head; // Corrected pointer declaration

    // Traverse the list to the specified position
    for (int i = 0; i < pos; i++) {
        current = current->next; // Move to the next node
    }

    // Return the data at the current node
    return current->element;  // Return the element at the current node
}

// Documented in .h file
bool CL_insert(CList list, CListElementType element, int pos) {
    assert(list);
    if (pos < 0 || pos > list->length) return false; // Invalid position

    if (pos == 0) {
        CL_push(list, element); // Insert at head
    } else {
        struct _cl_node *current = list->head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next; // Traverse to the insertion point
        }
        current->next = _CL_new_node(element, current->next); // Insert node
    }

    list->length++;
    return true;
}

// Documented in .h file
CListElementType CL_remove(CList list, int pos) {
    assert(list);
    if (pos < 0 || pos >= list->length) return INVALID_RETURN; // Invalid position

    struct _cl_node *current = list->head;
    CListElementType ret;

    if (pos == 0) {
        return CL_pop(list); // Use pop to remove the head
    } else {
        for (int i = 0; i < pos - 1; i++) {
            current = current->next; // Traverse to the node before the one to remove
        }
        struct _cl_node *to_remove = current->next; // Node to be removed
        ret = to_remove->element;
        current->next = to_remove->next; // Bypass the node
        free(to_remove);
    }

    list->length--;
    return ret;
}

// Documented in .h file
CList CL_copy(CList src_list) {
    assert(src_list);
  
    CList new_list = CL_new();
    for (struct _cl_node *current = src_list->head; current != NULL; current = current->next) {
        CL_append(new_list, current->element); // Append elements to new list
    }
  
    return new_list;
}

// Documented in .h file
int CL_insert_sorted(CList list, CListElementType element) {
    assert(list);
  
    if (list->head == NULL || strcmp(element, list->head->element) < 0) {
        CL_push(list, element); // Insert at head if list is empty or element is smaller
        return 1; // Inserted at the head
    }
  
    struct _cl_node *current = list->head;
    int pos = 1;

    while (current->next != NULL && strcmp(current->next->element, element) < 0) {
        current = current->next; // Traverse to find the correct position
        pos++;
    }

    current->next = _CL_new_node(element, current->next); // Insert node
    list->length++;
    return pos; // Return the position where it was inserted
}

// Documented in .h file
void CL_join(CList list1, CList list2) {
    assert(list1);
    assert(list2);

    if (list2->head == NULL) return; // If list2 is empty, do nothing

    if (list1->head == NULL) {
        list1->head = list2->head; // If list1 is empty, point to list2's head
    } else {
        struct _cl_node *current = list1->head;
        while (current->next != NULL) {
            current = current->next; // Traverse to the end of list1
        }
        current->next = list2->head; // Join list2 to the end of list1
    }

    list1->length += list2->length; // Update length
}

// Documented in .h file
void CL_reverse(CList list) {
    assert(list);

    struct _cl_node *prev = NULL;
    struct _cl_node *current = list->head;
    struct _cl_node *next = NULL;

    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse the link
        prev = current; // Move prev and current forward
        current = next;
    }
    list->head = prev; // Update head to new first node
}

// Documented in .h file
void CL_foreach(CList list, CL_foreach_callback callback, void *cb_data) {
    assert(list);
    assert(callback);

    struct _cl_node *node = list->head;
    for (int pos = 0; node != NULL; pos++) {
        callback(pos, node->element, cb_data); // Call the callback with the current node
        node = node->next; // Move to the next node
    }
}
