# 1 概论

![](Attachments/Pasted%20image%2020250614153240.png)
![](Attachments/Pasted%20image%2020250614154834.png)
![](Attachments/Pasted%20image%2020250614155104.png)


# 2 交换网络

| 开关阵列                                                        | S 接线器                                                | T 接线器                                               |
| ----------------------------------------------------------- | ---------------------------------------------------- | --------------------------------------------------- |
| 不允许出线冲突时，同 column 只允许一个 1 出现；<br>不允许同发广播时，同 row 只允许一个 1 出现。 | S接线器是开关阵列和控制存储器CM组成的                                 | 话音存储器（SM，Speech Memory）<br>控制存储器（CM，Control Memory） |
| 开关数为入线数与出线数的乘积，**无内部阻塞**<br>若为无向，需要×2                       | 一个 S 接线器所含控制存储器 CM 的数量=入（出）线数。<br>（输入控制 CM 数=入线数，反之） | SM存储单元个数等于 PCM 线路**每帧时隙数**<br>每单元至少 8bit（一路话音）      |
| 容易实现同发和广播                                                   | 每个控制存储器 CM 含有的存储单元个数=时隙数。                            | CM存储单元个数等于 SM；<br>每单元至少 $log_2n$（n为时隙数）比特           |
|                                                             | 输**出**控制方式易于实现多播                                     | 严格无阻塞，并且可避免出线冲突。<br>易于实现同发和广播。                      |

+ BANYAN 网络构造
![](Attachments/Pasted%20image%2020250614172457.png)



# 3 电路交换
![](Attachments/Pasted%20image%2020250614182857.png)

+ **全程话路连接**
【现代交换原理北京邮电大学】 https://www.bilibili.com/video/BV1pT4y157cf?p=31&vd_source=dbd67c6676f59c6eb87be4a08bf448c3



# 4 分组交换
- LSP：Label Switched Path 标记交换路径，类似虚电路。
- FEC：Forward Equivalence Class 前转等价类，灵活按照多种方式划分，相同 FEC 的包具有相同 Label，走相同 LSP。
- LIB：Label Information Base 标记信息库，保存转发 Labeled 分组所需要的信息。
- Ingress LER：Ingress Label Edge Router 入口边缘路由器，为每个 FEC 生成 Label，映射到 LSP 下一跳的标记。对入口 IP 分组进行分类，确定 FEC，根据 FEC 查询 LIB 得到下一跳 Label，将 Label 插入 IP 包头，从相应端口发送。
- LSR：Label Switch Router，维护 LIB、完成标记置换。
- Egress LER：去掉 Label 还原成普通 IP 包继续转发。


# 5 信令系统

![](Attachments/Pasted%20image%2020250615123422.png)


# 6 移动交换
- **MS 移动台**：
  - 移动终端 **ME** 
  - 手机客户识别卡 **SIM**
- **BSS 无线基站子系统**：
  - 基站收发信机 **BTS**
  - 基站控制器 **BSC**
- **NSS 交换网路子系统**：
  - 移动交换中心 **MSC**
  - 归属位置寄存器 **HLR**：存储本地用户位置信息的数据库。每个用户都必须在某个 HLR（相当于该用户的原籍）中登记。
    - 即使用户漫游到该 HLR 服务区外，HLR 也要登记漫游区域传送来的位置信息。
  - 访问位置寄存器 **VLR**：存储来访用户位置信息的数据库。一个 VLR 可以为一个或多个相邻 MSC 服务。
    - 当移动用户漫游到新的 MSC，向对应的 VLR 申请登记。
    - 移动用户离开此 VLR 服务区时，HLR 接收到新的 VLR 发来的消息，通知旧的 VLR 删除此用户的位置信息
  - 鉴权中心 **AUC**
  - 设备标志寄存器 **EIR**：存储移动台设备参数的数据库。
- OMC 维护操作子系统
- GMSC 网关交换中心

+ **GSM 切换**
  - 同一BSC内小区间的切换![](Attachments/Pasted%20image%2020250615154154.png)
  - 同一MSC内不同BSC小区间的切换![](Attachments/Pasted%20image%2020250615154211.png)
  - 不同MSC间的切换![](Attachments/Pasted%20image%2020250615154241.png)

# 7 NGN与SDN

