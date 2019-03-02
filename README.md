## MThread库概述
<br> MThread（Multi-Thread Management）库是对C++标准库（C++11后）中的std::thread和std::function进行再封装，实现线程相关操作的简单和易用。 </br>
<br> 和使用标准库中的的std::thread库相比，本库的主要贡献是解除了线程和线程函数的静态绑定关系，即在使用标准库中的std::thread创建线程时，需要指定线程函数，并且在线程结束前，不可以绑定别的线程函数。使用本库后，可以动态创建异步线程函数并Post到本线程组中，由线程组来调用线程函数，增强了系统实现的灵活性。</br>
<br> 同时，本库还实现了异步线程函数的优先级机制和线程函数的串行化机制。其中，线程函数的优先级机制中，优先级高的线程函数优先执行，可以满足特定的应用场景需求；线程函数的串行化机制中，可以提供线程函数的串行化执行，同一时间只有一个线程函数可以被执行。</br>

## MThread库主要功能及说明
  ### 1）线程组创建、销毁
  <br> 通过MThread::Start(int nThreadNum)创建并运行nThreadNum个线程的线程组，通过MThread::Stop()结束线程组运行；</br>
  ### 2）线程异步函数的创建和执行
  <br> 通过MTread::Post(std::function)和MThread::Dispatch(std::function)创建线程函数并执行，其中func通过std::bind产生，返回值为void的线程函数都可以被正确执行；</br>
  ### 3）线程异步函数的优先级管理
  <br> 通过Post创建的异步函数优先级最低，按照FIFO的顺序执行，通过Dispatch创建的异步函数优先级高于Post创建的异步函数，会被优先执行，Dispatch创建的线程函数之间，按照FILO的顺序执行；</br>
  ### 4）线程异步函数的串行化管理
  <br> 线程函数之间如果需要串行化执行，使用Strand即可，Strand可以保证同一时间只有其中的一个异步函数被执行，但是不保证异步函数的执行顺序。</br>

## MThread库的编译及使用
MThread库提供windows和Linux平台的生成方法，
