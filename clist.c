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

static struct _cl_node* _CL_new_node(CListElementType element, struct _cl_node *next) {
    struct _cl_node* new = (struct _cl_node*) malloc(sizeof(struct _cl_node));
    assert(new);
    new->element = element;
    new->next = next;
    return new;
}

CList CL_new() {
    CList list = (CList) malloc(sizeof(struct _clist));
    assert(list);
    list->head = NULL;
    list->length = 0;
    return list;
}

void CL_free(CList list) {
    assert(list);
    struct _cl_node *current = list->head;
    struct _cl_node *next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    free(list);
}

int CL_length(CList list) {
    assert(list);
#ifdef DEBUG
    int len = 0;
    for (struct _cl_node *node = list->head; node != NULL; node = node->next)
        len++;
    assert(len == list->length);
#endif // DEBUG
    return list->length;
}

void CL_print(CList list) {
    assert(list);
    int num = 0;
    for (struct _cl_node *node = list->head; node != NULL; node = node->next)
        printf("  [%d]: %s\n", num++, node->element);
}

void CL_push(CList list, CListElementType element) {
    assert(list);
    list->head = _CL_new_node(element, list->head);
    list->length++;
}

CListElementType CL_pop(CList list) {
    assert(list);
    struct _cl_node *popped_node = list->head;
    if (popped_node == NULL)
        return INVALID_RETURN;
    CListElementType ret = popped_node->element;
    list->head = popped_node->next;
    free(popped_node);
    list->length--;
    return ret;
}

void CL_append(CList list, CListElementType element) {
    assert(list);
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
}

CListElementType CL_nth(CList list, int pos) {
    assert(list);
    if (pos < 0 || pos >= list->length) {
        return INVALID_RETURN;
    }
    struct _cl_node *current = list->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->element;
}

bool CL_insert(CList list, CListElementType element, int pos) {
    assert(list);
    if (pos < 0 || pos > list->length) {
        return false;
    }
    if (pos == 0) {
        CL_push(list, element);
        return true;
    }
    struct _cl_node *new_node = _CL_new_node(element, NULL);
    struct _cl_node *current = list->head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    list->length++;
    return true;
}

CListElementType CL_remove(CList list, int pos) {
    assert(list);
    if (pos < 0 || pos >= list->length) {
        return INVALID_RETURN;
    }
    struct _cl_node *current = list->head;
    if (pos == 0) {
        return CL_pop(list);
    }
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }
    struct _cl_node *removed_node = current->next;
    if (removed_node == NULL) {
        return INVALID_RETURN;
    }
    current->next = removed_node->next;
    CListElementType ret = removed_node->element;
    free(removed_node);
    list->length--;
    return ret;
}

CList CL_copy(CList src_list) {
    assert(src_list);
    CList new_list = CL_new();
    struct _cl_node *current = src_list->head;
    while (current != NULL) {
        CL_append(new_list, current->element);
        current = current->next;
    }
    return new_list;
}

int CL_insert_sorted(CList list, CListElementType element) {
    assert(list);
    struct _cl_node *new_node = _CL_new_node(element, NULL);
    if (list->head == NULL || strcmp(list->head->element, element) >= 0) {
        new_node->next = list->head;
        list->head = new_node;
        list->length++;
        return 0; // inserted at the head
    }
    struct _cl_node *current = list->head;
    int pos = 1;
    while (current->next != NULL && strcmp(current->next->element, element) < 0) {
        current = current->next;
        pos++;
    }
    new_node->next = current->next;
    current->next = new_node;
    list->length++;
    return pos; // inserted at position
}

void CL_join(CList list1, CList list2) {
    assert(list1);
    assert(list2);
    if (list2->head == NULL) return; // Nothing to join
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
    free(list2); // Free list2 after joining
}

void CL_reverse(CList list) {
    assert(list);
    struct _cl_node *prev = NULL;
    struct _cl_node *current = list->head;
    struct _cl_node *next = NULL;
    
    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse the link
        prev = current;       // Move prev forward
        current = next;       // Move current forward
    }
    list->head = prev; // Reset head to the new front
}
