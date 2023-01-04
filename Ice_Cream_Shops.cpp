#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int NO_OF_SALES_PERSON = 5;
const int NO_OF_WEEK = 4;
const int NO_ICE_CREAM_TYPE = 6;

struct salesPersonRecord
{
	string Id;
	string name;
	double weeklyCollection[4];
	double totalSale;	
};

struct IceCream
{
	string type;
	double price;
	double weeklyCollection[4];
	double totalSale;
};

void get_salesPerson_ID (ifstream& infile, salesPersonRecord * );
void display_menu (int *choice);
void display_iceCream_menu(IceCream []);
void sales_Information(salesPersonRecord salesMan[], IceCream list[]);
void total_sales (salesPersonRecord salesMan[]);
void total_sales (IceCream list[]);
void weekly_Collection (salesPersonRecord salesMan[], IceCream list[]);
void print_report (ofstream& outfile, salesPersonRecord salesMan[]);
void print_report (ofstream& outfile, IceCream list[]);
void highest_collection(ofstream& outfile, salesPersonRecord salesMan[]);
void highest_collection(ofstream& outfile, IceCream list[]);
void back_to_menu();
void display_sales_person(salesPersonRecord salesMan[]);

int main()
{
	system ("title Ice Cream Shops");
	
	int choice;
	ifstream infile;
	ofstream outfile;
	
	salesPersonRecord salesMan[NO_OF_SALES_PERSON];
	IceCream list[NO_ICE_CREAM_TYPE] = {{"single cone", 1.00},
										{"double cone", 2.00},
										{"small cup", 1.50},
										{"large cup", 2.50},
										{"banana split", 4.00},
										{"waffle", 3.00}};

	infile.open("SalesPersonInfo.txt");
	if (infile.fail())
	{
		cout << "Cannot open the salesPerson file."
			 << endl;
		return 1;
	}
	get_salesPerson_ID (infile, &salesMan[0]);
	infile.clear();
	infile.close();
	
	do{
		display_menu(&choice);
		
		switch (choice){
			case 0: break;
		
			case 1:	system("cls");
					display_iceCream_menu(list);
					back_to_menu();
					break;
			
			case 2: system("cls");
					display_sales_person(salesMan);
					back_to_menu();
					break;
						
			case 3:	system("cls");
					sales_Information(salesMan, list);
					total_sales(salesMan);
					total_sales(list);
					back_to_menu();
					break;
					
			case 4:	system("cls");
					outfile.open("weekly_sales_report.txt");
			
					print_report(outfile, salesMan);
					print_report(outfile, list);
					highest_collection (outfile, salesMan);
					highest_collection (outfile, list);
					outfile.close();
					
					back_to_menu();
					break;
			
			default:
				system("cls");
				cout << endl << "Error! You have input an incorrect value." << endl << endl;
		}
		
	}while (choice != 0);

	return 0;
}

void display_menu (int *choice)
{
	cout << "+----------------------------------+" << endl;
	cout << "|                                  |" << endl;
	cout << "|         Ice Cream System         |" << endl;
	cout << "|     (Created By Group Dhawi)     |" << endl;
	cout << "|                                  |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "|                                  |" << endl;
	cout << "|   (1) View ice cream menu        |" << endl;
	cout << "|   (2) Display Salesperson        |" << endl;
	cout << "|   (3) Enter Sales Information    |" << endl;
	cout << "|   (4) Display weekly collection  |" << endl;
	cout << "|       and print report           |" << endl;
	cout << "|   (0) Exit                       |" << endl;
	cout << "+----------------------------------+" << endl;
	
	cout << endl << "Please enter a number of your choice from the menu: ";
	cin >> *choice;
}

void get_salesPerson_ID (ifstream& infile, salesPersonRecord *temp)
{
	int week;
	for (int index = 0; index < NO_OF_SALES_PERSON; index++)
	{
		getline (infile, temp[index].Id);
		getline (infile, temp[index].name);
		for (week = 0; week < NO_OF_WEEK; week++)
			temp[index].weeklyCollection[week] = 0.0;	
	}
}

