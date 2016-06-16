/*****************************************************************************
 * Alice Michael
 * solitaire.cpp
 *****************************************************************************/

#include "games.h"

/*****************************************************************************
 *                               SOLITAIRE CLASS
 *****************************************************************************/

//Something was happening when I put this in the initializaion list, so I had to 
//initialize my indecies in the body to fix it.
solitaire::solitaire()
{
  for(int i = 0; i <= 12; ++i)
    board[i] = NULL;
  initialize_board();


  player_index = 0;
  move_index   = 11;
}


//Walks through and sets the cards on the board.
int solitaire::initialize_board()
{

  int index = 0;
  for(int i = 0; i < 7; ++i)
    for(int j = i; j < 7; ++j)
      {
	node * temp = new node(a_deck[index]);
	add_node(temp, board[j]);
	++index;
      }
  
  while(index < 52){
    node * deck_temp = new node(a_deck[index]);
    add_node(deck_temp, board[11]);
    ++index;
    }

  //These are to set the completion decks.
  card * temp_s = new card(0, true, 's');
  card * temp_c = new card(0, true, 'c');
  card * temp_d = new card(0, true, 'd');
  card * temp_h = new card(0, true, 'h');
  
  node * temp_node = new node(temp_s);
  board[7]  = temp_node;
  temp_node = new node(temp_h);
  board[8]  = temp_node;
  temp_node = new node(temp_c);
  board[9]  = temp_node;
  temp_node = new node(temp_d);
  board[10] = temp_node;
  
  for(int a = 0; a <= 6; ++a)
    flip_cards(board[a]);
}


//Goes thru a list and makes things at the end flip, used to initialize the 
//Board so it needs to be private.
int solitaire::flip_cards(node *& head)
{
  if(!head->go_next()){
    head->flip();
    return true; }
  else
    flip_cards(head->go_next());
}


//Destructor
solitaire::~solitaire()
{
  if(board)
    for(int i = 0; i <= 12; ++i){
      if(board[i]){
	delete board[i];
	board[i] = NULL; }}
}



//Recursively adds a node to the list.
//CHANGE/UPDATE; I can recursively maintain
// the temp pointer on the way back in from the 
// recursive call utilizing the int and setting 
// the prev pointer of head->next to be head. BOOM!
int solitaire::add_node(node *& adding, node *& head)
{
  if(!adding)
    return 0;
  if(!head)
    head = adding;
  else
    add_node(adding, head->go_next());

  return 1;
}



//Need to work the e, and m inputs.
//Gets the input and chooses what to do based on that input.
bool solitaire::input()
{
  char user_input;
  cin >> user_input;


  //Try block will try each letter.  Each letter is laid out and described in the 
  //help text what it is supposed to do.  This sends the inputs to the right
  //algorithm to solve the smaller problem.
  try{
    if(user_input != 'q' && user_input != 'c' && user_input != 'm' && user_input != 'w' &&
       user_input != 's' && user_input != 'f' && user_input != 'e' && user_input != 'd')
      throw user_input;
    if(user_input == 'q') //Quits the game.
      return true;
    else if(user_input == 'c') { //choose to set this list as the one to move
      move_index = player_index; //Just set the index here to be ready to move
      return false; }
    else if(user_input == 'm') { //Move the previously chosen stack to onto the current stack
      move_here();
      return false;
    }
    else if(user_input == 'e') { //'end' of the list, goes onto it's complete deck
      move_end_card();
      return false;
    }
    else if(user_input == 'd'){
      move_index = 11;
      return false;
    }  
    else if(user_input == 'w'){ //travel up the screen
      if(player_index >0) //Don't decrement below 0
	--player_index;
      else
	player_index = 0;
      return false; }
    else if(user_input == 's'){ //Travel down the screen
      if(player_index < 6) //Don't increment above 6
	++player_index;
      else
	player_index = 6;
      return false; }
    else if(user_input == 'f'){ //Flip the deck
      flip_deck();
      return false;
    }
  }
 
  catch(char invalid) {
    cout << invalid << " is not a valid input, try again\n";
    return input(); //Call back to the top of this function
  } 
}



//option 'e'
//This function goes to the end, and moves it to the correct complete 
//stack.  It will do nothing if it is not a valid move.
int solitaire::move_end_card()
{
  //If there is nothing in this space, return 0
  if(!board[player_index])
    return 0;

  move_end_rec(board[player_index]);
  return 1; //return success
}


