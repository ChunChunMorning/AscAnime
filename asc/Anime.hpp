# pragma once

# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	namespace detail
	{
		/// <summary>
		/// パラパラ漫画のようなアニメーション
		/// </summary>
		template<typename TextureData>
		class Anime
		{
		private:

			TextureData m_data;

			Array<SecondsF> m_durations;

			SecondsF m_elapsedTime;

			bool m_isLoop;

			void updateElapsedTime(SecondsF elapsedTime)
			{
				const auto animationLength = m_durations.sum();

				if (!m_isLoop)
				{
					m_elapsedTime = Min(elapsedTime, animationLength);

					return;
				}

				m_elapsedTime = SecondsF(Math::Fmod(elapsedTime.count(), animationLength.count()));
			}

			uint32 index() const
			{
				auto animationTime = m_elapsedTime;

				for (uint32 index = 0; index < m_durations.size(); ++index)
				{
					if (animationTime < m_durations[index])
					{
						return index;
					}

					animationTime -= m_durations[index];
				}

				assert(m_durations.size());

				return m_durations.size() - 1;
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
			/// 1コマの描画時間[秒]
			/// </param>
			/// <param name="isLoop">
			/// アニメーションをループさせる場合は true
			/// </param>
			/// <param name="startImmediately">
			/// 即座にアニメーションを開始する場合は true
			/// </param>
			Anime(const TextureData& texture, size_t size, SecondsF duration, bool isLoop = true) :
				Anime(texture, Array<SecondsF>(size, duration), isLoop) {}

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
			Anime(const TextureData& texture, const Array<SecondsF>& duration, bool isLoop = true) :
				m_data(texture),
				m_durations(duration),
				m_isLoop(isLoop) {}

			/// <summary>
			/// テクスチャが空ではないかを返します。
			/// </summary>
			/// <returns>
			/// テクスチャが空ではない場合 true, それ以外の場合は false
			/// </returns>
			explicit operator bool() const { return !isEmpty(); }

			/// <summary>
			/// 内部のテクスチャが空かどうかを示します。
			/// </summary>
			/// <returns>
			/// テクスチャが空ではない場合 true, それ以外の場合は false
			/// </returns>
			bool isEmpty() const;

			/// <summary>
			/// 1コマの幅（ピクセル）
			/// </summary>
			uint32 width() const;

			/// <summary>
			/// 1コマの高さ（ピクセル）
			/// </summary>
			uint32 height() const;

			/// <summary>
			/// 描画するTextureRegionを取得します。
			/// </summary>
			/// <returns>
			/// 描画するTextureRegion
			/// </returns>
			const TextureRegion textureRegion() const;

			SecondsF elapsedTime() const
			{
				return m_elapsedTime;
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
			void setElapsedTime(SecondsF time) noexcept
			{
				updateElapsedTime(time);
			}

			/// <summary>
			/// 内部のテクスチャをリリースします。
			/// </summary>
			/// <remarks>
			/// プログラムのほかの場所で同じテクスチャが使われていない場合、テクスチャのメモリを解放します。
			/// </remarks>
			/// <returns>
			/// なし
			/// </returns>
			void release()
			{
				m_data.release();
			}

			void update(double seconds)
			{
				update(SecondsF(seconds));
			}

			void update(SecondsF deltaTime)
			{
				updateElapsedTime(m_elapsedTime + deltaTime);
			}

			/// <summary>
			/// s3d::Texture::draw
			/// </summary>
			const RectF draw(const Color& diffuse = Palette::White) const
			{
				return textureRegion().draw(diffuse);
			}

			/// <summary>
			/// s3d::Texture::draw
			/// </summary>
			const RectF draw(double x, double y, const Color& diffuse = Palette::White) const
			{
				return textureRegion().draw(x, y, diffuse);
			}

			/// <summary>
			/// s3d::Texture::draw
			/// </summary>
			const RectF draw(const Vec2& pos, const Color& diffuse = Palette::White) const
			{
				return textureRegion().draw(pos, diffuse);
			}

			/// <summary>
			/// s3d::Texture::drawAt
			/// </summary>
			const RectF drawAt(double x, double y, const Color& diffuse = Palette::White) const
			{
				return textureRegion().drawAt(x, y, diffuse);
			}

			/// <summary>
			/// s3d::Texture::drawAt
			/// </summary>
			const RectF drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const
			{
				return textureRegion().drawAt(pos, diffuse);
			}

			/// <summary>
			/// s3d::Texture::operator ()
			/// </summary>
			const TextureRegion operator ()(double x, double y, double w, double h) const
			{
				return m_data(index() * width + x, y, w, h);
			}

			/// <summary>
			/// s3d::Texture::uv
			/// </summary>
			const TextureRegion uv(double u, double v, double w, double h) const
			{
				return m_data.uv((index() + u) / m_durations.size(), v, w / m_durations.size(), h);
			}

			/// <summary>
			/// s3d::Texture::uv
			/// </summary>
			const TextureRegion uv(const RectF& rect) const
			{
				return m_data.uv(rect.movedBy(index() * width, 0.0));
			}

			/// <summary>
			/// s3d::Texture::mirror
			/// </summary>
			const TextureRegion mirrored() const
			{
				return textureRegion().mirrored();
			}

			/// <summary>
			/// s3d::Texture::flip
			/// </summary>
			const TextureRegion flipped() const
			{
				return textureRegion().flipped();
			}

			/// <summary>
			/// s3d::Texture::scaling
			/// </summary>
			const TextureRegion scaled(double scaling) const
			{
				return textureRegion().scaled(scaling);
			}

			/// <summary>
			/// s3d::Texture::scaling
			/// </summary>
			const TextureRegion scaled(double xScaling, double yScaling) const
			{
				return textureRegion().scaled(xScaling, yScaling);
			}

			/// <summary>
			/// s3d::Texture::scaling
			/// </summary>
			const TextureRegion scaled(const Vec2& scaling) const
			{
				return textureRegion().scaled(scaling);
			}

			/// <summary>
			/// s3d::Texture::resize
			/// </summary>
			const TextureRegion resized(double width, double height) const
			{
				return textureRegion().resized(width, height);
			}

			/// <summary>
			/// s3d::Texture::resize
			/// </summary>
			const TextureRegion resized(const Vec2& size) const
			{
				return textureRegion().resized(size);
			}

			/// <summary>
			/// s3d::Texture::rotate
			/// </summary>
			const TexturedQuad rotated(double radian) const
			{
				return textureRegion().rotated(radian);
			}

			/// <summary>
			/// s3d::Texture::rotateAt
			/// </summary>
			const TexturedQuad rotatedAt(double x, double y, double radian) const
			{
				return textureRegion().rotatedAt(x, y, radian);
			}

			/// <summary>
			/// s3d::Texture::rotateAt
			/// </summary>
			const TexturedQuad rotatedAt(const Vec2& pos, double radian) const
			{
				return textureRegion().rotatedAt(pos, radian);
			}
		};

		//////////////////////////////////////////////////
		//
		//	Template Specialization
		//
		//////////////////////////////////////////////////

		uint32 Anime<Texture>::width() const
		{
			return m_data.width() / static_cast<uint32>(m_durations.size());
		}

		uint32 Anime<AssetName>::width() const
		{
			return TextureAsset(m_data).width() / static_cast<uint32>(m_durations.size());
		}

		uint32 Anime<Texture>::height() const
		{
			return m_data.height();
		}

		uint32 Anime<AssetName>::height() const
		{
			return TextureAsset(m_data).height();
		}

		bool Anime<Texture>::isEmpty() const
		{
			return m_data.isEmpty();
		}

		bool Anime<AssetName>::isEmpty() const
		{
			return !TextureAsset::IsRegistered(m_data) || TextureAsset(m_data).isEmpty();
		}

		const TextureRegion Anime<Texture>::textureRegion() const
		{
			return m_data.uv(static_cast<double>(index()) / m_durations.size(), 0.0, 1.0 / m_durations.size(), 1.0);
		}

		const TextureRegion Anime<AssetName>::textureRegion() const
		{
			return TextureAsset(m_data).uv(static_cast<double>(index()) / m_durations.size(), 0.0, 1.0 / m_durations.size(), 1.0);
		}
	}

	/// <summary>
	/// パラパラ漫画のようなアニメーション
	/// </summary>
	using Anime = detail::Anime<Texture>;

	/// <summary>
	/// パラパラ漫画のようなアニメーション
	/// </summary>
	/// <remarks>
	/// Anime と違い TextureAsset に登録された Texture を使用します.
	/// </remarks>
	using AnimeAsset = detail::Anime<AssetName>;
}
