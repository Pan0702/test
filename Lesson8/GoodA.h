#pragma once
#include <string>

// Forward declaration（前方宣言）
// "class B;" と書くと、「Bという型が存在する」ことだけを知らせられる。
// これで A.h は B.h を include しなくて済む（循環を避けられる）。
class B;

class A
{
public:
    explicit A(std::string name) : name_(std::move(name)) {}

    // B の実体（サイズ）はここでは不要なので、参照/ポインタで持つのが基本。
    void Link(B* b) { b_ = b; }

    const std::string& Name() const { return name_; }

    void HelloFromA() const;

private:
    std::string name_;
    B* b_ = nullptr; // 「借りる」だけ（所有しない）という想定
};
