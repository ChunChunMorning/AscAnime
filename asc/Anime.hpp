# pragma once
# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	/// <summary>
	/// パラパラ漫画のようなアニメーション
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
		/// デフォルトコンストラクタ
		/// </summary>
		Anime() = default;

		/// <summary>
		/// s3d::Textureからasc::Animeを作成します。
		/// </summary>
		/// <param name="texture">
		/// テクスチャ
		/// </param>
		/// <param name="size">
		/// テクスチャに含まれるコマ数
		/// </param>
		/// <param name="duration">
		/// 1コマの描画時間[ミリ秒]
		/// </param>
		/// <param name="isLoop">
		/// アニメーションをループさせる場合は true
		/// </param>
		/// <param name="startImmediately">
		/// 即座にアニメーションを開始する場合は true
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
		/// s3d::Textureからasc::Animeを作成します。
		/// </summary>
		/// <param name="texture">
		/// テクスチャ
		/// </param>
		/// <param name="size">
		/// テクスチャに含まれるコマ数
		/// </param>
		/// <param name="duration">
		/// 各コマの描画時間[ミリ秒]
		/// </param>
		/// <param name="isLoop">
		/// アニメーションをループさせる場合は true
		/// </param>
		/// <param name="startImmediately">
		/// 即座にアニメーションを開始する場合は true
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
		/// デストラクタ
		/// </summary>
		virtual ~Anime() = default;

		/// <summary>
		/// 1コマの幅（ピクセル）
		/// </summary>
		__declspec(property(get = _get_width)) uint32 width;

		/// <summary>
		/// 1コマの高さ（ピクセル）
		/// </summary>
		__declspec(property(get = _get_height)) uint32 height;

		/// <summary>
		/// 内部のテクスチャをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じテクスチャが使われていない場合、テクスチャのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release() { m_texture.release(); }

		/// <summary>
		/// テクスチャが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// テクスチャが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return !isEmpty(); }

		/// <summary>
		/// 内部のテクスチャハンドルの ID を示します。
		/// </summary>
		Texture::IDType id() const { return m_texture.id(); };

		/// <summary>
		/// 内部のテクスチャが空かどうかを示します。
		/// </summary>
		/// <returns>
		/// テクスチャが空ではない場合 true, それ以外の場合は false
		/// </returns>
		bool isEmpty() const { return m_texture.isEmpty(); };

		/// <summary>
		/// アニメーションを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void start() { m_stopwatch.start(); }

		/// <summary>
		/// アニメーションが動作中であるかを示します。
		/// </summary>
		/// <remarks>
		/// アニメーションが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isActive() const noexcept { return m_stopwatch.isRunning(); }

		/// <summary>
		/// アニメーションが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// アニメーションが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isPaused() const noexcept { return m_stopwatch.isPaused(); }

		/// <summary>
		/// アニメーションを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause() { m_stopwatch.pause(); }

		/// <summary>
		/// アニメーションが一時停止中である場合、再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resume() { m_stopwatch.resume(); }

		/// <summary>
		/// アニメーションを停止し、初期状態にリセットします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept { m_stopwatch.reset(); }

		/// <summary>
		/// 初期状態にリセットして、アニメーションを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart() { m_stopwatch.restart(); }

		/// <summary>
		/// １コマの描画時間を設定します。
		/// </summary>
		/// <param name="duration">
		/// 1コマの描画時間[ミリ秒]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setDuration(int32 duration)
		{
			m_duration = Array<int32>(m_size, duration);
			m_length = m_size * duration;
		}

		/// <summary>
		/// アニメーションの経過時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する経過時間[ミリ秒]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(int32 time) { m_stopwatch.set(MicrosecondsF(time)); }

		/// <summary>
		/// 各コマの描画時間を設定します。
		/// </summary>
		/// <param name="duration">
		/// 各コマの描画時間[ミリ秒]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setDuration(const Array<int32>& duration)
		{
			m_duration = duration;

			m_length = 0;
			for (const auto& d : duration)
				m_length += d;
		}

		/// <summary>
		/// 描画するTextureRegionを取得します。
		/// </summary>
		/// <returns>
		/// 描画するTextureRegion
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
