#include "rand_generator.hpp"
#include "coverage_tracker.hpp"

#include <string>
#include <algorithm>
#include <fmt/ranges.h>
#include <functional>

// QuickCheck class
class QuickCheck
{
public:
    template <typename T, typename Func>
        requires RandomGeneratable<T> && PropertyTestable<Func, T>
    static bool check(const std::string &propertyName, Func &&property, int numTests = 100)
    {
        fmt::print("Testing property: {}\n", propertyName);
        CoverageTracker<T> tracker; // 统计测试覆盖率
        for (int i = 0; i < numTests; ++i)
        {
            T input = RandomGenerator<T>::generate();
            tracker.update(input); // 更新覆盖率统计
            if (!property(input))
            {
                fmt::print("Test failed for input: {}\n", input);

                fmt::print("Shrinking input...");
                std::function<bool(const T &)> propFunc = property;
                T minimalInput = shrinkInput(input, propFunc);
                fmt::print("Minimal failing input: {}\n", minimalInput);
                return false;
            }
        }
        fmt::print("All tests passed!\n");
        tracker.print(); // 输出覆盖率统计
        return true;
    }

private:
    // 缩小失败用例的功能
    template <typename T>
        requires RandomGeneratable<T>
    static T shrinkInput(const T &input, const std::function<bool(const T &)> &property)
    {
        T current = input;
        while (true)
        {
            T next = RandomGenerator<T>::shrink(current);
            if (next == current || !property(next))
            {
                break; // 无法进一步缩小，或缩小后的输入不再触发失败
            }
            current = next;
        }
        return current;
    }
};