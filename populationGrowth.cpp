//Brent Lewis
//Computes population growth and size

#include "pch.h"
#include <iostream>
using namespace std;

void run(void);
void howLong(int initpop, int overpop,
	int mrate, double grate, double opdrate,
	double pop, int target, int t);

void howMany(int initpop, int overpop,
	int mrate, double grate, double opdrate,
	double pop, int time, int t);

int main()
{
	char check;
	//run program
	run();

	//input- check to see if they want to run test again
	cout << "Would you like to test something else? (y/n)" << endl;
	cin >> check;
	while (check != 'y' && check != 'n') {
		cout << "Would you like to test something else? " << endl
			<< "enter lower case (y/n)" << endl;
		cin >> check;
		cout << endl;
	}

	//recurs
	if (check == 'y')
		main();

	return 0;
}

void run(void) {
	int initpop, overpop, irate, mrate, erate, type, t;
	double brate, drate, opdrate, grate, pop;

	//input- over population limit
	cout << "Input what the over-crowding threshold is." << endl;
	cin >> overpop;
	while (overpop < 0) {
		cout << "..Please enter a population limit that "
			<< "is greater than 0..." << endl;
		cin >> overpop;
		cout << endl;
	}

	//input- over population death rate
	cout << "Next the percent of population that will die if that threshold"
		<< " is exceeded (0.1 == 10%)" << endl;
	cin >> opdrate;
	while (opdrate > 1 || opdrate < 0) {
		cout << "Please enter a decimal percentage between 0 and 1 "
			<< "(0.50 == 50%)" << endl;
		cin >> opdrate;
		cout << endl;
	}

	//input- type of test
	cout << "Would you like to know how long it will take to"
		<< " reach a certain number (1)," << endl
		<< "or what the population will be after a given time "
		<< "has passed?(0)" << endl;
	cin >> type;
	while (type != 1 && type != 0) {
		cout << "Enter one (1) for how long it will take," << endl
			<< "or zero (0) for the population size after a given time "
			<< "has passed" << endl;
		cin >> type;
		cout << endl;
	}

	//input- initial population
	cout << "What is the starting chinchillas population?" << endl;
	cin >> initpop;
	while (initpop < 2) {
		cout << "..Please enter a population that is at least 2...." << endl;
		cin >> initpop;
		cout << endl;
	}

	//input- birth rate
	cout << "What is the birth rate per year in percentage "
		<< "(0.1 == 10%)?" << endl;
	cin >> brate;
	while (brate < 0) {
		cout << "Please enter a decimal percentage greater than 0 "
			<< "(0.50 == 50%, 2.5 == %250 )" << endl;
		cin >> brate;
		cout << endl;
	}

	//input- death rate
	cout << "What is the death rate per year in percentage"
		<< "(0.1 == 10%)?" << endl;
	cin >> drate;
	while (drate > 1 || drate < 0) {
		cout << "Please enter a decimal percentage between 0 and"
			<< "1 (0.50 == 50%)" << endl;
		cin >> drate;
		cout << endl;
	}

	//input- emigration rate
	cout << "What is the emigration rate per year?" << endl;
	cin >> erate;
	while (erate < 0) {
		cout << "Please enter an emigration rate that is greater "
			<< "than or equal to 0." << endl;
		cin >> erate;
		cout << endl;
	}
	//input- immigration rate
	cout << "What is the immigration rate per year?" << endl;
	cin >> irate;
	while (irate < 0) {
		cout << "Please enter an immigration rate that is "
			<< "greater than or equal to 0." << endl;
		cin >> irate;
		cout << endl;
	}

	//Here we compute the migration and Growth rate
	mrate = irate - erate;
	grate = brate - drate;

	//runs if they want to test how long it'll take to get to a set population.
	if (type == 1) {
		int target;
		cout << "what is the target population size you want?" << endl;
		cin >> target;
		cout << endl;
		while (target <= initpop || target > overpop) {
			cout << "Please enter a target population "
				<< "size that is greater than the origional population size: "
				<< initpop << endl
				<< "and greater than or equal to the over population size: "
				<< overpop << endl;
			cin >> target;
			cout << endl;
		}
		howLong(initpop, overpop, mrate, grate, opdrate, 
			pop = 0.0, target, t = 0);
	}

	//runs if they want to test What the population will be after a given time.
	else if (type == 0) {
		int time;
		cout << "How many years do you want to test?" << endl;
		cin >> time;

		while (time < 1) {
			cout << "Please enter at least 1 year to be tested" << endl;
			cin >> time;
			cout << endl;
		}
		howMany(initpop, overpop, mrate, grate, opdrate,
			pop = 0.0, time, t = 0);
	}

}

//runs if they want to test how long it'll take to get to a set population.
//recursive on initpop
void howLong(int initpop, int overpop,
	int mrate, double grate, double opdrate,
	double pop, int target, int t)
{
	pop = initpop + ((initpop * grate) + mrate);
	t += 1;

	//checks if the population exceeds population limits
	if (pop > overpop)
		pop -= (pop * opdrate);

	//typecast pop to int and round to nearest int
	initpop = (int)round(pop);

	//Checks if population size is < 0
	// cuts loop if so and says the farm failed
	if (initpop <= 0) {
		cout << "The farm was not sustainable." << endl
			<< "There are no more chinchillas after "
			<< t
			<< " years." << endl;
	}

	//recurs
	else if (initpop < target)
		howLong(initpop, overpop, mrate, grate, opdrate, pop, target, t);

	//output for the results
	else {
		cout << "After "
			<< t
			<< " years there are "
			<< initpop
			<< " chinchillas." << endl;
	}
}

//runs if they want to test What the population will be after a given time.
//recursive on t
void howMany(int initpop, int overpop,
	int mrate, double grate, double opdrate,
	double pop, int time, int t)
{
	pop = initpop + ((initpop * grate) + mrate);
	t += 1;

	//checks if the population exceeds population limits
	if (pop > overpop)
		pop -= (pop * opdrate);

	//typecast pop to int and round to nearest int
	initpop = (int)round(pop);

	//Checks if population size is < 0
	// cuts loop if so and says the farm failed
	if (initpop <= 0) {
		cout << "The farm was not sustainable." << endl
			<< "There are no more chinchillas after "
			<<t
			<<" years."<< endl;
	}

	//recurs
	else if (t < time)
		howMany(initpop, overpop, mrate, grate, opdrate, pop, time, t);

	//output for the results
	else {
		cout << "After "
			<< t
			<< " years there are "
			<< initpop
			<< " chinchillas." << endl;
	}
}
