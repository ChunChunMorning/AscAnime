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
		template<class TextureData>
		class Anime
		{
		private:

			SecondsF m_elapsedTime;

			size_t m_index;

			Array<SecondsF> m_durations;

			TextureData m_data;

			bool m_isLoop;

			void updateIndexAndElapsedTime(SecondsF deltaTime)
			{
				assert(!isEmpty());

				m_elapsedTime += deltaTime;

				while (m_elapsedTime > m_durations[m_index])
				{
					if (!m_isLoop && m_index + 1 == m_durations.size())
					{
						m_elapsedTime = m_durations[m_index];

						break;
					}

					m_elapsedTime -= m_durations[m_index];
					m_index = (m_index + 1) % m_durations.size();
				}
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
				m_elapsedTime(0.0s),
				m_index(0u),
				m_durations(duration),
				m_data(texture),
				m_isLoop(isLoop)
			{
				assert(m_durations.all([](SecondsF e) { return e > 0.0s; }));
			}

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

			std::pair<size_t, SecondsF> elapsedTime() const
			{
				return { m_index, m_elapsedTime };
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
			void setElapsedTime(size_t index, SecondsF elapsedTime) noexcept
			{
				m_index = index;
				m_elapsedTime = 0.0s;

				updateIndexAndElapsedTime(elapsedTime);
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
				m_durations.release();
				m_data.release();
			}

			void update(double seconds)
			{
				update(SecondsF(seconds));
			}

			void update(SecondsF deltaTime)
			{
				updateIndexAndElapsedTime(deltaTime);
			}

			template<class ...Args>
			RectF draw(Args&&... args) const
			{
				return textureRegion().draw(std::forward<Args>(args)...);
			}

			template<class ...Args>
			RectF drawClipped(Args&&... args) const
			{
				return textureRegion().drawClipped(std::forward<Args>(args)...);
			}

			template<class... Args>
			RectF drawAt(Args&&... args) const
			{
				return textureRegion().drawAt(std::forward<Args>(args)...);
			}

			template<class... Args>
			RectF drawAtClipped(Args&&... args) const
			{
				return textureRegion().drawAtClipped(std::forward<Args>(args)...);
			}

			template<class... Args>
			[[nodiscard]] TextureRegion mirrored(Args&&... args) const
			{
				return textureRegion().mirrored(std::forward<Args>(args)...);
			}

			template<class... Args>
			[[nodiscard]] TextureRegion flipped(Args&&... args) const
			{
				return textureRegion().flipped(std::forward<Args>(args)...);
			}

			template<class... Args>
			[[nodiscard]] TextureRegion scaled(Args&&... args) const
			{
				return textureRegion().scaled(std::forward<Args>(args)...);
			}

			template<class... Args>
			[[nodiscard]] TextureRegion resized(Args&&... args) const
			{
				return textureRegion().resized(std::forward<Args>(args)...);
			}

			template<class... Args>
			[[nodiscard]] TextureRegion fitted(Args&&... args) const
			{
				return textureRegion().fitted(std::forward<Args>(args)...);
			}

			template<class... Args>
			[[nodiscard]] TexturedQuad rotated(Args&&... args) const
			{
				return textureRegion().rotated(std::forward<Args>(args)...);
			}

			template<class... Args>
			[[nodiscard]] TexturedQuad rotatedAt(double x, double y, double angle) const
			{
				return TextureRegion().rotatedAt(std::forward<Args>(args)...);
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
			return  m_durations.isEmpty() || m_data.isEmpty();
		}

		bool Anime<AssetName>::isEmpty() const
		{
			return !TextureAsset::IsRegistered(m_data) || TextureAsset(m_data).isEmpty();
		}

		const TextureRegion Anime<Texture>::textureRegion() const
		{
			return m_data.uv(static_cast<double>(m_index) / m_durations.size(), 0.0, 1.0 / m_durations.size(), 1.0);
		}

		const TextureRegion Anime<AssetName>::textureRegion() const
		{
			return TextureAsset(m_data).uv(static_cast<double>(m_index) / m_durations.size(), 0.0, 1.0 / m_durations.size(), 1.0);
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
