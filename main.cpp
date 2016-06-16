/*****************************************************************************
 * Alice Michael
 * CS202 Project 2
 * main.cpp
 *
 * This is the client interface, it gets which game they want to play and it 
 * uses dynamic binding to make the right game to be played.
 *****************************************************************************/

#include "games.h"

char get_input();

int main()
{
  bool   done = false;
  game * my_game;  //Pointer that can either dictate solitare or war


  cout << "enter 'w' for war or 's' for solitaire: ";
  char input = get_input();

  if(input == 's')
    my_game = new solitaire;  
  else if (input == 'w')
    my_game = new war;  


  while(!done){
    my_game->display();
    done = my_game->input();
  }
  return 0;
}




char get_input()
{
  char input;

  cin >> input;
  cin.ignore();
  
  try{
    if(input != 'w' && input != 's')
      throw input;
  }
  catch(char invalid)
    {
      cout << invalid << " is not a valid response.\n"
	   << "Please enter 'w' for war, or 's' for solitaire.\n";
      return get_input();
    }

  return input;
}
