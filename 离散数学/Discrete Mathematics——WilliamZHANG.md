+ **一些写在前面的话：**
  本笔记分为离散上（1~6 章）和离散下（8~11 章+离散结构：群）两部分。其中离散上于 2023.03-2023.06 编写，离散下于 2023.09-2024.01 编写。
  由于笔者的个人原因，编写离散上时的水平有限，可读性、美观程度都较为一般，读者可选择其他的学习参考方式。
  仅笔者草率且不负责任的了解，我校计算机本科对于离散数学的学习内容是属于较多较细的一类，建议各位读者以自己学校的内容重点为主，该笔记仅可供一些提炼参考。
  若发现笔记的错误，读者自己学会就好，我已经不想再碰它啦 
  祝各位离散数学的 learner 们都可以学习到有用的知识，获得理想的成绩
  
***Discrete Mathematics 上***
# 1. Logic and Proofs 逻辑和证明

## 1.1 Propositional Logic 命题逻辑

### 1.1.2 Proposition 命题
A **proposition** is a declarative sentence (that is, a sentence that declares a fact) that is either true or false, but not both.

We use letters to denote **propositional variables 命题变量**(or **sentential variables 语句变量**).The conventional letters used for propositional variables are p, q, r, s, … . The **truth value** of a proposition is true, denoted by T, if it is a true proposition, and the truth value of a proposition is false, denoted by F, if it is a false proposition. Propositions that cannot be expressed in terms of simpler propositions are called **atomic propositions 原子命题**.

The area of logic that deals with propositions is called the **propositional calculus or propositional logic**.

---
### 1.1.3 Truth table 真值表
| ENGLISH | 中文 |
| ---- | ---- |
| negation | 否定 |
|Conjunction|合取|
|Disjunction|析取|
|Exclusive|异或|
|implication|蕴含|
|bi-implication|双向蕴含|

![[Pasted image 20230301205339.png]]
![[Pasted image 20230301205348.png]]
![[Pasted image 20230301205402.png]]
![[Pasted image 20230314184919.png]]
![[Pasted image 20230314184948.png]]

### 1.1.4 Precedence of Logical Operators 逻辑运算符的优先级
![[Pasted image 20230301205654.png]]

### 1.1.5 Logic and Bit Operations 逻辑运算和比特运算
A *bit string* is a sequence of zero or more bits. The *length* of this string is the number of bits in the string.

## 1.2 Applications of Propositional Logic 命题逻辑的应用

### 1.2.6 Logic Circuits 逻辑电路
A **logic circuit** (or **digital circuit**) receives input signals *p1, p2, … , pn*, each a bit \[either 0 (off) or 1 (on)], and produces output signals *s1, s2, … , sn*, each a bit. 

The **inverter**, or **NOT gate**, takes an input bit *p*, and produces as output *¬p*. The **OR gate** takes two input signals *p* and *q*, each a bit, and produces as output the signal *p ∨ q*. Finally, the **AND gate** takes two input signals *p* and *q*, each a bit, and produces as output the signal *p ∧ q*. 

![[Pasted image 20230301210543.png]]

## 1.3 Propositional Equivalences 命题等价式

### 1.3.1 Introduction 引言
A compound proposition that is always true, no matter what the truth values of the propositional variables that occur in it, is called a *tautology* **永真式/重言式**. A compound proposition that is always false is called a *contradiction* **永假式/矛盾式**. A compound proposition that is neither a tautology nor a contradiction is called a *contingency* **可满足式/可能式**

### 1.3.2 Logical Equivalences 逻辑等价式
The compound propositions *p* and *q* are called *logically equivalent* if *p ↔ q* is a tautology.
The notation *p ≡ q* denotes that *p* and *q* are logically equivalent.
![[Pasted image 20230301211206.png]]

+ ***De Morgan laws***
  > ![[Pasted image 20230301211258.png]]

![[Pasted image 20230301211646.png|550]]
![[Pasted image 20230311102507.png|500]]
![[Pasted image 20230301213539.png]]
![[Pasted image 20230314075755.png]]

### 1.3.5 Satisfiability 可满足性
A compound proposition is **satisfiable** if there is an assignment of truth values to its variables that makes it true (that is, when it is a tautology or a contingency). When no such assignments exists, that is, when the compound proposition is false for all assignments of truth values to its variables, the compound proposition is **unsatisfiable**.

### 1.3.6 Applications of Satisfifiability 可满足性的应用
+ The n-Queens Problem：
  > ![[Pasted image 20230302131211.png|500]]

### 1.3.7 Dual formula对偶式
![[Pasted image 20230314160503.png]]

## Supply补充：范式
### 简单析取式、简单合取式
只有析取/合取

### Disjunctive normal form 析取范式 DNF
有限个**简单合取式**的***析取***构成的析取式

### Conjunctive normal form 合取范式 CNF
有限个**简单析取式**的***合取***构成的合取式

### 存在性定理
任意一个命题公式均存在与之等值的析取范式和合取范式
**（不唯一）**
![[Pasted image 20230314190107.png]]

### Minterm 极小项
若公式中共有N个命题变项P1，……，P n，在这N个变项的合取式中，每个变项Pi或其否定~Pi，**均出现且两者仅出现一个**，并且按命题变项的下标排列（字母按字典序列），这样的**简单合取式**称为**极小项**，又称**布尔合取**。
![[Pasted image 20230314080313.png]]
**编码：**
> ![[Pasted image 20230314080346.png|inl]] ![[Pasted image 20230314080426.png|inl]]

### Principal/Major DNF 主析取范式
+ 若干不同的极小项组成的析取式

+ 定理：任意一个命题公式均存在与之等值的主析取范式且唯一

+ 求法：1. 真值表法     2. 等值演算法
![[Pasted image 20230414202540.png]]

### Maxterm 极大项
如公式中共有N个命题变项P1，……，P n ，这N个变项的简单析取式中，每个变项Pi或其否定~ Pi，**均出现且两者仅出现一个**，并且按命题变项的下标排列（字母按字典序列）这样的**简单析取式**称为**极大项**，又称**布尔析取**。
![[Pasted image 20230314080733.png]]

### Principal/Major CNF 主合取范式
+ 若干不同的极大项组成的析取式

+ 定理：任意一个命题公式均存在与之等值的主合取范式且唯一
![[Pasted image 20230414202840.png]]

## 1.4 Predicates and Quantifiers 谓词和量词

### 1.4.2 Predicates 谓词
A statement involving the $n$ variables $x_1, x_2, … , x_n$ can be denoted by
   $$P(x_1, x_2, … ,x_n)$$.
A statement of the form P(x1, x2, … , xn) is the value of the **propositional function P** at the *n-tuple (x1, x2, … , xn)*, and *P* is also called an *n* **-place predicate n位谓词** or an *n* **-ary predicate n元谓词**.

+ **PRECONDITIONS AND POSTCONDITIONS 前置条件和后置条件** 
  >The statements that describe valid input are known as **preconditions** and the conditions that the output should satisfy when the program has run are known as **postconditions**.

### 1.4.3 Quantifiers 量词
![[Pasted image 20230314082453.png]]
+ **唯一存在量词 unique existential**：
>存在量词符号后加：  ！
>The notation **∃!** $xP(x)$  states “There exists a unique x such that $P(x)$ is true.”

### 1.4.6 Precedence of Quantififiers 量词的优先级
The quantififiers ∀ and ∃ have higher precedence than all logical operators from propositional calculus.

### 1.4.7 Binding Variables 变量绑定
An expression like $P(x)$ is said to have a **free variable x** (meaning, x is undefined).

A quantifier (either ∀ or ∃) operates on an expression having one or more free variables, and **binds** one or more of those variables, to produce an expression having one or more **bound variables**.

### 1.4.9 Negating Quantifified Expressions 量化表达式的否定
#### De Morgan’s Laws for Quantififiers 量词的德摩根律:
¬∀xP(x) ≡ ∃x ¬P(x)
¬∃xQ(x) ≡ ∀x ¬Q(x)

#### 1.4.9.1 Example 示例
+ Some student in this class has visited Guangzhou.
+ Every student in this class has visited Chengdu or Guangzhou.

>G (x): “x has visited Guangzhou.” ，C (x):“x has visited Chengdu.”


**The U.D. for the variable x consists of the students in this class.**
+ ∃xG(x).
+ ∀x(C(x) ∨ G(x))

**The U.D. for the variable x consists of all people.**
S(x): “x is a student in this class.”
+ ∃x(S(x) ∧ G(x))
+ ∀x(S(x) → (C(x) ∨ G(x)))

**全称量词用蕴含，存在量词用合取**

## 1.5 Nested Quantififiers 嵌套量词

### 1.5.3 The Order of Quantififiers 量词的顺序
在没有其他量词的语句中，在不改变量化式意义的前提下嵌套全称量词的顺序是可以改变的

![[Pasted image 20230318102305.png]]

## Supply补充：合式公式、前束范式
### 1 一阶逻辑的合式公式

#### 1.1 定义
**项(term)**
+ 个体常项和个体变项是项
+ 若f(x1 ,x2 ,…,xn )是n元函数, t1 ,t2 ,…,tn是项, 则f(t1 ,t2 ,…,tn )是项
+ 所有的项都是有限次地应用上述规则形成的
+ 例如: a, x, f(a), g(a, x), g(x, f(a))

**原子公式(atomic formula)**
+ 若R(x1 ,x2 ,…,xn )是n元谓词, t1 ,t2 ,…,tn是项, 则R(t1 ,t2 ,…,tn )是原子公式
+ 例如: F(a), G(a, y), F(f(a)), G(x, g(a, y))

**合式公式(well-formed formula)**
+ 原子公式是合式公式
+ 若A是合式公式，则(~A)是合式公式
+ 若A,B是合式公式，则(A∧B), (A∨B), (A→B), (A↔B)也是合式公式
+ 若A是合式公式，则∃xA, ∀xA也是合式公式
+ 有限次地应用上述规则形成的符号串是合式公式
  >$F (f (a, a), b)$
  >$∃x(F(x)∧∀y(G(y)→H(x,y)))$

+ 约定：省略多余括号
  >最外层
  >优先级递减： ∃, ∀; ~; ∧, ∨; →, ↔

#### 1.2 合式公式中的变项
**量词辖域:** 在∃xA, ∀xA中, **A**是量词的辖域。例如:
∃x(**F(x)∧∀y(G(y)→H(x,y))**)
∃x**F(x)** ∧∀y **(G(y)→H(x,y))**

**指导变项:** 紧跟在量词后面的个体变项。例如：∃**x**(F(x)∧∀**y**(G(y)→H(x,y)))

**约束出现:** 在辖域中与指导变项同名的变项. 例如：∃**x**(F(**x**)∧∀*y*(G(*y*)→H(**x**,*y*)))

**自由出现:** 既非指导变项又非约束出现. 例如：∀*y*(G(*y*)→H(x,*y*))

#### 1.3 闭式 (Closed Form)
**闭式: 无自由出现的变项**

#### 1.4 合式公式的解释
![[Pasted image 20230320190705.png]]

#### 1.5 一阶逻辑类型
**永真式Tautology：**
+ 在各种**解释**下取值均为真 **(逻辑有效式)**
+ 命题逻辑永真式: 在各种赋值下取值均为真 **(重言式)**

**永假式Contradiction:**
+ 在各种**解释**下取值均为假 **(矛盾式)**
+ 命题逻辑永假式: 在各种赋值下取值均为假 **(矛盾式)**

**可满足式：** 非永假式

### 2 一阶逻辑等值式

#### 2.0 定义
![[Pasted image 20230320191917.png]]

### 一阶逻辑等值式(来源）
1.命题逻辑等值式的代换实例
2.与量词有关的
 >2.1 有限个体域量词消去
 >2.2 量词否定
 >2.3 量词辖域收缩与扩张
 >2.4 量词分配

3.与变项有关的
 >3.1 换名规则
 >3.2 代替规则

#### 2.1 命题逻辑等值式的代换实例
在命题逻辑等值式中, 代入一阶逻辑公式所得到的式子, 称为原来公式的代换实例。

#### 2.2 有限个体域量词消去
![[Pasted image 20230320192220.png]]

#### 2.3 量词辖域收缩与扩张（∀）
+ 假设B中不含x的出现
1）∀x(A(x)∨B) ⇔ ∀xA(x)∨B
2）∀x(A(x)∧B) ⇔ ∀xA(x)∧B
3）∀x(A(x)→B) ⇔ **∃x**A(x)→B
4）∀x(B→A(x)) ⇔ B→**∀x**A(x)

#### 2.4 量词辖域收缩与扩张（∃）
+ 假设: B中不含x的出现
1）∃x(A(x)∨B) ⇔ ∃xA(x)∨B
2）∃x(A(x)∧B) ⇔ ∃xA(x)∧B
3）∃x(A(x)→B) ⇔ **∀x**A(x)→B
4）∃x(B→A(x)) ⇔ B→**∃x**A(x)

#### 2.5 量词分配
+ ∀x(A(x)∧B(x)) ⇔ ∀xA(x)∧∀xB(x)
+ ∃x(A(x)∨B(x)) ⇔ ∃xA(x)∨∃xB(x)

##### 反例
![[Pasted image 20230320202334.png]]

##### 蕴含
![[Pasted image 20230320202428.png]]

##### 附加前提法
![[Pasted image 20230320202437.png]]

### 3.1 换名(rename)规则
把某个**指导变项**和其量词辖域中所有同名的**约束变项**, 都换成新的个体变项符号
![[Pasted image 20230320202609.png]]

### 3.2 代替(substitute)规则
把某个**自由变项**的所有出现, 都换成新的个体变项符号
![[Pasted image 20230320202636.png]]

### 4 谓词公式的范式(NF)
+ **前束范式（Prenex Normal Form ）**
如果量词均在合式公式的开头，它们的辖域延伸到整个公式末尾，则该公式称为前束范式。

* ∀x∀y∃z(Q(x,y) → R(z))
* ∀y∀x(~P(x,y) → Q(y))

* **存在性定理：**
谓词逻辑合式公式均存在与之等值的前束范式

* **构造方法：**
利用换名、代替、量词的收缩和扩张等进行等值变换

