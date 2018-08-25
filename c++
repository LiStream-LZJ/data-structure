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

C++ 变量作用域
作用域是程序的一个区域，一般来说有三个地方可以定义变量：
在函数或一个代码块内部声明的变量，称为局部变量。
在函数参数的定义中声明的变量，称为形式参数。
在所有函数外部声明的变量，称为全局变量。

初始化局部变量和全局变量
当局部变量被定义时，系统不会对其初始化，您必须自行对其初始化。定义全局变量时，系统会自动初始化为下列值：

数据类型	初始化默认值
int	0
char	'\0'
float	0
double	0
pointer	NULL
正确地初始化变量是一个良好的编程习惯，否则有时候程序可能会产生意想不到的结果。


转义序列	含义
\\	\ 字符
\'	' 字符
\"	" 字符
\?	? 字符
\a	警报铃声
\b	退格键
\f	换页符
\n	换行符
\r	回车
\t	水平制表符
\v	垂直制表符
\ooo	一到三位的八进制数
\xhh . . .	一个或多个数字的十六进制数

#define 预处理器
下面是使用 #define 预处理器定义常量的形式：

#define identifier value
具体请看下面的实例：

实例
#include <iostream>
using namespace std;
#define LENGTH 10   
#define WIDTH  5
#define NEWLINE '\n'
int main()
{
   int area;  
   area = LENGTH * WIDTH;
   cout << area;
   cout << NEWLINE;
   return 0;
}
当上面的代码被编译和执行时，它会产生下列结果：
50

const 关键字
您可以使用 const 前缀声明指定类型的常量，如下所示：

const type variable = value;
具体请看下面的实例：

实例
#include <iostream>
using namespace std;
int main()
{
   const int  LENGTH = 10;
   const int  WIDTH  = 5;
   const char NEWLINE = '\n';
   int area;  
   area = LENGTH * WIDTH;
   cout << area;
   cout << NEWLINE;
   return 0;
}
当上面的代码被编译和执行时，它会产生下列结果：
50

w

  934***022@qq.com

   参考地址

宏定义 #define 和常量 const 的区别
类型和安全检查不同

宏定义是字符替换，没有数据类型的区别，同时这种替换没有类型安全检查，可能产生边际效应等错误；

const常量是常量的声明，有类型区别，需要在编译阶段进行类型检查

编译器处理不同

宏定义是一个"编译时"概念，在预处理阶段展开，不能对宏定义进行调试，生命周期结束与编译时期；

const常量是一个"运行时"概念，在程序运行使用，类似于一个只读行数据

存储方式不同

宏定义是直接替换，不会分配内存，存储与程序的代码段中；

const常量需要进行内存分配，存储与程序的数据段中

定义域不同

void f1 ()
{
    #define N 12
    const int n 12;
}
void f2 ()
{
    cout<<N <<endl; //正确，N已经定义过，不受定义域限制
    cout<<n <<endl; //错误，n定义域只在f1函数中
}
定义后能否取消

宏定义可以通过#undef来使之前的宏定义失效

const常量定义后将在定义域内永久有效

void f1()
{
  #define N 12
  const int n = 12;

  #undef N //取消宏定义后，即使在f1函数中，N也无效了
  #define N 21//取消后可以重新定义
}
是否可以做函数参数

宏定义不能作为参数传递给函数

const常量可以在函数的参数列表中出现

1.const 定义常量之后，是不能够改变的

2.宏定义是可以取消的

定义： #define    N    21
取消： #undef    N    12

const限定符定以后是不可以改变的，所以在定义时必须赋初始值，要不然是错误的，除非这个变量是用extern修饰的外部变量。 例如：

const int A=10;       //正确。
const int A;          //错误，没有赋初始值。
extern const int A;   //正确，使用extern的外部变量。

const关键字

const是constant的简写，只要一个变量前面用const来修饰，就意味着该变量里的数据可以被访问，不能被修改。也就是说const意味着只读（readonly）。

规则：const离谁近，谁就不能被修改；

const修饰一个变量，一定要给这个变量初始化值，若不初始化，后面就无法初始化。

本质：const在谁后面谁就不可以修改，const在最前面则将其后移一位，二者等效。

const关键字作用

为给读你代码的人传达非常有用的信息，声明一个参数为常量是为了告诉用户这个参数的应用目的；
通过给优化器一些附加信息，使关键字const也许能产生更紧凑的代码；
合理使用关键字const可以使编译器很自然的保护那些不希望被修改的参数，防止无意的代码修改，可以减少bug的出现；
const关键字应用

欲阻止一个变量被改变，可使用const，在定义该const变量时，需先初始化，以后就没有机会改变他了；
对指针而言，可以指定指针本身为const，也可以指定指针所指的数据为const，或二者同时指定为const；
在一个函数声明中，const可以修饰形参表明他是一个输入参数，在函数内部不可以改变其值；
对于类的成员函数，有时候必须指定其为const类型，表明其是一个常函数，不能修改类的成员变量；
对于类的成员函数，有时候必须指定其返回值为const类型，以使得其返回值不为“左值”。

C++ 修饰符类型
C++ 允许在 char、int 和 double 数据类型前放置修饰符。修饰符用于改变基本类型的含义，所以它更能满足各种情境的需求。

下面列出了数据类型修饰符：

signed
unsigned
long
short
修饰符 signed、unsigned、long 和 short 可应用于整型，signed 和 unsigned 可应用于字符型，long 可应用于双精度型。

修饰符 signed 和 unsigned 也可以作为 long 或 short 修饰符的前缀。例如：unsigned long int。

C++ 允许使用速记符号来声明无符号短整数或无符号长整数。您可以不写 int，只写单词 unsigned、short 或 unsigned、long，int 是隐含的。例如，下面的两个语句都声明了无符号整型变量。

unsigned x;
unsigned int y;
为了理解 C++ 解释有符号整数和无符号整数修饰符之间的差别，我们来运行一下下面这个短程序：

实例
#include <iostream>
using namespace std;
 
/* 
 * 这个程序演示了有符号整数和无符号整数之间的差别
*/
int main()
{
   short int i;           // 有符号短整数
   short unsigned int j;  // 无符号短整数
 
   j = 50000;
 
   i = j;
   cout << i << " " << j;
 
   return 0;
}
当上面的程序运行时，会输出下列结果：

-15536 50000
上述结果中，无符号短整数 50,000 的位模式被解释为有符号短整数 -15,536。

C++ 中的类型限定符
类型限定符提供了变量的额外信息。

限定符	含义
const	const 类型的对象在程序执行期间不能被修改改变。
volatile	修饰符 volatile 告诉编译器不需要优化volatile声明的变量，让程序可以直接从内存中读取变量。对于一般的变量编译器会对变量进行优化，将内存中的变量值放在寄存器中以加快读写效率。
restrict	由 restrict 修饰的指针是唯一一种访问它所指向的对象的方式。只有 C99 增加了新的类型限定符 restrict。