int solitaire::move_end_rec(node * head)
{
  //In case there is no list
  if(!head)
    return 2;

  //Local variables.
  char suite;
  int num = 0;

  
  //Special case for if there is only one card
  if(!head->go_next()){
    suite = head->get_suite();
    if(suite == 's')
      num = complete_card(board[7], head);
    else if(suite == 'h')
      num = complete_card(board[8], head);
    else if(suite == 'c')
      num = complete_card(board[9], head);
    else if(suite == 'd')
      num = complete_card(board[10], head);
    board[player_index] = NULL;
    return 2; }

  //If we are at the last node, I need to handle it.
  if(!(head->go_next())->go_next()){
    suite = (head->go_next())->get_suite();
    
    //If it's a spade, board[7]
    if(suite == 's')
      num = complete_card(board[7], head->go_next());
    else if(suite == 'h')
      num = complete_card(board[8], head->go_next());
    else if(suite == 'c')
      num = complete_card(board[9], head->go_next());
    else if(suite == 'd')
      num = complete_card(board[10], head->go_next());
     
    //if num is 1, we moved the card and need to set the end to point to null
    //I also will need to flip the last card in the stack.
    if(num == 1){
      head->set_next(NULL); 
      is_last_flipped(head);
      //flip_last(board[player_index]);
    }
      
    return 0; //Stopping position.
  }
  else
    //If it wasn't the case to handle, I need to go to the next iteration
    move_end_rec(head->go_next());
  return 1; // Successfully came back out
}


int solitaire::is_last_flipped(node *& head)
{
  if(!head->go_next()){
    if(head->is_face_up())
      return 1;
    else
      head->flip(); }
  else 
    return is_last_flipped(head->go_next());
}


//Really it moves to the end of the list and does a comparison to verify it's 
//a valid move.
int solitaire::complete_card(node *& head, node *& moving)
{
  int num = 0;
  if(!head->go_next()){
    bool temp = head->is_next(moving);
    if(temp == true){
      node * temp = new node(moving); //Make a temp card to pull it off the list
      delete moving; //delete from the CURRENT list
      move_card(head, temp); //Call to the already existing call
      return 1;
    }
    else
      return 0; //Stopping condition so I want to signify I am here
  }
  else
    num = complete_card(head->go_next(), moving); //recursive call
  return num;
}




//recursively goes to the last card in the list and flips it.
int solitaire::flip_last(node *& head)
{
  if(!head)
    return 0;
  if(!head->go_next())
    head->flip();
  else
    flip_last(head->go_next());
  return 1;
}




//option m starts here
int solitaire::move_here()
{
  //I want to have a distinct 'nothing wrong but can't do' check.
  if(player_index == move_index)
    return 5;

  //Local variables.
  int refference;
  node * temp;
  
  if(move_index == 11){
    move_from_deck(temp);
    return 6; }
  
  //If there is no card in the chosen index.
  if(!board[move_index])
    return 0;

  else{
    refference = find_first_faceup(board[move_index], temp);
    
    //Most often occuring
    if(refference == 1) //Flip the card on the end
      flip_last(board[move_index]);
    //If there was only one card, this will get invoked.
    else if(refference == 2)
      board[move_index] = NULL;
    else if(refference == 0) //This is just if there were errors.
      return refference;
  }
  //add the card to the end of the desired list
  add_node(temp, board[player_index]);
  
  return refference; 
}



//Takes the top of the Deck (What is being displayed) and moves it onto
// the board in the current position.
int solitaire::move_from_deck(node *& temp)
{
  //If the deck is empty, get outta there!
  if(!board[11])
    return 0;

  temp = new node(board[11]);
  node * deleting = board[11];
  board[11] = board[11]->go_next();
  delete deleting;
  if(!temp->is_face_up())
    temp->flip();
  add_node(temp, board[player_index]);
  
  return 1;
}



//Goes thru the Linked List and checks to find the first one that is face up.
int solitaire::find_first_faceup(node *& head, node *& temp)
{
  if(!head){
    temp = NULL; //Set the temp to NULL since it's by reff
    return 0;}   //If there is nothing in the list to get.
  if(!temp)
    return 0; //if there is nothing coming in
  
  //If the current card IS faceup, need to handle the special case.
  if(head->is_face_up()){
    temp = head;    
    return 2; }
  //If the NEXT card is face up its easiest to handle.
  else if((head->go_next())->is_face_up()){
    temp = (head->go_next());
    head->set_next(NULL);
    return 1; }
  else //traverse
    return find_first_faceup(head->go_next(), temp);
}


//Recursively move to the end of the list, then move the 
int solitaire::move_here(node *& head, node *& moving)
{}


