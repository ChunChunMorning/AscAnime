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

			void updateIndexAndElapsedTime(SecondsF deltaTime);

			void updateForwardIndexAndElapsedTime(SecondsF deltaTime);

			void updateReverseIndexAndElapsedTime(SecondsF deltaTime);

		public:

			/// <summary>
			/// デフォルトコンストラクタ
			/// </summary>
			Anime() = default;

			/// <summary>
			/// Textureから Anime を作成します。
			/// </summary>
			/// <param name="texture">
			/// テクスチャ
			/// </param>
			/// <param name="size">
			/// テクスチャに含まれるコマ数
			/// </param>
			/// <param name="duration">
			/// 1コマの描画時間
			/// </param>
			/// <param name="isLoop">
			/// アニメーションをループさせる場合は true
			/// </param>
			Anime(const TextureData& texture, size_t size, SecondsF duration, bool isLoop = true) :
				Anime(texture, Array<SecondsF>(size, duration), isLoop) {}

			/// <summary>
			/// Texture から Anime を作成します。
			/// </summary>
			/// <param name="texture">
			/// テクスチャ
			/// </param>
			/// <param name="duration">
			/// 各コマの描画時間
			/// </param>
			/// <param name="isLoop">
			/// アニメーションをループさせる場合は true
			/// </param>
			/// <remarks>
			/// テクスチャに含まれるコマ数と durations.size() が一致する必要があります。
			/// </remarks>
			Anime(const TextureData& texture, const Array<SecondsF>& durations, bool isLoop = true) :
				m_elapsedTime(0.0s),
				m_index(0u),
				m_durations(durations),
				m_data(texture),
				m_isLoop(isLoop)
			{
				assert(m_durations.all([](SecondsF e) { return e > 0.0s; }));
			}

			/// <summary>
			/// アニメーションが空ではないかを返します。
			/// </summary>
			/// <returns>
			/// アニメーションが空ではない場合 true, それ以外の場合は false
			/// </returns>
			[[nodiscard]] explicit operator bool() const { return !isEmpty(); }

			/// <summary>
			/// アニメーションが空かどうかを示します。
			/// </summary>
			/// <returns>
			/// アニメーションが空ではない場合 true, それ以外の場合は false
			/// </returns>
			[[nodiscard]] bool isEmpty() const;

			/// <summary>
			/// 1 コマの幅（ピクセル）
			/// </summary>
			[[nodiscard]] uint32 width() const;

			/// <summary>
			/// 1 コマの高さ（ピクセル）
			/// </summary>
			[[nodiscard]] uint32 height() const;

			/// <summary>
			/// 描画する TextureRegion を取得します。
			/// </summary>
			/// <returns>
			/// 描画する TextureRegion
			/// </returns>
			[[nodiscard]] const TextureRegion textureRegion() const;

			/// <summary>
			/// アニメーションの経過時間を取得します。
			/// </summary>
			/// <returns>
			/// first -> コマ数, second -> そのコマでの経過時間
			/// </returns>
			[[nodiscard]] std::pair<size_t, SecondsF> elapsedTime() const
			{
				return { m_index, m_elapsedTime };
			}

			/// <summary>
			/// アニメーションの経過時間を変更します。
			/// </summary>
			/// <param name="index">
			/// 新しく設定するコマ
			/// </param>
			/// <param name="elapsedTime">
			/// 新しく設定するコマでの経過時間
			/// </param>
			/// <returns>
			/// first -> コマ数, second -> そのコマでの経過時間
			/// </returns>
			std::pair<size_t, SecondsF> setElapsedTime(size_t index, SecondsF elapsedTime) noexcept
			{
				m_index = index;
				m_elapsedTime = 0.0s;

				updateIndexAndElapsedTime(elapsedTime);

				return { m_index, m_elapsedTime };
			}

			/// <summary>
			/// アニメーションをリリースします。
			/// </summary>
			/// <returns>
			/// なし
			/// </returns>
			void release()
			{
				m_durations.release();
				m_data.release();
			}

			/// <summary>
			/// アニメーションの時間を更新します。
			/// </summary>
			/// <param name="deltaTime">
			/// 進める時間
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void update(double deltaTime)
			{
				update(SecondsF(deltaTime));
			}

			/// <summary>
			/// アニメーションの時間を更新します。
			/// </summary>
			/// <param name="deltaTime">
			/// 進める時間
			/// </param>
			/// <returns>
			/// なし
			/// </returns>
			void update(SecondsF deltaTime)
			{
				updateIndexAndElapsedTime(deltaTime);
			}

			/// <summary>
			/// TextureRegion::draw
			/// </summary>
			template<class ...Args>
			RectF draw(Args&&... args) const
			{
				return textureRegion().draw(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::drawClipped
			/// </summary>
			template<class ...Args>
			RectF drawClipped(Args&&... args) const
			{
				return textureRegion().drawClipped(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::drawAt
			/// </summary>
			template<class... Args>
			RectF drawAt(Args&&... args) const
			{
				return textureRegion().drawAt(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::drawAtClipped
			/// </summary>
			template<class... Args>
			RectF drawAtClipped(Args&&... args) const
			{
				return textureRegion().drawAtClipped(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::mirrored
			/// </summary>
			template<class... Args>
			[[nodiscard]] TextureRegion mirrored(Args&&... args) const
			{
				return textureRegion().mirrored(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::flipped
			/// </summary>
			template<class... Args>
			[[nodiscard]] TextureRegion flipped(Args&&... args) const
			{
				return textureRegion().flipped(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::scaled
			/// </summary>
			template<class... Args>
			[[nodiscard]] TextureRegion scaled(Args&&... args) const
			{
				return textureRegion().scaled(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::resized
			/// </summary>
			template<class... Args>
			[[nodiscard]] TextureRegion resized(Args&&... args) const
			{
				return textureRegion().resized(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::fitted
			/// </summary>
			template<class... Args>
			[[nodiscard]] TextureRegion fitted(Args&&... args) const
			{
				return textureRegion().fitted(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::rotated
			/// </summary>
			template<class... Args>
			[[nodiscard]] TexturedQuad rotated(Args&&... args) const
			{
				return textureRegion().rotated(std::forward<Args>(args)...);
			}

			/// <summary>
			/// TextureRegion::rotatedAt
			/// </summary>
			template<class... Args>
			[[nodiscard]] TexturedQuad rotatedAt(double x, double y, double angle) const
			{
				return TextureRegion().rotatedAt(std::forward<Args>(args)...);
			}
		};

		//////////////////////////////////////////////////
		//
		//	Template Implementation
		//
		//////////////////////////////////////////////////

		template<class TextureData>
		void Anime<TextureData>::updateIndexAndElapsedTime(SecondsF deltaTime)
		{
			deltaTime >= 0.0s ? updateForwardIndexAndElapsedTime(deltaTime) : updateReverseIndexAndElapsedTime(deltaTime);
		}

		template<class TextureData>
		void Anime<TextureData>::updateForwardIndexAndElapsedTime(SecondsF deltaTime)
		{
			assert(deltaTime >= 0.0s);

			m_elapsedTime += deltaTime;

			assert(!isEmpty());

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

		template<class TextureData>
		void Anime<TextureData>::updateReverseIndexAndElapsedTime(SecondsF deltaTime)
		{
			assert(deltaTime < 0.0s);

			m_elapsedTime += deltaTime;

			assert(!isEmpty());

			while (m_elapsedTime < 0.0s)
			{
				if (!m_isLoop && m_index == 0)
				{
					m_elapsedTime = 0.0s;

					break;
				}

				m_elapsedTime += m_durations[m_index];
				m_index = (m_durations.size() + m_index - 1) % m_durations.size();
			}
		}

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
