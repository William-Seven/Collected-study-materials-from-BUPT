# ch 2 语言及文法
+ 空串是任何字符串的前缀，后缀及子串
+ 语言的积不可交换 ![400](Attachments/Pasted%20image%2020240421154058.png)  
+ **文法**
  文法 G 是一个四元组 G=(N，T，P，S)，其中
	N  非终结符的有限集合
	T  终结符的有限集合   N∩T=Φ
	P 形式为α→β的生成式的有限集合。
	   且α∈(N∪T)* N+ (N∪T)* ,β∈(N∪T)*
	S  起始符且 S ∈N

+ **0 型文法：无限制文法**
+ **1 型文法：上下文有关文法**
  生成式的形式为α→β，
		其中 |α|≤|β|，β∈（N∪T）+，  
		α∈（N∪T）*N+（N∪T）*
  语言限定约束：
  + 左部的长度小于右部
  + 不含 $A->ε$
+ **2 型文法：上下文无关文法 CFG**
  A→α,    A∈N, 且α∈（N∪T）*
  语言限定约束：
  左部是单个非终结符。
+ **3 型文法：正则文法**
  右线性文法（Right-linear Grammar）：
  A→ωB 或 A→ω		A、B∈N, ω∈T*。
  左线性文法（Left-linear Grammar）：
  A→Bω或 A→ω		A、B∈N, ω∈T*。
  对应的语言：正则语言
+ **四者关系**
  只是对生成式形式加以限制
  0 型无限制
  1 型不允许 $A\rightarrow ε$ 形式
  2 型
  3 型属于 2 型
  **不含 $A\rightarrow ε$ 的 2 型、3 型属于 1 型；1 型、2 型、3 型均属于 0 型**
1 型和2 型区别在于：左部不同!!!
---
# ch 3 有限自动机和右线性文法
+ **有限自动机五要素**
  有限状态集、有限输入符号集、转移函数、一个开始**状态**、一个终态**集合**
+ **DFA** 是一个五元组 $M=(Q, T,δ, q_0, F)$
  $Q$: 有限的状态集合
  $T$: 有限的输入字母表
  $δ$: 转换函数 (状态转移集合): $Q×T\rightarrow Q$
  $q_0$: 初始状态， $q_0\in Q$
  $F$: 终止状态集,  $F\subseteq Q$
+ **被 DFA 接收的字符串**: 输入结束后使 DFA 的状态到达终止状态。否则该字符串不能被 DFA 接收
+ **DFA 接收的语言**: 被 DFA 接收的字符串的集合

+ **$\varepsilon$ - 闭包（closure）** :定义为从 q  经所有的 $\varepsilon$ 路径可以到达的状态（包括 q 自身）![300](Attachments/Pasted%20image%2020240421195704.png)
+  $\varepsilon-NFA$ 不确定的有限自动机的语言 ![350](Attachments/Pasted%20image%2020240421202048.png)
+  $\varepsilon-NFA$ 构造 NFA ![350](Attachments/Pasted%20image%2020240421202438.png)
  **注意：** 两次闭包都是**所有的 $\varepsilon$ 路径**可达的状态（一次 $\varepsilon$ ，两次 $\varepsilon$ ……）
+ **正则表达式**![400](Attachments/Pasted%20image%2020240421205137.png)
+ **正则式的性质**
  ![350](Attachments/Pasted%20image%2020240421205323.png) ![350](Attachments/Pasted%20image%2020240421205341.png)
+ **右线性文法导出正则式**
  设 $x = αx+β，α∈T^*，β∈(N∪T)^*, x∈N$   则 $x$ 的解为 $x＝α^*β$
+ **正则式导出右线性文法**
  上述反过来
+ **正则表达式构造等价的 $\varepsilon-NFA$** 
  ![350](Attachments/Pasted%20image%2020240421212056.png) ![350](Attachments/Pasted%20image%2020240421212117.png)
+ **右线性文法构造有限自动机**  ![380](Attachments/Pasted%20image%2020240421212454.png)
+ **有限自动机构造右线性文法**![400](Attachments/Pasted%20image%2020240421212901.png)
+ **DFA 化简**
  + **等价和可区分**![300](Attachments/Pasted%20image%2020240421213523.png)
  + **不可达**![300](Attachments/Pasted%20image%2020240421213548.png)
  + **最小化**：DFA Ｍ不存在互为等价状态及不可达状态，则称 DFA Ｍ是最小化的。
+ **最小化算法**
  1. 构成基本划分 $\Pi=\{\Pi^{’},\Pi^{”}\}$， ($\Pi^{’}$ 为终态集， $\Pi^{''}$ 为非终态集)
  2. 细分
![500](Attachments/Pasted%20image%2020240421213910.png)

+ **填表法** ![450](Attachments/Pasted%20image%2020240421214213.png)
+ **Pumping 引理** ![500](Attachments/Pasted%20image%2020240421215814.png)
![350](Attachments/Pasted%20image%2020240421215902.png)
+ **米兰机**： 输出字符与输入字符及状态有关 ![300](Attachments/Pasted%20image%2020240421221140.png)
+ **摩尔机**： 输出字符仅与状态有关 ![350](Attachments/Pasted%20image%2020240421221155.png)

---

