/*****************************************************************************
 * Alice Michael
 * deck.cpp
 *****************************************************************************/

#include "deck.h"
#include <stdlib.h>  //srandom
#include <unistd.h> //getpid() for use with srandom()

/*****************************************************************************
 *                                   DECK CLASS
 *****************************************************************************/
deck::deck()
{
  char suite_set;
  for(int i = 0; i < 4; ++i){
	if(i == 0)
	  suite_set = 's'; //Spades first
	else if(i == 1)
	  suite_set = 'c'; //Clubs 2nd
	else if(i == 2)
	  suite_set = 'd'; //Diamonds 3rd
	else if(i == 3)
	  suite_set = 'h'; //Hearts last
	for(int j = 0; j < 14; ++j)
	  {
	    //I need to use address 0 with a value of 1, so add 
	    //one to the j to be the value in the initial value position
	    a_deck[(i*13)+j] = new card((j+1), false, suite_set); 
	  }}

  shuffle();
}

/********************Algorithm********************/
//Random number mod by 52 since there are 52 spaces, 
//then switch the indicies for the pointers
//so they get put into a random order.
//Remeber to use the same thing from cs201
//so I get a different random number every time
//so it's not the same shuffle every time.
int deck::shuffle()
{
  if(!a_deck)
    return 0; // no cards, there was an error.

  int num = 0;
  int seed = getpid();
  srand(seed);
  card * temp_i;
  card * temp_num;

  for(int i = 0; i < 52; ++i) {
    num = rand() % 51;
    temp_i = new card(a_deck[i]);
    temp_num = new card(a_deck[num]);
    
    a_deck[i] = new card(temp_num);
    a_deck[num] = new card(temp_i);


    temp_num = temp_i = NULL;
  }

  delete temp_num;
  delete temp_i;

  return 1; //successful
}


deck::~deck()
{
  if(a_deck)
    for(int i = 0; i <= 52; ++i){
      delete a_deck[i];
      a_deck[i] = NULL; }
}






int deck::cut_deck(deck * one, deck * two)
{}


int deck::draw_card()
{}

void deck::display_deck()
{
  for(int i; i < 52; ++i){
    a_deck[i]->display_full_card();
    cout << endl;
  }
}



/*****************************************************************************
 *                                   CARD CLASS
 *****************************************************************************/
//default constructor makes a 7 of hearts.  I've been watching Now You See Me,
//Highly reccommend it
card::card() : value(7), face_up(true), suite('h')
{}


//initialize card in constructor
card::card(int value_card, bool up_set, char suite_set) : value(value_card), face_up(up_set), suite(suite_set)
{}


card::card(card *& to_copy) //: value(to_copy->value), face_up(to_copy->face_up), suite(to_copy->suite)
{
  this-> value  = to_copy->value;
  this->face_up = to_copy->face_up;
  this->suite   = to_copy->suite;
}


card::~card()
{}



//Trivial display function to display the card if it face up, and spaces
//to mask it's information if it is facedown
void card::display_card_value()
{
  if(face_up == false)
    cout << "   ";
  //If the value is less than 10, I want to add a space so things align
  else if(face_up == true){
    if(value < 10)
      cout << " " << value << suite;
    else
      cout << value << suite; }
}


void deck::display_top()
{ a_deck[1]->display_part_card(); 
  //  a_deck[2]->display_full_card();
}



//This is for if cards are stacked.
void card::display_part_card()
{
  cout << " ____ \n"
       << "|    |\n"
       << "|____|\n";

  
  display_card_value();
}



void card::display_top_bar()
{ cout << " ____ "; }
void card::display_card_middle()
{ cout << "|";
  display_card_value();
  cout <<" |"; }
void card::display_bottom_bar()
{ cout << "|____|";}


void card::display_full_card()
{
  display_card_value();

}



void card::display_card()
{
  cout << value << suite;
}


bool card::flip()
{ 
  face_up = !face_up;
  return face_up;
}



//Just returns if it's greater than 9 (double digits for display reasons)
bool card::greater_than9()
{
  if(value > 9)
    return true;
  else
    return false;
}




//I was struggling getting solitaire to work any other way with the e option, 
//So I broke down and used a getter...
char card::get_suite()
{ return suite; }


bool card::is_next(card * compare)
{
  int compare_val = value;
  ++compare_val;
  int compare_val2 = compare->value;

  if(compare_val == compare_val2)
    return true;
  else
    return false;
}


bool card::is_face_up()
{return face_up;}



//Compares the value of 2 cards.
int card::compare(card & comparing)
{
  if(value > comparing.value)  //If the card being refferenced is larger, return 1
    return 1;
  else if(value < comparing.value) //If the card coming in is larger, return 2
    return 2;
  else if(value == comparing.value) //If they are equal return 3
    return 3;
}
