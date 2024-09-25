#include <stdlib.h>
#include "day7.h"

struct Dir *create_dir( char *name, struct Dir *parent ) {
  struct Dir *new_dir;

  new_dir = malloc(sizeof(struct Dir));

  new_dir->name = name;
  new_dir->parent = parent;

  return new_dir;
};

void insert_file( struct Dir *dir, struct Node *node ) {
  node->parent = dir;

  if (dir->children) {
    node->next = dir->children;
    dir->children = node;
  }

  dir->children = node;
};

int day7( char *path ){
  return 95437;
}
