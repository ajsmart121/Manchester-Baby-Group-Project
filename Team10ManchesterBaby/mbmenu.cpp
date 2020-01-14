#include "assembler.cpp"
#include <iomanip>
#include <stdlib.h>

using namespace std;
int AssemblerMenu() // menu for assembeler
{		
		system("clear");

		int spaceNums; //store number of storage spaces
		int processBits; //store number of Processer Bits
		string fileName; //store file name

		cout<< "\033[1;31m" <<endl;
		cout<< setw(27);
		cout<< "- ASSEMBLER -\n" <<endl;
		cout<< setw(38);
		cout<< "-----------------------------------\n" <<endl;
		cout<< "\033[9;0m";
		cout<< setw(40);
		cout<< "Please Enter the Name of the File :\n" <<endl;
		cin>>fileName;
		cout<<"\n"<<endl;
		cout<< setw(40);
		cout<< "Please Enter the Number of Stroage Spaces :\n" <<endl;
		cin>>spaceNums;
		cout<<"\n"<<endl;
		cout<< "Please Enter the Number of bits in the processer :\n" <<endl;
		cin>>processBits;
		cout<<"\n"<<endl;
		cout<< "\033[1;36m" <<endl;
		cout<< "Name of File : " << fileName <<"\n" <<endl;
		cout<< "Bits in the processer : " << processBits <<"\n" <<endl;
		cout<< "Number of Stroage Spaces : " << spaceNums << "\n"<<endl;
		cout<< "\033[9;0m";
		assembler(fileName);
}
int	CompilerMenu() // menu for compiler
{
		system("clear");

		int spaceNums; //store number of storage spaces
		int processBits; //store number of Processer Bits
		string fileName; //store file name

		cout<< "\033[1;31m" <<endl;
		cout<< setw(26);
		cout<< "- COMPILER -\n" <<endl;
		cout<< setw(38);
		cout<< "-----------------------------------\n" <<endl;
		cout<< "\033[9;0m";
		cout<< setw(40);
		cout<< "Please Enter the Name of the File :\n" <<endl;
		cin>>fileName;
		cout<<"\n"<<endl;
		cout<< setw(40);
		cout<< "Please Enter the Number of Stroage Spaces :\n" <<endl;
		cin>>spaceNums;
		cout<<"\n"<<endl;
		cout<< "Please Enter the Number of bits in the processer :\n" <<endl;
		cin>>processBits;
		cout<<"\n"<<endl;
		cout<< "\033[1;36m" <<endl;
		cout<< "Name of File : " << fileName <<"\n" <<endl;
		cout<< "Bits in the processer : " << processBits <<"\n" <<endl;
		cout<< "Number of Storage Spaces : " << spaceNums << "\n"<<endl;
		cout<< "\033[9;0m";
		compiler(processBits, spaceNums, fileName);
}

int main()
{
	int choice;
	

	system("clear");

	cout<< "\033[1;31m" <<endl;		//set title colour to red
	cout<< setw(30);					//useing setw to center text
	cout<< "- MANCHESTER BABY -\n" <<endl;
	cout<< setw(38);
	cout<< "-----------------------------------\n" <<endl;
	cout<< "\033[9;0m";			//set text back to white
	cout<< setw(40);
	cout<< "- Please Select an Option from Below -\n" <<endl;

	//3 options in main menue :
	cout<< setw(26);
	cout<< "1) Assembler\n" <<endl;
	cout<< setw(25);
	cout<< "2) Complier\n" <<endl;
	cout<< setw(21);
	cout<< "0) Exit\n" <<endl;
	//get user choice
	cin>>choice;
	//options in the the menue based on uesers choice
	switch (choice)
	{
		case 1: //Assembler Menu

		AssemblerMenu();
		break;

		case 2:	//Compiler Menu

		int CompilerMenu();
		break;

		case 0: //Exit Menus

			system("clear");
			cout<<"\n"<<endl;
			cout<< "\033[1;36m" <<endl;
			cout<< setw(30);
			cout<<"Goodbye!"<<endl;
			cout<< "\033[9;0m";
			cout<<"\n"<<endl;
			cout<<"\n"<<endl;
			cout<<"\n"<<endl;
			cout<<"\n"<<endl;
		break;

		default: //Errors Menu

		 		system("clear");

		int choice2;

		cout<< "\033[1;31m" <<endl;
		cout<< setw(30);
		cout<< "- !ERROR! -" <<endl;;
		
		cout<< setw(32);
		cout<< "Invalid Choice\n" <<endl;
		cout<< "\033[9;0m" <<endl;
		cout<< setw(30);
		cout<< "1) Re-enter\n" <<endl;
		cout<< setw(26);
		cout<< "0) Exit\n" <<endl;

		cin>>choice2;

		switch (choice2)
	{
		case 1: //Assembler Menu

		 main();
		break;

		case 0: //Exit Menus

			system("clear");
			cout<<"\n"<<endl;
			cout<< "\033[1;36m" <<endl;
			cout<< setw(30);
			cout<<"Goodbye!"<<endl;
			cout<< "\033[9;0m";
			cout<<"\n"<<endl;
			cout<<"\n"<<endl;
			cout<<"\n"<<endl;
			cout<<"\n"<<endl;
		break;

		default: //Errors Menu

		  main();
		break;

	}
		break;

	}
}


