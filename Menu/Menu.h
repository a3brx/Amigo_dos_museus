#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "../Table/Table.h"
#include "../System/System.h"

class Menu {
protected:
    friend class System;
    char nextMenu;
    System *sys;
public:
    Menu(System *system);
    virtual vector<vector<string>> getOptions() const = 0;
    bool validOption(const string & option) const;
    string readOption() const;
    char option() const;
    char getNext() const;
};

class MainMenu : public Menu {
public:
    MainMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

class EventMenu : public Menu {
public:
    EventMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

class PersonMenu : public Menu {
public:
    PersonMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

class MuseumMenu : public Menu {
public:
    MuseumMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

class UpdateMuseumMenu:public Menu{
public:
    UpdateMuseumMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

class UpdatePersonMenu:public Menu{
public:
    UpdatePersonMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

class UpdateEventMenu:public Menu{
public:
    UpdateEventMenu(System *system);
    vector<vector<string>> getOptions() const override;
};