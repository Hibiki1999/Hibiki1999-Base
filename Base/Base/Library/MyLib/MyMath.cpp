#include "MyMath.h"

const float MyMath::Sqrt2 = 1.41421356237f;//(floatは有効桁は実質7桁まで正確だがそれ以降は環境によって誤差出るよ)

const float MyMath::PI = 3.14159265359f;

const float MyMath::Deg2Rad = PI / 180;

// 【ルールとして.hでfloatなどstatic小数などの初期化許さなかった理由】
// 一言
// 以下を一言でまとめると「.hヘッダはマシン環境によって変わるようなことは記述できない」
// PCやマシン語翻訳コンパイラによって小数の精度などや数値に誤差が出るから
// 環境によって変動する可能性のあるfloatなど(int整数は誤差がない)
// をstatic const静的定数として.hヘッダで初期化することを許可しなかった(定数といえない) 「マシン依存」
// cppで大丈夫なのはcppは実際の処理ベースで動くので【動的な動いてもよい数字となるから】(どの環境でも同じとは限らない)
// 【勉強】以下サイトにC++のBjarneさんの説明を翻訳したものがある
// https://qastack.jp/programming/9656941/why-cant-i-initialize-non-const-static-member-or-static-array-in-class