void display_iceCream_menu (IceCream list[])
{
	cout << "\nIce Cream menu:\n" << endl;
	cout << "+-------------------------------------------------------+" << endl;
	cout << "|No.	|type          		|Price			|" 			<< endl;
	cout << "+-------------------------------------------------------+" << endl;

	for(int i = 0; i < NO_ICE_CREAM_TYPE; i++)
	{
		cout << "| " << i+1 << "\t " << left << setw(12)<< list[i].type << "\t\t"; 
		cout << fixed << showpoint << setprecision(2);
		cout << " RM " << list[i].price << "\t\t";
		
		cout << "|" << endl;	
		cout << "|" << right << setw(56) << "|"<< endl;
	}
	cout << "+-------------------------------------------------------+" << endl;
}

void sales_Information (salesPersonRecord salesMan[], IceCream list[])
{
	int week, type, quantity, index; 
	int salespersonIndex, typeIndex;
	bool isExist ;
	string tempId;

	cout << "Enter week (1-4)/(-1 to exit): ";
	cin >> week;
	
	while (week < 1 || week > 4){
		if (week == -1)
			break;
		cout << "Invalid! " << endl;
		cout << "Enter week (1-4)/(-1 to exit): ";
		cin >> week;

		}
	while (week != -1)
	{
		isExist = false;
		while(!isExist){
			
			cout << "Enter salesperson ID: ";
			cin >> tempId;
			cout << endl;

			for (index = 0; index < NO_OF_SALES_PERSON; index++){
				if(tempId == salesMan[index].Id ){
					salespersonIndex = index;
					isExist = true;
					break;
				}
			}
			if(index == NO_OF_SALES_PERSON)
			cout << "Invalid Id!" << endl;
		}
	
		cout << "1. single cone" 
			 << "\n2. double cone " 
			 << "\n3. small cup" 
			 << "\n4. large cup "
			 << "\n5. banana split" 
			 << "\n6. ice cream waffle\n";
		cout << "Select type (1-6): ";
		cin >> type;
	
		while(type < 1 || type > 6){
			cout << "Invalid! \n";
			cout << "Select type (1-6): ";
			cin >> type;
		}
		typeIndex = type - 1;
	
		cout << endl;
		cout << "Enter quantity: ";
		cin >> quantity;
		cout << endl << endl;
	
		salesMan[salespersonIndex].weeklyCollection[week-1] += (quantity * list[typeIndex].price); 
		list[typeIndex].weeklyCollection[week-1] += (quantity * list[typeIndex].price);

		system("cls");
	
		cout << "Enter week (1-4)/(-1 to exit): ";
		cin >> week;
		
		while (week < 1 || week > 4){
			if (week == -1)
				break;
			cout << "Invalid! " << endl;
			cout << "Enter week (1-4)/(-1 to exit): ";
			cin >> week;
			

		}
	}
}

void total_sales (salesPersonRecord salesMan[])
{
	for (int i=0; i < NO_OF_SALES_PERSON; i++){
		salesMan[i].totalSale = 0;	

		for(int j=0; j < NO_OF_WEEK; j++){
			salesMan[i].totalSale += salesMan[i].weeklyCollection[j];
		}	
	}
}

void total_sales (IceCream list[])
{
	for (int i=0; i < NO_ICE_CREAM_TYPE; i++){
		list[i].totalSale=0;
		
		for(int j=0; j <  NO_OF_WEEK; j++){
			list[i].totalSale += list[i].weeklyCollection[j];
		}	
	}
}

void print_report (ofstream& outfile, salesPersonRecord salesMan[])
{
	int index;
	int week;
	
	cout << "\t\t------------------  weekly Sales Report -------------------" << endl << endl;
	cout << "ID			Week 1		Week 2		Week 3		Week 4		Total" << endl;
	cout << "______________________________________________________________________________________________" << endl;
	
	for (index = 0; index < NO_OF_SALES_PERSON; index++){
		cout << left << setw(20) << salesMan[index].Id << "\t";
		
		for (week = 0; week < NO_OF_WEEK; week++){
			cout << fixed << showpoint << setprecision(2);
			cout << salesMan[index].weeklyCollection[week] << "\t\t";	
		}
		cout << salesMan[index].totalSale << endl;
	}	
	
	outfile << "\t\t------------------  weekly Sales Report -------------------" << endl << endl;
	outfile << "ID			Week 1		Week 2		Week 3		Week 4		Total" << endl;
	outfile << "______________________________________________________________________________________________" << endl;
	
	for (index = 0; index < NO_OF_SALES_PERSON; index++){
		outfile << left << setw(20) << salesMan[index].Id << "\t";
		
		for (week = 0; week < NO_OF_WEEK; week++){
			outfile << fixed << showpoint << setprecision(2);
			outfile << salesMan[index].weeklyCollection[week] << "\t\t";	
		}
		outfile << salesMan[index].totalSale << endl;
	}	
}

