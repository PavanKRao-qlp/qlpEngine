#pragma once
#include <thread>
#include <future>
#include <condition_variable>
#include <future>
#include <vector>
#include <map>
#include <queue>

template <class T>
class ThreadSafeQueue
{
public:
	inline ThreadSafeQueue<T>();
	inline ~ThreadSafeQueue() {};
	void TryEmpty();
	T TryPop();
	bool TryPush(T);
	int GetSize();

private:
	std::queue<T> mQueue;
	std::mutex mMutex;
};

template<class T>
inline ThreadSafeQueue<T>::ThreadSafeQueue()
{
}

template<class T>
inline void ThreadSafeQueue<T>::TryEmpty()
{
	std::unique_lock<std::mutex> lock(mMutex);
	mQueue.empty();
}

template<class T>
inline T ThreadSafeQueue<T>::TryPop()
{
	std::unique_lock<std::mutex> lock(mMutex);
	if (!mQueue.empty()) {
		T element = mQueue.front();
		mQueue.pop();
		return element;
	}
	return nullptr;
}

template<class T>
inline bool ThreadSafeQueue<T>::TryPush(T element)
{
	std::unique_lock<std::mutex> lock(mMutex);
	mQueue.push(element);
	return false;
}

template<class T>
inline int ThreadSafeQueue<T>::GetSize()
{
	std::unique_lock<std::mutex> lock(mMutex);
	return mQueue.size();
}



class SimpleThreadPool
{
public:

	inline SimpleThreadPool(size_t noOfthread_) : noOfThreads(noOfthread_), mKillAllJobs(false)
	{
		for (unsigned int i = 0; i < noOfThreads; i++)
		{
			workerThreads.emplace_back(std::thread(&SimpleThreadPool::ConsumeTasks, this));
		}
	}

	inline ~SimpleThreadPool()
	{
		KillThreads();
		for (size_t i = 0; i < workerThreads.size(); i++)
		{
			if (workerThreads[i].joinable()) {
				auto id = workerThreads[i].get_id();
				workerThreads[i].join();
			}
		}
		workerThreads.clear();
	}

private:
	unsigned int noOfThreads = 15;
	std::vector<std::thread> workerThreads;
	ThreadSafeQueue<std::function<void()>> mTasks;
	std::atomic_bool mKillAllJobs = false;
	std::mutex mMutex;
	std::condition_variable mCond;

	inline void ConsumeTasks() {
		while (!mKillAllJobs)
		{
			std::unique_lock<std::mutex> lock(mMutex);
			mCond.wait(lock, [&]() { return mTasks.GetSize() > 0 || mKillAllJobs; });
			if (mKillAllJobs) {
				break;
			}
			if (mTasks.GetSize() > 0) {
				auto  task = mTasks.TryPop();
				task();
			}
		}
	}

public:
	template<typename F, class... Args>
	inline std::future<typename std::result_of<F(Args...)>::type> SumbitTask(F func, Args... args) {
		using returnType = typename std::result_of<F(Args...)>::type;
		auto taskPtr = std::make_shared<std::packaged_task<returnType()>>(std::bind(func, args...));
		auto co = [taskPtr]() { (*taskPtr)();  };
		mTasks.TryPush(co);
		mCond.notify_one();
		return  (*taskPtr).get_future();
	}

	inline void KillThreads() {
		mKillAllJobs = true;
		mCond.notify_all();
	}
}; 
