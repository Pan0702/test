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
Lesson3: VECTOR3 とは何か？（位置・方向・速度）

今日のゴール：
- Vector3 は (x,y,z) の集合で、位置/方向/速度に使うと理解する
- pos += vel * dt の意味が分かる
*/
#include "Vector3.h"

struct Actor
{
    Vector3 pos{0,0,0};
    Vector3 vel{1,0,0}; // x方向に1m/s

    void Update(float dt)
    {
        pos = Add(pos, Mul(vel, dt));
    }
};

static void Explanation()
{
    PrintTitle("Lesson3 解説：Vector3 と移動");

    Actor a;
    a.vel = Vector3{ 3.0f, 0.0f, 0.0f };

    float dt = 0.5f; // 0.5秒
    a.Update(dt);

    std::cout << "pos = (" << a.pos.x << ", " << a.pos.y << ", " << a.pos.z << ")\n";
    std::cout << "期待：xは 1.5（3.0 * 0.5）\n";
}

static void Exercise()
{
    PrintTitle("Lesson3 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：Vector3 を「位置/方向/速度」として扱えるようにする

やること：
1) pos += vel * dt の意味を説明する
   - vel が 2m/s、dt が 2s なら 4m 進む

2) Actor の vel を (0, 1, 0) にして y方向移動に変える
3) 追加課題（任意）
   - Length(vel) を表示して、速度の大きさ（スカラー）を理解する
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
