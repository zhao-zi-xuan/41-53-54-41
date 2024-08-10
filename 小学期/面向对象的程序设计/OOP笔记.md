# 面向对象的程序设计

## DAY-01

### 类的声明

class关键字、大括号，public/protected/private控制的成员，成员分为数据成员和成员函数。

### 头文件的编写

* 哨兵

  ```cpp
  #ifndef FILENAME_H
  
  #define FILENAME_H
  
  
  
  #endif
  ```

* 类声明

### 拷贝构造函数

```cpp
<classname>( );//构造函数

<classname>(const <classname>& 对象名)//拷贝构造函数
```

### 作业要求

定义日期类：

1. 年的范围1900~9999

2. 年月日均有常引用成员，方便快捷读出值

3. 默认构造函数初始化对象为为1900年1月1日

4. 带参数构造函数初始化对象为形参指定日期

5. 有拷贝构造函数

6. 分h和cpp文件编写，h文件有哨兵

7. 数据成员、成员函数的参数和返回值，类型选择合理

8. 有一个函数IsValidDate，返回对象自身存储日期是否为合理日期（考虑年月日范围，包括闰年），返回值类型如何选取？

9. 自行编写main函数，从键盘输入一个日期，显示其是否为合理日期。

10. 考虑年的“范围1900~9999”是否可以作为静态成员，为什么？如果可以，如何实现？



## DAY-02

### 静态（static）

0/ALL: 当成员函数是0个或所有对象的特征或成员函数的操作对象是0或全体对象时，当使用静态（static）

### 运算符重载

赋值运算符重载：

```cpp
Vector& Vector::operator=(const Vector& aVector){

if(this != &aVector){

delete[] Data;

Data = new int[10];

}

}
```

注：

1. 赋值运算符重载函数的参数**一般**是函数所在类的const类型的引用

* 我们不希望在这个函数中对用来进行赋值的“原版”做任何修改。

  加上const，对于const的和非const的实参，函数就能接受；如果不加，就只能接受非const的实参。

* 用引用是因为：

  可以避免在函数调用时对实参的一次拷贝，提高了效率。

  

2. 返回值一般是被赋值者的引用，即*this，原因是

* 这样在函数返回时避免一次拷贝，提高了效率。

* 更重要的，这样可以实现连续赋值，即类似a=b=c这样。如果不是返回引用而是返回值类型，那么，执行a=b时，调用赋值运算符重载函数，在函数返回时，由于返回的是值类型，所以要对return后边的“东西”进行一次拷贝，得到一个未命名的副本（有些资料上称之为“匿名对象”），然后将这个副本返回，而这个副本是右值，所以，执行a=b后，得到的是一个右值，再执行=c就会出错。

* **这不是强制的**，我们可以将函数返回值声明为void，然后什么也不返回，只不过这样就不能够连续赋值了。

### 异常处理

#include <stdexcept>

```cpp
try {   // 保护代码 

}catch( ExceptionName e1 ) { 

// catch 块 

}catch( ExceptionName e2 ) { 

// catch 块 

}catch( ExceptionName eN ) { 

// catch 块 

}
```



### 作业要求

定义日期类：

1、年的范围1900~9999：作为私有静态数据成员；通过自行定义的公有静态成员函数进行修改，修改时应保证数据逻辑关系正确，否则抛出异常；用过公有静态常引用成员进行读取

2、用于初始化对象的默认年月日：作为私有静态数据成员（用1900年1月1日初始化静态数据成员）；通过自行定义的公有静态成员函数进行修改，修改时应保证数据逻辑关系正确，否则抛出异常；用过公有静态常引用成员进行读取

~~3、年月日均有常引用成员，方便快捷读出值~~

4、默认造函数初始化对象为年月日默认值

5、带参数构造函数初始化对象为形参指定日期，非合理日期则抛出异常

~~6、拷贝构造函数~~

7、赋值运算符

8、分h和cpp文件编写，h文件有哨兵

9、数据成员、成员函数的参数和返回值，类型选择合理

10、静态成员函数IsValidDate、IsLeapYear等

11、自行编写main函数，从键盘输入一个日期，显示其是否为合理日期。



