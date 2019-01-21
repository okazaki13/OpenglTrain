#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx_; // 排他制御用ミューテックス
uint32_t count_;

void add_count()
{
	// count_を加算する前にミューテックスを取得する
	std::lock_guard<std::mutex> lock(mtx_);
	++count_;
}

void ThreadA()
{
	for (int i = 0; i<100000; ++i) {
		add_count();
	}
}

void HapticLoopCalculation() {
	std::thread haptic_calculation(ThreadA);

	haptic_calculation.join();
}