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

	/// <summary>�R���e�i���󂩂ǂ����𔻒肷��</summary>
	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.empty();
	}

	/// <summary>�R���e�i���̗v�f����Ԃ�</summary>
	size_t size() const
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.size();
	}

	/// <summary>�擪�v�f�ւ̎Q�Ƃ��擾����</summary>
	reference front()
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.front();
	}

	/// <summary>�擪�v�f�ւ̎Q�Ƃ��擾����(const��)</summary>
	const reference front() const
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_container.front();
	}

	/// <summary>�����ɗv�f��ǉ�����</summary>
	void push(const T& x)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_container.push_back(x);
	}

	/// <summary>�擪�ɗv�f��ǉ�����(���[�u��)</summary>
	void push(T&& y)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_container.push_back(std::forward<T>(y));
	}

	/// <summary>�擪�ɗv�f��ǉ�����(emplace��)</summary>
	template <class... Args>
	void emplace(Args&&... args)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_container.emplace_back(args ...);
	}

	/// <summary>�擪�v�f���폜����</summary>
	/// <remarks>
	/// ��̏�ԂŎ��s����Ɨ�O�𓊂���
	/// </remarks>
	void pop()
	{
		if (empty()) {
			throw "empty";
		}
		m_container.pop_front();
	}
};
