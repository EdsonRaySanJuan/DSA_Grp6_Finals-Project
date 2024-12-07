#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

string email, password, storedEmail, storedPassword, studentNumber, storedStudentNumber;
bool loggedIn = false;

void Intro() // I N T R O
{
    cout << "\n\n\n\t\t  MANAGEMENT SYSTEM          ";
    cout << "\n\n\t\t    LOST AND FOUND             ";
    cout << "\n\n\t\t     DSA PROJECT               ";
    cout << "\n\n\n\tMADE BY : GROUP 6 BLACKBOX     ";
    cout << "\n\tSCHOOL : TECHNOLOGICAL INSTITUTE   " << endl;
    cout << "                       OF THE          " << endl;
    cout << "                     PHILIPPINES       " << endl;      
    cout << "\n\n\n\n\t Press Enter to continue...  ";   
    cin.get();
}

void ShowLoginMenu() // L O G  I N 
{
    system("cls");
    cout << "\n\n\t\tLOGIN SYSTEM                 " << endl;
    cout << "\n\n\t 1. Login                      " << endl;
    cout << "\n\n\t 2. Sign Up                    " << endl;
    cout << "\n\n\t 3. Exit                       " << endl;
    cout << "\n\n\t Select an option (1-4):       ";
}

void ShowMainMenu() // M A I N   M E N U 
{
    system("cls");
    cout << "\n\n\n\t MAIN MENU                       " << endl;
    cout << "\n\n\t 1. Submit a Lost Item            " << endl;
    cout << "\n\n\t 2. Claim an Item                 " << endl;
    cout << "\n\n\t 3. List of Items                 " << endl;
    cout << "\n\n\t 4. View Claimed Items            " << endl;
    cout << "\n\n\t 5. Exit                          " << endl;
    cout << "\n\n\t Please Select Your Option (1-5): ";
}

void Login()  // L O G  I N
{
    cout << "\n\n\t ============================ Log In ============================ " << endl;

    while (!loggedIn)
    {
        cout << "\n\n\t Do you want to log in? (Enter your School Email)/(N): ";
        cin >> email;

        if (email == "N" || email == "n")
        {
            cout << "\n\n\t Returning to the login menu...\n";
            return; 
        }

        cout << "\n\n\t Enter Password/(N): ";
        cin >> password;
        
		if (password == "N" || password == "n")
        {
            cout << "\n\n\t Returning to the login menu...\n";
            return; 
        }

        ifstream file("accounts.txt");
        bool found = false;

        while (file >> storedEmail >> storedStudentNumber >> storedPassword)
        {
            if (email == storedEmail && password == storedPassword)
            {
                loggedIn = true;
                cout << "\n\n\t Login Successful! Press Enter to continue...\n";
                return;
            }
        }

        if (!found)
        {
            cout << "\n\n\t Invalid! Make sure you have entered the correct email and password.\n";
        }
    }
}

void SignUp() // S I G N  U P
{
    cout << "\n\n\t ============================ Sign Up ============================ \n";

    while (true)
    {
        cout << "\n\n\t Do you want to sign up? (Enter your School Email)/(N): ";
        cin >> email;

        if (email == "N" || email == "n")
        {
            cout << "\n\n\t Returning to the login menu...\n";
            return; 
        }

        ifstream file("accounts.txt");
        bool emailExists = false;

        while (file >> storedEmail >> storedStudentNumber >> storedPassword)
        {
            if (email == storedEmail)
            {
                emailExists = true;
                break;
            }
        }

        if (emailExists)
        {
            cout << "\n\n\t This email is already registered!\n";
            continue; 
        }

        cout << "\n\n\t Enter your Student Number/(N): ";
        cin >> studentNumber;
		if (studentNumber == "N" || studentNumber == "n")
        {
            cout << "\n\n\t Returning to the login menu...\n";
            return; 
        }
        cout << "\n\n\t Enter Password/(N): ";
        cin >> password;
		if (password == "N" || password == "n")
        {
            cout << "\n\n\t Returning to the login menu...\n";
            return; 
        }

        ofstream outFile("accounts.txt", ios::app);
        outFile << email << " " << studentNumber << " " << password << endl;

        cout << "\n\n\t Sign Up Successful! You can now log in.\n";
        return;
    }
}

