#define private public
#include "formula.hpp"
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
        formula f("");
        AreEqual<bool>("has_not_accepted_character 1")(f.has_not_accepted_character(""), false);
        AreEqual<bool>("has_not_accepted_character 2")(f.has_not_accepted_character("あ"), true);
        AreEqual<bool>("has_not_accepted_character 3")(f.has_not_accepted_character("%"), true);
        AreEqual<bool>("has_not_accepted_character 4")(f.has_not_accepted_character("1"), false);
        AreEqual<bool>("has_not_accepted_character 5")(f.has_not_accepted_character("!222"), true);
        AreEqual<bool>("has_not_accepted_character 6")(f.has_not_accepted_character("222!"), true);
    }

    /*test : split*/
    {
        formula f("");
        auto v = f.split("111 222");
        AreEqual<string>("split 1")(v[0], "111");
        AreEqual<string>("split 2")(v[1], "222");
        AreEqual<int>("split 3")(v.size(), 2);
        v = f.split("(111*222)");
        AreEqual<string>("split 4")(v[0], "(");
        AreEqual<string>("split 5")(v[1], "111");
        AreEqual<string>("split 6")(v[2], "*");
        AreEqual<string>("split 7")(v[3], "222");
        AreEqual<string>("split 8")(v[4], ")");
        AreEqual<int>("split 9")(v.size(), 5);
        v = f.split("");
        AreEqual<int>("split 10")(v.size(), 0);
        v = f.split("111");
        AreEqual<string>("split 11")(v[0], "111");
        AreEqual<int>("split 12")(v.size(), 1);
        v = f.split("   111   ");
        AreEqual<string>("split 13")(v[0], "111");
        AreEqual<int>("split 14")(v.size(), 1);
    }

    /*test : has_invalid_mumber*/
    {
        formula f("");
        {
            vector<string> v = {"123"};
            AreEqual<bool>("has_invalid_mumber 1")(f.has_invalid_mumber(v), false);
        }
        {
            vector<string> v = {""};
            AreEqual<bool>("has_invalid_mumber 2")(f.has_invalid_mumber(v), false);
        }
        {
            vector<string> v = {"0123", "456"};
            AreEqual<bool>("has_invalid_mumber 3")(f.has_invalid_mumber(v), true);
        }
        {
            vector<string> v = {"123", "0456"};
            AreEqual<bool>("has_invalid_mumber 4")(f.has_invalid_mumber(v), true);
        }
        {
            vector<string> v = {"0"};
            AreEqual<bool>("has_invalid_mumber 5")(f.has_invalid_mumber(v), false);
        }
        {
            vector<string> v = {"12300000"};
            AreEqual<bool>("has_invalid_mumber 6")(f.has_invalid_mumber(v), false);
        }
        {
            vector<string> v = {"123000000"};
            AreEqual<bool>("has_invalid_mumber 7")(f.has_invalid_mumber(v), true);
        }
    }

    /*test : has_not_accepted_sign*/
    {
        formula f("");
        {
            vector<string> vv = {"+"};
            AreEqual<bool>("has_not_accepted_sign 7")(f.has_not_accepted_sign(vv), false);
        }
        {
            //vector<string> v = {"*+"};
            //AreEqual<bool>("has_not_accepted_sign 7")(f.has_not_accepted_sign(v), false);
        }
        {
            //vector<string> v = {"*++"};
            //AreEqual<bool>("has_not_accepted_sign 7")(f.has_not_accepted_sign(v), true);
        }
    }

    return 0;
}