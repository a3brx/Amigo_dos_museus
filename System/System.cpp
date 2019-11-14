#include "System.h"

using namespace std;

System::System(const string &fileName/*,const string pass*/) {
    this->fileName = fileName;
    ifstream file;
    vector<string> aux = split(fileName, "/");
    aux.pop_back();
    string path = join(aux, '/');
    string museumsFile, peopleFile, eventsFile, ticketsFile;
    file.open(fileName);
    /*if(file.fail()){
        throw InvalidInput("Invalid login credentials!");
    }
    getline(file,this->pass);
    if(this->pass!=pass){
        throw InvalidInput("Invalid login credentials!");
    }*/
    file >> eventsFile >> peopleFile >> museumsFile >> ticketsFile;
    eventsFile = path + eventsFile;
    peopleFile = path + peopleFile;
    museumsFile = path + museumsFile;
    ticketsFile = path + ticketsFile;
    file.close();

    file.open(museumsFile);
    Museum *m;
    while (!file.eof()) {
        try {
            file >> &m;
        }
        catch (InvalidInput &) {
            throw InvalidInput("Error reading museums!");
        }
        this->museums.push_back(m);
    }
    file.close();

    file.open(peopleFile);

    while (!file.eof() || file.peek() != '\n') {
        char type = file.peek();
        switch (type) {
            case '-':
                Person *p;
                file >> &p;
                this->people.push_back(p);
                break;
            case '0':
                IndividualClient *i;
                file >> &i;
                if((Date().getYear() - 1 - i->getBirthday().getYear()) >= 65){
                    cout << "Good news for " << i->getName() << ", they are over 65 and now are a Silver Client " << endl;
                    SilverClient *s;
                    s = new SilverClient(i->getName(), i->getAcquisitionDate(), i->getBirthday(), i->getAddress(), i->getContact());
                    this->people.push_back(s);
                    this->clients.push_back(s);
                }else{
                    this->people.push_back(i);
                    this->clients.push_back(i);
                }
                break;
            case '1':
                SilverClient *s;
                file >> &s;
                this->people.push_back(s);
                this->clients.push_back(s);
                break;
            case '2':
                UniClient *u;
                file >> &u;
                if((Date().getYear() - 1 - i->getBirthday().getYear()) >= 65){
                    cout << "Good news for " << i->getName() << ", they are over 65 and now are a Silver Client " << endl;
                    SilverClient *s;
                    s = new SilverClient(i->getName(), i->getAcquisitionDate(), i->getBirthday(), i->getAddress(), i->getContact());
                    this->people.push_back(s);
                    this->clients.push_back(s);
                } else {
                    this->people.push_back(u);
                    this->clients.push_back(u);
                }
                break;
            default:
                break;
        }
    }
    file.close();

    file.open(eventsFile);
    Event *e;
    while (!file.eof() || file.peek() != '\n') {
        try {
            file >> &e;
        }
        catch (...) {
            throw InvalidInput("Error reading events!");
        }
        this->events.push_back(e);
        string museumName;
        getline(file, museumName);
        if ((this->findMuseum(museumName)) == museums.end()) throw InvalidInput("Museum name does not exist!");
        this->events.back()->setMuseum(*(this->findMuseum(museumName)));
    }

    file.close();

    file.open(ticketsFile);
    string auxStr;
    vector<string> vecPerson, vecEvent;
    Ticket *ticket;
    while (!file.eof() || file.peek() != '\n') {
        getline(file, auxStr);
        try {
            if (auxStr.empty()) throw InvalidInput();
            aux = trim(split(auxStr, "|"));
            vecPerson = trim(split(aux.at(0), ","));
            vecEvent = trim(split(aux.at(1), ","));
            float price = stof(aux.at(2));
            auto ite = findEvent(vecEvent.at(0), Date(vecEvent.at(1)));
            auto itp = findPerson(vecPerson.at(0), Date(vecPerson.at(1)));
            if (ite == events.end()) {
                throw InvalidInput("Event of a Ticket not found!(While reading)");
            }
            if (itp == people.end()) {
                throw InvalidInput("Person of a Ticket not found!(While reading)");
            }
            Event *ev = *this->findEvent(vecEvent.at(0), Date(vecEvent.at(1)));
            Person *p = *this->findPerson(vecPerson.at(0), Date(vecPerson.at(1)));
            ticket = new Ticket(ev, p);
            ticket->setPrice(price);
            this->soldTickets.push_back(ticket);
        }
        catch (...) {
            throw InvalidInput("Error reading tickets!");
        }
    }
    file.close();

    velho();
}

