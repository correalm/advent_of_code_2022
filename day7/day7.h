#ifndef _DAY7_H_
#define _DAY7_H_

struct Node {
  long size;
  char *name;
  struct Node *next;
  struct Dir *parent;
};

struct Dir {
  char *name;
  struct Node *children;
  struct Dir *parent;
  struct Dir *next;
};


struct Dir *create_dir ( char* name, struct Dir* parent );
void insert_file ( struct Dir* dir, struct Node* file );
int day7 (char *path);

#endif /* _DAY7_H_ */
