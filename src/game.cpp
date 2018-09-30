#include "game.hpp"
#include <random>
#include <iostream>

Game::Game()
{
	cell.setFillColor( sf::Color::White );
	cell.setSize(sf::Vector2f(10, 10));
}

void Game::Init( uint width, uint height )
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> dice{0, 1};

	grid.clear();

	for ( int y = 0; y < height; y++ )
	{
		std::vector<bool> row;
		for ( int x = 0; x < width; x++ )
		{
			if (dice(eng) == 0) {
				row.push_back( false );
			} else {
				row.push_back( true );
			}
		}
		grid.push_back(row);
	}
	newGrid = grid;
}

void Game::Render( sf::RenderWindow& window )
{
	window.clear( sf::Color::Black );
	// draw grid onto image
	for (int y = 0; y < this->grid.size(); y++)
	{
		for (int x = 0; x < this->grid[0].size(); x++)
		{
			if (grid[y][x] == true)
			{
				cell.setPosition(x * 10, y * 10);
				window.draw(cell);
			}
		}
	}
	window.display();
}

uint Game::GetNeighborsCount(uint x, uint y)
{
	uint count = 0;

	// left coll
	if (x > 0)
	{
		if (y > 0 && grid[y - 1][x - 1] == true)
		{
			count++;
		}
		if (grid[y][x - 1] == true)
		{
			count++;
		}
		if (y < grid.size() - 1 && grid[y + 1][x - 1] == true)
		{
			count++;
		}
	}
	// center
	if (y > 0 && grid[y - 1][x] == true)
	{
		count++;
	}
	if (y < grid.size() - 1 && grid[y + 1][x] == true)
	{
		count++;
	}

	// right
	if (x < grid[0].size() - 1)
	{
		if (y > 0 && grid[y - 1][x + 1] == true)
		{
			count++;
		}
		if (grid[y][x + 1] == true)
		{
			count++;
		}
		if (y < grid.size() - 1 && grid[y + 1][x + 1] == true)
		{
			count++;
		}
	}
	return count;
}

void Game::Update()
{
	for ( int y = 0; y < this->grid.size(); y++ )
	{
		for ( int x = 0; x < this->grid[0].size(); x++ )
		{
			uint neighbors = GetNeighborsCount( x, y );
			//alive
			if ( grid[y][x] == true )
			{
				// 1. Any live cell with fewer than two live neighbors dies, as if by under population.
				if ( neighbors < 2 )
				{
					newGrid[y][x] = false;
				}
				else if ( neighbors >= 2)
				{
					if (neighbors > 3){
						// 3. Any live cell with more than three live neighbors dies, as if by overpopulation.
						newGrid[y][x] = false;
					}
					else
					{
						// 2. Any live cell with two or three live neighbors lives on to the next generation.
						newGrid[y][x] = true;
					}
				}
			}
			// 4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
			else if ( neighbors == 3 )
			{
				newGrid[y][x] = true;
			}
			else
			{
				newGrid[y][x] = false;
			}
		}
	}
	grid = newGrid;
}