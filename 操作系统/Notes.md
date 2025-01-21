![](Attachments/Pasted%20image%2020250103202345.png)
# Chapter 1   Introduction
## OS 定义
![](Attachments/Pasted%20image%2020241110154710.png)
## I/O Structure
+ Programmed I/O
+ Interrupt-Driven I/O
  + Synchronous I/O 同步 I/O
  + Asynchronous I/O 异步 I/O
+ DMA
+ I/O 通道控制方式

## 1.4 OS 类型及特点
+ Multiprogramming 多道程序设计
 > To keep CPU and I/O devices busy at all times.
 > **job scheduling** – selects one job to run.

+ Time sharing systems（multitasking）分时系统/多任务
 > response time 通常小于 1 s
 > Each user has at least one program executing in memory ==> **process**
 > If several jobs ready to run at the same time  ==> **CPU scheduling**
 > **特点：**
 > **I/O routines** supplied by the system.
 > **Memory management** – the system must allocate the memory to several jobs.
 > **Virtual memory** – allows the execution of job not be completely in memory.
 > **Disk management** – file system must be provided, which resides on a collection of disks.
 > **CPU scheduling** – mechanisms for concurrent execution, job synchronization and communication, avoiding deadlock.
 > **Allocation of resources**.

## 1.5  Operating-System Operations
+ 软件中断——**exception** or **trap**
+ Dual-mode operation 双重模式操作
 > user mode + monitor mode![500](Attachments/Pasted%20image%2020241110160847.png)
 > 使用 timer 阻止程序陷入死循环

## 1.6  Process Management
+ A process is a program in execution
+ program counter 程序计数器用来明确下一个执行的指令
+ 多线程进程具有多个程序计数器

## 1.7  Memory Management
Memory management determines what is in memory
## 1.8  Storage Management
+ File-System management 文件系统管理
+ Mass-Storage Management
 > **disk**
+ Caching

---

# Chapter 2 OS Structures
## 2.1  Operating-System Services
一组操作系统服务提供对用户很有用的函数:
+ User interface (UI) 用户界面
 + Command-Line (CLI)
 + Batch interface
 + Graphics User Interface (GUI)
+ Program execution 程序执行
+ I/O operations I/O 操作
+ File-system manipulation 文件系统操作
+ Communications 通信
+ Error detection 错误检测
确保系统本身高效运行的函数：
+ Resource allocation 资源分配
+ Accounting 统计
+ Protection and security 保护和安全
## 2.2  User Operating-system Interface
+ Command  Interpreter (CLI)
+ Graphical User Interface (GUI)
## 2.3  System Calls 系统调用
+ 系统调用  (system  call) 提供了操作系统提供的有效服务界面
+ Mostly accessed by programs via a high-level **Application Program Interface (API)** rather than direct system call use. 一般开发人员根据应用程序接口API 设计程序
+ 三种应用程序员常用的 API:  
  + 适用于  **Windows**  系统的  Win 32 API 
  + 适用于  POSIX  系统的  **POSIX  API** (包括几乎所有 UNIX Linux MacOSX 版本) 
  + 用于设计运行于 Java 虚拟机程序的 **Java API**
the **run-time support system 运行时支持系统** provides a **system-call interface 系统调用接口** that serves as the link to system calls.
## 2.4  Types of System Calls
五大类：
+ Process control 进程控制
 > **Dump** memory if error
 > **Debugger** for determining bugs, single step execution
 > **Locks** for managing access to shared data between processes
+ File management 文件管理
+ Device management 设备管理
+ Information maintenance 信息维护
+ Communications 通信

## 2.5  System Programs
File management 文件管理
Status information 状态信息
File modification 文件修改
Programming-language support 程序语言支持
Program loading and execution 程序装入和执行
Communications 通信
## 2.6  OS Design and Implementation
Important principle:  separate Policy 策略 from Mechanism 机制
## 2.7  Operating-System Structure
+ 简单结构 MS-DOS
+ Layered Approach 分层法——系统模块化
 > 与其他方法相比其效率稍差
+ Microkernels 微内核
+ modules 模块
 > Many modern operating systems implement **loadable kernel modules 模块化的内核**![500](Attachments/Pasted%20image%2020241110165710.png)

---

# Chapter 3   Processes
## 3.1    Process Concept
+ **Process** -- a program in execution 执行中的程序
+ *Program* is **passive** entity stored on disk (**executable file**), *process* is **active**. 
  程序是被动实体，进程是活动实体
