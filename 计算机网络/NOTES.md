# ch 1 Introduction
**2013 期中**
1. 
+ Internet 和 internet 的区别和联系
  + internet 小写代表互联网，Internet 大写代表因特网。
    + 以小写字母 i 开始的 internet（互联网或互连网）是一个通用名词，它泛指多个计算机网络互连而组成的网络，在这些网络之间的通信协议（即通信规则）可以是任意的。
    + 以大写字母 I 开始的 Internet（因特网）则是一个专用名词，它指当前世界上最大的、开放的、由众多网络相互连接而成的特定计算机网络，它采用 TCP/IP 协议族作为通信的规则。
  + 互联网、因特网的关系是：互联网包含因特网 
2. 
+ 协议 (protocol)：一台机器上的第 n 层与另一台机器上的第 n 层进行对话，该对话中使用的规则和约定统称为第 n 层协议。
+ Services：服务，每一层通过接口（interface）向上一层提供的功能
+ 服务是通过协议实现的![](Attachments/Pasted%20image%2020240423215314.png)
+ 面向连接是可靠的传输，无连接不可靠；面向连接只有建立连接时需要完整的地址，无连接每个 packet 都需要完整地址；IP 语音，垃圾邮件![](Attachments/Pasted%20image%2020240423220118.png)
## Category of Computer Networks
+ **根据范围分类**
  PAN 个域网
  LAN 局域网：Local area network
  MAN 城域网
  WAN 广域网：![450](Attachments/Pasted%20image%2020240621192324.png)
+ **根据传输技术分类**
  Broadcast networks 广播网络（WiFi）
  Point-to-point networks 点到点网络

+ **根据位置分类**
  Access Networks 接入网：接入用户的网
  Core Networks 核心网
## Network architecture and protocols
+ 网络体系结构（分层）的**动机**
  降低上下层之间的耦合度
+ **术语**![](Attachments/Pasted%20image%2020240423204459.png)**协议里的元素：**![](Attachments/Pasted%20image%2020240423204610.png)
  Syntax：语法，协议消息的格式
  Semantics：语义，消息的字段区某个值的含义
  Services：服务，每一层通过接口（interface）向**上一层**提供的功能

+ **PDU**：协议数据单元![](Attachments/Pasted%20image%2020240621195912.png)
  物理层没有 PDU 的概念

+  **Connection-oriented 面向连接服务 vs. Connectionless 无连接服务**
  ![300](Attachments/Pasted%20image%2020240423205125.png)
![](Attachments/Pasted%20image%2020240423205305.png)
+ **Service Primitives (服务原语): Message Style**![450](Attachments/Pasted%20image%2020240423205449.png)
  **服务是通过协议实现的** ![400](Attachments/Pasted%20image%2020240423205633.png)
## Reference Models
OSI 实现起来很困难，寻址、流控与差错控制在每一层里都重复出现，必然降低系统效率
TCP/IP 在服务、接口与协议的区别上不清楚
TCP/IP的主机－网络层本身并不是实际的一层，它定义了网络层与数据链路层的接口。
### The OSI Reference Model 7 层
上四层是端到端的 ![400](Attachments/Pasted%20image%2020240423205824.png)
+ **Physical layer 物理层**
  + 主要任务是在物理媒体上实现比特流的透明传输。
  + 物理层传输单位是比特。
  + **透明传输**: 指不管所传数据是什么样的比特组合, 都应当能够在链路上传送。
  + 功能：
    + 定义接口特性
    + 定义传输模式
      + 单工：接受方和发送方已经确定，不能更改
      + 半双工：介于两者之间。同一时间段内，只能有一个接受方或发送方，但是身份可以调换。
      + 双工：可以同时当做接收方和发送方，类似于打电话
    + 定义传输速率
    + 比特同步
    + 比特编码
+ **Data link layer 数据链路层**
  + 主要任务是把网络层传下来的**数据报**组装成帧
  + 数据链路层/链路层的传输单位是**帧**frame
  + 功能:
    + 成帧（定义帧的开始和结束）
    + **差错**控制
    + **流量**控制
    + 访问（接入）控制（控制对信道的访问）
+ **Network layer 网络层**
  + 主要任务是把**分组**从源端传到目的端，为分组交换网上的不同主机提供通信服务
  + 网络层传输单位是数据报。把数据报进行切割后，就是分组。
  + 功能：
    + **转发数据**
    + **路由**选择（选择最合适的路由来传递数据）
    + 流量控制
    + 差错控制
    + **拥塞控制**（若所有结点都来不及接受分组，而要丢弃大量分组的话，网络就处于拥塞状态。因此要采取一定撒施，缓解这种拥塞。）
