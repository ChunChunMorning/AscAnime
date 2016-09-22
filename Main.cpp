# include <Siv3D.hpp>
# include "asc\Anime.hpp"

void Main()
{
	Texture texture(L"sample.png");
	asc::Anime anime(texture, 4, 100);

	while (System::Update())
	{
		anime.draw(Mouse::Pos());
	}
}


/*

// TextureAssetに登録されたTextureを使用する場合.

# include <Siv3D.hpp>
# include "asc\AnimeAsset.hpp"

void Main()
{
	TextureAsset::Register(L"anime", L"sample.png");

	asc::AnimeAsset anime(L"anime", 4, 100);

	while (System::Update())
	{
		anime.draw(Mouse::Pos());
	}
}
*/
