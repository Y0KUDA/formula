# 四則演算プログラム
## 環境
* OS : Linux  
* コンパイラ : g++ (GCC) 8.2.1 20181127  
* その他ツール : make  

## ファイル
* eval_formula.cpp , Formula.hpp : プログラムのソースコード
* test.cpp : ユニットテスト用コード
* Makefile : make用ファイル
* README.md

## ビルド方法
以下コマンドを実行すると実行ファイルevalfが生成される。  
make

## 使用方法
以下のように引数に数式を渡す。  
./evalf "-3+4"

## 仕様
### 使用可能文字
* 演算子 : + , - , * , /
* 符号 : + , -
* 括弧 : ( , )
* 数字 : 0 ~ 9
* 空白 : ' '

### 符号
* 演算子と符号は並べて利用可能。
  - 4--4 は 4-(-4) として解釈される。
* 符号は2つ以上並べて利用不可。

### 数
* 利用可能な整数は8桁まで。
* 最大桁が0の整数は利用不可。
* 間に空白を含む数は利用不可。

### 各種メッセージ
* 「使用不可な文字が使われています。」
  - 使用可能文以外の文字が仕様されている場合に表示される。
* 「不正な数が使われています。」
  - 9桁以上、もしくは先頭の桁が0の整数が使われている場合に表示される。
* 「符号が2つ以上並んでいます。」
* 「構文が間違っています。」
* 「0除算が存在します。」
* 「不明なエラーが発生しました。」
* 「引数がありません。」

## 実装方針
1. 入力された式をトークン単位に分割する。
   - 4 * -35 / ( 22 + 3 )  ->  4,*,-,35,/,(,22,+,3,) 
2. プッシュダウンオートマトンを用いて、構文が正しいか検証する。
   - Parsable_checker::is_accepted に対応。
3. 以下関数を用いて式を評価する。いくつか例も合わせて示す。
   1. Calc::sign_formula : 符号と式を与えると乗算の式に変換する。
      * Calc::sign_formula(-,3+4)  ->  eval( -1*(3+4) )
   2. Calc::val_op_formula : 値と演算子と式を与えると、演算子に合わせて適切に分割する。
      * val_op_formula(5,+,3/4-5)  ->  5 + eval(3/4-5)
      * val_op_formula(5,/,(3+4)+3/4)  ->  val_op_formula( 5 / eval(3+4) , + , 3/4 )
      * val_op_formula(5,/,3/4+3/4)  ->  val_op_formula( 5 / eval(3/4) , + , 3/4 )
   3. Calc::eval : 式から値を求める。先頭のトークンに合わせて適切に処理する。
      * eval( (3+4)*4+5 )  ->  val_op_formula( eval(3+4) , * , 4+5 )
      * eval( -(3+4)/4+5 )  -> sign_formula( - , (3+4)/4+5 )
      * eval( 3+4/9 )  ->  val_op_formula( 3 , + , 4/9 )