struct LostItem // V A R I A B L E S 
{
    int itemID;
    string itemName;
    string locationLost;
    string dateLost;
    string contactInfo;
    string email; 
    string studentNumber;
    string status;
    LostItem* next;
};

LostItem* lostItemsHead = nullptr;
int itemCounter = 0;

void SubmitLostItem(LostItem*& head, const string& email, const string& studentNumber) // S U B M I T   L O S T   I T E M S
{
	system("cls");
    LostItem* newItem = new LostItem();
    
    itemCounter++; 
    newItem->itemID = itemCounter;

    cout << "\n\n\t ============== SUBMIT LOST/FOUND ITEM ============== \n";
    cout << "\n\t Enter Item Description (e.g., 'Black Wallet')/(N): ";
    cin.ignore();
    getline(cin, newItem->itemName);

    if (newItem->itemName == "N" || newItem->itemName == "n") 
	{
        cout << "\n\n\t Returning to the Main Menu...\n";
        delete newItem;
        return;
    }

    cout << "\n\t Enter Location Lost (e.g., 'Library, 2nd floor')/(N): ";
    getline(cin, newItem->locationLost);

    if (newItem->locationLost == "N" || newItem->locationLost == "n") 
	{
        cout << "\n\n\t Returning to the Main Menu...\n";
        delete newItem;
        return;
    }

    cout << "\n\t Enter Date Lost (e.g., '2024-11-11')/(N): ";
    getline(cin, newItem->dateLost);

    if (newItem->dateLost == "N" || newItem->dateLost == "n") 
	{
        cout << "\n\n\t Returning to the Main Menu...\n";
        delete newItem;
        return;
    }

    cout << "\n\t Enter Contact Information (optional, press Enter to skip)/(N): ";
    getline(cin, newItem->contactInfo);

    if (newItem->contactInfo == "N" || newItem->contactInfo == "n") 
	{
        cout << "\n\n\t Returning to the Main Menu...\n";
        delete newItem;
        return;
    }

    newItem->email = email; 
    newItem->studentNumber = studentNumber;
    newItem->status = "Lost";
    newItem->next = head;
    head = newItem;

    ofstream outFile("lost_items.txt", ios::app); 
    if (outFile.is_open()) 
	{
        outFile << newItem->itemID << "|"
                << newItem->itemName << "|"
                << newItem->locationLost << "|"
                << newItem->dateLost << "|"
                << newItem->contactInfo << "|"
                << newItem->email << "|"
                << newItem->studentNumber << "|"
                << newItem->status << endl;
        outFile.close();
        cout << "\n\n\t Item successfully!";
    } else {
        cout << "\n\n\t Error: Unable to save item to the txt files.";
    }

    cout << "\n\n\t Item successfully submitted! Here are the details:\n";
    cout << "\t Item ID: " << newItem->itemID << endl;
    cout << "\t Email: " << newItem->email << endl;
    cout << "\t Student Number: " << newItem->studentNumber << endl;
    cout << "\t Status: " << newItem->status << endl;

    cout << "\n\n\t Press Enter to return to the Main Menu...";
    cin.get();
}

