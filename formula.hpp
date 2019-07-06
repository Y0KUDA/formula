#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <vector>

using std::string;
using std::vector;

class formula
{
public:
    formula(string s_formula) : m_formula(s_formula)
    {
        s_formula = this->m_formula;
    }
    string eval()
    {
        return m_formula;
    }

private:
    string m_formula;

    bool has_not_accepted_character(string formula)
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

    vector<string> split(string formula)
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

    bool has_invalid_mumber(vector<string> v_formula)
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

    bool has_not_accepted_sign(vector<string> v_formula)
    {
        for (int i = 0; i < v_formula.size() - 2; i++)
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
