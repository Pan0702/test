#include <iostream>
#include <string>

/*
Lesson10: GoFデザインパターン（Singleton）
============================================

難易度：低（仕組みは単純） ただし「乱用すると保守が崩壊」する危険あり。

今日のゴール：
- Singleton = 「インスタンスが1つだけ」になるようにする設計の型
- どこからでも同じインスタンスにアクセスできる（便利）
- ただし依存が増えるので、使いどころを意識する（テスト/保守）

ゲームでの例：
- 設定（Config）
- ログ（Logger）
- サウンド管理（AudioManager）※大規模になると依存設計が重要
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n" << s << "\n==============================\n";
}

class Logger
{
public:
    // Singleton: ここで「唯一のインスタンス」を返す
    static Logger& Instance()
    {
        static Logger inst; // 初回呼び出しで生成され、プログラム終了まで生きる
        return inst;
    }

    void Log(const std::string& msg)
    {
        std::cout << "[LOG] " << msg << "\n";
    }

private:
    Logger() = default;                 // 外部から new できない
    Logger(const Logger&) = delete;     // コピー禁止
    Logger& operator=(const Logger&) = delete;
};

static void Explanation()
{
    PrintTitle("Lesson10 解説：Singleton");

    Logger::Instance().Log("start");
    Logger::Instance().Log("player spawned");

    // 同じインスタンスか確認（アドレスが同じ）
    Logger* a = &Logger::Instance();
    Logger* b = &Logger::Instance();
    std::cout << "same instance? " << (a == b) << "\n";

    std::cout << "\nポイント：\n";
    std::cout << "- Instance() が唯一の入口\n";
    std::cout << "- static Logger inst は1回だけ生成される\n";
    std::cout << "- 便利だけど、何でもSingletonにすると依存関係が絡まって死ぬ\n";
}

static void Exercise()
{
    PrintTitle("Lesson10 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
1) Logger にカウンタを追加して、Logが呼ばれた回数を表示する
2) 「ゲーム設定」っぽい Singleton（Config）を作ってみる
   - 例：画面幅/高さ、音量、難易度など
3) 注意点をメモする
   - どこからでもアクセス可能＝依存が見えにくい
   - テストしにくくなる（差し替えが難しい）
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
