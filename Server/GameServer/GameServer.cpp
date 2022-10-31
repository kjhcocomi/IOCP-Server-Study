#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

vector<int32> v;

// Mutual Exclusive (상호배타적)
mutex m;

// RAII
template<typename T> 
class LockGuard { // == std::lock_guard
public:
	LockGuard(T& m) {
		_mutex = &m;
		_mutex->lock();
	}
	~LockGuard() {
		_mutex->unlock();
	}
private:
	T* _mutex;
};

void Push() {
	for (int32 i = 0; i < 10000; i++) {
		//m.lock();
		std::lock_guard<std::mutex> lockGuard(m);
		v.push_back(i);
		//m.unlock();
	}
}



int main()
{
	std:: thread t1(Push);
	std:: thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size();
}