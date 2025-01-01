#include <random>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <set>
#include <unordered_map>
#include <utility>
#include <concepts>

// 随机生成器模板
template <typename T>
struct RandomGenerator;

// 定义概念：要求类型 T 必须实现 RandomGenerator 的 generate 和 shrink 方法
template <typename T>
concept RandomGeneratable = requires {
    { RandomGenerator<T>::generate() } -> std::same_as<T>;
    { RandomGenerator<T>::shrink(std::declval<T>()) } -> std::same_as<T>;
};

// 定义概念：要求类型 Func 必须是一个可调用对象，接受 T 类型参数并返回 bool
template <typename Func, typename T>
concept PropertyTestable = std::invocable<Func, T> && std::same_as<std::invoke_result_t<Func, T>, bool>;

// 特化：生成随机 char
template <>
struct RandomGenerator<char>
{
    static char generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis('a', 'z');
        return static_cast<char>(dis(gen));
    }

    // 缩小策略：逐步减小字符值
    static char shrink(char value)
    {
        return static_cast<char>(value - 1); // 返回前一个字符
    }
};

// 特化：生成随机 int
template <>
struct RandomGenerator<int>
{
    static int generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(-100, 100);
        return dis(gen);
    }

    // 缩小策略：逐步减半
    static int shrink(int value)
    {
        return value / 2;
    }
};

// 特化：生成随机 long long
template <>
struct RandomGenerator<long long>
{
    static long long generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<long long> dis(-1000, 1000);
        return dis(gen);
    }
};

// 特化：生成随机 float
template <>
struct RandomGenerator<float>
{
    static float generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(-100.0f, 100.0f);
        return dis(gen);
    }
};

// 特化：生成随机 double
template <>
struct RandomGenerator<double>
{
    static double generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(-100.0, 100.0);
        return dis(gen);
    }
};

// 特化：生成随机 std::string
template <>
struct RandomGenerator<std::string>
{
    static std::string generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 25);
        std::string result;
        int length = RandomGenerator<int>::generate() % 10 + 1; // 随机长度
        for (int i = 0; i < length; ++i)
        {
            result.push_back('a' + dis(gen));
        }
        return result;
    }

    // 缩小策略：逐步缩短字符串
    static std::string shrink(const std::string &value)
    {
        if (value.empty())
            return value;
        return value.substr(0, value.size() / 2);
    }
};

// 特化：生成随机 std::pair<K, V>
template <typename K, typename V>
struct RandomGenerator<std::pair<K, V>>
{
    static std::pair<K, V> generate()
    {
        return {RandomGenerator<K>::generate(), RandomGenerator<V>::generate()};
    }
};

// 特化：生成随机 std::tuple<Ts...>
template <typename... Ts>
struct RandomGenerator<std::tuple<Ts...>>
{
    static std::tuple<Ts...> generate()
    {
        return std::make_tuple(RandomGenerator<Ts>::generate()...);
    }
};

// 特化：生成随机 std::vector<T>
template <typename T>
struct RandomGenerator<std::vector<T>>
{
    static std::vector<T> generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::vector<T> result;
        int length = RandomGenerator<int>::generate() % 10; // 随机长度（0 到 9）
        for (int i = 0; i < length; ++i)
        {
            result.push_back(RandomGenerator<T>::generate());
        }
        return result;
    }

    // 缩小策略：逐步删除元素
    static std::vector<T> shrink(const std::vector<T> &value)
    {
        if (value.empty())
            return value;
        std::vector<T> result = value;
        result.pop_back(); // 删除最后一个元素
        return result;
    }
};

// 特化：生成随机 std::map<K, V>
template <typename K, typename V>
struct RandomGenerator<std::map<K, V>>
{
    static std::map<K, V> generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::map<K, V> result;
        int length = RandomGenerator<int>::generate() % 5; // 随机长度（0 到 4）
        for (int i = 0; i < length; ++i)
        {
            result.insert(RandomGenerator<std::pair<K, V>>::generate());
        }
        return result;
    }

    // 缩小策略：逐步删除元素
    static std::map<K, V> shrink(const std::map<K, V> &value)
    {
        if (value.empty())
            return value;
        std::map<K, V> result = value;
        result.erase(result.begin()); // 删除第一个元素
        return result;
    }
};

// 特化：生成随机 std::set<T>
template <typename T>
struct RandomGenerator<std::set<T>>
{
    static std::set<T> generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::set<T> result;
        int length = RandomGenerator<int>::generate() % 5; // 随机长度（0 到 4）
        for (int i = 0; i < length; ++i)
        {
            result.insert(RandomGenerator<T>::generate());
        }
        return result;
    }

    // 缩小策略：逐步删除元素
    static std::set<T> shrink(const std::set<T> &value)
    {
        if (value.empty())
            return value;
        std::set<T> result = value;
        result.erase(result.begin()); // 删除第一个元素
        return result;
    }
};

// 特化：生成随机 std::unordered_map<K, V>
template <typename K, typename V>
struct RandomGenerator<std::unordered_map<K, V>>
{
    static std::unordered_map<K, V> generate()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::unordered_map<K, V> result;
        int length = RandomGenerator<int>::generate() % 5; // 随机长度（0 到 4）
        for (int i = 0; i < length; ++i)
        {
            result.insert(RandomGenerator<std::pair<K, V>>::generate());
        }
        return result;
    }

    // 缩小策略：逐步删除元素
    static std::unordered_map<K, V> shrink(const std::unordered_map<K, V> &value)
    {
        if (value.empty())
            return value;
        std::unordered_map<K, V> result = value;
        result.erase(result.begin()); // 删除第一个元素
        return result;
    }
};