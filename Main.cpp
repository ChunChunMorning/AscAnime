# include <Siv3D.hpp>
# include "asc/Anime.hpp"

void Main()
{
	Texture texture(U"asc_anime_sample.png");

	asc::Anime anime(texture, 4, 100);

	while (System::Update())
	{
		anime.draw(Cursor::Pos());
	}
}


/*

// TextureAssetに登録されたTextureを使用する場合.

# include <Siv3D.hpp>
# include "asc/AnimeAsset.hpp"

void Main()
{
	TextureAsset::Register(U"anime", U"asc_anime_sample.png");

	asc::AnimeAsset anime(U"anime", 4, 100);

	while (System::Update())
	{
		anime.draw(Cursor::Pos());
	}
}
*/