void System::readPerson() const {
    string name = getInput(isName, "Type the name of the Client: ", "Invalid name.");
    string birthday = getInput(isDate, "Type its birthday: ", "Invalid Date.");
    Person * personPtr = * findPerson(name, Date(birthday));
    if(personPtr == *this->people.end()) {
        vector<Person *> aux = {};
        readPeople(aux);
    } else
        readPeople({personPtr});
}

void System::readPeople(const vector<Client *> &container) const {
    if(container.empty()){
        cout << "The search is empty :(" << endl;
        return;
    }
    auto read = toTable(container, this);
    cout << read;
    pause();
}

void System::readPeople(const vector<Person *> &container) const {
    if(container.empty()){
        cout << "The search is empty :(" << endl;
        return;
    }
    auto read = toTable(container, this);
    cout << read;
    pause();
}

void System::readEvent() const {
    string name = getInput(notEmptyString, "Type the name of the Event: ", "Invalid name.");
    string date = getInput(isDate, "Type its date: ", "Invalid Date.");
    Event * eventPtr = * findEvent(name, Date(date));
    if(eventPtr == *this->events.end())
        readEvents({});
    else
        readEvents({eventPtr});
}

void System::readEvents(const vector<Event *> &container) const {
    if(container.empty()){
        cout << "The search is empty :(" << endl;
        return;
    }
    auto read = toTable(container, this);
    cout << read;
    pause();
}

void System::readMuseum() const {
    string name = getInput(notEmptyString, "Type the name of the Museum: ", "Invalid name.");
    Museum * museumPtr = * findMuseum(name);
    if(museumPtr == *this->museums.end())
        readMuseums({});
    else
        readMuseums({museumPtr});
}

void System::readMuseums(const vector<Museum *> &container) const {
    if(container.empty()){
        cout << "The search is empty :(" << endl;
        return;
    }
    auto read = toTable(container);
    cout << read;
    pause();
}

vector<Museum *> System::getMuseums() const {
    return this->museums;
}

vector<Event *>::const_iterator System::findEvent(string name, const Date &date) const {
    auto *tempE = new Event(nullptr, date, 0, move(name), Time());
    for (auto event = events.begin(); event != events.end(); ++event) {
        if (*tempE == **event)
            return event;
    }
    return events.end();
}

vector<Person *>::const_iterator System::findPerson(string name, const Date &birthday) const {
    auto *tempP = new Person(move(name), birthday, Address(), 0);
    for (auto person = people.begin(); person != people.end(); ++person) {
        if (*tempP == **person)
            return person;
    }
    return people.end();
}

vector<Museum *>::const_iterator System::findMuseum(const string &name) const {
    for (auto museum = museums.begin(); museum != museums.end(); ++museum) {
        if (trim(upper((*museum)->getName())) == trim(upper(name)))
            return museum;
    }
    return museums.end();
}

vector<Client *>::const_iterator System::findClient(string name, const Date &birthday) const {
    auto *tempP = new Person(move(name), birthday, Address(), 0);
    for (auto person = clients.begin(); person != clients.end(); ++person) {
        if (*tempP == **person)
            return person;
    }
    return clients.end();
}

System::~System() {
    fstream file;
    vector<string> aux = split(this->fileName, "/");
    aux.pop_back();
    string path = join(aux, '/');
    string museumsFile, peopleFile, eventsFile, ticketsFile;

    file.open(this->fileName);
    //getline(file,this->pass);
    file >> eventsFile >> peopleFile >> museumsFile >> ticketsFile;
    eventsFile = path + eventsFile;
    peopleFile = path + peopleFile;
    museumsFile = path + museumsFile;
    ticketsFile = path + ticketsFile;
    file.close();

    file.open(museumsFile);
    auto itm = this->museums.begin(), itml = this->museums.end();
    bool firstTime = true;
    for (; itm != itml; itm++) {
        if (firstTime) {
            file << *(*itm);
            firstTime = false;
            continue;
        }
        file << endl << *(*itm);
    }
    file.close();

    file.open(peopleFile);
    auto itp = this->people.begin(), itpl = this->people.end();
    firstTime = true;
    for (; itp != itpl; itp++) {
        if (firstTime) {
            file << (*itp);
            firstTime = false;
            continue;
        }
        file << endl << *itp;
    }
    file.close();

    file.open(eventsFile);
    auto ite = this->events.begin(), itel = this->events.end();
    firstTime = true;
    for (; ite != itel; ite++) {
        if (firstTime) {
            file << *(*ite);
            firstTime = false;
            continue;
        }
        file << endl << *(*ite);
    }
    file.close();

    file.open(ticketsFile);
    auto itt = this->soldTickets.begin(), ittl = this->soldTickets.end();
    firstTime = true;
    for (; itt != ittl; itt++) {
        if (firstTime) {
            file << *(*itt);
            firstTime = false;
            continue;
        }
        file << endl << *(*itt);
    }
    file.close();

}

