/*****************************************************************************
 * Alice Michael
 * CS202 Project 2
 * file: deck.h
 * 
 *     This file controls the deck class and the card class.  The deck class
 * is like if you have a deck, and it has 52 cards.  Then the card class will
 * dictate how the cards themselves behave individually.  These classes should
 * not dictate how the games are played, simply how the deck and cards work.
 *****************************************************************************/
#include <iostream>

using namespace std;

#ifndef DECK_H
#define DECK_H
class card;

//Deck class.  Controls the basic things you can do with cards and 
//how to organize them
class deck
{
 public:
  deck();
  ~deck();
  void display_deck();
  
  void display_top();

  int shuffle();
  int cut_deck(deck * one, deck * two);
  int draw_card();
  
 protected: 
  card * a_deck[52];
};


//Card class.  It holds it's vlaue of the card and it also holds it's suite
class card
{
 public: 
  card();
  card(card *&);
  card(int value_card, bool up_set, char suite_set);
  ~card();

  bool flip(); //Flips the card
  char get_suite();
  bool is_next(card * compare); //Compares 2 cards to see if the incoming is the next card 
  bool is_face_up();
  int compare(card & comparing);

  //Display function options.
  void display_top_bar();
  void display_card_middle();
  void display_bottom_bar();
  void display_full_card();
  void display_part_card();
  bool greater_than9(); //Used for visual decision

  void display_card();


  protected:
  int  value;      // Numerical value to card
  bool face_up;    // True is face up, false is face down
  char suite;

 private:
  void display_card_value();
};




#endif
