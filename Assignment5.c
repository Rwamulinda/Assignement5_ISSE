/*
 * clist.c
 * 
 * Linked list implementation for ISSE Assignment 5
 *
 * Author: <Pauline Uwase>
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
  //
}




// Documented in .h file
CListElementType CL_nth(CList list, int pos)
{
  assert(list);

  //
  // TODO: Add your code here
  //
  return INVALID_RETURN;
}



// Documented in .h file
bool CL_insert(CList list, CListElementType element, int pos)
{
  assert(list);

  //
  // TODO: Add your code here
  //
  return true;
}


    
// Documented in .h file
CListElementType CL_remove(CList list, int pos)
{
  assert(list);

  //
  // TODO: Add your code here
  //
  return INVALID_RETURN;
}



// Documented in .h file
CList CL_copy(CList src_list)
{
  assert(src_list);

  //
  // TODO: Add your code here
  //
  return NULL;
}



// Documented in .h file
int CL_insert_sorted(CList list, CListElementType element)
{
  assert(list);

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
  //
}


// Documented in .h file
void CL_reverse(CList list)
{
  assert(list);

  //
  // TODO: Add your code here
  //
}


// Documented in .h file
void CL_foreach(CList list, CL_foreach_callback callback, void *cb_data)
{
  assert(list);

  //
  // TODO: Add your code here
  //
}