void System::inputAddress(Address &address) {
    string street, doornumber, postalcode, local;
    cout << "Introduce the street name: ";
    getline(cin, street);
    address.setStreet(street);
    doornumber = getInput(isNum, "Introduce the door number: ", "Invalid door number");
    address.setDoorNumber(stoi(doornumber));
    address.setPostalCode(
            getInput(isPostalCode, "Introduce a valid Postal Code (Format: XXXX-YYY): ", "Invalid postal code."));
    cout << "Introduce the local: ";
    getline(cin, local);
    address.setLocality(local);
}

void System::createClient() {
    string name, birthday, contact;
    Date bday;
    Address address;
    cout << "Name: ";
    getline(cin, name);
    birthday = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    bday = Date(birthday);
    auto it = findPerson(name, bday);
    auto itc = findClient(name, bday);
    if (itc != clients.end()) {
        cout << "This client already exists!" << endl;
        return;
    }
    if (it != people.end()) {
        people.erase(it);
        cout << "Deleted Person with name " << name << " to create a client profile";
    }
    inputAddress(address);
    do {
        cout << "Contact: ";
        getline(cin, contact);
    } while (!isNum(contact) || contact.size() != 9);
    if (bday - Date() > 65 * 365) {
        auto *tempS = new SilverClient(name, Date(), bday, address, stoi(contact));
        this->people.push_back(tempS);
        cout << "Registered the client as Silver with success!\n";
        return;
    }
    bool uni = stoi(getInput(isYorN, "Does the client go to University? (1-True/0-False)", "Invalid Response"));
    if (uni) {
        auto *tempU = new UniClient(name, Date(), bday, address, stoi(contact));
        this->people.push_back(tempU);
        cout << "Registered the client as Uni with success!\n";
        return;
    }
    auto *tempI = new IndividualClient(name, Date(), bday, address, stoi(contact));
    this->people.push_back(tempI);
    cout << "Registered the client as Individual with success!\n";
}

void System::createPerson(Person *person) {
    if (findPerson(person->getName(), person->getBirthday()) == people.end()) {
        this->people.push_back(person);
        return;
    }
    throw ExistingPerson(*person);
}

vector<Event *> System::getEvents() const {
    return this->events;
}

vector<Person *> System::getPeople() const {
    return this->people;
}

void System::deleteClient(const string &name, const Date &birthday) {
    auto toRemoveP = findPerson(name, birthday);
    auto toRemoveC = findClient(name, birthday);
    if (toRemoveP == people.end())
        return;
    if (toRemoveC == clients.end())
        return;
    auto toAdd = new Person(name, birthday, (*toRemoveP)->getAddress(), (*toRemoveP)->getContact());
    this->clients.erase(toRemoveC);
    this->people.erase(toRemoveP);
    this->createPerson(toAdd);
}

void System::deleteClient() {
    string name = getInput(isName, "Type the name of the Client: ");
    string date = getInput(isDate, "Type their birthday: ", "Invalid Date.");
    deleteClient(name, Date(date));
}

void System::deleteEvent() {
    string name = getInput(notEmptyString, "Type the name of the Event: ");
    string date = getInput(isDate, "Type its date: ", "Invalid Date.");
    deleteEvent(name, Date(date));
}

void System::deleteEvent(string name, const Date &date) {
    auto toRemove = findEvent(move(name), date);
    if (toRemove == events.end())
        return;
    for (auto ticket = soldTickets.begin(); ticket != soldTickets.end(); ticket++)
        if ((*ticket)->getEvent() == *toRemove)
            soldTickets.erase(ticket);
    this->events.erase(toRemove);
}

void System::deleteMuseum() {
    string name = getInput(notEmptyString, "Type the name of the Museum: ");
    deleteMuseum(name);
}

void System::deleteMuseum(const string &name) {
    auto toRemove = findMuseum(name);
    if (toRemove == museums.end())
        return;
    (*toRemove)->valid = false;
}

void System::createEvent(Event *ev) {
    if (findEvent(ev->getName(), ev->getDate()) == events.end()) {
        this->events.push_back(ev);
        return;
    }
    throw ExistingEvent(*ev);
}

