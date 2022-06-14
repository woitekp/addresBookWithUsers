#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cstdio> // rename(), remove() file
#include <sstream> //stringstream

int loadInteger() {
    std::cin.clear();
    fflush(stdin);
    std::string input;
    int number = 0;

    while ( true ) {
        getline( std::cin, input );
        std::stringstream myStream( input );
        if ( myStream >> number ){ break;}
            std::cout << "This is not the number. Type again: ";
    }
    return number;
}

char loadCharacter() {
    std::cin.clear();
    fflush(stdin);
    std::string input = "";
    char character = '{0}';

    while ( true ) {
        getline( std::cin, input );
        if ( input.length() == 1 ) {
            character = input[0];
            break;
        }
        std::cout << "This is not single charater. Type again: ";
    }
    return character;
}

struct Addressee
{
    int ID;
    int ownerID;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string email;
    std::string addres;
};

struct User
{
    int ID;
    std::string login;
    std::string password;
};

Addressee loadAddresseeDataFromLine ( std::string lineToGetDataFrom ) {
    Addressee addresseeToLoad;
    std::string fieldData;
    size_t delimiterPosition = lineToGetDataFrom.find( "|" );
    int i=0;
    while ( delimiterPosition != std::string::npos )
    {
        fieldData = lineToGetDataFrom.substr( 0, delimiterPosition );
        switch ( i ) {
            case 0: addresseeToLoad.ID = atoi( fieldData.c_str() ); break;
            case 1: addresseeToLoad.ownerID = atoi( fieldData.c_str() ); break;
            case 2: addresseeToLoad.firstName = fieldData; break;
            case 3: addresseeToLoad.lastName = fieldData; break;
            case 4: addresseeToLoad.phoneNumber = fieldData; break;
            case 5: addresseeToLoad.email = fieldData; break;
            case 6: addresseeToLoad.addres = fieldData; break;
    }
        lineToGetDataFrom = lineToGetDataFrom.substr( delimiterPosition+1, lineToGetDataFrom.length()-delimiterPosition );
        delimiterPosition = lineToGetDataFrom.find( "|" );
        i++;
    }
    return addresseeToLoad;
}

void initializeAddresBookFromFile ( int userID, std::vector <Addressee> &addressees, int &lastAddresseeID ) {
    std::fstream file;
    std::string line;
    Addressee addressee;
    file.open( "addresBook.txt", std::ios::in) ;

    if( file.good() ) {
        while ( getline( file, line ) ) {
            addressee = loadAddresseeDataFromLine( line );
            lastAddresseeID = addressee.ID;
            if ( addressee.ownerID == userID )
                { addressees.push_back( addressee ) ;}
        }
        file.close();
    }
    else {
        file.close();
    }
    return;
}

void displayContacts ( std::vector <Addressee> &addressees ) {
    system( "cls" );
    int addresseesCount = addressees.size();
    std::cout << "You have " << addresseesCount << " contacts:\n\n";

    for ( int i = 0; i < addresseesCount; i++ ) {
        std::cout << "ID: " << addressees[ i ].ID << std::endl;
        std::cout << "First name: " << addressees[ i ].firstName << std::endl;
        std::cout << "Last name: " << addressees[ i ].lastName << std::endl;
        std::cout << "Phone number: " << addressees[ i ].phoneNumber << std::endl;
        std::cout << "Email: " << addressees[ i ].email << std::endl;
        std::cout << "Addres: " <<  addressees[ i ].addres << std::endl;
        std::cout << std::endl;
    }
    system( "pause" );
    return;
}

