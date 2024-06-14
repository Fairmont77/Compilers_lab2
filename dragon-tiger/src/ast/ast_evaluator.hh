#ifndef AST_EVALUATOR_HH
#define AST_EVALUATOR_HH

#include "../utils/errors.hh"
#include "nodes.hh"

namespace ast {

class ASTEvaluator : public ConstASTIntVisitor {
public:
  // IntegerLiteral
  int32_t visit(const IntegerLiteral& literal) override {
    return literal.value;
  }

  // BinaryOperator
  int32_t visit(const BinaryOperator& oper) override {
    int32_t left = oper.get_left().accept(*this);
    int32_t right = oper.get_right().accept(*this);

    switch (oper.op) {
      case o_plus:
        return left + right;
      case o_minus:
        return left - right;
      case o_times:
        return left * right;
      case o_divide:
        if (right == 0) {
          utils::error("Division by zero");
          return 0;
        }
        return left / right;
      case o_eq:
        return left == right;
      case o_neq:
        return left != right;
      case o_lt:
        return left < right;
      case o_le:
        return left <= right;
      case o_gt:
        return left > right;
      case o_ge:
        return left >= right;
      default:
        utils::error("Unsupported operator");
        return 0;
    }
  }

  // Sequence
  int32_t visit(const Sequence& seq) override {
    if (seq.get_exprs().empty()) {
      utils::error("Sequence empty");
      return 0;
    }
    int32_t result = 0;
    for (auto expr : seq.get_exprs()) {
      result = expr->accept(*this);
    }
    return result;
  }

  // IfThenElse
  int32_t visit(const IfThenElse& ite) override {
    if (ite.get_condition().accept(*this)) {
      return ite.get_then_part().accept(*this);
    } else {
      return ite.get_else_part().accept(*this);
    }
  }
  int32_t visit(const class StringLiteral &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class Let &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class Identifier &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class VarDecl &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class FunDecl &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class FunCall &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class WhileLoop &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class ForLoop &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class Break &) {
    utils::error("Not implemented");
  }
  int32_t visit(const class Assign &) {
    utils::error("Not implemented");
  }
};

}

#endif
