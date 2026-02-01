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
Lesson5: コンストラクタ / デストラクタの役割（生成と破棄）

今日のゴール：
- コンストラクタ：生成時に1回（初期化）
- デストラクタ：破棄時に1回（後片付け）
- スコープを抜けたら自動でデストラクタが呼ばれることを体感
*/

struct FakeTexture
{
    // DirectXの本物のテクスチャではなく「例」としての擬似リソース
    std::string name;

    FakeTexture(const std::string& n) : name(n)
    {
        std::cout << "[Acquire] texture: " << name << "\n";
    }

    ~FakeTexture()
    {
        std::cout << "[Release] texture: " << name << "\n";
    }
};

class Player
{
public:
    // TODO(体験で触る)：コンストラクタで初期HPを設定する
    Player(int hp) : hp_(hp) {}

    void Damage(int amount)
    {
        hp_ -= amount;
        if (hp_ < 0) hp_ = 0;
    }

    int HP() const { return hp_; }

private:
    int hp_ = 0;
};

static void Explanation()
{
    PrintTitle("Lesson5 解説：コンストラクタ/デストラクタ");

    std::cout << "スコープ開始\n";
    {
        FakeTexture t("player_diffuse");
        std::cout << "スコープ内：ここで使う\n";
    }
    std::cout << "スコープ終了（ここで自動Releaseが走る）\n";

    Player p(100);
    p.Damage(30);
    std::cout << "Player HP = " << p.HP() << "\n";

    std::cout << "\nポイント：\n";
    std::cout << "- A a; はスコープで自動破棄\n";
    std::cout << "- new は手動破棄（delete）が必要になりやすい\n";
}

static void Exercise()
{
    PrintTitle("Lesson5 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：コンストラクタ/デストラクタが「いつ」「なぜ」呼ばれるか理解する

やること：
1) Player の初期HPを 150 にして、Damage(40) したときの HP を確認する
2) FakeTexture のログを見て、Acquire/Release のタイミングを説明する
   - スコープに入った時に Acquire
   - スコープを抜けた時に自動で Release（デストラクタ）

3) 追加課題（任意）
   - Player に「初期化が必要なメンバ」を増やして、コンストラクタで初期化する
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