void searchContacts( std::vector <Addressee> &addressees, std::string nameToFind, std::string fieldToSearch ) {
    int matching = 0;
    if ( fieldToSearch == "firstName" ) {
        for ( int i = 0, addresseesCount = addressees.size(); i < addresseesCount; i++ ) {
            if ( addressees[ i ].firstName == nameToFind ) {
                std::cout << "ID: " << addressees[ i ].ID << std::endl;
                std::cout << "First name: " << addressees[ i ].firstName << std::endl;
                std::cout << "Last name: " << addressees[ i ].lastName << std::endl;
                std::cout << "Phone number: " << addressees[ i ].phoneNumber << std::endl;
                std::cout << "Email: " << addressees[ i ].email << std::endl;
                std::cout << "Addres: " << addressees[ i ].addres << std::endl;
                std::cout << std::endl;
                matching++;
            }
        }
    }
    else if ( fieldToSearch == "lastName" ) {
        for ( int i = 0, addresseesCount = addressees.size(); i < addresseesCount; i++ ) {
            if ( addressees[ i ].lastName == nameToFind ) {
                std::cout << "ID: " << addressees[ i ].ID << std::endl;
                std::cout << "First name: " << addressees[ i ].firstName << std::endl;
                std::cout << "Last name: " << addressees[ i ].lastName << std::endl;
                std::cout << "Phone number: " << addressees[ i ].phoneNumber << std::endl;
                std::cout << "Email: " << addressees[ i ].email << std::endl;
                std::cout << "Addres: " << addressees[ i ].addres << std::endl;
                std::cout << std::endl;
                matching++;
            }
        }
    }
    if ( matching == 0 ) {
        std::cout << "No matching contact found\n";
    }
    system( "pause" );
}

void searchContactsMenu( std::vector<Addressee> &addressees ) {
    system("cls");
    std::cout << "1. Search by first name\n";
    std::cout << "2. Search by last name\n";
    char userChoice;
    std::cin >> userChoice;
    std::string nameToFind;
    switch ( userChoice ) {
        case '1':
            std::cout << "Enter the first name: ";
            std::cin >> nameToFind;
            searchContacts( addressees, nameToFind, "firstName" );
            break;

        case '2':
            std::cout << "Enter the last name: ";
            std::cin >> nameToFind;
            searchContacts( addressees, nameToFind, "lastName" );
            break;
    }
}

void addContact ( std::vector<Addressee> &addressees, int ownerID, int &lastAddresseeID ) {
    system("cls");

	std::fstream file;
    file.open( "addresBook.txt", std::ios::out | std::ios::app );
	if( ! file.good() ) {
        std::cout << "ERROR! Addres book can't be opened";
        Sleep(2000);
        return;
    }

    Addressee addresseeToAdd;
    lastAddresseeID++;
    addresseeToAdd.ID = lastAddresseeID;

    file << addresseeToAdd.ID << "|";
    addresseeToAdd.ownerID = ownerID;
    file << addresseeToAdd.ownerID << "|";
    std::cout << "Enter first name: ";
    std::cin >> addresseeToAdd.firstName;
    file << addresseeToAdd.firstName << "|";
    std::cout << "Enter last name: ";
    std::cin >> addresseeToAdd.lastName;
    file << addresseeToAdd.lastName << "|";
    std::cout << "Enter phone number: ";
    std::cin >> addresseeToAdd.phoneNumber;
    file << addresseeToAdd.phoneNumber << "|";
    std::cout << "Enter email: ";
    std::cin >> addresseeToAdd.email;
    file << addresseeToAdd.email << "|";
    std::cout << "Enter addres: ";
    std::cin >> addresseeToAdd.addres;
    file << addresseeToAdd.addres << "|\n";
    file.close();
    addressees.push_back( addresseeToAdd );
    std::cout << "Addressee added";
    Sleep(2000);
}

