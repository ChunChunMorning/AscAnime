# include <Siv3D.hpp>
# include "asc\Anime.hpp"

void Main()
{
	asc::Anime anime(Texture(L"sample.png"), 4, 100);

	anime.start();

	while (System::Update())
	{
		anime.update();
		anime.draw(Mouse::Pos());
	}
}
