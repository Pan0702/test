#include "GoodA.h"
#include "GoodB.h"
#include <iostream>

// ここ（.cpp）で相手のヘッダを include すれば、型の中身が見える。
// メンバ関数の実装で b_->Name() を呼ぶには B の定義が必要。
void A::HelloFromA() const
{
    std::cout << "A(" << name_ << ") says hello";
    if (b_) std::cout << " to B(" << b_->Name() << ")";
    std::cout << "\n";
}