int editContactInFile( Addressee addresseeToEdit, int idOfAddresseeToEdit ) {
    std::fstream file;
    file.open( "addresBook.txt", std::ios::in );
	if( !file.good() ) {
        std::cout << "ERROR! Addres book can't be opened. Failed to edit contact!";
        Sleep(2000);
        return 1;
    }
    std::fstream tempFile;
    tempFile.open( "temp", std::ios::out | std::ios::app );
	if( !tempFile.good() ) {
        std::cout << "ERROR occured! Failed to edit contact!";
        Sleep(2000);
        return 2;
    }
    std::string line;
    while ( getline( file, line ) ) {
        size_t delimiterPosition = line.find( "|" );
        int ID = atoi( line.substr( 0, delimiterPosition ).c_str() );
        if ( ID != idOfAddresseeToEdit ) {
            tempFile << line << std::endl;
        }
        else {
            tempFile << addresseeToEdit.ID << "|"
                     << addresseeToEdit.ownerID << "|"
                     << addresseeToEdit.firstName << "|"
                     << addresseeToEdit.lastName << "|"
                     << addresseeToEdit.phoneNumber << "|"
                     << addresseeToEdit.email << "|"
                     << addresseeToEdit.addres << "|\n";
        }
    }
    file.close();
    tempFile.close();
    std::remove( "addresBook.txt" );
    std::rename( "temp", "addresBook.txt" );
    return 0;
}

void editContact ( std::vector<Addressee> &addressees ) {
    system( "cls" );
    std::cout << "Please provide the ID of addressee to edit: ";
    int idOfAddresseeToEdit = loadInteger();
    int indexOfAddresseeToEdit = -1;
    for ( int i = 0, addresseesCount = addressees.size(); i < addresseesCount; i++ ) {
        if ( addressees[ i ].ID == idOfAddresseeToEdit ) {
            indexOfAddresseeToEdit = i;
            break;
        }
    }
    if ( indexOfAddresseeToEdit == -1 ) {
        std::cout << "No such ID!";
        Sleep(2000);
        return;
    }
    std:: cout << "\nWhich data do you like to edit?:\n1. First name\n2. Last name\n3. Phone number\n4. Email\n5. Addres\n";
    int i = loadInteger();
    switch ( i ) {
        case 1:
            std::cout << "\nProvide new first name: ";
            std::cin >> addressees[ indexOfAddresseeToEdit ].firstName;
            break;
        case 2:
            std::cout << "\nProvide new last name: ";
            std::cin >> addressees[ indexOfAddresseeToEdit ].lastName;
            break;
        case 3:
            std::cout << "\nProvide new phone number: ";
            std::cin >> addressees[ indexOfAddresseeToEdit ].phoneNumber;
            break;
        case 4:
            std::cout << "\nProvide new email: ";
            std::cin >> addressees[ indexOfAddresseeToEdit ].email;
            break;
        case 5:
            std::cout << "\nProvide new addres: ";
            std::cin >> addressees[ indexOfAddresseeToEdit ].addres;
            break;
    }
    editContactInFile( addressees[ indexOfAddresseeToEdit ], idOfAddresseeToEdit );
    std::cout << "\n\nChanges have been saved";
    Sleep(2000);
    return;
}

int removeContactFromFile( int idOfAddresseeToRemove ) {
    std::fstream file;
    file.open( "addresBook.txt", std::ios::in );
	if( !file.good() ) {
        std::cout << "ERROR! Addres book can't be opened. Failed to remove contact!";
        Sleep(2000);
        return -11;
    }
    std::fstream tempFile;
    tempFile.open( "temp", std::ios::out | std::ios::app );
	if( !tempFile.good() ) {
        std::cout << "ERROR occured! Failed to remove contact!";
        Sleep(2000);
        return -12;
    }
    std::string line;
    int lastAddresseeID = 0;
    while ( getline( file, line ) ) {
        size_t delimiterPosition = line.find( "|" );
        int ID = atoi( line.substr( 0, delimiterPosition ).c_str() );
        if ( ID != idOfAddresseeToRemove ) {
            tempFile << line << std::endl;
            lastAddresseeID = ID;
        }
    }
    file.close();
    tempFile.close();
    std::remove( "addresBook.txt" );
    std::rename( "temp", "addresBook.txt" );
    return lastAddresseeID;
}

