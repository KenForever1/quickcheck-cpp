#include "quickcheck.hpp"

// 示例：测试 reverse 函数的属性
bool testReverseProperty(const std::vector<int> &xs)
{
    std::vector<int> rev = xs;
    std::reverse(rev.begin(), rev.end());
    std::vector<int> revRev = rev;
    std::reverse(revRev.begin(), revRev.end());
    return revRev == xs;
}

int main()
{
    // 测试 reverse 函数的属性
    QuickCheck::check<std::vector<int>>(
        "reverse(reverse(xs)) == xs",
        testReverseProperty);

    return 0;
}