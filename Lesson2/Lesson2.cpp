#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <memory>
#include <algorithm>

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n";
    std::cout << s << "\n";
    std::cout << "==============================\n";
}

static void Expect(bool cond, const std::string& msg)
{
    if (cond) std::cout << "[PASS] " << msg << "\n";
    else      std::cout << "[FAIL] " << msg << "\n";
}

/*
Lesson2: 関数の書き方（引数・戻り値・切り出し）

今日のゴール：
- 関数は「入力(引数) -> 処理 -> 出力(戻り値)」だと理解する
- 何を return するべきか判断できる
- Update(dt) の dt が何かイメージできる
*/

// 距離（2D）
static float Distance2D(float ax, float ay, float bx, float by)
{
    float dx = bx - ax;
    float dy = by - ay;
    return std::sqrt(dx * dx + dy * dy);
}

// 画面内に収める（クランプ）
static float Clamp(float v, float minV, float maxV)
{
    if (v < minV) return minV;
    if (v > maxV) return maxV;
    return v;
}

static void Explanation()
{
    PrintTitle("Lesson2 解説：関数（引数・戻り値）");

    float d = Distance2D(0, 0, 3, 4);
    std::cout << "Distance2D(0,0)-(3,4) = " << d << "  ※5になる\n";

    float x = 120.0f;
    x = Clamp(x, 0.0f, 100.0f);
    std::cout << "Clamp(120,0,100) = " << x << "\n";

    std::cout << "\nポイント：\n";
    std::cout << "- return が必要なのは「値を外に渡したい」時\n";
    std::cout << "- 何かを表示するだけなら void でもOK\n";
}

static void Exercise()
{
    PrintTitle("Lesson2 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：関数を「入力→処理→出力」で組み立てられるようにする

やること：
1) Clamp(v, minV, maxV) を自分で実装して説明する
   - v < minV なら minV
   - v > maxV なら maxV
   - それ以外は v

2) ゲーム例に置き換える
   - 画面外に出ないように座標 x を Clamp する
   - HP が 0～最大HP を超えないように Clamp する

3) 追加課題（任意）
   - Distance2D を Vec2 構造体版にしてみる（Lesson6の前準備）
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
