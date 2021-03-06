// 结构声明的语法：
//
// struct {int a; char b; float c;} x;
// struct {int a; char b; float c;} *z;
//
// 这两个声明编译器当作截然不同的类型，即使它们的成员列表完全相同。所以
//
// z = &x; // 非法
// ----------------------------------------------------------------------
//
// 标签允许多个声明使用同一个成员列表，并且创建同一种类型的结构。
//
// struct SIMPLE{
//     int a;
//     char b;
//     float c;
// };
//
// 该声明没有提供变量列表，所以它并未创建任何变量。
//
// struct SIMPLE x;
// struct SIMPLE *z;
// z = &x; // 合法
// ----------------------------------------------------------------------
// 
// typedef struct{
//     int a;
//     char b;
//     float c;
// } Simple;
//
// struct SIMPLE x;
// struct SIMPLE *z;
// z = &x; // 合法
//
// Simple 和 SIMPLE 效果几乎相同，区别是 Simple 是类型名而 SIMPLE 是结构
// 标签名
// ----------------------------------------------------------------------
//
// 结构的自引用：
//
// struct SELF{
//     int a;
//     struct SELF b;
//     int c;
// }; // 非法，使用不完整的结构
//
// struct SELF{
//     int a;
//     struct SELF *b;
//     int c;
// }; // 合法
//
// typedef struct SELF_TAG{
//     int a;
//     struct SELF_TAG *b;
//     int c;
// } SELF; // 合法
// --------------------------------------------------------------------
//
// 结构间的相互依赖关系：不完整声明
//
// struct B;
//
// struct A{
//     struct B;
// };
//
// struct B{
//     struct A;
// };
// ---------------------------------------------------------------------------
//
// 结构的储存分配：
//
// struct A{
//     char a;
//     int b;
//     char c;
// }; // 结构占 12 字节
//
// 设机器整型长度为 4 个字节，并且它的起始存储位置必须能被 4 整除，则：
// a    b    c
// #*** #### #***
//
// struct A{
//     int b;
//     char a;
//     char c;
// }; // 结构占 8 字节
//
// 设机器整型长度为 4 个字节，并且它的起始存储位置必须能被 4 整除，则：
// b    ac  
// #### ##**
//
// --> 默认情况下，编译器规定各成员变量存放的起始地址相对于结构的起始地址的
// --> 偏移量必须为该变量的类型所占用的字节数的倍数
//
// #pragma pack(n) 设定变量以 n 字节对齐方式。
//
// n 字节对齐就是说变量存放的起始地址的偏移量有两种情况：
//
// 第一、如果 n 大于等于该变量所占用的字节数，那么偏移量必须满足默认
//       对齐方式
// 第二、如果 n 小于该变量的类型所占用的字节数，那么偏移量为 n 的倍数，
//       不用满足默认的对齐方式
// 
// 如果数据类型为结构，它的默认对齐方式就是它的所有成员使用的对齐参数中
// 最大的一个
//
// #pragma pack(8)
// struct S1{
//     char a;
//     long b;
// };
//
// struct S2{
//     char c;
//     struct S1 d;
//     long long e;
// };
// #pragma pack() // 解除设定
//
// 则 sizeof(S1) = 4 + 4 = 8  sizeof(S2) = 4 + 8 + 4 + 8 = 24
//
// 1，每个成员分别按自己的对齐方式，并能最小化长度
// 2，复杂类型（如结构）的默认对齐方式是它最长的成员的对齐方式，这样
//    在成员是复杂类型时，可以最小化长度
// 3，对齐后的长度必须是成员中最大的对齐参数的整数倍，这样在处理数组
//    时可以保证每一项都边界对齐
//
// typedef struct{
//     char c1;
//     short s;
//     char c2;
//     int i;
// } Struct;
//
// #*## #*** ####
//
// size_t offsetof(type, member) 宏（定义于 stddef.h）
// 返回值表示指定成员开始存储的位置距离结构开始存储的位置偏移几个字节
// -------------------------------------------------------------------------
//
// 作为函数参数的结构：
//
// 在许多机器，可以把参数声明为寄存器变量，用以提高指针传递的效率。
// void print(register StructA const *st);
// ---------------------------------------------------------------------
//
// 位段（bit field）：
//
// 位段的声明和结构类似，但它的成员是一个或多个位的字段。这些不同长度的字段
// 实际上存储于一个或多个整型变量中。
//
// 位段成员必须声明为 int、signed int、或 unsigned int；其次，在成员名的后面
// 是一个冒号和一个整数，这个整数指定该位段所占用的位的数目。
//
// 最好不要用 int，它究竟被解释为有符号数还是无符号数取决于编译器
//
// struct CHAR{
//     unsigned ch   : 7;
//     unsigned font : 6;
//     unsigned size : 19;
// };
// struct CHAR ch1;
// --------------------------------------------------------------------------
//
// 联合（union）
//
// 所有成员引用的是内存中的相同位置
// 作用：在不同时刻把不同的东西存储于同一个位置
//
