#include <deque>
#include <mutex>

template<typename T, typename Container = std::deque<T>>
class ThreadSafeQueue
{
	Container m_container;
	mutable std::mutex m_mtx;

public:
	using reference = T&;
	using const_reference = const T&;

	/// <summary>コンテナが空かどうかを判定する</summary>
	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.empty();
	}

	/// <summary>コンテナ内の要素数を返す</summary>
	size_t size() const
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.size();
	}

	/// <summary>先頭要素への参照を取得する</summary>
	reference front()
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.front();
	}

	/// <summary>先頭要素への参照を取得する(const版)</summary>
	const reference front() const
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.front();
	}

	/// <summary>末尾に要素を追加する</summary>
	void push(const T& x)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_container.push_back(x);
	}

	/// <summary>先頭に要素を追加する(ムーブ版)</summary>
	void push(T&& y)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_container.push_back(std::forward<T>(y));
	}

	/// <summary>先頭に要素を追加する(emplace版)</summary>
	template <class... Args>
	void emplace(Args&&... args)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_container.emplace_back(args ...);
	}

	/// <summary>先頭要素を削除する</summary>
	/// <remarks>
	/// 空の状態で実行すると例外を投げる
	/// </remarks>
	void pop()
	{
		if (empty()) {
			throw "empty";
		}
		m_container.pop_front();
	}
};