+ **Transport Layer 传输层**
  + 负责主机中两个进程的通信，即**端到端**的通信。
  + 传输单位是报文段或用户数据报
  + 功能：
    - 可靠传输，不可靠传输（一般用于小文件）
    - 差错控制（用来处理传输过程中出现的错误）
    - 流量控制（当两台主机处理数据的速度不匹配时，会对速度过快的主机进行控制）
    - 复用分用
      - 复用: 多个应用层进程可同时使用下面运输层的服务。
      - 分用: 运输层把收到的信息分别交付给上面应用层中相应的进程。
+ **Session Layer 会话层**
  + 允许不同机器上的用户建立会话
  + 对话控制 (dialogcontol)（记录该由谁来传递数据）
  + 令牌管理 (token management)（禁止双方同时执行同一个关键操作）
  + 同步功能 (swchmnimtion)（在一个长传输过程中设置一些断点，以便在系统崩潰之后还能恢复到崩潰前的状态继续运行)
+ **Presentation Layer 表示层**
  + 用于处理在两个通信系统中交换信息的表示方式（**语法**和**语义**）
+ **Application Layer 应用层**
  + 包含了用户通常需要的各种各样的协议。

### The TCP/IP Reference Model 4 层
![](Attachments/Pasted%20image%2020240423211324.png)
+ **Link Layer 链路层**
  + 描述了链路必须完成什么功能才能满足无连接的互联网络层的需求，比如串行线和经典以太网链路。
  + 这不是真正意义上的一个层，而是主机与传输线路之间的一个接口
+ **The Internet Layer 网际层/网络层**
  + 无连接、IP
  + 该层的任务是允许主机将数据包注入到任何网络，并且让这些数据包独立地到达接收方（接收方可能在不同的网络上）
+ **The Transport Layer 传输层**
  + **传输控制协议 TCP (Transmission Control Protocol)**
    + **可靠的、面向连接**的协议
    + 在目标机器，接收 TCP 进程把收到的报文重新装配到输出流中。
    + TCP 还负责处理**流量控制**，以便确保一个快速的发送方不会因发送太多的报文而淹没掉一个处理能力跟不上的慢速接收方。
    + 拥塞控制 congestion control
  + **用户数据报协议 UDP (User Datagram Protocol)**
    + 不可靠的、无连接协议
+ **Application Layer应用层**
![](Attachments/Pasted%20image%2020240621205759.png)![](Attachments/Pasted%20image%2020240621205929.png)
# ch 2 Physical Layer 物理层
T 1: data rate=1.544 Mbps
## Fundamental Concepts
+ **Bandwidth（带宽）**：The Width of the frequency range transmitted without being strongly attenuated (Hz)
+ **Bit Rate (bps、数据率):** The number of bits transmitted per second
+ **Baud Rate (Baud、信号速率):** The number of times per second the signal can change the electrical state
  >Baud Rate=$1/T$
  >T is the period of a signal unit
  >每毫秒采样 1 次，即每秒采样 1000 次，即 Baud rate=1000 Baud
+ $Bit\ Rate = Baud\ Rate\times(log_2V)$
  V 是信号的有效状态数（电平级数）
  V is the number of signal levels used to represent data
+ 关系:若一个码元携带 n bit 的信息量，则 M Baud 的码元传输速率所对应的信息传输速率为$M×n$ bit/s
+ 信道容量
+ 吞吐量
+ **时延带宽积**
  时延带宽积=传播时延（秒） $\times$ 带宽（比特/秒）
  时延带宽积又称为以比特为单位的链路长度。即“某段链路现在有多少比特”。
![inl|300](Attachments/Pasted%20image%2020240423221348.png) ![|inl|300](Attachments/Pasted%20image%2020240423221407.png)
+ Simplex 单工, Half-duplex 半双工, Full-duplex 全双工
+ Serial transmission 串行传输 vs. Parallel transmission 并行传输

## 带宽与最大数据率的关系
+ **Nyquist Bit Rate 奈奎斯特公式（无噪声信道）**
  尼奎斯特证明，如果一个任意信号通过了一个带宽为 B 的低通滤波器，那么只要进行每秒 2B 次（确切）采样，就可以完全重构出被过滤的信号。
  $bit\ rate = 2 \times bandwidth \times\log_2 V$
  V is the number of signal levels used to represent data 信号的电平级数![](Attachments/Pasted%20image%2020240423223613.png)