void System::createEvent() {
    string name, dateStr, price, musName, timeStr;
    Date date;
    Museum *mus;
    while (true) {
        cout << "Name: ";
        getline(cin, name);
        date = Date(getInput(isDate, "Introduce a date (Format: DD/MM/YYYY): ", "Invalid Date"));
        if (findEvent(name, date) != events.end()) {
            cout << "An Event with that name and date already exists\n Enter a new ";
            continue;
        }
        break;
    }
    timeStr = getInput(isTime, "Time of the Event (Format: HH:MM): ", "Invalid Time");
    while (true) {
        cout << "Place of the event: ";
        getline(cin, musName);
        if (findMuseum(musName) == museums.end()) {
            cout << "That place doesn't exist\n";
            continue;
        }
        break;
    }
    mus = *(findMuseum(musName));
    price = getInput(isNum, "Price: ", "Invalid Price");
    auto *tempE = new Event(mus, date, (float) stof(price), name, Time(timeStr));
    events.push_back(tempE);
    cout << "Created event with success!" << endl;
}

void System::createMuseum() {
    string name, capStr;
    Address address;
    while (true) {
        cout << "Introduce the Museum name: ";
        getline(cin, name);
        if (findMuseum(name) != museums.end()) {
            cout << "Museum with that name already exists\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Introduce the capacity of the Museum: ";
        getline(cin, capStr);
        if (!isNum(capStr)) {
            cout << "Invalid Capacity\n";
            continue;
        }
        break;
    }
    cout << "Museum's Address" << endl;
    inputAddress(address);
    auto *tempM = new Museum(address, stoi(capStr), name);
    museums.push_back(tempM);
    cout << "Created Museum with success!" << endl;
}

void System::createMuseum(Museum *mus) {
    if (findMuseum(mus->getName()) == museums.end()) {
        this->museums.push_back(mus);
        return;
    }
    throw ExistingMuseum(*mus);
}

void System::sellTicket() {
    string buyerName, buyerDate, eventName, eventDate;
    Date buyerDt, eventDt;
    Person *buyer;
    Event *event;
    cout << "Name of the buyer: ";
    getline(cin, buyerName);
    buyerDate = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    buyerDt = Date(buyerDate);
    auto finderB = findPerson(buyerName, buyerDt);
    if (finderB == people.end()) {
        cout << "This is a new Person" << endl;
        buyer->setContact(stoi(getInput(isContact, "Introduce the person's contact: ", "Invalid contact")));
        Address address;
        cout << "Person's Address" << endl;
        inputAddress(address);
        people.push_back(buyer);
    } else {
        buyer = *finderB;
    }
    while (true) {
        cout << "Name of the Event: ";
        getline(cin, eventName);
        eventDate = getInput(isDate, "Introduce the event's date (Format: DD/MM/YYYY): ", "Invalid Date");
        eventDt = Date(eventDate);
        auto finderE = findEvent(eventName, eventDt);
        if (finderE == events.end()) {
            cout << "This event doesn't exist! Choose another one\n";
            continue;
        }
        event = *finderE;
        break;
    }
    sellTicket(event, buyer);
}

void System::sellTicket(Event *event, Person *person) {
    unsigned newSoldTickets = getEventSoldTickets(event);
    if (event->getMuseum()->capacity < newSoldTickets) {
        throw OverBookedEvent(event->getMuseum(), newSoldTickets);
    }
    auto *ticket = new Ticket(event, person);
    setTicketsPrice(ticket);
    this->soldTickets.push_back(ticket);
    cout << "Ticket sold!" << endl;
}

double System::anualRevenue() const {
    auto oneYearAgo = Date();
    if(oneYearAgo.getMonth() == 2 && oneYearAgo.getDay() == 29)
        oneYearAgo.setDay(28);
    oneYearAgo.setYear(oneYearAgo.getYear() - 1);
    double total = 0;
    for (auto ticket : soldTickets){
        if(ticket->getEvent()->getDate() >= oneYearAgo)
            total += ticket->getPrice();
    }
    for (auto client : clients){
        total += client->getCost();
    }
    return total;
}

double System::totalRevenue() const {
    double total = 0;
    for (auto ticket : soldTickets){
        total += ticket->getPrice();
    }
    return total;
}

unsigned System::getEventSoldTickets(Event *ev) const {
    unsigned counter = 0;
    auto it = soldTickets.begin();
    for (; it != soldTickets.end(); it++) {
        if (*(*it)->getEvent() == *ev) {
            counter++;
        }
    }
    return counter;
}

vector<Ticket*> System::getEventTickets(Event *ev) {
    vector<Ticket*> ticks;
    auto it = soldTickets.begin();
    for (; it != soldTickets.end(); it++) {
        if (*(*it)->getEvent() == *ev) {
            ticks.push_back(new Ticket (*it));
        }
    }
    return ticks;
}

void System::setTicketsPrice(Ticket *ticket) {
    float p;
    p = ticket->getEvent()->getPrice();
    if (findClient(ticket->getPerson()->getName(), ticket->getPerson()->getBirthday()) != clients.end()) {
        p *= 0.75;
    }
    ticket->setPrice(p);
}

vector<Ticket *> System::getTickets() {
    return this->soldTickets;
}

double System::moneySpentPerson() {
    string name;
    vector<Person *>::const_iterator it;
    while (true) {
        cout << "Enter the Person's name: ";
        getline(cin, name);
        Date bDay(getInput(isDate, "Enter the Person's birthday (DD/MM/YYYY): ", "Invalid Date"));
        it = findPerson(name, bDay);
        if (it == people.end()) {
            cout << "This Person doesn't exist!" << endl;
            continue;
        }
        break;
    }
    double money = 0;
    auto itt = soldTickets.begin(), ittl = soldTickets.end();
    for (; itt != ittl; itt++) {
        if (*(*itt)->getPerson() == **it) {
            money += (*itt)->getPrice();
        }
    }
    return money;
}

double System::eventRevenue() {
    string name;
    vector<Event *>::const_iterator it;
    while (true) {
        cout << "Enter the Event's name: ";
        getline(cin, name);
        Date date(getInput(isDate, "Enter the Event's date (DD/MM/YYYY): ", "Invalid Date"));
        it = findEvent(name, date);
        if (it == events.end()) {
            cout << "This Event doesn't exist!" << endl;
            continue;
        }
        break;
    }
    double money = 0;
    auto itt = soldTickets.begin(), ittl = soldTickets.end();
    for (; itt != ittl; itt++) {
        if (*(*itt)->getEvent() == **it) {
            money += (*itt)->getPrice();
        }
    }
    return money;
}

void System::velho() const {
    Time atual;
    Date atualDate;
    auto it = events.begin(), itl = events.end();
    vector<Event *> eventsIn8Hours;
    for (; it != itl; it++) {
        if ((((*it)->getTime() - atual).getHour() <= 7) && (((*it)->getDate() - atualDate) <= 1) &&
            (getEventSoldTickets(*it) < (*it)->getMuseum()->capacity)) {
            eventsIn8Hours.push_back(*it);
        }
    }
    cout << "This Events are happening in 8 hours! Any Silver Client who lives in the same locality\n"
         << "as where the Event will happen, can get a free ticket!" << endl;
    readEvents(eventsIn8Hours);
    cout << endl;
}

vector<Ticket *>::const_iterator System::findTicket(Ticket *ticket) {
    for(auto tick=soldTickets.begin();tick!=soldTickets.end();tick++){
        if((*tick)==ticket){
            return tick;
        }
    }
    return soldTickets.end();
}

Table<string> toTable(const vector<Event *> &container, const System * sys){
    vector<string> header = {"Name", "Museum", "Date", "Time", "Sold Tickets", "Price"};
    vector<vector<string>> content;
    for (auto event : container) {
        stringstream date, time, price;
        unsigned sold = sys->getEventSoldTickets(event);
        time << event->getTime();
        date << event->getDate();
        price << fixed << setprecision(2) << event->getPrice();
        content.push_back({event->getName(), event->getMuseum()->getName(), date.str(), time.str(), to_string(sold), price.str()});
    }
    Table<string> data(header, content);
    return data;
}

Table<string> toTable(const vector<Client *> &container, const System * sys){
    vector<string> header = {"Name", "Birthday", "Address", "Contact"};
    vector<vector<string>> content;
    for (auto client : container) {
        stringstream address, birthday;
        address << client->getAddress();
        birthday << client->getBirthday();
        vector<string> aux = {client->getName(), birthday.str(), address.str(), to_string(client->getContact())};
        content.push_back(aux);
    }
    Table<string> data(header, content);
    return data;
}

Table<string> toTable(const vector<Person *> &container, const System * sys){
    vector<string> header = {"Name", "Birthday", "Address", "Contact"};
    vector<vector<string>> content;
    for (auto client : container) {
        stringstream address, birthday;
        address << client->getAddress();
        birthday << client->getBirthday();
        vector<string> aux = {client->getName(), birthday.str(), address.str(), to_string(client->getContact())};
        content.push_back(aux);
    }
    Table<string> data(header, content);
    return data;
}