#pragma once
#include <functional>

/// 2�̓��͈������󂯎���Č��ʂ�Ԃ��Ȃ��I�y���[�V������\���܂��B
/// @tparam T �I�y���[�V�����̑�1�����̌^
/// @tparam U �I�y���[�V�����̑�2�����̌^
/// @note Java8�ɂ���֐��C���^�t�F�[�X��C++�Ŏ������Ă݂�����
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
