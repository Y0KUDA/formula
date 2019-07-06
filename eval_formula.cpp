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
            if (formula[i] != '*' ||
                formula[i] != '/' ||
                formula[i] != '+' ||
                formula[i] != '-' ||
                formula[i] != '(' ||
                formula[i] != ')' ||
                formula[i] != ' ' ||
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
            if (formula[i] != ' ')
            {
                continue;
            }
            else if (formula[i] != '*' ||
                     formula[i] != '/' ||
                     formula[i] != '+' ||
                     formula[i] != '-' ||
                     formula[i] != '(' ||
                     formula[i] != ')')
            {
                v_formula.push_back(string{formula[i]});
            }
            else if (formula[i] >= '0' && formula[i] <= '9')
            {
                for (int j = 0; j < formula.length(); j++)
                {
                    if (formula[j] != '*' ||
                        formula[j] != '/' ||
                        formula[j] != '+' ||
                        formula[j] != '-' ||
                        formula[j] != '(' ||
                        formula[j] != ')' ||
                        formula[j] != ' ' ||
                        formula[j] != '\0')
                    {
                        v_formula.push_back(formula.substr(i, j - i - 1));
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
};

int main()
{
    std::string str = "abcd";
    std::cout << str.length();
    return 0;
}
