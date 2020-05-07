#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;
//Counters to keep track of customers, destinations, and shipments 
int countCustomers = 0;
int countDestination = 0;
int countShipments = 0;

//Arrays to store customer information
string custName[100];
int custID[100];

//Arrays to store distination information
int destId[100];
string destName[100];
double firstHalfKilo[100];
double eachAddKilo[100];

//Arrays to store shipment information
int shippersID[100];
int shippingCustomersID[100];
int shippingDestination[100];
double shipWeight[100];
double shipCost[100];

//Prints main menu
void menu()
{
	cout << "\nMain Menu\n";
	cout << "---------\n";
	cout << "1. Add new customer\n";
	cout << "2. Add new destination\n";
	cout << "3. Add new shipment\n";
	cout << "4. Edit existing shipment\n";
	cout << "5. Delete existing shipment\n";
	cout << "6. Produce invoice\n";
	cout << "7. Exit\n\n";
	cout << "PLease select a choice from the menu:";
}
//Reads Customers from file and populates customer information arrays
void readCustomersFromFile()
{
	ifstream infile;
	infile.open("customers.txt");
	int customersInfile = 0;
	if (infile)
	{
		while (infile >> custName[customersInfile] >> custID[customersInfile])
		{
			customersInfile++;
		}
	}
	countCustomers = customersInfile;
	infile.close();
}
void readDestinationsFromFile()
{
	ifstream infile;
	infile.open("destinations.txt");
	countDestination = 0;
	if (infile)
	{
		while (infile >> destId[countDestination] >> destName[countDestination] >> firstHalfKilo[countDestination] >> eachAddKilo[countDestination])
		{
			countDestination++;
		}
	}
	infile.close();
}
void readShipmentsFromFile()
{
	ifstream infile;
	infile.open("shipments.txt");
	countShipments = 0;
	if (infile)
	{
		while (infile >> shippersID[countShipments] >> shippingCustomersID[countShipments] >> shippingDestination[countShipments] >> shipWeight[countShipments]>> shipCost[countShipments])
		{
			countShipments++;
		}
	}
	infile.close();
}
void addCustomer()
{
	string input;
	char anotherCustomer = 'y';
	bool match = false;
	if (countCustomers == 0)
	{
		ofstream outfile;
		outfile.open("customers.txt");
		cout << "Please input the customers name:";
		cin >> input;
		outfile << input << "\t" << countCustomers+1001 << "\n";
		outfile.close();
		cout << "Would you like to add another customer (y/n):";
		cin >> anotherCustomer;
	}
	while (anotherCustomer=='Y'||anotherCustomer=='y')
	{
		match = false;
		anotherCustomer = 'y';
		cout << "Please input the customers name:";
		cin >> input;
		readCustomersFromFile();
		ofstream outfile;
		outfile.open("customers.txt",ios::app);
		for (int i = 0; i < countCustomers; i++)
		{
			if (custName[i] == input)
				match = true;
		}
		if (!match)
		{
			outfile << input << "\t" << countCustomers + 1001 << "\n";
		}
		else
		{
			cout << "The name already exist.\n";
		}
		switch (anotherCustomer)
		{
		case 'y':
		case 'Y':
			break;
		case 'n':
		case 'N':
			cout << "Returning to main menu\n";
			break;
		default: cout << "\nInvalid Choice Try Again!\n";
		}
		cout << "Would you like to add another customer (y/n):";
		cin >> anotherCustomer;
	}
}
void addNewDestination() 
{
	string input;
	double input2;
	char anotherDest='y';
	bool match = false;
	
	if (countDestination == 0)
	{
		ofstream outfile;
		outfile.open("destinations.txt");
		
		outfile << countDestination + 1001<<"\t";
		cout << "Please input distantion name:";
		cin >>input;
		outfile << input << "\t";
		cout << "Please first half kilo price:";
		cin >>input2;
		outfile << input2 << "\t";
		cout << "Please input additional kilo price:";
		cin >> input2;
		outfile << input2 << "\n";
		countDestination++;
		cout << "Would you like to add another destination (y/n):";
		cin >> anotherDest;
		outfile.close();
	}
	while (anotherDest == 'y' || anotherDest == 'Y')
	{
		match = false;
		readDestinationsFromFile();
		ofstream outfile;
		outfile.open("destinations.txt",ios::app);
		cout << "Please input distantion name:";
		cin >> input;
		for (int i=0; i < countDestination; i++)
		{
			if (input == destName[i])
				match = true;
		}
		if (!match)
		{
			outfile << countDestination + 1001 << "\t";
			outfile << input << "\t";
			cout << "Please first half kilo price:";
			cin >> input2;
			outfile << input2 << "\t";
			cout << "Please input additional kilo price:";
			cin >> input2;
			outfile << input2 << "\n";
		}
		else
		{
			cout << "The distination already exist.\n";
		}
		cout << "\nWould you like add anotther destination (y/n):";
		cin >> anotherDest;
		if (anotherDest == 'n' || anotherDest == 'N')
		{
			cout << "Returning to main menu\n";
		}
		else if (anotherDest == 'y' || anotherDest == 'Y')
		{
		}
		else
		{
			cout << "\nInvalid Choice Try Again!\n";
		}
		outfile.close();
	}
}
void addNewShipment()
{
	readCustomersFromFile();
	readDestinationsFromFile();
	bool custExists = false;
	bool desExists = false;
	int customerID;
	int destinationID;
	double shipmentWeight;
	double shipmentCost=0;
	char anotherShipment = 'y';
	
	if (countShipments == 0)
	{
		int customerPosition;
		int destinationPostion;
		ofstream outfile;
		outfile.open("shipments.txt");
		cout << "Please enter a customer ID:";
		cin >> customerID;
		do {
			for (int i = 0; i < countCustomers; i++)
				if (custID[i] == customerID) {
					custExists = true;
					customerPosition = i;
				}
			if (!custExists)
			{
				cout << "\nCustomer does not exist please insert a valid customer ID:";
				cin >> customerID;
			}
		} while (!custExists);
		cout << "Please enter a Destination ID:";
		cin >> destinationID;
		do {
			for (int i = 0; i < countDestination; i++)
				if (destId[i] == destinationID) {
					desExists = true;
					destinationPostion = i;
				}
			if (!desExists)
			{
				cout << "\nDestination does not exist please insert a valid Destination ID:";
				cin >> destinationID;
			}
		} while (!desExists);
		cout << "Please input shipment weight:";
		cin >> shipmentWeight;
		double temp = shipmentWeight - 0.5;
		shipmentCost += firstHalfKilo[destinationPostion];
		if (temp > 0)
			shipmentCost += ceil(temp)*eachAddKilo[destinationPostion];
		outfile << countShipments + 1001 << "\t" << customerID << "\t"<<destinationID<<"\t" << shipmentWeight << "\t" << shipmentCost << "\n";
		cout << "\nShipment ID: " << countShipments + 1001 << "\n";
		cout << "==================\n\n";

		cout << "Customer ID: " << customerID << endl;
		cout << "Customer Name: " << custName[customerPosition] << endl;
		cout << "==================\n\n";

		cout << "Destination ID: " << destinationID << endl;
		cout << "Destination Name: " << destName[destinationPostion] << endl;
		cout << "==================\n\n";

		cout << "Shipment Detailes:\n";
		cout << left << setw(21) << "First Half Kilo" << left << setw(24) << "Each.Add.Kilo" << left << setw(25) << "Shipment Weight" << "Cost\n";
		cout << left << setw(21) << "---------------" << left << setw(24) << "-------------" << left << setw(25) << "---------------" << "----\n";
		cout << left << setw(21) << firstHalfKilo[destinationPostion] << left << setw(24) << eachAddKilo[destinationPostion] << left << setw(25) << shipmentWeight << shipmentCost<<"\n";


		do {
			cout << "\n\nWould you like to enter another shipment(y/n):";
			cin >> anotherShipment;
			if (anotherShipment == 'n' || anotherShipment == 'N')
			{
				cout << "Returning to main menu\n";
			}
			else if (anotherShipment == 'y' || anotherShipment == 'Y')
			{
			}
			else
			{
				cout << "\nInvalid Choice Try Again!\n";
			}
		} while (anotherShipment != 'y' && anotherShipment != 'Y' && anotherShipment != 'n' && anotherShipment != 'Y');
	}
	while (anotherShipment == 'y' || anotherShipment == 'Y')
	{
		readShipmentsFromFile();
		int customerPosition;
		int destinationPostion;
		ofstream outfile;
		outfile.open("shipments.txt",ios::app);
		cout << "Please enter a customer ID:";
		cin >> customerID;
		do {
			for (int i = 0; i < countCustomers; i++)
				if (custID[i] == customerID) {
					custExists = true;
					customerPosition = i;
				}
			if (!custExists)
			{
				cout << "\nCustomer does not exist please insert a valid customer ID:";
				cin >> customerID;
			}
		} while (!custExists);
		cout << "Please enter a Destination ID:";
		cin >> destinationID;
		do {
			for (int i = 0; i < countDestination; i++)
				if (destId[i] == destinationID) {
					desExists = true;
					destinationPostion = i;
				}
			if (!desExists)
			{
				cout << "\nDestination does not exist please insert a valid Destination ID:";
				cin >> destinationID;
			}
		} while (!desExists);
		cout << "Please input shipment weight:";
		cin >> shipmentWeight;
		double temp = shipmentWeight - 0.5;
		shipmentCost += firstHalfKilo[destinationPostion];
		if (temp > 0)
			shipmentCost += ceil(temp) * eachAddKilo[destinationPostion];
		outfile << countShipments + 1001 << "\t" << customerID << "\t" << destinationID << "\t" << shipmentWeight << "\t" << shipmentCost << "\n";
		cout << "\nShipment ID: " << countShipments + 1001 << "\n";
		cout << "==================\n\n";

		cout << "Customer ID: " << customerID << endl;
		cout << "Customer Name: " << custName[customerPosition] << endl;
		cout << "==================\n\n";

		cout << "Destination ID: " << destinationID << endl;
		cout << "Destination Name: " << destName[destinationPostion] << endl;
		cout << "==================\n\n";

		cout << "Shipment Detailes:\n";
		cout << left << setw(21) << "First Half Kilo" << left << setw(24) << "Each.Add.Kilo" << left << setw(25) << "Shipment Weight" << "Cost\n";
		cout << left << setw(21) << "---------------" << left << setw(24) << "-------------" << left << setw(25) << "---------------" << "----\n";
		cout << left << setw(21) << firstHalfKilo[destinationPostion] << left << setw(24) << eachAddKilo[destinationPostion] << left << setw(25) << shipmentWeight << shipmentCost << "\n";

		do {
			cout << "\n\nWould you like to enter another shipment(y/n):";
			cin >> anotherShipment;
			if (anotherShipment == 'n' || anotherShipment == 'N')
			{
				cout << "Returning to main menu\n";
			}
			else if (anotherShipment == 'y' || anotherShipment == 'Y')
			{
			}
			else
			{
				cout << "\nInvalid Choice Try Again!\n";
			}
		} while (anotherShipment != 'y' && anotherShipment != 'Y' && anotherShipment != 'n' && anotherShipment != 'Y');
	}
}
void editExistingShipment()
{
	readShipmentsFromFile();
	char anotherEdit = 'y';
	int shipIDEdit;
	bool match = false;
	int shipmentPostion;
	int menuChoice;
	do
	{
		cout << "Please enter the shipment ID for the shipment you would like to edit:";
		cin >> shipIDEdit;
		for (int i = 0; i < countShipments; i++)
		{
			if (shipIDEdit == shippersID[i])
			{
				match = true;
				shipmentPostion = i;
			}
		}
		int newCustID;
		int newDestID;
		double newShipWeight;
		bool custExists = false;
		bool desExists = false;
		int customerPosition;
		int destinationPostion;
		readCustomersFromFile();
		readDestinationsFromFile();
		if (match)
		{
			ofstream outfile;
			outfile.open("shipments.txt");
			cout << "\n1. Edit customer ID\n";
			cout << "2. Edit the destination ID\n";
			cout << "3. Edit the shiment weight\n\n";
			cout << "What would you like to edit:";
			cin >> menuChoice;
			int i = 0;
			double newShipingCost = 0;
			switch (menuChoice)
			{
			case 1:
				cout << "Please enter a customer ID:";
				cin >> newCustID;
				do {
					for (int i = 0; i < countCustomers; i++)
						if (custID[i] == newCustID) {
							custExists = true;
							customerPosition = i;
						}
					if (!custExists)
					{
						cout << "\nCustomer does not exist please insert a valid customer ID:";
						cin >> newCustID;
					}
				} while (!custExists);
				shippingCustomersID[shipmentPostion] = newCustID;
				while (i < countShipments) {
					outfile << shippersID[i] << "\t" << shippingCustomersID[i] << "\t" << shippingDestination[i] << "\t" << shipWeight[i] << "\t" << shipCost[i] << "\n";
					i++;
				}
				cout << "Customer ID Edited Sucessfully\n";
				outfile.close();

				break;
			case 2:
				cout << "Please enter a Destination ID:";
				cin >> newDestID;
				do {
					for (int i = 0; i < countDestination; i++)
						if (destId[i] == newDestID) {
							desExists = true;
							destinationPostion = i;
						}
					if (!desExists)
					{
						cout << "\nDestination does not exist please insert a valid Destination ID:";
						cin >> newDestID;
					}
				} while (!desExists);
				shippingDestination[shipmentPostion] = newDestID;

				while (i < countShipments) {
					outfile << shippersID[i] << "\t" << shippingCustomersID[i] << "\t" << shippingDestination[i] << "\t" << shipWeight[i] << "\t" << shipCost[i] << "\n";
					i++;
				}
				cout << "Destination ID Edited Sucessfully\n";
				outfile.close();
				break;
			case 3:
				cout << "Please enter weight:";
				cin >> newShipWeight;
				shipWeight[shipmentPostion] = newShipWeight;
				newShipingCost += firstHalfKilo[shipmentPostion];
				newShipWeight -= .05;
				if (newShipWeight > 0)
					newShipingCost += ceil(newShipingCost) * newShipWeight;
				shipCost[shipmentPostion] = newShipingCost;
				while (i < countShipments) {
					outfile << shippersID[i] << "\t" << shippingCustomersID[i] << "\t" << shippingDestination[i] << "\t" << shipWeight[i] << "\t" << shipCost[i] << "\n";
					i++;
				}
				cout << "Shipment Edited Sucessfully\n";
				outfile.close();
				break;
			default: cout << "Invalid Choice!\n";
			}
		}
		else {
			cout << "Shipment Does not Exist in System!\n";
		}
		do {
			cout << "\n\nWould you like to edit another shipment(y/n):";
			cin >> anotherEdit;
			if (anotherEdit == 'n' || anotherEdit == 'N')
			{
				cout << "Returning to main menu\n";
			}
			else if (anotherEdit == 'y' || anotherEdit == 'Y')
			{
			}
			else
			{
				cout << "\nInvalid Choice Try Again!\n";
			}
		} while (anotherEdit != 'y' && anotherEdit != 'Y' && anotherEdit != 'n' && anotherEdit != 'Y');

	}while (anotherEdit == 'y' || anotherEdit == 'Y');
}
void deleteExistingShipment()
{
	readShipmentsFromFile();
	char anotherDelete = 'y';
	int shipIDEdit;
	bool match = false;
	int shipmentPostion;
	do
	{
		cout << "Please enter the shipment ID for the shipment you would like to edit:";
		cin >> shipIDEdit;
		for (int i = 0; i < countShipments; i++)
		{
			if (shipIDEdit == shippersID[i])
			{
				match = true;
				shipmentPostion = i;
			}
		}
		if (match)
		{
			ofstream outfile;
			outfile.open("shipments.txt");
			for (int i = 0; i < countShipments; i++)
			{
				if(i!=shipmentPostion)
					outfile << shippersID[i] << "\t" << shippingCustomersID[i] << "\t" << shippingDestination[i] << "\t" << shipWeight[i] << "\t" << shipCost[i] << "\n";
			}
		}
		else {
			cout << "Shipment Does not Exist in System!\n";
		}
		do {
			cout << "\n\nWould you like to edit another shipment(y/n):";
			cin >> anotherDelete;
			if (anotherDelete == 'n' || anotherDelete == 'N')
			{
				cout << "Returning to main menu\n";
			}
			else if (anotherDelete == 'y' || anotherDelete == 'Y')
			{
			}
			else
			{
				cout << "\nInvalid Choice Try Again!\n";
			}
		} while (anotherDelete != 'y' && anotherDelete != 'Y' && anotherDelete != 'n' && anotherDelete != 'Y');
	} while (anotherDelete == 'y' || anotherDelete == 'Y');
}
void produceInvoice()
{
	readShipmentsFromFile();
	readDestinationsFromFile();
	readCustomersFromFile();
	char anotherDelete = 'y';
	int shipIDEdit;
	bool match = false;
	int shipmentPostion;

	string destNameLocal;
	string custNameLocal;

	cout << "Please enter the shipment ID for the shipment you would have an invoice for:";
	cin >> shipIDEdit;
	for (int i = 0; i < countShipments; i++)
	{
		if (shipIDEdit == shippersID[i])
		{
			match = true;
			shipmentPostion = i;
		}
	}
	if (match)
	{
		for (int i = 0; i < countDestination; i++)
		{
			if (shippingDestination[shipmentPostion] == destId[i])
			{
				destNameLocal = destName[i];
			}
		}
		for (int i = 0; i < countCustomers; i++)
		{
			if (shippingCustomersID[shipmentPostion] == custID[i])
			{
				custNameLocal = custName[i];
			}
		}
		cout << "\n\nDestination ID: " << shippingDestination[shipmentPostion]<<"\n";
		cout << "Destination name: " << destNameLocal <<"\n\n";

		cout << left << setw(15) << "Ship. ID" << left << setw(15) << "Cust. ID" << left << setw(17) << "Cust. Name" << left << setw(16) << "Ship. Weight" << "Ship. Cost\n";
		cout << left << setw(15) << "========" << left << setw(15) << "=========" << left << setw(17) << "=========" << left << setw(16) << "============" << "==========\n";
		cout << left << setw(15) << shipIDEdit << left << setw(15) << shippingCustomersID[shipmentPostion] << left << setw(17) << custNameLocal << left << setw(16) << shipWeight[shipmentPostion] << shipCost[shipmentPostion]<<"\n\n";

	}
	else {
		cout << "Shipment Does not Exist in System!\n";
	}
	system("pause");
}
int main()
{
	bool exit = false;
	int menuChoice;
	int countCustomers = 0;
	cout << "---------------------------\n";
	cout << "Shipping Information System\n";
	cout << "---------------------------\n";
	do {
		menu();
		cin >> menuChoice;
		switch (menuChoice) {
		case 1:
			addCustomer();
			break;
		case 2: 
			addNewDestination();
			break;
		case 3: 
			addNewShipment();
			break;
		case 4:
			editExistingShipment();
			break;
		case 5:
			deleteExistingShipment();
			break;
		case 6:
			produceInvoice();
			break;
		case 7:
			cout << "\nThank You for using Shipping Information System!\n";
			exit = true;
			break;
		default:
			cout << "\nINVALID SELECTION RETURNING TO MAIN MENU\n";
		}

	} while (!exit);

}


