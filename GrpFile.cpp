#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void printTimestamp (); //prints the timestamp
void voltAvg (); //average voltage
void wattAvg (); //average wattage

ifstream myInFile; //in file
ofstream myOutFile; // out file

float sum; //global variable

int main ()
{
	string s;
	string locateWord;

	int index;

	myInFile.open("OperationActive-2015.xml"); //opens file
	myOutFile.open("outFile.txt"); //opens file

	if (!myInFile) //if it can't open
	{
		cout << "Cannot open file";
		return 1;
	}

	getline(myInFile, s); //gets first line of file
	index = s.find(' '); //finds first white space
	locateWord = s.substr(0, index); //cuts up line and assigns to locateWord

	//Search file for this text
	while (locateWord != "<VoltAmpereReactiveTimeSeries")
		{
			getline(myInFile, s);
			index = s.find(' ');
			locateWord = s.substr(0, index);
		}
    //gets timestamp and average voltage
	s = s.substr(index+1, s.length()); 
	index = s.find('"');
	index = s.find('"');

	myOutFile << "Data Item ID: " << s.substr(12, index) << endl;
	cout << "Data Item ID: "  << s.substr(12, index) << endl;
	
	s = s.substr(36, s.length());
	index = s.find('"');
	
	myOutFile << "Timestamp: " << s.substr(0, index) << endl;
	cout << "Timestamp: " << s.substr(0, index) << endl;
	s = " ";
	voltAvg ();
	
	//ignores useless lines
	myInFile.ignore(200, '\n');
	myInFile.ignore(200, '\n');

	for (int count = 0; count < 2; count++) //voltage data
		{
			printTimestamp ();
			voltAvg ();
			//ignores line
			myInFile.ignore(200, '\n');
			myInFile.ignore(200, '\n'); 
		}

	for (int count = 0; count < 3; count++) //wattage data
		{
			printTimestamp ();
			wattAvg ();
			//ignore
			myInFile.ignore(200, '\n');
			myInFile.ignore(200, '\n');
		}
	myInFile.close();//closes input files
	myOutFile.close();//closes the outFile
	system ("pause");
	return 0;
}

void wattAvg ()
{
	float ave;
	float dataValues;
	for (int count = 0; count < 25; count++) //sums 25 wattage values
		{
			myInFile >> dataValues; //extract wattage data values from myInFile
			sum += dataValues;
		}
	ave = sum/25.0; //calculate the average wattage
	cout << "Average Wattage: " << ave <<endl << endl;//outputs ave on screen
	myOutFile << "Average Wattage: " << ave <<endl << endl; //Prints the average to out file
	sum = 0; //re initialize sum
}

void voltAvg () 
{
	float ave;
	float dataValues;
	for (int count = 0; count < 25; count++) //sums 25 voltage values
		{
			myInFile >> dataValues;//extract voltage data values from myInFile
			sum += dataValues;
		}
	ave = sum/25.0; //calculate the average voltage
    cout << "Average Voltage: " << ave <<endl << endl;//outputs ave on screen
	myOutFile << "Average Voltage: " << ave << endl << endl; //Prints the average to out file
	sum = 0; // re initialize sum 
}

void printTimestamp ()
{
	int index;
	string s;
	getline(myInFile, s); //gets the line
	index = s.find('"'); //finds the "
	s = s.substr(index, s.length()); //re define s
	myOutFile << "Data Item ID: " << s.substr(1, 11) << endl;
	cout << "Data Item ID: "  << s.substr(1, 11) << endl;
	s = s.substr(25, s.length());
	myOutFile << "Timestamp: " << s.substr(0, 24) << endl;
	cout << "Timestamp: " << s.substr(0, 24) << endl;
	s = " "; //re define s
}