+ **Noisy Channel: Shannon Capacity 香农公式**![](Attachments/Pasted%20image%2020240423223706.png)![](Attachments/Pasted%20image%2020240423223456.png)![](Attachments/Pasted%20image%2020240423223620.png)
## 传输介质
![](Attachments/Pasted%20image%2020240423225825.png)
+ 传输介质带宽![](Attachments/Pasted%20image%2020240423225310.png)
## Digital modulation and encoding
+ QPSK: Quadrature Phase Shift Keying——正交相移键控
+ QAM: Quadrature Amplitude Modulation——正交幅度调制
+ Constellation Diagram星云图
![](Attachments/Pasted%20image%2020240423225759.png)
例：![](Attachments/Pasted%20image%2020240423225949.png)
两个公式都要算一下![](Attachments/Pasted%20image%2020240423230250.png)
+ **Manchester (IEEE 802.3 version)**![](Attachments/Pasted%20image%2020240423230511.png)
+ 模拟数据->数字信号：采样、量化、编码—— PCM
## Multiplexing复用
+ **TDM 时分复用**![](Attachments/Pasted%20image%2020240423231603.png)
  + 每个输入流的比特从一个固定的时间槽 (time slot) 取出并输出到混合流。该混合流以各个流速率的总和速度发送。
  + 这种工作方式要求输入流在时间上必须同步。
  + 类似于频率保护带，为了适应时钟的微小变化可能要增加保护时间 (guard time) 间隔。
  + 统计时分复用 (STDM, Statistical Time Division Multiplexing)：**按需分配**
  + 这里的前缀"统计"表明组成多路复用流的各个流没有固定的调度模式，而是根据其需求产生。
+ **FDM 频分复用**![350](Attachments/Pasted%20image%2020240423231004.png)
  **保护带**：比语音通信所需多出来的那部分频带称为保护带 (**guard band**)，它使信道之间完全隔离。
+ **WDM 波分复用**
+ **CDM码分复用**![](Attachments/Pasted%20image%2020240423231921.png)
## Physical network: PSTN
+ **ADSL: Asymmetric DSL (非对称数字用户线)**![](Attachments/Pasted%20image%2020240424134130.png)
  **本地回路上的 1.1 MHz 频谱被分成 256 条独立的信道，每条信道宽 4312.5 Hz**。
  信道 **0** 用于简单老式电话服务 (POTS, Plain Old TelephoneService)。
  信道 **1~5** 空闲，目的是防止语音信号与数据信号相互干扰。
  在剩下的 **250** 条信道中，一条用于上行流控制，另一条用于下行流控制，其他的**248**信道全部用于用户数据。
  在每条信道内使用了 **QAM** 调制方案，**速率约为 4000 符号/秒**

## 电路交换&分组交换
![](Attachments/Pasted%20image%2020240424135529.png)


# ch 3数据链路层
+ 解决点到点之间的问题
  点到点：two ***adjacent*** machines
  端到端：e.g.从我的手机发送数据到你的手机
## Framing(成帧)
+ Character count (字符计数法)
+ Flag byte with byte stuffing (字节填充法)
+ Starting and ending flags, with bit stuffing(比特填充法)
+ Physical layer coding violations (物理层编码违例法)
![](Attachments/Pasted%20image%2020240424143616.png)

## Error Control(差错控制)
### Error detection
Parity check: able to detect single bit errors
单个奇偶校验位性能
可检出奇数个位翻转错误，其它情况漏检率50%
Cyclic Redundancy Check (CRC): detecting some burst errors
![](Attachments/Pasted%20image%2020240424145722.png)
Checksum, to be studied in Network layer

+ **Error Correcting Code纠错码: Hamming Distance汉明/海明距离**
To **detect** t-bit errors, need a distance **t+1** code
To **correct** t –bit errors, need a distance **2t+1** code
![](Attachments/Pasted%20image%2020240424145439.png)

## Flow control(流量控制)
1. 协议 1——乌托邦
2. 协议 2——简单停等
3. 协议 3——PAR、 Positive ACK with Retransmission
   Sequence number in frame、 Time out and retransmission
4. 协议 4——A One-Bit Sliding Window Protocol  
5. 协议 5—— Go Back N
   $W<2^n-1$
6. 协议 6——Selective Repeat
   $W<2^{n-1}$


# ch 4 The Medium Access Control Sublayer
+ **10 M 以上的网络不再使用曼彻斯特编码**

+ **Hubs, Bridges, Switches**
  冲突域（Collision Domain）不同，下图依次为 1 个，2 个，8 个（一个端口一个）![](Attachments/Pasted%20image%2020240423192355.png)
  广播域都是一个（Broadcast Domain）