+ One program can be several processes
+ **进程状态**
 > new：进程正在被创建
 > running
 > waiting：进程等待某个事件的发生（如 I/O 完成或收到信号）
 > ready：等待分配处理器
 > terminated
 > **Only one process can be running on any processor 处理器 at any time**, many processes may be ***ready*** and ***waiting***. ![400](Attachments/Pasted%20image%2020241110170003.png)
+ **Process Control Block (PCB) 进程控制块**
 > 进程状态、进程编号、程序计数器、寄存器、内存界限、打开文件列表 ![100](Attachments/Pasted%20image%2020241110170124.png)

## 3 .2    Process Scheduling
一个处理器只能运行一个进程!!!
+ Scheduling Queues 调度队列
 > **job queue 作业队列**——进程进入系统就被加入
 > **ready queue 就绪队列**——ready 和 wait 的都保存在这个
 > **Device queues 设备列表**——等待特定 I/O 设备的进程
+ Queueing diagram 队列图
 > ![400](Attachments/Pasted%20image%2020241110171807.png)
+ 调度程序
 > **长期调度程序 (long-term scheduler)** 或**作业调度程序 (job scheduler)** 从缓冲池中选择进程，并装入内存以准备执行。（将进程放入 ready queue）
 > **短期调度程序 (short-term scheduler)** CPU 调度程序从准备执行的进程中选择进程，并为之分配 CPU。（选择进程执行）
+ I/O-bound process I/O 为主的进程：在执行 I/O 方面比执行计算要花费更多的时间
+ CPU-bound process
+ **中期调度程序 ( medium-term scheduler)** 核心思想是能将进程从内存 (或从 CPU 竞争) 中移出

![450](Attachments/Pasted%20image%2020250103223502.png) ![500](Attachments/Pasted%20image%2020250103225239.png)

+ **Context Switch 上下文切换**
 > ![400](Attachments/Pasted%20image%2020241110173159.png)
## 3 .3    Operations on Processes
+ **进程创建**
 > 唯一的pid
 > ![L|300](Attachments/Pasted%20image%2020241110173821.png)
 > 通过 `fork()` 创建新进程
 > 调用 `exec()` 用新程序来取代进程的内存空间
 > 父进程调用 `wait()` 把自己移出就绪队列来等待子进程的终止
 > 子进程的 pid 值为 0，而父进程的 pid 值大于 0。
 > **8、16**![450](Attachments/Pasted%20image%2020250103223914.png) ![450](Attachments/Pasted%20image%2020241110174701.png) ![450](Attachments/Pasted%20image%2020250103225510.png)
## 3 .4    Interprocess Communication
Independent 独立的
Cooperating 协作的
+ Two fundamental models
 > **Shared-memory 共享内存**
 > > 两种缓存：无限缓冲 ( unbounded-buffer) 和有限缓冲  (bounded-buffer) 
 > **Message passing 消息传递**
 > > 提供至少两种操作：发送 (消息) 和接收 (消息)。

+ **实现 send() /receive()**
 > **直接通信——naming**
 > > ![300](Attachments/Pasted%20image%2020241110175600.png) ![450](Attachments/Pasted%20image%2020241110175630.png)
 > 
 > **间接通信**
 > > 邮箱或端口
 > 
 > **Synchronization 同步**
 > **Buffering 缓冲**
 
