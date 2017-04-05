#pragma once
#include <functional>

/// 2つの入力引数を受け取って結果を返さないオペレーションを表します。
/// @tparam T オペレーションの第1引数の型
/// @tparam U オペレーションの第2引数の型
/// @note Java8にある関数インタフェースをC++で実装してみたもの
template<typename T, typename U>
class BiConsumer
{
	std::function<void(const T&, const U&)> m_func;

public:
	BiConsumer() = delete;

	explicit BiConsumer(std::function<void(const T&, const U&)> f)
		: m_func(f)
	{
	}

	void operator()(const T& t, const U& u)
	{
		m_func(t, u);
	}
};