# ch 4 上下文无关文法与下推自动机
+ **归约与推导**
  + **归约**过程将产生式的右部（body）替换为产生式的左部（ head ）.
  + **推导**过程将产生式的左部（ head ）替换为产生式的右部（ body ）.
![400](Attachments/Pasted%20image%2020240506081012.png)
![400](Attachments/Pasted%20image%2020240506081027.png)

+ **最左推导**
  推导过程的每一步总是替换出现在最左边的非终结符 ![400](Attachments/Pasted%20image%2020240506081649.png)
+ **最右推导**
  推导过程的每一步总是替换出现在最右边的非终结符（rm）

+ **推导树的边缘**
  叶子从左向右组成的字符串称为推导树的边缘 ![350](Attachments/Pasted%20image%2020240506082117.png)

+ **二义性**
  2 型文法是二义的, 当且仅当对于句子 $ω∈L (G)$, 存在两棵不同的具有边缘为ω的推导树。 
  即：如果文法是二义的, 那么它所产生的某个句子必然能从不同的最左 (右)推导推出

+ **Chomsky 范式 (CNF - Chomsky Normal Form)**
  生成式形式为 $A→BC,  A→a,  A, B, C∈N ,  a∈T$ 
  每个上下文无关文法都有一个 CNF 文法
+ **Greibach 范式 (GNF)**
  生成式形式为 $A→aβ,  a∈T ,  β∈N^*$  
  意义: 对每个 2 型语言都可找到一个文法使产生式的**右端都以终结符开始**
  中心思想: 消除左递归.

+ **有用符号（useful symbol）**![450](Attachments/Pasted%20image%2020240506090500.png)
+ **消去无用符号**
  - 计算生成符号（generating symbol）集 （**算法 1**）
  - 计算可达符号（reachable symbol）集（**算法 2**）
  - 消去非生成符号、不可达符号
  - 消去相关产生式

+ **算法 1: 找出有用非终结符（生成符号集）**![450](Attachments/Pasted%20image%2020240506090711.png)
+ **算法 2: 找出有用符号 (从 S 可达的符号)**![400](Attachments/Pasted%20image%2020240506090737.png)

+ **消去 $\varepsilon$ 产生式**
  + **可致空符号（nullable symbol）**![500](Attachments/Pasted%20image%2020240506092009.png)
+ **算法 3: 生成无 $\varepsilon$ 文法**![450](Attachments/Pasted%20image%2020240506092733.png) ![450](Attachments/Pasted%20image%2020240506093134.png)

+ **消去单产生式**
  单产生式形如 $A\rightarrow B$ 的产生式，其中 A、B 为非终结符
  + **单元偶对**![400](Attachments/Pasted%20image%2020240513081019.png)
+ **算法 4**![450](Attachments/Pasted%20image%2020240513081428.png) ![450](Attachments/Pasted%20image%2020240513081442.png)
  
![450](Attachments/Pasted%20image%2020240513082855.png)

+ **消除递归**![450](Attachments/Pasted%20image%2020240513082920.png)
+ **消除直接左递归**![450](Attachments/Pasted%20image%2020240513083655.png)
+ **算法 5：消除全部左递归**![450](Attachments/Pasted%20image%2020240513084531.png)
  
+ **CNF 的构成步骤**![450](Attachments/Pasted%20image%2020240513090203.png)
+ **GNF 的构成步骤**![450](Attachments/Pasted%20image%2020240513090802.png)
## 下推自动机
![450](Attachments/Pasted%20image%2020240513093132.png)
![450](Attachments/Pasted%20image%2020240513093144.png)

+ **下推自动机的格局**![400](Attachments/Pasted%20image%2020240520080831.png)
+ **下推自动机接受的语言**![450](Attachments/Pasted%20image%2020240520081004.png)

+ **确定的下推自动机（DPDA）**![450](Attachments/Pasted%20image%2020240520083123.png)
+ **非确定的下推自动机（NPDA）**

+ **空栈接受与终态接受的等价**

+ **从上下文无关文法构造等价的下推自动机**![450](Attachments/Pasted%20image%2020240520090808.png)
  定理的物理意义：利用下推自动机进行自顶向下的分析，检查一个句子的最左推导过程
  **步骤如下：**
  1. 初始时，将文法开始符号压入空栈.
  2. 如果栈为空，则分析完成.
  3. 如果栈顶为一非终结符，先将其从栈中弹出. 选择下一个相应于该非终结符的产生式，并将其右部符号从右至左地一一入栈. 如果没有可选的产生式，则转出错处理.
  4. 如果栈顶为一终结符，那么这个符号必须与当前输入符号相同，将其弹出栈，读下一符号，转第(2)步；否则，回溯到第(3)步.

+ **从下推自动机构造等价的上下文无关文法 （需要掌握）**![450](Attachments/Pasted%20image%2020240520092511.png)

+ **2 型语言的泵浦引理**![](Attachments/Pasted%20image%2020240527082722.png)
+ **二义性问题**![](Attachments/Pasted%20image%2020240527085659.png)
+ **线性文法**![450](Attachments/Pasted%20image%2020240527090855.png)
+ **顺序文法**![450](Attachments/Pasted%20image%2020240527090916.png)

# ch 5 图灵机
+ **形式定义** ![450](Attachments/Pasted%20image%2020240603080205.png)
+ **格局**![500](Attachments/Pasted%20image%2020240603080408.png)
![500](Attachments/Pasted%20image%2020240616224720.png)