## Day-03

### 默认函数

#### 不生成默认函数

```cpp
//显示删除默认构造函数

<classname>() = delete

//显示删除默认类型转换

<classname>(const char* Name, const char* PassWord)) = dalete;
 
//不允许拷贝构造和赋值对象，因为会造成两个实例用户名相同，故delete
User(const User&) = delete;
User& operator=(const User&) = delete;


```

### 枚举

#### **枚举**（*enum*）

(1)首先，请看下面的语句：

```cpp
enum enumType {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
```

1. 声明`enumType`为新的数据类型，称为**枚举**(enumeration);

2. 声明Monday、Tuesday等为符号常量，通常称之为**枚举量**，其值默认分别为0-6。

(2)接着利用新的枚举类型`enumType`声明这种类型的变量：

`enumType Weekday`就像使用基本变量类型int声明变量一样，如 *int a;*

也可以在定义枚举类型时定义枚举变量：

```cpp
enum enumType {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday}Weekday；
```

(3)不能对枚举量进行算术运算，那么枚举量能不能参与其他类型变量的运算呢？`int a;a = 1 + Monday;`这是允许的，因为编译器会自动把枚举量转换为int类型。

(4)前面讲通过定义

```cpp
enum enumType {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
```

**枚举量**Monday、Tuesday等的值默认分别为0-6

我们可以显式的设置**枚举量**的值：

```cpp
enum enumType {Monday=1, Tuesday=2, Wednesday=3, Thursday=4, Friday=5, Saturday=6, Sunday=7};
```

指定的值必须是**整数**！

(5)也可以只显式的定义一部分**枚举量**的值：

```cpp
enum enumType {Monday=1, Tuesday, Wednesday=1, Thursday, Friday, Saturday, Sunday};
```

这样Monday、Wednesday均被定义为1，则Tuesday=2，Thursday、Friday、Saturday、Sunday的值默认分别为2、3、4、5.

未被初始化的枚举值的值默认将比其前面的枚举值大1。

 还说明另外一个现象，就是枚举量的值可以相同。

#### 强类型枚举（Strongly-typed enums）



强类型枚举使用`enum class`语法来声明，如下：

```cpp
enum class Enumeration{
 VAL1,
 VAL2,
 VAL3=100,
 VAL4
};
```

这样，枚举类型时安全的，枚举值也不会被隐式转换为整数，无法和整数数值比较，比如（`Enumeration：：VAL4==10`会触发编译错误）。

 另外枚举类型所使用的类型默认为int类型，也可指定其他类型，比如：

```cpp
enum class Enum:unsigned int{VAL1,VAL2};
```

正如前面所说，强类型枚举能解决传统枚举不同枚举类下同枚举值名的问题，使用枚举类型的枚举名时，必须指明所属范围，比如：`Enum::VAL1`，而单独的`VAL1`则不再具有意义。

还有一点值得说明的是C++11中枚举类型的前置声明也是可行的，比如：

```cpp
enum class Enum;
enum class Enum1:unsigned int;
```

### 容器（vector）

#### 初始化

```cpp
vector<int> a;
//a保存int类型的对象

vector<int> a(10); 
//定义了10个整型元素的向量（尖括号中为元素类型名，它可以是任何合法的数据类型），但没有给出初值，其值是不确定的。

vector<int> a(10,1); 
//定义了10个整型元素的向量,且给出每个元素的初值为1

vector<int> a(b);
//用b向量来创建a向量，整体复制性赋值

vector<int> a(b.begin(),b.begin+3); 
//定义了a值为b中第0个到第2个（共3个）元素

int b[7]={1,2,3,4,5,9,8};
vector<int> a(b,b+7); 
//从数组中获得初值
```

#### 操作

