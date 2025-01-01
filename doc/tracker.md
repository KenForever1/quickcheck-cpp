

## CoverageTracker 类

用于统计测试覆盖率，记录输入的最小值、最大值和测试次数。支持基本类型（如 int）和容器类型（如 std::vector）等。

### func

+ update 方法：

更新统计信息，记录输入的范围和分布。

+ print 方法：

输出统计结果，显示测试覆盖的输入范围。

### 在 QuickCheck 中使用 CoverageTracker

在每次生成输入后，调用 update 方法更新统计信息。

在测试结束后，调用 print 方法输出覆盖率统计。