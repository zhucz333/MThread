## 1 MThread库概述
<br> MThread（Multi-Thread Management）库是对C++标准库（C++11后）中的std::thread和std::function进行再封装，实现线程相关操作的简单和易用。 </br>
<br> 和使用标准库中的的std::thread库相比，本库的主要贡献是解除了线程和线程函数的绑定关系，即在使用标准库中的std::thread创建线程时，需要指定线程函数，并且在线程结束前，不可以绑定别的线程函数。使用本库后，可以动态创建异步线程函数并Post/Dispatch到本线程组中，由线程组来调用异步线程函数，创建函数的线程和执行函数的线程是相互隔离的，是生产者和消费者的关系。</br>
<br> 同时，本库还实现了异步线程函数的优先级机制和线程函数的串行化机制。其中，线程函数的优先级机制中，优先级高的线程函数优先执行，可以满足特定的应用场景需求；线程函数的串行化机制中，可以提供线程函数的串行化执行，同一时间只有一个线程函数可以被执行。</br>
<br> 在功能上，MThread库和boost::asio::ioservice类似，相比而言MThread库优势是接口更简单、实现更紧凑、使用更方便。</br>

## 2 MThread库主要功能及说明
  ### 2.1 线程组创建、销毁
  <br> 通过MThread::Start(int nThreadNum)创建并运行nThreadNum个线程的线程组，通过MThread::Stop()结束线程组运行；</br>
  ### 2.2 线程异步函数的创建和执行
  <br> 通过MTread::Post(std::function)和MThread::Dispatch(std::function)创建线程函数并执行，其中func通过std::bind产生，返回值为void的线程函数都可以被正确执行；</br>
  ### 2.3 线程异步函数的优先级管理
  <br> 通过Post创建的异步函数优先级最低，按照FIFO的顺序执行，通过Dispatch创建的异步函数优先级高于Post创建的异步函数，会被优先执行，Dispatch创建的线程函数之间，按照FILO的顺序执行；</br>
  ### 2.4 线程异步函数的串行化管理
  <br> 线程函数之间如果需要串行化执行，使用Strand即可，Strand可以保证同一时间只有其中的一个异步函数被执行，但是不保证异步函数的执行顺序。</br>

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
<br>*创建线程函数print() printi()：</br>
<br>
class A  
{  
public:  
    void print() {  
        printf("printf test!\n");  
        printf("printf test! end!\n");  
    }  

    void printi(int i) {  
	printf("printf int test %d\n", i);  
#ifdef _WIN32  
	Sleep(1000);  
#else  
	sleep(1);  
#endif // _WIN32  
	printf("printf int test %d ing\n", i);  
#ifdef _WIN32  
	Sleep(1000);  
#else  
	sleep(1);  
#endif // _WIN32  
	printf("printf int test %d end\n", i);  
    }  
} ;  
<br />
<br>
*创建线程组：
    MThread threads;  
    threads.Start(3);  
    Strand strand(threads);  
<br />
<br>
*投递函数到线程组中：
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
    
<br />
