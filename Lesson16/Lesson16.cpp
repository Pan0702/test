#include <iostream>
#include <memory>
#include <string>

/*
Lesson16: GoFデザインパターン（State 応用）
===========================================

難易度：高（設計の話が増える）

このレッスンは Lesson13（State基礎）の続きとして、
「一時状態（Stun/HitStopなど）」「戻り先（前の状態）」「タイマー遷移」を扱います。

今日のゴール：
- 一時状態（例：Stun）に入った後、元の状態に戻る設計ができる
- 状態遷移が増えても責務を分けて保ちやすい
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n" << s << "\n==============================\n";
}

struct Player;

struct IState
{
    virtual ~IState() = default;
    virtual const char* Name() const = 0;
    virtual void Update(Player& p, float dt) = 0;
};

struct Player
{
    float x = 0.0f;
    float v = 0.0f;

    std::unique_ptr<IState> state;

    // “元に戻る” 用（一時状態の終了先）
    std::unique_ptr<IState> returnState;

    void Change(std::unique_ptr<IState> next)
    {
        state = std::move(next);
    }

    void PushTemporary(std::unique_ptr<IState> temp, std::unique_ptr<IState> backTo)
    {
        returnState = std::move(backTo);
        state = std::move(temp);
    }

    void PopTemporary()
    {
        if (returnState) state = std::move(returnState);
    }

    void Update(float dt) { state->Update(*this, dt); }
    void Draw() const
    {
        std::cout << "Draw: state=" << state->Name() << " x=" << x << " v=" << v << "\n";
    }
};

struct Walk : IState
{
    const char* Name() const override { return "Walk"; }
    void Update(Player& p, float dt) override
    {
        p.x += p.v * dt;
    }
};

struct Stun : IState
{
    float timer = 0.0f;
    explicit Stun(float sec) : timer(sec) {}

    const char* Name() const override { return "Stun"; }

    void Update(Player& p, float dt) override
    {
        // スタン中は動けない
        p.v = 0.0f;

        timer -= dt;
        if (timer <= 0.0f)
        {
            // 終了したら元の状態へ戻る
            p.PopTemporary();
        }
    }
};

static void Explanation()
{
    PrintTitle("Lesson16 解説：State 応用（スタン→復帰）");

    Player p;
    p.v = 2.0f;
    p.Change(std::make_unique<Walk>());

    float dt = 0.5f;

    for (int frame = 0; frame < 8; ++frame)
    {
        if (frame == 2)
        {
            // 2フレーム目でスタンに入る（1.0秒）
            // “戻り先” は Walk を保存しておく
            p.PushTemporary(std::make_unique<Stun>(1.0f), std::make_unique<Walk>());
        }

        p.Update(dt);
        p.Draw();
    }

    std::cout << "\nポイント：\n";
    std::cout << "- 一時状態（Stun）をスタックっぽく扱う\n";
    std::cout << "- タイマーで自動復帰ができる\n";
    std::cout << "- 状態が増えると設計の整理が重要になる\n";
}

static void Exercise()
{
    PrintTitle("Lesson16 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
1) Stun の時間を 2.0秒 にして、復帰が遅くなることを確認
2) “HitStop” 状態を追加する（短時間だけ更新を止める）
3) 追加課題（任意）
   - returnState を1つだけでなく「スタック（複数）」にしてみる
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
