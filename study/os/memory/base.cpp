#if 0

程序装入内存的方式
--------------------

1. 绝对装入
2. 重定位
3. 动态运行时装入 : 内存可换出磁盘，以后再装入

重定位
-------

静态重定位 : 把程序的逻辑地址改为实际的内存地址，在装入时一次完成，在程序
             运行期间不再进行重定位，难实现共享
动态重定位 : 在程序执行期间，每次访问内存之前进行重定位，方便实现共享

分区管理技术
-------------

1. 固定分区法 : 分区大小，数量固定，每个分区只可装入一个进程
2. 动态分区法 : 分区在进程装入内存才建立，大小为进程大小；释放时与邻居
                空闲块合并
                分区链表
				分配算法 : 最先适应，最佳适应

碎片
-----

外碎片 : 分区内部出现的碎片（固定分区法）
内碎片 : 在所有分区之外产生的碎片（动态分区法）

可重定位分区分配 : 使所有进程的分区连在一起，则所有空间区留在另一端

动态重定位硬件实现包括一对寄存器
1. 基址寄存器 : 存放用户程序在内存的起始地址
2. 限长寄存器 : 存放用户程序的逻辑地址的最大范围

分页技术
---------

1. 逻辑空间分页
2. 内存空间分块 : 每块大小与页面大小相同

例如 : 地址字长 32 位

31          12 11           0
#####页号##### ###页内地址###

页表
-----

1. 页号
2. 块号

页表的作用是实现从页号到物理块号的地址映射

内存块表 : 操作系统必须知道哪些块已经分配出去，哪些没有

多级页表
---------

二级页表
1. 外层页表
2. 内层页表
3. 页内地址

分段技术
--------

段表地址寄存器
1. 起始地址
2. 段表长（一共有多少表项）

逻辑地址的确定（即逻辑地址是二维的）
1. 段号
2. 段内地址（段的逻辑起始地址）

为了找出每个逻辑段在所对应的物理内存中分区的位置，引入段表
1. 段号
2. 段长
3. 段起始地址（段的物理起始地址）

虚拟存储管理
-------------

例子：大型游戏无法一次全部装入内存

特征：
1. 虚拟扩充
2. 部分装入
3. 离散分配
4. 多次对换

请求分页技术
-------------

之前的分页管理属于单纯分页技术，要求把运行的进程全部装入内存；请求分页
技术则提供虚拟存储器

因此，页表结构相应变为：

页号  内存块号  改变位   状态位  引用位   外存地址
####  ########  ######   ######  ######   ########

改变位 : 为 1 表示该页已被修改过
引用位 : 用来指示最近是否访问过该页

页面置换算法
-------------

缺页率 = (1 - p) * ma + p * mb

ma : 内存存取时间
mb : 缺页处理时间

抖动 : 刚换出的页，很快又要被换入

例子 :
页面访问序列 : 7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1
内存块数 : 3

1. 先进先出法 (FIFO)
2. 最佳置换法 (OPT) : 所选择的老页面应在将来不被使用，或者是在最远
					  的将来才被访问
3. 最近最少使用置换法 (LRU) : 把最近最长一段时间内不曾使用的页面淘汰掉
							  实现 : 计数器，栈
4. 最近未使用置换法 (NRU) : 存储分块表表项增加引用位，操作系统定期置零，当
							访问该页时置 1，内存满了后把 0 的置换出来

内存分配算法
------------

1. 等分法
2. 比例法
3. 优先权法

防止抖动
---------

1. 采用局部置换策略 : 一个进程发生抖动，不能从其他进程获取内存块
2. 挂起某些进程
3. 采用缺页频度法 : 设定一个缺页率上下限，如果进程缺页率高于上限则为其分配
                    内存，如果低于下限则从该进程占有的内存中取走一块内存块

段页式结合系统
---------------

逻辑地址结构

段号  段内页号  页内地址
####  ########  ########

Linux 三级页表

虚拟地址

PGD 表项下标  PMD 表项下标  PT 下标  页内偏移
############  ############  #######  ########

#endif
