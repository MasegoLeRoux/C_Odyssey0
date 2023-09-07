#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class AccountQuery
{
private:
    char accountNumber[20];
    char firstName[10];
    char lastName[10];
    float totalBalance;

public:
    void readData();
    void showData();
    void writeRecord();
    void readRecord();
    void searchRecord();
    void editRecord();
    void deleteRecord();
};

void AccountQuery::readData()
{
    cout << "Enter Account Number: ";
    cin >> accountNumber;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Balance: ";
    cin >> totalBalance;
    cout << endl;
}

void AccountQuery::showData()
{
    cout << "Account Number: " << accountNumber << endl;
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Current Balance: Rs. " << totalBalance << endl;
    cout << "-------------------------------" << endl;
}

void AccountQuery::writeRecord()
{
    ofstream outFile;
    outFile.open("record.bank", ios::binary | ios::app);
    readData();
    outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    outFile.close();
}

void AccountQuery::readRecord()
{
    ifstream inFile;
    inFile.open("record.bank", ios::binary);
    if (!inFile)
    {
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
    }
    cout << "\n****Data from file****" << endl;
    while (!inFile.eof())
    {
        if (inFile.read(reinterpret_cast<char*>(this), sizeof(*this)) > 0)
        {
            showData();
        }
    }
    inFile.close();
}

void AccountQuery::searchRecord()
{
    int n;
    ifstream inFile;
    inFile.open("record.bank", ios::binary);
    if (!inFile)
    {
        cout << "\nError in opening! File Not Found!!" << endl;
        return;
    }
    inFile.seekg(0, ios::end);
    int count = inFile.tellg() / sizeof(*this);
    cout << "\n There are " << count << " records in the file";
    cout << "\n Enter Record Number to Search: ";
    cin >> n;
    inFile.seekg((n - 1) * sizeof(*this));
    inFile.read(reinterpret_cast<char*>(this), sizeof(*this));
    showData();
}

void AccountQuery::editRecord()
{
    int n;
    fstream ioFile;
    ioFile.open("record.bank", ios::in | ios::binary);
    if (!ioFile)
    {
        cout << "\nError in opening! File Not Found!!" << endl;
        return;
    }
    ioFile.seekg(0, ios::end);
    int count = ioFile.tellg() / sizeof(*this);
    cout << "\n There are " << count << " records in the file";
    cout << "\n Enter Record Number to edit: ";
    cin >> n;
    ioFile.seekg((n - 1) * sizeof(*this));
    ioFile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout << "Record " << n << " has the following data" << endl;
    showData();
    ioFile.close();
    ioFile.open("record.bank", ios::out | ios::in | ios::binary);
    ioFile.seekp((n - 1) * sizeof(*this));
    cout << "\nEnter data to Modify " << endl;
    readData();
    ioFile.write(reinterpret_cast<char*>(this), sizeof(*this));
}

void AccountQuery::deleteRecord()
{
    int n;
    ifstream inFile;
    inFile.open("record.bank", ios::binary);
    if (!inFile)
    {
        cout << "\nError in opening! File Not Found!!" << endl;
        return;
    }
    inFile.seekg(0, ios::end);
    int count = inFile.tellg() / sizeof(*this);
    cout << "\n There are " << count << " records in the file";
    cout << "\n Enter Record Number to Delete: ";
    cin >> n;
    fstream tmpFile;
    tmpFile.open("tmpfile.bank", ios::out | ios::binary);
    inFile.seekg(0);
    for (int i = 0; i < count; i++)
    {
        inFile.read(reinterpret_cast<char*>(this), sizeof(*this));
        if (i == (n - 1))
            continue;
        tmpFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    inFile.close();
    tmpFile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
}

int main()
{
    AccountQuery A;
    int choice;
    cout << "***Account Information System***" << endl;
    while (true)
    {
        cout << "Select one option below ";
        cout << "\n\t1-->Add record to file";
        cout << "\n\t2-->Show record from file";
        cout << "\n\t3-->Search Record from file";
        cout << "\n\t4-->Update Record";
        cout << "\n\t5-->Delete Record";
        cout << "\n\t6-->Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            A.writeRecord();
            break;
        case 2:
            A.readRecord();
            break;
        case 3:
            A.searchRecord();
            break;
        case 4:
            A.editRecord();
            break;
        case 5:
            A.deleteRecord();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