void SearchForItems() // C L A I M  AN  I T E M S
{
	system("cls");
    ifstream inFile("lost_items.txt");
    ofstream tempFile("temp_lost_items.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        cout << "\n\n\t Error: Unable to process the file.\n";
        return;
    }

    string line;
    bool hasLostItems = false;

    cout << "\n====================================================================================================================================\n";
    cout << "   Item ID    Description      Location Lost      Date Lost      Contact Info    EmailUsed        StudentNumber         Status\n";
    cout << "=====================================================================================================================================\n";

    while (getline(inFile, line)) {
        stringstream ss(line);
        string itemID, description, location, date, contactInfo, email, studentNumber, status;

        getline(ss, itemID, '|');
        getline(ss, description, '|');
        getline(ss, location, '|');
        getline(ss, date, '|');
        getline(ss, contactInfo, '|');
        getline(ss, email, '|');
        getline(ss, studentNumber, '|');
        getline(ss, status, '|');

        if (status == "Lost") {
            hasLostItems = true;

            cout << setw(6) << itemID
                 << setw(14) << description
                 << setw(20) << location
                 << setw(20) << date
                 << setw(14) << contactInfo
                 << setw(13) << email
                 << setw(19) << studentNumber
                 << setw(19) << status << endl;
        }
    }

    if (!hasLostItems) 
	{
        cout << "\n\n\t No lost items found.\n";
        inFile.close();
        tempFile.close();
        remove("temp_lost_items.txt");
        cout << "\n\t Press Enter to return to the main menu...";
        cin.ignore();
        cin.get();
        return;
    }

    inFile.clear();
    inFile.seekg(0, ios::beg); 

    string itemIDToClaim;
    
    cout << "\n\n\t Enter the Number of Item ID you would like to Claim/(N): ";
    cin >> itemIDToClaim;

    if (itemIDToClaim == "N" || itemIDToClaim == "n") {
        cout << "\n\n\t Returning to the main menu...\n";
        inFile.close();
        tempFile.close();
        remove("temp_lost_items.txt");
        return;
    }

    bool itemFound = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string itemID, description, location, date, contactInfo, email, studentNumber, status;

        getline(ss, itemID, '|');
        getline(ss, description, '|');
        getline(ss, location, '|');
        getline(ss, date, '|');
        getline(ss, contactInfo, '|');
        getline(ss, email, '|');
        getline(ss, studentNumber, '|');
        getline(ss, status, '|');

        if (itemID == itemIDToClaim && status == "Lost") {
            itemFound = true;

            cout << "\n\t Item ID: " << itemID
                 << "\n\t Description: " << description
                 << "\n\t Location Lost: " << location
                 << "\n\t Date Lost: " << date
                 << "\n\t Contact Info: " << contactInfo
                 << "\n\t Email Used: " << email
                 << "\n\t Student Number: " << studentNumber
                 << "\n\t Status: " << status << endl;

            cout << "\n\t --------------------------------------------------\n";
            cout << "\t Successfully Claimed by Email Used: " << email
                 << ", Student Number: " << studentNumber << endl;

            status = "Claimed";
        }

        tempFile << itemID << "|" << description << "|" << location << "|" << date << "|" << contactInfo << "|" << email << "|" << studentNumber << "|" << status << endl;
    }

    inFile.close();
    tempFile.close();

    if (itemFound) {
        remove("lost_items.txt");
        rename("temp_lost_items.txt", "lost_items.txt");

        cout << "\n\n\t Item successfully claimed! Would you like to claim another? (Y/N): ";
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            SearchForItems();
        }
    } else {
        cout << "\n\n\t Item ID not found or already claimed.\n";
        remove("temp_lost_items.txt");
    }

    cout << "\n\t Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}

void ListOfItems() // L I S T  O F  I T E M S
{
    system("cls");
    ifstream inFile("lost_items.txt");

    if (!inFile.is_open()) {
        cout << "\n\n\t Error: Unable to open the file.\n";
        return;
    }

    struct LostItem {
        string itemID;
        string description;
        string location;
        string date;
        string contactInfo;
        string email;
        string studentNumber;
        string status;
        LostItem* next;
    };

    LostItem* head = nullptr;
    LostItem* tail = nullptr;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        LostItem* newItem = new LostItem();

        getline(ss, newItem->itemID, '|');
        getline(ss, newItem->description, '|');
        getline(ss, newItem->location, '|');
        getline(ss, newItem->date, '|');
        getline(ss, newItem->contactInfo, '|');
        getline(ss, newItem->email, '|');
        getline(ss, newItem->studentNumber, '|');
        getline(ss, newItem->status, '|');
        newItem->next = nullptr;

        if (head == nullptr) {
            head = newItem;
            tail = newItem;
        } else {
            tail->next = newItem;
            tail = newItem;
        }
    }

    inFile.close();

    if (head == nullptr) {
        cout << "\n\n\t No items found.\n";
    } else {
        cout << "\n====================================================================================================================================\n";
    cout << "   Item ID    Description      Location Lost      Date Lost      Contact Info    EmailUsed        StudentNumber         Status\n";
    cout << "=====================================================================================================================================\n";

        LostItem* current = head;
        while (current != nullptr) {
            cout << setw(6) << current->itemID
                 << setw(14) << current->description
                 << setw(20) << current->location
                 << setw(20) << current->date
                 << setw(14) << current->contactInfo
                 << setw(13) << current->email
                 << setw(19) << current->studentNumber
                 << setw(19) << current->status << endl;
            current = current->next;
        }
    }

    while (head != nullptr) {
        LostItem* temp = head;
        head = head->next;
        delete temp;
    }

    cout << "\n\n\t Press Enter to go back to the main menu...";
    cin.ignore();
    cin.get();
}

