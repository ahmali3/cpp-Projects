// Created by Ahmed Ali on Nov 10 2018
// Program to output instructions for a coin sorting machine
// The program asks for an input file, and reads the data to sort the coins accordingly

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	// Declare variables and constants 
	
	const double MAX_WEIGHT_BENT = 100.0;
	const double MAX_WEIGHT_OTHER = 200.0;
	const double DIAMETER_NICKEL = 21.0;
	const double DIAMETER_DIME = 18.0;
	const double DIAMETER_QUARTER = 23.7;
	const double DIAMETER_LOONIE = 26.0;
	const double DIAMETER_TOONIE = 28.0;
	const double WEIGHT_NICKEL = 3.95;
	const double WEIGHT_DIME = 1.75;
	const double WEIGHT_QUARTER = 4.40;
	const double WEIGHT_LOONIE = 7.00;
	const double WEIGHT_TOONIE = 7.30;
	const double WEIGHT_NICKEL_DIFF = 0.35;
	const double WEIGHT_DIME_DIFF = 0.45;
	const double WEIGHT_QUARTER_DIFF = 0.40;
	const double WEIGHT_LOONIE_DIFF = 0.50;
	const double WEIGHT_TOONIE_DIFF = 0.55;
	const double DIAMETER_NICKEL_DIFF = 0.8;
	const double DIAMETER_DIME_DIFF = 0.7;
	const double DIAMETER_QUARTER_DIFF = 0.9;
	const double DIAMETER_LOONIE_DIFF = 1.0;
	const double DIAMETER_TOONIE_DIFF = 1.1;
	const double DIAMETER_FACTOR = 0.1176470588235294;
	const double WEIGHT_FACTOR = 0.0392156862745098;
	const double TEN = 10;
	const int MAX_LINES = 5000;
	const int MIN_LINES = 0;
	const int MAX_TRIES = 3;
	const int MAX_NICKEL_ROLL = 40;
	const int MAX_DIME_ROLL = 50;
	const int MAX_QUARTER_ROLL = 40;
	const int MAX_LOONIE_ROLL = 25;
	const int MAX_TOONIE_ROLL = 25;
	const int MAX_VALUE = 255;
	const int MIN_VALUE = 0;
	const string BENT = "bent";
	const string USABLE = "usable";
	const string BOTHMATCH = "BothMatch";
	double bentWeight = 0;
	double otherWeight = 0;
	double weight = 0.0;
	double diameter = 0.0;
	int countNickel = 0;
	int countDime = 0;
	int countQuarter = 0;
	int countLoonie = 0;
	int countToonie = 0;
	int countOther = 0;
	int countOtherRenewed = 0;
	int countBent = 0;
	int rollsNickel = 0;
	int rollsDime = 0;
	int rollsQuarter = 0;
	int rollsLoonie = 0;
	int rollsToonie = 0;
	int rollsBent = 0;
	int rollsOther = 0;
	int tries = 0;
	int weightValue = 0;
	int diameterValue = 0;
	int linesOfData = 0;
	int count=0;
	int coin = 0;
	char inputName[1024] = { '\0' };
	char outputName[1024] = { '\0' };
	char character = ' ';
	string condition;
	string bothmatch;
	ifstream inFile;
	ofstream outFile;


	// Asks for the name of the input file, then checks if it was opened correctly

	while (tries == 0 || inFile.fail())
	{
		cout << "Type the name of the input file containing sensor readings: " << endl;
		cin >> inputName;
		tries++;
		inFile.clear();
		inFile.open(inputName);

		if (inFile.fail())
		{
			cerr << "ERROR: File " << inputName << " could not be opened for input" << endl;
		}
		if (tries >= MAX_TRIES)
		{
			cerr << "ERROR: You exceeded maximum number of tries allowed" << endl << "while entering the input file name";
			return 1;
		}
	}

	tries = 0;

	// Asks for the name of the output file, then checks if it was opened correctly

	while (tries == 0 || outFile.fail())
	{
		
		cout << "Type the name of the output file which will hold the simulation results: " << endl;
		cin >> outputName;
		tries++;

		outFile.clear();
		outFile.open(outputName);

		if (outFile.fail())
		{
			cerr << "ERROR: File " << outputName
				<< " could not be opened" << endl;
		}
		if (tries >= MAX_TRIES)
		{
			cerr << "ERROR: You exceeded maximum number of tries allowed" << endl
				<< "while entering the output file name";
			return 2;
		}
	}
	tries = 0;

	//Reads the first integer in the file to determine the amount of lines in the file

	if (!(inFile >> linesOfData))
	{
		if (inFile.eof())
		{
			cerr << "ERROR: Input data file is empty";
			inFile.close();
			outFile.close();
			return 3;
		}
		else
		{
			cerr << "ERROR: First piece of data in the file is not an integer";
			inFile.close();
			outFile.close();
			return 4;
		}
	}

	//Determines if the number of lines is in range

	if (linesOfData <= MIN_LINES || linesOfData > MAX_LINES)
	{
		cerr << "ERROR: The number of sensor readings is out of range" << endl;
		inFile.close();
		outFile.close();
		return 5;
	}

	//Loop to start counting the coins from the input file

	for (count = 0; count < linesOfData; count++)
	{

		// Reads weightValue and checks if it was opened correctly

		if (!(inFile >> weightValue) && !inFile.eof())
		{
			cerr << "ERROR: Weight sensor value read on line "
				<< count + 1 << " is not an integer" << endl
				<< "Simulation terminated early: "
				<< "Please correct your data file";
			break;
		}
		else if (inFile.eof())
		{
			cerr << "ERROR: No more data" << endl
				<< "Simulation completed early before line ";
			cerr << count + 1 << " of input";
			break;
		}
		else
		{
			// Removes any tabs or spaces 
			character = inFile.peek();
			while (character == '	' || character == ' ')
			{
				character = inFile.get();
				character = inFile.peek();
			}
			
			// Checks if the next character is a new line

			if (character == '\n' || inFile.eof())
			{
				cerr << "ERROR: Weight sensor measurement only" << endl
					<< "Ignoring line " << count + 1
					<< " of the input file" << endl;
				continue;
			}
		}

		// Reads diameterValue and checks if it was opened correctly

		if (!(inFile >> diameterValue) && !inFile.eof())
		{
			cerr << "ERROR: Diameter sensor value read on line " << count + 1 << " is not an integer" << endl
				<< "Simulation terminated early: " << "Please correct your data file";
			break;
		
		}

		else if (inFile.eof())
		{
			cerr << "ERROR: No more data" << endl
				<< "Simulation completed early at line ";
			cerr << count + 1 << " of input";
			break;
		}


		else
		{
			// Removes any tabs or spaces 
			character = inFile.peek();
			while (character == '	' || character == ' ')
			{
				character = inFile.get();
				character = inFile.peek();
			}
			// Checks if the next character is a new line

			if (character == '\n')
			{
				cerr << "ERROR: Weight and diameter sensor measurements only" << endl
					<< "Ignoring line " << count + 1
					<< " of the input file" << endl;
				continue;
			}
		}

		//Reads the string that checks if the coin is bent or usable

		inFile >> condition;

		if (condition != BENT && condition != USABLE)
		{
			cerr << "ERROR: Result of test to determine if coin is bent at line " << count + 1 << " is invalid" << endl << "Ignoring this line of data";
			continue;
		}

		//Reads the string that checks if the proper coin is scanned correctly

		if (!(inFile >> bothmatch) && !inFile.eof())
		{
			cerr << "ERROR: Weight and diameter sensor measurements and bent string only" << endl << "Ignoring line " << count + 1
				<< " of the input file" << endl;
			continue;
		}
		
		
		//Converts weightValue to the weight of the coin
		
		weight = WEIGHT_FACTOR * weightValue;
		
		//Converts diameterValue to the diameter of the coin
		
		diameter = (DIAMETER_FACTOR * diameterValue)+TEN;

		//If both string conditions are the correct type, proceeds

		if (condition == USABLE && bothmatch == BOTHMATCH)
		{
			if (weightValue <= MAX_VALUE && weightValue >= MIN_VALUE
				&& diameterValue <= MAX_VALUE && diameterValue >= MIN_VALUE)
			{
				
				//Assigns a number depending on the diameter of the coin
				//Nickel = 1, Dime = 2, Quarter = 3 , Loonie = 4 , Toonie = 5, Other = 0

				if (diameter >= DIAMETER_NICKEL - DIAMETER_NICKEL_DIFF &&
					diameter <= DIAMETER_NICKEL + DIAMETER_NICKEL_DIFF)
				{
					coin = 1;
				}
				else if (diameter >= DIAMETER_DIME - DIAMETER_DIME_DIFF &&
					diameter < DIAMETER_DIME + DIAMETER_DIME_DIFF)

				{
					coin = 2;
				}
				else if (diameter >= DIAMETER_QUARTER - DIAMETER_QUARTER_DIFF &&
					diameter <= DIAMETER_QUARTER + DIAMETER_QUARTER_DIFF)
				{
					coin = 3;
				}
				else if (diameter >= DIAMETER_LOONIE - DIAMETER_LOONIE_DIFF &&
					diameter <= DIAMETER_LOONIE + DIAMETER_LOONIE_DIFF)
				{
					coin = 4;
				}
				else if (diameter >= DIAMETER_TOONIE - DIAMETER_TOONIE_DIFF &&
					diameter <= DIAMETER_TOONIE + DIAMETER_TOONIE_DIFF)
				{
					coin = 5;
				}
				else
				{
					coin = 0;
				}

				// Determines the coin by checking it's weight

				if (weight >= WEIGHT_NICKEL - WEIGHT_NICKEL_DIFF &&
					weight <= WEIGHT_NICKEL + WEIGHT_NICKEL_DIFF &&
					coin == 1)
				{
					countNickel++;

					if (countNickel >= MAX_NICKEL_ROLL)
					{
						cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl
							<< "The nickel wrapper is now full" << endl
							<< "The nickel wrapper has been replaced" << endl;
						outFile << "The Coin Sorter has sent one coin to the nickels wrapper" << endl
							<< "The nickel wrapper is now full" << endl
							<< "The nickel wrapper has been replaced" << endl;
						countNickel = 0;
						rollsNickel++;
					}

					else	cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl << "There are now "
						<< countNickel << " coins in the nickels wrapper" << endl;
					outFile << "The Coin Sorter has sent one coin to the nickels wrapper" << endl << "There are now "
						<< countNickel << " coins in the nickels wrapper" << endl;
					continue;

				}
				else if (weight >= WEIGHT_DIME - WEIGHT_DIME_DIFF &&
					weight <= WEIGHT_DIME + WEIGHT_DIME_DIFF &&
					coin == 2)
				{
					countDime++;

					if (countDime >= MAX_DIME_ROLL)
					{
						cout << "The Coin Sorter has sent one coin to the dimes wrapper" << endl
							<< "The dime wrapper is now full" << endl
							<< "The dime wrapper has been replaced" << endl;
						outFile << "The Coin Sorter has sent one coin to the dimes wrapper" << endl
							<< "The dime wrapper is now full" << endl
							<< "The dime wrapper has been replaced" << endl;
						countDime = 0;
						rollsDime++;
					}

					else cout << "The Coin Sorter has sent one coin to the dimes wrapper" << endl << "There are now "
						<< countDime << " coins in the dimes wrapper" << endl;
					outFile << "The Coin Sorter has sent one coin to the dimes wrapper" << endl << "There are now "
						<< countDime << " coins in the dimes wrapper" << endl;
					continue;
				}

				else if (weight >= WEIGHT_QUARTER - WEIGHT_QUARTER_DIFF &&
					weight <= WEIGHT_QUARTER + WEIGHT_QUARTER_DIFF &&
					coin == 3)
				{
					countQuarter++;

					if (countQuarter >= MAX_QUARTER_ROLL)
					{
						cout << "The Coin Sorter has sent one coin to the quarters wrapper" << endl
							<< "The quarter wrapper is now full" << endl
							<< "The quarter wrapper has been replaced" << endl;
						outFile << "The Coin Sorter has sent one coin to the quarters wrapper" << endl
							<< "The quarter wrapper is now full" << endl
							<< "The quarter wrapper has been replaced" << endl;
						countQuarter = 0;
						rollsQuarter++;
					}

					else cout << "The Coin Sorter has sent one coin to the quarters wrapper" << endl << "There are now "
						<< countQuarter << " coins in the quarters wrapper" << endl;
					outFile << "The Coin Sorter has sent one coin to the quarters wrapper" << endl << "There are now "
						<< countQuarter << " coins in the quarters wrapper" << endl;
					continue;
				}

				else if (weight >= WEIGHT_LOONIE - WEIGHT_LOONIE_DIFF && weight <= WEIGHT_LOONIE + WEIGHT_LOONIE_DIFF && coin == 4)
				{
					countLoonie++;
					if (countLoonie >= MAX_LOONIE_ROLL)
					{
						cout << "The Coin Sorter has sent one coin to the loonies wrapper" << endl
							<< "The loonie wrapper is now full" << endl
							<< "The loonie wrapper has been replaced" << endl;
						outFile << "The Coin Sorter has sent one coin to the loonies wrapper" << endl
							<< "The loonie wrapper is now full" << endl
							<< "The loonie wrapper has been replaced" << endl;
						countLoonie = 0;
						rollsLoonie++;
					}
					else cout << "The Coin Sorter has sent one coin to the loonies wrapper" << endl << "There are now "
						<< countLoonie << " coins in the loonies wrapper" << endl;
					outFile << "The Coin Sorter has sent one coin to the loonies wrapper" << endl << "There are now "
						<< countLoonie << " coins in the loonies wrapper" << endl;
					continue;
				}
				else if (weight >= WEIGHT_TOONIE - WEIGHT_TOONIE_DIFF && weight <= WEIGHT_TOONIE + WEIGHT_TOONIE_DIFF && coin == 5)
				{
					countToonie++;

					if (countToonie >= MAX_TOONIE_ROLL)
					{
						cout << "The Coin Sorter has sent one coin to the toonies wrapper" << endl
							<< "The toonie wrapper is now full" << endl
							<< "The toonie wrapper has been replaced" << endl;
						outFile << "The Coin Sorter has sent one coin to the toonies wrapper" << endl
							<< "The toonie wrapper is now full" << endl
							<< "The toonie wrapper has been replaced" << endl;
						countToonie = 0;
						rollsToonie++;
					}
					else cout << "The Coin Sorter has sent one coin to the toonies wrapper" << endl << "There are now "
						<< countToonie << " coins in the toonies wrapper" << endl;
					outFile << "The Coin Sorter has sent one coin to the toonies wrapper" << endl << "There are now "
						<< countToonie << " coins in the toonies wrapper" << endl;
					continue;
				}

				else if (coin==0)
				{
					otherWeight += weight;
					countOther++;
					countOtherRenewed++;
					if (otherWeight >= MAX_WEIGHT_OTHER)
					{
						countOtherRenewed = 0;
						cout << " The Coin Sorter has sent this coin to the other coin container" << endl << "This coins does not fit in the other coin container" << endl
							<< "The other coin container has been replaced" << endl << "The coin in the new coin container weighs " << weight << " grams" << endl;
						outFile << " The Coin Sorter has sent this coin to the other coin container" << endl << "This coins does not fit in the other coin container" << endl
							<< "The other coin container has been replaced" << endl << "The coin in the new coin container weighs " << weight << " grams" << endl;
						rollsOther++;
					}
					else	cout << "The Coin Sorter has sent this coin to the other coin container" << endl
						<< "The coins in the other coin container now weigh " << otherWeight << " grams" << endl;
					outFile << "The Coin Sorter has sent this coin to the other coin container" << endl
						<< "The coins in the other coin container now weigh " << otherWeight << " grams" << endl;
					continue;
				}
			}		
			else
			{
				otherWeight += weight;
				countOther++;
				countOtherRenewed++;
				if (otherWeight >= MAX_WEIGHT_OTHER)
				{
					countOtherRenewed = 0;
					cout << " The Coin Sorter has sent this coin to the other coin container" << endl << "This coins does not fit in the other coin container" << endl
						<< "The other coin container has been replaced" << endl << "The coin in the new coin container weighs " << weight << " grams" << endl;
					outFile << " The Coin Sorter has sent this coin to the other coin container" << endl << "This coins does not fit in the other coin container" << endl
						<< "The other coin container has been replaced" << endl << "The coin in the new coin container weighs " << weight << " grams" << endl;
					rollsOther++;
				}
				else	cout << "The Coin Sorter has sent this coin to the other coin container" << endl
					<< "The coins in the other coin container now weigh " << otherWeight << " grams" << endl;
				outFile << "The Coin Sorter has sent this coin to the other coin container" << endl
					<< "The coins in the other coin container now weigh " << otherWeight << " grams" << endl;
				continue;
			}
		}

		else if (condition == BENT)
			{
			bentWeight += weight;
			countBent++;
			if (bentWeight >= MAX_WEIGHT_BENT)
			{
				cout << "The Coin Sorter has sent this coin to the bent coin container" << endl << "This coin does not fit in the bent coin container" << endl
					<< "The bent coin container has been replaced" << endl << " The coin in the new bent coin container weighs " << weight << " grams" << endl;
				outFile << "The Coin Sorter has sent this coin to the bent coin container" << endl << "This coin does not fit in the bent coin container" << endl
					<< "The bent coin container has been replaced" << endl << " The coin in the new bent coin container weighs " << weight << " grams" << endl;
				rollsBent++;
			}
			else {
				cout << "The Coin Sorter has sent this coin to the bent coin container" << endl
					<< "The coins in the bent coin container now weigh " << bentWeight << " grams" << endl;
				outFile << "The Coin Sorter has sent this coin to the bent coin container" << endl
					<< "The coins in the bent coin container now weigh " << bentWeight << " grams" << endl;
			}
			continue;
			}

		else if (!(condition == USABLE && condition == BENT))
		{
		otherWeight += weight;
		countOther++;
		countOtherRenewed++;
		if (otherWeight >= MAX_WEIGHT_OTHER)
		{
			countOtherRenewed = 0;
			cout << " The Coin Sorter has sent this coin to the other coin container" << endl << "This coins does not fit in the other coin container" << endl
				<< "The other coin container has been replaced" << endl << "The coin in the new coin container weighs " << weight << " grams" << endl;
			outFile << " The Coin Sorter has sent this coin to the other coin container" << endl << "This coins does not fit in the other coin container" << endl
				<< "The other coin container has been replaced" << endl << "The coin in the new coin container weighs " << weight << " grams" << endl;
			rollsOther++;
		}
		else	cout << "The Coin Sorter has sent this coin to the other coin container" << endl
			<< "The coins in the other coin container now weigh " << otherWeight << " grams" << endl;
		outFile << "The Coin Sorter has sent this coin to the other coin container" << endl
			<< "The coins in the other coin container now weigh " << otherWeight << " grams" << endl;
		continue;
 }

		
		else
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << count + 1 << " in the input file" << endl;
			continue;
		}
	}
	inFile.close();
	
	//Closes the input file
	
	cout << endl << endl << endl;
	outFile << endl << endl << endl;

	//Displays the final results and also saves them on the output file

	cout << "SUMMARY" << endl;
	outFile << "SUMMARY" << endl;

	cout << "The Coin Sorter made " << rollsNickel << " rolls of nickels." << endl << endl
		<< "    There are " << countNickel << " nickels in the partially full roll." << endl << endl;
	outFile << "The Coin Sorter made " << rollsNickel << " rolls of nickels." << endl << endl
		<< "    There are " << countNickel << " nickels in the partially full roll." << endl << endl;

	cout << "The Coin Sorter made " << rollsDime << " rolls of dimes." << endl << endl
		<< "    There are " << countDime << " dimes in the partially full roll." << endl << endl;
	outFile << "The Coin Sorter made " << rollsDime << " rolls of dimes." << endl << endl
		<< "    There are " << countDime << " dimes in the partially full roll." << endl << endl;

	cout << "The Coin Sorter made " << rollsQuarter << " rolls of quarters." << endl << endl
		<< "    There are " << countQuarter << " quarters in the partially full roll." << endl << endl;
	outFile << "The Coin Sorter made " << rollsQuarter << " rolls of quarters." << endl << endl
		<< "    There are " << countQuarter << " quarters in the partially full roll." << endl << endl;

	cout << "The Coin Sorter made " << rollsLoonie << " rolls of loonies." << endl << endl
		<< "    There are " << countLoonie << " loonies in the partially full roll." << endl << endl;
	outFile << "The Coin Sorter made " << rollsLoonie << " rolls of loonies." << endl << endl
		<< "    There are " << countLoonie << " loonies in the partially full roll." << endl << endl;

	cout << "The Coin Sorter made " << rollsToonie << " rolls of toonies." << endl << endl
		<< "    There are " << countToonie << " toonies in the partially full roll." << endl << endl;
	outFile << "The Coin Sorter made " << rollsToonie << " rolls of toonies." << endl << endl
		<< "    There are " << countToonie << " toonies in the partially full roll." << endl << endl;

	cout << "The Coin Sorter processed " << countOther << " other coins." << endl << endl
		<< "    The other coins completely filled " << rollsOther << " containers" << endl << endl;
	outFile << "The Coin Sorter processed " << countOther << " other coins." << endl << endl
		<< "    The other coins completely filled " << rollsOther << " containers" << endl << endl;

	cout << "    There were " << countOtherRenewed << " other coins in the partially full container" << endl << endl;
	outFile << "    There were " << countOtherRenewed << " other coins in the partially full container" << endl << endl;

	cout << "    The total weight of the other coins was " << otherWeight << " grams" << endl << endl;
	outFile << "    The total weight of the other coins was " << otherWeight << " grams" << endl << endl;

	cout << "The coin sorter processed " << bentWeight << " g of bent coins" << endl << endl;
	outFile << "The coin sorter processed " << bentWeight << " g of bent coins" << endl << endl;

	outFile.close();

	//Closes the output file and ends the program

	return 0;
}