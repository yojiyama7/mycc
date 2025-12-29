#include "mycc.h"

Type *ty_int = &(Type){ INT };

Type *copy_type(Type *ty) {
  Type *cloned = calloc(1, sizeof(Type));
  if (ty->ptr_to) {
    cloned->ptr_to = copy_type(ty->ptr_to);
  } else {
    cloned->core = ty->core;
  }
  return cloned;
}

Type *pointer_to(Type *ty) {
  Type *ptr = calloc(1, sizeof(Type));

  ptr->core = PTR;
  ptr->ptr_to = ty;
  return ptr;
}

void solve_type(Node *node) {
  if (node == NULL) {
    return ;
  }
  // fprintf(stderr, "[%p]\n", node->type);
  if (node->type) {
    return;
  }

  solve_type(node->lhs);
  solve_type(node->rhs);

  switch (node->kind) {
  case ND_ADD:
    Type *a = node->lhs->type;
    Type *b = node->rhs->type;
    // fprintf(stderr, "[%d, %d]\n", node->lhs->kind, node->rhs->kind);
    // fprintf(stderr, "<%p, %p>\n", a->ptr_to, b->ptr_to);

    // node->type = ty_int;
    // return;
    if (a->ptr_to && b == ty_int) {
      node->type = copy_type(a);
      return;
    }
    break;
  default:
    break;
  }
  node->type = ty_int;
  return;
}