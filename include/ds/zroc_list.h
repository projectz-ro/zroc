#ifndef ZROC_LIST
#define ZROC_LIST
#include <stdlib.h>

typedef struct List_Node {
  void *data;
  struct List_Node *next;
  struct List_Node *previous;
  size_t element_size;
} List_Node;

typedef struct {
  struct List_Node *head;
  struct List_Node *tail;
  size_t size;
  size_t element_size;
} Zroc_List;

int list_create_node(size_t element_size, struct List_Node **out);
int list_new(size_t element_size, int count, void *values, Zroc_List *out);
int list_get(Zroc_List *list, int index, void *out);
int list_add(Zroc_List *list, int index, void *value);
int list_remove(Zroc_List *list, int index, void *out);
void list_free(Zroc_List *list);
#endif
