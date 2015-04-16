# pragma once

# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	/// <summary>
	/// テクスチャでアニメーションを作るクラス
	/// </summary>
	class Anime
	{
	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Anime();

		/// <summary>
		/// s3d::Textureからasc::Animeを作成
		/// </summary>
		/// <param name="size">
		/// Textureに含まれるフレームの数
		/// </param>
		/// <param name="count">
		/// 1フレームの描画回数
		/// </param>
		Anime(const Texture& texture, unsigned size, unsigned count);

		/// <summary>
		/// s3d::Textureからasc::Animeを作成
		/// </summary>
		/// <param name="size">
		/// Textureに含まれるフレームの数
		/// </param>
		/// <param name="frame">
		/// フレームの設定
		/// </param>
		Anime(const Texture& texture, unsigned size, const Array<unsigned>& frame);

		/// <summary>
		/// 内部のTextureが空ではないか
		/// </summary>
		/// <returns>
		/// 内部のテクスチャが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const;

		/// <summary>
		/// 内部のTextureを返します
		/// </summary>
		/// <returns>
		/// 内部のテクスチャ
		/// </returns>
		const Texture& texture() const;

		/// <summary>
		/// 1フレームの横幅
		/// </summary>
		/// <returns>
		/// 横幅の大きさ（ピクセル）
		/// </returns>
		double width() const;

		/// <summary>
		/// 1フレームの高さ
		/// </summary>
		/// <returns>
		/// 高さの大きさ（ピクセル）
		/// </returns>
		double height() const;

		/// <summary>
		/// 内部に含まれるフレームの個数
		/// </summary>
		/// <returns>
		/// フレームの個数
		/// </returns>
		unsigned size() const;

		/// <summary>
		/// 現在、どのフレームを描写しているか
		/// </summary>
		/// <returns>
		/// フレームのインデックス
		/// </returns>
		unsigned index() const;

		/// <summary>
		/// 現在のフレームを何回描写したか
		/// </summary>
		/// <returns>
		/// 描画した回数
		/// </returns>
		unsigned count() const;

		/// <summary>
		/// フレームの描画方法を設定する
		/// </summary>
		/// <param name="count">
		/// 1フレームの描画回数
		/// </param>
		void setFrame(unsigned count);

		/// <summary>
		/// フレームの描画方法を設定する
		/// </summary>
		/// <param name="frame">
		/// フレームの設定
		/// </param>
		void setFrame(const Array<unsigned>& frame);

		/// <summary>
		/// Anime内部の時間を進める
		/// </summary>
		void update();

		/// <summary>
		/// 指定したフレームに移動する
		/// </summary>
		/// <param name="index">
		/// 移動するインデックス
		/// </param>
		/// <param name="count">
		/// 移動するインデックスを事前に何回描画するか
		/// </param>
		void jump(unsigned index, unsigned count = 0);

		/// <summary>
		/// 描画するテクスチャを取得
		/// </summary>
		/// <returns>
		/// 描画するテクスチャ
		/// </returns>
		const TextureRegion get() const;

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Vec2& pos, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::operator
		/// </summary>
		const TextureRegion operator ()(double x, double y, double w, double h) const;

		/// <summary>
		/// s3d::Texture::operator
		/// </summary>
		const TextureRegion operator ()(const RectF& rect) const;

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(double u, double v, double w, double h) const;

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(const RectF& rect) const;

		/// <summary>
		/// s3d::Texture::mirror
		/// </summary>
		const TextureRegion mirror() const;

		/// <summary>
		/// s3d::Texture::flip
		/// </summary>
		const TextureRegion flip() const;

		/// <summary>
		/// s3d::Texture::scale
		/// </summary>
		const TextureRegion scale(double scaling) const;

		/// <summary>
		/// s3d::Texture::scale
		/// </summary>
		const TextureRegion scale(double xScaling, double yScaling) const;

		/// <summary>
		/// s3d::Texture::scale
		/// </summary>
		const TextureRegion scale(const Vec2& scaling) const;

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resize(double width, double height) const;

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resize(const Vec2& size) const;

		/// <summary>
		/// s3d::Texture::rotate
		/// </summary>
		const TexturedQuad rotate(double radian) const;

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotateAt(double x, double y, double radian) const;

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotateAt(const Vec2& pos, double radian) const;

	private:

		Texture m_texture;

		unsigned m_size;

		Array<unsigned> m_frame;

		unsigned m_index;

		unsigned m_count;
	};
}
