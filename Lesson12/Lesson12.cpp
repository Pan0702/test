#include <iostream>
#include <vector>
#include <functional>
#include <string>

/*
Lesson12: GoFデザインパターン（Observer）
==========================================

難易度：中（イベント通知の考え方が必要）

今日のゴール：
- Observer = 「ある変化を複数の相手に通知する」仕組み
- 発行側（Subject）と受け手（Observer）を疎結合にする

ゲームでの例：
- HPが変わったらUI更新
- スコアが増えたらUI更新
- アイテム取得でSE再生、実績更新、ログ出力…などを同時にやる
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n" << s << "\n==============================\n";
}

class EventInt
{
public:
    using Callback = std::function<void(int)>;

    int Subscribe(Callback cb)
    {
        observers_.push_back(std::move(cb));
        return static_cast<int>(observers_.size() - 1);
    }

    void Notify(int value)
    {
        for (auto& cb : observers_) cb(value);
    }

private:
    std::vector<Callback> observers_;
};

class Player
{
public:
    EventInt OnHPChanged;

    void Damage(int amount)
    {
        hp_ -= amount;
        if (hp_ < 0) hp_ = 0;
        OnHPChanged.Notify(hp_);
    }

    int HP() const { return hp_; }

private:
    int hp_ = 100;
};

static void Explanation()
{
    PrintTitle("Lesson12 解説：Observer（イベント通知）");

    Player p;

    // UI（っぽい）購読者
    p.OnHPChanged.Subscribe([](int hp){
        std::cout << "[UI] HP = " << hp << "\n";
    });

    // ログ購読者
    p.OnHPChanged.Subscribe([](int hp){
        std::cout << "[LOG] HP changed -> " << hp << "\n";
    });

    p.Damage(30);
    p.Damage(80);

    std::cout << "\nポイント：\n";
    std::cout << "- Playerは「通知する」だけ。誰が受け取るかは知らない\n";
    std::cout << "- 受け手を追加しても Player を変更しなくていい\n";
}

static void Exercise()
{
    PrintTitle("Lesson12 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
1) OnHPChanged に「ゲームオーバー判定」購読者を追加する
   - hp==0 になったら "[GAME] GAME OVER" を表示
2) スコア用の EventInt OnScoreChanged を Player に追加してみる
3) 注意点をメモする
   - 通知先が増えるほど「どこで何が起きるか」追いにくい（ログが大事）
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
