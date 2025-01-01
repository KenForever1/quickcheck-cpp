

## quickcheck-cpp

基于 C++20 实现一个简化版的 quickcheck 一个基本的属性测试框架。

包括如下功能：
（1）随机输入生成：
使用 C++ 的随机数库（如 <random>）生成随机数据。支持基本类型（如 int、double、std::string）和自定义类型。

（2）属性测试：
用户提供一个 Lambda 函数作为属性测试函数。会生成随机输入并验证属性是否成立。

（3）缩小失败用例：
如果测试失败，尝试缩小输入，找到最小的失败用例。


## 依赖

+ gtest
+ fmt

## 特性

### 生成任意值

通过RandomGenerator 模板，用于生成随机数据。通过特化支持如下类型：
+ 基本类型：

char、int、long long、float、double 等基本类型均支持随机生成。

+ 字符串：

std::string 生成长度为 1 到 10 的随机字符串。

+ 容器：

std::vector<T>：生成随机长度的向量，元素类型 T 可以是任意支持的类型。

std::map<K, V>：生成随机长度的映射，键值对由 RandomGenerator<std::pair<K, V>> 生成。

std::set<T>：生成随机长度的集合，元素类型 T 可以是任意支持的类型。

std::unordered_map<K, V>：生成随机长度的无序映射。

+ 元组和键值对：

std::tuple<Ts...>：生成随机元组，元素类型由 RandomGenerator<Ts> 生成。

std::pair<K, V>：生成随机键值对，键和值分别由 RandomGenerator<K> 和 RandomGenerator<V> 生成。

### 缩小失败(shrink)

实现缩小失败用例的功能是 quickcheck 的核心特性之一。当测试失败时，我们需要逐步缩小输入，找到最小的、仍然能触发失败的用例。

缩小策略：

对于数值类型（如 int、double），逐步将值减半。

对于容器类型（如 std::vector、std::map），逐步删除元素。

对于复合类型（如 std::tuple），逐步缩小其组成部分。

递归缩小：

对于复杂类型，递归地缩小其子元素。

停止条件：

当输入无法进一步缩小，或缩小后的输入不再触发失败时，停止缩小。

例如，测试函数错误，输出：

```bash
Testing property: reverse(reverse(xs)) == xs
Test failed for input: [-80, 62, 40, -98, -50, 95, -21]
Shrinking input...Minimal failing input: [-80, 62, 40, -98, -50, 95, -21]
```

### 统计测试覆盖率

用于统计测试覆盖率，记录输入的最小值、最大值和测试次数。

```bash
Testing property: reverse(reverse(xs)) == xs
All tests passed!
Vector Coverage: minSize = 0, maxSize = 9, sizeCount = 100 
Element Coverage: Coverage: min = -100, max = 100, count = 202
```

## doc

[从这里开始](./doc/concepts.md)。

## inspired

[BurntSushi/quickcheck](https://github.com/BurntSushi/quickcheck): Automated property based testing for Rust (with shrinking).

[emil-e/rapidcheck](https://github.com/emil-e/rapidcheck): QuickCheck clone for C++ with the goal of being simple to use with as little boilerplate as possible.