```cpp
a.assign(b.begin(), b.begin()+3); 
//b为向量，将b的0~2个元素构成的向量赋给a

a.assign(4,2); 
//是a只含4个元素，且每个元素为2
  
a.back(); 
//返回a的最后一个元素

a.front();
//返回a的第一个元素

a[i]; 
//返回a的第i个元素，当且仅当a[i]存在
    
a.clear(); 
//清空a中的元素

a.empty(); 
//判断a是否为空，空则返回ture,不空则返回false

a.pop_back(); 
//删除a向量的最后一个元素
 
a.erase(a.begin()+1,a.begin()+3); 
//删除a中第1个（从第0个算起）到第2个元素，也就是说删除的元素从a.begin()+1算起（包括它）一直到a.begin()+         3（不包括它）

a.push_back(5); 
//在a的最后一个向量后插入一个元素，其值为5

a.insert(a.begin()+1,5); 
//在a的第1个元素（从第0个算起）的位置插入数值5，如a为1,2,3,4，插入元素后为1,5,2,3,4

a.insert(a.begin()+1,3,5); 
//在a的第1个元素（从第0个算起）的位置插入3个数，其值都为5

a.insert(a.begin()+1,b+3,b+6); 
//b为数组，在a的第1个元素（从第0个算起）的位置插入b的第3个元素到第5个元素（不包括b+6）

a.size(); 
//返回a中元素的个数；

a.capacity(); 
//返回a在内存中总共可以容纳的元素个数

a.resize(10); 
//将a的现有元素个数调至10个，多则删，少则补，其值随机

a.resize(10,2); 
//将a的现有元素个数调至10个，多则删，少则补，其值为2

a.reserve(100); 
//将a的容量（capacity）扩充至100，也就是说现在测试a.capacity();的时候返回值是100.这种操作只有在需要给a添加大量数据的时候才显得有意义，因为这将避免内存多次容量扩充操作（当a的容量不足时电脑会自动扩容，当然这必然降低性能） 

a.swap(b); 
//b为向量，将a中的元素和b中的元素进行整体性交换

a==b; 
//b为向量，向量的比较操作还有!=,>=,<=,>,<
```

#### 访问vector的几种方式

向向量a中添加元素

```cpp
1  vector<int> a;
2 for(int i=0;i<10;i++)
3 a.push_back(i);
```

从数组中选择元素向向量中添加

```cpp
int a[6]={1,2,3,4,5,6};
vector<int> b；
for(int i=1;i<=4;i++)
b.push_back(a[i]);
```

从现有向量中选择元素向向量中添加

```cpp
int a[6]={1,2,3,4,5,6};
vector<int> b;
vector<int> c(a,a+4);
for(vector<int>::iterator it=c.begin();it<c.end();it++)
b.push_back(*it);
```

也可以从文件中读取元素向向量中添加

```cpp
ifstream in("data.txt");
vector<int> a;
for(int i; in>>i)
    a.push_back(i);
```

【误区】

```cpp
vector<int> a;
for(int i=0;i<10;i++)
    a[i]=i;
//这种做法以及类似的做法都是错误的。下标只能用于获取已存在的元素，而现在的a[i]还是空的对象
```

 从向量中读取元素：通过下标方式读取

```
int a[6]={1,2,3,4,5,6};
vector<int> b(a,a+4);
for(int i=0;i<=b.size()-1;i++)
    cout<<b[i]<<" ";
```

 从向量中读取元素：通过遍历器方式读取

```
int a[6]={1,2,3,4,5,6};
vector<int> b(a,a+4);
for(vector<int>::iterator it=b.begin();it!=b.end();it++)
    cout<<*it<<" ";
```

### 内嵌类

C++嵌套类等同于内部类的概念，定义嵌套类的目的是为了隐藏信息，提高代码的抽象能力，相当与在内部为外部类提供了一种新的类型。

* **内嵌类可以访问定义在外围类（enclosing class）中的静态实例变量。外围类不可以访问嵌套类的私有成员.**

  ```cpp
  // 实现一个内嵌垃圾回收类 
  class CGarbo {
  public:
     ~CGarbo()
    };
  
  // 定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数从而释放单例对象
  static CGarbo Garbo;
  ```

* **不能从内嵌类中访问外部类的非静态成员.**

* **可以在外部通过作用域限定符调用.**

  

### for遍历

C++11增加了一个行特性foreach（Range-based for loops ，基于范围的for循环）。可以对集合、数组、初始化列逐个访问。

