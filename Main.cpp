
# include <Siv3D.hpp>

# include "asc/Anime.hpp"

void Main()
{
	TextureAsset::Register(U"sample", U"asc_anime_sample.png");

	Texture texture(U"asc_anime_sample.png");

	asc::Anime anime(texture, 4, 0.1s);
	asc::AnimeAsset animeAsset(U"sample", { 0.1s, 0.5s, 0.1s, 0.1s });

	bool stop = false;
	bool slow = false;

	while (System::Update())
	{
		if (MouseL.down())
		{
			stop = !stop;
		}

		if (MouseR.down())
		{
			slow = !slow;
		}

		ClearPrint();
		Print(U"[MouseL] stop : {}"_fmt(stop));
		Print(U"[MouseR] slow : {}"_fmt(slow));

		if (!stop)
		{
			anime.update(System::DeltaTime());
		}

		animeAsset.update((slow ? 0.2 : 1.0) * System::DeltaTime());

		anime.mirrored().draw(Arg::topLeft = Point(50, 70));
		animeAsset.draw(Arg::center = Cursor::Pos());
	}
}
