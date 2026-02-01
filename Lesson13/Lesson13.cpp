#include <iostream>
#include <string>
#include <memory>
#include <chrono>

/*
Lesson13: GoFデザインパターン（Stateパターン）
============================================

DirectX/ゲーム開発でよく出てくる「状態（Idle/Walk/Attack）」の管理を、
if/switchの巨大化から救うのが GoF の State パターンです。

今日のゴール：
- GoF（Gang of Four）のデザインパターンが「設計の型」だと理解する
- Stateパターンで「状態ごとの処理」「状態遷移」を分離できる
- Update/Draw（ここではDrawは出力）に自然に乗る形を体験する

なぜ必要？
- if/switch で state を分岐すると、状態が増えるほど「変更が怖い」構造になる
- Stateパターンだと「状態を追加＝クラス追加」で済みやすい（責務が分かれる）
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n";
    std::cout << s << "\n";
    std::cout << "==============================\n";
}

struct Player;

// Stateインターフェース（GoFの典型）
struct IPlayerState
{
    virtual ~IPlayerState() = default;
    virtual const char* Name() const = 0;
    virtual void Update(Player& p, float dt) = 0;
};

// プレイヤー本体（状態を「持つ」側）
struct Player
{
    float x = 0.0f;
    float v = 0.0f; // 速度（0ならIdle、0以外ならWalkにする例）

    std::unique_ptr<IPlayerState> state;

    void ChangeState(std::unique_ptr<IPlayerState> next)
    {
        state = std::move(next);
    }

    void Update(float dt)
    {
        // 状態に丸投げ（ここがポイント）
        state->Update(*this, dt);
    }

    void Draw() const
    {
        std::cout << "Draw: state=" << state->Name() << "  x=" << x << "  v=" << v << "\n";
    }
};

// 具体State：Idle
struct IdleState : IPlayerState
{
    const char* Name() const override { return "Idle"; }

    void Update(Player& p, float dt) override
    {
        (void)dt;
        // Idle中は止まってるだけ。例として摩擦で速度を0に寄せる（0のままだけど）
        p.v = 0.0f;

        // 状態遷移：速度が付いたら Walk へ
        if (p.v != 0.0f)
        {
            // この例ではここに来ないが、現実だと入力で速度が変わる
        }
    }
};

// 具体State：Walk
struct WalkState : IPlayerState
{
    const char* Name() const override { return "Walk"; }

    void Update(Player& p, float dt) override
    {
        // Walk中は移動
        p.x += p.v * dt;

        // 状態遷移：速度が0になったら Idle へ
        if (p.v == 0.0f)
        {
            p.ChangeState(std::make_unique<IdleState>());
        }
    }
};

static void Explanation()
{
    PrintTitle("Lesson13 解説：Stateパターン（GoF）");

    Player p;
    p.ChangeState(std::make_unique<IdleState>());

    // 簡易ゲームループ：数フレーム回す
    // ここでは「途中で速度を変える＝入力が入った」ことにする
    float dt = 0.5f; // 0.5秒/フレーム（雑）

    for (int frame = 0; frame < 6; ++frame)
    {
        if (frame == 1)
        {
            // 入力が入って歩き始めた（と仮定）
            p.v = 2.0f;
            p.ChangeState(std::make_unique<WalkState>());
        }
        if (frame == 4)
        {
            // 入力が止まった（と仮定）
            p.v = 0.0f;
            // WalkStateのUpdate内で Idle に戻る
        }

        p.Update(dt);
        p.Draw();
    }

    std::cout << "\nポイント：\n";
    std::cout << "- Player::Update は state->Update を呼ぶだけ\n";
    std::cout << "- 状態ごとの処理（Idle/Walk）と遷移がクラスに分かれる\n";
    std::cout << "- 状態が増えても switch が爆発しにくい\n";
}

static void Exercise()
{
    PrintTitle("Lesson13 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
目的：Stateパターンを「自分のゲームのState」に置き換えられるようにする

やること：
1) IdleState / WalkState の Update を読んで、責務（何を担当しているか）を説明する
   - Idle：止まっている間の処理
   - Walk：移動中の処理
   - 遷移条件（v==0 など）もState側にある

2) 新しい状態を1つ追加する（例：AttackState）
   - Name() は "Attack"
   - Update で一定時間経過したら Idle に戻る（タイマーを使う）
   - 実行して状態が切り替わるログを確認する

3) 追加課題（任意）：switch版を書いてみて、どっちが変更しやすいか比べる
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
