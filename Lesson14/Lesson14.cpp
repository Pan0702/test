#include <iostream>
#include <string>
#include "ObjectPool.h"

/*
Lesson14: デザインパターン（Object Pool）
==========================================

難易度：中～高（便利だが、管理ミスがバグになる）

今日のゴール：
- Object Pool = 「使い回し」で new/delete を減らし、フレーム落ちを避ける
- 弾/エフェクト/一時オブジェクトを大量生成するゲームで特に有効
- ただし、Release忘れや二重Releaseなど事故が起きやすい

このレッスンは「最小の概念モデル」です。
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n" << s << "\n==============================\n";
}

struct Bullet
{
    float x = 0.0f;
    float v = 10.0f;
    bool active = false;

    void Fire(float startX)
    {
        x = startX;
        active = true;
    }

    void Update(float dt)
    {
        if (!active) return;
        x += v * dt;
        if (x > 30.0f) active = false; // 画面外で消えたことにする
    }
};

static void Explanation()
{
    PrintTitle("Lesson14 解説：Object Pool");

    ObjectPool<Bullet> pool(3); // 3発分だけ用意
    std::cout << "capacity = " << pool.Capacity() << "\n";

    // 3発撃つ
    Bullet* b1 = pool.Acquire(); if (b1) b1->Fire(0);
    Bullet* b2 = pool.Acquire(); if (b2) b2->Fire(0);
    Bullet* b3 = pool.Acquire(); if (b3) b3->Fire(0);

    // 4発目は取れない（空きがない）
    Bullet* b4 = pool.Acquire();
    std::cout << "4th acquire = " << (b4 ? "OK" : "NULL (no free)") << "\n";
    std::cout << "in use = " << pool.InUseCount() << "\n";

    // 更新して弾を“自然消滅”させる
    float dt = 1.0f;
    for (int i = 0; i < 5; ++i)
    {
        if (b1) b1->Update(dt);
        if (b2) b2->Update(dt);
        if (b3) b3->Update(dt);
    }

    // 本当のゲームなら active==false を見て Release する
    if (b1 && !b1->active) pool.Release(b1);
    if (b2 && !b2->active) pool.Release(b2);
    if (b3 && !b3->active) pool.Release(b3);

    std::cout << "after release, in use = " << pool.InUseCount() << "\n";

    // 空きができたので再取得できる
    Bullet* b5 = pool.Acquire();
    std::cout << "acquire after release = " << (b5 ? "OK" : "NULL") << "\n";

    std::cout << "\nポイント：\n";
    std::cout << "- new/delete を毎回やらない\n";
    std::cout << "- Release忘れがあると、永遠に空きが増えない\n";
}

static void Exercise()
{
    PrintTitle("Lesson14 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
1) “Release忘れ” をわざと作って、何が起きるか確認する（空きが増えない）
2) active==false になった弾を自動で Release するループを作る
   - Bullet* を配列で持つ、など工夫してみる
3) 注意点をメモする
   - Acquire/Release の対応が崩れるとバグになる
   - マルチスレッドだとさらに難しい（今回は考えない）
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
