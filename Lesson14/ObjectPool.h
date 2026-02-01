#pragma once
#include <vector>
#include <memory>
#include <iostream>

// Object Pool の簡易版：
// - あらかじめ N 個作っておく
// - 使うとき Acquire() で取り出す（使用中フラグ）
// - 使い終わったら Release() で返す
// 本物のゲームだと「弾」「エフェクト」「一時オブジェクト」でよく使う。

template<class T>
class ObjectPool
{
public:
    explicit ObjectPool(size_t initialCount)
    {
        items_.reserve(initialCount);
        inUse_.reserve(initialCount);
        for (size_t i = 0; i < initialCount; ++i)
        {
            items_.push_back(std::make_unique<T>());
            inUse_.push_back(false);
        }
    }

    // 使えるものを探して返す（無ければ nullptr）
    T* Acquire()
    {
        for (size_t i = 0; i < items_.size(); ++i)
        {
            if (!inUse_[i])
            {
                inUse_[i] = true;
                return items_[i].get();
            }
        }
        return nullptr;
    }

    void Release(T* ptr)
    {
        for (size_t i = 0; i < items_.size(); ++i)
        {
            if (items_[i].get() == ptr)
            {
                inUse_[i] = false;
                return;
            }
        }
    }

    size_t Capacity() const { return items_.size(); }
    size_t InUseCount() const
    {
        size_t c = 0;
        for (bool b : inUse_) if (b) ++c;
        return c;
    }

private:
    std::vector<std::unique_ptr<T>> items_;
    std::vector<bool> inUse_;
};
