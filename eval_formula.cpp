#include <iostream>
#include "Formula.hpp"
using std::cout;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "引数がありません。" << std::endl;
        return 0;
    }
    auto result = Formula::eval(argv[1]);
    switch (result.first)
    {
    case Formula::Status::CHARACTER_ERROR:
        cout << "使用不可な文字が使われています。" << std::endl;
        break;
    case Formula::Status::NUMBER_ERROR:
        cout << "不正な数が使われています。" << std::endl;
        break;
    case Formula::Status::SIGN_ERROR:
        cout << "符号が2つ以上並んでいます。" << std::endl;
        break;
    case Formula::Status::PARSER_ERROR:
        cout << "構文が間違っています。" << std::endl;
        break;
    case Formula::Status::ZERO_DIV:
        cout << "0除算が存在します。" << std::endl;
        break;
    case Formula::Status::UNKNOWN_ERROR:
        cout << "不明なエラーが発生しました。" << std::endl;
        break;
    case Formula::Status::SUCCESS:
        cout << result.second << std::endl;
        break;
    default:
        break;
    }

    return 0;
}
