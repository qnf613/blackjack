#include <string>
#include <vector>
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