注意：在循环过程中，不可以对vector长度做出改变，否则迭代器会失效。

#### 范围for函数

```cpp
for ( range_declaration : range_expression)
    loop_statement           
//编译时会转换为以下代码
auto && __range = range_expression;
for (auto __begin = std::begin(range),__end = std::end(range);__begin != __end; ++__begin) {
    range_declaration = *__begin;
    loop_statement
}
```
例子

```cpp
//遍历一个vector<User*> a, 释放指向的内存

for(auto& n ： a){

if(n!=nullprt)

   delete n;

n=nullprt;

}
```

#### for each函数

循环范围：

Applies function fn to each of the elements in the range `[first,last)`.

实际意义：对范围内的对象进行fn函数操作

The behavior of this template function is equivalent to:

```cpp
template<class InputIterator, class Function>
  Function for_each(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (*first);
    ++first;
  }
  return fn;      // or, since C++11: return move(fn);
}
```

例子：

```cpp
// for_each example
#include <iostream>     // std::cout
#include <algorithm>    // std::for_each
#include <vector>       // std::vector

void myfunction (int i) {  // function:
  std::cout << ' ' << i;
}

struct myclass {           // function object type:
  void operator() (int i) {std::cout << ' ' << i;}
} myobject;

int main () {
  std::vector<int> myvector;
  myvector.push_back(10);
  myvector.push_back(20);
  myvector.push_back(30);

  std::cout << "myvector contains:";
  for_each (myvector.begin(), myvector.end(), myfunction);
  std::cout << '\n';

  // or:
  std::cout << "myvector contains:";
  for_each (myvector.begin(), myvector.end(), myobject);
  std::cout << '\n';

  return 0;
}
```

输出：

```
myvector contains: 10 20 30
myvector contains: 10 20 30 
```

trick：

```cpp
//fn处也可以使用一个匿名函数[&]
vector a = { 11, 12, 13, 14 };   
bool IsFound = false;
for_each(std::begin(a), std::end(a), [&](int p) {if(p == 11) IsFound = true;});
//代码功能为，在a中寻找是否存在11。当所有代码执行完毕后，如存在，则IsFound为true。
```



### 作业要求

* 用户类声明
  1. 枚举类定义用户类型
  2. 不允许无用户名和密码的用户创建
  3. 不允许拷贝构造和赋值对象
  4. 只允许一个管理员实例（用户名密码均为Admin）
  5. 添加任意数量普通用户（普通用户不能重名，也不能是Admin）
  6. 私有的构造函数（私有是为了保证使用者无法跳过用户名称和数量规则自行创建用户）
  7. 私有函数释放所有已经创建的用户实例（私有是因为不允许使用者自行释放，函数要在程序结束时自动被调用）
  8. 私有数据成员：用户名、密码、用户类型
  9. 私有静态成员：默认的管理员用户名和密码
  10. 私有静态成员：用户列表（vector）
  11. 私有静态嵌套类及对象：Garbo，实现析构的自动调用和释放 用户列表

## Day-04

### 括号运算符重载





### 行为类的模板



### find与find_if

#### **find:**

```cpp
using namespace std;
int main()
{
    list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    list<int>::iterator it = find(lst.begin(), lst.end(), 10); // 查找list中是否有元素“10”
    if (it != lst.end()) // 找到了
    {
        // do something 
    }
    else // 没找到
    {
        // do something
    }
    return 0;
}
```

那么，如果容器里的元素是一个类呢？例如，有list<CPerson> ，其中CPerson类定义如下：

```cpp
class CPerson
{
public:
    CPerson(void); 
    ~CPerson(void);

bool CPerson::operator==(const CPerson &rhs) const
{
    return (age == rhs.age);
}

public:
    int age; // 年龄
};
```

那么如何用find()函数进行查找呢？这时，我们需要提供一个判断两个CPerson对象“相等”的定义，find()函数才能从一个list中找到与指定的CPerson“相等”的元素。



这个“相等”的定义，是通过重载“==”操作符实现的，我们在CPerson类中添加一个方法，定义为：

