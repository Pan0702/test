#pragma once
#include <string>

// “¯‚¶‚­‘O•ûéŒ¾‚ÅzŠÂ‚ğ”ğ‚¯‚é
class A;

class B
{
public:
    explicit B(std::string name) : name_(std::move(name)) {}

    void Link(A* a) { a_ = a; }

    const std::string& Name() const { return name_; }

    void HelloFromB() const;

private:
    std::string name_;
    A* a_ = nullptr;
};
