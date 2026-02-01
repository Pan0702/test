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
Lesson9: Update / Draw はいつ呼ばれてるのか？（ゲームループ）

今日のゴール：
- Update/Draw は「毎フレーム」メインループから呼ばれていると理解する
- Update：状態更新（座標、AI、当たり判定）
- Draw：描画（描く、だけ）
*/

struct SimpleObject
{
    float x = 0.0f;
    float v = 2.0f; // 速度

    void Update(float dt)
    {
        // 状態更新
        x += v * dt;
    }

    void Draw() const
    {
        // 描画（ここでは出力で代用）
        std::cout << "Draw: x=" << x << "\n";
    }
};

static void Explanation()
{
    PrintTitle("Lesson9 解説：Update/Draw とゲームループ");

    SimpleObject obj;

    using clock = std::chrono::steady_clock;
    auto prev = clock::now();

    // 例：10フレームだけ回す
    for (int frame = 0; frame < 10; ++frame)
    {
        auto now = clock::now();
        std::chrono::duration<float> dt = now - prev;
        prev = now;

        // 重要：呼んでるのは “このループ”
        obj.Update(dt.count());
        obj.Draw();
    }

    std::cout << "\nポイント：\n";
    std::cout << "- Update/Draw は勝手に呼ばれない\n";
    std::cout << "- 自分（またはフレームワーク）のメインループが呼ぶ\n";
}

static void Exercise()
{
    PrintTitle("Lesson9 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：Update/Draw が「メインループから毎フレーム呼ばれている」ことを体感する

やること：
1) Update → Draw の順番で呼ぶ理由を説明する
   - Update：状態更新（座標、AI、当たり判定）
   - Draw：その状態を描く

2) 実際のDirectXアプリの流れを紙に書く
   - メッセージ処理（Windows）
   - 何も無い時に 1フレーム進める（Update/Draw）

3) 追加課題（任意）
   - Update を 2回呼んだらどうなる？ Draw を 2回呼んだらどうなる？
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
