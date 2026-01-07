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
    printfe("GVAR{ name: %.*s }", node->gvar->len, node->gvar->name);
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
  case ND_EQ:
    printfe("EQ{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_NE:
    printfe("NE{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_LT:
    printfe("LT{ lhs: ");
    print_node(node->lhs);
    printfe(", rhs: ");
    print_node(node->rhs);
    printfe(" }");
    return;
  case ND_LE:
    printfe("LE{ lhs: ");
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
    printfe("CALL{ name: %.*s, args: [ ", node->call_len, node->call_name);
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
  case ND_LVARDEF:
    printfe("LVARDEF{ name: %.*s, offset: %d }", node->defined_lvar->len, node->defined_lvar->name, node->defined_lvar->offset);
    return;
  case ND_GVARDEF:
    printfe("GVARDEF{ name: %.*s }", node->defined_gvar->len, node->defined_gvar->name);
    return;
  case ND_IF:
    printfe("IF{ cond: ");
    print_node(node->cond);
    printfe(", then: ");
    print_node(node->then);
    printfe(" }");
    return;
  case ND_IFELSE:
    printfe("IFELSE{ cond: ");
    print_node(node->cond);
    printfe(", then: ");
    print_node(node->then);
    printfe(", els: ");
    print_node(node->els);
    printfe(" }");
    return;
  case ND_FOR:
    printfe("FOR{ init: ");
    print_node(node->init);
    printfe(", cond: ");
    print_node(node->cond);
    printfe(", inc: ");
    print_node(node->inc);
    printfe(", then: ");
    print_node(node->then);
    printfe(" }");
    return;
  case ND_WHILE:
    printfe("WHILE{ cond: ");
    print_node(node->cond);
    printfe(", then: ");
    print_node(node->then);
    printfe(" }");
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
    printfe("FUNCDEF{ name: %.*s, lvar: [", node->defined_func->len, node->defined_func->name);
    for (LVar *lvar = node->defined_func->locals; lvar; lvar = lvar->next) {
      printfe("LVAR(name: %.*s, offset: %d) ", lvar->len, lvar->name, lvar->offset);
    }
    printfe("], body: [ ");
    for (Node *n = node->defined_func->body; n; n = n->next) {
      print_node(n);
      printfe(", ");
    }
    printfe("] }");
    return;
  case ND_FUNCNAME:
    printfe("FUNCNAME{ name: %.*s }", node->call_len, node->call_name);
    return;
  default:
  }
  printfe("未知のノードです, kind=%d\n", node->kind);
}