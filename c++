标准库
标准的 C++ 由三个重要部分组成：

核心语言，提供了所有构件块，包括变量、数据类型和常量，等等。
C++ 标准库，提供了大量的函数，用于操作文件、字符串等。
标准模板库（STL），提供了大量的方法，用于操作数据结构等。

C++ 语言定义了一些头文件，这些头文件包含了程序中必需的或有用的信息。上面这段程序中，包含了头文件 <iostream>。
using namespace std; 告诉编译器使用 std 命名空间。命名空间是 C++ 中一个相对新的概念。

C++ 关键字
下表列出了 C++ 中的保留字。这些保留字不能作为常量名、变量名或其他标识符名称。
asm	else	new	this
auto	enum	operator	throw
bool	explicit	private	true
break	export	protected	try
case	extern	public	typedef
catch	false	register	typeid
char	float	reinterpret_cast	typename
class	for	return	union
const	friend	short	unsigned
const_cast	goto	signed	using
continue	if	sizeof	virtual
default	inline	static	void
delete	int	static_cast	volatile
do	long	struct	wchar_t
double	mutable	switch	while
dynamic_cast	namespace	template

下表显示了各种变量类型在内存中存储值时需要占用的内存，以及该类型的变量所能存储的最大值和最小值。

注意：不同系统会有所差异。

类型	位	范围
char	1 个字节	-128 到 127 或者 0 到 255
unsigned char	1 个字节	0 到 255
signed char	1 个字节	-128 到 127
int	4 个字节	-2147483648 到 2147483647
unsigned int	4 个字节	0 到 4294967295
signed int	4 个字节	-2147483648 到 2147483647
short int	2 个字节	-32768 到 32767
unsigned short int	2 个字节	0 到 65,535
signed short int	2 个字节	-32768 到 32767
long int	8 个字节	-9,223,372,036,854,775,808 到 9,223,372,036,854,775,807
signed long int	8 个字节	-9,223,372,036,854,775,808 到 9,223,372,036,854,775,807
unsigned long int	8 个字节	0 to 18,446,744,073,709,551,615
float	4 个字节	+/- 3.4e +/- 38 (~7 个数字)
double	8 个字节	+/- 1.7e +/- 308 (~15 个数字)
long double	16 个字节	+/- 1.7e +/- 308 (~15 个数字)
wchar_t	2 或 4 个字节	1 个宽字符

typedef 与 #define 的区别

1. 执行时间不同

关键字 typedef 在编译阶段有效，由于是在编译阶段，因此 typedef 有类型检查的功能。

#define 则是宏定义，发生在预处理阶段，也就是编译之前，它只进行简单而机械的字符串替换，而不进行任何检查。

【例1.1】typedef 会做相应的类型检查：

typedef unsigned int UINT;
 
void func()
{
    UINT value = "abc"; // error C2440: 'initializing' : cannot convert from 'const char [4]' to 'UINT'
    cout << value << endl;
}
【例1.2】#define不做类型检查：

// #define用法例子：
#define f(x) x*x
int main()
{
    int a=6, b=2, c;
    c=f(a) / f(b);
    printf("%d\n", c);
    return 0;
}
程序的输出结果是: 36，根本原因就在于 #define 只是简单的字符串替换。

2、功能有差异

typedef 用来定义类型的别名，定义与平台无关的数据类型，与 struct 的结合使用等。

#define 不只是可以为类型取别名，还可以定义常量、变量、编译开关等。

3、作用域不同

#define 没有作用域的限制，只要是之前预定义过的宏，在以后的程序中都可以使用。

而 typedef 有自己的作用域。

【例3.1】没有作用域的限制，只要是之前预定义过就可以

void func1()
{
    #define HW "HelloWorld";
}
 
void func2()
{
    string str = HW;
    cout << str << endl;
}
【例3.2】而typedef有自己的作用域

void func1()
{
    typedef unsigned int UINT;
}
 
void func2()
{
    UINT uValue = 5;//error C2065: 'UINT' : undeclared identifier
}
【例3.3】

class A
{
    typedef unsigned int UINT;
    UINT valueA;
    A() : valueA(0){}
};
 
class B
{
    UINT valueB;
    //error C2146: syntax error : missing ';' before identifier 'valueB'
    //error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
};
上面例子在B类中使用UINT会出错，因为UINT只在类A的作用域中。此外，在类中用typedef定义的类型别名还具有相应的访问权限，【例3.4】：

class A
{
    typedef unsigned int UINT;
    UINT valueA;
    A() : valueA(0){}
};
 
void func3()
{
    A::UINT i = 1;
    // error C2248: 'A::UINT' : cannot access private typedef declared in class 'A'
}
而给UINT加上public访问权限后，则可编译通过。

【例3.5】：

class A
{
public:
    typedef unsigned int UINT;
    UINT valueA;
    A() : valueA(0){}
};
 
void func3()
{
    A::UINT i = 1;
    cout << i << endl;
}
4、对指针的操作

二者修饰指针类型时，作用不同。

typedef int * pint;
#define PINT int *
 
int i1 = 1, i2 = 2;
 
const pint p1 = &i1;    //p不可更改，p指向的内容可以更改，相当于 int * const p;
const PINT p2 = &i2;    //p可以更改，p指向的内容不能更改，相当于 const int *p；或 int const *p；
 
pint s1, s2;    //s1和s2都是int型指针
PINT s3, s4;    //相当于int * s3，s4；只有一个是指针。
 
void TestPointer()
{
    cout << "p1:" << p1 << "  *p1:" << *p1 << endl;
    //p1 = &i2; //error C3892: 'p1' : you cannot assign to a variable that is const
    *p1 = 5;
    cout << "p1:" << p1 << "  *p1:" << *p1 << endl;
 
    cout << "p2:" << p2 << "  *p2:" << *p2 << endl;
    //*p2 = 10; //error C3892: 'p2' : you cannot assign to a variable that is const
    p2 = &i1;
    cout << "p2:" << p2 << "  *p2:" << *p2 << endl;
}
结果：

p1:00EFD094  *p1:1
p1:00EFD094  *p1:5
p2:00EFD098  *p2:2
p2:00EFD094  *p2:5

