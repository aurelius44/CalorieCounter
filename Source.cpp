/*
Name: Mark Middleton
Date: 8-3-2022
Project Name: Calorie Counter
Project Description:
This program will accept two weeks of
caloric input for breakfast, lunch, and
dinner. It will then tell the user how much
they will have lost based solely on a caloric
deficit per week.*/

using namespace std;

#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>

void descriptionAndWarning();  // Display a explanation/instructions, as well as a warning to user.
double dailySum(double, double, double); // Caclulates sum of three daily meals.
double weightLost(double);     // Calculate deficit in terms of pounds shed.

int main()
{
	double breakfast, lunch, dinner,
		deficit, sum;
	double total = 0; // Counter for calculating daily and weekly deficits.
	char answer; // To hold input for do-while loop.

	descriptionAndWarning();

	ofstream outputFile;
	outputFile.open("CaloricData.txt"); // File to write daily deficits to be read later.
	
	do // Loop will repeat ad infinitum until user is satisfied.
	{

		for (int i = 0; i < 7; i++) // Loop repeats for all days of the week, storing meal deficits to file.
		{	
			cout << "Day " << (i + 1) << "\nInput Calories from Breakfast, Lunch, and Dinner: \n";
			cin >> breakfast >> lunch >> dinner;
			sum = dailySum(breakfast, lunch, dinner);
			outputFile << sum << endl;
		}

		cout << "\nWould you like to calculate another week? (Y/N) ";
		cin >> answer;

	} while (answer == 'Y' || answer == 'y');

	outputFile.close();

	double elements; // To hold file values.
	ifstream inputFile;
	inputFile.open("CaloricData.txt");
	inputFile >> elements; // Plugging file values into variable 'elements'
	vector <double> calorieData(7, elements); // Vector now holds contents of 'CaloricData'


	for (int i = 0; i < 7; i++)
	{
		deficit = 2000 - calorieData[i]; // This finds the daily deficit.
		total += deficit; // Total deficit for the week.
	}

	if (total < 7000 && total > 0)
	{
		cout << "\nYou have a calorie deficit of " << total;
		cout << "\nYou have lost " << fixed << setprecision(2) << showpoint << weightLost(total) << " lbs! Congratulations!\n";
		cout << "\nThank you for using this program!\n";
	}
	else if (total <= 0)
	{
		cout << "\nYou have not produced a deficit.\n";
	}
	else
	{
		cout << "\nYour calorie intake is too low. Consult a physician or a dietary specialist.\n";
	}

	inputFile.close();

	return 0;
}

void descriptionAndWarning()
{
	cout << "The purpose of this program is to collect total caloric data for three meals a day per week.\n"
		<< "This is for an attempted 1500 calories per day against a 2000 calorie per day diet. Having a deficit of\n"
		<< "500 calories per day will result in a weekly deficit of 3500 calories. This is roughly the equivalent\n"
		<< "of one pound of weight loss per week.\n"
		<< "\nWARNING: Do not drop below 1000 calories per day. This can be harmful to your health.\n"
		<< "\nTo begin, input your data below: \n\n";
}

double dailySum(double breakfast, double lunch, double dinner)
{
	int sum = breakfast + lunch + dinner;
	return sum;
}

double weightLost(double weeklyDeficit)
{
	double lost = weeklyDeficit / 3500;

	return lost;
}