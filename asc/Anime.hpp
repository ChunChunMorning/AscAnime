# pragma once
# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	/// <summary>
	/// �p���p������̂悤�ȃA�j���[�V����
	/// </summary>
	class Anime
	{

	private:

		Texture m_texture;

		size_t m_size;

		Array<int32> m_duration;

		Stopwatch m_stopwatch;

		int32 m_length;

		bool m_isLoop;

		uint32 index() const
		{
			auto ms = m_isLoop ?
				m_stopwatch.ms() % m_length :
				Min(m_stopwatch.ms(), m_length);
			auto currentIndex = 0;

			while (ms > m_duration[currentIndex])
			{
				ms -= m_duration[currentIndex];
				currentIndex++;
			}

			return currentIndex;
		}

	public:

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^
		/// </summary>
		Anime() = default;

		/// <summary>
		/// s3d::Texture����asc::Anime���쐬���܂��B
		/// </summary>
		/// <param name="texture">
		/// �e�N�X�`��
		/// </param>
		/// <param name="size">
		/// �e�N�X�`���Ɋ܂܂��R�}��
		/// </param>
		/// <param name="duration">
		/// 1�R�}�̕`�掞��[�~���b]
		/// </param>
		/// <param name="isLoop">
		/// �A�j���[�V���������[�v������ꍇ�� true
		/// </param>
		/// <param name="startImmediately">
		/// �����ɃA�j���[�V�������J�n����ꍇ�� true
		/// </param>
		Anime(const Texture& texture, size_t size, int32 duration, bool isLoop = true, bool startImmediately = true) :
			m_texture(texture),
			m_size(size),
			m_duration(size, duration),
			m_length(size * duration),
			m_isLoop(isLoop)
		{
			if (startImmediately)
				m_stopwatch.start();
		}

		/// <summary>
		/// s3d::Texture����asc::Anime���쐬���܂��B
		/// </summary>
		/// <param name="texture">
		/// �e�N�X�`��
		/// </param>
		/// <param name="size">
		/// �e�N�X�`���Ɋ܂܂��R�}��
		/// </param>
		/// <param name="duration">
		/// �e�R�}�̕`�掞��[�~���b]
		/// </param>
		/// <param name="isLoop">
		/// �A�j���[�V���������[�v������ꍇ�� true
		/// </param>
		/// <param name="startImmediately">
		/// �����ɃA�j���[�V�������J�n����ꍇ�� true
		/// </param>
		Anime(const Texture& texture, size_t size, const Array<int32>& duration, bool isLoop = true, bool startImmediately = true) :
			m_texture(texture),
			m_size(size),
			m_duration(duration),
			m_length(0),
			m_isLoop(isLoop)
		{
			for (const auto& d : duration)
				m_length += d;

			if(startImmediately)
				m_stopwatch.start();
		}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~Anime() = default;

		/// <summary>
		/// 1�R�}�̕��i�s�N�Z���j
		/// </summary>
		__declspec(property(get = _get_width)) uint32 width;

		/// <summary>
		/// 1�R�}�̍����i�s�N�Z���j
		/// </summary>
		__declspec(property(get = _get_height)) uint32 height;

		/// <summary>
		/// �����̃e�N�X�`���������[�X���܂��B
		/// </summary>
		/// <remarks>
		/// �v���O�����̂ق��̏ꏊ�œ����e�N�X�`�����g���Ă��Ȃ��ꍇ�A�e�N�X�`���̃�������������܂��B
		/// </remarks>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void release() { m_texture.release(); }

		/// <summary>
		/// �e�N�X�`������ł͂Ȃ�����Ԃ��܂��B
		/// </summary>
		/// <returns>
		/// �e�N�X�`������ł͂Ȃ��ꍇ true, ����ȊO�̏ꍇ�� false
		/// </returns>
		explicit operator bool() const { return !isEmpty(); }

		/// <summary>
		/// �����̃e�N�X�`���n���h���� ID �������܂��B
		/// </summary>
		Texture::IDType id() const { return m_texture.id(); };

		/// <summary>
		/// �����̃e�N�X�`�����󂩂ǂ����������܂��B
		/// </summary>
		/// <returns>
		/// �e�N�X�`������ł͂Ȃ��ꍇ true, ����ȊO�̏ꍇ�� false
		/// </returns>
		bool isEmpty() const { return m_texture.isEmpty(); };

		/// <summary>
		/// �A�j���[�V�������J�n���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void start() { m_stopwatch.start(); }

		/// <summary>
		/// �A�j���[�V���������쒆�ł��邩�������܂��B
		/// </summary>
		/// <remarks>
		/// �A�j���[�V�������J�n����Ă���A�܂��͊J�n��ꎞ��~���ł���ꍇ true, ����ȊO�̏ꍇ�� false
		/// </remarks>
		bool isActive() const noexcept { return m_stopwatch.isRunning(); }

		/// <summary>
		/// �A�j���[�V�������ꎞ��~���ł��邩�������܂��B
		/// </summary>
		/// <remarks>
		/// �A�j���[�V�������J�n��ꎞ��~���ł���ꍇ true, ����ȊO�̏ꍇ�� false
		/// </remarks>
		bool isPaused() const noexcept { return m_stopwatch.isPaused(); }

		/// <summary>
		/// �A�j���[�V�������ꎞ��~���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void pause() { m_stopwatch.pause(); }

		/// <summary>
		/// �A�j���[�V�������ꎞ��~���ł���ꍇ�A�ĊJ���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void resume() { m_stopwatch.resume(); }

		/// <summary>
		/// �A�j���[�V�������~���A������ԂɃ��Z�b�g���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void reset() noexcept { m_stopwatch.reset(); }

		/// <summary>
		/// ������ԂɃ��Z�b�g���āA�A�j���[�V�������J�n���܂��B
		/// </summary>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void restart() { m_stopwatch.restart(); }

		/// <summary>
		/// �P�R�}�̕`�掞�Ԃ�ݒ肵�܂��B
		/// </summary>
		/// <param name="duration">
		/// 1�R�}�̕`�掞��[�~���b]
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void setDuration(int32 duration)
		{
			m_duration = Array<int32>(m_size, duration);
			m_length = m_size * duration;
		}

		/// <summary>
		/// �A�j���[�V�����̌o�ߎ��Ԃ�ύX���܂��B
		/// </summary>
		/// <param name="time">
		/// �V�����ݒ肷��o�ߎ���[�~���b]
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void set(int32 time) { m_stopwatch.set(MicrosecondsF(time)); }

		/// <summary>
		/// �e�R�}�̕`�掞�Ԃ�ݒ肵�܂��B
		/// </summary>
		/// <param name="duration">
		/// �e�R�}�̕`�掞��[�~���b]
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void setDuration(const Array<int32>& duration)
		{
			m_duration = duration;

			m_length = 0;
			for (const auto& d : duration)
				m_length += d;
		}

		/// <summary>
		/// �`�悷��TextureRegion���擾���܂��B
		/// </summary>
		/// <returns>
		/// �`�悷��TextureRegion
		/// </returns>
		const TextureRegion get() const
		{
			return m_texture.uv(static_cast<double>(index()) / m_size, 0.0, 1.0 / m_size, 1.0);
		}

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Color& diffuse = Palette::White) const
		{
			return get().draw(diffuse);
		}

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(double x, double y, const Color& diffuse = Palette::White) const
		{
			return get().draw(x, y, diffuse);
		}

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Vec2& pos, const Color& diffuse = Palette::White) const
		{
			return get().draw(pos, diffuse);
		}

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(double x, double y, const Color& diffuse = Palette::White) const
		{
			return get().drawAt(x, y, diffuse);
		}

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const
		{
			return get().drawAt(pos, diffuse);
		}

		/// <summary>
		/// s3d::Texture::operator ()
		/// </summary>
		const TextureRegion operator ()(double x, double y, double w, double h) const
		{
			return m_texture(index() * width + x, y, w, h);
		}

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(double u, double v, double w, double h) const
		{
			return m_texture.uv((index() + u) / m_size, v, w / m_size, h);
		}

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(const RectF& rect) const
		{
			return m_texture.uv(rect.movedBy(index() * width, 0.0));
		}

		/// <summary>
		/// s3d::Texture::mirror
		/// </summary>
		const TextureRegion mirrored() const
		{
			return get().mirrored();
		}

		/// <summary>
		/// s3d::Texture::flip
		/// </summary>
		const TextureRegion flipped() const
		{
			return get().flipped();
		}

		/// <summary>
		/// s3d::Texture::scaling
		/// </summary>
		const TextureRegion scaled(double scaling) const
		{
			return get().scaled(scaling);
		}

		/// <summary>
		/// s3d::Texture::scaling
		/// </summary>
		const TextureRegion scaled(double xScaling, double yScaling) const
		{
			return get().scaled(xScaling, yScaling);
		}

		/// <summary>
		/// s3d::Texture::scaling
		/// </summary>
		const TextureRegion scaled(const Vec2& scaling) const
		{
			return get().scaled(scaling);
		}

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resized(double width, double height) const
		{
			return get().resized(width, height);
		}

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resized(const Vec2& size) const
		{
			return get().resized(size);
		}

		/// <summary>
		/// s3d::Texture::rotate
		/// </summary>
		const TexturedQuad rotated(double radian) const
		{
			return get().rotated(radian);
		}

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotatedAt(double x, double y, double radian) const
		{
			return get().rotatedAt(x, y, radian);
		}

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotatedAt(const Vec2& pos, double radian) const
		{
			return get().rotatedAt(pos, radian);
		}

		uint32 _get_width() const { return m_texture.width() / static_cast<uint32>(m_size); }

		uint32 _get_height() const { return m_texture.height(); }
	};
}
