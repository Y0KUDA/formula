#pragma once
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

namespace Formula_internal
{

class Calc
{
public:
    enum Status
    {
        SUCCESS,
        ZERO_DIV,
        UNKNOWN_ERROR,
    };

private:
    static bool is_number(string s)
    {
        if ((s[s.length() - 1] >= '0' && s[s.length() - 1] <= '9'))
        {
            return true;
        }
        return false;
    }
    static vector<string> trim(vector<string> v_formula, int begin, int end)
    {
        vector<string> ret;
        for (int i = begin; i <= end; i++)
        {
            ret.push_back(v_formula[i]);
        }
        return ret;
    }
    static int find_right_parenthesis(vector<string> v_formula)
    {
        int stack = 1;
        vector<string> v_sub_formula;
        for (int i = 1; i < v_formula.size(); i++)
        {
            if (v_formula[i] == ")")
            {
                stack--;
            }
            else if (v_formula[i] == "(")
            {
                stack++;
            }
            if (stack == 0)
            {
                return i;
            }
        }
        return -1;
    }
    static int find_block_tail(vector<string> v_formula)
    {
        int stack = 0;
        vector<string> v_sub_formula;
        for (int i = 0; i < v_formula.size(); i++)
        {
            if (v_formula[i] == ")")
            {
                stack--;
            }
            else if (v_formula[i] == "(")
            {
                stack++;
            }
            if (stack == 0)
            {
                if (i == 0)
                    continue;
                if ((v_formula[i] == "+" || v_formula[i] == "-") &&
                    (is_number(v_formula[i - 1]) || (v_formula[i - 1] == ")")))
                    return i - 1;
            }
        }
        return v_formula.size() - 1;
    }
    static pair<Status, double> val_op_formula(double val, string op, vector<string> v_formula)
    {
        if (op == "+")
        {
            auto result = eval(v_formula);
            result.second = val + result.second;
            return result;
        }
        else if (op == "-")
        {
            v_formula.insert(v_formula.begin(), {"-1", "*"});
            return val_op_formula(val, "+", v_formula);
        }
        else if (op == "*")
        {
            if (v_formula[0] == "(")
            {
                int rp = find_right_parenthesis(v_formula);
                if (rp == v_formula.size() - 1)
                {
                    auto result = eval(trim(v_formula, 1, v_formula.size() - 2));
                    if (result.first != Status::SUCCESS)
                    {
                        return result;
                    }
                    result.second = val * result.second;
                    return result;
                }
                else
                {
                    auto result = eval(trim(v_formula, 1, rp - 1));
                    if (result.first != Status::SUCCESS)
                    {
                        return result;
                    }
                    result.second = val * result.second;
                    return val_op_formula(result.second, v_formula[rp + 1], trim(v_formula, rp + 2, v_formula.size() - 1));
                }
            }
            else if (is_number(v_formula[0]))
            {
                if (v_formula.size() == 1)
                {
                    return {Status::SUCCESS, val * std::stod(v_formula[0])};
                }
                else
                {
                    return val_op_formula(val * std::stod(v_formula[0]), v_formula[1], trim(v_formula, 2, v_formula.size() - 1));
                }
            }
            else if (v_formula[0] == "+" || v_formula[0] == "-")
            { // sign
                if (v_formula[0] == "-")
                {
                    vector<string> v = trim(v_formula, 1, v_formula.size() - 1);
                    v_formula = v;
                    val = -val;
                }
                auto bt = find_block_tail(v_formula);
                if (bt == v_formula.size() - 1)
                {
                    auto result = eval(v_formula);
                    result.second = val * result.second;
                    return result;
                }
                else
                {
                    auto result = eval(trim(v_formula, 0, bt));
                    result.second = val * result.second;
                    if (result.first != Status::SUCCESS)
                        return {result.first, 0};
                    return val_op_formula(result.second, v_formula[bt + 1], trim(v_formula, bt + 2, v_formula.size() - 1));
                }
            }
        }
        else if (op == "/")
        {
            if (v_formula[0] == "(")
            {
                int rp = find_right_parenthesis(v_formula);
                if (rp == v_formula.size() - 1)
                {
                    auto result = eval(trim(v_formula, 1, v_formula.size() - 2));
                    if (result.first != Status::SUCCESS)
                    {
                        return result;
                    }
                    else if (result.second == 0)
                    {
                        return {Status::ZERO_DIV, 0};
                    }
                    result.second = val / result.second;
                    return result;
                }
                else
                {
                    auto result = eval(trim(v_formula, 1, rp - 1));
                    if (result.first != Status::SUCCESS)
                    {
                        return result;
                    }
                    else if (result.second == 0)
                    {
                        return {Status::ZERO_DIV, 0};
                    }
                    result.second = val / result.second;
                    return val_op_formula(result.second, v_formula[rp + 1], trim(v_formula, rp + 2, v_formula.size() - 1));
                }
            }
            else if (is_number(v_formula[0]))
            {
                if (std::stod(v_formula[0]) == 0)
                {
                    return {Status::ZERO_DIV, 0};
                }
                else if (v_formula.size() == 1)
                {
                    return {Status::SUCCESS, val / std::stod(v_formula[0])};
                }
                else
                {
                    return val_op_formula(val / std::stod(v_formula[0]), v_formula[1], trim(v_formula, 2, v_formula.size() - 1));
                }
            }
            else if (v_formula[0] == "+" || v_formula[0] == "-")
            { // sign
                if (v_formula[0] == "-")
                {
                    vector<string> v = trim(v_formula, 1, v_formula.size() - 1);
                    v_formula = v;
                    val = -val;
                }
                auto bt = find_block_tail(v_formula);
                if (bt == v_formula.size() - 1)
                {
                    auto result = eval(v_formula);
                    result.second = val / result.second;
                    return result;
                }
                else
                {
                    auto result = eval(trim(v_formula, 0, bt));
                    if (result.second == 0)
                    {
                        return {Status::ZERO_DIV, 0};
                    }
                    result.second = val / result.second;
                    if (result.first != Status::SUCCESS)
                        return {result.first, 0};
                    return val_op_formula(result.second, v_formula[bt + 1], trim(v_formula, bt + 2, v_formula.size() - 1));
                }
            }
        }
        return {Status::UNKNOWN_ERROR, 0};
    }
    static pair<Status, double> sign_formula(string sign, vector<string> v_formula)
    {
        if (sign == "-")
        {
            v_formula.insert(v_formula.begin(), {"-1", "*"});
        }
        else if (sign == "+")
        {
        }
        return eval(v_formula);
    }

public:
    static pair<Status, double> eval(vector<string> v_formula)
    {
        if (v_formula.size() == 1)
        {
            return {Status::SUCCESS, std::stod(v_formula[0])};
        }
        else if (v_formula[0] == "(")
        {
            int rp = find_right_parenthesis(v_formula);
            if (rp == v_formula.size() - 1)
            {
                return eval(trim(v_formula, 1, v_formula.size() - 2));
            }
            else
            {
                auto result = eval(trim(v_formula, 1, rp - 1));
                if (result.first != Status::SUCCESS)
                {
                    return result;
                }
                return val_op_formula(result.second, v_formula[rp + 1], trim(v_formula, rp + 2, v_formula.size() - 1));
            }
        }
        else if (v_formula[0] == "-" || v_formula[0] == "+")
        {
            return sign_formula(v_formula[0], trim(v_formula, 1, v_formula.size() - 1));
        }
        else if (is_number(v_formula[0]))
        {
            return val_op_formula(std::stod(v_formula[0]), v_formula[1], trim(v_formula, 2, v_formula.size() - 1));
        }
        return {UNKNOWN_ERROR, 0};
    }
};

class Parsable_checker
{
    static bool is_operator(string s)
    {
        if (s == "*" || s == "/" || s == "+" || s == "-")
            return true;
        return false;
    }
    static bool is_sign(string s)
    {
        if (s == "+" || s == "-")
            return true;
        return false;
    }
    static bool is_number(string s)
    {
        if (s[0] >= '0' && s[0] <= '9')
            return true;
        return false;
    }
    static bool is_transitionable_from_start(string s)
    {
        if (is_number(s))
            return true;
        if (is_sign(s))
            return true;
        if (s == "(")
            return true;
        return false;
    }
    static bool is_transitionable_without_stack(string s1, string s2)
    {
        if (is_number(s1))
        {
            if (is_operator(s2))
            {
                return true;
            }
        }
        if (is_operator(s1))
        {
            if (is_number(s2) || is_sign(s2) || (s2 == "("))
            {
                return true;
            }
        }
        if (is_sign(s1))
        {
            if (is_number(s2) || (s2 == "("))
            {
                return true;
            }
        }
        if (s1 == "(")
        {
            if (is_number(s2) || (s2 == "(") || is_sign(s2))
            {
                return true;
            }
        }
        return false;
    }
    static bool is_transitionable_with_stack(string s1, string s2)
    {
        if (is_number(s1))
        {
            if (is_operator(s2) || (s2 == ")"))
            {
                return true;
            }
        }
        if (is_operator(s1))
        {
            if (is_number(s2) || is_sign(s2) || (s2 == "("))
            {
                return true;
            }
        }
        if (is_sign(s1))
        {
            if (is_number(s2) || (s2 == "("))
            {
                return true;
            }
        }
        if (s1 == "(")
        {
            if (is_number(s2) || (s2 == "(") || is_sign(s2))
            {
                return true;
            }
        }
        if (s1 == ")")
        {
            if (is_operator(s2) || (s2 == ")"))
            {
                return true;
            }
        }
        return false;
    }
    static bool is_accepted(string s, int stack)
    {
        if (stack == 0)
        {
            if (is_number(s) || (s == ")"))
                return true;
        }
        return false;
    }

public:
    static bool is_accepted(vector<string> v_formula)
    {
        int stack = 0; // "("
        if (v_formula.size() == 0)
            return false;

        if (!is_transitionable_from_start(v_formula[0]))
        {
            return false;
        }

        for (int i = 0; i + 1 < v_formula.size(); i++)
        {
            if (stack == 0)
            {
                if (is_transitionable_without_stack(v_formula[i], v_formula[i + 1]))
                {
                    if (v_formula[i] == "(")
                        stack++;
                    continue;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (is_transitionable_with_stack(v_formula[i], v_formula[i + 1]))
                {
                    if (v_formula[i] == "(")
                        stack++;
                    else if (v_formula[i] == ")")
                        stack--;
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
        if (v_formula[v_formula.size() - 1] == ")")
            stack--;
        return is_accepted(v_formula[v_formula.size() - 1], stack);
    }
};

} // namespace Formula_internal

class Formula
{
public:
    enum Status
    {
        SUCCESS,
        CHARACTER_ERROR,
        NUMBER_ERROR,
        SIGN_ERROR,
        PARSER_ERROR,
        ZERO_DIV,
        UNKNOWN_ERROR
    };
    static pair<Status, double> eval(string formula)
    {
        if (has_not_accepted_character(formula))
        {
            return {Status::CHARACTER_ERROR, 0};
        }
        auto v_formula = split(formula);
        if (has_invalid_number(v_formula))
        {
            return {Status::NUMBER_ERROR, 0};
        }
        if (has_not_accepted_sign(v_formula))
        {
            return {Status::SIGN_ERROR, 0};
        }
        if (!Formula_internal::Parsable_checker::is_accepted(v_formula))
        {
            return {Status::PARSER_ERROR, 0};
        }
        auto result = Formula_internal::Calc::eval(v_formula);
        if (result.first == Formula_internal::Calc::Status::ZERO_DIV)
        {
            return {Status::ZERO_DIV, result.second};
        }
        return {Status::SUCCESS, result.second};
    }

private:
    static bool has_not_accepted_character(string formula)
    {
        for (int i = 0; i < formula.length(); i++)
        {
            if (formula[i] == '*' ||
                formula[i] == '/' ||
                formula[i] == '+' ||
                formula[i] == '-' ||
                formula[i] == '(' ||
                formula[i] == ')' ||
                formula[i] == ' ' ||
                (formula[i] >= '0' && formula[i] <= '9'))
            {
                continue;
            }
            return true;
        }
        return false;
    }

    static vector<string> split(string formula)
    {
        vector<string> v_formula;
        for (int i = 0; i < formula.length(); i++)
        {
            if (formula[i] == ' ')
            {
                continue;
            }
            else if (formula[i] == '*' ||
                     formula[i] == '/' ||
                     formula[i] == '+' ||
                     formula[i] == '-' ||
                     formula[i] == '(' ||
                     formula[i] == ')')
            {
                v_formula.push_back(string{formula[i]});
            }
            else if (formula[i] >= '0' && formula[i] <= '9')
            {
                for (int j = i + 1; j <= formula.length(); j++)
                {
                    if (j == formula.length() ||
                        !(formula[j] >= '0' && formula[j] <= '9'))
                    {
                        v_formula.push_back(formula.substr(i, j - i));
                        i = j;
                        i--;
                        break;
                    }
                }
            }
        }
        return v_formula;
    }

    static bool has_invalid_number(vector<string> v_formula)
    {
        for (auto &str : v_formula)
        {
            if (str[0] >= '0' && str[0] <= '9')
            {
                if (str.length() > 8)
                {
                    return true;
                }
                if (str.length() > 1 &&
                    str[0] == '0')
                {
                    return true;
                }
            }
        }
        return false;
    }

    static bool has_not_accepted_sign(vector<string> v_formula)
    {
        if (v_formula.size() >= 2)
        {
            if (
                v_formula[0] == "+" ||
                v_formula[0] == "-")
            {
                if (
                    v_formula[1] == "+" ||
                    v_formula[1] == "-")
                {
                    return true;
                }
            }
        }
        for (int i = 0; i + 2 < v_formula.size(); i++)
        {
            if (v_formula[i] == "*" ||
                v_formula[i] == "/" ||
                v_formula[i] == "+" ||
                v_formula[i] == "-")
            {
                if (
                    v_formula[i + 1] == "+" ||
                    v_formula[i + 1] == "-")
                {
                    if (
                        v_formula[i + 2] == "+" ||
                        v_formula[i + 2] == "-")
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
