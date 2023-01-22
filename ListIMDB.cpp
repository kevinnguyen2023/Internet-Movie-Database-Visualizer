#include "Bridges.h"
#include "DataSource.h"
#include "Array.h"
#include "SLelement.h"
using namespace bridges;

//
//  This program illustrates how to access a small subset of the IMDB actor movie data
//  set (a list of actor movie pairs and build a linked list and visualize it.
//
int main() {

  //create the Bridges object, set credentials
  Bridges bridges(1, "knguyen159", "54380843058");

  bridges.setTitle("List IMDB");

  // TODO:  access the IMDB dataset - use the data source object within BRIDGES and call
  // its getActorMovieIMDBData() method
  // this will return a list (vector) of actor-movie objects of type
  // ActorMovieIMDB - refer to the docs for that object and its attributes
  DataSource ds (&bridges);
  vector<ActorMovieIMDB> actor_list = ds.getActorMovieIMDBData(1814);
  


  // TODO: build a linked list, using singly linked list elements, SLElement<ActorMovieIMDB>
  // where the actormovie object is a generic parameter that

  // iterate through the vector and put each of the actor movie names into the label
  // field of the SLelement (using the setLabel() method of the element) -
  //  this will show up in the visualization when you do a moouse  over the node
  SLelement<ActorMovieIMDB> *head = nullptr;

  for (int i = 0; i < actor_list.size(); i++ ) {
    SLelement<ActorMovieIMDB>* nextNode = new SLelement<ActorMovieIMDB> (actor_list.at(i));
    string label = nextNode->getValue().getActor() 
     + nextNode->getValue().getMovie(); 
    nextNode->setLabel(label);


    if (head == nullptr) {
      head = nextNode;
    }
    else {
      nextNode->setNext(head);
      head = nextNode;
    }
  }

  // tell Bridges what data structure to visualize
  bridges.setDataStructure(head);

  // visualize the list
  bridges.visualize();

  //free the list as you have created dynamic memory
  for (int i = 0; i < actor_list.size()-1; ++i) {
    //SLelement<ActorMovieIMDB>* nextnextNode = head->getNext()->getNext();
    SLelement<ActorMovieIMDB>* nextNode;
    nextNode = head->getNext();
    delete head;
    head = nextNode;
  }

  return 0;
}
