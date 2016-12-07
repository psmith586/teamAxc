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
			cin.ignore();
		}

        switch (choice)
        {
            case 1: add();
                    break;
            case 2: display();
                    break;
            case 3: delete_rec();
                    break;
            case 4: modify();
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

    fstream accounts("cust.dat", ios::app | ios::binary);

	if (!accounts)
        cout << "Error opening file.\n";

	do
	{
	    cout << "Enter the following information:\n";
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

        cout << "\nRecord written.";
        cout << "Would you like to add another file [Y/N]: ";
        cin >> again;
        cin.ignore();
	} while (again == 'Y' || again == 'y');

    accounts.close();
}

void display_all()
{
	accountHolder record;
    fstream accounts("cust.dat", ios::in | ios::binary);

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

    fstream accounts("cust.dat", ios::in | ios::binary);

	if (!accounts)
        cout << "Error opening file.\n";

	//get record number from user
	cout << "Enter the Record Number you want to view[starting from 1]: ";
	cin >> recNum;
	recNum -= 1;

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

	accounts.close();

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
	cout << "Enter the Record Number you want to edit[starting from 1]: ";
	cin >> recNum;
	recNum -= 1;
	cin.ignore();

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

	//go back to the beginning of this record
	accounts.seekp(recNum * sizeof(record), ios::beg);

	//rewrite the record
	accounts.write(reinterpret_cast<char *>(&record), sizeof(record));

	accounts.close();
}

void delete_rec()
{
	accountHolder record;
	long recNum;

	//open file and temp
	fstream accounts("cust.dat", ios::in | ios::out | ios::binary);
	fstream temp("temp.dat", ios::out | ios::binary);

	if (!accounts || !temp)
        cout << "Error opening one of the files.";

	//get record number from user
	cout << "Enter the Record Number you want to delete[starting from 1]: ";
	cin >> recNum;
	recNum -= 1;

	//move to the position of the record and read it
	accounts.seekg(recNum * sizeof(record), ios::beg);
	accounts.read(reinterpret_cast<char *>(&record), sizeof(record));

	//change 1st field to null
	record.name[0] = '\0';

	//rewrite the record
	accounts.seekp(recNum * sizeof(record), ios::beg);
	accounts.write(reinterpret_cast<char *>(&record), sizeof(record));

	//return to the beginning of file
	accounts.seekg(0L, ios::beg);

	//reread 1st record
	accounts.read(reinterpret_cast<char *>(&record), sizeof(record));

	//write the records except the flagged one to temp
	while (!accounts.eof())
	{
		if (record.name[0] != '\0')
			temp.write(reinterpret_cast<char *>(&record), sizeof(record));

		accounts.read(reinterpret_cast<char *>(&record), sizeof(record));

	}

	accounts.close();
	temp.close();
	remove("cust.dat");
	rename("temp.dat", "cust.dat");

}
