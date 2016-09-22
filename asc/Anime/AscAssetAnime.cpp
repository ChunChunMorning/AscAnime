# include "AssetAnime.hpp"

using namespace asc;

AnimeAsset::AnimeAsset() = default;

AnimeAsset::AnimeAsset(const TextureAssetName& name, size_t size, int32 duration) :
	m_name(name),
	m_size(size),
	m_duration(size, duration),
	m_index(0) {}

AnimeAsset::AnimeAsset(const TextureAssetName& name, size_t size, const Array<int32>& duration) :
	m_name(name),
	m_size(size),
	m_duration(duration),
	m_index(0) {}

AnimeAsset::~AnimeAsset() = default;

void AnimeAsset::reset() noexcept
{
	m_index = 0;
	m_stopwatch.reset();
}

void AnimeAsset::restart()
{
	m_index = 0;
	m_stopwatch.restart();
}

void AnimeAsset::setDuration(int32 duration)
{
	m_duration = Array<int32>(m_size, duration);
}

void AnimeAsset::setDuration(const Array<int32>& duration)
{
	m_duration = duration;
}

void AnimeAsset::jump(int index, const MillisecondsF& time)
{
	m_index = index;
	m_stopwatch.set(time);
}

void AnimeAsset::update()
{
	auto ms = m_stopwatch.ms();

	while (ms > m_duration[m_index])
	{
		ms -= m_duration[m_index];
		m_index >= m_size - 1 ? m_index = 0 : m_index++;
	}

	m_stopwatch.set(MicrosecondsF(ms * 1000));
}

const TextureRegion AnimeAsset::get() const
{
	return TextureAsset(m_name).uv(static_cast<double>(m_index) / m_size, 0.0, 1.0 / m_size, 1.0);
}
