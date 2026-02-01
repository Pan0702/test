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
Lesson4: const参照（const T&）とは？なぜ必要？

今日のゴール：
- const参照 =「コピーせず借りる＋変更しない保証」だと説明できる
- 値渡しが重いケース（string/vector/大きいstruct）で const& を使える
*/

struct HeavyData
{
    std::vector<int> payload;

    // コピーが起きたか分かるようにカウンタ
    static int copyCount;

    HeavyData() : payload(100000, 1) {}

    HeavyData(const HeavyData& other) : payload(other.payload)
    {
        copyCount++;
    }
};
int HeavyData::copyCount = 0;

static int SumByValue(HeavyData data) // 値渡し：コピーが発生しやすい
{
    long long sum = 0;
    for (int v : data.payload) sum += v;
    return static_cast<int>(sum);
}

static int SumByConstRef(const HeavyData& data) // const参照：コピーしない
{
    long long sum = 0;
    for (int v : data.payload) sum += v;
    return static_cast<int>(sum);
}

static void Explanation()
{
    PrintTitle("Lesson4 解説：const参照（コピーを避ける）");

    HeavyData::copyCount = 0;
    HeavyData h;

    std::cout << "値渡しで呼ぶ...\n";
    (void)SumByValue(h);
    std::cout << "copyCount = " << HeavyData::copyCount << "（1以上になりがち）\n";

    HeavyData::copyCount = 0;
    std::cout << "const参照で呼ぶ...\n";
    (void)SumByConstRef(h);
    std::cout << "copyCount = " << HeavyData::copyCount << "（0のはず）\n";

    std::cout << "\nポイント：\n";
    std::cout << "- 大きいデータを関数に渡すなら const T& が基本\n";
    std::cout << "- const が付くと関数内で data を変更できない（安全）\n";
}

static void Exercise()
{
    PrintTitle("Lesson4 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。
";
}

/*
【体験（コメントのみ）】
目的：const参照（const T&）を使う理由を説明できるようにする

やること：
1) 「値渡し」と「const参照渡し」の違いを言葉で説明する
   - 値渡し：コピーが起きやすい（重い）
   - const参照：コピーしない＋変更しない保証

2) DirectXっぽい例に置き換える
   - 大きい構造体（行列、頂点配列、文字列）を関数に渡すときは const&

3) 自分のプロジェクトで「値渡しになっている重い引数」を探して
   const& にできないか検討する（変更しない引数限定）
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
