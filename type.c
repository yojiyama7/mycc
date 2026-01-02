#include "mycc.h"

Type *ty_int = &(Type){ INT, NULL, 0 };
Type *ty_char = &(Type){ CHAR, NULL, 0 };

size_t calc_type_size(Type *ty) {
  if (ty->core == CHAR) {
    return 1;
  } else if (ty->core == INT) {
    return 4;
  } else if (ty->core == PTR) {
    return 8;
  } else if (ty->core == ARRAY) {
    return calc_type_size(ty->ptr_to) * ty->array_size;
  }
  error("不正なタイプのサイズは計算できません");
  return 0;
}

// size_t calc_type_mem_size(Type *ty) {
//   size_t size = calc_type_size(ty);
//   if (size < 8) {
//     size = 8;
//   }
//   return size;
// }

Type *copy_type(Type *ty) {
  if (ty->core == PTR) {
    Type *cloned = calloc(1, sizeof(Type));
    cloned->core = ty->core;
    cloned->ptr_to = copy_type(ty->ptr_to);
    return cloned;
  } else if (ty->core == ARRAY) {
    Type *cloned = calloc(1, sizeof(Type));
    cloned->core = ty->core;
    cloned->ptr_to = copy_type(ty->ptr_to);
    cloned->array_size = ty->array_size;
    return cloned;
  }
  return ty;
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
    if (node->lhs->type->ptr_to && node->rhs->type == ty_int) {
      node->type = copy_type(node->lhs->type);
      return;
    }
    break;
  case ND_SUB:
    if (node->lhs->type->ptr_to && node->rhs->type == ty_int) {
      node->type = copy_type(node->lhs->type);
      return;
    }
    break;
  case ND_DEREF:
    if (node->lhs->type->ptr_to == NULL) {
      error("ポインタ型でない値をデリファレンスしています");
    }
    node->type = copy_type(node->lhs->type->ptr_to);
    return;
  default:
    break;
  }
  node->type = ty_int;
  return;
}