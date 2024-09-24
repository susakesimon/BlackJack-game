/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
 // ♥, ♠, ♦, ♣
 // ♥, ♠, ♦, ♣
const char* suit[4] = {"\U00002665","\U00002660","\U00002666","\U00002663"}; // H, S, D, C 
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
	// initializes it from to 0-51
	for(int i=0; i<NUM_CARDS; i++){
		cards[i] = i;
	}

	//loop for the random numbers part
	for(int i= NUM_CARDS-1; i>=1; i--){
		int randNum = rand() % (i + 1);
		//swap with the current and the random
		int temp = cards[i];
		cards[i] = cards[randNum];
		cards[randNum] = temp;
	}
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  /******** You complete ****************/
	//check if it is in bounds
	if(id < 0 && id >= NUM_CARDS){
		cout << "invalid card id" << endl;
		return;
	}

	int suitCard;
	int typeCard;
	// math to split them into categories to find index for array
	suitCard = id / 13;
	typeCard = id % 13;

	// print using global arrays	
	cout << type[typeCard] << suit[suitCard];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
	int NewCardValue;
	// checks if in bounds 
	if(id < 0 && id >= NUM_CARDS){
		cout << "invalid card id" << endl;
		return 0;
	}
	int valueCard = id % 13;
	NewCardValue = value[valueCard];
	return NewCardValue;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
	// each so loop
	for(int i=0; i<numCards; i++){
		printCard(hand[i]);
		cout << " ";
	}
	cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
	int total=0;
	int aceCounter = 0;
	// to get the total score
	for(int i=0; i<numCards; i++){
		int cardVal = cardValue(hand[i]);
		total += cardVal;
		// count the num of aces
		if(cardVal == 11){
			aceCounter++;
		}
		while(total > 21 && aceCounter > 0){
			// subtracts score by 10
			total -= 10;
			aceCounter--;
		}
	}
	// return the score
	return total;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
 
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
	
	char input, start = 'y';
	while (start == 'y'){
		int dealerCount = 2;
		int playerCount = 2;
		int passoutCards = 0;
		shuffle(cards);
		// print the ? for the innitial dealers hand
		// also printing the initial two cards for player and dealer
		phand[0] = cards[passoutCards];
		passoutCards++;
		dhand[0] = cards[passoutCards];
		passoutCards++;
		phand[1] = cards[passoutCards];
		passoutCards++;
		dhand[1] = cards[passoutCards];
		passoutCards++;
		// print the dealer hand
		cout << "Dealer: ? ";
		printCard(dhand[1]);
		cout << endl;
		// print the player hand
		cout << "Player: ";
		printHand(phand, playerCount);
		if(getBestScore(phand, playerCount) == 21){
			input = 's';
		}
		else if(getBestScore(phand, NUM_CARDS) != 21){
			cout << "Type 'h' to hit and 's' to stay:" << endl;\
			cin >> input;
		}

		// ends program if not q or s
		if(input != 'h' && input != 's'){
			return 0;
		}

		// while the player wants to hit
		while(input == 'h'){
			// if they didnt bust and they hit 
			// give them some cards
			phand[playerCount] = cards[passoutCards];
			playerCount++;
			passoutCards++;
			cout << "Player: ";
			printHand(phand, playerCount);
			// checks if player hand is over 21
			if(getBestScore(phand, playerCount) > 21 ){
				break;
			}
			else if (getBestScore(phand, playerCount) == 21){
				input = 's';
				break;
			}
			// ask player to hit or stand
			cout << "Type 'h' to hit and 's' to stay:" << endl;
			cin >> input;
		}

		// print the player lose screen if they bust
		if(getBestScore(phand, playerCount) > 21){
			cout << "Player busts" << endl;
			// prints the lose and the number
			// finish the last part of the cout 
			// cout << "Lose " << printhand(phand, playerCount) << " " << printhand(dhand, dealerCount);
		}
		else if(input != 'h' && input != 's'){
			return 0;
		}
		// if the player hits stand
		else if(input == 's'){
			// now doing the same input for the dealer
			while(getBestScore(dhand, dealerCount) < 17 ){
				// giving the dealer more cards if it is under 17
				dhand[dealerCount] = cards[passoutCards];
				dealerCount++;
				passoutCards++;
			}
			cout << "Dealer: ";
			printHand(dhand, dealerCount);
			if(getBestScore(dhand, dealerCount) > 21){
				cout << "Dealer busts" << endl;
			}

		}
		// print result 
		if(getBestScore(dhand, dealerCount) > 21 || (getBestScore(phand, playerCount) >  getBestScore(dhand, dealerCount) && getBestScore(phand, playerCount) <= 21)){
			cout << "Win " << getBestScore(phand, playerCount) << " " << getBestScore(dhand, dealerCount) << endl;
		}
		else if(getBestScore(phand, playerCount) > 21 || ((getBestScore(dhand, dealerCount) > getBestScore(phand, playerCount)) && getBestScore(dhand, dealerCount) <= 21)){
		cout << "Lose " << getBestScore(phand, playerCount) << " " << getBestScore(dhand, dealerCount) << endl;
		}
		else{
			cout << "Tie" << getBestScore(phand, playerCount) << " " << getBestScore(dhand, dealerCount) << endl;;
		}

		// to play game again
	cout << endl << "Play again? [y/n]" << endl;
	cin >> start;
}
  return 0;
}
