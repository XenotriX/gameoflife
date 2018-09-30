#include <SFML/Graphics.hpp>

class Game
{
private:
	std::vector<std::vector<bool>> grid;
	std::vector<std::vector<bool>> newGrid;
	sf::RectangleShape cell;
public:
	Game();
	void Init(uint width, uint height);
	uint GetNeighborsCount(uint x, uint y);
	void Render(sf::RenderWindow& window);
	void Update();
};