/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/9/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnfrule.h
 *
 * \brief       Declares the structure of the Backus-Naur Form LL(1) grammar
 *              rule class.
 */
#ifndef BNFRULE_H
#define BNFRULE_H

#include <string>
#include <vector>

class BnfTerm;

/// Typedefs for simplicity
typedef std::vector<BnfTerm*> BnfExpression;
typedef std::vector<BnfExpression*> BnfExpressionVector;

/*!
 * \brief The BnfRule class defines a single rule of a BnfGrammar.
 */
class BnfRule
{
    friend class BnfGrammar;
public:
    /// Instantiates a BnfRule object.
    BnfRule();

    /// Creates a copy of the given BnfRule.
    BnfRule(const BnfRule& copy);

    /// Gets the expressions within a BnfRule.
    BnfExpressionVector* expressions() const;

    /// Adds an expression to the rule.
    void addExpression(BnfExpression* expression);

    /// Gets the name of the rule.
    std::string ruleName() const;

    /// Sets the name of the rule.
    void setRuleName(const std::string value);

    /// Gets whether the rule is nullable.
    bool isNullable() const;

    /// Returns the left factored rules of the rule.
    std::vector<BnfRule*>* leftFactor();

private:
    /// The name of the rule.
    std::string m_RuleName;

    /// The vector of expressions in the rule.
    BnfExpressionVector* m_Expressions;

    /// Tracks whether the rule is nullable.
    bool m_HasLambda;
};

#endif // BNFRULE_H
