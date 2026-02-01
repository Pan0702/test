#include <iostream>
#include <string>

/*
Lesson8: 循環include（Circular Include）
========================================

「基礎じゃない気がする」と思うのは分かる。
でも現実は、C++初心者が DirectX を触って最初に死ぬ理由の上位にこれがいる。
つまり “基礎の顔をした地雷” です。

今日のゴール：
- 循環include が起きる理由を説明できる
- 前方宣言（forward declaration）で避けられる
- 「ヘッダは宣言だけ」「実装はcppでincludeして型の中身を見る」流れが分かる

よくある状況：
- A.h が B.h を include
- B.h が A.h を include
- include guard（#pragma once）で無限にはならないが、
  「型の中身が見えない（incomplete type）」でエラーになる
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n" << s << "\n==============================\n";
}

// “悪い例” はコンパイルが止まるので、ここでは説明だけ（必要なら #if 0 を外して地獄を体験）
#if 0
// BadA.h
#pragma once
#include "BadB.h"
class A { B b; }; // B のサイズが必要 -> B の定義が必要

// BadB.h
#pragma once
#include "BadA.h"
class B { A a; }; // A のサイズが必要 -> A の定義が必要
// → お互い相手の「中身」が必要で、終わる。
#endif

#include "GoodA.h"
#include "GoodB.h"

// 実装はcpp側に分離（GoodA.cpp / GoodB.cpp を参照）
void LinkAndGreet()
{
    A a("Alice");
    B b("Bob");

    a.Link(&b);
    b.Link(&a);

    a.HelloFromA();
    b.HelloFromB();
}

static void Explanation()
{
    PrintTitle("Lesson8 解説：循環includeを避ける定石");

    LinkAndGreet();

    std::cout << "\nポイント：\n";
    std::cout << "- ヘッダでは相手の“中身”が不要な形にする（ポインタ/参照）\n";
    std::cout << "- ヘッダでは前方宣言（class B;）で済ませる\n";
    std::cout << "- 相手のメンバ/関数を使う実装は cpp 側で include して書く\n";
}

static void Exercise()
{
    PrintTitle("Lesson8 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
1) #if 0 の “悪い例” を #if 1 にして、どういうエラーになるか確認する
   - どこで「型が不完全」と言われるか見る
   - どこで「再定義」や「循環」が起きてるか追う

2) A/B のどちらかが「値として持つ」(B b;) をしたくなったら、どう設計するべきか考える
   - 値で持つ＝サイズが必要＝完全型が必要
   - 多くの場合、所有関係を整理して “片側だけが所有” にする
   - それでも必要なら PImpl（ポインタ実装）などの手法を使う

3) 自分のプロジェクトで include が増えている場所を見つけて、前方宣言にできるか検討する
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