```cpp
bool operator==(const CPerson &rhs) const;
      实现为：
bool CPerson::operator==(const CPerson &rhs) const
{
    return (age == rhs.age);
}
```

然后我们就可以这样查找（假设list中已经有了若干CPerson对象）了：

```cpp
list<CPerson> lst;
// 向lst中添加元素，此处省略

CPerson cp_to_find; // 要查找的对象
cp_to_find.age = 50;
list<CPerson>::iterator it = find(list.begin(), list.end(), cp_to_find); // 查找

if (it != lst.end()) // 找到了
{
}
else // 没找到
{
}
```

这样就实现了需求。

#### **find_if**

 有人说，如果我有自己定义的“相等”呢？例如，有一个list<CPerson*>，这个list中的每一个元素都是一个对象的指针，我们要在这个list中查找具有指定age的元素，找到的话就得到对象的指针。
      这时候，你不再能像上面的例子那样做，我们需要用到find_if函数，并自己指定predicate function（即find_if函数的第三个参数，请查阅STL手册）。

我们在CPerson类外部定义这样一个结构体：

```cpp
typedef struct finder_t
{
    finder_t(int n) : age(n) { } 
    bool operator()(CPerson *p) 
    { 
        return (age == p->age); 
    } 
    int age;
}finder_t;
```

然后就可以利用find_if函数来查找了：

```cpp
list<CPerson*> lst;
// 向lst中添加元素，此处省略

list<CPerson*>::iterator it = find_if(lst.begin(), lst.end(), finder_t(50)); // 查找年龄为50的人
if (it != lst.end()) // 找到了
{
    cout << "Found person with age : " << (*it)->age;
}
else // 没找到
{
    // do something
}
```





### Lambda表达式



