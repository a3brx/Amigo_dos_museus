#pragma once
#include <utility>
#include <vector>
#include <fstream>
#include "../Event/Event.h"
#include "../Card/Client.h"
#include "../Museum/Museum.h"

class System{
private:
    string fileName;
    vector<Event*> events;
    vector<Client*> cards;
    vector<Museum*> museums;
public:
    System(string fileName);                                               //Ler ficheiros no inicio
    ~System();                                              //Escrever nos ficheiros no fim

    void createEvent();                                     //Ler do input, dar nome ao event
    void createEvent(Event *ev);
    Event* readEvent();                                     //Pesquisa
    vector<Event*> readEvents();                            //Mostra Tabela com todos Events
    void updateEvent();                                     //Pedir input
    void updateEvent(Event* oldEvent, Event* newEvent);
    void deleteEvent();                                     //Pedir input
    void deleteEvent(string name);

    void createCard();                                      //Ler do input
    void createCard(Client *card);
    Client* readCard();                                       //Pesquisa
    vector<Client*> readCards();                              //Mostra Tabela com todos Cards
    void updateCard();                                      //Pedir input
    void updateCard(Client* oldCard, Client* newCard);
    void deleteCard();              //Pedir input
    void deleteCard(string name);

    void createMuseum();                                        //Ler do input
    void createMuseum(Museum *mus);
    Museum* readMuseum();                                       //Pesquisa
    vector<Museum*> readMuseums();                              //Mostra Tabela com todos Museums
    void updateMuseum();                                        //Pedir input
    void updateMuseum(Museum* oldMuseum, Museum* newMuseum);
    void deleteMuseum();            //Pedir input
    void deleteMuseum(string name);

    void calcBudget();
};

class InvalidInput : exception {
private:
    string type;
public:
    InvalidInput(string type) : type(move(type)) {};
};