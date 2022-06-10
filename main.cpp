#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cstdio> // rename(), remove() file
#include <sstream> //stringstream

struct Person
{
    int id;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string email;
    std::string addres;
};

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

Person loadDataFromLine ( std::string lineToGetDataFrom ) {
    Person personToLoad;
    std::string fieldData;
    size_t delimiterPosition = lineToGetDataFrom.find( "|" );
    int i=0;
    while ( delimiterPosition != std::string::npos )
    {
        fieldData = lineToGetDataFrom.substr( 0, delimiterPosition );
        switch ( i ) {
            case 0: personToLoad.id = atoi( fieldData.c_str() ); break;
            case 1: personToLoad.firstName = fieldData; break;
            case 2: personToLoad.lastName = fieldData; break;
            case 3: personToLoad.phoneNumber = fieldData; break;
            case 4: personToLoad.email = fieldData; break;
            case 5: personToLoad.addres = fieldData; break;
    }
        lineToGetDataFrom = lineToGetDataFrom.substr( delimiterPosition+1, lineToGetDataFrom.length()-delimiterPosition );
        delimiterPosition = lineToGetDataFrom.find( "|" );
        i++;
    }
    return personToLoad;
}

void initializeAddresBookFromFile ( std::vector <Person> &persons ) {
    std::fstream file;
    std::string line;
    Person personToLoad;
    file.open( "addresBook.txt", std::ios::in) ;

    if( file.good() ) {
        while ( getline( file, line ) ){
            personToLoad = loadDataFromLine( line );
            persons.push_back( personToLoad );
        }
        file.close();
    }
    else {
        file.close();
    }
    return;
}

void displayContacts ( std::vector <Person> &persons ) {
    system( "cls" );
    int personsCount = persons.size();
    std::cout << "You have " << personsCount << " contacts:\n\n";

    for ( int i = 0; i < personsCount; i++ ) {
        std::cout << "ID: " << persons[ i ].id << std::endl;
        std::cout << "First name: " << persons[ i ].firstName << std::endl;
        std::cout << "Last name: " << persons[ i ].lastName << std::endl;
        std::cout << "Phone number: " << persons[ i ].phoneNumber << std::endl;
        std::cout << "Email: " << persons[ i ].email << std::endl;
        std::cout << "Addres: " <<  persons[ i ].addres << std::endl;
        std::cout << std::endl;
    }
    system( "pause" );
    return;
}

