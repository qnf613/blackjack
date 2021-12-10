#include "utils.h"
#include "logic.hpp"

//this is where I need to check some units from main that is either worked well or not
//which one to check(logic part) is up to me

//copy + paste main.cpp due to test cannot get data well
Card::Card() 
{
	this->value = 1;
	this->suit = "Spade";
}
Card::~Card()
{
	this->value = 0;
	this->suit = "";
}

Player::Player()
{
	this->name = "Player";
	this->hand.size();
	this->hValues = 0;
}
Player::~Player() 
{
	this->name = "";
	this->hand.clear();
	this->hValues = 0;
}

//Draw a card from a deck into the players hand; pops the deck card
std::string Player::Hit(std::vector<Card> * deck) 
{
	this->hValues += deck->back().value;
	this->hand.push_back(deck->back());
	
	std::string output;
	output = this->name + " draws a new card.";

	deck->pop_back();
	return output;
}
//Display to console the players hand and total value
std::string Player::DisplayHand() 
{
	std::string output;

	output += this->name +" value is: " + std::to_string(this->hValues);

	return output;
}

//make the shuffled deck
std::vector<Card> GenerateDeck() 
{
	std::vector<Card> newDeck;

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 4; j++) 
		{
			//new card
			Card newCard;
			//assign suites
			switch (j) 
			{
				case 0:
					newCard.suit = " of Spade";
					break;
				case 1:
					newCard.suit = " of Heart";
					break;
				case 2:
					newCard.suit = " of Diamond";
					break;
				case 3:
					newCard.suit = " of Club";
					break;
			}
			//assign values
			newCard.value = i + 1;
			if (newCard.value > 10) 
			{
				newCard.value = 10; //make Jack, Queen, and King also has values of 10
			}
			newDeck.push_back(newCard);
		}
	}
	//shuffle the deck, all vectors are getting shuffled at least once
	for (int i = 0; i < 52; i++) 
	{
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	    std::shuffle(newDeck.begin(), newDeck.end(), std::default_random_engine(seed));
	}
	return newDeck;
}

int repeatingGame()
{
	Player player;
	player.name = "Player";
	Player dealer;
	dealer.name = "Dealer";

	srand(time(0));

	std::vector<Card> deck = GenerateDeck();

	std::cout << player.Hit(&deck) << std::endl;
	std::cout << player.Hit(&deck) << std::endl;
	std::cout << dealer.Hit(&deck) << std::endl;
	std::cout << dealer.Hit(&deck) << std::endl;
	std::cout << player.DisplayHand() << std::endl;
    std::cout << dealer.DisplayHand() << std::endl;

	//no risky play. 
	//(ran btw 1~10's expected value = 5.5, u don't want to draw more card when u hav 16 or higher)
	while (player.hValues < 15.5)
	{
		if(player.hValues == 11)
		{
			if(player.hand[0].value == 1 || player.hand[1].value == 1){
				std::cout << "The player got a combination of an Ace a 10 (or Face), BLACKJACK, player win!" << std::endl;
				return 0;
			}
		}
		
		std::cout << player.Hit(&deck) << std::endl;

		if (player.hValues == 21)
		{
			std::cout << "The player got a hand of 21, player win!" << std::endl;
			return 0;
		}

		else if (player.hValues > 21)
		{
			std::cout << "The player drew a hand over 21, player bust!" << std::endl;
			return 0;
		}

		std::cout << player.DisplayHand() << std::endl;
	}

	while (dealer.hValues < 17) 
	{
		std::cout << dealer.Hit(&deck) << std::endl;
		std::cout << dealer.DisplayHand() << std::endl;
	}

	if (dealer.hValues > 21) 
	{
		std::cout << "The dealer busts, player win!" << std::endl;
		return 0;
	}

	else if (dealer.hValues < player.hValues) 
	{
		std::cout << "The player drew a better hand than the dealer, player win!" << std::endl;
		return 0;
	}

	else if (dealer.hValues > player.hValues)
	{
		std::cout << "The dealer drew a better hand than player, player lose!" << std::endl;
		return 0;
	}

	else 
	{
		std::cout << "You two drew an equal hand, the dealer wins by default rule." << std::endl;
		return 0;
	}
}



class BlackjackTestHarness : public AbstractTestHarness {
private:
    Player p = Player();
public:
    BlackjackTestHarness(){
        register_test_func("Player start with no card in their hand.", 
            [this]() -> void { assert_equal(0, (int) p.hand.size()); });
        
    }
};

class GlobalTestManager : public TestManager {
public:
  GlobalTestManager() { add_test("BlackjackTests", BlackjackTestHarness()); }
};

int main() { 
    GlobalTestManager tm = GlobalTestManager();
    tm.execute();
}
