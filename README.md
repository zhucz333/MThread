# MThread库概述
MThread（Multi-Thread Management）库是对原生std::thread和std::function进行再封装，实现线程相关操作的简单和易用，本库的主要特点包括异步线程函数的创建和执行，异步函数的执行优先级机制，异步函数的串行化机制。

# MThread库主要功能及使用说明
主要功能包括： 
  # 1）线程组创建、销毁
  通过MThread::Start(int nThreadNum)创建并运行线程组，通过MThread::Stop()结束线程组运行；
  # 2）线程异步函数的创建和执行
  通过MTread::Post(std::function<> func)和MThread::Dispatch(std::function<> func)创建线程函数并执行，其中func通过std::bind产生，返回值为void的线程函数都可以被正确执行；
  # 3）线程异步函数的优先级管理
  通过Post创建的异步函数优先级最低，按照FIFO的顺序执行，通过Dispatch创建的异步函数优先级高于Post创建的异步函数，会被优先执行，Dispatch创建的线程函数之间，按照FILO的顺序执行；
  # 4）线程异步函数的串行化管理
  线程函数之间如果需要串行化执行，使用Strand即可，Strand可以保证同一时间只有其中的一个异步函数被执行。
