#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
//class for Card
struct Card 
{
public:
	int value;
	std::string suit;

	Card();
	~Card();
};

//class for Player
struct Player
{
public:
	
	std::string name;
	std::vector<Card> hand;
	int hValues;

	Player();
	~Player();
	std::string Hit(std::vector<Card> * deck);
	std::string DisplayHand();

};