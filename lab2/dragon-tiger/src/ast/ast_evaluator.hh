#ifndef AST_EVALUATOR_HH
#define AST_EVALUATOR_HH

#include "../utils/errors.hh"
#include "nodes.hh"

namespace ast {
    class ASTEvaluator : public ConstASTIntVisitor {
        int32_t visit(const class IntegerLiteral &intlit) {
            return intlit.value;
        }

        int32_t visit(const class BinaryOperator &binop) {
            int32_t left = binop.get_left().accept(*this);
            int32_t right = binop.get_right().accept(*this);
            switch (binop.op) {
                case o_plus:
                    return left + right;
                case o_minus:
                    return left - right;
                case o_times:
                    return left * right;
                case o_divide:
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
                    utils::error("unknown operator");
            }
        }

        int32_t visit(const class Sequence &seq) {
            std::vector<ast::types::Expr *> exprs = seq.get_exprs();
            if (exprs.empty()) {
                utils::error("empty sequence");
            }

            int32_t result = 0;
            for (Expr *expr : exprs) {
                result = expr->accept(*this);
            }
            return result;
        }

        int32_t visit(const class IfThenElse &condexpr) {
            if (condexpr.get_condition().accept(*this)){
                return condexpr.get_then_part().accept(*this);
            } else {
                return condexpr.get_else_part().accept(*this);
            }
        }

        int32_t visit(const class StringLiteral &) {
            utils::error("string literal evaluation not implemented");
        }
        int32_t visit(const class Let &) {
            utils::error("let evaluation not implemented");
        }
        int32_t visit(const class Identifier &) {
            utils::error("idetifier evaluation not implemented");
        }
        int32_t visit(const class VarDecl &) {
            utils::error("variable decalration evaluation not implemented");
        }
        int32_t visit(const class FunDecl &) {
            utils::error("function declaration evaluation not implemented");
        }
        int32_t visit(const class FunCall &) {
            utils::error("function call evaluation not implemented");
        }
        int32_t visit(const class WhileLoop &) {
            utils::error("while loop evaluation not implemented");
        }
        int32_t visit(const class ForLoop &) {
            utils::error("for loop evaluation not implemented");
        }
        int32_t visit(const class Break &) {
            utils::error("break evaluation not implemented");
        }
        int32_t visit(const class Assign &) {
            utils::error("assign evaluation not implemented");
        }
    };
}

#endif