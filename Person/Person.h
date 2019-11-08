#pragma once
#include "../Address/Address.h"
#include "../Date/Date.h"
#include "../utils/utils.h"

class Person{
private:
    string name;
    const Date birthday;
    Address address;
    unsigned contact;
public:
    Person(string n, Date bday, Address ad, unsigned cont);
    ///@brief Gets the name of person.
    ///@return The name attribute of person.
    string getName() const;

    ///@brief Gets the birthday date of the person.
    ///@return The Birthday date attribute of the person.
    Date getBirthday() const;

    ///@brief Gets the Address of the person.
    ///@return The Address attribute of the person.
    Address getAddress() const;

    ///@brief Gets the contact date of the person.
    ///@return The Contact attribute of the person.
    unsigned getContact() const;

    ///@brief Sets the name of the card.
    ///@param n The name to be attributed to the card.
    void setName(string n);

    ///@brief Sets the Address of the card.
    ///@param ad The address to be attributed to the card.
    void setAddress(Address ad);

    ///@brief Sets the Contact of the card.
    ///@param cont The contact to be attributed to the card.
    void setContact(unsigned cont);

    friend istream & operator>>(istream & in, Person *person);

};

class Client:public Person{
    const Date acquisitionDate;
public:
    Client(string n, Date acqdate, Date bday, Address ad, unsigned cont);

    ///@brief Gets the acquistion date of the card.
    ///@return The Acquisition date attribute of the card.
    Date getAcquisitionDate() const;

    virtual float getCost() const = 0;

};

class SilverClient: public Client{
private:
    static float cost;
public:
    SilverClient(string n, Date acqdate, Date bday, Address ad, unsigned cont);
    float getCost() const;
    ///@brief Sets the Cost of the SilverCard.
    ///@param cost The cost to be attributed to the card.
    void setCost(float cost);
};

class UniClient: public Client{
private:
    static float cost;
public:
    UniClient(string n, Date acqdate, Date bday, Address ad, unsigned cont);
    float getCost() const;
    ///@brief Sets the Cost of the UniCard.
    ///@param cost The cost to be attributed to the card.
    void setCost(float cost);
};

class IndividualClient: public Client{
private:
    static float cost;
public:
    IndividualClient(string n, Date acqdate, Date bday, Address ad, unsigned cont);
    float getCost() const;
    ///@brief Sets the Cost of the IndividualCard.
    ///@param cost The cost to be attributed to the card.
    void setCost(float cost);
};

class InvalidClient : exception{
private:
    unsigned char day;
    unsigned char month;
    unsigned short year;
public:
    InvalidClient(unsigned char d, unsigned char m, unsigned short y):
            day(d), month(m), year(y) {};
};