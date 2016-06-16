/*****************************************************************************
 * Alice Michael
 * CS202 Project 2
 * file: game.h
 * 
 *     This file is to control the general game class, as well as individual
 * rules for each unique game.  In this project, that would be war and 
 * solitare
 *****************************************************************************/


#include <iostream>
#include "deck.h"


using namespace std;



#ifndef GAMES_H
#define GAMES_H

class war_node;
class node;

//Most likely Abstract base class.
//Need to make sure to make the destructor virtual!
class game : public deck
{
 public:
  game();
  virtual ~game();
  
  virtual void display() = 0;
  virtual bool input() = 0;
  

 protected:
};


//Solitare.  Needs to do things that solely this game will do.
class solitaire : public game
{
 public: 
  solitaire();
  ~solitaire();
    
  void display(); //virtual in base class
  bool input();
  
  int add_node(node *& adding, node *& head);
  
 protected:
  //0-6 board columns
  //7  -> spades
  //8  -> hearts
  //9  -> clubs
  //10 -> diamonds
  //11 -> leftover deck
  node * board[12]; 
  int player_index;
  int move_index;


 private: 
  //Display functions to break things up a bit, called inside the public display function
  //I don't want them to be inheritable.
  void display_board();
  void display_help();
  int display_board(node * head);
  int display_board_card(node * head);
  int display_board_top(node * head);  
  int display_board_bottom(node * head);
  int display_deck(node * card);
  int display_completion_decks();
  int display_completion_decks(node * head);

  //The functions to control option 'e' exclusive
  int move_end_card();
  int move_end_rec(node * head);
  int complete_card(node *& head, node *& moving);

  int flip_last(node *& head);

  int move_here();
  int move_here(node *& head, node *& moving);
  int find_first_faceup(node *& head, node *& temp);
  int move_from_deck(node *& temp);
  int is_last_flipped(node *& head);

  int flip_deck();
  int move_card(node *& head, node *& moving);

  int initialize_board();
  int flip_cards(node *& head);
};




//war class.  It needs to be able to do things that only war would do
class war : public game
{
 public: 
  war();
  
  int initialize_deck();
  
  void display(); //virtual in base class
  bool input();
  int winner();  
  
  int its_war_time();
  
 protected:  
  war_node * player1;  //After splitting the deck, player1's deck
  war_node * player2;  //After splitting the deck, player2's deck

 private:
  int add_card(war_node *& head, card *& adding);
  int flip_card();
};



//The node inherits the card class since it will link them together and need
// to be able to interact easily with each other.
class node : public card
{
 public: 
  node();
  node(card *& to_add);
  node(node *&);
  ~node();
  
  node *& go_next();
  node *& go_prev();
  int set_next(node * set);

  
 protected:
  node * next;
  node * prev;
};



//The node inherits the card since it will be used to connect the cards anyways.
class war_node
{
 public: 
  war_node();
  war_node(war_node &);
  ~war_node();

  int  add_card(card *& adding);
  int  display_card();
  int  init_index();
  int  compare(war_node *& player1, war_node *& comparing);
  int  delete_node(war_node *& head);
  void display_card_value();
  bool is_greater_than9();

  //????
  war_node *& go_next();
  
 protected:
  war_node * next;
  card array[5];
  int index;
};

#endif
