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

C++ 存储类
存储类定义 C++ 程序中变量/函数的范围（可见性）和生命周期。这些说明符放置在它们所修饰的类型之前。下面列出 C++ 程序中可用的存储类：

auto
register
static
extern
mutable
thread_local (C++11)

auto 存储类
自 C++ 11 以来，auto 关键字用于两种情况：声明变量时根据初始化表达式自动推断该变量的类型、声明函数时函数返回值的占位符。

C++98标准中auto关键字用于自动变量的声明，但由于使用极少且多余，在C++11中已删除这一用法。

根据初始化表达式自动推断被声明的变量的类型，如：

auto f=3.14;      //double
auto s("hello");  //const char*
auto z = new auto(9); // int*
auto x1 = 5, x2 = 5.0, x3='r';//错误，必须是初始化为同一类型
register 存储类
register 存储类用于定义存储在寄存器中而不是 RAM 中的局部变量。这意味着变量的最大尺寸等于寄存器的大小（通常是一个词），且不能对它应用一元的 '&' 运算符（因为它没有内存位置）。

{
   register int  miles;
}
寄存器只用于需要快速访问的变量，比如计数器。还应注意的是，定义 'register' 并不意味着变量将被存储在寄存器中，它意味着变量可能存储在寄存器中，这取决于硬件和实现的限制。

static 存储类
static 存储类指示编译器在程序的生命周期内保持局部变量的存在，而不需要在每次它进入和离开作用域时进行创建和销毁。因此，使用 static 修饰局部变量可以在函数调用之间保持局部变量的值。

static 修饰符也可以应用于全局变量。当 static 修饰全局变量时，会使变量的作用域限制在声明它的文件内。

在 C++ 中，当 static 用在类数据成员上时，会导致仅有一个该成员的副本被类的所有对象共享。

实例
#include <iostream>
 
// 函数声明 
void func(void);
 
static int count = 10; /* 全局变量 */
 
int main()
{
    while(count--)
    {
       func();
    }
    return 0;
}
// 函数定义
void func( void )
{
    static int i = 5; // 局部静态变量
    i++;
    std::cout << "变量 i 为 " << i ;
    std::cout << " , 变量 count 为 " << count << std::endl;
}
当上面的代码被编译和执行时，它会产生下列结果：

变量 i 为 6 , 变量 count 为 9
变量 i 为 7 , 变量 count 为 8
变量 i 为 8 , 变量 count 为 7
变量 i 为 9 , 变量 count 为 6
变量 i 为 10 , 变量 count 为 5
变量 i 为 11 , 变量 count 为 4
变量 i 为 12 , 变量 count 为 3
变量 i 为 13 , 变量 count 为 2
变量 i 为 14 , 变量 count 为 1
变量 i 为 15 , 变量 count 为 0

extern 存储类
extern 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的。当您使用 'extern' 时，对于无法初始化的变量，会把变量名指向一个之前定义过的存储位置。

当您有多个文件且定义了一个可以在其他文件中使用的全局变量或函数时，可以在其他文件中使用 extern 来得到已定义的变量或函数的引用。可以这么理解，extern 是用来在另一个文件中声明一个全局变量或函数。

extern 修饰符通常用于当有两个或多个文件共享相同的全局变量或函数的时候，如下所示：

第一个文件：main.cpp

实例
#include <iostream>
 
int count ;
extern void write_extern();
 
int main()
{
   count = 5;
   write_extern();
}
第二个文件：support.cpp

实例
#include <iostream>
 
extern int count;
 
void write_extern(void)
{
   std::cout << "Count is " << count << std::endl;
}
在这里，第二个文件中的 extern 关键字用于声明已经在第一个文件 main.cpp 中定义的 count。现在 ，编译这两个文件，如下所示：

$ g++ main.cpp support.cpp -o write
这会产生 write 可执行程序，尝试执行 write，它会产生下列结果：

$ ./write
Count is 5
mutable 存储类
mutable 说明符仅适用于类的对象，这将在本教程的最后进行讲解。它允许对象的成员替代常量。也就是说，mutable 成员可以通过 const 成员函数修改。

thread_local 存储类
使用 thread_local 说明符声明的变量仅可在它在其上创建的线程上访问。 变量在创建线程时创建，并在销毁线程时销毁。 每个线程都有其自己的变量副本。

thread_local 说明符可以与 static 或 extern 合并。

可以将 thread_local 仅应用于数据声明和定义，thread_local 不能用于函数声明或定义。

以下演示了可以被声明为 thread_local 的变量：

thread_local int x;  // 命名空间下的全局变量
class X
{
    static thread_local std::string s; // 类的static成员变量
};
static thread_local std::string X::s;  // X::s 是需要定义的
 
void foo()
{
    thread_local std::vector<int> v;  // 本地变量
}

std::cout << "Count is " << count << std::endl;
在前面的学习中我们看到的输出没有 std::，而这一节出现了上面的代码。

std 是标准库函数使用的命名空间，是 standard（标准）的缩写。

using namespace std ，它声明了命名空间 std，后续如果有未指定命名空间的符号，那么默认使用 std，这样就可以使用 cin、cout、vector 等。