void searchContacts( std::vector <Person> &persons, std::string nameToFind, std::string fieldToSearch ) {
    int matching = 0;
    if ( fieldToSearch == "firstName" ) {
        for ( int i = 0, personsCount = persons.size(); i < personsCount; i++ ) {
            if ( persons[ i ].firstName == nameToFind ) {
                std::cout << "ID: " << persons[ i ].id << std::endl;
                std::cout << "First name: " << persons[ i ].firstName << std::endl;
                std::cout << "Last name: " << persons[ i ].lastName << std::endl;
                std::cout << "Phone number: " << persons[ i ].phoneNumber << std::endl;
                std::cout << "Email: " << persons[ i ].email << std::endl;
                std::cout << "Addres: " << persons[ i ].addres << std::endl;
                std::cout << std::endl;
                matching++;
            }
        }
    }
    else if ( fieldToSearch == "lastName" ) {
        for ( int i = 0, personsCount = persons.size(); i < personsCount; i++ ) {
            if ( persons[ i ].lastName == nameToFind ) {
                std::cout << "ID: " << persons[ i ].id << std::endl;
                std::cout << "First name: " << persons[ i ].firstName << std::endl;
                std::cout << "Last name: " << persons[ i ].lastName << std::endl;
                std::cout << "Phone number: " << persons[ i ].phoneNumber << std::endl;
                std::cout << "Email: " << persons[ i ].email << std::endl;
                std::cout << "Addres: " << persons[ i ].addres << std::endl;
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

void searchContactsMenu( std::vector<Person> &persons ) {
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
            searchContacts( persons, nameToFind, "firstName" );
            break;

        case '2':
            std::cout << "Enter the last name: ";
            std::cin >> nameToFind;
            searchContacts( persons, nameToFind, "lastName" );
            break;
    }
}

void addContact ( std::vector<Person> &persons ) {
    system("cls");

	std::fstream file;
    file.open( "addresBook.txt", std::ios::out | std::ios::app );
	if( ! file.good() ) {
        std::cout << "ERROR! Addres book can't be opened";
        Sleep(2000);
        return;
    }

    Person personToAdd;
    if ( persons.size() > 0 ) {

    personToAdd.id  = persons[ persons.size()-1 ].id + 1;
    }
    else {
        personToAdd.id = 1;
    }
    file << personToAdd.id << "|";
    std::cout << "Enter first name: ";
    std::cin >> personToAdd.firstName;
    file << personToAdd.firstName << "|";
    std::cout << "Enter last name: ";
    std::cin >> personToAdd.lastName;
    file << personToAdd.lastName << "|";
    std::cout << "Enter phone number: ";
    std::cin >> personToAdd.phoneNumber;
    file << personToAdd.phoneNumber << "|";
    std::cout << "Enter email: ";
    std::cin >> personToAdd.email;
    file << personToAdd.email << "|";
    std::cout << "Enter addres: ";
    std::cin >> personToAdd.addres;
    file << personToAdd.addres << "|\n";
    file.close();
    persons.push_back( personToAdd );
}

int removeContactFromFile( int indexOfPersonToRemove ) {
    std::fstream file;
    file.open( "addresBook.txt", std::ios::in );
	if( !file.good() ) {
        std::cout << "ERROR! Addres book can't be opened. Failed to remove contact!";
        Sleep(2000);
        return 1;
    }
    std::fstream tempFile;
    tempFile.open( "temp", std::ios::out | std::ios::app );
	if( !tempFile.good() ) {
        std::cout << "ERROR occured! Failed to remove contact!";
        Sleep(2000);
        return 2;
    }
    std::string line;
    while ( getline( file, line ) ) {
        size_t delimiterPosition = line.find( "|" );
        int id = atoi( line.substr( 0, delimiterPosition ).c_str() );
        if ( id != indexOfPersonToRemove ) {
            tempFile << line << std::endl;
        }
    }
    file.close();
    tempFile.close();
    std::remove( "addresBook.txt" );
    std::rename( "temp", "addresBook.txt" );
    std::remove( "temp" );
    return 0;
}

void removeContact (std::vector<Person> &persons ) {
    system( "cls" );
    std::cout << "Please provide the ID of person to edit: ";
    int indexOfPersonToRemove = loadInteger();
    for ( int i = 0, personsCount = persons.size(); i < personsCount; i++ ) {
        if ( persons[ i ].id == indexOfPersonToRemove ) {
                std::cout << "\nIf want to delete this contact, press 'y': ";
                char userChoice = loadCharacter();
                if ( userChoice == 'y' ) {
                    if ( removeContactFromFile( indexOfPersonToRemove ) == 0 ){
                        persons.erase( persons.begin()+i );
                        std::cout << "\nContact has been removed";
                    }
                }
                else { std::cout << "Contact NOT removed"; };
                Sleep(2000);
            return;
        }
    }
    std::cout << "No such ID!";
    Sleep(2000);
    return;
}

int editContactInFile( Person personToEdit, int indexOfPersonToEdit ) {
    std::fstream file;
    file.open( "addresBook.txt", std::ios::in );
	if( !file.good() ) {
        std::cout << "ERROR! Addres book can't be opened. Failed to remove contact!";
        Sleep(2000);
        return 1;
    }
    std::fstream tempFile;
    tempFile.open( "temp", std::ios::out | std::ios::app );
	if( !tempFile.good() ) {
        std::cout << "ERROR occured! Failed to remove contact!";
        Sleep(2000);
        return 2;
    }
    std::string line;
    while ( getline( file, line ) ) {
        size_t delimiterPosition = line.find( "|" );
        int id = atoi( line.substr( 0, delimiterPosition ).c_str() );
        if ( id != indexOfPersonToEdit ) {
            tempFile << line << std::endl;
        }
        else {
            tempFile << personToEdit.id << "|"
                     << personToEdit.firstName << "|"
                     << personToEdit.lastName << "|"
                     << personToEdit.phoneNumber << "|"
                     << personToEdit.email << "|"
                     << personToEdit.addres << "|\n";
        }
    }
    file.close();
    tempFile.close();
    std::remove( "addresBook.txt" );
    std::rename( "temp", "addresBook.txt" );
    std::remove( "temp" );
    return 0;
}

void editContact ( std::vector<Person> &persons ) {
    system( "cls" );
    std::cout << "Please provide the ID of person to edit: ";
    int idOfPersonToEdit = loadInteger();
    int indexOfPersonToEdit = -1;
    for ( int i = 0, personsCount = persons.size(); i < personsCount; i++ ) {
        if ( persons[ i ].id == idOfPersonToEdit ) {
            indexOfPersonToEdit = i;
            break;
        }
    }
    if ( indexOfPersonToEdit == -1 ) {
        std::cout << "No such ID!";
        Sleep(2000);
        return;
    }
    std:: cout << "\nWhich data do you like to edit?:\n1. First name\n2. Last name\n3. Phone number\n4. Email\n5. Addres\n";
    int i = loadInteger();
    switch ( i ) {
        case 1:
            std::cout << "\nProvide new first name: ";
            std::cin >> persons[ indexOfPersonToEdit ].firstName;
            break;
        case 2:
            std::cout << "\nProvide new last name: ";
            std::cin >> persons[ indexOfPersonToEdit ].lastName;
            break;
        case 3:
            std::cout << "\nProvide new phone number: ";
            std::cin >> persons[ indexOfPersonToEdit ].phoneNumber;
            break;
        case 4:
            std::cout << "\nProvide new email: ";
            std::cin >> persons[ indexOfPersonToEdit ].email;
            break;
        case 5:
            std::cout << "\nProvide new addres: ";
            std::cin >> persons[ indexOfPersonToEdit ].addres;
            break;
    }
    editContactInFile( persons[ indexOfPersonToEdit ], idOfPersonToEdit );
    std::cout << "\n\nChanges have been saved";
    Sleep(2000);
    return;
}


int main() {
    std::vector <Person> persons;
    int personsCount = 0;
    initializeAddresBookFromFile( persons );
    char userChoice;
    while ( true ) {
        system( "cls" );
        std::cout << "1. Display contacts\n";
        std::cout << "2. Search contacts\n";
        std::cout << "3. Add contact\n";
        std::cout << "4. Remove contact\n";
        std::cout << "5. Edit contact\n";
        std::cout << "9. Exit\n";
        std::cin >> userChoice;
        switch ( userChoice ) {
            case '1': displayContacts( persons ); break;
            case '2': searchContactsMenu( persons ); break;
            case '3': addContact( persons ); break;
            case '4': removeContact( persons ); break;
            case '5': editContact( persons ); break;
            case '9': return 0;
        }
    }
}
