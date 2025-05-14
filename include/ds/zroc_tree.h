#ifndef ZROC_TREE_H
#define ZROC_TREE_H

#include <stddef.h>

typedef struct Tree_Node {
  void *data;
  struct Tree_Node *parent;
  struct Tree_Node **children;
  size_t num_children;
  size_t children_capacity;
} Tree_Node;

typedef struct {
  Tree_Node *root;
  size_t size;
  size_t element_size;
} Zroc_Tree;

Zroc_Tree *tree_new(size_t element_size);
Tree_Node *tree_create_node(Zroc_Tree *tree, void *value, Tree_Node *parent);
int tree_add_child(Zroc_Tree *tree, Tree_Node *parent, void *value);
Tree_Node *tree_find(Zroc_Tree *tree, void *value,
                     int (*compare)(void *, void *));
Tree_Node *tree_remove(Zroc_Tree *tree, void *value,
                       int (*compare)(void *, void *));
void tree_free_node(Zroc_Tree *tree, Tree_Node *node);
void tree_free(Zroc_Tree *tree);

#endif
