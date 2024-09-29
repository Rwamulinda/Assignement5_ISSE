/*
 * clist.c
 * 
 * Linked list implementation for ISSE Assignment 5
 *
 * Author: <Pauline uwase>
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



/*
 * Create (malloc) a new _cl_node and populate it with the supplied
 * values
 *
 * Parameters:
 *   element, next  the values for the node to be created
 * 
 * Returns: The newly-malloc'd node, or NULL in case of error
 */
static struct _cl_node*
_CL_new_node(CListElementType element, struct _cl_node *next)
{
  struct _cl_node* new = (struct _cl_node*) malloc(sizeof(struct _cl_node));

  assert(new);

  new->element = element;
  new->next = next;

  return new;
}



// Documented in .h file
CList CL_new()
{
  CList list = (CList) malloc(sizeof(struct _clist));
  assert(list);

  list->head = NULL;
  list->length = 0;

  return list;
}



// Documented in .h file
void CL_free(CList list)
{

assert(list);

  struct _cl_node *current = list->head;
  struct _cl_node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  free(list);
  //
  // TODO: Add your code here
  //
}



// Documented in .h file
int CL_length(CList list)
{
  assert(list);
#ifdef DEBUG
  // In production code, we simply return the stored value for
  // length. However, as a defensive programming method to prevent
  // bugs in our code, in DEBUG mode we walk the list and ensure the
  // number of elements on the list is equal to the stored length.

  int len = 0;
  for (struct _cl_node *node = list->head; node != NULL; node = node->next)
    len++;

  assert(len == list->length);
#endif // DEBUG

  return list->length;
}



// Documented in .h file
void CL_print(CList list)
{
  assert(list);

  int num = 0;
  for (struct _cl_node *node = list->head; node != NULL; node = node->next)
    printf("  [%d]: %s\n", num++, node->element);
}



// Documented in .h file
void CL_push(CList list, CListElementType element)
{
  assert(list);
  list->head = _CL_new_node(element, list->head);
  list->length++;
}



// Documented in .h file
CListElementType CL_pop(CList list)
{
  assert(list);

  struct _cl_node *popped_node = list->head;

  if (popped_node == NULL)
    return INVALID_RETURN;

  CListElementType ret = popped_node->element;

  // unlink previous head node, then free it
  list->head = popped_node->next;
  free(popped_node);
  // we cannot refer to popped node any longer

  list->length--;

  return ret;
}



// Documented in .h file
void CL_append(CList list, CListElementType element)
{
  assert(list);

  //
  // TODO: Add your code here

  struct _cl_node *new_node = _CL_new_node(element, NULL);
  
  if (list->head == NULL) {
    list->head = new_node;
  } else {
    struct _cl_node *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }

  list->length++;
  //
}




// Documented in .h file
CListElementType CL_nth(CList list, int pos)
{
  assert(list);

  //
  // TODO: Add your code here

  if (pos < 0 || pos >= list->length) {
    return INVALID_RETURN;
  }

  struct _cl_node *current = list->head;
  for (int i = 0; i < pos; i++) {
    current = current->next;
  }

  return current->element;
  //
  return INVALID_RETURN;
}



// Documented in .h file
bool CL_insert(CList list, CListElementType element, int pos)
{
  assert(list);

  //
  // TODO: Add your code here

  if (pos < 0 || pos > list->length) {
    return false; // Position out of bounds
  }

  if (pos == 0) {
    CL_push(list, element);
    return true;
  }

  struct _cl_node *prev = list->head;
  for (int i = 0; i < pos - 1; i++) {
    prev = prev->next;
  }

  struct _cl_node *new_node = _CL_new_node(element, prev->next);
  prev->next = new_node;
  list->length++;

  return true;
}


    
// Documented in .h file
CListElementType CL_remove(CList list, int pos)
{
  assert(list);

  // If the list is empty or pos is out of bounds, return INVALID_RETURN
    if (list->head == NULL || pos < 0 || pos >= CL_length(list)) {
        return INVALID_RETURN;
    }

    struct _cl_node *node_to_remove = list->head;
    struct _cl_node *previous = NULL;
    CListElementType element;

    // Special case: removing the head
    if (pos == 0) {
        element = node_to_remove->element;
        list->head = node_to_remove->next;
        free(node_to_remove);
    } else {
        // Traverse to the node at position `pos`
        for (int i = 0; i < pos; i++) {
            previous = node_to_remove;
            node_to_remove = node_to_remove->next;
        }

        // Remove the node by adjusting the previous node's next pointer
        element = node_to_remove->element;
        previous->next = node_to_remove->next;

        free(node_to_remove);
    }

    // Return the element that was removed
    return element;
  //
  // TODO: Add your code here
  
}



// Documented in .h file
CList CL_copy(CList src_list)
{
  assert(src_list);

  //
  // TODO: Add your code here
   CList new_list = CL_new();
  struct _cl_node *current = src_list->head;

  while (current != NULL) {
    CL_append(new_list, current->element);
    current = current->next;
  }

  //
  return NULL;
}



// Documented in .h file
int CL_insert_sorted(CList list, CListElementType element)
{
  assert(list);

  struct _cl_node *current = list->head;
  int pos = 0;

  while (current != NULL && strcmp(current->element, element) < 0) {
    current = current->next;
    pos++;
  }

  CL_insert(list, element, pos);

  //
  // TODO: Add your code here
  //
  return -1;
}


// Documented in .h file
void CL_join(CList list1, CList list2)
{
  assert(list1);
  assert(list2);

  //
  // TODO: Add your code here

  if (list1->head == NULL) {
    list1->head = list2->head;
  } else {
    struct _cl_node *current = list1->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = list2->head;
  }

  list1->length += list2->length;
  //
}


// Documented in .h file
void CL_reverse(CList list)
{
  assert(list);

  //
  // TODO: Add your code here
  struct _cl_node *prev = NULL;
  struct _cl_node *current = list->head;
  struct _cl_node *next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  list->head = prev;
  //
}


// Documented in .h file
void CL_foreach(CList list, CL_foreach_callback callback, void *cb_data)
{
  assert(list);

  //
  // TODO: Add your code here
  assert(callback); // Ensure the callback is valid

    struct _cl_node *current = list->head; // Assuming _cl_node is the internal node structure
    int pos = 0; // To track the position of the current element in the list

    while (current != NULL) {
        // Call the callback for the current element
        callback(pos, current->element, cb_data);

        // Move to the next node
        current = current->next;
        pos++;
    }
  //
}