int removeContact ( std::vector<Addressee> &addressees ) {
    system( "cls" );
    std::cout << "Please provide the ID of addressee to remove: ";
    int idOfAddresseeToRemove = loadInteger();
    for ( int i = 0, addresseesCount = addressees.size(); i < addresseesCount; i++ ) {
        if ( addressees[ i ].ID == idOfAddresseeToRemove ) {
                std::cout << "\nIf want to remove this contact, press 'y': ";
                char userChoice = loadCharacter();
                if ( userChoice == 'y' ) {
                    int lastAddresseeID = removeContactFromFile( idOfAddresseeToRemove );
                    if ( lastAddresseeID >= 0 ){
                        addressees.erase( addressees.begin()+i );
                        std::cout << "\nContact has been removed";
                    }
                    else
                        { "Error occurred. Contact NOT removed"; }
                    Sleep(2000);
                    return lastAddresseeID;
                }
                else
                    { std::cout << "Contact NOT removed"; };
                Sleep(2000);
                return -1;
        }
    }
    std::cout << "No such ID!";
    Sleep(2000);
    return -2;
}

int changePasswordInFile( User userToEdit, int userID ) {
    std::fstream file;
    file.open( "users.txt", std::ios::in );
	if( !file.good() ) {
        std::cout << "ERROR! Failed to change password!";
        Sleep(2000);
        return 1;
    }
    std::fstream tempFile;
    tempFile.open( "temp", std::ios::out | std::ios::app );
	if( !tempFile.good() ) {
        std::cout << "ERROR occured! Failed to change password!";
        Sleep(2000);
        return 2;
    }
    std::string line;
    while ( getline( file, line ) ) {
        size_t delimiterPosition = line.find( "|" );
        int ID = atoi( line.substr( 0, delimiterPosition ).c_str() );
        if ( ID != userID ) {
            tempFile << line << std::endl;
        }
        else {
            tempFile << userToEdit.ID << "|"
                     << userToEdit.login << "|"
                     << userToEdit.password << "|\n";
        }
    }
    file.close();
    tempFile.close();
    std::remove( "users.txt" );
    std::rename( "temp", "users.txt" );
    return 0;
}

void changeUserPassword ( int userID, std::vector<User> &users ) {
    system( "cls" );
    std::string password;
    std::cout << "Enter new password: ";
    std::cin >> password;
    int indexOfUserToEdit = -1;
    for ( int i = 0, usersCount = users.size(); i < usersCount; i++ ) {
        if ( users[ i ].ID == userID ) {
            users[ i ].password = password;
            indexOfUserToEdit = i;
            break;
        }
    }
    changePasswordInFile( users[ indexOfUserToEdit ], userID );
    std::cout << "\n\nChanges have been saved";
    Sleep(2000);
    return;
}

void addressBookMenu ( int userID, std::vector<User> &users ) {
    std::vector <Addressee> addressees;
    int lastAddresseeID = 0;
    initializeAddresBookFromFile( userID, addressees, lastAddresseeID );
    char userChoice;
    while ( true ) {
        system( "cls" );
        std::cout << "1. Display contacts\n";
        std::cout << "2. Search contacts\n";
        std::cout << "3. Add contact\n";
        std::cout << "4. Edit contact\n";
        std::cout << "5. Remove contact\n";
        std::cout << "6. Change Password\n";
        std::cout << "9. Logout\n";
        std::cin >> userChoice;
        switch ( userChoice ) {
            case '1': displayContacts( addressees ); break;
            case '2': searchContactsMenu( addressees ); break;
            case '3': addContact( addressees, userID, lastAddresseeID ); break;
            case '4': editContact( addressees ); break;
            case '5': {
                        int removeContactResult = removeContact( addressees );
                        if ( removeContactResult >= 0 )
                          { lastAddresseeID = removeContactResult; }
                        break;
                      }
            case '6': changeUserPassword( userID, users ); break;
            case '9': return;
        }
    }
}

