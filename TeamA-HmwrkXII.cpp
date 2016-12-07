#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<cstring>


using namespace std;

//funtion prototypes
void modify();
void add();
void delete_rec();
void display();
void display_all();

//sizes for record fields
const int NAME_SIZE = 60,
          ADD_SIZE = 60,
          LOC_SIZE = 100,
          PHONE_SIZE = 15,
          DATE_SIZE = 11;

//structure for customer records
struct accountHolder
{
    char name[NAME_SIZE];
    char address[ADD_SIZE];
    char location[LOC_SIZE];
    char phone[PHONE_SIZE];
    double balance;
    char date[DATE_SIZE];

};

int main()
{
	int choice;

	//display menu and get choice
    do
    {

		cout << "* * * * MAIN MENU * * * *\n\n"
		<< "1. Enter a new Customer Account\n"
		<< "2. Display a Customer Account\n"
		<< "3. Delete a Customer Account\n"
		<< "4. Change a Customer Account\n"
		<< "5. Display All Customer Accounts\n"
		<< "6. Exit the Program\n\n"
		<< "Enter your choice: ";
		cin >> choice;
		cin.ignore();

		while (choice > 6 || choice < 1)
		{
			cout << "Please Enter a valid choice: ";
			cin >> choice;
		}

        switch (choice)
        {
            case 1: add();
                    break;
            case 2: display();
                    break;
            case 3: cout << "Under Construction";
                    break;
            case 4: modify;
                    break;
            case 5: display_all();
                    break;
            case 6: return 0;
        }

    } while (choice != 6);

	return 0;
}

void add()
{
    accountHolder record;
    char again;

    fstream accounts("cust.dat", ios::out | ios::binary);

    if (!accounts)
    	cout << "Error opening file.\n";

    do
    {
	//get info
	cout << "Enter Name: ";
        cin.getline(record.name, NAME_SIZE);
        cout << "Enter Address: ";
        cin.getline(record.address, ADD_SIZE);
        cout << "Enter City, State, Zip: ";
        cin.getline(record.location, LOC_SIZE);
        cout << "Enter Phone Number: ";
        cin.getline(record.phone, PHONE_SIZE);
        cout << "Enter Balance: $";
        cin >> record.balance;
        cin.ignore();
        cout << "Enter Today's Date: ";
        cin.getline(record.date, DATE_SIZE);

        //write to file
        accounts.write(reinterpret_cast<char *>(&record), sizeof(record));
        cout << "Record written.";
        cout << "Would you like to add another file [Y/N]: ";
        cin >> again;
    } while (again == 'Y' || again == 'y');

    accounts.close();
}

void display_all()
{
    accountHolder record;
    char again;
    fstream accounts("cust.dat", ios::out | ios::binary);

    if (!accounts)
        cout << "Error opening file.\n";

    cout << "Accounts:\n\n";

    //read first record
    accounts.read(reinterpret_cast<char *>(&record), sizeof(record));

	while (!accounts.eof())
	{
		cout << "Name: " << record.name << endl;
		cout << "Address: " << record.address << endl;
		cout << "Location: " << record.location << endl;
		cout << "Phone Number: " << record.phone << endl;
		cout << "Balance: $" << record.balance << endl;
		cout << "Date: " << record.date << endl << endl;
		accounts.read(reinterpret_cast<char *>(&record), sizeof(record));
	}

    accounts.close();

}

void display()
{
    accountHolder record;
    long recNum;
	
    fstream accounts("cust.dat", ios::out | ios::binary);
	
	if (!accounts)
            cout << "Error opening file.\n";
	
	//get record number from user
	cout << "Enter the Record Number you want to view: ";
	cin >> recNum;
	
	//get to record chosen
	accounts.seekg(recNum * sizeof(record), ios::beg);
	accounts.read(reinterpret_cast<char *>(&record), sizeof(record));

	//display contents
	cout << "Name: " << record.name << endl;
	cout << "Address: " << record.address << endl;
	cout << "Location: " << record.location << endl;
	cout << "Phone Number: " << record.phone << endl;
	cout << "Balance: $" << record.balance << endl;
	cout << "Date: " << record.date << endl;


}

void modify()
{
	accountHolder record;
	long recNum;

	//open file
	fstream accounts("cust.dat", ios::in | ios::out |ios::binary);

	if (!accounts)
        cout << "Error opening file.";

	//get record number from user
	cout << "Enter the Record Number you want to edit: ";
	cin >> recNum;

	//get to record chosen
	accounts.seekg(recNum * sizeof(record), ios::beg);
	accounts.read(reinterpret_cast<char *>(&record), sizeof(record));

	//display current contents
	cout << "Name: " << record.name << endl;
	cout << "Address: " << record.address << endl;
	cout << "Location: " << record.location << endl;
	cout << "Phone Number: " << record.phone << endl;
	cout << "Balance: $" << record.balance << endl;
	cout << "Date: " << record.date << endl;

	//get new information
	cout << "Enter new information:\n";
	cout << "Enter Name: ";
        cin.getline(record.name, NAME_SIZE);
        cout << "Enter Address: ";
        cin.getline(record.address, ADD_SIZE);
        cout << "Enter City, State, Zip: ";
        cin.getline(record.location, LOC_SIZE);
        cout << "Enter Phone Number: ";
        cin.getline(record.phone, PHONE_SIZE);
        cin.ignore();
        cout << "Enter Balance: $";
        cin >> record.balance;
        cout << "Enter Today's Date: ";
        cin.getline(record.date, DATE_SIZE);

	//go back to the beginning of this record
	accounts.seekp(recNum * sizeof(record), ios::beg);

	//rewrite the record
	accounts.write(reinterpret_cast<char *>(&record), sizeof(record));

	accounts.close();
}
