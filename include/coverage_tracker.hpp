#include <fmt/ranges.h>
#include <limits>
#include <vector>

// 统计测试覆盖率的工具类
template <typename T>
class CoverageTracker
{
public:
    void update(const T &value)
    {
        if (value < min)
            min = value;
        if (value > max)
            max = value;
        count++;
    }

    void print() const
    {
        fmt::print("Coverage: min = {}, max = {}, count = {}\n", min, max, count);
    }

private:
    T min = std::numeric_limits<T>::max();
    T max = std::numeric_limits<T>::min();
    size_t count = 0;
};

// 特化：统计 std::vector<T> 的覆盖率
template <typename T>
class CoverageTracker<std::vector<T>>
{
public:
    void update(const std::vector<T> &value)
    {
        size_t size = value.size();
        if (size < minSize)
            minSize = size;
        if (size > maxSize)
            maxSize = size;
        sizeCount++;

        for (const auto &elem : value)
        {
            elementTracker.update(elem);
        }
    }

    void print() const
    {
        fmt::print("Vector Coverage: minSize = {}, maxSize = {}, sizeCount = {} \n", minSize, maxSize, sizeCount);
        fmt::print("Element Coverage: ");
        elementTracker.print();
    }

private:
    size_t minSize = std::numeric_limits<size_t>::max();
    size_t maxSize = 0;
    size_t sizeCount = 0;
    CoverageTracker<T> elementTracker;
};