User loadUserDataFromLine ( std::string lineToGetDataFrom ) {
    User userToLoad;
    std::string fieldData;
    size_t delimiterPosition = lineToGetDataFrom.find( "|" );
    int i=0;
    while ( delimiterPosition != std::string::npos )
    {
        fieldData = lineToGetDataFrom.substr( 0, delimiterPosition );
        switch ( i ) {
            case 0: userToLoad.ID = atoi( fieldData.c_str() ); break;
            case 1: userToLoad.login = fieldData; break;
            case 2: userToLoad.password = fieldData; break;
    }
        lineToGetDataFrom = lineToGetDataFrom.substr( delimiterPosition+1, lineToGetDataFrom.length()-delimiterPosition );
        delimiterPosition = lineToGetDataFrom.find( "|" );
        i++;
    }
    return userToLoad;
}

void loadUsersFromFile ( std::vector <User> &users ) {
    std::fstream file;
    std::string line;
    User userToLoad;
    file.open( "users.txt", std::ios::in) ;

    if( file.good() ) {
        while ( getline( file, line ) ){
            userToLoad = loadUserDataFromLine( line );
            users.push_back( userToLoad );
        }
        file.close();
    }
    else {
        file.close();
    }
    return;
}

int login ( std::vector <User> &users ) {
    std::string login;
    std::string password;
    std::cout << "Enter your username: ";
    std::cin >> login;
    for ( int i = 0, usersCount = users.size(); i < usersCount; i++ ) {
        if ( users[ i ].login == login ) {
            for ( int tries = 3; tries > 0; tries-- ) {
                std::cout << "\nEnter the password (" << tries << " tries remaining): ";
                std::cin >> password;
                if ( users[ i ].password == password )
                    { return users[ i ].ID; }
            }
            Sleep(5000);
            return 0;
        }
    }
    std::cout << "\nSuch user does not exists!";
    Sleep(2000);
    return 0;
}

bool suchUserExists ( std::string login, std::vector <User> &users) {
    for ( int i = 0, usersCount = users.size(); i < usersCount; i++ ) {
            if ( users[ i ].login == login ) {
                return true;
            }
        }
    return false;
}

void registration ( std::vector <User> &users ) {
    system( "cls" );
    std::string login;
	std::fstream file;
    file.open( "users.txt", std::ios::out | std::ios::app );
	if( ! file.good() ) {
        std::cout << "ERROR! Addres book can't be opened";
        Sleep(2000);
        return;
    }

    User userToAdd;
    if ( users.size() > 0 ) {

    userToAdd.ID  = users[ users.size()-1 ].ID + 1;
    }
    else {
        userToAdd.ID = 1;
    }
    file << userToAdd.ID << "|";
    std::cout << "Enter your username: ";
    std::cin >> login;
    while ( suchUserExists( login, users ) ) {
        std::cout << "\nSuch user already exists!\nEnter another username: ";
        std::cin >> login;
    }
    userToAdd.login = login;
    file << userToAdd.login << "|";
    std::cout << "Enter your password: ";
    std::cin >> userToAdd.password;
    file << userToAdd.password << "|\n";
    file.close();
    users.push_back( userToAdd );
    std::cout << "\nRegistration completed!";
    Sleep(2000);
}

void usersMenu() {
    std::vector <User> users;
    loadUsersFromFile( users );
    char userChoice;
    while ( true ) {
        system( "cls" );
        std::cout << "1. Sign in\n";
        std::cout << "2. Registration\n";
        std::cout << "3. Exit\n";
        std::cin >> userChoice;
        switch ( userChoice ) {
            case '1':
                {
                    int loggedUser = login ( users );
                    if ( loggedUser )
                        { addressBookMenu( loggedUser, users );}
                    break;
                }
            case '2': registration( users ); break;
            case '3': return;
        }
    }
    return;
}

int main() {
    usersMenu();
    return 0;
}
