#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"
#include <unordered_map>//辞書配列

enum class Pad
{
    All = -2, // すべてのうちどれか1つでも押されたとき
    None = -1,
    Key = 0, // キーボード
    One,
    Two,
    Three,
    Four,
    NUM,
};

// 入力クラス
class Input
{
public:
    static int prevStates[(int)Pad::NUM]; // 1フレーム前の状態
    static int currentStates[(int)Pad::NUM]; // 現在の状態

    static std::unordered_map<int, int> padDic;

    static void InitPadDictionary();//辞書配列の初期化

    // 初期化。最初に1回だけ呼んでください。
    static void Init();

    // 最新の入力状況に更新する処理。
    // 毎フレームの最初に（ゲームの処理より先に）呼んでください。
    static void Update();

    // ボタンが押されているか？
    static bool GetButton(Pad pad, int buttonId);

    // ボタンが押された瞬間か？
    static bool GetButtonDown(Pad pad, int buttonId);

    // ボタンが離された瞬間か？
    static bool GetButtonUp(Pad pad, int buttonId);
};

#endif