void print_report (ofstream& outfile, IceCream list[])
{
	int index;
	int week;
	
	cout << endl << endl ;
	cout << "Type			Week 1		Week 2		Week 3		Week 4		Total" << endl;
	cout << "______________________________________________________________________________________________" << endl;
	
	for (index = 0; index < NO_ICE_CREAM_TYPE; index++){
		cout << left << setw(20) << list[index].type << "\t";
		
		for (week = 0; week < NO_OF_WEEK; week++){
			cout << fixed << showpoint << setprecision(2);
			cout << list[index].weeklyCollection[week] << "\t\t";	
		}
		cout << list[index].totalSale << endl;
	}	
	cout << endl << endl;
	
	outfile << endl << endl ;
	outfile << "Type			Week 1		Week 2		Week 3		Week 4		Total" << endl;
	outfile << "______________________________________________________________________________________________" << endl;
	
	for (index = 0; index < NO_ICE_CREAM_TYPE; index++){
		outfile << left << setw(20) << list[index].type << "\t";
		
		for (week = 0; week < NO_OF_WEEK; week++){
			outfile << fixed << showpoint << setprecision(2);
			outfile << list[index].weeklyCollection[week] << "\t\t";	
		}
		outfile << list[index].totalSale << endl;
	}	
	outfile << endl << endl ;
}

void highest_collection (ofstream& outfile, salesPersonRecord salesMan[])
{
	int index;
	int highestIndex = 0;
	
	for (index = 0; index < NO_OF_SALES_PERSON; index++){
		if (salesMan[highestIndex].totalSale < salesMan[index].totalSale)
			highestIndex = index;
	}
	
	cout	<< "Highest Sale by Salesperson: Id = "
			<< salesMan[highestIndex].Id
			<< ", Amount = RM " << salesMan[highestIndex].totalSale
			<< endl;
	
	outfile << "Highest Sale by Salesperson: Id = "
			<< salesMan[highestIndex].Id
			<< ", Amount = RM " << salesMan[highestIndex].totalSale
			<< endl;
}

void highest_collection (ofstream& outfile, IceCream list[])
{
	int index;
	int highestIndex = 0;
	
	for (index = 0; index < NO_ICE_CREAM_TYPE; index++){
		if (list[highestIndex].totalSale < list[index].totalSale)
			highestIndex = index;
	}
	
	cout	<< "Highest Sale by Ice cream type: "
			<< list[highestIndex].type
			<< ", Amount = RM " << list[highestIndex].totalSale
			<< endl;
			
	outfile << "Highest Sale by Ice cream type: "
			<< list[highestIndex].type
			<< ", Amount = RM " << list[highestIndex].totalSale
			<< endl;
}

void back_to_menu ()
{
	char back_input;
	cout <<"\n\nPlease enter 'B' to go back to the menu: ";
	cin >> back_input;

	while(back_input != 'B')
	{
		cout << endl << "Error! You have input an incorrect value." << endl << endl;
		cout << "Please enter 'B' to go back: ";
		cin >> back_input;
	}
		system("cls");
}

void display_sales_person (salesPersonRecord salesMan[])
{
	cout << "+---------------------------------------+" << endl;
	cout << "| Id\t\t| Name\t\t\t|" << endl;
	cout << "+---------------------------------------+" << endl;
	for (int i=0; i < NO_OF_SALES_PERSON; i++){
		cout << "| " << salesMan[i].Id << "\t\t| " << salesMan[i].name  << "\t\t|"<< endl;
		cout <<"|\t\t|\t\t\t|" << endl;
	}
	cout << "+---------------------------------------+" << endl;
}
