#include<iostream>
#include<fstream>

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
          DATE_SIZE = 11,
          MAX_SIZE = 300;

//structure for customer records
struct AccountItem
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
	cout << "* * * * MAIN MENU * * * *\n\n"
		 << "1. Enter a new Customer Account\n"
		 << "2. Display a Customer Account\n"
		 << "3. Delete a Customer Account\n"
		 << "4. Change a Customer Account\n"
		 << "5. Display All Customer Accounts\n"
		 << "6. Exit the Program\n\n"
		 << "Enter your choice: ";
		 cin >> choice;

	while (choice > 6 && choice < 1)
	{
		cout << "Please Enter a valid choice: ";
		cin >> choice;
	}

	switch (choice)
	{
		case 1: add();
			    break;
		case 2: cout << "Under Construction";
	        	break;
		case 3: cout << "Under Construction";
				break;
		case 4: cout << "Testing";
				break;
		case 5: display_all();
				break;
		case 6: return 0;
	}

	return 0;
}

void add(AccountItem record)
{
	char name[NAME_SIZE], address[ADD_SIZE],
		 location[LOC_SIZE], phone[PHONE_SIZE],
		 date[DATE_SIZE];

	double balance;

	cout << "Enter Name: ";
	cin >> record.name;
	cout << "\nEnter Address: ";
	cin >> record.address;
	cout << "\nEnter City, State, Zip: ";
	cin >> record.location;
	cout << "\nEnter Phone Number: ";
	cin >> record.phone;
	cout << "\nEnter Balance: ";
	cin >> record.balance;
	cout << "\nEnter Today's Date: ";
	cin >> record.date;

	AccountItem record = {name, address, location, phone, balance, date};

	fstream accounts("cust.dat", ios::out | ios::binary);

	for (int count = 0;count < sizeof(record); count++)
		accounts.write(reinterpret_cast<char *>(&record),sizeof(record));

	cout << "Record written.";

	accounts.close();
}

void display_all()
{
	AccountItem record;

	fstream accounts("cust.dat", ios::in | ios::binary);
	accounts.read(reinterpret_cast<char *>(&record),sizeof(record));

	while (!accounts.eof())
	{
		cout << "Name: " << record.name << endl;
		cout << "Address: " << record.address << endl;
		cout << "Location: " << record.location << endl;
		cout << "Phone Number: " << record.phone << endl;
		cout << "Balance: " << record.balance << endl;
		cout << "Date: " << record.date << endl << endl;
		accounts.read(reinterpret_cast<char *>(&record),sizeof(record));
	}

	accounts.close();

}
