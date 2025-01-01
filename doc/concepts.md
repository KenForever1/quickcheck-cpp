
## C++20 Concept约束

### RandomGeneratable Concept

要求类型 T 必须实现 RandomGenerator<T>::generate() 和 RandomGenerator<T>::shrink() 方法。

用于约束 RandomGenerator 的模板参数。

### PropertyTestable Concept

要求类型 Func 必须是一个可调用对象，接受 T 类型参数并返回 bool。

用于约束属性测试函数的模板参数。


## 使用概念的好处

一方面，增强代码安全性，在编译时检查模板参数是否满足要求，避免运行时错误。其二，提高代码可读性，明确模板参数的要求，使代码更易于理解。而且，更好的错误提示，如果模板参数不满足概念约束，编译器会给出清晰的错误信息。