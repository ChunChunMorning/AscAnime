# include "AscAnime.hpp"

using namespace asc;

Anime::Anime() {}

Anime::Anime(const Texture& texture, unsigned size, unsigned count) :
	m_texture(texture),
	m_size(size),
	m_frame(size, count),
	m_index(0),
	m_count(0) {}

Anime::Anime(const Texture& texture, unsigned size, const Array<unsigned>& frame) :
	m_texture(texture),
	m_size(size),
	m_frame(frame),
	m_index(0),
	m_count(0) {}

Anime::operator bool() const
{
	return static_cast<bool>(m_texture);
}

const Texture& Anime::texture() const
{
	return m_texture;
}

inline double Anime::width() const
{
	return m_texture.width / m_size;
}

inline double Anime::height() const
{
	return m_texture.height;
}

inline unsigned Anime::size() const
{
	return m_size;
}

inline unsigned Anime::index() const
{
	return m_index;
}

inline unsigned Anime::count() const
{
	return m_count;
}

void Anime::setFrame(unsigned count)
{
	m_frame = Array<unsigned>(m_size, count);
}

void Anime::setFrame(const Array<unsigned>& frame)
{
#ifdef _DEBUG
	if (frame.size() != m_size)
	{
		LOG(L"asc::Anime frameの枚数がsizeと一致しません。");
	}
#endif
	m_frame = frame;
}

void Anime::update()
{
	while (m_count >= m_frame[m_index])
	{
		++m_index;
		m_count = 0;

		if (m_index >= m_size)
		{
			m_index = 0;
		}
	}

	++m_count;
}

void Anime::jump(unsigned index, unsigned count)
{
#ifdef _DEBUG
	if (index >= m_size)
	{
		LOG(L"asc::Anime jump関数で存在しないindexにアクセスしました。");
	}
#endif
	m_index = index;
	m_count = count;
}

const TextureRegion Anime::get() const
{
	return m_texture.uv(static_cast<double>(m_index) / m_size, 0.0, 1.0 / m_size, 1.0);
}

const RectF Anime::draw(const Color& diffuse) const
{
	return get().draw(diffuse);
}

const RectF Anime::draw(double x, double y, const Color& diffuse) const
{
	return get().draw(x, y, diffuse);
}

const RectF Anime::draw(const Vec2& pos, const Color& diffuse) const
{
	return get().draw(pos, diffuse);
}

const RectF Anime::drawAt(double x, double y, const Color& diffuse) const
{
	return get().drawAt(x, y, diffuse);
}

const RectF Anime::drawAt(const Vec2& pos, const Color& diffuse) const
{
	return get().draw(pos, diffuse);
}

const TextureRegion Anime::operator ()(double x, double y, double w, double h) const
{
	return m_texture(m_index * width() + x, y, w, h);
}

const TextureRegion Anime::operator ()(const RectF& rect) const
{
	return m_texture(m_index * width() + rect.x, rect.y, rect.w, rect.h);
}

const TextureRegion Anime::uv(double u, double v, double w, double h) const
{
	return m_texture.uv((m_index + u) / m_size, v, w / m_size, h);
}

const TextureRegion Anime::uv(const RectF& rect) const
{
	return m_texture.uv(rect.movedBy(m_index * width(), 0.0));
}

const TextureRegion Anime::mirror() const
{
	return get().mirror();
}

const TextureRegion Anime::flip() const
{
	return get().flip();
}

const TextureRegion Anime::scale(double scaling) const
{
	return get().scale(scaling);
}

const TextureRegion Anime::scale(double xScaling, double yScaling) const
{
	return get().scale(xScaling, yScaling);
}

const TextureRegion Anime::scale(const Vec2& scaling) const
{
	return get().scale(scaling);
}

const TextureRegion Anime::resize(double width, double height) const
{
	return get().resize(width, height);
}

const TextureRegion Anime::resize(const Vec2& size) const
{
	return get().resize(size);
}

const TexturedQuad Anime::rotate(double radian) const
{
	return get().rotate(radian);
}

const TexturedQuad Anime::rotateAt(double x, double y, double radian) const
{
	return get().rotateAt(x, y, radian);
}

const TexturedQuad Anime::rotateAt(const Vec2& pos, double radian) const
{
	return get().rotateAt(pos, radian);
}