假设你不使用预处理 using namespace std;,就要加上 std::cin 或者 std::cout。

cin 用于从控制台获取用户输入，cout 用于将数据输出到控制台。

cin 是输入流对象，cout 是输出流对象，它们分别可以用 >> 和 <<，是因为分别在其类中对相应运算符进行了重载。

静态局部变量
在局部变量前，加上关键字static，该变量就被定义成为一个静态局部变量。 我们先举一个静态局部变量的例子，如下：

#include <iostream>

void fn();
int main()
{
    fn();
    fn();
    fn();
}
void fn()
{
    static int  n=10;
    std::cout<<n<<std::endl;
    n++;
}
通常，在函数体内定义了一个变量，每当程序运行到该语句时都会给该局部变量分配栈内存。但随着程序退出函数体，系统就会收回栈内存，局部变量也相应失效。但有时候我们需要在两次调用之间对变量的值进行保存。

通常的想法是定义一个全局变量来实现。但这样一来，变量已经不再属于函数本身了，不再仅受函数的控制，给程序的维护带来不便。

静态局部变量正好可以解决这个问题。静态局部变量保存在全局数据区，而不是保存在栈中，每次的值保持到下一次调用，直到下次赋新值。

静态局部变量有以下特点：

该变量在全局数据区分配内存；
静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化；
静态局部变量一般在声明处初始化，如果没有显式初始化，会被程序自动初始化为0；
它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，当定义它的函数或语句块结束时，其作用域随之结束；

1.static 修饰类的成员变量

 1). 静态成员变量是先于类的对象而存在
 2). 这个类的所有对象共用一个静态成员
 3). 如果静态成员是公有的，那么可以直接通过类名调用
 4). 静态成员数据在声明时候类外初始化
#include <iostream>

using namespace std;
class Data
{
public:
    Data(){}
    ~Data(){}
    void show()
    {
        cout<<this->data<<" "<<number<<endl;
    }

    static void showData()//先于类的对象而存在
    {
        //这方法调用的时候不包含this指针
        cout<<" "<<number<<endl;
    }

private:
    int data;
public:
    static int number; //静态数据在声明时候类外初始化
};
int Data::number=0;//静态成员初始化

int main()
{
    Data::showData();//通过类名直接调用


    Data::number = 100;//通过类名直接使用
    Data d;
    d.show();
    d.showData();//通过对象调用

    cout << "Hello World!" << endl;
    return 0;
}
2.static 修饰类的成员方法

 1). 静态成员函数是先于类的对象而存在
 2). 可用类名直接调用（公有）
 3). 在静态成员函数中没有this指针，所以不能使用非静态成员
const 修饰--常量	---- const修饰的常量代替宏定义

修饰成员变量

const int data;
const 修饰的成员变量必须在构造方法的参数列表初始化（const static int pdata=10;除外）const 修饰的成员变量不能被修改

修饰成员方法

void showData()const{ }
const 修饰的成员函数中不能修改成员变量，不能调用非 const 修饰的函数

