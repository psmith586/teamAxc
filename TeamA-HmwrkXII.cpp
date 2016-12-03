#include<iostream>
#include<fstream>

using namespace std;

//funtion prototypes
void Modify();
void Add();

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
		case 1: Add();
			break;
		case 2: cout << "Under Construction";
	        	break;
		case 3: cout << "Under Construction";
		        break;
		case 4: Modify();
			break;
		case 5: cout << "Under Construction";
			break;
		case 6: return 0;
	}

	return 0;
}
