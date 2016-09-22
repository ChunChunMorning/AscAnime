# include <Siv3D.hpp>
# include "asc\Anime.hpp"

void Main()
{
	asc::Anime anime(Texture(L"sample.png"), 4, 100);

	while (System::Update())
	{
		anime.draw(Mouse::Pos());
	}
}
