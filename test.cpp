#define private public
#include "Formula.hpp"
#undef private

#include <string>
#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::vector;

template <class T>
class AreEqual
{
    string m_test_name;

public:
    AreEqual(string test_name) : m_test_name(test_name) {}
    AreEqual() : m_test_name("no name"){};
    void operator()(T a, T b)
    {
        if (a == b)
        {
            cout << "OK : " << m_test_name << std::endl;
        }
        else
        {
            cout << "NG : " << m_test_name << std::endl;
        }
    }
};

int main(void)
{
    /*test : has_not_accepted_character*/
    {
        
        AreEqual<bool>("has_not_accepted_character 1")(Formula::has_not_accepted_character(""), false);
        AreEqual<bool>("has_not_accepted_character 2")(Formula::has_not_accepted_character("あ"), true);
        AreEqual<bool>("has_not_accepted_character 3")(Formula::has_not_accepted_character("%"), true);
        AreEqual<bool>("has_not_accepted_character 4")(Formula::has_not_accepted_character("1"), false);
        AreEqual<bool>("has_not_accepted_character 5")(Formula::has_not_accepted_character("!222"), true);
        AreEqual<bool>("has_not_accepted_character 6")(Formula::has_not_accepted_character("222!"), true);
    }

    /*test : split*/
    {
        
        auto v = Formula::split("111 222");
        AreEqual<string>("split 1")(v[0], "111");
        AreEqual<string>("split 2")(v[1], "222");
        AreEqual<int>("split 3")(v.size(), 2);
        v = Formula::split("(111*222)");
        AreEqual<string>("split 4")(v[0], "(");
        AreEqual<string>("split 5")(v[1], "111");
        AreEqual<string>("split 6")(v[2], "*");
        AreEqual<string>("split 7")(v[3], "222");
        AreEqual<string>("split 8")(v[4], ")");
        AreEqual<int>("split 9")(v.size(), 5);
        v = Formula::split("");
        AreEqual<int>("split 10")(v.size(), 0);
        v = Formula::split("111");
        AreEqual<string>("split 11")(v[0], "111");
        AreEqual<int>("split 12")(v.size(), 1);
        v = Formula::split("   111   ");
        AreEqual<string>("split 13")(v[0], "111");
        AreEqual<int>("split 14")(v.size(), 1);
    }

    /*test : has_invalid_number*/
    {
        
        {
            vector<string> v = {"123"};
            AreEqual<bool>("has_invalid_number 1")(Formula::has_invalid_number(v), false);
        }
        {
            vector<string> v = {""};
            AreEqual<bool>("has_invalid_number 2")(Formula::has_invalid_number(v), false);
        }
        {
            vector<string> v = {"0123", "456"};
            AreEqual<bool>("has_invalid_number 3")(Formula::has_invalid_number(v), true);
        }
        {
            vector<string> v = {"123", "0456"};
            AreEqual<bool>("has_invalid_number 4")(Formula::has_invalid_number(v), true);
        }
        {
            vector<string> v = {"0"};
            AreEqual<bool>("has_invalid_number 5")(Formula::has_invalid_number(v), false);
        }
        {
            vector<string> v = {"12300000"};
            AreEqual<bool>("has_invalid_number 6")(Formula::has_invalid_number(v), false);
        }
        {
            vector<string> v = {"123000000"};
            AreEqual<bool>("has_invalid_number 7")(Formula::has_invalid_number(v), true);
        }
    }

    /*test : has_not_accepted_sign*/
    {
        
        {
            vector<string> v;
            AreEqual<bool>("has_not_accepted_sign 1")(Formula::has_not_accepted_sign(v), false);
        }
        {
            vector<string> v = {"+", "3"};
            AreEqual<bool>("has_not_accepted_sign 2")(Formula::has_not_accepted_sign(v), false);
        }
        {
            vector<string> v = {"+", "+", "3"};
            AreEqual<bool>("has_not_accepted_sign 3")(Formula::has_not_accepted_sign(v), true);
        }
        {
            vector<string> v = {"3", "+", "3"};
            AreEqual<bool>("has_not_accepted_sign 4")(Formula::has_not_accepted_sign(v), false);
        }
        {
            vector<string> v = {"3", "*", "+", "3"};
            AreEqual<bool>("has_not_accepted_sign 5")(Formula::has_not_accepted_sign(v), false);
        }
        {
            vector<string> v = {"3", "*", "+", "+", "3"};
            AreEqual<bool>("has_not_accepted_sign 6")(Formula::has_not_accepted_sign(v), true);
        }
    }

    /*test : Parsable_checker::is_accepted*/
    {
        {
            vector<string> v = {"3", "+", "3"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 1")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {"3", "+", "+", "3"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 2")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {"3", "+", "*", "3"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 3")(Formula_internal::Parsable_checker::is_accepted(v), false);
        }
        {
            vector<string> v = {"+"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 4")(Formula_internal::Parsable_checker::is_accepted(v), false);
        }
        {
            vector<string> v = {"++"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 5")(Formula_internal::Parsable_checker::is_accepted(v), false);
        }
        {
            vector<string> v = {"3"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 6")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {"3", "3"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 7")(Formula_internal::Parsable_checker::is_accepted(v), false);
        }
        {
            vector<string> v = {"+", "3"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 8")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {"(", "3", ")"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 9")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {"(", "+", "3", ")"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 10")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {"(", ")"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 11")(Formula_internal::Parsable_checker::is_accepted(v), false);
        }
        {
            vector<string> v = {"-", "(", "-", "(", "+", "3", ")", ")"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 12")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {")", "3", "("};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 13")(Formula_internal::Parsable_checker::is_accepted(v), false);
        }
        {
            vector<string> v = {"(", "3", ")", "+","-", "(", "3", ")"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 14")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
        {
            vector<string> v = {"3","*","(","3",")","+","(","3","+","4",")"};
            AreEqual<bool>("Formula_internal::Parsable_checker::is_accepted 15")(Formula_internal::Parsable_checker::is_accepted(v), true);
        }
    }

    /*test : Formula_internal::Calc::eval*/
    {
        {
            vector<string> v={"(","-","(","(","4","+","7",")","*","-","5",")",")"};
            AreEqual<double>("Formula_internal::Calc::eval 1")(Formula_internal::Calc::eval(v).second,(-((4+7)*-5)));
        }
        {
            vector<string> v={"(","-","(","(","4","+","7",")","*","-","5",")",")","/","0"};
            AreEqual<Formula_internal::Calc::Status>("Formula_internal::Calc::eval 2")(Formula_internal::Calc::eval(v).first,Formula_internal::Calc::Status::ZERO_DIV);
        }
        {
            vector<string> v={"(","2","-","4","+","5",")","*","4"};
            AreEqual<double>("Formula_internal::Calc::eval 3")(Formula_internal::Calc::eval(v).second,(2-4+5)*4);
        }
    }
    

    /*test : Formula::eval*/
    {
        AreEqual<pair<Formula::Status,double>>("Formula::eval 1")(Formula::eval("1+1"),{Formula::Status::SUCCESS,1+1});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 2")(Formula::eval("((1+1))"),{Formula::Status::SUCCESS,((1+1))});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 3")(Formula::eval("8*8* (8*90+ -2)"),{Formula::Status::SUCCESS,8*8* (8*90+ -2)});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 4")(Formula::eval("(0+0+1+  2-4+3)/5"),{Formula::Status::SUCCESS,(double(0+0+1+2-4+3))/5});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 5")(Formula::eval("((4*5)+(3+3))*(3*(9-2))+2"),{Formula::Status::SUCCESS,((4*5)+(3+3))*(3*(9-2))+2});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 6")(Formula::eval("(-((4+7)*-5))"),{Formula::Status::SUCCESS,(-((4+7)*-5))});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 7")(Formula::eval("4-(-3+5)*10"),{Formula::Status::SUCCESS,4-(-3+5)*10});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 7")(Formula::eval("4+3-+4"),{Formula::Status::SUCCESS,4+3-+4});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 7")(Formula::eval("3--4+-3"),{Formula::Status::SUCCESS,3+4-3});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 7")(Formula::eval("-1*-4+-3"),{Formula::Status::SUCCESS,-1*-4+-3});
        AreEqual<pair<Formula::Status,double>>("Formula::eval 7")(Formula::eval("(-(-(-(3*-(4*4)*(4+4)+(3))*-(4/3))*4/3*(-4--41)))"),{Formula::Status::SUCCESS,(-(-(-(3.0*-(4.0*4.0)*(4.0+4.0)+(3.0))*-(4.0/3.0))*4.0/3.0*(-4.0+41.0)))});

        AreEqual<Formula::Status>("Formula::eval 8")(Formula::eval("aaa+222").first,Formula::Status::CHARACTER_ERROR);
        AreEqual<Formula::Status>("Formula::eval 9")(Formula::eval("111111111").first,Formula::Status::NUMBER_ERROR);
        AreEqual<Formula::Status>("Formula::eval 10")(Formula::eval("11111111").first,Formula::Status::SUCCESS);
        AreEqual<Formula::Status>("Formula::eval 11")(Formula::eval("--3").first,Formula::Status::SIGN_ERROR);
        AreEqual<Formula::Status>("Formula::eval 12")(Formula::eval("-3").first,Formula::Status::SUCCESS);
        AreEqual<Formula::Status>("Formula::eval 13")(Formula::eval("4*--3").first,Formula::Status::SIGN_ERROR);
        AreEqual<Formula::Status>("Formula::eval 14")(Formula::eval("4*-3").first,Formula::Status::SUCCESS);
        AreEqual<Formula::Status>("Formula::eval 15")(Formula::eval("((3)").first,Formula::Status::PARSER_ERROR);
        AreEqual<Formula::Status>("Formula::eval 16")(Formula::eval("(3)").first,Formula::Status::SUCCESS);
        AreEqual<Formula::Status>("Formula::eval 17")(Formula::eval("0/0").first,Formula::Status::ZERO_DIV);
        AreEqual<Formula::Status>("Formula::eval 18")(Formula::eval("0/(4-2*2)").first,Formula::Status::ZERO_DIV);
    }


    return 0;
}