+ **量词顺序不同**
![[E}W@@[~OB~(W`EL1KJ$}54D.jpg]]

## 1.6 Rules of Inference 推理规则
### 1.6.1 Tautological implication 重言蕴含
**定义：**
A、C是两个公式，如果A→C是**重言式（tautologies）**，则称A重言蕴含C，或称A能逻辑地推出 C，记作A ⇒ C

**说明：** →与⇒是有区别的
+ →是联结词，A→C仍然是公式，公式A→C，当且仅当A真C假时才为假
+ ⇒是公式间的关系符，描述了两个公式间的关系，只能说A⇒C式成立或不成立
+ 重言蕴含A⇒C要成立的充要条件是对一切赋值，如果使A为真，则C也必须为真（**此时A→C 为永真式/重言式**）。

### 1.6.2 Definition 定义
**定义：**
+ 设 $A_1、A_2、…、A_m$，C 是公式，如果 $(A_1 ∧ A_2 ∧ … ∧A_m）→C$ 是**重言式**，则称 C 是前提集合{$A_1、A_2、…、A_m$}的有效结论，或称由{$A_1、A_2 、…、A_m$}逻辑地推论出 C，或称{$A_1、A_2 、…、A_m$} 重言蕴含 C。

+ 由⇒的定义，可以记作 **（A1 ∧ A2 ∧ … ∧ Am）⇒ C**。

### 1.6.3 Rules of Inference 推理规则
#### modus ponens/law of detachment 假言推理规则
(p ∧ (p → q)) → q
![[Pasted image 20230321081345.png]]

#### Famous rules of inference 一些著名的推理规则
![[Pasted image 20230322181529.png]]

### 1.6.4 Formal Proofs 规范证明
![[Pasted image 20230322183104.png]]
### 1.6.5 Rules of inference for Predicate logic 谓词逻辑的推理规则
**来源：**
1. 命题逻辑推理规则的代换实例
2. 一阶逻辑等值式生成的推理规则
3. 一阶逻辑蕴含式生成的推理规则
4. 一阶逻辑量词相关的推理规则

#### 1.6.5.1 代换实例
![[Pasted image 20230322184129.png]]

|中文|ENGLISH|
|---|---|
|假言推理|            Modus Ponens|
|析取引入           | Addition|
|合取消去        |    Simplification|
|拒取式            |  Modus Tollens|
|合取引入         |   Conjunction|
|假言三段论      |    Hypothetical syllogism|
|析取三段论       |   Disjunctive syllogism|
|消解规则           | Resolution|
|构造性两难        |  Constructive dilemma|
#### 1.6.5.2 一阶逻辑等值式生成的推理规则
![[Pasted image 20230322184507.png]]

#### 1.6.5.3 一阶逻辑蕴含式生成的推理规则
∀xA(x)∨∀xB(x) ⇒ ∀x(A(x)∨B(x))
∃x(A(x)∧B(x)) ⇒ ∃xA(x)∧∃xB(x)
∀x(A(x)→B(x)) ⇒ ∀xA(x)→∀xB(x)
∃x(A(x)→B(x)) ⇒ ∀xA(x)→∃xB(x)
∃xA(x) →∀xB(x) ⇒ ∀x(A(x)→B(x))

#### 1.6.5.4 一阶逻辑量词相关推理规则

**先EI，后UI**

##### UI规则：universal instantiation
![[Pasted image 20230322184911.png]]
##### UG规则：universal generalization
![[Pasted image 20230322185039.png]]
##### EI规则：existential instantiation
![[Pasted image 20230322185049.png]]
##### EG规则：existential generalization
![[Pasted image 20230322185100.png]]

### 1.6.6 Fallacies 谬误
The proposition **((p → q) ∧ q) → p** is not a tautology, because it is false when p is false and q is true.This type of incorrect reasoning is called the **fallacy of affirming the conclusion 肯定结论的谬误**.

The proposition **((p → q) ∧ ¬p) → ¬q** is not a tautology, because it is false when p is false and q is true.This type of incorrect reasoning is called the **fallacy of denying the hypothesis 否定假设的谬误**.

## Supply：Construction of Proofs 补充：构造证明

### 构造证明1—直接证明法
![[Pasted image 20230322185341.png]]
### 构造证明2—附加前提证明法(CP规则)
+ **欲证明**
前提：A1 , A2 , …, Ak
结论：C→B

+ **等价地证明**
前提：A1 , A2 , …, Ak , C
结论：B

+ **理由：
    (A1∧A2∧…∧Ak )→(C→B)**
⇔ ~( A1∧A2∧…∧Ak )∨(~C∨B)
⇔ ~ A1∨~ A2∨ … ∨~Ak∨~C∨B
⇔ ~(A1∧A2∧…∧Ak∧C)∨B
⇔ (A1∧A2∧…∧Ak∧C)→B

### 构造证明3—反证法
![[Pasted image 20230322185950.png]]

**设计命题或谓词
给出前提和结论的形式化表示
推理过程要完整
给出规范的三列形式**

## 1.7 Introduction to Proofs 证明介绍

### 1.7.1 Definition 定义
- A ***theorem(定理)*** is a ***valid (正确)*** logical assertion which can be proved using
+ other theorems
+ ***axioms (公理)*** (statements which are given to be true)
+ ***rules of inference (推理规则)*** (logical rules which allow the deduction of conclusions from premises).

- A ***lemma (引理)*** is a 'pre-theorem' or a result which is needed to prove a theorem.
- A ***corollary (推论)*** is a 'post-theorem' or a result which follows directly from a theorem.
- A ***conjecture (猜想)*** is a statement that is being proposed to be a true statement.

+ **Form of theorems**
  > ![[Pasted image 20230330151947.png|300]]

### 1.7.2 Proof Methods for Implications 蕴含的证明方法
![[Pasted image 20230330152057.png|500]]

#### 1.7.2.1 Direct proof 直接证明法
+ assumes the hypotheses are true
+ uses the rules of inference, axioms and any logical equivalences to establish the truth of the conclusion.
>![[Pasted image 20230330152352.png]]

#### 1.7.2.2 Indirect proof 间接证明法
+ **A direct proof of the contrapositive（逆反式）**
  >![[Pasted image 20230330152609.png]]![[Pasted image 20230330152744.png]]

#### 1.7.2.3 Trivial proof 平凡证明
+ If we know Q is true then P → Q is true.
  >![[Pasted image 20230330152905.png]]

#### 1.7.2.4 Vacuous proof 空证明
+ If we know one of the hypotheses in P is false then P→Q is **vacuously true**.
  >![[Pasted image 20230330153510.png]]

#### 1.7.2.5 Proof by contradiction 归谬证明
To prove that a statement P is true
+ assumes the statement P is false
+ derives a contradiction, usually of the form Q ∧ ~Q which establishes ~ P → (Q ∧ ~Q )
+ from which it follows that P must be true.
  > ![[Pasted image 20230330153945.png|400]]

Contrast: The ***contrapositive*** proof:
**To proof P→ Q, construct and proof ~Q→ ~ P**

#### 1.7.2.6 Proof by Cases 案例证明
![[Pasted image 20230330154504.png]]

![[Pasted image 20230330154938.png]]
![[Pasted image 20230330154948.png]]

#### 1.7.2.7 Exhaustive Proof 详尽证明
![[Pasted image 20230330155458.png]]
![[Pasted image 20230330155506.png]]

#### 1.7.2.8 Proof by Examples 示例证明
**Remember**：A universal statement can <u>never</u> be proven by using examples, <u>unless</u> the universe can be validly reduced to only <u>finitely</u> many examples, and your proof covers <u>all</u> of them!
![[Pasted image 20230330155953.png]]

### 1.7.3 Without Loss of generality 不丢失普遍性
![[Pasted image 20230330160509.png]]
![[Pasted image 20230330160516.png]]


## 1.8 Proof Methods and Strategy 证明方法和策略
### 1.8.1 Proof Methods for Existence 存在性证明
![[Pasted image 20230330161003.png]]

#### 1.8.1.1 Constructive Existence Proof 构造性的存在性证明
![[Pasted image 20230330161341.png]]

#### 1.8.1.2 Nonconstructive existence proof 非构造性的存在性证明
![[Pasted image 20230330161517.png]]

### 1.8.2 Proof Methods for Uniqueness 唯一性证明
两个部分：
**存在性**：证明存在某个元素 x 具有期望的性质
**唯一性**：证明如果 x 和 y 都具有期望的性质，则x=y
![[Pasted image 20230330163150.png]]

### 1.8.3 Proof Methods for Nonexistence 不存在性证明
![[Pasted image 20230330163650.png]]

### 1.8.4 Universally Quantified Assertions 普遍量化的断言
![[Pasted image 20230330164538.png]]
![[Pasted image 20230330165009.png|500]]

### 1.8.5 Proof strategy Overview 证明策略概述
#### 1.8.5.1 Forward Reasoning 正向推理
![[Pasted image 20230330170502.png|500]]

#### 1.8.5.2 Backward Reasoning 逆向推理
![[Pasted image 20230330170530.png]]

### 1.8.6 Additional Proof Methods 额外的证明方法
+ **Mathematical induction**, which is a useful method for proving statements of the form "∀n P(n), where the domain consists of all positive integers.
+ **Structural induction**, which can be used to prove such results about recursively defined sets.
+ **Cantor diagonalization** is used to prove results about the size of infinite sets.
+ **Combinatorial proofs** use counting arguments.

---
# 2. Basic Structures: Sets, Functions, Sequences, Sums, and Matrices 基本结构

## 2.1 Set 集合
### 2.1.1 Introduction 引言
**Definition 1:**
![[Pasted image 20230404120315.png]]

**Notation: roster method 花名册方法** 
list the elements between braces:
S = {a, b, c, d}={b, c, a, d, d}

**Notation: specification by predicates（谓词）**
![[Pasted image 20230404120817.png]]

**Common Universal Sets:**
![[Pasted image 20230404120642.png]]
![[Pasted image 20230404120650.png]]

**Definition 2:**
![[Pasted image 20230404120854.png]]

**Empty Set 空集：**
The void set, the null set, the empty set, denoted {} or ∅, is the set with no members.

### 2.1.3 Subsets 子集
**Subsets 子集：**
![[Pasted image 20230404145401.png]]

**Proper subset 真子集**
![[Pasted image 20230404145604.png]]

### 2.1.4 The Size of a Set 集合的大小
**Cardinality 基数**
![[Pasted image 20230404081336.png]]

+ N is *infinite* since |N| is not a natural number.
+ It is called a ***transfinite cardinal number***.
### 2.1.5 Power Sets 幂集
![[Pasted image 20230404081633.png]]
幂集中的元素都是集合
If a set has *n* elements, then its power set has $2^n$ elements.

### 2.1.6 Cartesian Products 笛卡尔积
**ordered n-tuples 有序n元组**
![[Pasted image 20230404082104.png]]

**ordered pairs 序偶**：有序二元组
The ordered pairs (a, b) and (c, d) are equal if and only if a = c and b = d.

**Cartesian product 笛卡尔乘积**
![[Pasted image 20230404150800.png]]
**Note: The Cartesian product of anything with ∅ is ∅.**

![[Pasted image 20230404150905.png]]

+ 笛卡尔乘积不满足交换律
+ 笛卡尔乘积不满足结合律

### 2.1.7 Truth Sets and Quantififiers 真值集和量词
**Definition：**
Given a predicate P, and a domain D, The *truth set* of P(x) is denoted by **{x∈D | P(x)}**.

## 2.2 Set Operations 集合运算

### 2.2.1 Introduction 引言
**Definition 1**
Let A and B be sets. The **union（并集）** of the sets A and B, denoted by **A ∪ B**, is the set that contains those elements that are either in A or in B, or in both.

**Definition 2**
Let A and B be sets. The **intersection（交集）** of the sets A and B, denoted by **A ∩ B**, is the set containing those elements in both A and B.

**Definition 3**
Two sets are called **disjoint（不相交）** if their intersection is the empty set.

**Definition 4**
**complement（补集）**
![[Pasted image 20230404151724.png]]

**principle of inclusion–exclusion 容斥原理**
|A ∪ B| = |A| + |B| − |A ∩ B|

**Definition 5**
Let A and B be sets. The **difference（差）** of A and B, denoted by **A − B**, is the set containing those elements that are in A but not in B. The difference of A and B is also called the complement of B relative to A.
![[Pasted image 20230404093351.png]]
![[Pasted image 20230404151952.png]]

**symmetric difference（对称差）**
![[Pasted image 20230404152021.png]]

### 2.2.2 Set Identities 集合恒等式
![[Pasted image 20230404152319.png|inl|350]] ![[Pasted image 20230404152358.png|inl|300]]

![[Pasted image 20230404152822.png]]

**Proving Set Identities 证明集合恒等式**
1) Prove S1 ⊆ S2 and S2 ⊆ S1 separately.
2) Use a membership table.
3) Use set builder notation & logical equivalences.
![[Pasted image 20230404153133.png]]
![[Pasted image 20230404153201.png]]
![[Pasted image 20230404153216.png]]

### 2.2.3 Generalized Unions and Intersections 扩展的并集和交集
![[Pasted image 20230404153459.png]]

### 2.2.4 Computer Representation of Sets 集合的计算机表示
![[Pasted image 20230404154108.png]]
![[Pasted image 20230404154223.png]]

## 2.3 Function 函数
### 2.3.1 introduction 引言
+ Definition:
  >Let A and B be nonempty sets. A function f from A to B is an assignment of exactly one element of B to each element of A. We write f(a) = b if b is the unique element of B assigned by the function f to the element a of A. If f is a function from A to B, we write f : A → B.![[Pasted image 20230418155811.png]]

A is called the **domain（域/定义域）**
B is called the **codomain （陪域）**
If $f (x) = y$
+ y is called the **image (像)** of x under f **(value)**
+ x is called a **preimage (源像) ****** of y **(argument)**
The **range (值域)** of f is the set of all images of set $A$ under $f$. It is denoted by $f (A)$.
![[Pasted image 20230418160046.png]]

### 2.3.2 Special types of Functions 特殊种类的函数
**1. One-to-One Functions**
A function f is said to be one-to-one, or an injection, if and only if f(a) = f(b) implies that a = b for all a and b in the domain of f. A function is said to be injective if it is one-to-one.
![[Pasted image 20230418160540.png]]

___Sufficient conditions for 1-1 functions___
For functions f over numbers, we say:
+ f is strictly (or monotonically) increasing iff **x>y → f(x)>f(y)** for all x,y in domain;
+ f is strictly (or monotonically) decreasing iff **x>y → f(x)<f(y)** for all x,y in domain;
+ If f is either strictly increasing or strictly decreasing, then f is one-to-one. 
+ *Converse is not necessarily true. E.g. 1/x*

**2. Onto (Surjective) Functions**
A function f from A to B is called onto, or a surjection, if and only if for every element b ∈ B there is an element a ∈ A with f(a) = b. A function f is called surjective if it is onto.
![[Pasted image 20230418161144.png]]

**3. Bijection Functions**
A function f is said to be a **one-to-one correspondence**, or a **bijection**, or **reversible**, or **invertible**, iff it is both one-to-one and onto.

+ If two finite sets can be placed into 1-1 correspondence, then they have the same size

### 2.3.3 Properties of functions 函数的特性
**Function Operations**
![[Pasted image 20230418161850.png]]
![[Pasted image 20230418161904.png]]

**The Identity Function 恒等函数**
![[Pasted image 20230418193041.png]]

**Inverse Functions 反函数**
![[Pasted image 20230418193257.png]]

**Composition of Functions 合成函数**
![[Pasted image 20230418193407.png]]
+ The commutative law does not hold for the composition of functions.
+ The associative law holds for the composition of functions.
![[Pasted image 20230418193456.png]]

![[Pasted image 20230418193551.png]]

### 2.3.4 Graphs of Functions 函数的图
![[Pasted image 20230418193746.png]]

### 2.3.5 Some Important functions 一些重要函数
1. **Floor and ceiling function**
![[Pasted image 20230418194016.png]]
Application: Truncation used in computer network and communication network
![[Pasted image 20230418194117.png]]
**Properties of floor and ceiling**
![[Pasted image 20230418194217.png]]

2. **Factorial function**
![[Pasted image 20230418194311.png]]

3. **Characteristic Functions**
![[Pasted image 20230418194434.png]]

4. **Mod-n Functions**
![[Pasted image 20230418194518.png]]

5. **Partial Functions**
![[Pasted image 20230418194546.png]]

## 2.4 Sequences and Summations 序列与求和
### 2.4.1 Introduction 引言
A **sequence** or **series** is just like an ordered n-tuple,
except:
+ Each element in the series has an associated ***index*** number.
+ A sequence or series may be ***infinite***.

A **summation** is a compact notation for the sum of all terms in a (possibly infinite) series.

### 2.4.2 Sequences 序列
![[Pasted image 20230418202221.png]]

### 2.4.3 Recurrence relations 递推关系
![[Pasted image 20230418202551.png]]
![[Pasted image 20230418202601.png]]

**Fibonacci sequence 斐波那契数列**
![[Pasted image 20230418202643.png]]

**closed Formula 闭公式**
Definition：
We say that we have solved the recurrence relation together with the initial conditions when we find an **explicit formula**, called a **closed formula**, for the terms of the sequence.
![[Pasted image 20230418203001.png]]

### 2.4.4 Special sequences 特殊的序列
![[Pasted image 20230418203103.png]]

### 2.4.5 Summation 求和
![[Pasted image 20230418203152.png]]

**Manipulations**
![[Pasted image 20230418203421.png]]

**Some Shortcut Expressions**
![[Pasted image 20230418203618.png]]

## 2.5 Cardinality of Sets 集合的基数

### 2.5.1 Introduction 引言
Definition:
The number of distinct elements in set A, denoted |A|, is called the **cardinality** of A.

**Definition 1**
The sets $A$ and $B$ have the same **cardinality** if and only if there is a *one-to-one correspondence* from $A$ to $B$. When $A$ and $B$ have the same cardinality, we write $|A| = |B|$.
![[Pasted image 20230425190729.png]]
![[Pasted image 20230425191103.png]]

### 2.5.2 Countable Sets 可数集合
**Definition:**
For any set $S$, if $S$ is finite or if $|S|=|N|$, we say that S is **countable**. Else, $S$ is **uncountable**.
Examples: $N$，$Z$
Examples: $R$

**Definition:**
The cardinalities of infinite sets are not natural numbers, but are special objects called **transfinite cardinal numbers (超限基数)**.

When an infinite set $S$ is countable, we denote the cardinality of $S$ by $ℵ₀$ (where $ℵ$ is aleph, the first letter of the Hebrew alphabet). We write $|S| = ℵ₀$ and say that $S$ has cardinality “aleph null.”

The **continuum hypothesis (连续统假设)** claims that $ℵ₁ :≡ |R|$, the **second transfinite cardinal**.

## 2.6 Matrices 矩阵

|Properties of Matrices |矩阵的性质|
|:------:|:------:|
|Matrix Equality|矩阵相等|
|Matrix Sums|矩阵和|
|Matrix Products|矩阵积|
|Identity Matrices|单位矩阵|
|Matrix Inverses|矩阵的逆|
|Powers of Matrices|矩阵的幂|
|Matrix Transposition|转置矩阵|
|Symmetric Matrices|对称矩阵|
|Zero-One Matrices|0-1矩阵|

### Zero-One Matrices 0-1矩阵
![[Pasted image 20230425201713.png]]

### Boolean Products 布尔积
![[Pasted image 20230425202005.png]]
![[Pasted image 20230425202027.png]]

### Basic properties 基本性质
![[Pasted image 20230425202629.png]]

---
# 3. Algorithms 算法

## 3.1 Algorithms 算法
### 3.1.1 Algorithm Characteristics 算法的性质

|名称|性质|
|:----:|:----:|
|Input(输入).|Information or data that comes in.|
|Output (输出).|Information or data that goes out.|
|Definiteness(确定性).| Algorithm is precisely defined.|
|Correctness(正确性).| Outputs correctly relate to inputs.|
|Finiteness(有限性).|Won’t take forever to describe or run.|
|Effectiveness(有效性).| Individual steps are all do-able.|
|Generality(通用性).| Works for many possible inputs.|
|Efficiency(高效性).|Takes little time & memory to run.|

**Pseudocode Language 伪代码**
![[Pasted image 20230425211456.png]]
![[Pasted image 20230425211818.png]]
![[Pasted image 20230425211840.png]]
![[Pasted image 20230425211916.png]]

### 3.1.2 Searching Algorithms 搜索算法
#### Linear Search 线性搜索
![[Pasted image 20230425212155.png]]

#### Binary Search 二分搜索
![[Pasted image 20230425212223.png]]

### 3.1.3 Sorting 排序算法
#### Bubble sort 冒泡排序
**procedure** bubblesort($a₁,… , an$ : real numbers with $n ≥ 2$)
for i := 1 to $n − 1$
	for j := 1 to $n − i$
		if $aj > aj₊₁$ then interchange $aj$ and $aj₊₁$
{$a₁,… , an$ is in increasing order}

#### Insertion sort 插入排序
![[Pasted image 20230425212646.png]]

### 3.1.5 Greedy Algorithms 贪心算法
![[Pasted image 20230425212732.png]]

## 3.2 Growth of functions 函数的增长

### 3.2.1 Orders of Growth 增长的阶
We say $f_A (n)=30n+8$ is *(at most) order n*, or $O(n)$. It is at most roughly proportional to $n$
We say $f_B (n)=n^2+1$ is *order $n^2$* , or $O(n^2)$. It is (at most) roughly proportional to $n^2$ .

### 3.2.2 The Big-O Notation 大O记号
#### 大O
‘$f$ is $O(g)$’ or ‘$f$ is $big-O \ of\ g$’ ***iff***
$$∃k\exists c\forall n(n>k → |f(n)| ≤ c|g(n)|)$$
‘$f$ is at most order $g$’, or ‘$f$ is $O(g)$’ or ‘$f =O(g)$’ all just mean that $f\in O(g)$.
**实际上相当于给出函数的渐进上界**

**Note:**
Choose $k$, choose $c$ which may depend on the choice of $k$.
Once you choose $k$ and $c$, you must prove the truth of the *implication* (often by induction).

***$k, c$ : witnesses(凭证) to the relationship $f(x)$ is $O(g(x))$***

#### 小o
If
$$\lim_{n\to \infty}{\frac{f(n)}{g(n)}} = 0 $$
Then $f$ is $o(g)$ (called little-o of g)
$$o(g) : \equiv \{ f |\forall c>0 \exists k \forall x(x>k → |f(x)| < c|g(x)|\}$$
**Theorem**
If $f$ is $o(g)$ then $f$ is $O(g)$.

### 3.2.3 Some important Big-O results 一些重要函数的大O估算
$f(x) = a_n x^n+a_{n-1} x^{n-1}+…+ a_1 x+a_0$ then $f(x)$ is $O(x^n )$

$n!$ is $O(n^n )$
$log\  n!$ is $O(nlogn)$ 
$log\ n$ is $O(n)$

![[Pasted image 20230510151119.png]]

### 3.2.4 Useful Big-O Estimates 有用的大O估计
+ If $d > c > 1$, then $n^c$ is $O(n^d )$, but $n^d$ is not $O(n^c )$.
+ If $b > 1$ and $c, d$ are positive, then $(log_b\ n) ^c$ is $O(n ^d )$, but $n ^d$ is not $O((log_b\ n)^ c )$.
+ If $b > 1$ and $d$ is positive, then $n ^d$ is $O(b ^n )$, but $b^ n$ is not $O(n ^d )$.
+ If $c > b > 1$, then $b ^n$ is $O(c ^n )$, but $c ^n$ is not $O(b ^n )$.
+ If $c > 1$, then $c ^n$ is $O(n!)$, but $n!$ is not $O(c^n )$.

### 3.2.5 Growth of combinations of functions 函数组合的增长
Suppose that $f_1$ is $O(g_1 )$ and $f_2$ is $O(g_2 )$ . Then $f_1 + f_2$ is $O(max\{ g_1 , g_2 \})$

Suppose that $f_1$ is $O(g_1 )$ and $f_2$ is $O(g_2 )$ .Then $f_1f_2$ is $O(g_1g_2 )$

### 3.2.6 Big-omega notation:  $\Omega$ 大 $\Omega$ 记号
$$\exists k\exists c \forall n[n > k → | f(n)| \ge c| g(n)| ]$$
**实际上相当于给出函数的渐进下界**

### 3.2.7 Big-Theta notation:  $\Theta$  大 $\Theta$  记号
$$f\in \Omega (g)\ and\ f\in O(g)$$
**互为渐进上界**

## 3.3 Complexity of Algorithms 算法的复杂度

### 3.3.1 Algorithmic Complexity 算法复杂度
Time complexity: # of operations or steps required
Space complexity: # of memory bits required

### 3.3.2  Time complexity 时间复杂度

#### Max algorithm 最大值算法
$$\Theta (n)$$
#### Linear Search 线性搜索
$$\Theta (n)$$
#### Binary Search 二分搜索
$$\Theta (log\ n)$$

### 3.3.3 Some orders of growth 一些增长的顺序
$\Theta (1)$                        Constant 常量复杂度
$\Theta (log_c\ n)$                  Logarithmic (same order $\forall$c) 对数复杂度
$\Theta (log\ n^ c )$                  Polylogarithmic(With c a constant.) 
$\Theta (n)$                        Linear  线性复杂度
$\Theta (nlog\ n)$                 Linear logarithmic          线性对数复杂度
$\Theta (n ^c )$                       Polynomial (for any c)   多项式复杂度
$\Theta (c ^n )$                       Exponential (for c>1)     指数复杂度
$\Theta (n!)$                       Factoria                         阶乘复杂度
![[Pasted image 20230510154031.png]]

### 3.3.4 Problem Complexity 问题复杂度
问题复杂度指解决该问题或执行该任务的复杂度增长最低阶的算法的复杂度

#### Tractable vs. intractable 易解的vs 难解的
**Definition：**
A problem or algorithm with at most polynomial time complexity is considered ***tractable*** (or *feasible*).
**P** (Polynomial) problem is the set of all tractable problems.
A problem or algorithm that has complexity greater than polynomial is considered ***intractable*** (or *infeasible*).

#### P vs. NP
**Definition:**
+ **NP** (Nondeterministic Polynomial time) is the set of problems for which there exists a tractable algorithm for ***checking a proposed*** solution to tell if it is correct.
+ We know that $P\subseteq NP$.
+ the most famous unproven conjecture in computer science is that this inclusion is proper.
  i.e., that $P\subset NP$ rather than $P=NP$

#### NP-Complete Problem
**Definition:**
NPC满足两个条件：
+ 是一个NP问题。
+ 其他NP问题能够在多项式时间内**规约**（转化）为该问题（该问题的复杂度大于原NP问题）。
NPC示例：可满足性问题、旅行商问题TSP、汉密尔顿回路问题等。

#### NP-Hard Problem 
+ NP问题能够在多项式时间内规约（转化）为某个问题X，X的复杂度一般大于原NP问题，若X是一个NP问题，则称X是NPC的，否则X是NP-Hard的。
+ NPH问题满足NPC问题的第2个条件但不满足第1个条件，也就是说NPH不一定是NP问题，NPH问题比NPC问题范围广，更难以解决。

![[Pasted image 20230510155146.png]]

#### Unsolvable problems
problems unsolvable by any algorithm

### 3.3.5 Rules for determining the $\Theta$-Class 确定$\Theta$类的规则
1. $\Theta (1)$ functions are constant and have zero growth.
2. $\Theta (log(n))$ is lower than $\Theta (n ^k )$ if $k>0$.
3. $\Theta (n ^a )$ is lower than $\Theta (n ^b )$ if and only if $0<a<b$.
4. $\Theta (a ^n )$ is lower than $\Theta (b ^n )$ if and only if $0<a<b$.
5. $\Theta (n ^k )$ is lower than $\Theta (a ^n )$ for any power of $n ^k$ and any $a>1$.
6. $\Theta (a ^n )$ is lower than $\Theta (n!)$ for any $a>1$.
7. $\Theta (n!)$ is lower than $\Theta (n ^n )$
8. If $r$ is not zero, then $\Theta (rf) = \Theta (f)$ for any function $f$.
9. If $h$ is a non zero function and $\Theta (f)$ is lower than (or same order as) $\Theta (g)$, then $\Theta (fh)$ is lower than (or same order as) $\Theta (gh)$.
10. If $\Theta (f)$ is lower than $\Theta (g)$, then $\Theta (f+g)= \Theta (g)$

---
# 4. Number Theory and Cryptography 数论和密码学

## 4.1 Divisibility and Modular Arithmetic 整除性和模算术

### 4.1.1 Divides, Factor, Multiple 整除，因子，倍数
**Definition：**
$$a|b \equiv\  a\ divides\ b \equiv: (\exists c\in Z: b=ac)$$
Iff a divides b, then we say a is a ***factor*** or a ***divisor*** of b, and b is a ***multiple*** of a.
![[Pasted image 20230516081138.png]]

**Theorem 1: **
$\forall a,b,c \in Z, a \neq 0$
1. $a|0$
2. $(a|b \wedge a|c) → a | (b + c)$
3. $a|b → a|bc$
4. $(a|b \wedge b|c) → a|c$

**Corollary 1：**
$$\forall a,b,c,m,n \in Z: (a|b \wedge a|c) → a | (mb +nc)$$

### 4.1.2 The Division “Algorithm” 除法算法
$$\forall a,d\in Z, d≠0: \exists !q,r\in Z:0\leq r<|d|, a=dq+r$$
$q=a\ div\ d, r=a\ mod\ d$

### 4.1.3 The mod operator 取模运算符
![[Pasted image 20230516082142.png]]

### 4.1.4 Arithmetic Modulo m 模算数
#### 4.1.4.1 Definition 定义
![[Pasted image 20230516082251.png]]

#### 4.1.4.2 Modular Congruence 模同余
![[Pasted image 20230516082337.png]]

#### 4.1.4.3 Useful Congruence Theorems 常用的同余定理
![[Pasted image 20230516082426.png]]
![[Pasted image 20230516082439.png]]

## 4.2 Integers Representations & Algorithms 整数表示和算法
![[Pasted image 20230516112547.png]]

### 4.2.1 Algorithms for Integer Operations 整除运算算法

#### 4.2.1.1 Addition of Binary Numbers 二进制加法
![[Pasted image 20230516082952.png]]

#### 4.2.1.2 Multiplication of Binary Numbers 二进制乘法
![[Pasted image 20230516083028.png]]

#### 4.2.1.3 Binary Division with Remainder 二进制除法与余数
![[Pasted image 20230516083055.png]]

### 4.2.3 Modular Exponentiation 模指数运算
![[Pasted image 20230516083839.png]]

![[Pasted image 20230516084411.png]]

## 4.3 Primes and GCD 素数和最大公约数

### 4.3.1 Prime Numbers 素数
$p\ is\ prime \Leftrightarrow p>1 \wedge \neg \exists a\in N: (1<a<p \wedge a|p)$

### 4.3.2 Theorems about Prime 素数的定理
**Theorem 1: Fundamental Theorem of Arithmetic 算术基本定理
Prime Factorization (质因数分解):**
Every positive integer has a ***unique*** representation as the product of a non-decreasing series of ***zero or more primes***.
(每个正整数都可唯一地表示为0个或多个非递减素数的乘积)

**Theorem 2：Trial Division (试除定理)**
If $n$ is a composite integer, then $n$ has a prime divisor less than or equal to $\sqrt{n}$.

**Theorem 3: There are infinitely many primes.**

**Theorem 4: The prime number theorem**
**Distribution of Primes (素数分布)**
The ratio of the number of primes not exceeding $x$ and $x/lnx$ approaches $1$ as $x$ grows without bound.
当x无约束增长时，不超过x的质数数与x/lnx的比率趋于1。
The theorem tells us that the number of primes not exceeding $x$, can be approximated by $x/ln x$. (不超过$x$的素数的个数近似为$x/ln x$)
The odds that a randomly selected positive integer less than $n$ is prime are approximately $(n/ln\ n)/n = 1/ln\ n$. (随机选择一个小于$n$的正整数是素数的概率近似为$1/ln\ n$)

### 4.3.2 Greatest Common Divisor 最大公约数
**GCD Shortcut：**
![[Pasted image 20230516090730.png]]

### 4.3.3 Relative Primality 互质
**Definition：**
+ Integers a and b are called ***relatively prime*** or ***coprime***(互质) iff $gcd(a,b)\ =\ 1$.
+ A set of integers ${a_1 ,a_2 ,…}$ is ***pairwise relatively prime***(两两互质) if all pairs $(a_i , a_j )$, for $i\neq j$, are relatively prime.

### 4.3.4 Least Common Multiple 最小公倍数
**LCM Shortcut：**
![[Pasted image 20230516090926.png]]

**Theorem 5:**
Let a and b be positive Integers. Then $ab=gcd(a,b) · lcm(a,b)$

### 4.3.5 Euclid’s Algorithm for GCD 欧几里得算法
**辗转相除法**

**Lemma 1:**
Let $a = bq + r$, where a, b, q, and r are integers.
Then $gcd(a,b) = gcd(b,r)$.

![[Pasted image 20230516091757.png]]

### 4.3.6 gcds as Linear Combinations gcd的线性组合表示
#### 4.3.6.1 Bézout’s Theorem 贝祖定理
If $a$ and $b$ are positive integers, then there exist integers $s$ and $t$ such that $gcd(a,b) = sa + tb$.

This method is a **two pass method**. It first uses the Euclidian algorithm to find the gcd and then works backwards to express the gcd as a linear combination of the original two integers.

#### 4.3.6.2 Consequences of Bézout’s Theorem 贝祖定理的推论
**Lemma 2：**
If a, b, and c are positive integers such that $gcd(a, b) = 1$ and $a | bc$, then $a | c$.

**Theorem 7：**
Let $m$ be a positive integer and let $a, b$ and $c$ be integers.
If $ac ≡ bc (mod\ m)$ and $gcd(c, m) =1$, then $a ≡ b (mod\ m）$

**Lemma 3:**
If $p$ is prime and $p | a_1a_2 ...a_n$ , then $p | a_i$ for some $i$

**Uniqueness theorem：**
A prime factorization of a positive integer where the primes are in nondecreasing order is unique.

## 4.4 Solving Congruences 求解线性同余方程

### 4.4.1 Definition 引言
A congruence of the form $ax ≡ b (mod m)$, where $m$ is a positive integer, $a$ and $b$ are integers, and $x$ is a variable, is called a **linear congruence**.

### 4.4.2 Linear Congruences 线性同余方程

#### 4.4.2.1 Method 方法
One method that we will describe uses an integer if such an integer exists. Such an integer ā is said to be an **inverse of a modulo m (a模m的逆元)**.
$$āa ≡ 1 (mod\ m)$$
#### 4.4.2.2 Theorem 1 定理1
+ If a and m are relatively prime integers and $m > 1$, then an inverse of a modulo $m$ exists.
+ a模m的任何其他逆与该逆为模m的同余

#### 4.4.2.3 Using Inverses to Solve Congruences 用逆元求解线性同余方程
**Definition：**
We can solve the congruence $ax ≡ b (mod\ m)$ by multiplying both sides by $ā$. $$x ≡ ā \cdot b (mod\ m)$$

### 4.4.3 The Chinese Remainder Theorem 中国剩余定理
***中国剩余定理需要互质，反向替代不需要***
#### 4.4.3.1 Theorem 2: (The Chinese Remainder Theorem:CRT) 定理2
+ Let $m_1 ,m_2 ,…,m_n$ be pairwise relatively prime positive integers greater than $1$ and $a_1 ,a_2 ,…,a_n$ be arbitrary integers. Then the system
  $$x ≡ a_1 ( mod\ m_1 ) ,
  x ≡ a_2 ( mod\ m_2 ),
  …,
  x ≡ a_n ( mod\ m_n )$$
  has a unique solution modulo $m$ while $m = m_1m_2 ... m_n$ .
+ That is, there is a solution $x$ with $0 ≤ x <m$ and all other solutions are congruent modulo $m$ to this solution.
![[Pasted image 20230523085249.png]]

#### 4.4.3.2 Back Substitution 反向替代/后向代入法
![[Pasted image 20230523084129.png]]

### 4.4.4 Computer Arithmetic with large Integers 大整数的计算机算术

### 4.4.5 Fermat’s Little Theorem 费马小定理
**Theorem 3:**
If $p$ is prime and $a$ is an integer not divisible by $p$, then
$$a^{p-1} ≡ 1 (mod\ p)$$
Furthermore, for every integer a we have
$$a ^p ≡ a (mod\ p)$$

### 4.4.6 Pseudoprimes 伪素数
#### Definition 1
If $n$ is a composite integer, and $$b ^{n-1} ≡ 1 (mod\ n)$$ then $n$ is called a ***pseudoprime to the base b***（基数b的伪素数）

#### Definition 2: Carmichael Numbers 卡迈克尔数
There are composite integers $n$ that pass all tests with bases $b$ such that $gcd(b,n) = 1$.
A composite integer $n$ that satisfies the congruence $b^ {n-1} ≡ 1 (mod\ n)$ for all positive integers $b$ with $gcd(b,n) = 1$ is called a Carmichael number.
1. $n$ 是合数
2. 对于所有与$n$ 互质的数$b$ 而言，$n$ 都是伪素数

### 4.4.7 Primitive Roots and Discrete Logarithms 原根和离散对数
**Definition 3：**
A primitive root modulo a prime $p$ is an integer $r$ in $Z_p$ , such that every nonzero element of $Z_p$ is a power of $r$.
$p$ 为素数，若存在一个正整数$r$，使得 $r, r^2 , r ^3 , … , r ^{p−1}$ 模$p$ 互不同余，则称$r$ 为模$p$ 的一个原根
There is a primitive root modulo p for every prime number p.

**Definition 4：**
Suppose that $p$ is a prime, $r$ is a primitive root modulo $p$, and $a$ is an integer between $1$ and $p−1$ inclusive ($Z_p$ ).
If $r ^e ≡ a (mod\ p)$ and $0 ≤e≤p−1$, we say that $e$ is the **discrete logarithm** of a modulo $p$ to the base $r$ and we write $log_r\ a = e$ (where the prime $p$ is understood)

---
# 5. Induction and Recursion 归纳与递归

## 5.1 Mathematical Induction 数学归纳法
![[Pasted image 20230530080817.png]]
***Outline of an Inductive Proof:***
Let us say we want to prove $\forall nP(n)$.
Do the base case (or basis step): Prove $P(1)$.
Do the inductive step: Prove $\forall k(P(k)→P(k+1))$.
+ E.g. you could use a direct proof, as follows:
  Let $k\in N$, assume $P(k)$. (inductive hypothesis)
  Now, under this assumption, prove $P(k+1)$.
By mathematical induction, $\forall nP(n)$ is true.

## 5.2 Strong Induction 强归纳法
![[Pasted image 20230530081801.png]]

***example：***
![[Pasted image 20230530083544.png]]

|计算几何| |
| :----: | :----: |
|Polygon|多边形|
|Vertex|多边形顶点|
|Simple|简单多边形|
|Interior|多边形内部|
|Exterior|多边形外部|
|Diagonal|对角线|
|Convex|凸多边形
|Triangulation|三角化

###  The Method of Infinite Descent 无限递降法/费马递降法
![[Pasted image 20230530090018.png]]

## 5.3 Recursive Definitions and Structural Induction 递归定义与结构归纳法

### 5.3.1 definitions 定义
In ***induction (归纳)***, we prove all members of an infinite set satisfy some predicate P by:
+ proving the truth of the predicate for larger members in terms of that of smaller members.
In ***recursive definitions (递归定义)***, we similarly define a function, a predicate, a set, or a more complex structure over an infinite domain (universe of discourse) by:
+ defining the function, predicate value, set membership, or structure of larger elements in terms of those of smaller ones.
In ***structural induction (结构归纳)***, we inductively prove properties of recursively-defined objects in a way that parallels the objects’ own recursive definitions. (用对象自己的递归定义来归纳地证明递归定义对象的属性)
***Recursion（递归）*** is the general term for the practice of defining an object in terms of itself or of part of itself. (This may seem circular, but it isn’t necessarily.)

### 5.3.2 Lamé’s Theorem 拉梅定理
Theorem:
$\forall a,b\in N, a≥b>0$, the number of steps in Euclid’s algorithm to find $gcd(a,b)$ is $≤ 5k$, where $k = \lfloor {log_{10} b}\rfloor +1$ is the number of decimal digits in $b$.
Thus, Euclid’s algorithm is linear-time in the number of digits in $b$.

### 5.3.3 Recursively Defined Sets 递归地定义集合
***Definition:***
An ***infinite set S*** may be defined recursively, by giving:
+ A small finite set of ***base*** elements of S.
+ A ***rule*** for constructing new elements of S from previously-established elements.
+ Implicitly, S has no other elements but these.

---
# 6. Counting 计数

## 6.1 Basics of Counting 计数基础
![[Pasted image 20230606082058.png]]
![[Pasted image 20230606082114.png]]
![[Pasted image 20230606082130.png]]
![[Pasted image 20230606082143.png]]

## 6.2 Pigeonhole Principle 鸽巢原理

### 6.2.1 Definition 定义
+ If $≥k+1$ objects are assigned to $k$ places, then at least $1$ place must be assigned $≥2$ objects.
+ In terms of the assignment function: If $f:A→B$ and $|A|≥|B|+1$, then some element of $B$ has $≥2$ preimages under $f$.

### 6.2.2 Generalized Pigeonhole Principle 广义鸽巢原理(G.P,P)
If $N$ objects are assigned to $k$ places, then at least one place must be assigned at least $\lceil N/k\rceil$ objects.

### 6.2.3 Ramsey theory 拉姆齐理论
![[Pasted image 20230606085806.png]]

## 6.3 Permutations and Combinations 排列与组合

### 6.3.1 Permutations 排列
**Definition:**
+ A *permutation* of a set $S$ of objects is a sequence that contains each object in $S$ exactly once.
+ An ordered arrangement of r **distinct** elements of S is called an *r-permutation of S*.

**Theorem 1:**
The number of r-permutations of a set with $|S|=n$ elements is $$P(n,r) = n(n−1)…(n−r+1) = \frac {n!}{(n−r)!}$$

### 6.3.2 Combinations 组合
**Definition:**
+ An r-combination of elements of a set $S$ is simply a subset $T\subseteq S$ with $r$ members, $|T|=r$.

**Theorem 2:**
+ The number of r-combinations of a set with $|S|=n$ elements is
$$C(n,r)=\frac {P(n,r)}{P(r,r)}=\frac{n!/(n-r)!}{r!}=\frac{n!}{r!(n-r)!}$$
+ **Corollary:** C(n,r) = C(n, n−r)

## 6.5 Generalized Permutations and Combinations 排列与组合的推广

### 6.5.1 Permutation with repetition 有重复的排列
**Theorem 1:**
The number of r-permutations of a set of $n$ objects with repetition allowed is $n^r$.

### 6.5.2 Combinations with Repetition 有重复的组合
**Theorem 2:**
The number of r-combinations from a set with $n$ elements when repetition of elements is allowed is $C(n + r – 1,r) = C(n + r – 1, n –1)$.

### 6.5.3 Summarizing the Formulas 公式总结
![[Pasted image 20230606102854.png]]

### 6.5.4 Permutations with Indistinguishable Objects 无区别物体集合的排列
**Theorem 3**
The number of different permutations of $n$ objects, where there are $n_1$ indistinguishable objects of type $1$, $n_2$ indistinguishable objects of type $2$,…and $n_k$ indistinguishable objects of type $k$, is$$\frac{n!}{n_1!n_2!...n_k!}$$

### 6.5.5 Distributing Objects into Boxes 把物体放入盒子
**Distinguishable objects and distinguishable boxes**
**Theorem 4**
The number of ways to distribute $n$ distinguishable objects into $k$ distinguishable boxes so that $n_i$ objects are placed into box $i, i=1,2,…k$, equals$$\frac{n!}{n_1!n_2!...n_k!}$$
**Indistinguishable objects and distinguishable boxes**
There are $C(n + r−1, r)$ ways to place r indistinguishable objects into $n$ distinguishable boxes.


---
***Discrete Mathematics下***
# 8. Advanced Counting Techniques 高级计数技术
## 8.1 Recurrence Relations 递推关系
**参考：** PPT+教材
答题格式：初始条件+递归公式+成立范围（e.g. $n\geq 3$）
+ ***EXAMPLES***
  >兔子和斐波那契数列
  >汉诺塔
  >编码字的枚举
  >*Catalan Numbers 卡塔兰数*
  >书上各例
## 8.2 Solving Recurrence Relations 求解递推关系
**参考：** PPT+教材+ [8.2解决递推式(Solving Recurrences) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12153683.html)
+ ***A linear homogeneous recurrence of degree k with constant coefficients (“k-LiHoReCoCo”）k 阶定常系数线性齐次递推关系***
> ![[Pasted image 20231116102222.png|350]]
+ ***Characteristic equation 特征方程***
> ![[Pasted image 20231116102704.png#center|定义|300]]
> 方程的解叫做该递推关系的特征根 **characteristic roots**
+ ***利用特征方程和特征根解决递推关系***
  + 一些定理
> 以 2 阶定常系数线性齐次递推关系 $a_n=c_1a_{n-1}+c_2a_{n-2}$ 为基础
> **情况 1:** 有两个不等的根 $r_1\neq r_2$ ![[Pasted image 20231116103053.png|500]] $a_1,a_1$ 通过初始条件求得
> **情况 2:** 有两个相等的根 $r_1=r_2=r_0$ ![[Pasted image 20231116103116.png|500]] **情况 3:** 有 $k$ 个不等的根 ![[Pasted image 20231116103152.png|500]] **情况 4:** 有 $k$ 个根，其中有 $m$ 个相等的根 ![[Pasted image 20231116103209.png|500]]
> 举例计算见教材

+ ***推广到 $k$ 阶定常系数线性*非*齐次递推关系 LiNoReCoCos***
>形如：$a_n=c_1a_{n-1}+c_2a_{n-2}+\cdots+c_ka_{n-k}+F(n)$
>*相伴的齐次递推关系* $a_n=c_1 a_{n-1}+c_2 a_{n-2}+\cdots+c_ka_{n-k}$ 
>The associated homogeneous recurrence relation (associated LiHoReCoCo)
>
>>求解非齐次递推关系的**一些定理**
> ![[Pasted image 20231116105642.png|600]] 先求通解，然后求特解，最后求通解的系数
>**example**
>> ![[Pasted image 20231116110612.png|500]] ![[Pasted image 20231116110631.png|500]]
>
> ![[Pasted image 20231116110926.png|600]]


## 8.3 Divide-and-Conquer Algorithms and Recurrence Relations 分治算法和递推关系
**参考：** PPT+教材
+ ***分治递推关系***
>一个递归算法将一个规模为 $n$ 的问题分成 $a$ 个子问题，每个子问题的规模是 $\frac{n}{b}$.
>假设把子问题的解组合成原来问题的解的算法处理步骤中需要总量为 $g(n)$ 的额外运算
>那么, 若 $f(n)$ 表示求解原问题所需的运算数，则
>> $f(n)=af(\frac{n}{b})+g(n)$

+ ***Example***
  Binary search 二分搜索 ![[Pasted image 20231123100715.png|inl|100]]
  Merge sort 归并排序 ![[Pasted image 20231123101119.png|inl|100]]
  Fast Multiplication Example 整数的快速乘法 ![[Pasted image 20231123101512.png|inl|100]]
  ![[Pasted image 20231123101429.png|L|400]]
![[Pasted image 20231123101738.png#L|恒等式推导过程|300]]











+ ***定理 1***
  > ![[Pasted image 20231123102019.png|600]]
> ***example***
>> ![[Pasted image 20231123102412.png|500]]

+ ***定理 2 The Master Theorem 主定理***
  > ![[Pasted image 20231123102542.png]]
  > ***example***
  >> ![[Pasted image 20231123102745.png|500]]
  
+ ***Backtracking 回溯法***
  > ![[Pasted image 20231123103231.png|inl|250]] ![[Pasted image 20231123103313.png|inl|250]]
  
## 8.4 Generating Functions 生成函数
**参考：** PPT+教材
### 8.4.1 定义 1
  > ![[Pasted image 20231123103509.png]]
  > ![[Pasted image 20231123103526.png]]
  > 有时该函数叫做 **ordinary generating function 普通生成函数**
  > ***example***
  > > ![[Pasted image 20231123104058.png]]
  > **要记住：**![[Pasted image 20231123104138.png|inl|300]]

### 8.4.2 Useful Facts About Power Series 幂级数的有用事实
+ ***example***
> ![[Pasted image 20231123104425.png|400]]

+ ***定理 1***
  > ![[Pasted image 20231123104512.png|450]]
  
+ ***定义 2 extended binomial coefficient 广义二项式系数***
  > ![[Pasted image 20231123104837.png|470]]
  > 当上面的参数 $u$ 为负整数时，广义二项式系数可以用通常的二项式系数的项表示：
  > > ![[Pasted image 20231123105131.png|450]]
  
+ ***定理 2 The extended binomial theorem 广义二项式定理***
  >设 $x$ 是实数，$\left |x\right |<1$, $u$ 是实数，则
  > ![[Pasted image 20231123105350.png|200]]
  
+ ***Useful Generating Functions 常用的生成函数***
  > ![[Pasted image 20231123105646.png|600]] **5-8 需要记得**

### 8.4.3 Counting problems and Generating Functions 计数问题和生成函数
**书上例题**
![[Pasted image 20231123110230.png|500]]
例题 14、15 解题过程看懂就能理解生成函数的应用
### 8.4.4 Using Generating Functions to Solve Recurrence Relations 使用生成函数求解递推关系
**同 8.4.3**
### 8.4.5 Proving Identities via Generating Functions 使用生成函数证明恒等式
**同上**

---
# 9. Relations 关系
## 9.1 Relations and Their Properties 关系及其性质
***参考：*** PPT+[9.1 关系及关系性质 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868593.html)
### 9.1.1 基本概念，前提须知
+ ***Ordered pair (序偶)***
  An ordered pair (a, b) is a listing of the objects a and b in a prescribed order, with a appearing first and b appearing second. 
  The ordered pairs $(a_1, b_1) = (a_2, b_2)$ 当且仅当 $a_1 = a_2\ and\ b_1 = b_2$

+ ***Cartesian product (笛卡尔积)***
  ![[Pasted image 20231108215615.png#center|笛卡尔积|300]]
+ ***m 元笛卡尔积***
  ![[Pasted image 20231108215751.png#center|m元笛卡尔积|300]]
+ ***Partitions (划分)***
  ![[Pasted image 20231108215959.png#center|划分定义]]
  非空集 A 的划分（或称为商集）的集合 P 具有以下性质：
  - A 的每个元素属于 P 中的一个集合
  - 如果 $A_1$ 和 $A_2$ 是 P 的不同元素，那么 $A_1∩A_2=∅$
### 9.1.2 Relations 关系
+ ***定义***
  设 A 和 B 是非空集，那么从 A 到 B 的一个关系 R 就是 $A×B$ 的一个子集，并且有以下性质：
  - 如果 R 属于 $A×B$ 并且 $(a，b)\in R$，我们就说 a 与 b 有关，写作：a R b。如果 a 与 b 无关，写作：a ~~R~~ b。
  - 通常，A 和 B 是相等的。在这种情况下，我们经常说 R 属于 A×A 是 A 上的关系. ![[Pasted image 20231108220703.png#center|定义]]
![[Pasted image 20231108221222.png#center|集合A的关系个数]]
+ ***Sets Arising from Relations 由关系产生的集合***
  ![[Pasted image 20231108221847.png#inl|由关系产生的集合|300]] ![[Pasted image 20231108222201.png#inl||300]]
+ ***定理***
  ![[Pasted image 20231108222314.png#inl|定理1|300]] ![[Pasted image 20231108222520.png#inl|定理2|300]]
### 9.1.3 二元关系的特殊性质
+ ***Reflexive (自反) and Irreflexive (反自反)***
   ![[Pasted image 20231108222703.png#center|自反定义|200]]
   Note:
   - 若 A = ∅，那么其也符合定义
   - The void relation on a void Universe is reflexive!  (全集 U 为∅时，空关系也是自反的)
   - 如果 U 不是空的，那么自反关系中的**所有**顶点 (vertices)都必须有环！
   ![[Pasted image 20231108222921.png#center|反自反定义|200]]
   Note:
   - 若 A = ∅，那么其也符合定义
   - 任何空关系都是反自反的
+ ***Symmetric (对称), Asymmetric (非对称), and Antisymmetric (反对称)***
  ![[Pasted image 20231108223506.png#inl|对称定义|200]] ![[Pasted image 20231108223549.png#inl|非对称定义|200]]
  ![[Pasted image 20231108223612.png#center|反对称定义|300]]
  Note:
  - 如果从 x 到 y 存在 arc，则从 y 到 x 不能有一个弧 arc
  - 如果（x，y）在 R 中并且 x≠y，则（y，x）一定不在 R 中 (anti反对称)

  Note:
   1. 对称和非对称不是矛盾对立关系 (即存在既不是对称也不是非对称的关系) ；对称和反对称也不是矛盾对立关系。
   2. 形式逻辑的定义：
      - 【对称关系】：当 aRb 为真时, bRa 必为真；
      - 【非对称关系】；当 aRb 为真时, bRa 必为假；
      - 【反对称关系】；当 aRb 为真时,bRa 有时真、有时假。
+ ***Transitive (传递)***
  ![[Pasted image 20231108223925.png#center|传递定义|300]]
  Note:
  - 如果有一个从 x 到 y 的 arc 和一个从 y 到 z 的 arc，则必须有一个从 x 到 z 的 arc
### 9.1.4 Combing relations 关系的组合
![[Pasted image 20231108224239.png|200]]
+ ***Composition 合成***
  ![[Pasted image 20231108224652.png#center|关系的合成|400]]
  The composition of R and S(R 和 S 的复合关系)，记作 SoR，定义为：
> 如果a∈A并且c∈C，那么有：a SoR c 当且仅当 存在b∈B，使得a R b and b S c.

  **定理：** 设 R 是从 A 到 B 的关系，S 是从 B 到 C 的关系。那么，如果 $A_1$ 是 A 的子集，我们有:  $(S\circ R)(A_1) = S(R(A_1))$
+ ***power 关系的幂***
  令 R 为 A 到 A 的关系，则 $R^n,n=1,2,3…$ 定义有：$R^1=R\ and\ R^{n+1}=R^n\circ R$
  **定理：** A 到 A 的关系 R 是 transitive (传递的) <==> $R^n⊆R,n=1,2,3…$

### 9.1.5 补充
+ ***等价关系***
  一个「等价关系」需要满足：自反性，对称性和传递性，缺一不可

+ 如果一个二元关系集合 P 定义在一个 n 元素集合 (设 A={1，2，3...... n})上，那么：
  - 满足 symmetric (对称)的集合个数为: $2^{\frac{n(n+1)}{2}}$ 个
    ![[Pasted image 20231109095738.png#center|示例|300]]
    满足对称性定义的最小元素组: ${(1,1)}, {(2,2)}, ......{(n,n)}$ 这 n 个单元素集合和 ${(1,2), (2,1)}, ......{(n-1,n), (n, n-1)}$ 这 $\frac{(n^2-n)}{2}$ 个元素组
    故：$sum=2^{n+\frac{(n^2-n)}{2}}=2^{\frac{n(n+1)}{2}}$ 个
  - 满足 antisymmetric (反对称)的集合个数为: $2^n*3^{\frac{n(n-1)}{2}}$ 个
  - 满足 asymmetric (非对称)的集合个数为: $3^{\frac{n(n-1)}{2}}$ 个
  - 满足 irreflexive (反自反)的集合个数为: $2^{n(n-1)}$ 个
  - 满足 reflexive (自反)同时 symmetric (对称)的集合个数为: $2^{\frac{n(n-1)}{2}}$ 个
  - 既不满足 reflexive (自反)又不 irreflexive (反自反)的集合个数为: $2^{n^2}-2\times 2^{n(n-1)}$ 个

## 9.2 n-ary Relations and Their Applications n 元关系及其应用
![[Pasted image 20231109101726.png#center|定义]]
![[Pasted image 20231109101756.png]]

![[Pasted image 20231109101956.png]]

![[Pasted image 20231109102008.png]]

![[Pasted image 20231109102017.png]]

## 9.3 Representing Relations 关系的表示
***参考：*** PPT+ [9.3 关系的表示 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868611.html)
### 9.3.1 关系的一般表示方法
- 将所有关系列出；
- 用一个到{T, F}的映射

### 9.3.2 用矩阵表示关系
+ ***connection matrix of R 邻接矩阵***
  ![[Pasted image 20231109102630.png#center|邻接矩阵定义|300]]
+ ***0-1 矩阵性质***
  - 拥有自反性 (reflexive)的 0-1 矩阵主对角线全为“1”
  - 拥有非自反性 (irreflexive)的 0-1 矩阵主对角线全为“0”
  - 拥有对称性 (symmetric)的 0-1 矩阵主对角线任意，关于主对角线对称的元素相等
  - 拥有反对称性(antisymmetric)的0-1矩阵主对角线任意，关于主对角线对称的元素不能同时为“1”
    ![[Pasted image 20231109102914.png#inl|自反性质|100]] ![[Pasted image 20231109103000.png#inl|非自反性质|100]] ![[Pasted image 20231109103102.png#inl|对称性质|100]] ![[Pasted image 20231109103126.png#inl|反对称性质|100]]
+ ***Composite of relations***
  - 定义两个邻接矩阵的 join 为这两个矩阵的布尔或运算 (boolean 'or')
  - 定义两个邻接矩阵的 meet 为这两个矩阵的布尔与运算 (boolean 'and')
  - 令 $M_{S\circ R}=[t_{ij}],M_R=[r_{ij}],M_S=[s_{ij}]$ 则 $M_{S\circ R}=M_R⊙M_S$  其中，⊙表示两个矩阵进行布尔乘运算 (boolean product)
    $M_{S\circ R}$ 的每个 $t_{ij}$ 由 $M_R$ 的第 i 行与 $M_S$ 的第 j 列进行布尔乘运算
### 9.3.3 用图表示关系
- 顶点(vertex)
- 边(arc or edge)
- 有向图 (directed graph or digraph)
+ ***in-degree and out-degree 入度和出度***
  - 顶点 a 的入度: 以顶点 a 为终点的箭头的个数
    ![[Pasted image 20231109104639.png]]
  - 顶点 a 的出度: 以顶点 a 为起点的箭头的个数
    ![[Pasted image 20231109104654.png]]
+ ***restriction 限制***
  ![[Pasted image 20231109104829.png]]
+ ***有特殊性质的图***
  - 具有自反性的图：每个节点都有自环
  - 具有反自反性的图：无自环节点
  - 具有对称性的图：所有箭头都是双向的
  - 具有反对称性的图：无双向箭头

## 9.4 Closures of Relations 关系闭包
***参考：*** PPT+ [9.4 关系的闭包 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868619.html)
### 9.4.1 定义
>关系 R 对于性质 P 的闭包，是加入最小数量的序偶，使得 R 恰好符合性质 P 所得到的集合
>R 的闭包 $R_1$ 具有如下 3 个特点: 
>>①. $R_1$ 包含 R 
>>②. $R_1$ 具有性质 P 
>>③. 如果 $R_2$ 具有性质 P 且 $R_2$ 包含 R，那么 $R_2$ 包含 $R_1$

### 9.4.2 不同类型的闭包
+ ***自反闭包 (reflexive closure)***
  >1. 在 R 的有向图的所有顶点上添加闭环
  >2. 令 R 的邻接矩阵的对角线上全为1
+ ***对称闭包 (symmetric closure)***
  >沿相反方向添加弧线(箭头)
+ ***传递闭包 (transitive closure)***
  >如果 a 到 b 连通，那么就添加从 a 到 b 的弧线(箭头)
  
### 9.4.3 Paths 路径
+ ***定义***
  假设 R 为定义在 A 上的关系，则 R 从 a 到 b，长度为 n 的路径可表示为以 a 为起始点，b 为终点的一个有限序列π:  $a, x_1, x_2, ..., x_{n-1}, b$;  其中, 满足: $a\ R\ x_1, x_1\ R\ x_2, ..., x_{n-1}\ R\ b$

### 9.4.4 一些重要定义
- ***环(cycle):***
> 一条起始点和终点为相同顶点的路径称为:环(cycle)

- $R^n$:
> $x\ R^n\ y$ 表示，在 R 中存在一条或多条从 x 到 y 的路径

- ***连通关系(connectivity relation)*** $R*$
> $R*$ 包含的序偶对 (a, b)，其中在 R 中至少存在一条从 a 到 b 的路径

### 9.4.5 一些重要定理
![[Pasted image 20231109111444.png|300]]
n≥2 时 ![[Pasted image 20231109111527.png#inl||300]]
### 9.4.6 The connectivity relation 连通关系
![[Pasted image 20231109111834.png]]

### 9.4.7 Composition of paths 路径的合成
>令:  
> $π_1: a, x_1, x_2, … , x_{n-1}, b$ 
> $π_2: b, y_1, y_2, … , y_{m-1}, c$
>则 $π_1$ 与 $π_2$ 合成后的路径为:  
>> $π_2\circ π_1:a,x_1,x_2,…,x_{n-1},b,y_1,y_2,…,y_{m-1},c$
***NOTE THE ORDER!!!(注意顺序)***

### 9.4.8 Transitive closure 传递闭包
>①. 关系 R 的传递闭包是包含 R 的最小的传递关系。
>②. R 是传递的，当且仅当，对于任何的 n，均有 Rn ⊆ R(结论来自9.1)
>③. 如果传递闭包存在一条从 x 到 y 的路径，那么一定有从 x 直接到 y 的弧线 (箭头)

+ ***传递闭包里有用的一些结论：***
  >①. If A ⊆ B and C ⊆ B, then (A∪C) ⊆ B.
  >②. If R ⊆ S and T ⊆ U then $(R\circ T) ⊆ (S\circ U)$.
  >推论: If R ⊆ S then $R^n⊆S^n$
  >③. 如果 R 是传递的，那么 $R^n$ 也是传递的  
  >> 只需证明: $(R^n)^2=(R^2)^n⊂R^n$
  >④. 如果对于 $j>k$, 有 $R^k=R^j$，那么对于某些 $n>=j$, 有 $R^{j+m}=R^n$  
  >除了 $R^j$ 之外，我们无法得到任何新的关系
  
+ ***定理***
  R 为定义在 A 上的一个关系，那么 R 的传递闭包就等于 R*
  ![[Pasted image 20231109113119.png]]
![[Pasted image 20231109113521.png]]

![[Pasted image 20231109113642.png]]

### 9.4.9 Warshall’s Algorithm 沃舍尔算法
[5 分钟快速搞懂沃舍尔算法！我三岁的弟弟都学会了！]( https://www.bilibili.com/video/BV1uM411v7kE?vd_source=dbd67c6676f59c6eb87be4a08bf448c3 )

![[Pasted image 20231109113814.png|400]]

![[Pasted image 20231109113829.png|400]]
***例子***
![[Pasted image 20231109113930.png|inl|200]] ![[Pasted image 20231109113947.png|inl|300]]

## 9.5 Equivalence Relations 等价关系
***参考：*** PPT+ [9.5 等价关系 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868626.html)
### 9.5.1 定义
定义在集合 A 上的关系 R 是**等价关系** iff(当且仅当)R 具有
> 1. 自反性(reflexive)
> 2. 对称性(symmetric)
> 3. 传递性 (transitive)

+ ***证明等价关系步骤***
  ![[Pasted image 20231109115128.png|500]]
### 9.5.2 Equivalence class and Partition 等价类与划分
>设 R 是定义在集合 A 上的等价关系。与 A 中的一个元素 a 有关系的所有元素的集合叫做 a 的等价类，记作: $[a]_R$.  
>如果 $b∈[a]_R$，那么 b 叫做这个等价类的代表元.  
>容易知道，一个等价类的任何元素都可以作为这个类的代表元.

+ ***定理***
  ![[Pasted image 20231109115336.png]]
  ![[Pasted image 20231109115449.png]]
  
## 9.6 Partial Orderings 偏序
***参考：*** PPT+[9.6偏序关系 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868629.html)
### 9.6.1 定义
- ***偏序(Partial order)***：定义在 A 上的集合 R 是偏序关系 iff(当且仅当)其具有以下性质:
> 1. 自反性(reflexive)
> 2. 反对称性(antisymmetric)
> 3. 传递性 (transtive)
- ***偏序集(Partially ordered set)/(或简写为 poset)***: 集合 A 及定义在其上的偏序关系 R 一起称为偏序集，记作$(A, R)$，A 中的元素也称为偏序集中的元素.

- 如果(A, ≤)是一个偏序集(poset)，那么对于其中的元素 a 和 b,  
    1. a≤b 或者 b≤a,那么称为可比的 **(Comparable)**  
    2. 即不存在 a≤b，也不存在 b≤a, 那么称为不可比的 **(Imcomparable)**
+ ***线序/全序 (Linear Order)***
  >如果偏序集 A 中每对元素 (every pair of elements)都是可比的，那么我们就称 A 是**线序集合 (linearly ordered set)或全序集合 (totally ordered set)**, 称偏序关系 R 为**线序或全序**关系 (linear order). 我们也称 A 为链(chain)
  
+ ***良序集 (Well-ordered set)***
  >设集合 $(S,≤)$ 为一全序集，≤是其全序关系，若对任意的 S 的非空子集，在其序下都**有最小元素**，则称≤为良序关系，(S,≤)为良序集。
  >>***良序归纳原理  The principle of well-ordered induction：*** 
  >> ![[Pasted image 20231109215030.png]]
  
+ ***拟序 (Quasiorder)***
  >定义在 A 上的关系 R 是拟序关系 iff 其具有以下关系
  >1. 反自反性 (irreflexive)
  >2. 传递性(transitive) 
> **NOTE:** 满足反对称性的拟序关系就称为偏序关系

+ ***乘积偏序 (Product Partial Order)***
  >如果 (A, ≤)和 (B, ≤)都是偏序集，那么他们的笛卡尔积也是个偏序集，其偏序关系≤被定义为:
  >> 如果在A中有a ≤ a'，在B中有b ≤ b'，那么(a, b) ≤ (a', b')

### 9.6.2 Lexicographic Order 词典顺序
对于一个乘积偏序，  
(a, b) ＜ (a', b')在a ＜ a'(或a == a'并且b ＜ b')时成立  
那么我们称其为词典顺序(Lexicographic Order)或字典序(“dictionary” order)

### 9.6.3 Hasse Diagram 哈斯图
- 哈斯图是有限集 A 上的**偏序图**，并且:
  > 删除了所有的自环 (self-cycles)
  > 消除了由传递性生成的边
  > 自底向上的制图
  
![[Pasted image 20231109215518.png#center|流程|300]]
>设 (S, ≤)是一个 poset. 若 x＜y 且不存在元素 z∈S，使得 x＜z＜y，则称 y∈S 覆盖 x∈S.而 y 覆盖 x 的有序对 (x, y)的集合也称为 (S, ≤)的**覆盖关系**. 可以看出，(S, ≤)的哈斯图的边与其覆盖关系是一一对应的.

+ ***Isomorphism 同构***
![[Pasted image 20231109215748.png#inl|定义|300]] ![[Pasted image 20231109215800.png#inl|示例|300]]
+ ***Principle of correspondence 对应原理***
  >两个有限同构偏序集必定具有相同的 Hasse 图.
### 9.6.4 maximal element and minimal element 极大元和极小元
+ ***极大元 (maximal element)和极小元 (minimal element)***
  >偏序集中的一个元素称为极大 (小)元，当它不小 (大)于这个偏序集中的任何其他元素, 利用哈斯图很容易判别它们就是图中的"顶" ("底")元素
  >极大 (小)元一定存在，且可能是不唯一的
  
+ ***最大元 (greatest element)和最小元 (least element)***
  >如果在偏序集中存在一个元素大(小)于**任何其他的元素**，那么称这样的元素为最大(小)元
  >最大 (小)元可能不存在，若存在则唯一
  
+ ***最小上界 (least upper bound)和最大上界 (greatest lower bound)***
  >如果存在一个元素 $u\ or\ l\in S$，使得对于偏序集 (S, ≤)的子集 A 中的所有元素 a，有 $a≼u (l≼a)$，那么称 $u(l)$ 为 A 的一个上 (下)界，如果 $u(l)$ 是所有上 (下)界中最小 (大)的，就叫最小上界 (LUB)(最大下界 (GLB))
  >
  >上界的最小元就叫最小上界；下界的最大元叫最大下界
  
**上述结合书上例子理解**
+ ***定理***
  ![[Pasted image 20231109221658.png|300]]
  
+ ***Topological Sorting（拓扑排序）***
  [拓扑排序的实现方法以及环路检测 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/34871092)

### 9.6.5 Lattice 格
+ ***定义***
  >如果一个偏序集的**每对元素**都有最小上界和最大上界，那么就称这个偏序集为**格**
  > ![[Pasted image 20231109222100.png#center|300]]
  
+ ***定理***
  >1. 两个格的笛卡尔乘积也是格
  >   ![[Pasted image 20231109222445.png|inl|250]] ![[Pasted image 20231109222520.png|inl|259]]
  >2. 格 L 的子集，如果还是格，就称为 L 的子格 (Sublattice)
  >3. 两个格同构，我们称它们为同构格 (哈斯图相同)  
  >4. 如果一个格既有最大元，也有最小元，我们就称其为有界格  
  >5. 满足分配律: ![[Pasted image 20231109222754.png|inl|200]]
  >   这样的格我们称为分配格 (Distributive lattice)，否则称为非分配格 (Nondistributive lattice)
  >6. 补元 (Complement): ![[Pasted image 20231109222833.png|inl|200]]
  >>  特别地: 0' = I, I' = 0  
  >>   Note: 补元若存在，可能不唯一  
  >>   如果一个格的所有元素均有补元在格中，我们就说它是补格(Complemented)，否则不是补格
+ ***定理***
  > ![[Pasted image 20231109223020.png|300]]

---
# （补） Semigroups and Groups 半群和群
## 10.1 本章基础知识及前提
***参考：*** PPT+教材+ [10.1代数结构 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868632.html)
+ ***二元运算 (Binary operation)***
  > 定义:对两个对象进行操作的运算称为二元运算
+ ***封闭律 (Closure)***
  > 设集合 S 有二元运算∗,若对 S 中的任意两个元素 $a_1$、$a_2$,都有: $a_1∗a_2∈S$,则称运算∗对集合 S 封闭

+ ***交换律 (Commutative)***
  > 交换律也称为阿贝尔律 (Abel 律), 设有代数 $(S,∗)$，若对任意 $a_1,a_2∈S$,都符合等式: $a_1∗a_2=a_2∗a_1$,那么称代数 $(S,∗)$ 运算符合交换律
  > 容易得到: 若 $(S,∗)$ 运算符合交换律，那么对于运算序列 $a_1∗a_2∗...∗a_n$，设 $θ(12...n)$ 为任意重排列，那么有:  
  >> $a_θ(1)∗a_θ(2)∗...∗a_θ(n)=a_1∗a_2∗...∗a_n$

+ ***结合律 (Associative)***
+ ***分配律(Distributive)***
+ ***德·摩根律(De Morgan‘s laws)***

+ ***单位元 (Identity)***
  >单位元也称幺元，如果对于代数结构 (S,∗)中任意元素 x∈S, 均有 $e∗x=x∗e=x$,我们就称 e 为单位元
  >**定理一：** 单位元唯一

+ ***逆元 (Inverse)***
  >如果运算符 $*$ 有单位元 e，如果存在 x $*$ y = y $*$ x = e, 那么我们称 x 是关于操作符 $*$ 的 y 的一个逆元，y 也是关于操作符 $*$ 的 x 的一个逆元 (**互为逆元**)
  >**定理二：** 如果操作符 $*$ 具有结合律，并且 x 的关于 $*$ 的一个逆元为 y，那么 y 是唯一的

*example 见书，便于理解*
+ ***集合上的二元运算***
  > 定义在集合上的二元运算是一个处处定义的函数 $f:A×A\rightarrow A$  
  > 且需满足:
  >> 1. $f(a, b)$ 的结果还在 A 中 (即具有封闭性)；
  >> 2. 每个序偶仅对应一个A中的元素

+ ***运算表(Tables)***
> A 是一个有限集(设有 n 个元素)，$*$ 是定义在集合 A 上的二元运算，那么我们可以得到 $n^{n^2}$ 个运算表

+ ***定义在集合上的二元运算的性质***
> 对于集合A中的元素a,b,c和二元运算*
>> 可交换律(Commutative)
>> 可结合律(Associative)
>> 幂等律(Idempotent)
>>> a∗a=a

## 10.2 Semigroup 半群
***参考：*** PPT+教材+ [10.2半群，同余关系，半群直积，商半群 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868642.html)
### 10.2.1 半群基础概念
+ ***半群 (Semigroup)***
  >非空集合 S 和定义在集合 S 上的具有结合律 (封闭性显然)的二元运算∗组成了一个半群 (S, \*);
  > 通常记为 (S, \*)或者 S
  > a\*b 称为 a 和 b 的积
  > **如果**∗具有**交换律**，那么 (S, \*)称为**交换半群** (阿贝尔半群)
  > >如: (Z, +); (P (S), ∪)； (Z, -)... 
  > >Note: P (S)指的是 S 的全集，如 S={1, 2, 3}, 那么 P (S) = {∅, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}
  >
  >***自由半群***
  > ![[Pasted image 20231110135808.png#center|自由半群例子]]
  > 操作符·是指连接运算，显然其具有结合律
  > 称 $(A^∗,·)$ 为由 A 生成的自由半群 (free semigroup generated by A)
  
+ ***定理 1***
  >如果 $a_1,\ a_2,\ …,\ a_n$ 是半群的任意元素（其中 $n ≥ 3$），那么在任意元素的乘积中插入有意义的括号形成的乘积是相等的。
  
+ ***Identity 单位元，幺元***
  > ![[Pasted image 20231110140408.png|250]]
  > >单位元若存在必唯一
  
+ ***Monoid——独异点，幺半群***
  >半群 $(S, *)$ 中存在单位元，则称为独异点
  
+ ***子半群 (Subsemigroup)***
  > ![[Pasted image 20231110141142.png#center|定义]]
+ ***子独异点、子幺半群 (Submonoid)***
  >T 是 S 的子集，并且 $(T, *)$ 同样满足独异点定义，同时 $e∈T$
> > 显然，半群(S,∗)本身也是S的子半群；独异点(S,∗)本身也是S的子独异点；  
> > T = {e} 一定是群(S,∗)的子独异点

+ ***Powers（幂） of A***
  >**定义：**![[Pasted image 20231110141621.png]]
### 10.2.2 Isomorphism 同构映射
+ ***定义***
  ![[Pasted image 20231110143246.png]]
>**Note:** 如果 $f$ 是从 $S\rightarrow T$ 的同构，即 $f$ 是从 $S\rightarrow T$ 的**一一对应**的函数，那么 $f^{−1}$ 必定存在，并且 $f^{−1}$ 是从 $S\rightarrow T$ 的一一对应的函数, 且一定是同构

+ ***构造同构/证明是否为同构的一般步骤:***
  >1. (构造或直接给出)构造一个函数 $f: S\rightarrow T$ , 使得 $f$ 的定义域 $Dom (f) = S$;
  >2. 证明 $f$ 是单射 (one-to-one)的，可用反证法
  >3. 证明 $f$ 是满射 (onto)的 $\rightarrow$ 故而是双射的
  >4. 证明 $f(a∗b)=f(a)∗′f(b)$
  
*例子步骤见书*

+ ***定理 2***
  > 如果 S 和 T 是独异点，且幺元分别为 $e，e′$ , 并且存在 $f:S\rightarrow T$ 是从 S 到 T 的同构映射，那么:
  > > $f(e)=e′$
>**Note:** 显然，如果(S,∗)有独异点，但(T,∗)没有独异点，那么必定不存在从 $S\rightarrow T$ 的同构<u>(常用于证明不存在同构)</u>
### 10.2.3 Homomorphism 同态
+ ***定义***
  > ![[Pasted image 20231110144429.png]]
  >**homomorphic image** (同态像)
  
*Note:同构和同态均满足：像点的乘积等于乘积的像点*

+ ***定理 3***
  > ![[Pasted image 20231110145624.png]]
  
+ ***定理 4***
  > ![[Pasted image 20231110145839.png]]
  
+ ***定理 5***
  > ![[Pasted image 20231110150017.png]]
  

## 10.3 Products and Quotients of Semigroups 乘积半群、商半群
### 10.3.1 半群的笛卡尔乘积
+ ***定理 1***
  ![[Pasted image 20231110150158.png]]
### 10.3.2 Congruence relation 同余关系
+ ***定义***
  >定义在半群 (S,∗)上的**等价关系**R，如果满足:‘’
  >> 任意 a R a' 并且 b R b' $\Rightarrow$ (a∗b) R (a′∗b′)
  >那么我们说 R 是**同余关系**
 > ![[Pasted image 20231110150657.png]]
 > 一个 $[a]$ 称为代表元

+ ***定理 2***
  > ![[Pasted image 20231110150904.png]]
  >S/R 称为**商半群**(quotient semigroup 或者 factor semigroup)
  
+ ***推论***
  > ![[Pasted image 20231110151045.png]]
  
+ ***定理 3***
  > ![[Pasted image 20231110151321.png]]
  
### 10.3.3 Fundamental Homomorphism Theorem 同态基本定理
![[Pasted image 20231110151445.png]]

## 10.4 Groups 群
[10.3群，群直积，商群 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868785.html)
因为太懒了，所以不想整理了（
## 10.5 Products and Quotients of Groups
[10.3群，群直积，商群 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11868785.html)
同上

---
# 10. Graphs 图
## 10.1 Graphs and Graph Models 图和一些图模型
**参考：** [10.1图和一些图模型 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12052258.html) +PPT+教材
+ ***定义 1***
  > ![[Pasted image 20231123113945.png]]
  > 端点 endpoint
  > **无限图 infinite graph：** 顶点（vertices）集为无限集或有无限条边（edges）的图
  > **有限图 finite graph：** 顶点集和边集为有限集
  
+ ***Types of Graphs 图的种类***
  >**Simple graph 简单图：** 无重边，无自环的无向图
  >**Multigraph 多重图：** 有重边的无向图
  >**Pseudograph 伪图/自环图：** 带有自环的无向图
  >**Simple directed graph 简单有向图：** 无重边，无自环的有向图
  >**Directed multigraph 有向多重图：** 有重边的有向图
  >**Mixed graph 复杂图：** 既有有向边，又有无向边的图
  >> ![[Pasted image 20231123115110.png|500]]
  
+ ***Graph models 图的模型***
  >了解即可

## 10.2 Graph Terminology and Special Types of graphs 图的术语和几种特殊的图
**参考：** [10.2图的一些术语(Graph Terminology) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12150972.html) +PPT+教材
### 10.2.1 Graph Terminology 图的基本术语
1. **相邻(Adjacency):**
> 无向图G中的一边e连接u，v，那么我们称u和v是相邻/连通(adjacent / neighbors / connected)的;其中也称u和v是边e的端点(endpoints)

2. **领域(Neighborhood)**
> 与顶点v相邻的所有点的集合N(v)称为v的领域(neighborhood of v);顶点集合A的领域指的是其内所有点领域的交集  ![inl](https://img2018.cnblogs.com/blog/1803261/202001/1803261-20200104235946402-2074052543.png)

3. **度(degree)**
> 顶点 v 的度，记作 deg (v)，等于入度 (in-degree)和出度 (out-degree)的和；度为 0 的点称为孤立点；度为 1 的点称为悬挂点 (pendant)

4. **握手定理(Handshaking Theorem)**
> ![200](Pasted%20image%2020231130095820.png)
> 无向图中，如果有度为奇数的点，那么这些点的个数必为偶数个

5. **有向图中的相邻**
> e映射到(u, v)，称之为u通过e邻接到v；u是e的初始点(initial vertex)，v是e的终点(terminal vertex )  
> 用 $\deg^−(v)$ 表示 v 的入度, $\deg^+(v)$ 表示 v 的出度
> **NOTE:** 顶点上的环对该点的入度和出度贡献都为 1
> **有向图握手定理 Directed Handshaking Theorem**
> ![400](Pasted%20image%2020231130100407.png)

6. **基本无向图 Underlying undirected graph**
>The undirected graph that results from ignoring directions of edges

### 10.2.2 Special Graph Structures 一些特殊的图结构
1. **完全图 Complete graphs $K_n$**
>n 阶完全图记为 $K_n$
> ![](Pasted%20image%2020231130101054.png)
2. **环图 Cycles** $C_n$ ![300](Pasted%20image%2020231130101158.png)

3. **车轮图 Wheels** $W_n$ ![300](Pasted%20image%2020231130101448.png) 含 n 个顶点的轮图的边数：$2\times (n - 1)$

4. **n 维体图 n-Cubes/hypercubes** $Q_n$ ![400](Pasted%20image%2020231130101540.png)

5. **二部图/二分图 Bipartite graphs**
>顶点能被分为两个集合，使得任意一个集合中的点没有边直接相连 ![100](Pasted%20image%2020231130101800.png)
>![](Pasted%20image%2020231130101959.png)
6. **完全二分图 Complete bipartite graphs** $K_{m, n}$
> ![300](Pasted%20image%2020231130102048.png)
> 用邻接矩阵表示的话，结果是一个上三角/下三角矩阵

### 10.2.3 Bipartite Graphs and Matchings 二分图和匹配
![](Pasted%20image%2020231130102648.png)

+ **HALL’S  MARRIAGE  THEOREM 霍尔婚姻定理**
>![](Pasted%20image%2020231130102755.png)

### 10.2.4 从旧图构造新图
+ **Subgraphs 子图**
>![](Pasted%20image%2020231130103247.png)
>proper subgraph 真子图
+ **Graph Unions 图的并集**
>![](Pasted%20image%2020231130103620.png)

## 10.3 Graph Representations & Isomorphism 图的表示和同构
**参考：** [10.3图的表示和同构(Graph Representations and Isomorphism) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12151018.html) +PPT+教材
### 10.3.1 Graph representations 图的表示
1. **Adjacency lists 邻接表表示法**![300](Pasted%20image%2020231130104552.png)
2. **Adjacency matrices 邻接矩阵表示法**
   > ![inl|200](Pasted%20image%2020231130104902.png) ![inl|250](Pasted%20image%2020231130105105.png)
   > **NOTE：** 
   > The adjacency matrix of a simple graph is symmetric.
   > $a_{ii}=0$
   >> **Adjacency matrix for a directed multigraph**
   >> $a_{ij}$ equals the number of edges that are associated to $(v_i, v_j)$.

3. **Incidence matrices 关联矩阵表示法**
   > ![inl|300](Pasted%20image%2020231130105741.png) ![inl|300](Pasted%20image%2020231130105755.png)
   
### 10.3.2 Graph Isomorphism 图的同构
+ **通俗定义:** 两个图是同构的，当且仅当(iff)除了它们的节点名称之外，它们是相同的。  
+ **正式定义:** $G_1=(V_1, E_1)$ 和 $G_2=(V_2, E_2)$ 之间存在顶点上的双射(bijection)函数 $f: V_1\to V_2$ ，使得任意 $a，b\in V_1$，有 $a$ 和 $b$ 在 $G_1$ 中相邻，那么 $f(a)$ 和 $f(b)$ 也在 $G_2$ 中相邻  

**图同构 $\Rightarrow$ 子图必定同构**

+ **Graph Invariants under Isomorphism 同构下的图不变量**
  （用来证明两个图不同构很方便）![|300](Pasted%20image%2020231130110608.png)
## 10.4 Connectivity 图的连通性
**参考：** [10.4图的连通性(Connectivity) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12151064.html) +PPT+教材
### 10.4.1 Paths 路径
如果存在一条路径，使得从 u 到 v，那么顶点 u 和 v 就是连通的
1. 如果能存在一条路径从u到u，那么这样的路径称为自环(circuit)
2. 路径可以视作穿过点(through the vertices)，也可视为遍历边(traverses the edges)
3. 如果这条路径穿过的边都是一次的 (无重复穿过同一条边)，那么我们称其为简单路径

### 10.4.2 Connectedness 图连通
+ **定义**
  An undirected graph is connected if there is a path between every pair of distinct vertices in the graph. 针对于无向图而言，如果任意两个顶点都能够连通，那么称这个图为连通图
+ **定理**
  无向连通图的每对顶点都存在简单路径 (simple path)
+ **Connected component 连通分支**
  ![|500](Pasted%20image%2020231130112418.png)
+ 割点(cut vertex)或割边(cut edge)能将连通图分为两部分
### 10.4.3 Vertex Connectivity 点连通
+ **Nonseparable graphs 不可分割图**
  无割点的图称为不可分割图
  e.g. 完全图 $K_n$
+ **Vertex cut 点割集**
  去掉点割集 V'后，使得连通图 G 变为 G-V'不再连通
+ **Vertex connectivity 点连通性**
  非完全图 G 的边连通性，指的是存在的点割集的点的最小数；记为 $\kappa(G)$; 通俗的说，就是最少去掉多少条点使得 G 不再是连通图
  - $0 ≤ 𝜅(G) ≤ n − 1$ if G has n vertices
  - $𝜅(K_n) = n − 1$
  - $𝜅(G) = 0$ if and only if G is disconnected or $G = K_1$
  - A graph is k-connected (or k-vertex-connected), if $𝜅(G) ≥ k$.
    - Note that if G is a k-connected graph, then G is a j-connected graph for all j with $0 ≤ j ≤ k$.

### 10.4.4 Edge Connectivity 边连通
+ **Edge cut 边割集**
  去掉边割集 E'后，使得连通图 G 变为 G-E'不再连通
+ **Edge connectivity 边连通性**
  非完全图 G 的边连通性，指的是存在的边割集的边的最小数；记为𝜆(G); 通俗的说，就是最少去掉多少条边使得 G 不再是连通图

### 10.4.5 Directed Connectedness 有向图的连通性
+ 有向图中，路径只能沿着箭头出发  
+ **强连通(strongly connected):** a 和 b 强连通，指存在路径从 a 连通到 b，也存在路径从 b 到 a  
+ **弱连通(weakly connected):** a 和 b 弱连通，指存在路径从 a 连通到 b 或存在路径从 b 到 a(强连通必定弱连通)
> **NOTE:** 连通性以及路径都是图同构中的同构不变量  
> **NOTE:** 用 tarjan 算法求有向图的强连通分量极其有效

### 10.4.6 Paths & Isomorphism 通路与同构
见书上例题即可

### 10.4.7 Counting Paths by Adjacency Matrices 通过邻接矩阵计算路径数
如果 A 是图 G 的邻接矩阵，那么 $(A^k)_{i,j}$ 表示 $v_i$ 到 $v_j$ 的路径为 k 的数目(1的数目)
> **NOTE: 注意这里求路径为 k 和之前沃舍尔算法求连通性的区别**

## 10.5 Euler Paths and Circuits 欧拉路径与欧拉回路
**参考：** PPT+教材+[10.5欧拉路径和欧拉回路(Euler Paths and Circuits) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12152343.html)
### 10.5.1 Eulerian graph 欧拉图
1. 图 G 的**欧拉回路(Euler circuit)** 指的是遍历 G 中每一条边的**简单回路(simple circuit)**, 这样的轨迹称为**欧拉环游(Euler tour)**
2. 图 G 的**欧拉通路/道路(Euler path)** 指的是遍历 G 中每一条边的**简单路径(simple path)**, 这样的轨迹称为**欧拉轨迹(Euler trail)**
3. 有欧拉回路的图称为欧拉图，无欧拉回路但是有欧拉通路的图称为半欧拉图

+ **定理 1：**
  >连通图 G 是欧拉图，当且仅当，G 是连通的，并且没有度为奇数 (odd)的顶点
  > ![[Pasted image 20231207101146.png]]
  
+ **定理 2：**
  >连通图 G 是存在从 a 到 b 的欧拉通路，当且仅当，G 是连通的，并且除 a 和 b (a≠b)的度为奇数 (odd)之外，没有度为奇数 (odd)的顶点
  > ![[Pasted image 20231207101344.png]]
  
+ **定理 3：**
  >有向连通图 G 是欧拉图，当且仅当：
  >>1. G 是连通的
  >>2. G 的每个顶点的入度＝出度

+ **定理 4：**
  >有向连通图 G 含有欧拉通路，当且仅当，G 是连通的，并且 G 中除两个顶点 (节点不相等)外，其余每个顶点的入度=出度，且此两点满足 $deg^−(u)−deg^+(v)=±1$
  
### 10.5.2 Hamilton Paths and Circuits 哈密顿通路与回路
+ **哈密顿图 Hamiltonian Graph**
  >1. 图 G 的**哈密顿回路 (Hamiltonian circuit)** 指的是遍历 G 中*每一个点*且只遍历一次的回路, 这样的轨迹称为**哈密顿环游 (Hamiltonian tour)**
  >2. 图 G 的**哈密顿路径 (Hamiltonian path)** 指的是遍历 G 中*每一个点*且只遍历一次的路径, 这样的轨迹称为**哈密顿轨迹 (Hamiltonian trail)**
  >3. 有哈密顿回路的图称为哈密顿图，无哈密顿回路但是有哈密顿路径的图称为半哈密顿图
  >
  >>遗憾的是，现在还没有快速判别一个图是否为哈密顿图的方法

+ **定理s：**
  > ![[Pasted image 20231207102509.png]]
  > Let the number of edges of G be m. Then G has a Hamiltonian circuit if 
  >> $m\geq\frac{(n^2-3n-6)}{2}$.
  >
  >有向完全图一定存在**哈密顿道路**
  >
  >一些哈密顿图判定的**充分条件**
  >>**定理 1：**
  >>> 简单图 G 的最小度数的顶点度数≥n/2
  >>**定理 2：**
  >>> 简单图G的任意一对相邻点的度数和≥n


+ **记忆轮 memory wheel**
  >具有 $2^n$ 的记忆轮能存储 n 位二进制的所有信息；且其和相应的哈密顿图是一一对应的
  > ![[Pasted image 20231207105041.png|500]]
  > 当然，相应转化后的欧拉图也具有一一对应关系，且更任意找
  > ![[Pasted image 20231207105122.png|500]]
  
## 10.6 Shortest Path Problem 最短路径问题
**参考：** PPT+ [10.6最短路径问题(Shortest Path Problem) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12151077.html) +教材

+ **分类：**
  >1. 单源最短路径问题
  >   Determining the shortest path from a vertex to an assigned vertex.
  >2. 多源最短路径问题
  >   Determining the shortest path of any two vertices in the graph.

+ **Dijkstra Algorithm：**
  > The algorithm is to find the shortest way from $v_1$ to $v_n$, at the same time, it gets the shortest way from  $v_1$ to each other vertices in the graph.
  > ![[Pasted image 20231207110430.png]]
  >**定理：**
  > ![[Pasted image 20231207110932.png]]![[Pasted image 20231207110944.png]]

+ **flody 算法**
  >多源最短路径
  >[多源最短路径--flody算法 - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/11549668.html)

## 10.7 Planar Graphs 平面图
**参考：** [10.7平面图(Planar Graphs) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12152524.html) +PPT+教材
### 10.7.1 平面图定义
+ 平面图的定义:能在平面上画出没有相交的边的图，称为平面图(planar)
![[Pasted image 20231207113251.png|400]]
+ 针对平面图而言的**面 (faces)**: ![[Pasted image 20231207113323.png|400]] A planar representation of a graph splits the plane into regions that we call  faces, including an unbounded region.
+ **边界：** 面的各边所组成的回路
+ **面的次数**：面边界回路的长度。记为**Deg (r)**

### 10.7.2 Euler Theorem 欧拉定理
+ **定理内容：**
  >令 G 是一个连通的平面简单图，那么有:  
  >> $V−E+F=2$ 或 $V−E+R=2$  $\Rightarrow R = E-V+2$
> 其实就算 G 具有重边或自环的平面图也成立
> ![[Pasted image 20231207114400.png|300]]

+ **定理 1**
  >具有 n 个顶点的**简单图**G, 最多有 $3n-6$ 条边
  >**PROOF:** ![[Pasted image 20231207114458.png|300]]

+ **推论：**
  >1. 如果 G 是连通平面简单图，那么 G 中至少有一个顶点的度不超过5
  >2. 如果 G 是连通平面简单图，并且 $v≥3$ 且没有长为 3 的环，那么 $e≤2v-4$
  > 
  > 通过以上分析: $K_5$ 和 $K_{3,3}$ 都不是平面图
  
### 10.7.3 The Kuratowski’s theorem 库拉托夫斯基定理
+ **elementary subdivision 初等细分：**
  >如果一个图是平面图，那么通过移除一条边 {u, v} 并添加一个新的顶点 w，以及边 {u, w} 和 {w, v}，所得到的任何图也将是平面图。
  
+ **homeomorphic 同胚：**
  >给定两个图 $G_1$ 和 $G_2$ ，如果它们同构或者通过一系列初等细分操作（反复插入或去掉 2 度结点）后, $G_1$ 和 $G_2$ 同构，则称 $G_1$ 和 $G_2$ 是 2 度结点内同构的，也称 $G_1$ 和 $G_2$ 是同胚的
  
+ **定理内容：**
  >证明一个图是平面图的**必要充分条件**是它不包含任何**同胚**于 $K_5$ 或 $K_{3,3}$ 的子图
  > ![[Pasted image 20231207115448.png|400]]
  
### 10.7.4 柏拉图体
![[Pasted image 20231207115616.png#center|对偶图|600]]
![[Pasted image 20231207115621.png#center|完全正则图|300]]
+ **柏拉图体：**
  > ![[Pasted image 20231207115835.png|400]]
  
+ **柏拉图体的平面化:**![[Pasted image 20231207115742.png|300]]
+ **推论：**
  > ![[Pasted image 20231207115918.png|300]]
  
## 10.8 Graph Coloring 图的着色
**参考：** [10.8图着色(Graph Coloring) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12152824.html) +PPT+教材

+ **chromatic number of G 图 G 的着色数**
>用 $n$ 种颜色给一副无重边和自环的图染色，要求任意一条边的端点颜色不同；满足情况下使用的最少颜色数称为**图 G 的着色数(chromatic number of G)**，记为 $\chi(G)$.

+ **Appel-Haken Four-Color Theorem 四色定理**
>任何**平面图**都能用 4 种颜色着色 (计算机证明)

+ **Five Color Theorem 五色定理**
> 任何平面图都能用 5 种颜色着色

+ **五色定理证明:**
> 引理:所有平面图都至少有一个顶点度数$≤5$  
> 证明略 (平面图不同胚于 $K_5$)

+ **Chromatic Polynomials 染色多项式**
>定义 $P_G(n)$ 表示对图 $G$ 用 $n$ 种 (或更少)颜色进行染色的方法数 ($n≥0$)，$P_G(n)$ 称为 $G$ 的染色多项式 (chromatic polynomial)
>*example:*
>> ![[Pasted image 20231214101612.png|300]]
>
>可见: 最小的使得染色多项式为正数的 $n$ 值就是 $\chi(G)$

+ **定理 1：**
  >如果图 $G$ 由互不连通的子图 $G_1,G_2\cdots G_m$ 构成，那么有:
  > $P_G(x)=P_{G_1}(x)P_{G_2}(x)\cdots P_{G_m}(x)$

+ **Subgraph 子图：**
  > $G_e$ ![[Pasted image 20231214102404.png|350]]
  
+ **拓展：**
  >**商图 (Quotient graph):** 无重边的图 G，按某种规则划分等价类之后得到商图
  >> ![[Pasted image 20231214102442.png|350]]
  
+ **定理 2**
  >通过一条边 e 来构建图 G 的子图:
> $G_e$：通过删除边 $e$ 得到的子图，通常会得到两个互不连通的图  
> $G^e$：通过**合并** $e$ 两边的**端点**得到的 G 的商图  
> 那么有:
> > $P_G(x)=P_{G_e}(x)-P_{G^e}(x)$
> 
> *example:*
> ![[Pasted image 20231214102853.png|inl|300]] ![[Pasted image 20231214102929.png|inl|300]]

+ **k 阶临界图:**
  >称图 $G$ 是 $k$ 阶临界图/被 $k$ 阶染色的(**chromatically k-critical**)，指的是 $\chi(G)=3$，且其任意真子图 $G'$ 的染色数 $\chi(G')$.

## 10.9 Transport networks 传输网
**参考：** [10.9传输网(Transport network) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12152965.html) +PPT

+ **一些名词：**![[Pasted image 20231214103828.png|L|300]]
![[Pasted image 20231214104546.png|400]]

+ **流量守恒 (Conservation of flow)**
  >除**源点 s (source)** 和**宿点 t (sink)** 之外，要求其他节点流入的流量和流出的流量相等
  
+ **Maximal flow 最大流**
  >对于网络流图 G，流量最大的可行流 $f$，称为最大流

+ **剩余容量、反向容量：**
  > ![[Pasted image 20231214105345.png|400]]
  
+ **基本算法描述：**
>[最大流算法 - 标号法_标号法求最大流-CSDN博客](https://blog.csdn.net/weixin_42419611/article/details/105413547)
>> 1. 最为朴素的算法，便是利用回溯法，对所有可能的路径情况分析并取所有可能情况的最大值
>> 2. 基于贪心算法的思考，在最开始先找一可行流(feasible flow)，在此基础上上不断的寻找增广路径，直到再无增广路径；但是问题在于贪心寻找时不一定最优，故引入反向边的概念，利用这一思路达到回溯的作用以确保正确性；这就是这个算法的精华部分，利用反向边，使程序有了一个后悔和改正的机会
>因此得到如下基本算法:
> 1. 找一可行流，对每条边的流量更新称剩余流量和反向流量
> 2. 寻找增广路径，注意流量既可以走正向流量，也可以走反向流量；将总的流量值更新
> 3. 重复过程 2 直至再无增广路径；此时得到的流量值即为最大流

+ **割集 Cut**
  >参考：[最大流最小割(Max-flow min-cut)定理 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/65793018)
  ![[Pasted image 20231214112851.png|L|450]]

+ **最大流最小割定理：**
  >最大流等于最小割

---
# 11. Trees 树
## 11.1 Trees 树
**参考：** PPT+教材+[11.1树(TREES) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12150454.html)
+ **树的特点：**
  >1. 树是一个无向无环图，任意两个节点间都有唯一的一个简单路径
  >2. 一系列树组成森林 (forest)
  >3. 树或森林的叶子节点指悬挂点 (pendant)或孤立顶点 (isolated vertex)
  >4. 内部顶点 (**internal node**)的度≥2
  
+ **Rooted Trees 有根树：**
  >1. 有根的树称为有根树
  >2. 有根树中的一些术语:
  >>父母；孩子；兄弟姐妹 (siblings)；祖先 (ancestors)；后代 (descendents)；叶子；内部节点 (internal node)；子树...
  >3. 根若有，可能不唯一

+ **N-ary Trees N 叉树：**
  >定义一颗有根树中任何一个节点都不超过 n 个孩子节点的树为 n 叉树；特别的，2-ary tree 也称为 binary tree.
  
+ **Ordered Rooted Tree 有序有根树**
  >孩子节点有序排列的有根树称为有序有根树(如左孩子，右孩子等等)

+ **一些树的定理**
  >1. n 个节点的树有 $e=n-1$ 条边
  >2. **满**m 叉树如果有 i 个内部节点，则有 $n=mi+1$ 个节点，有 $l=(m-1) i+1$ 个叶子节点 (提示:$l=n-i$)
  >3. 对于一颗满 m 叉树，**边数 $e$，内部节点数 $i$，节点总数 $n$ 和叶子节点数 $l$** 这 4 者知其一则另外 3 个都能得知，具体关系如下: ![[Pasted image 20231221102135.png|300]]
  >4. 高为 $h$ (只有根节点默认高度为 1)的 m 叉树最多有 $m^h$ 个叶子，最少有 $h$ 个节点![[Pasted image 20231221102950.png|500]]
  >5. A rooted m-ary tree with height h is called **balanced** if all leaves are at levels **h** or **h−1**
  
## 11.2 Applications of Trees 树的应用
**参考：** [11.2树的一些运用(Applications of Trees) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12150572.html) +PPT+教材
### 11.2.1 Binary Search Trees 二叉搜索树
二叉搜索树中，规定数据存储在节点中，且规定右孩子的 key 大于父节点，左孩子的 key 小于父节点(如果存在的话)
一般情况下，二叉搜索树查找，插入(必插到叶子节点上)和删除的时间复杂度为 $O(log_n)$，但当退化到线性链表时会使得复杂度提高到 $O(n)$，此时应当选择二叉平衡树来解决(AVL 树，红黑树等)

### 11.2.2 Decision Trees 决策树
根节点：决策树具有数据结构里面的二叉树、树的全部属性
非叶子节点 ：（决策点） 代表测试的条件，数据的属性的测试
叶子节点 ：分类后获得分类标记
分支： 测试的结果
![[Pasted image 20231228100740.png]]

### 11.2.3 Prefix codes 前缀码
+ **最优树(哈夫曼树)**
> ![[Pasted image 20231228100958.png|500]] ![[Pasted image 20231228101021.png|500]] ![[Pasted image 20231228101102.png|500]]

+ **二元前缀码**
>设 $\alpha_1,\alpha_2,\cdots,\alpha_n$ 是长为 $n$ 的符号串，$\alpha_1,\alpha_1\alpha_2,\cdots,\alpha_1\alpha_2\cdots\alpha_{n-1}$ 均为该符号串的前缀，它们的长度分别为 $1,2,\cdots,n-1$
> $A=\{\beta_1,\beta_2,\cdots,\beta_m\}$ 为一个符号串集合，对于任意的 $\beta_i,\beta_j\in A\ \ \ (i\neq j),\ \ \beta_i$ 与 $\beta_j$ 互不为前缀，则称 $A$ 为前缀码
> 若符号串中只出现 $0，1$ 两个符号，则称 $A$ 为二元前缀码
> 
> **定理**
> 任意一棵二叉树都可产生一个前缀码。
> 任何一个前缀码都对应一棵二叉树。

### 11.2.4 Game trees 博弈树
似乎不重要，看看书得了

## 11.3 Tree Traversal 树的遍历
**参考：**[11.3~11.4树的遍历(Tree Traversal) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12150727.html) +PPT+教材
### 11.3.1 Universal address systems 通用地址系统
![[Pasted image 20231228102758.png]]
### 11.3.2 Traversal algorithms 遍历算法
![[Pasted image 20240106154645.png]]

+ **Preorder traversal 前序遍历**
  >根左右 ![[Pasted image 20231228102926.png]]
  
+ **Inorder traversal 中序遍历**
  >左根右![[Pasted image 20231228103023.png]]
  
+ **Postorder traversal 后序遍历**
  >左右根 ![[Pasted image 20231228103109.png]]

+ **深度优先搜索-DFS (Depth-first search)**

+ **广度优先搜索-BFS(Breadth-First Search)**
### 11.3.3 Infix/prefix/postfix notation 中缀、前缀和后缀表达式
一个表达式的前缀(波兰式)，中缀和后缀表示即相应的二叉表达式树的前序，中序和后续遍历的结果

## 11.4 Spanning Trees 生成树
+ **定义**
>简单图 G 的生成树是 G 的子图，它是包含 G 每个顶点的树。

+ **定理**
>一个简单图是连通的，当且仅当其有生成树

## 11.5 Minimum Spanning Trees 最小生成树
**参考：**[11.5最小生成树(Minimum Spanning Trees) - 进击の辣条 - 博客园 (cnblogs.com)](https://www.cnblogs.com/SpicyArticle/p/12150738.html) +PPT+教材
+ **Weighted graph 加权图**
  >Definition: a **weighted graph** is a graph for which each edge is labeled with a numerical value called its **weight**（权值） .
  >
  >1. The weight of an edge $(v_i, v_j)$ is some times referred to as the *distance between vertice* $v_i$ and $v_j$
  >2. A vertex $u$ is a **nearest neighbor of vertex** $v$ if $u$ and $v$ are adjacent and no other vertex is joined to $v$ by an edge of lesser weight than $(u, v)$.
  >3. Note $v$ may have more than one nearest neighbor. 

+ **Minimum spanning tree**
>对加权图求使得权值和最小的生成树，即为最小生成树，基于以点为基准和以边为基准，有两种求最小生成树的方法: Prim 算法和 Kruskal 算法


