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
Lesson1: 変数・型・void/int/float/bool（DirectXを始める前に必須）

今日のゴール：
- int / float / bool / void の意味が言える
- 「関数の先頭の型」は“戻り値の型”だと理解する
*/

static int AddInt(int a, int b) { return a + b; }
static float AddFloat(float a, float b) { return a + b; }
static bool IsGameOver(int hp) { return hp <= 0; }
static void PrintHP(int hp) { std::cout << "HP = " << hp << "\n"; }

static void Explanation()
{
    PrintTitle("Lesson1 解説：型と返り値（void/int/float/bool）");

    int score = 10;
    float x = 1.5f;
    bool alive = true;

    std::cout << "score(int) = " << score << "\n";
    std::cout << "x(float)   = " << x << "\n";
    std::cout << "alive(bool)= " << alive << "\n";

    std::cout << "AddInt(2,3) = " << AddInt(2,3) << "\n";
    std::cout << "AddFloat(0.5, 1.25) = " << AddFloat(0.5f, 1.25f) << "\n";
    PrintHP(100);

    // よくある事故：int同士の割り算は小数にならない
    std::cout << "1/60 (int) = " << (1 / 60) << "  ※0になる\n";
    std::cout << "1.0f/60.0f (float) = " << (1.0f / 60.0f) << "\n";
}

static void Exercise()
{
    PrintTitle("Lesson1 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：型と返り値を自分で説明できるようにする

やること：
1) score / speed / isOver の「型」が適切か確認する
   - score は int（整数：スコア、残機など）
   - speed は float（小数：速度、座標など）
   - isOver は bool（真偽：状態フラグ）

2) 下の例を参考に、自分で1つ関数を作ってみる（戻り値あり）
   例：int Double(int x) { return x * 2; }

3) よくある事故を再現して、なぜ起きるか説明する
   - 1/60 が 0 になる理由（int同士の割り算）

メモ：
- DirectXのコードでも「型」と「関数の戻り値」は常に出てくる
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
