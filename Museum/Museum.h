#pragma once

#include <utility>
#include "../Table/Table.h"
#include "../Address/Address.h"
#include "../utils/InvalidInput.h"


using namespace std;

///@brief Museum Class
class Museum {
    friend class System;

private:
    /// @brief True if the museum is active on the system
    bool valid = true;

    /// @brief The name of the museum
    string name;

    /// @brief The address of the museum
    Address address;

    /// @brief The capacity of the museum
    unsigned capacity;

public:
    ///@brief Contructs a Museum
    ///@param adr Address of the museum
    ///@param cap Capacity of the museum
    ///@param name Name of the museum
    Museum(Address adr, unsigned cap, string name);

    ///@brief Gets the museum name
    ///@return Returns the name of the Musuem
    string getName();

    ///@brief Gets the museum address
    ///@return Returns the address of the Musuem
    Address getAddress();

    ///@brief Gets the museum capacity
    ///@return Returns the capacity of the Musuem
    unsigned getCapacity();

    /// @brief Verifies if a museum is active in the system
    /// @return Returns true if the museum is valid
    bool isValid() const;

    /// @brief Sets the name of the museum
    /// @param name The new name of the museum
    void setName(string name);

    /// @brief Sets the address of the museum
    /// @param adr The new address of the museum
    void setAddress(Address adr);

    /// @brief Sets the capacity of the museum
    /// @param cap The new capacity of the museum
    void setCapacity(unsigned cap);

    /// @brief Sends a museum information to a ostream object
    /// @param out The ostream object to where the museum information is gonna be send
    /// @param museum The museum object that is gonna be printed on the ostream object
    /// @return Returns the ostream itself
    friend ostream &operator<<(ostream &out, const Museum &museum);

    /// @brief Creates a new museum from a istream
    /// @param in A istream object from where the information of the museum is gonna be acquired
    /// @param museum A pointer to a pointer of museum, that will point to the new museum created inside the function
    /// @return Returns the istream itself
    friend istream &operator>>(istream &in, Museum **museum);

    template<class T>
    friend bool compareName(T left, T right);

    /// @brief Compares the capacities of two museums
    /// @param left The first museum to be tested
    /// @param right The second museum to be tested
    /// @return Returns true if the capacities of the museums are equal
    friend bool compareCapacity(Museum *left, Museum *right);
};

/// @brief Existing Museum Exception
class ExistingMuseum : public exception, public Museum {
public:
    /// @brief Constructs an ExistingMuseum exception
    /// @param m The Museum that already exists
    ExistingMuseum(Museum m) : Museum(m) {}

};

/// @brief invalid Museum Exception
class InvalidMuseum : public exception, public Museum {
public:
    /// @brief Constructs an InvalidMuseum exception
    /// @param name The name of the supposed museum
    /// @param add The address of the supposed museum
    /// @param cap The capacity of the supposed museum
    InvalidMuseum(string name, Address add, unsigned cap) : Museum(add, cap, name) {}
};

/// @brief Creates a Table from museums
/// @param container A vector of pointers to Museums
/// @return A table made from the museums information
Table<string> toTable(const vector<Museum *> &container);