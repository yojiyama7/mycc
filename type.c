#include "mycc.h"

Type *ty_int = &(Type){ INT };

size_t calc_type_size(Type *ty) {
  if (ty->core == INT) {
    return 4;
  } else if (ty->core == PTR) {
    return 8;
  } else if (ty->core == ARRAY) {
    return calc_type_size(ty->ptr_to) * ty->array_size;
  }
  error("不正なタイプのサイズは計算できません");
  return 0;
}

size_t calc_type_mem_size(Type *ty) {
  size_t size = calc_type_size(ty);
  if (size < 8) {
    size = 8;
  }
  return size;
}

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

Type *array_of(Type *ty) {
  Type *arr = calloc(1, sizeof(Type));

  arr->core = ARRAY;
  arr->ptr_to = ty;
  return arr;
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