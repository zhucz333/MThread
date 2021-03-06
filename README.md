## 1 MThread库概述
<br> MThread（Multi-Thread Management）库是对C++标准库（C++11后）中的`std::thread`和`std::function`进行再封装，特点是接口简单、实现紧凑、使用方便。 </br>
<br> 和使用标准库中的的std::thread库相比，本库的主要贡献是解除了线程和线程函数的绑定关系，即在使用标准库中的std::thread创建线程时，需要指定线程函数，并且在线程结束前，不可以绑定别的线程函数。使用本库后，可以动态创建异步线程函数并Post/Dispatch到本线程组中，由线程组来调用异步线程函数，创建函数的线程和执行函数的线程是相互隔离的，是生产者和消费者的关系。</br>
<br> 同时，本库还实现了异步线程函数的`优先级`机制和线程函数的`串行化`机制。其中，线程函数的优先级机制中，优先级高的线程函数优先执行，可以满足特定的应用场景需求；线程函数的串行化机制中，可以提供线程函数的串行化执行，同一时间只有一个线程函数可以被执行。</br>
## 2 MThread库主要功能及说明
  <br> 2.1 线程组创建、销毁</br>
  <br> 通过`MThread::Start(int nThreadNum)`创建并运行nThreadNum个线程的线程组，通过MThread::Stop()结束线程组运行；</br>
  <br> 2.2 线程异步函数的创建和执行</br>
  <br> 通过`MTread::Post(std::function)`和`MThread::Dispatch(std::function)`创建线程函数并执行，其中func通过`std::bind()`产生，返回值为void的线程函数都可以被正确执行；</br>
  <br> 2.3 线程异步函数的优先级管理</br>
  <br> 通过Post创建的异步函数优先级最低，按照`FIFO`的顺序执行，通过Dispatch创建的异步函数优先级高于Post创建的异步函数，会被优先执行，Dispatch创建的线程函数之间，按照`FILO`的顺序执行；</br>
  <br> 2.4 线程异步函数的串行化管理</br>
  <br> 线程函数之间如果需要串行化执行，使用Strand即可，Strand可以保证同一时间只有其中的一个异步函数被执行，但是不保证`异步函数的执行顺序`。</br>

## 3 MThread库的编译及使用
### 3.1 编译
<br>MThread库提供windows和Linux平台的生成方法，具体如下： </br>
<br>Linux平台：cd MThread/src && make && make test； </br>
<br>Windows平台：直接打开MThread\vs2017\MThread\MThread.sln工程文件即可编译lib和测试样例； </br>
<br>编译的lib库文件在MThread/lib中，头文件在MThread/include中，测试样例在MThread/bin中； </br>
### 3.2 使用
<br>Linux平台：</br>
<br>源代码中#include "MThread.h" 和 #include "Strand.h" </br>
<br>编译时 -lMThread即可 ；</br>
<br />
<br>Windows平台：</br>
<br>源代码中#include "MThread.h" 和 #include "Strand.h" </br>
<br>编译时静态链接MThread.lib即可。 </br>
### 3.3 Example
<br>源码：<br />
```cpp
class A
{
public:
    void print() {
        printf("printf test!\n");
        printf("printf test! end!\n");
    }

    void printi(int i) {
	printf("printf int test %d\n", i);
	sleep(1);
	printf("printf int test %d ing\n", i);
	sleep(1);
	printf("printf int test %d end\n", i);
    }
} ;  
```
```c
int main()  
{  
    MThread threads;  
    threads.Start(3);  
    Strand strand(threads);  
    A a;  

    threads.Post(std::bind(&A::print, &a));  
    threads.Post(std::bind(&A::printi, &a, 1));  
    threads.Post(std::bind(&A::printi, &a, 2));  
    threads.Post(std::bind(&A::printi, &a, 3));  
    threads.Dispatch(std::bind(&A::printi, &a, 4));  

    strand.Post(std::bind(&A::print, &a));  
    strand.Post(std::bind(&A::printi, &a, 5));  
    strand.Post(std::bind(&A::printi, &a, 6));  
    strand.Post(std::bind(&A::printi, &a, 7));  
    strand.Post(std::bind(&A::printi, &a, 8));  
    strand.Dispatch(std::bind(&A::printi, &a, 9));  
    
    getchar();  
    threads.Stop();  
    return 0;  
}  
```
<br><br />