#include <iostream>
int main()
{
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
std 代表标准命名空间，:: 则是作用域运算符，在这里用于定位到 std 命名空间。

头文件 <iostream> 在这个命名空间内声明了 istream 与 ostream 等 IO 类，同时在 std 内声明了 istream cin; 与 ostream cout; 这两个常用对象。

using namespace std; 的作用是曝光整个 std 名称空间，使其中的所有成员皆可直接使用。


  grh***g@foxmail.com

const 相比 #define 的优点：

1.const 常量有数据类型，而 #define 没有，编译器可以对前者进行类型安全检查，而对后者只能进行字符替换，没有安全检查，并且在字符替换时候可能导致意想不到的错误。

2.有些集成化的调试工具可以对 const 常量进行调试，但是不能对宏常量进行调试。

thread_local 在跨线程时使用:

eg: A 线程是用来拉取数据的，B 线程是用来更新 UI 的，那么 A在拉去数据后应该通知B线程去更新 UI，因为 A 线程不能更新 UI，此时更新 UI 就应该由 B 线程的 thread_local 去进行(因为只有 B 线程能访问)，这样可以防止因为跨线程更新 UI 引起的问题。

C++ 运算符
运算符是一种告诉编译器执行特定的数学或逻辑操作的符号。C++ 内置了丰富的运算符，并提供了以下类型的运算符：

算术运算符
关系运算符
逻辑运算符
位运算符
赋值运算符
杂项运算符

算术运算符
下表显示了 C++ 支持的算术运算符。

假设变量 A 的值为 10，变量 B 的值为 20，则：

运算符	描述	实例
+	把两个操作数相加	A + B 将得到 30
-	从第一个操作数中减去第二个操作数	A - B 将得到 -10
*	把两个操作数相乘	A * B 将得到 200
/	分子除以分母	B / A 将得到 2
%	取模运算符，整除后的余数	B % A 将得到 0
++	自增运算符，整数值增加 1	A++ 将得到 11
--	自减运算符，整数值减少 1	A-- 将得到 9

关系运算符
下表显示了 C++ 支持的关系运算符。

假设变量 A 的值为 10，变量 B 的值为 20，则：

运算符	描述	实例
==	检查两个操作数的值是否相等，如果相等则条件为真。	(A == B) 不为真。
!=	检查两个操作数的值是否相等，如果不相等则条件为真。	(A != B) 为真。
>	检查左操作数的值是否大于右操作数的值，如果是则条件为真。	(A > B) 不为真。
<	检查左操作数的值是否小于右操作数的值，如果是则条件为真。	(A < B) 为真。
>=	检查左操作数的值是否大于或等于右操作数的值，如果是则条件为真。	(A >= B) 不为真。
<=	检查左操作数的值是否小于或等于右操作数的值，如果是则条件为真。	(A <= B) 为真。

逻辑运算符
下表显示了 C++ 支持的关系逻辑运算符。

假设变量 A 的值为 1，变量 B 的值为 0，则：

运算符	描述	实例
&&	称为逻辑与运算符。如果两个操作数都非零，则条件为真。	(A && B) 为假。
||	称为逻辑或运算符。如果两个操作数中有任意一个非零，则条件为真。	(A || B) 为真。
!	称为逻辑非运算符。用来逆转操作数的逻辑状态。如果条件为真则逻辑非运算符将使其为假。	!(A && B) 为真。

位运算符
位运算符作用于位，并逐位执行操作。&、 | 和 ^ 的真值表如下所示：

p	q	p & q	p | q	p ^ q
0	0	  0	    0	    0
0	1	  0	    1	    1
1	1	  1	    1	    0
1	0	  0	    1	    1

赋值运算符
下表列出了 C++ 支持的赋值运算符：

运算符	描述	实例
=	简单的赋值运算符，把右边操作数的值赋给左边操作数	C = A + B 将把 A + B 的值赋给 C
+=	加且赋值运算符，把右边操作数加上左边操作数的结果赋值给左边操作数	C += A 相当于 C = C + A
-=	减且赋值运算符，把左边操作数减去右边操作数的结果赋值给左边操作数	C -= A 相当于 C = C - A
*=	乘且赋值运算符，把右边操作数乘以左边操作数的结果赋值给左边操作数	C *= A 相当于 C = C * A
/=	除且赋值运算符，把左边操作数除以右边操作数的结果赋值给左边操作数	C /= A 相当于 C = C / A
%=	求模且赋值运算符，求两个操作数的模赋值给左边操作数	C %= A 相当于 C = C % A
<<=	左移且赋值运算符	C <<= 2 等同于 C = C << 2
>>=	右移且赋值运算符	C >>= 2 等同于 C = C >> 2
&=	按位与且赋值运算符	C &= 2 等同于 C = C & 2
^=	按位异或且赋值运算符	C ^= 2 等同于 C = C ^ 2
|=	按位或且赋值运算符	C |= 2 等同于 C = C | 2

杂项运算符
下表列出了 C++ 支持的其他一些重要的运算符。

运算符	描述
sizeof	sizeof 运算符返回变量的大小。例如，sizeof(a) 将返回 4，其中 a 是整数。
Condition ? X : Y	条件运算符。如果 Condition 为真 ? 则值为 X : 否则值为 Y。
,	逗号运算符会顺序执行一系列运算。整个逗号表达式的值是以逗号分隔的列表中的最后一个表达式的值。
.（点）和 ->（箭头）	成员运算符用于引用类、结构和共用体的成员。
Cast	强制转换运算符把一种数据类型转换为另一种数据类型。例如，int(2.2000) 将返回 2。
&	指针运算符 & 返回变量的地址。例如 &a; 将给出变量的实际地址。
*	指针运算符 * 指向一个变量。例如，*var; 将指向变量 var。
C++ 中的运算符优先级
运算符的优先级确定表达式中项的组合。这会影响到一个表达式如何计算。某些运算符比其他运算符有更高的优先级，例如，乘除运算符具有比加减运算符更高的优先级。

例如 x = 7 + 3 * 2，在这里，x 被赋值为 13，而不是 20，因为运算符 * 具有比 + 更高的优先级，所以首先计算乘法 3*2，然后再加上 7。

下表将按运算符优先级从高到低列出各个运算符，具有较高优先级的运算符出现在表格的上面，具有较低优先级的运算符出现在表格的下面。在表达式中，较高优先级的运算符会优先被计算。

类别 	运算符 	结合性 
后缀 	() [] -> . ++ - -  	从左到右 
一元 	+ - ! ~ ++ - - (type)* & sizeof 	从右到左 
乘除 	* / % 	从左到右 
加减 	+ - 	从左到右 
移位 	<< >> 	从左到右 
关系 	< <= > >= 	从左到右 
相等 	== != 	从左到右 
位与 AND 	& 	从左到右 
位异或 XOR 	^ 	从左到右 
位或 OR 	| 	从左到右 
逻辑与 AND 	&& 	从左到右 
逻辑或 OR 	|| 	从左到右 
条件 	?: 	从右到左 
赋值 	= += -= *= /= %=>>= <<= &= ^= |= 	从右到左 
逗号 	, 	从左到右 
