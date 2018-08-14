# Algorithm-Basis
Some notes for the course [Algorithm basis](https://www.coursera.org/learn/suanfa-jichu/home/welcome) on Coursera.

### Week 1: 枚举算法

#### 基本思想
对问题可能解集合的每一项，根据问题给定的检验条件判定哪些是成立的，使条件成立的即是问题的解。

#### 枚举过程
- 判断猜测的答案是否正确
- 进行新的猜测: 有两个关键因素要注意：
  - 猜测的结果必须是前面的猜测中没有出现过的
  - 猜测的过程中要及早排除错误的答案

#### 三个关键问题
- 给出解空间, 建立简洁的数学模型
  - 可能的情况是什么
  - 模型中变量数**尽可能少**, 它们之间相互独立
- 减少搜索的空间
  - 利用知识缩小模型中各变量的取值范围, 避免不必要的计算（**减少代码中循环体执行次数**）
- 采用合适的搜索顺序
  - 搜索空间的遍历顺序要与模型中条件表达式一致

#### 案例（详细解释见代码）
- Case 1: 熄灯问题

- Case 2: 讨厌的青蛙

- Exercise1: [画家问题](http://cxsjsxmooc.openjudge.cn/test/Y/)

  思路同Case1，需要注意的问题：
  - 矩阵大小由给定的输入来确定而不是固定值，因此矩阵不能定义为全局变量，而只能作为参数传入其他函数中进行处理
  - 读入的初始值为字符串而不是单个字符，可将其先存入字符数组中再赋值给相应矩阵
  - 一种情况可能会有多种解，采用所需操作数最少的解

- Exercise2: [拨钟问题](http://cxsjsxmooc.openjudge.cn/test/Z/)

  - 思路1

    每种移动可行执行0 1 2 3次，因为执行4次的话结果跟0次一样，没有意义。

    一共九种移动，每种移动4种可能性，4^9=262144，范围太大。因此考虑缩小范围。

  - 思路2

    即exercise2_v1.cpp中的思路。

    考虑A钟的情况，只有三种移动（1 2 4）能使A钟转动。首先将枚举范围缩小到可能使得A成功的所有情况，即一共4^3=64种情况可能使得A成功归零。对这64种情况进行枚举，如果某种情况不能使得A归零，则直接跳过，不用再进行其他步骤的枚举。

    如果某种情况可以使得A成功归零，则下一步进行与B有关的移动的枚举（3 5），此时不需再考虑1 2 4三种移动。若某种情况B不能归零，则跳过这次循环，若可以归零，则继续进行涉及C的移动的枚举等等。直到最后一种移动也枚举完毕。能使得所有钟归零的移动步骤则是可能解。

    收集所有可能解，最后判断哪一个为最优解。

    注意事项：

    - 每次迭代开始时，要将存储移动步骤的数组相应位置零，以及记录钟状态的数组还原到移动开始前的状态。
    - 数组拷贝函数 `memcpy(dest, source, sizeof(clock));`的使用问题。有时候没用？？
    - 嵌套迭代部分的代码很冗余，exercise2_v2进行中。。

    
