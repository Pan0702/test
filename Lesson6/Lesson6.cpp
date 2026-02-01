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
Lesson6: ポインタと動的確保（new/delete）、new A と A a の違い

今日のゴール：
- A a は「スタック」：スコープで自動破棄（デストラクタが呼ばれる）
- new A は「ヒープ」：手動で delete が必要（忘れるとリーク）
- nullptr チェックができる
*/

struct Counter
{
    static int alive;
    Counter()  { alive++; }
    ~Counter() { alive--; }
};
int Counter::alive = 0;

static void StackExample()
{
    Counter c; // スタック：関数を抜けたら自動破棄
}

static void HeapExample_Leak()
{
    // ヒープ：deleteしないと alive が減らない（リークの例）
    Counter* c = new Counter();
    (void)c;
    // delete c; // これが無いとリーク
}

static void HeapExample_NoLeak()
{
    Counter* c = new Counter();
    delete c;
    c = nullptr;
}

static void Explanation()
{
    PrintTitle("Lesson6 解説：new A と A a の違い");

    Counter::alive = 0;
    StackExample();
    std::cout << "StackExample後 alive=" << Counter::alive << "（0のはず）\n";

    Counter::alive = 0;
    HeapExample_Leak();
    std::cout << "HeapExample_Leak後 alive=" << Counter::alive << "（1のまま＝リーク）\n";

    Counter::alive = 0;
    HeapExample_NoLeak();
    std::cout << "HeapExample_NoLeak後 alive=" << Counter::alive << "（0のはず）\n";
}

static void Exercise()
{
    PrintTitle("Lesson6 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：new/delete と、new A と A a の違いを説明できるようにする

やること：
1) 「スタック」と「ヒープ」の寿命の違いを説明する
   - A a：スコープを抜けると自動破棄（安全）
   - new A：delete しないと破棄されない（リーク）

2) HeapExample_Leak を「リークしない」ように書き直す（deleteする）
3) 追加課題（任意）
   - nullptr を使う理由（誤って使わないため）を説明する
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
