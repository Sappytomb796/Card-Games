/*****************************************************************************
 * Alice Michael
 * games.cpp 
 *****************************************************************************/


#include "games.h"



/*****************************************************************************
 *                               GAME CLASS
 *****************************************************************************/
game::game() 
{
  //  my_deck = new deck;
}

game::~game()
{
  /*
  if(my_deck){
    delete my_deck;
    my_deck = NULL; } */
}



/*****************************************************************************
 *                                   WAR CLASS
 *****************************************************************************/
war::war() : player1(NULL), player2(NULL)
{
  initialize_deck();
}



int war::initialize_deck()
{
  //Player1 initialization.
  //Since the deck is shuffled, I am just splitting the deck into halvsies
  for(int i = 0; i < 26; ++i)
    add_card(player1, a_deck[i]);
  

  //Player2 initialization.
  for(int j = 26; j < 52; ++j)
    add_card(player2, a_deck[j]);

  player1->init_index();
  player2->init_index();
  
  return 1; // Return that we got thru the function successfully
}


int war::add_card(war_node *& head, card *& adding)
{
  if(!head){
    head = new war_node;
    head->add_card(adding);
     return 1; }
  else
    head->add_card(adding);

  return 1;
}



//virtual in base class
void war::display()
{
  //Display the player card
  //Display the computer's card
  /*  cout << "Player 1 every 5th card; \n";
  player1->display_card();
  cout << "Player 2 every 5th card; \n";
  player2->display_card();
  */

  int win = winner();
  cout << " PLAYER 1                 PLAYER 2 \n"
       << " _____                     _____   \n";

  cout << "| ";
  player1->display_card_value();
  
  if(player1->is_greater_than9())
    cout << " |                   | ";
  else
    cout << "  |                   | ";


  player2->display_card_value();
  if(player2->is_greater_than9())
    cout <<" |  \n";
  else
    cout <<"  |  \n";
  cout << "|     |                   |     |  \n"
       << "|     |                   |     |  \n"
       << "|_____|                   |_____|  \n"
       << endl
       << endl;

  if(win != 3)  
    cout << "         WINNER: PLAYER " << win << "\n\n";
  else{
    cout << "         WAR!!!!!\n";
    its_war_time();
  }
}


int war::its_war_time()
{}


int war::winner()
{
  int num = 0;
  num = player1->compare(player1, player2);
  
  return num;
}





bool war::input()
{
  char user_input;
  cout << "***You do have to press enter after your choice***\n"
       << "Enter 'q' to quit, any other letter to flip a card.";
  cin >> user_input;

  if(user_input == 'q')
    return true;
  
  //flip_card();

  return false;
}


int war::flip_card()
{

}

/*****************************************************************************
 *                                  NODE CLASS
 *****************************************************************************/

node::node()
{}

node::node(card *& to_add) : card(to_add)
{}


//Really I just want to copy the card...
node::node(node *& to_copy) : card(to_copy->value, to_copy->face_up, to_copy->suite), next(NULL), prev(NULL)
{}


node::~node()
{
  next = prev = NULL;
}




node *& node::go_next()
{ return next; }



node *& node::go_prev()
{}

int node::set_next(node * set)
{  next = set; }


/*****************************************************************************
 *                                 WAR_NODE CLASS
 *****************************************************************************/
 war_node::war_node() : next(NULL), index(0)
{
 
}


war_node::war_node(war_node &)
{}



war_node::~war_node()
{}


war_node *& war_node::go_next()
{ return next; }



int war_node::add_card(card *& adding)
{
  if(index == 5){
    war_node * temp = new war_node;
    war_node * current = this;

    while(current->next)
      current = current->next;
    current->next = temp;
    temp->array[temp->index] = adding;
  }
  else{
    array[index] = adding;
    ++index; 
  }

}



int war_node::display_card()
{
  /*  cout << &array[0] << endl << &array[1] << endl 
       << &array[2] << endl << &array[3] << endl
       << &array[4] << "\n\n";
  //  array[0]->display_card_value();
  
  array[0].display_card_value();*/
  war_node * temp_node = this;
  
  while(temp_node) {
    temp_node->array[0].display_card();
    cout << endl;
    temp_node = temp_node->next; }
  
  
}

int war_node::init_index()
{ 
  war_node * temp = this;
    while(temp) {
      temp->index = 0; 
      temp = temp->next; }

  return 1;
}


int war_node::compare(war_node *& player1, war_node *& comparing)
{
  if(!comparing)
    return 0; //Failure.
  ++(player1->index);
  ++(comparing->index);

  war_node * temp = this;
  if(player1->index == 5){
    
  }
  
  if(comparing->index == 5)
    delete_node(comparing);
  
  int num = player1->array[player1->index - 1].compare(comparing->array[comparing->index -1]); 


  return num;
}


int war_node::delete_node(war_node *& head)
{
  //Something major happened and get the hell out...
  if(!head)
    return 0;

  war_node * temp = head->next;
  delete head;
  head = temp;
  head->index = 0; // Just to make sure...
  return 1; //Deleted and progressed forward.
}


void war_node::display_card_value()
{
  array[index].display_card();
}



//Just used for visual decisions to make things pretty
bool war_node::is_greater_than9()
{
  return array[index].greater_than9(); //Used for visual decision
}
