#include "mycc.h"

void printfe(char *fmt, ...) {
  va_list va;
  va_start(va, fmt);
  vfprintf(stderr, fmt, va);
}

// print_node
void print_node(Node *node) {
  if (node == NULL) {
    printfe("(null)");
    return;
  }
  switch (node->kind) {
  case ND_NUM: 
    printfe("ND_NUM(%d)", node->val);
    return;
  case ND_STRING:
    printfe("ND_STRING{ str: \"%.*s\", id: %d }", node->string->len, node->string->str, node->string->id);
    return;
  case ND_LVAR:
    printfe("LVAR{ offset: %d }", node->offset);
    return;
  case ND_GVAR:
    printfe("GVAR{ name: %.*s }", node->gvar_name_len, node->gvar_name);
    return;
  case ND_ADD: 
    printfe("ADD{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_SUB: 
    printfe("SUB{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_MUL: 
    printfe("MUL{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_DIV:
    printfe("DIV{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_ASSIGN:
    printfe("ASSIGN{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_DEREF: 
    printfe("DEREF{ lhs: ");
    print_node(node->lhs);
    printfe(" }");
    return;
  case ND_CALL:
    printfe("CALL{ name: %.*s, args: [ ", node->func_name_len, node->func_name);
    for (Node *n = node->args; n; n = n->next) {
      print_node(n);
      printfe(", ");
    }
    printfe("] }");
    return;
  case ND_ADDR: 
    printfe("ADDR{ lhs: ");
    print_node(node->lhs);
    printfe(" }");
    return;
  case ND_EXPRSTMT:
    printfe("EXPRSTMT{ lhs: ");
    print_node(node->lhs);
    printfe(" }");
    return;
  case ND_RETURN:
    printfe("RETURN{ lhs: ");
    print_node(node->lhs);
    printfe(" }");
    return;
  case ND_VARDEF:
    printfe("VARDEF{ name: %.*s, offset: %d }", node->defined_var->len, node->defined_var->name, node->defined_var->offset);
    return;
  case ND_BLOCK:
    printfe("BLOCK{ body: [ ");
    for (Node *n = node->body; n; n = n->next) {
      print_node(n);
      printfe(", ");
    }
    printfe("] }");
    return;
  case ND_FUNCDEF:
    printfe("FUNCDEF{ name: %.*s, lvar: [", node->func_name_len, node->func_name);
    for (LVar *lvar = node->locals; lvar; lvar = lvar->next) {
      printfe("LVAR(name: %.*s, offset: %d) ", lvar->len, lvar->name, lvar->offset);
    }
    printfe("], body: [ ");
    for (Node *n = node->body; n; n = n->next) {
      print_node(n);
      printfe(", ");
    }
    printfe("] }");
    return;
  case ND_FUNCNAME:
    printfe("FUNCNAME{ name: %.*s }", node->func_name_len, node->func_name);
    return;
  default:
    printfe("未知のノードです, kind=%d\n", node->kind);
  }
}