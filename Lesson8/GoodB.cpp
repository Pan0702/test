#include "GoodB.h"
#include "GoodA.h"
#include <iostream>

void B::HelloFromB() const
{
    std::cout << "B(" << name_ << ") says hello";
    if (a_) std::cout << " to A(" << a_->Name() << ")";
    std::cout << "\n";
}
