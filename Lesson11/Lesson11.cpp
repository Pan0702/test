#include <iostream>
#include <memory>
#include <string>

/*
Lesson11: GoFデザインパターン（Factory Method）
================================================

難易度：中（でもゲームで超使う）

今日のゴール：
- 「生成（new）を直接書かない」設計を理解する
- 生成ロジックを1箇所に集めて、呼び出し側をシンプルにする
- 新しい種類を追加しても、使う側の変更を最小にする

ゲームでの例：
- Enemyを種類（Slime/Goblin/Boss）で生成する
- 弾を種類（Normal/Homing/Spread）で生成する
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n" << s << "\n==============================\n";
}

struct Enemy
{
    virtual ~Enemy() = default;
    virtual const char* Name() const = 0;
    virtual void Update() = 0;
};

struct Slime : Enemy
{
    const char* Name() const override { return "Slime"; }
    void Update() override { std::cout << "Slime: bounce\n"; }
};

struct Goblin : Enemy
{
    const char* Name() const override { return "Goblin"; }
    void Update() override { std::cout << "Goblin: chase\n"; }
};

// Factory Method（生成を1箇所へ）
class EnemyFactory
{
public:
    virtual ~EnemyFactory() = default;
    virtual std::unique_ptr<Enemy> CreateEnemy() = 0;
};

class SlimeFactory : public EnemyFactory
{
public:
    std::unique_ptr<Enemy> CreateEnemy() override
    {
        return std::make_unique<Slime>();
    }
};

class GoblinFactory : public EnemyFactory
{
public:
    std::unique_ptr<Enemy> CreateEnemy() override
    {
        return std::make_unique<Goblin>();
    }
};

static void Explanation()
{
    PrintTitle("Lesson11 解説：Factory Method");

    std::unique_ptr<EnemyFactory> factory;

    factory = std::make_unique<SlimeFactory>();
    auto e1 = factory->CreateEnemy();
    std::cout << "spawn: " << e1->Name() << "\n";
    e1->Update();

    factory = std::make_unique<GoblinFactory>();
    auto e2 = factory->CreateEnemy();
    std::cout << "spawn: " << e2->Name() << "\n";
    e2->Update();

    std::cout << "\nポイント：\n";
    std::cout << "- 生成（new）はFactoryに閉じ込める\n";
    std::cout << "- 呼び出し側は CreateEnemy() を呼ぶだけ\n";
    std::cout << "- 種類追加はFactory追加で済みやすい\n";
}

static void Exercise()
{
    PrintTitle("Lesson11 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
1) 新しい敵（Boss）を追加する
   - Boss : Enemy を作る
   - BossFactory : EnemyFactory を作る
2) main（Explanation）で BossFactory を使って生成してみる
3) 「switchで生成する版」と比べて、どちらが変更しやすいかメモする
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