//move the first node to the end of the list, then flip the head of the list.
int solitaire::flip_deck()
{
  //flip the first card to not be flipped, 
  board[11]->flip();

  //copy the node into a new node
  node * temp = new node(board[11]);
  node * deleting = board[11];
  board[11] = board[11]->go_next();
  delete deleting;

  add_node(temp, board[11]);
   //Flip the new top of the list.  BOOM!!! perfection in flipping digital cards
  board[11]->flip();
}


//Recursively move a card to the end of the list.
//Utilize numbers to test for when to change the previous pointer.
int solitaire::move_card(node *& head, node *& moving)
{
  if(!head){
    head = moving;
    return 1; }
  else
    move_card(head->go_next(), moving);
}



//virtual in base class.  Calls all the smaller step problems.
void solitaire::display()
{
  display_board();
  cout << "\n\n\n\n\n";
  display_help();
}



int solitaire::display_board(node * head)
{
  if(!head){
    cout << endl;
    return 0; }
  head->display_card();
  if(head->go_next())
    cout << " , ";
  display_board(head->go_next());
 
  return 1;
}


int solitaire::display_board_card(node * head)
{
  if(!head){
    cout << endl;
    return 0; }

  head->display_card_middle();
  display_board_card(head->go_next());

  return 1;
}


int solitaire::display_board_top(node * head)
{
  if(!head){
    cout << "\n";
    return 0; }

  head->display_top_bar();
  display_board_top(head->go_next());

  return 1;
}



//Displays the bottom of the board
int solitaire::display_board_bottom(node * head)
{
  if(!head){
    cout << "\n";
    return 0; }


  head->display_bottom_bar();
  display_board_bottom(head->go_next());

  return 1;
}


//Show the board.  Makes calls to recursive functions and 
//controls to graphics.
void solitaire::display_board()
{
  //Temporary to show what is under each card that is face down.
  /*
  for(int i = 0; i < 7; ++i)
    display_board(board[i]);
  cout << endl << endl;
  */
  //Works through to show the lists of cards.
  for(int j = 0; j < 7; ++j)
    {
      if(player_index == j){
	cout << "   ";
	display_board_top(board[j]);
	cout << " > ";	
	display_board_card(board[j]);
	cout << " > ";
	display_board_bottom(board[j]); }
      
      else {
	display_board_top(board[j]);
	display_board_card(board[j]);
	display_board_bottom(board[j]); }
    }
  cout << endl;
  //Call to show the deck.
  display_deck(board[11]);
  display_completion_decks();

}


//The same decisions for the other cards, but for the deck.  Special
// display for an empty deck, and decision on spacing based on the value
// of the card.
int solitaire::display_deck(node * card)
{
  if(!card){
    cout << " ____ \n"
	 << "|    |\n"
	 << "| X  |\n"
	 << "|____|\n";
    return 0; }

  cout << " ____ \n";
  cout << "|";
  card->display_card();

  if(card->greater_than9() == true)
    cout <<" |\n";
  else
    cout <<"  |\n";
  cout << "|    |\n";
  cout << "|____|\n";
  return 1;
}


//Display the completion decks (array positions 7 thru 10)
int solitaire::display_completion_decks()
{
  cout << " ____   ____   ____   ____ \n";

  for(int i = 7; i <11; ++i){
    cout << "|";
    display_completion_decks(board[i]);
  }
  cout << endl;
  cout << "|    | |    | |    | |    |\n"
       << "|____| |____| |____| |____|\n";
}



//Display the decks you put the cards into.  Just another display function.
int solitaire::display_completion_decks(node * head)
{
  if(!head)
    return 0; //Theres a problem... so handle it. 
  if(!head->go_next()){
    head->display_card();
    if(head->greater_than9() == true)
      cout <<" | ";
    else
      cout <<"  | ";
    return 1;
    }
  else display_completion_decks(head->go_next());
  return 1;
}



//Displays the instructions for the user.
void solitaire::display_help()
{
  cout << "     ***You do have to press enter after your choice***\n"
       << "***You do have to move a card from the deck onto the board***\n"
       << "Please use 's' to move the cursor down, and 'w' to move up\n"
       << "Use 'c' to choose a row to move from\n"
       << "Use 'm' to move the chosen deck to the current row\n"
       << "Use 'e' to move the end of the deck onto the completion stack\n"
       << "Use 'd' to choose to move a card from the deck, and then 'm' to move it to the current row\n"
       << "Use 'f' to flip the top card of the deck\n"
       << "'q' to quit\n";
}

