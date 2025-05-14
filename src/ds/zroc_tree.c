#include "include/ds/zroc_tree.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CHILDREN_CAPACITY 4

Zroc_Tree *tree_new(size_t element_size) {
  errno = 0;
  if (element_size == 0) {
    errno = EINVAL;
    return NULL;
  }

  Zroc_Tree *new_tree = (Zroc_Tree *)malloc(sizeof(Zroc_Tree));
  if (new_tree == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  new_tree->root = NULL;
  new_tree->size = 0;
  new_tree->element_size = element_size;
  return new_tree;
}

Tree_Node *tree_create_node(Zroc_Tree *tree, void *value, Tree_Node *parent) {
  errno = 0;
  if (tree == NULL || value == NULL) {
    errno = EINVAL;
    return NULL;
  }

  Tree_Node *new_node = (Tree_Node *)malloc(sizeof(Tree_Node));
  if (new_node == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  new_node->data = malloc(tree->element_size);
  if (new_node->data == NULL) {
    errno = ENOMEM;
    free(new_node);
    return NULL;
  }

  memcpy(new_node->data, value, tree->element_size);

  new_node->parent = parent;
  new_node->children = NULL;
  new_node->num_children = 0;
  new_node->children_capacity = 0;

  tree->size++;

  return new_node;
}

int tree_add_child(Zroc_Tree *tree, Tree_Node *parent, void *value) {
  errno = 0;
  if (tree == NULL || value == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (tree->root == NULL && parent == NULL) {
    tree->root = tree_create_node(tree, value, NULL);
    return tree->root != NULL ? 0 : -1;
  }

  if (parent == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (parent->children == NULL) {
    parent->children =
        (Tree_Node **)malloc(INITIAL_CHILDREN_CAPACITY * sizeof(Tree_Node *));
    if (parent->children == NULL) {
      errno = ENOMEM;
      return -1;
    }
    parent->children_capacity = INITIAL_CHILDREN_CAPACITY;
  } else if (parent->num_children >= parent->children_capacity) {
    size_t new_capacity = parent->children_capacity * 2;
    Tree_Node **new_children = (Tree_Node **)realloc(
        parent->children, new_capacity * sizeof(Tree_Node *));
    if (new_children == NULL) {
      errno = ENOMEM;
      return -1;
    }
    parent->children = new_children;
    parent->children_capacity = new_capacity;
  }

  Tree_Node *new_node = tree_create_node(tree, value, parent);
  if (new_node == NULL) {
    return -1;
  }

  parent->children[parent->num_children++] = new_node;
  return 0;
}

Tree_Node *tree_find_recursive(Tree_Node *node, void *value,
                               int (*compare)(void *, void *)) {
  if (node == NULL) {
    return NULL;
  }

  if (compare(node->data, value) == 0) {
    return node;
  }

  for (size_t i = 0; i < node->num_children; i++) {
    Tree_Node *found = tree_find_recursive(node->children[i], value, compare);
    if (found != NULL) {
      return found;
    }
  }

  return NULL;
}

Tree_Node *tree_find(Zroc_Tree *tree, void *value,
                     int (*compare)(void *, void *)) {
  errno = 0;
  if (tree == NULL || value == NULL || compare == NULL) {
    errno = EINVAL;
    return NULL;
  }

  return tree_find_recursive(tree->root, value, compare);
}

Tree_Node *tree_remove(Zroc_Tree *tree, void *value,
                       int (*compare)(void *, void *)) {
  errno = 0;
  if (tree == NULL || value == NULL || compare == NULL) {
    errno = EINVAL;
    return NULL;
  }

  // Find the node to remove
  Tree_Node *node = tree_find(tree, value, compare);
  if (node == NULL) {
    errno = ENOENT;
    return NULL;
  }

  // If this is the root node with no children, just free it
  if (node == tree->root && node->num_children == 0) {
    free(node->data);
    free(node);
    tree->root = NULL;
    tree->size--;
    return NULL;
  }

  // If the node has a parent, remove it from the parent's children array
  if (node->parent != NULL) {
    Tree_Node *parent = node->parent;
    size_t index = 0;

    // Find the index of the node in the parent's children array
    while (index < parent->num_children && parent->children[index] != node) {
      index++;
    }

    // Shift all subsequent children to fill the gap
    for (size_t i = index; i < parent->num_children - 1; i++) {
      parent->children[i] = parent->children[i + 1];
    }

    parent->num_children--;
  }

  // Make all children point to the parent of the removed node
  for (size_t i = 0; i < node->num_children; i++) {
    node->children[i]->parent = node->parent;

    // If the node has a parent, add its children to the parent
    if (node->parent != NULL) {
      if (node->parent->num_children >= node->parent->children_capacity) {
        size_t new_capacity = node->parent->children_capacity * 2;
        Tree_Node **new_children = (Tree_Node **)realloc(
            node->parent->children, new_capacity * sizeof(Tree_Node *));
        if (new_children == NULL) {
          errno = ENOMEM;
          return NULL;
        }
        node->parent->children = new_children;
        node->parent->children_capacity = new_capacity;
      }

      node->parent->children[node->parent->num_children++] = node->children[i];
    } else if (node == tree->root) {
      // If we're removing the root, the first child becomes the new root
      if (i == 0) {
        tree->root = node->children[i];
      }
    }
  }

  // Free the node
  free(node->data);
  free(node->children);
  free(node);
  tree->size--;

  return node->parent;
}

void tree_free_node(Zroc_Tree *tree, Tree_Node *node) {
  if (node == NULL) {
    return;
  }

  // Recursively free all children
  for (size_t i = 0; i < node->num_children; i++) {
    tree_free_node(tree, node->children[i]);
  }

  // Free the node's resources
  if (node->data != NULL) {
    free(node->data);
  }

  if (node->children != NULL) {
    free(node->children);
  }

  free(node);
  tree->size--;
}

void tree_free(Zroc_Tree *tree) {
  if (tree == NULL) {
    return;
  }

  tree_free_node(tree, tree->root);
  free(tree);
}