# Chapter 4  Threads
线程：{//某些**进程**需要同时处理很多事，因此引入线程增加并发度
轻量级进程
**线程是基本的 CPU 执行单位**，程序执行流的最小单位
带来的变化：{
1. 线程变成了资源分配的基本单位
2. 各个线程间可以并发，加大了并发度
3. 同一进程内的线程切换可以不切换进程环境，系统开销小
}
线程的属性：{
1. 是处理机调度的单位
2. 多 CPU 中，不同线程可以占用不同的 CPU
3. 类似进程，线程有线程 ID，TCB
4. 有**就绪 ready，阻塞 waiting，运行 running**三种
5. 线程几乎不拥有系统资源
6. 同一个进程内的线程共享资源
7. 线程间通信不需要系统干预
8. 同一个进程中的线程切换不会引起进程切换
9. 不同进程中的线程切换需要进程切换
}
线程的实现方式：{
**用户级线程 User threads**；早期操作系统不支持线程，程序员使用线程库，线程的管理工作由应用程序调度，不需要 CPU 变态，操作系统不知道有线程的存在
优点：不需要 CPU 变态，开销小，效率高
缺点：如果其中的某个线程被阻塞，所有的线程都被阻塞，并发度不高，多个线程不能在多个 CPU 上运行


**内核级线程 Kernel threads**：由操作系统完成，需要CPU变态，操作系统看得到线程
优点：并发能力强，多核运行多线程，不会阻塞
缺点：需要内核介入，开销大


多线程模型：{
**一对一**：一个用户级线程对应一个内核级线程
并发性强，不会相互阻塞
但成本较高，开销大

**多对一**：多个用户级映射到一个内核级线程
退化为一个用户级线程，会被阻塞，但开销小

**多对多**：对上面两个模型的折中
//只有内核级线程才能被处理机看见并处理
}
![500](Attachments/Pasted%20image%2020250103224859.png)
线程的状态和转换：{//其实和进程的状态转换一模一样
TCB：{
    线程标识符：TID
    程序计数器PC：线程目前执行到哪里
    其他寄存器：线程运行的中间结果
    堆栈指针：保存函数调用信息，局部变量等等
    线程运行状态：就绪/阻塞/运行
    优先级：线程调度，资源分配
}
多个TCB组成一张线程表（thread table）
}

}


# Chapter 5 CPU Scheduling
## 5.1 Basic Concepts
+ **Nonpreemptive 非抢占的**：Once a process is in the running state, it will continue until it terminates or blocks itself for I/O.
+ **Preemptive 抢占的**：Currently running process may be interrupted and moved to the ready state by the operating system.
+ **dispacher 分派程序**：![500](Attachments/Pasted%20image%2020241110182256.png)
## 5.2 Scheduling Criteria 
+ **CPU utilization** – keep the CPU as busy as possible
 > In a real system, range from 40%  to 90%
+ **throughput (吞吐量)** – the number of processes that complete their execution per time unit.
+ **turnaround time (周转时间)** – amount of time to execute a particular process. 
 > 从进程提交到进程完成的时间段 **完成时间点-到达时间点**
+ **waiting time** – amount of time a process has been waiting in the ready queue.
 > **waiting time = turnaround time - burst time**
+ **response time** – 提交请求到产生第一响应的时间段

+ response rate = $\frac{turnaround\ time}{response\ time}$
+ Weighted turnaround time (WTT) = turnaround time / burst time

## 5 .3 Scheduling Algorithms
+ **First-Come, First-Served (FCFS) Scheduling**
 > 非抢占的
+ **Shortest-Job-First (SJF) Scheduling**
 > SJF is optimal – gives minimum average **waiting time** for a given set of processes
 > 非抢占
 > 抢占——抢占 SJF 调度有时称为最短剩余时间优先调度 ( shortest-remaining-time-first scheduling)
+ **Priority Scheduling**
 > 存在问题：无穷阻塞 (indefinite blocking) 或饥饿 (starvation)
 > 解决方法：aging 老化
+ **Round Robin (RR) Scheduling**
 > 时间片 (time quantum or time slice)
 > RR策略的平均等待时间通常较长
+ **Multilevel Queue Scheduling**
 > ![400](Attachments/Pasted%20image%2020241110211214.png)
+ **Multilevel Feedback Queue Scheduling**
 > 优先级反转
+ **Highest Response-Ratio Next Scheduling**
 > ![](Attachments/Pasted%20image%2020241111091955.png)

## 5 .4 Multiple-Processor Scheduling 
![](Attachments/Pasted%20image%2020241110211802.png)

+ **Load balancing**
 > ![](Attachments/Pasted%20image%2020241110212119.png)
## 5 .5 Thread scheduling 


# Chapter 6   Process Synchronization
## 6.2 The Critical-Section Problem 临界区问题
- 在该区中进程可能改变共同变量、更新一个表、写一个文件等
- 没有两个进程可以同时在临界区内执行
+ **通用结构**
 > 进入区 entry section
 > 退出区 exit section
 > 剩余区 remainder section
 > ![500](Attachments/Pasted%20image%2020241109155034.png)
-  临界区问题的解答必须满足如下三项要求
  - Mutual Exclusion 互斥
  - Progress 空闲让进
  - Bounded Waiting 有限等待

+ **两种方法处理临界区问题**
  + 抢占内核 (preemptive  kernel)
  + 非抢占内核 (nonpreemptive kernel)
## 6 .3 Peterson’s Solution
![](Attachments/Pasted%20image%2020241109160221.png)
![](Attachments/Pasted%20image%2020241109160231.png)
## 6 .4 Synchronization Hardware 硬件同步
+ **lock-锁**
 > ![](Attachments/Pasted%20image%2020241109161056.png)
 
+ atomic = uninterruptible

## 6 .5 Semaphores 信号量
+ `wait()` decrements the semaphore value
+ `signal()` increments semaphore value

### 用法
+ Binary semaphore 二进制信号量
 > 只能为 0 或 1——互斥锁
+ Counting semaphore 计数信号量
 > 值域不受限制
 > initialized to the number of resources available. 
 > wishes to use a resource, performs a wait () operation.
 > releases a resource, performs a signal () operation.

+ **busy waiting 忙等待**
 > ![500](Attachments/Pasted%20image%2020241109163929.png)
### Semaphore Implementation with no Busy waiting
![500](Attachments/Pasted%20image%2020241109164804.png)
+  `block ()`：place the process invoking this operation on the appropriate waiting queue.
+  `wakeup (P)`：remove one of processes in the waiting queue and place it in the ready queue.
![500](Attachments/Pasted%20image%2020241109164944.png)
### Deadlock and Starvation
+ **deadlock**：两个或多个进程无限地等待一个事件，而该事件只能由这些等待进程之一来产生
+ **Starvation**：indefinite blocking 无限期阻塞
  A process may never be removed from the semaphore queue in which it is suspended.

## 6 .6 Classic Problems of Synchronization
### The Bounded-Buffer Problem 有限缓冲问题

### The Readers-Writers Problem 读者-写者问题
+ **Readers**: only read the content of the shared object.
+ **Writers**: may update the content of the shared object.
竞争：读-写、写-写
共享：读-读

+ **解决方法**
 > **读优先**：writer 可能会 starvation
 > **写优先**：reader 可能会 starvation
 
+ **读优先**
 > 注意读和读不竞争 
 > 第一个读者需要和 writer 判断 wait ()
 > 最后一个读者需要 signal ()
 > mutex_r 用于保护 read_count 信号量
 > ![500](Attachments/Pasted%20image%2020241109171825.png)
### The Dining-Philosophers Problem

## 6 .7 Monitors
当一个进程发出信号（signal）通知另一个等待的进程可以继续执行时，控制权立即从当前进程转交给那个等待的进程，而不是等到当前进程完成它的整个临界区操作后再转交。
![](Attachments/Pasted%20image%2020241110222257.png)

# Chapter 7  Deadlocks
## 7.1 System Model
+ 用 $R_n$ 表示资源
+ 分为物理资源 physical resources + 逻辑资源 logical resources
  + 物理资源分为可抢占资源 preemptive resources + 不可抢占资源 non-preemptive resources

+ 每个资源可以有多个实例（instances）

## 7.2  Deadlock Characterization
+ **Mutual exclusion 互斥**：一次只有一个进程可以使用该资源。
+ **Hold and wait**：占有一部分资源的同时也在等待其他资源
+ **No preemption**
+ **Circular wait**
+ 当上述四个条件都发生时，死锁一定发生。充分必要条件

+ **Resource-Allocation Graph**
 > 两种边
 > **request edge** -- directed edge $P_i \rightarrow R_j$
 > **assignment edge** -- directed edge $R_j \rightarrow P_i$
 > ![500](Attachments/Pasted%20image%2020241104102113.png)
 > 没有环路，则没有 deadlock
 > 存在环路
 > > ![500](Attachments/Pasted%20image%2020241104102327.png)

## 7.3  Methods for Handling Deadlocks

## 7.4  Deadlock Prevention
针对四个条件
+ **Mutual Exclusion** – not required for sharable resources; must hold for nonsharable resources.
+ **Hold and Wait**
 > 1. 开始时分配所有需要的资源
 > > 缺点：资源利用率太低
 > 2. Allow a process to request resources only when it **has none** (release resources first).
 > > 缺点: Starvation possible.
+ **No Preemption**
 > 1. 类似 hold and wait 的第二种：Resources being held by requesting process are preempted. The process must **wait with no resources**.
 > 2. Waiting with holding resources, but resources may be preempted by other process requesting them.
+ **Circular Wait**
 > 对所有资源进行排序，要求每个进程按递增顺序来申请资源

## 7.5  Deadlock Avoidance
+ Simplest and most useful model requires：each process declare the **maximum number** of resources of each type that it may need.
+ 动态检查资源分配状态，以确保永远不会存在循环等待条件

+ **safe state**
 > System is in safe state only if there exists a **safe sequence** of all processes.
 > > ![](Attachments/Pasted%20image%2020241104104537.png)
 > > 

+ **Resource-Allocation Graph Algorithm 资源分配图算法**
 >![](Attachments/Pasted%20image%2020241104105423.png)
 > ![500](Attachments/Pasted%20image%2020241104105700.png)

+ **Banker's Algorithm**
 > **见 PPT 例题!!!** ![550](Attachments/Pasted%20image%2020241104110626.png)
 > > **Safety Algorithm**
 > > 用于寻找安全序列 ![500](Attachments/Pasted%20image%2020241104110912.png)
 > > **Resource-Request Algorithm**
 > > ![500](Attachments/Pasted%20image%2020241104111245.png)

## 7.6  Deadlock Detection
+ **等待图 wait-for graph**
 > 前提是每个资源类型只有**单个实例** ![500](Attachments/Pasted%20image%2020241108103024.png)
 > deadlock $\Leftrightarrow$ 等待图中存在一个环路

+ **每个资源类型有多个实例**
 > ![](Attachments/Pasted%20image%2020241108161909.png)
 > **Detection Algorithm**
 > > ![](Attachments/Pasted%20image%2020241108212237.png)

## 7.7  Recovery from Deadlock			
+ **杀死死锁进程**
 > 直接杀死
 > 单布回退
 > ![](Attachments/Pasted%20image%2020241108213603.png)
+ **资源可抢占**

---

# Chapter 8 Main Memory 
## 8 .1 Background
+ **Protection: Base and Limit Registers**
 > 先比较是否 ≥ 基地址，再比较是否 ＜ base+limit
 > 只有操作系统可以通过特权指令来加载 base 寄存器和 limit 寄存器
 
+ **Address Binding 地址绑定**
 > Compile time如果生成绝对 absolute地址，在加载/运行进程都在固定的地址
 > 现在生成可重定位地址
 > 在加载过程 **load time**中完成地址绑定
 > 在 **Execution time** 中完成地址绑定

+ **Logical vs. Physical Address Space**
 > **Logical address** – generated by the CPU;  also referred to as virtual address.
 > **Physical address** – address seen by the memory unit;  
 > 在 **Execution time** 中完成的地址绑定，逻辑地址和物理地址不同 ![600](Attachments/Pasted%20image%2020241118102102.png)

+ **Memory-Management Unit (MMU)**
 > 内存管理单元 ![400](Attachments/Pasted%20image%2020241118102505.png)
 
## 8 .2    Swapping 
A process can be temporarily ***swapped out of memory*** to a ***backing store***, and then ***brought back into memory*** for continued execution.

+ **Roll out, Roll in**
 > 基于优先级的调度算法中的交换

+ **ready queue**
 >  Consists of all processes whose memory images are on the ***backing store*** or ***in memory*** and are *ready to run*.

+ **Overlays 覆盖**
 > 当用户程序所需要的内存空间比分配给它使用的内存空间大时

## 8 .3 Contiguous Memory Allocation
User space is divided into Multiple partitions，每个区域可以加载一个进程运行

+ Placement Algorithm with **Partitions 分区**
 > Equal-size partitions
 > Unequal-size partitions
+ **Variable-partition scheme 可变分区**
 > Dynamic Partitioning (called MVT)
 > **Hole** – a block of available memory.
+ **Dynamic Storage-Allocation Problem**
 > First-fit：按空闲区首地址递增的次序组织空闲区表 (队列)
 > Best-fit：按空闲区大小递增的次序组成空闲区表/队列
 > Worst-fit：按空闲区大小递减的顺序组织空闲区表/队列
 > ![](Attachments/Pasted%20image%2020241118111215.png)

+ **Fragmentation 碎片**
 > **External Fragmentation** – total memory space exists to satisfy a request, but it is not contiguous.（first-fit 和 best-fit 都有该问题）
 > > 总的空间碎片满足需求，但由于分散，无法使用
 > **Internal Fragmentation** – allocated memory may be slightly *larger* than requested memory; 多出来的**差值**称为内部碎片，这部分内存在分区内，但不能使用
 > **外部碎片**的解决办法： **compaction 紧缩**——移动内存内容，以便所有空闲空间合并为一整块

## 8 .4 Paging
允许进程的物理地址空间可以是非连续的

+ **基本要求**
 > ***Physical memory*** is divided into fixed-sized blocks,  **frames**.
 > ***Logical memory*** is divided into blocks of same size, **pages**.
 > ***Backing store*** is divided into fixed-sized **blocks** that are of the same size as the memory frames.
 > 三个大小一样

+ **page table 页表**
 > 记录每一页实际占用的内存的信息
 > ***Page number (p)***：页号，所在物理内存的基地址
 > ***Page offset (d)***：页偏移，combined with base address to define the physical memory address that is sent to the memory unit
 
 ![450](Attachments/Pasted%20image%2020241122082433.png)
+ **地址转换**
 > ![450](Attachments/Pasted%20image%2020241122082704.png)
 > PTBR 指向页表的起始
 > ![](Attachments/Pasted%20image%2020250104160618.png)

+ **TLB** --Translation Look-aside Buffer
 > 转换表缓冲区
 > ![](Attachments/Pasted%20image%2020241122085904.png)
 > **Effective Access Time (EAT)**![350](Attachments/Pasted%20image%2020241122090546.png)
 > 访问 TLB，访问 Page Table，访问内存
 > 

+ **Memory Protection**
 >  Valid (v)-Invalid (i) Bit ![400](Attachments/Pasted%20image%2020241122091604.png)

+ **Shared Pages**
 > reentrant code（只读）
 > **Shared code must appear in same location in the logical address space of all processes.**

## 8 .5 Structure of the Page Table
+ **层次结构**
 > ![](Attachments/Pasted%20image%2020241122092642.png)
+ **Hashed Page Tables**
 > 通常超过 32 位地址空间
 > Each element consists of three fields:
 > >(1)  The virtual page number
 > >(2)  The value of the mapped page frame (frame number)
 > >(3)  A pointer to the next element in the linked list
 > ![450](Attachments/Pasted%20image%2020241128221529.png)
 > 

+ **Inverted Page Table 反向页表**
 > 对于每个真正的内存页或帧才有一个条目
 > 包含保存在真正内存位置的页的虚拟地址和拥有该页的进程的信息
 > 整个系统只有一个页表，对每个物理内存的页只有一条相应的条目 ![400](Attachments/Pasted%20image%2020241128222516.png)
 > ![500](Attachments/Pasted%20image%2020241128222617.png)

## 8 .6 Segmentation
![500](Attachments/Pasted%20image%2020241128223003.png)
Elements within a segment are identified by **their offset from the beginning of the segment**.

- **Segment table 段表**
 > **Segment base** – contains the starting physical address where the segment resides in memory.
 > **Segment limit** – specifies the length of the segment. ![450](Attachments/Pasted%20image%2020241128223202.png)
 
## Segmentation With Paging 段页式
![500](Attachments/Pasted%20image%2020241128223921.png)
![500](Attachments/Pasted%20image%2020241128224010.png)
![500](Attachments/Pasted%20image%2020241128224026.png)

---

# Chapter 9 Virtual Memory
## 9 .1 Background
- 虚拟内存 (virtual memory  ) 将用户逻辑内存与物理内存分开。
- **Virtual-address Space**
 > ![](Attachments/Pasted%20image%2020241129081430.png)
 
## 9 .2 Demand Paging
只有程序需要执行时才载入 page
![450](Attachments/Pasted%20image%2020241129081634.png)

![](Attachments/Pasted%20image%2020241129081807.png)

- **Valid-Invalid Bit**
 > v -> valid & in-memory, 
 > i -> invalid or valid but not-in-memory -> page fault 缺页

- Steps in Handling a Page Fault
 > ![400](Attachments/Pasted%20image%2020241129082059.png)

+ **Performance of Demand Paging**
 > ![450](Attachments/Pasted%20image%2020241129082315.png) ![450](Attachments/Pasted%20image%2020250104165337.png)
## 9 .3 Copy-on-write
![450](Attachments/Pasted%20image%2020241129082422.png)


## 9 .4 Page Replacement
![500](Attachments/Pasted%20image%2020241129082736.png) ![500](Attachments/Pasted%20image%2020241129083426.png)
- **reference strings**
 > 用来评估 Frame-allocation algorithm 和 Page-replacement algorithm
### FIFO (First-In-First-Out) Algorithm
![500](Attachments/Pasted%20image%2020241129084130.png)

- **Belady 异常 (Belady's anomaly)** 
 > 页错误率随着分配的帧数的增加而增加

### Optimal Algorithm
Replace the page that will not be used for the **longest period** of time
![400](Attachments/Pasted%20image%2020241129084536.png)
- 理论最优，效率最高
- 作为标杆—衡量算法性能
### Least Recently Used (LRU) Algorithm
replaces the page that **has not been used** for the **longest** period of time. 

### LRU Approximation Algorithms
- **Additional-reference-bits algorithm**
 > 
- **Enhanced Second-Chance Algorithm** 
 > 

## 9 .5 Allocation of Frames 
Each process needs **minimum number** of pages.

### Fixed Allocation
- **Equal allocation 平均分配**

- **Proportional allocation 比例分配**
 > ![](Attachments/Pasted%20image%2020241202100516.png)
 
### Priority Allocation
- **全局置换 (global replacement)** 
 > 大多数操作系统采用
- **局部置换 (local replacement)**

## 9 .6 Thrashing 抖动
频繁的页调度行为 This high paging activity is called **thrashing**.
A **process is thrashing** if it is spending most time paging than executing.
- 产生原因：$\sum$ locality size > total memory size
- **Locality model**
 > a set of pages that are actively used together.
 > Process migrates from one locality to another.
- **working-set model**
 >  ![500](Attachments/Pasted%20image%2020241202102049.png) ![450](Attachments/Pasted%20image%2020250104172552.png) ![450](Attachments/Pasted%20image%2020250104173030.png)
 >  峰值：从一个 locality 迁移到另外一个 locality
- **Page-Fault Frequency Scheme**
 > 监控缺页率，调整 ![4503](Attachments/Pasted%20image%2020250104172811.png)
## 9 .7 Memory-mapped file 
## 9 .8 Allocating Kernel Memory
- **Buddy System (伙伴系统）**
 > 内存按 2 的幂的大小来进行分配，即 4 KB 、8 KB、 16 KB 等. 如果请求大小不为 2的幂，那么需要调整到下一个更大的 2 的幂
 > ![500](Attachments/Pasted%20image%2020250104173428.png)
- **slab 分配**
 > ![450](Attachments/Pasted%20image%2020250104173816.png)
 > 两个**优点：**
 > > ![450](Attachments/Pasted%20image%2020250104173912.png)

---

# Chapter 10   File-System Interface
## 10 .1 File Concept
- 文件是逻辑外存的最小分配单位
- 连续的逻辑地址空间
- **File Attributes**
 > Name
 > Identifier
 > Type
 > Location
 > Size
 > Protection
 > Time, date, and user identification![450](Attachments/Pasted%20image%2020241206083204.png)
- **File Operations**
 > ![500](Attachments/Pasted%20image%2020241206083441.png)
 > Create, Write, Read, Reposition, Delete, Truncate
- Open-file table 打开文件表
- **Open ($F_i$)**
 > ![450](Attachments/Pasted%20image%2020241206084846.png)
- 每个打开的文件有信息：文件指针，文件打开计数器，文件磁盘位置，访问权限
- **共享锁 (shared lock)**：类似于读者锁，可供多个进程并发获取
- **专用锁 (exclusive lock )**：类似于写者锁，只有一个进程可获取
- File types

- File Structure

- Internal file structure
 > ![450](Attachments/Pasted%20image%2020241206090235.png)


## 10 .2 Access Methods
- **Sequential Access 顺序访问**
![](Attachments/Pasted%20image%2020241206091051.png)
- **Direct Access 直接访问**
![](Attachments/Pasted%20image%2020241206091100.png)

## 10 .3 Directory Structure
- **Operations Performed on a Directory**
 > Search for a file
 > Create a file
 > Delete a file
 > List a directory
 > Rename a file
 > Traverse the file system

- **Single-Level Directory**
 > ![400](Attachments/Pasted%20image%2020241209101227.png)

- **Two-Level Directory**
 > ![550](Attachments/Pasted%20image%2020241209101524.png)

- **Tree-Structured Directories**
 > ![450](Attachments/Pasted%20image%2020241209101951.png)

- **Acyclic-Graph Directories**
 > ![450](Attachments/Pasted%20image%2020241209102443.png)
 > a shared file/directory is not the same as two copies of the file/directory.

- **General Graph Directory**
 > ![500](Attachments/Pasted%20image%2020241209102713.png)
## 10 .4 File System Mounting

## 10 .5 File Sharing

## 10 .6 Protection

---

# Chapter 11 File-System Implementation
## 11.1 File System Structure
![500](Attachments/Pasted%20image%2020241213081919.png)
![450](Attachments/Pasted%20image%2020250104193652.png)
## 11 .2 File System Implementation 
- **On-disk File System Structures**
 > ![500](Attachments/Pasted%20image%2020241213082548.png)
- **In-Memory File System Structures**
 > ![500](Attachments/Pasted%20image%2020241213083022.png)
- **Partitions and Mounting**
 > ![](Attachments/Pasted%20image%2020241213083232.png)
 > 根分区 root partition，在引导时装入内存
- **Virtual File Systems**
 > 

##  11 .3 Directory Implementation
![](Attachments/Pasted%20image%2020241213084318.png)

## 11.4 Allocation Methods
- **Contiguous allocation 连续分配**
 > ![550](Attachments/Pasted%20image%2020241213085117.png) ![550](Attachments/Pasted%20image%2020241213085912.png)
 > **problems：**
 > > Difficult to find space for a new file.
 > > External fragmentation
 > > Determine how much space is needed for a file
- **Linked allocation**
 > 解决了连续分配的所有问题
 > 每个文件是磁盘块的链表:磁盘块分布在磁盘的任何地方。
 > ![400](Attachments/Pasted%20image%2020250104194846.png)
- **Indexed allocation**
 > ![450](Attachments/Pasted%20image%2020250104195229.png)![](Attachments/Pasted%20image%2020250104195427.png)

## 11 .5 Free-Space Management 
- Bit map / Bit vector 位图/位向量
  1 表示空闲，0 表示占用

- Linked list 链表
  ![400](Attachments/Pasted%20image%2020250104200931.png)
- Grouping 组
  将 n 个空闲块的地址存在第一个空闲块中![](Attachments/Pasted%20image%2020250104201019.png)
- Counting 计数
  ![](Attachments/Pasted%20image%2020250104201035.png)


---

# Chapter 12 Mass-Storage Structure
## 12 .1 Overview of Mass Storage Structure
![](Attachments/Pasted%20image%2020241216095720.png)

- **Hard Disk Performance**
 > Access Latency = Average access time = average seek time + average latency
 > Average I/O time = average access time + (amount to transfer / transfer rate) + controller overhead
## 12 .2 Disk Structure
![](Attachments/Pasted%20image%2020241216101341.png)

![450](Attachments/Pasted%20image%2020241216101834.png)

## 12 .3 Disk Attachment
- Host-attached storage 主机附属存储
- Network-Attached Storage (NAS) 网络附属存储
- Storage Area Network (SAN) 存储区域网络

## 12 .4 Disk Scheduling
- **FCFS--First Come First Served**
- **SSTF--Shortest Seek Time First**
- **SCAN Scheduling**：磁臂从磁盘的一端向另一端移动，同时当磁头移过每个柱面时，处理位于该柱面上的服务请求。当到达另一端时，磁头改变移动方向，处理继续。
- **C-SCAN Scheduling— Circular SCAN**：只在一个方向提供服务，返程不提供服务
- **LOOK and C-LOOK Scheduling**：通常，磁头只移动到一个方向上最远的请求为止。接着，它马上回头，而不是继续到磁盘的尽头。

## 12 .5 Disk Management
- Disk formatting
- Boot block

---

# Chapter 13 I/O Systems
## 13 .2 I/O Hardware
![500](Attachments/Pasted%20image%2020241223100536.png)
- **I/O port** ![500](Attachments/Pasted%20image%2020241223101243.png)
- **Polling**
 > ![450](Attachments/Pasted%20image%2020241223102102.png)
- **Interrupts**
 > ![450](Attachments/Pasted%20image%2020241223102902.png)
- **Direct Memory Access**
 > ![450](Attachments/Pasted%20image%2020241223104536.png)

## 13 .3 Application I/O Interface


