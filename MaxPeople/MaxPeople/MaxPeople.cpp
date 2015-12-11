#include "stdafx.h"
#include<iostream>
#include<fstream>
#include"time.h"
#include<vector>  
#include"cstdio"

using namespace std;

void generatePeople() // Generates random number of people with random birth and death years and stores them in a comma separated value (CSV) file
{
	srand(time(NULL)); //Makes the rand() function pseudo random

	int numPeople = rand() % 201 + 800; //Generates a random number of people between 800 and 1000
	int bYear, dYear; //Birth Year and Death Year

	ofstream ip;		// Writes values generated on a CSV file
	ip.open("Input.csv");
	ip << "Birth,Death\n";

	for (int i = 1; i <= numPeople; i++)//Creates birth and death year for every person
	{
		bYear = rand() % 101 + 1900; //Selects a random birth year between 1900 and 2000
		dYear = (rand() % (2000 - bYear + 1)) + bYear; //Selects a random death year between birth year and 2000
		ip << bYear << "," << dYear << "\n"; 
	}

	ip.close();
}

int main()
{
	generatePeople(); //Generates people. Is not needed if user wants to give his own file as an input.

	ifstream ip;
	ip.open("Input.csv"); //Input file(we created) is read
	ip.ignore(256, '\n'); // First line(heading) is ignored
	
	vector<int> ppl(101, 0); //101 element vector is created representing years from 1900-2000. All values are initially set to 0.
	int bTemp, dTemp;
	int max = 0;

	while (!ip.eof()) //Till the end of the file
	{
		ip >> bTemp;
		ppl[bTemp - 1900]++; //Reads the file and when a birth year is detected subsequent cell in vector is incremented
		ip.ignore(1, ','); //Used to ignore "," which is the separator

		ip >> dTemp;
		ppl[dTemp - 1900]--; //Reads the file and when a death year is detected subsequent cell in vector is decremented
		ip.ignore(1, ','); //Used to ignore "," which is the separator
	}

	ip.close();

	ofstream op;
	op.open("Output.csv"); // Writes output to the file

	for (int i = 0; i <= 100; i++) // Calculates people alive in each year and max people alive in all the years
	{
		if (ppl[i] > max)
			max = ppl[i];

		if (i != 100)
			ppl[i + 1] = ppl[i + 1] + ppl[i];
	}

	op << max << " is the maximum number of people alive in the year(s) : "; 
	cout << max << " is the maximum number of people alive in the year(s) : "; //Displays output in console

	for (int i = 0; i <= 100; i++) //Displays the Maximum number of people alive and which years this occurred in
	{
		if (ppl[i] == max)
		{
			cout << 1900 + i << "; ";
			op << 1900 + i << "; ";
		}
	}

	op << "\n";
	op << "\n";
	op << "Year,People Alive\n";
	for (int i = 0; i <= 100; i++) // Displays all the years with the number of people alive in them. The years with maximum number of people alive are denoted by "<----MAX" 
	{
		if (ppl[i]==max)
			op << 1900 + i << "," << ppl[i] <<",<----MAX\n";
		else
			op << 1900 + i << "," << ppl[i] << "\n";
	}
	op.close();

	getchar();
	return 0;
}