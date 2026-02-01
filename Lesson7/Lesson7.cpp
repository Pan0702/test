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
Lesson7: スマートポインタ（unique_ptr）で安全に管理する

今日のゴール：
- new/delete を直書きしないで管理できる（事故を減らす）
- vector<unique_ptr<T>> で「大量オブジェクト」を扱う基本が分かる
*/

struct Enemy
{
    int hp = 3;
    explicit Enemy(int h) : hp(h) {}
    void Update() { hp--; }
    bool IsDead() const { return hp <= 0; }
};

static void Explanation()
{
    PrintTitle("Lesson7 解説：unique_ptr とオブジェクト管理");

    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Enemy>(2));
    enemies.push_back(std::make_unique<Enemy>(1));

    // 更新
    for (auto& e : enemies) e->Update();

    // 死んだ敵を削除（erase-remove）
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e){ return e->IsDead(); }),
        enemies.end()
    );

    std::cout << "残った敵の数 = " << enemies.size() << "\n";
    std::cout << "ポイント：deleteを書いてないのに安全に片付く\n";
}

static void Exercise()
{
    PrintTitle("Lesson7 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：unique_ptr で安全に大量オブジェクトを管理する

やること：
1) enemies に make_unique<Enemy>(3) と make_unique<Enemy>(1) を追加する
2) Update で hp が減る流れと、erase-remove で削除される流れを説明する
3) 追加課題（任意）
   - Enemy に position(Vector3) を持たせて、Updateで動かす（Lesson6と合体）
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