![Lambda 表达式的结构元素的图例。](https://docs.microsoft.com/zh-cn/cpp/cpp/media/lambdaexpsyntax.png?view=msvc-160)



1. *捕获子句* (也称为 c + + 规范中的 *引导* 。 )

    `[ ]` 指示 lambda 表达式的主体不访问封闭范围中的变量。

    `[&]` 所有变量都按引用捕获

    `  [=]` 这意味着它们是通过值捕获的

   

2. *参数表* 可有可无. (也称为 *lambda 声明符*)

3. *可变规范* 可有可无.

4. *异常规范* 可有可无.

5. *尾随-返回类型* 可有可无.

6. *lambda 体*。

### 





### 类的继承与派生

**派生类声明：**

```cpp
class 派生类名：继承方式1 基类名1, 继承方式2 基类2……
{
  成员声明；
}
例如：
class Derived:public Base1, private Base2
{
public:
 Derived ();
 ~Derived ();
};
```

**派生类生成过程**

* 吸收基类成员

  （构造函数和析构函数将不被继承）

  (注：C++11对此进行了修改，允许构造函数被继承)

* 改造基类成员

* 添加新成员

**保护成员与访问控制**

* protected成员不可以从类外通过对象或对象指针访问

  (这一点与private成员相同)

* protected成员可以从本类的内部访问

  (这一点与private成员相同)

* protected成员可以从本类派生类的内部访问

  (这一点与private成员**不同**)

* 好处：既实现了数据隐藏，又方便继承，实现代码重用。

**类型兼容规则**

在需要基类对象的任何地方，都可用公有派生类对象来替代。

* 派生类的对象可以隐含转化为基类对象
* 派生类对象可以初始化基类的引用
* 派生类的指针可以隐含转换为基类的指针

**继承时的构造和析构函数**

* 构造函数：只需对新增成员初始化

  ```cpp
  派生类名::派生类名(基类所需的形参，本类成员所需的形参):基类名(参数表)//初始化列表需要指明如何调用基类构造函数
  {
   本类成员初始化赋值语句；
  }；
  ```


* 当基类中声明有缺省构造函数或未声明构造函数时，派生类构造函数可以不向基类构造函数传递参数，也可以不声明，构造派生类的对象时，基类的缺省构造函数将被调用

* 拷贝构造函数

  1. 若建立派生类对象时没有编写拷贝构造函数，编译器会生成一个隐含的拷贝构造函数，该函数先调用基类的拷贝构造函数，再为派生类新增的成员对象执行拷贝

  2. 若编写派生类的拷贝构造函数，**则需要为基类相应的拷贝构造函数传递参数**

     例如:

     ```cpp
     C::C(const C &c1): B(c1) {…}
     //由兼容规则，c1可转化为基类对象
     ```

* 析构函数
  1. 析构函数也不被继承，派生类自行声明
  2. 声明方法与一般（无继承关系时）类的析构函数相同
  3. 不需要显式地调用基类的析构函数，系统会自动隐式调用
  4. 析构函数的调用次序与构造函数相反

**同名隐藏及二义性**

* 当派生类与基类中有相同成员时：

  1. 若未强行指名，则通过派生类对象使用的是派生类中的同名成员(对于函数，仅考虑函数名，不考虑重载问题)

  2. 如要通过派生类对象访问基类中被隐藏的同名成员，应使用基类名限定

     例如：

     ```cpp
     #include <iostream>
     using namespace std;
     class Base1 	 //定义基类Base1
     {	
     public:
     	int var;
     	void fun() { cout << "Member of Base1" << endl; }
     };
     class Base2 	 //定义基类Base2
     {	
     public:
     	int var;
     	void fun() { cout << "Member of Base2" << endl; }
     };
     class Derived: public Base1, public Base2 	 //定义派生类Derived
     { 
     public:
     	int var;	//同名数据成员
     	void fun() { cout << "Member of Derived" << endl; }	//同名函数成员
     };
     
     ```

     ```cpp
     int main() 
     {
     	Derived d;
     	Derived *p = &d;
     
     	d.var = 1;	//对象名.成员名标识
     	d.fun();	//访问Derived类成员
     	
     	d.Base1::var = 2;	//作用域分辨符标识
     	d.Base1::fun();		//访问Base1基类成员
     	
     	p->Base2::var = 3;	//作用域分辨符标识
     	p->Base2::fun();	//访问Base2基类成员
     
     	return 0;
     }
     
     ```

**虚函数**

声明语法

```cpp
virtual 函数类型 函数名（形参列表）；
```

C++多态(polymorphism)是通过虚函数来实现的，虚函数允许子类重新定义成员函数，而子类重新定义父类的做法称为覆盖(override)，或者称为重写。

最常见的用法就是声明基类的指针，利用该指针指向任意一个子类对象，调用相应的虚函数，动态绑定。由于编写代码的时候并不能确定被调用的是基类的函数还是哪个派生类的函数，所以被成为“虚”函数。

如果没有使用虚函数的话，即没有利用C++多态性，则利用基类指针调用相应的函数的时候，将总被限制在基类函数本身，而无法调用到子类中被重写过的函数。

**派生类对象的内存布局**

* 单继承：基类数据在前，派生类新增数据在后

  ```cpp
  class Base 
  { … };
  class Derived: public Base 
  { … };
  Derived *pd = new Derived();
  Base *pb = pd;
  //Derived类型指针pd转换为Base类型指针时，地址不需要改变
  ```

**组合与继承**

组合：B类中存在一个A类型的内嵌对象

* 有一个（has-a）关系：表明每个B类型对象“有一个” A类型对象

* A类型对象与B类型对象是部分与整体关系

* B类型的接口不会直接作为A类型的接口

公有继承：A类是B类的公有基类

* 是一个（is-a）关系：表明每个B类型对象“是一个” A类型对象

* A类型对象与B类型对象是一般与特殊关系

* 回顾类的兼容性原则：在需要基类对象的任何地方，都可以使用公有派生类的对象来替代

* B类型对象包括A类型的全部接口

### 作业要求

1、以继承思路复现user和administrator类，重点考虑功能是如何分解到各个类、对象，以及如何复用和分离成员函数，实现代码精炼

2、为user类，增加“程序结束时自动释放所有实例”的功能

3、查阅std::ofstream，考虑如何用分治法实现多有user对象和administrator对象信息存储到文件。建议尝试编写代码。

本次作业思考为主，欢迎大家和老师助教讨论设计、实现过程中的没一点疑惑。提出自己的想法，对比老师课上实现的方法，考虑优缺点各是什么？思路有何不同。不同实现方式，是否满足泛化性(脱离具体作业要求，类仍然可以满足别人使用的需求)、合理性(类设计实现是否配合得当，这个类应不应该有，这个成员函数是谁的？静态/非静态？用户在不安你的预想使用代码是，会不会有问题？……)，正确性（C++11标准兼容，没有使用特定编译环境特有的功能，尽可能少的bug，类、对象、成员、变量、常量的类型是是否准确），可读性（类、对象、成员、变量、常量的命名是否可理解，无歧义，更接近自然语言描述，是否符合语法规范）



* admin才能创建user，



## DAY-05

### 智能指针

shared_ptr实现共享式拥有概念。多个智能指针可以指向相同对象，该对象和其相关资源会在“最后一个引用被销毁”时候释放。从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。可以通过成员函数use_count()来查看资源的所有者个数。除了可以通过new来构造，还可以通过传入auto_ptr,  unique_ptr,weak_ptr来构造。当我们调用release()时，当前指针会释放资源所有权，计数减一。当计数等于0时，资源会被释放。

shared_ptr 是为了解决 auto_ptr 在对象所有权上的局限性(auto_ptr 是独占的), 在使用引用计数的机制上提供了可以共享所有权的智能指针。

成员函数：

use_count 返回引用计数的个数

unique 返回是否是独占所有权( use_count 为 1)

swap 交换两个 shared_ptr 对象(即交换所拥有的对象)

reset 放弃内部对象的所有权或拥有对象的变更, 会引起原有对象的引用计数的减少

get 返回内部对象(指针), 由于已经重载了()方法, 因此和直接使用对象是一样的.如

cpp

```cpp
shared_ptr<int> sp(new int(1)); 
```

sp 与 sp.get()是等价的。

share_ptr的简单例子：

cpp

```cpp
int main()
{
	string *s1 = new string("s1");

	shared_ptr<string> ps1(s1);
	shared_ptr<string> ps2;
	ps2 = ps1;

	cout << ps1.use_count()<<endl;	//2
	cout<<ps2.use_count()<<endl;	//2
	cout << ps1.unique()<<endl;	//0

	string *s3 = new string("s3");
	shared_ptr<string> ps3(s3);

	cout << (ps1.get()) << endl;	//033AEB48
	cout << ps3.get() << endl;	//033B2C50
	swap(ps1, ps3);	//交换所拥有的对象
	cout << (ps1.get())<<endl;	//033B2C50
	cout << ps3.get() << endl;	//033AEB48

	cout << ps1.use_count()<<endl;	//1
	cout << ps2.use_count() << endl;	//2
	ps2 = ps1;
	cout << ps1.use_count()<<endl;	//2
	cout << ps2.use_count() << endl;	//2
	ps1.reset();	//放弃ps1的拥有权，引用计数的减少
	cout << ps1.use_count()<<endl;	//0
	cout << ps2.use_count()<<endl;	//1
}
```

### C++文件读写



* 相关的头文件：#include <fstream>

* 需要相关的类

* fstream提供三种类，实现C++对文件的操作
  1. ofstream：写操作，由ostream引申而来
  2. ifstream：读操作，由istream引申而来 
  3. fstream ：同时读写操作，由iostream引申而来 

* 文件读写的步骤：
  1. 包含的头文件：#include <fstream>
  2. 创建流
  3. 打开文件(文件和流关联)
  4. 读写 (写操作：<<,put( ), write( ) 读操作： >> , get( ),getline( ), read( ))
  5. 关闭文件：把缓冲区数据完整地写入文件， 添加文件结束标志， 切断流对象和外部文件的连接

* 文本文件的读写：

  一次性读写若干字符

  1. 使用运算符<< 和 >>进行读写

     `<<` 能实现以行为单位写入文件

     `>>`不能一行为单位读入内存,总是以空格、Tab、回车结束，而是以单词为单位

     ```cpp
     #include <fstream>  
     #include <iostream>  
     using namespace std;  
     void main()  
     { 
        ofstream OpenFile("file.txt");  
        if (OpenFile.fail())  
     　   {  
             cout<<"打开文件错误!"<<endl;  
     　　　　  exit(0);  
     　　  }  
        OpenFile<<"abc def ghi";  
     　　OpenFile.close();  
     　　system("pause");  
     
     }  
     
     ```

     运行结果：文件中写入内容:abc def ghi

     函数功能：使用>>，从文件读入一个单词

     ```cpp
     #include <fstream>  
     #include <iostream>  
     using namespace std;  
     void main()  
     {  
     　　const int len=20;  
     　　char str[len];  
          ifstream OpenFile("file.txt");  
     　　if (OpenFile.fail())  
          {  
             cout<<"打开文件错误!"<<endl;  
             exit(0);  
         }  
         OpenFile>>str;  
         cout<<str<<endl;  
         OpenFile.close();  
         system("pause");  
     }  
     ```

     运行结果：str的内容为abc，而不是abc def ghi(见空格停止)

  2. 使用运算符<<(写)和getline()进行读写

       <<：以行为单位输入文件

     ​    getline()：以行为单位 读入内存，能一次读入一行

     ​    函数原型：istream &getline( char *buffer, streamsize num );

     ​    功能：getline( )函数用于从文件读取num-1个字符到buffer(内存)中，直到下列情况发生时，读取结束:

     ​    1)：num - 1个字符已经读入

     ​    2)：碰到一个换行标志

     ​    3)：碰到一个EOF

     ```cpp
     #include <fstream>  
     #include <iostream>  
     using namespace std;  
     void main()  
     {  
     　　const int len=20;  
     　　char str[len];  
           ifstream OpenFile("file.txt");  
     　　if (OpenFile.fail())  
         {  
             cout<<"打开文件错误!"<<endl;  
             exit(0);  
         }  
         OpenFile.getline(str,20);  
         cout<<str<<endl;  
         OpenFile.close();  
         system("pause");  
     }  
     
     运行结果：str的内容为abc def ghi （一直把一行读完）
     一次读写一个字符:
     使用get( )和put( )函数
     函数声明：istream& get(char &c);
     函数功能：使用 get( )函数 把字符1输入到文件
     
     #include <fstream>  
     #include <iostream>  
     using namespace std;  
     void main()  
     {  
     　　char ch='1';  
          ofstream OpenFile("file.txt");  
     　　if (OpenFile.fail())  
         {  
             cout<<"打开文件错误!"<<endl;  
             exit(0);  
         }  
         OpenFile.put(ch);  
         OpenFile.close();  
         system("pause");  
     }  
     ```

     运行结果：把字符1写入文件

     函数功能：使用 put( )函数 把文件中第一个字符输入内存

     ```cpp
     #include <fstream>  
     #include <iostream>  
     using namespace std;  
     void main()  
     {  
     　　char ch;  
          ifstream OpenFile("file.txt");  
     　　if (OpenFile.fail())  
         {  
             cout<<"打开文件错误!"<<endl;  
             exit(0);  
         }  
         OpenFile.get(ch);  
         cout<<ch;  
         OpenFile.close();  
         system("pause");  
     
     }  
     ```

     运行结果：把字符1从文件中读到ch（内存）中

## Later

### C++输出间隔控制与补齐

有如下4个语句：

```cpp
① cout<<'A'<<setfill('*')<<left<<setw(7)<<'B'<<endl;
② cout<<setfill('*')<<left<<setw(7)<<'A'<<'B'<<endl;
③ cout<<'A'<<setfill('*')<<right<<setw(7)<<'B'<<endl;
④ cout<<setfill('*')<<right<<setw(7)<<'A'<<'B'<<endl;
```

其中执行时显示 A******B 的是
A) ①和③
B) ①和④
C) ②和③
D) ②和④

1、setw后面紧跟的内容有效
2、setw默认右对齐，就是从右边开始填，比如C,D，
如果指明从左边开始填写left,则setw后面的内容先左对齐，然后是setfill的内容补齐setw括号中制定的宽度

四句话结果

```
    AB******
    A******B
    A******B
    ******AB
```

























