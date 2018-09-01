
# include <Siv3D.hpp>

# include "asc/Anime.hpp"

void Main()
{
	Texture texture(U"asc_anime_sample.png");

	TextureAsset::Register(U"sample", U"asc_anime_sample.png");

	asc::Anime anime(texture, 4, 0.1s);

	asc::AnimeAsset animeAsset(U"sample", { 0.1s, 0.5s, 0.1s, 0.5s });

	while (System::Update())
	{
		anime.draw(Cursor::Pos());

		animeAsset.draw(50, 50);
	}
}