void ViewClaimedItems() // V I E W   C L A I M E D  I T E M S 
{
    system("cls");
    ifstream inFile("lost_items.txt");

    if (!inFile.is_open()) {
        cout << "\n\n\t Error: Unable to open the file.\n";
        return;
    }

    struct LostItem {
        string itemID;
        string description;
        string location;
        string date;
        string contactInfo;
        string email;
        string studentNumber;
        string status;
        LostItem* next;
    };

    LostItem* head = nullptr;
    LostItem* tail = nullptr;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        LostItem* newItem = new LostItem();

        getline(ss, newItem->itemID, '|');
        getline(ss, newItem->description, '|');
        getline(ss, newItem->location, '|');
        getline(ss, newItem->date, '|');
        getline(ss, newItem->contactInfo, '|');
        getline(ss, newItem->email, '|');
        getline(ss, newItem->studentNumber, '|');
        getline(ss, newItem->status, '|');
        newItem->next = nullptr;

        if (newItem->status == "Claimed") {
            if (head == nullptr) {
                head = newItem;
                tail = newItem;
            } else {
                tail->next = newItem;
                tail = newItem;
            }
        } else {
            delete newItem; 
        }
    }

    inFile.close();

    if (head == nullptr) {
        cout << "\n\n\t No claimed items founds.\n";
    } else {
        cout << "\n====================================================================================================================================\n";
    cout << "   Item ID    Description      Location Lost      Date Lost      Contact Info    EmailUsed        StudentNumber         Status\n";
    cout << "=====================================================================================================================================\n";

        LostItem* current = head;
        while (current != nullptr) {
            cout << setw(6) << current->itemID
                 << setw(14) << current->description
                 << setw(20) << current->location
                 << setw(20) << current->date
                 << setw(14) << current->contactInfo
                 << setw(13) << current->email
                 << setw(19) << current->studentNumber
                 << setw(19) << current->status << endl;
            current = current->next;
        }
    }

    while (head != nullptr) {
        LostItem* temp = head;
        head = head->next;
        delete temp;
    }

    cout << "\n\n\t Press Enter to go back to the main menu...";
    cin.ignore();
    cin.get();
}

int main() // I N T  M A I N
{
    int MainChoice, loginChoice;

    Intro();

    do
    {
        ShowLoginMenu();
        cin >> loginChoice;

        switch (loginChoice)
        {
        case 1: 
            Login(); 
            break;
        case 2: 
            SignUp();
            continue;
        case 3: 
            cout << "\n\n\n\t Exiting the program. Thank you!\n";
            return 0;
        default:
            cout << "\n\n\n\t Invalid choice. Please select between 1-4.\n";
            cin.get();
        }
    } while (loginChoice != 4 && !loggedIn);

    if (loggedIn) 
    {
        do
        {
            ShowMainMenu();
            cin >> MainChoice;

            switch (MainChoice)
            {
            case 1:
                SubmitLostItem(lostItemsHead, email, studentNumber); 
                break;
            case 2:
                SearchForItems();
                break;
            case 3:
            	ListOfItems();
            	break;
            case 4:
                ViewClaimedItems();
                break;
            case 5:
                cout << "\n\n\n\t Exiting the program. GG!" << endl;
                break;
            default:
                cout << "\n\n\n\t Invalid choice. Please enter a number between 1 and 5." << endl;
            }
        } while (MainChoice != 5);
    }

    return 0;
}
