//Brent Lewis
//A program for basic tax computations. 

#include "pch.h"
#include <iostream>
using namespace std;
#include<math.h>

int main()
{
	char relation, depend, blind, born, sborn, sblind;
	float wages, tax_intrest, dividens, total_income,
		adjust_income, total_tax, fed_income, paid;
	int stan_deduct, social, count;
	const int single = 12000;
	const int married = 24000;

	cout << "So you have taxes you need to do... that sucks." << endl
		<< "Let's see if we can't help with that" << endl;

	cout << "To start, are you single, or married? "
		<< "\n(s for single, m for married)" << endl;

	cin >> relation;

	cout << "Please enter your "
		<< "social security number." << endl;
	cin >> social;

	cout << "Please enter your wages, salaries, tips, etc." << endl;
	cin >> wages;

	cout << "Enter your taxable interest "
		<< "\n(if you have none enter 0) " << endl;
	cin >> tax_intrest;

	cout << "Enter your Oridinary dividens "
		<< "\n(if you have none enter 0)" << endl;
	cin >> dividens;

	cout << "Enter your adjusted gross income "
		<< "(if you have no adjustments enter 0)" << endl;
	cin >> adjust_income;

	total_income = wages + tax_intrest + dividens + adjust_income;
	adjust_income += (wages + tax_intrest + dividens);

	cout << "Does someone claim you as a dependent? (y/n)" << endl << endl;
	cin >> depend;

	if (depend == 'y' || depend == 'Y')
	{
		count = 0;
		if (relation == 'm' || relation == 'M') {
			cout << "The following questions will repeat twice.\n Once for you, "
				<< "and once for your spouse. \n Please fill it out "
				<< "twice for each respectively." << endl;

			cout << "Are you blind? (y/n)" << endl;
			cin >> blind;

			cout << "Were you born before January 2, 1954? (y/n)" << endl;
			cin >> born;

			cout << "is your spouse blind? (y/n)" << endl;
			cin >> sblind;

			cout << "Were you born before January 2, 1954? (y/n)" << endl;
			cin >> sborn;

			if (born == 'y' && sborn == 'y')
				count += 2;
			else if (born == 'y' || sborn == 'y')
				count++;
			if (blind == 'y' && sblind == 'y')
				count++;
			else if (sblind == 'y' || blind == 'y')
				count++;
		}
		else {
			cout << "Are you blind? (y/n)" << endl;
			cin >> blind;

			cout << "Were you born before January 2, 1954? (y/n)" << endl;
			cin >> born;

			if (blind == 'y' || blind == 'Y')
				count++;

			if (born == 'y' || born == 'Y')
				count++;

		}

		if (wages > 700)
			stan_deduct = wages + 350;
		else
			stan_deduct = wages;

		if (relation == 'm' || relation == 'M') {
			if (married < stan_deduct)
				stan_deduct = married;
		}
		else {
			if (single < stan_deduct)
				stan_deduct = single;
		}

		if (count > 0)
		{
			if (relation == 'm' || relation == 'M')
				// need to add up blind and born
				stan_deduct += (count * 1300);
			else
				// need to add up blind and born
				stan_deduct += (count * 1600);
		}

	}
	else
	{
		if (relation == 'm' || relation == 'M')
			stan_deduct = married;
		else
			stan_deduct = single;
	}

	if (total_income - stan_deduct < 0)
		total_tax = 0;
	else
		total_tax = total_income - stan_deduct;

	//formula to figure out federal income tax***
	if (relation == 'm' || relation == 'M') {

		if (total_income < 19051)
			fed_income = total_income * .1;

		else if (total_tax < 38701)
			fed_income = ((total_income - 9525) * .12) + 952.5;

		else if (total_tax < 82501)
			fed_income = ((total_income - 38700) * .22) + 4453.5;

		else
			fed_income = ((total_income - 82500) * .24) + 14089.5;
	}
	else {

		if (total_income < 19051)
			fed_income = total_income * .1;

		else if (total_income < 77401)
			fed_income = ((total_income - 19050) * .12) + 1905;

		else
			fed_income = ((total_income - 82500) * .22) + 8907;
	}

	cout << "Your Social Security Number is: "
		<< social << endl
		<< "Your Adjusted Gross Income is: "
		<< total_income << endl
		<< "Your Taxable Income is: "
		<< total_tax << endl
		<< "Your Taxable Amount is: "
		<< fed_income << endl;

	if (total_tax < fed_income)
	{
		paid = fed_income - total_tax;
		cout << "You over paid by $"
			<< paid << endl;
	}
	else
	{
		paid = fed_income - total_tax;
		cout << "You owe $"
			<< paid << endl;
	}

	return 0;
}
