#pragma once
#include "Expr.hh" // Залежить від вашої структури проекту

class UnaryOperator : public Expr {
public:
    Expr* operand;
    OperatorType op;

    UnaryOperator(Expr* operand, OperatorType op)
        : operand(operand), op(op) {}
};

