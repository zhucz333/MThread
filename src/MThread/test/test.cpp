#include "MThread.h"
#include "Strand.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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
