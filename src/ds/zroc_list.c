#include "include/ds/zroc_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int list_create_node(size_t element_size, struct List_Node **out) {
  if (!out) {
    fputs("Error: Null \"out\".\n", stderr);
    return -1;
  }

  *out = malloc(sizeof(struct List_Node));
  if (!*out) {
    fputs("Error: Memory allocation failed for node.\n", stderr);
    return -1;
  }

  (*out)->data = malloc(element_size);
  if (!(*out)->data) {
    fputs("Error: Memory allocation failed for node data.\n", stderr);
    free(*out);
    return -1;
  }

  (*out)->element_size = element_size;
  (*out)->next = NULL;
  (*out)->previous = NULL;

  return 0;
}

int list_get(Zroc_List *list, int index, void *out) {
  if (!out) {
    fputs("Error: Null \"out\".\n", stderr);
    return -1;
  }
  if (!list) {
    fputs("Error: Null \"list\".\n", stderr);
    return -1;
  }
  if ((int)list->size <= index || index < 0) {
    fprintf(stderr,
            "Error: Index out of bounds for list_get. Index: %d, Size: %zu\n",
            index, list->size);
    return -1;
  }

  struct List_Node *node = list->head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  memcpy(out, node->data, list->element_size);

  return 0;
}

int list_add(Zroc_List *list, int index, void *value) {
  struct List_Node *newNode;
  if (list_create_node(list->element_size, &newNode) != 0) {
    return -1;
  }

  memcpy(newNode->data, value, list->element_size);

  if (index < 0 || index > (int)list->size) {
    fprintf(stderr,
            "Error: Index out of bounds for list_add. Index: %d, Size: %zu\n",
            index, list->size);
    free(newNode->data);
    free(newNode);
    return -1;
  }

  if (index == 0) {
    newNode->next = list->head;
    if (list->head) {
      list->head->previous = newNode;
    }
    list->head = newNode;
    if (list->size == 0) {
      list->tail = newNode;
    }
  } else if (index == list->size) {
    if (list->tail) {
      list->tail->next = newNode;
      newNode->previous = list->tail;
    }
    list->tail = newNode;
    if (list->size == 0) {
      list->head = newNode;
    }
  } else {
    struct List_Node *node = list->head;
    for (int i = 0; i < index - 1; i++) {
      node = node->next;
    }
    newNode->next = node->next;
    if (node->next) {
      node->next->previous = newNode;
    }
    node->next = newNode;
    newNode->previous = node;
  }

  list->size++;
  return 0;
}

int list_remove(Zroc_List *list, int index, void *out) {
  if (index < 0 || index >= (int)list->size) {
    fprintf(
        stderr,
        "Error: Index out of bounds for list_remove. Index: %d, Size: %zu\n",
        index, list->size);
    return -1;
  }

  list_get(list, index, out);

  struct List_Node *node = list->head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }

  if (node->previous) {
    node->previous->next = node->next;
  }
  if (node->next) {
    node->next->previous = node->previous;
  }

  if (node == list->head) {
    list->head = node->next;
  }
  if (node == list->tail) {
    list->tail = node->previous;
  }

  free(node->data);
  free(node);
  list->size--;
  return 0;
}

int list_new(size_t element_size, int count, void *values, Zroc_List *out) {
  if (!out) {
    fputs("Error: Null \"out\".\n", stderr);
    return -1;
  }

  out->element_size = element_size;
  out->size = count;
  out->head = NULL;
  out->tail = NULL;

  if (!values) {
    out->size = 0;
  }

  return 0;
}

void list_free(Zroc_List *list) {
  struct List_Node *node = list->head;
  while (node) {
    struct List_Node *next = node->next;
    free(node->data);
    free(node);
    node = next;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}
