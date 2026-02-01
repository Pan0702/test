#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

/*
Lesson15: GoFデザインパターン（Flyweight）
===========================================

難易度：高（「共有する状態」と「個別の状態」を分ける必要がある）

今日のゴール：
- Flyweight = 共有できる重いデータ（画像、メッシュ等）を使い回す
- “同じ見た目”のオブジェクトが大量にある時にメモリを節約できる
- 共有（Intrinsic）と個別（Extrinsic）を分けて設計する

ゲームでの例：
- タイル（同じ絵を大量配置）
- 同じモデルの敵が多数
- 同じフォントグリフ（文字）を多数描画
*/

static void PrintTitle(const std::string& s)
{
    std::cout << "\n==============================\n" << s << "\n==============================\n";
}

// 共有される重いデータ（例：テクスチャ/メッシュの代わりに文字列）
struct SpriteAsset
{
    std::string spriteName;

    explicit SpriteAsset(std::string n) : spriteName(std::move(n))
    {
        std::cout << "[Load] SpriteAsset: " << spriteName << "\n";
    }
};

// Flyweight Factory：同じキーなら同じ資産を返す
class SpriteAssetFactory
{
public:
    std::shared_ptr<SpriteAsset> Get(const std::string& key)
    {
        auto it = cache_.find(key);
        if (it != cache_.end())
            return it->second;

        auto asset = std::make_shared<SpriteAsset>(key);
        cache_[key] = asset;
        return asset;
    }

    size_t CacheSize() const { return cache_.size(); }

private:
    std::unordered_map<std::string, std::shared_ptr<SpriteAsset>> cache_;
};

// 個別状態（位置など）は“共有しない”
struct Tile
{
    int x = 0;
    int y = 0;
    std::shared_ptr<SpriteAsset> asset; // 共有資産
};

static void Explanation()
{
    PrintTitle("Lesson15 解説：Flyweight（共有でメモリ節約）");

    SpriteAssetFactory factory;

    // タイル100個を作る（同じ2種類の絵を使い回す）
    std::vector<Tile> tiles;
    tiles.reserve(100);

    for (int i = 0; i < 100; ++i)
    {
        Tile t;
        t.x = i % 10;
        t.y = i / 10;

        // 共有資産：grass と stone を使い回す
        t.asset = factory.Get((i % 2 == 0) ? "grass" : "stone");
        tiles.push_back(std::move(t));
    }

    std::cout << "tiles = " << tiles.size() << "\n";
    std::cout << "cache size (unique assets) = " << factory.CacheSize() << "  ※2になる\n";

    std::cout << "\nポイント：\n";
    std::cout << "- 重い部分（SpriteAsset）は共有する\n";
    std::cout << "- 位置などの個別状態はTile側に持つ（共有しない）\n";
}

static void Exercise()
{
    PrintTitle("Lesson15 体験（コメントのみ）");
    std::cout << "このレッスンの体験はコメントを読んで、自分でコードを編集して確認してください。\n";
}

/*
【体験（コメントのみ）】
1) タイルの種類を3種類（grass/stone/water）に増やして cache size を確認する
2) もし共有せずに毎回 new SpriteAsset したら何が起きるか説明する
3) 注意点をメモする
   - 共有すると「勝手に書き換え」できなくなる（const的な扱いが必要）
   - shared_ptr の参照管理が増える（設計ミスると循環参照）
*/

int main()
{
    Explanation();
    Exercise();
    return 0;
}
