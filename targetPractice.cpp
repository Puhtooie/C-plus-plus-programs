//Brent Lewis
//Program for playing a shooter game
//no gui

#include "pch.h"
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

int menu(void);
int menu2(void);
void options(int &choice);

void Night(void);
void radar(int radr, int x1, int y1, int x2, int y2);
void adjustHoz(int hoz, int &adj);

//main subs
void Target(void);
void Artillery(void);
void Calcs(void);

void adjustVert(int vert, int &adj);

//computational funcs
void compDestination(int x, int y, double distance, double hozAngle,
	double &x2, double &y2);
double fire(int x1, int y1, int x2, int y2, int hoz, int vert, int maxVel);
double compDistance(double x1, double x2, double y1, double y2);
double compHozAngle(double x1, double x2, double y1, double y2);
double compHozDistance(double elev, double velo);
// rand num gen
int random(int max, int min);

//get values
void pValues(double &x1, double &x2, double &y1, double &y2);
void shipValues(int &x1, int &y1, int &x2, int &y2, int &shipVel, double &damage, int &direct);
void twoVAls(int x1, int y1, double &x3, double &y3);
void tVals(int &rad, int &x1, int &y1, double &x2, double &y2);
void aValues(double &vert, double &vel, int &rows, int &vary, double &vryval);
void hozValues(double &elev, double &velo);
void destValues(double &x, double &y, double &distance, double &hozAngle);

int main()
{
	int choice;
	char cont;

	do {
		choice = menu2();

		if (choice == 1)
			Calcs();

		else if (choice == 2)
			Artillery();

		else if (choice == 3)
			Target();

		else if (choice == 4)
			Night();

		cout << "Would you like to play another game? (y/n)" << endl;
		cin >> cont;
		while (cont != 'y' && cont != 'n')
		{
			cout << "Please input y for yes or n for no (y/n)" << endl;
			cin >> cont;
		}

	} while (cont == 'y');

	return 0;
}

int menu2()
{
	int choice;
	do {
		cout << "Please input the correspoding number to the computation you want." << endl
			<< "1. Basic Calculations" << endl
			<< "2. Artillery Table." << endl
			<< "3. Target Practice." << endl
			<< "4. Night Passage." << endl;

		cin >> choice;
	} while (choice < 1 && choice > 4);

	return choice;
}

///////NIGHT////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////NIGHT////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Night() {
	int x1, y1, x2, y2, x3, y3, hoz, shipVel, vert, round, choice;
	int hozDist, adjHoz, adjVert, quit, destroyed, fired, hits, direct, radr, n;
	const int maxVel = 250;
	double velp, dist, dam, damage;

	fired = 0;
	hits = 0;
	quit = 0;
	radr = 0;
	destroyed = 0;
	n = 0;

	shipValues(x1, y1, x2, y2, shipVel, damage, direct);

	hoz = 90;
	vert = 45;

	options(choice);

	do {
		if (n == 1) {
			n = 0;
			shipValues(x1, y1, x2, y2, shipVel, damage, direct);
		}
		if (choice == 1) {

			dam = fire(x1, y1, x2, y2, hoz, vert, maxVel);
			damage += dam;
			fired++;

			if (dam > 0) {
				hits++;

				if (damage >= 100) {
					cout << "You sunk the ship!" << endl;
					destroyed++;
					n = 1;
				}
			}

			else if (choice == 2) {
				radar(radr, x1, y1, x2, y2);
			}
			else if (choice == 3) {
				adjustHoz(hoz, adjHoz);
				hoz = adjHoz;
			}
			else if (choice == 4) {
				adjustVert(vert, adjVert);
				vert = adjVert;
			}
			else if (choice == 5) {
				//create mp3 file open for frozen theme song
				n = 1;
			}
			else {
				quit = 1;
			}

			if (direct == 1) {
				x2 += (1 - (damage / 100)) * shipVel;
			}
			else {
				x2 -= (1 - (damage / 100)) * shipVel;
			}

			if (x2 >= 5000 || x2 <= 0) {
				cout << "the ship escaped" << endl;
				n = 1;
			}

		} while (quit < 1);

		cout << "You sunk " << destroyed << " ships, hit " << hits << "times and fired "
			<< fired << " times" << endl;
	} while (quit == 0);
}

void adjustHoz(int hoz, int &adj)
{
	int choice;

	do {
		cout << "Enter a 1 to go left and 0 to go right." << endl;
		cin >> choice;
	} while (choice != 0 && choice != 1);

	do {
		cout << "Enter the adjustment to the cannon's horizontal angle." << endl
			<< "from 0 to 30" << endl;
		cin >> adj;
	} while (adj < 0 && adj > 30);
}

void adjustVert(int vert, int &adj)
{
	do {
		cout << "How much would you like to adjust the cannon's vertical angle?"
			<< endl
			<< "from -30 to 30" << endl;
		cin >> adj;
	} while (adj > 30 && adj < -30);

	adj += vert;

	if (adj > 80)
		adj = 80;
	else if (adj < 10)
		adj = 10;
}

void radar(int radr, int x1, int y1, int x2, int y2)
{
	int r, ang;
	r = random(5, 0);

	if (radr > r)
		cout << "The radar has malfunctioned." << endl;
	else {
		ang = compHozAngle(x1, x2, y1, y2);
		cout << "The horizontal angle is " << ang << " degrees." << endl;
	}
}

double fire(int x1, int y1, int x2, int y2, int hoz, int vert, int maxVel) {

	int d, round, velp;
	double hozDist, dist, x3, y3;

	do {
		cout << "Do you want to fire a flash grenade, or a shell?" << endl
			<< "1: flash" << endl
			<< "0: shell" << endl;
		cin >> round;

	} while (round != 1 && round != 0);

	do {
		cout << "What wold you like the maximum velocity to be?" << endl
			<< "from 0 to 100 percent" << endl;
		cin >> velp;

	} while (velp < 0 && velp > 100);

	velp = (velp / 100.0) * maxVel;

	hozDist = compHozDistance(vert, velp);

	compDestination(x1, y1, hozDist, hoz, x3, y3);

	dist = compDistance(x2, x3, y2, y3);

	if (round == 1) {
		if (dist < 500)
			cout << "The shipt is at: " << x2 << " " << y2 << endl;
		else
			cout << "You see nothing." << endl;
		return 0.0;
	}
	else {
		d = ((500 - dist) / 500) * 100;
		if (d < 0)
			d = 0;
		//compute the damage done to the ship
		return d;
	}
}

void options(int &choice)
{
	do {
		cout << "Choose one of the following actions: " << endl
			<< "1) fire the cannon" << endl
			<< "2) consult radar" << endl
			<< "3) adjust the cannon's horizontal andle" << endl
			<< "4) adjust the cannon's elevation angle" << endl
			<< "5) let this ship go" << endl
			<< "6) quit the game" << endl;

		cin >> choice;
	} while (choice < 1 && choice > 6);
}

void shipValues(int &x1, int &y1, int &x2, int &y2,
	int &shipVel, double &damage, int &direct)
{
	int EoW;
	//x1,y1 = cannon
	//x2,y2= ship
	x1 = 2500;
	y1 = 0;
	// east or west
	EoW = random(1, 0);

	if (EoW == 1)
	{
		x2 = 0;
	}
	else {
		x2 = 5000;
	}

	y2 = random(5000, 100);
	shipVel = random(4000, 800);
	damage = 0.0;
	direct = random(1, 0);
}

///////TARGET////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////TARGET////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Target()
{
	int rad, x1, y1, count, hit, scount;
	double hoz, dist, x2, y2, x3, y3;
	char cont, cheat, quit;

	do {
		cout << "Would you like to cheat?" << endl;
		cin >> cheat;
	} while (cheat != 'y' && cheat != 'n');

	count = 0;
	hit = 0;
	do {
		tVals(rad, x1, y1, x2, y2);
		scount = 0;
		quit = 'w';


		cout << "The target is at " << x1 << " , " << y1 << endl;
		if (cheat != 'n')
		{
			cout << "The horizontal angle is: " << compHozAngle(x1, x2, y1, y2) << endl;
			cout << "And the distance to the target is: " << compDistance(x1, x2, y1, y2) << endl;
		}

		twoVAls(x1, y1, x3, y3);

		count++;
		hit++;
		scount++;

		if (compDistance(x2, x3, y2, y3) <= rad)
		{
			cout << "BOOM!" << endl;
		}
		else {
			do {
				cout << "Ahh looks like you missed!" << endl << endl
					<< "Better shoot again" << endl
					<< "The target is at " << x1 << " , " << y1 << endl;

				twoVAls(x1, y1, x3, y3);

				count++;
				hit++;
				scount++;
				if (scount > 5)
				{
					do {
						cout << "Do you want to give up on this target and move on to the next? (y/n)" << endl;
						cin >> quit;
					} while (quit != 'y' && quit != 'n');
				}

			} while (compDistance(x2, x3, y2, y3) <= rad && quit != 'y');

			cout << "BOOM!" << endl;
		}

		do {
			cout << "would you like to play again? (y/n)" << endl;
			cin >> cont;
		} while (cont != 'n' && cont != 'y');

	} while (cont != 'n');

	cout << "You've shot " << count << " times and hit " << hit << " times." << endl << endl;
}

void twoVAls(int x1, int y1, double &x3, double &y3) {
	int hoz;
	double dist, elev, velo;

	hozValues(elev, velo);

	do {
		cout << "Enter the horizontal angle( from 0- 180 degrees)" << endl;
		cin >> hoz;
	} while (hoz < 0 && hoz >180);

	dist = compHozDistance(elev, velo);

	compDestination(x1, y1, dist, hoz, x3, y3);
}

void tVals(int &rad, int &x1, int &y1, double &x2, double &y2)
{
	int lvl;

	x1 = 2500;
	y1 = 0;
	const int max = 5000;
	const int min = 0;

	srand(time(NULL));

	x1 = random(max, min);

	y1 = random(max, min);

	do {
		cout << "Enter the difficulty level you'd like." << endl
			<< "1: easy, 2: medium. 3: hard" << endl;
		cin >> lvl;
	} while (lvl < 1 && lvl > 3);

	if (lvl == 1)
		rad = 100;

	else if (lvl == 2)
		rad = 25;

	else if (lvl == 3)
		rad = 5;

}

///////ARTILLERY////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////ARTILLERY////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Artillery()
{
	double vert, vel, vryval;
	int rows, vary, ix;

	aValues(vert, vel, rows, vary, vryval);

	cout << "Angle | " << "Distance " << endl
		<< "______ | ________" << endl
		<< "(degs) | " << "(feet) " << endl;

	if (vary < 0) {

		for (ix = 0; ix < rows; ix++)
		{
			cout << vert << " | " << compHozDistance(vert, vel) << endl;

			vert += vryval;

		}
	}
	else {

		for (ix = 0; ix < rows; ix++)
		{
			cout << vert << " | " << compHozDistance(vert, vel) << endl;

			vel += vryval;

		}
	}
}

void aValues(double &vert, double &vel, int &rows, int &vary, double &vryval)
{
	cout << "Enter the vertical angle (in degrees)." << endl;
	cin >> vert;

	cout << "Enter the velocity (in ft.)" << endl;
	cin >> vel;

	cout << "Enter how many rows in the table" << endl;
	cin >> rows;

	do {
		cout << "Enter -1 to vary the verticle angle, or 1 to vary the velocity." << endl;
		cin >> vary;
	} while (vary != -1 || vary != 1);

	cout << "Enter How much to vary it by." << endl;
	cin >> vryval;
}


///////CALC////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////CALC////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Calcs()
{
	int choice;
	char cont;
	do {
		choice = menu();

		if (choice == 1) {
			double x1, x2, y1, y2;
			pValues(x1, x2, y1, y2);

			cout << "The distance between the two points is: "
				<< compDistance(x1, x2, y1, y2) << " ft." << endl;
		}
		else if (choice == 2) {
			double x1, x2, y1, y2;
			pValues(x1, x2, y1, y2);

			cout << "The Horizontal Angle is " << compHozAngle(x1, x2, y1, y2)
				<< " degrees." << endl;
		}


		else if (choice == 3) {
			double elev, velo;
			hozValues(elev, velo);

			cout << "The Horizantal distance traveled was: "
				<< compHozDistance(elev, velo) << " Ft." << endl;
		}

		else if (choice == 4) {
			double x2, y2, x, y, distance, hozAngle;

			destValues(x, y, distance, hozAngle);

			compDestination(x, y, distance, hozAngle, x2, y2);

			cout << "The destination point is "
				<< "(" << x2 << "," << y2 << ") ft." << endl;
		}
		cout << "Would you like to run another computation? (y/n)" << endl;
		cin >> cont;
		while (cont != 'y' && cont != 'n')
		{
			cout << "Please input y for yes or n for no (y/n)" << endl;
			cin >> cont;
		}

	} while (cont == 'y');

}

int menu()
{
	int choice;
	cout << "Please input the correspoding number to the computation you want." << endl
		<< "1. Compute the distance between the two points." << endl
		<< "2. Compute the horizontal angle from the first to the second point." << endl
		<< "3. Compute the horizontal distance an object travels." << endl
		<< "4. Compute the destination point." << endl;

	cin >> choice;
	while (choice < 1 && choice > 4)
	{
		cout << "Please input a number between 1 and 4 " << endl
			<< "that corresponds with the desired computatoin." << endl;
		cin >> choice;
	}

	return choice;
}


double compDistance(double x1, double x2, double y1, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double compHozAngle(double x1, double x2, double y1, double y2)
{
	double dx, dy, a;
	const double pi = 3.145;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx > 0)
		a = atan(dy / dx);

	else if (dx < 0)
		a = atan(dy / dx) + pi;

	else if (dx == 0 && dy >= 0)
		a = pi / 2.0;

	else
		a = -pi / 2.0;

	return a * (180 / pi);
}


double compHozDistance(double elev, double velo)
{
	double f, w;
	const double pi = 3.145;
	const double gravity = 32.172;
	const int fpm = 5280;
	const int sph = 3600;

	f = elev * (pi / 180.0);
	w = velo * (5280 / 3600.0);
	return pow(w, 2) * sin(2 * f) / gravity;
}

void compDestination(int x, int y,
	double distance, double hozAngle,
	double &x2, double &y2)
{
	double dx, dy, a;
	const double pi = 3.145;

	a = hozAngle * pi / 180.0;
	dx = distance * cos(a);
	dy = distance * sin(a);
	x2 = x + dx;
	y2 = y + dy;
}

void pValues(double &x1, double &x2, double &y1, double &y2)
{
	cout << "Please enter x1 (in ft.)." << endl;
	cin >> x1;

	cout << "Please enter x2 (in ft.)" << endl;
	cin >> x2;

	cout << "Please enter y1 (in ft.)." << endl;
	cin >> y1;

	cout << "Please enter y2 (in ft.)" << endl;
	cin >> y2;
}


void hozValues(double &elev, double &velo)
{
	cout << "Please enter the elevation. (in degrees)" << endl;
	cin >> elev;
	while (elev < 1 && elev > 89)
	{
		cout << "Please input an angle between 0 and 90 (but not 0 or 90)." << endl;
		cin >> elev;
	}

	do {
		cout << "Please enter the velocity. (in mph)" << endl
			<< "Make sure it is more than 0." << endl;
		cin >> velo;
	} while (velo < 1);
}

void destValues(double &x, double &y, double &distance, double &hozAngle)
{
	cout << "Please enter the x coordinate" << endl;
	cin >> x;

	cout << "Please enter the y coordinate" << endl;
	cin >> y;

	cout << "Please enter the distance. (in ft.)" << endl;
	cin >> distance;
	while (distance < 1)
	{
		cout << "Please input a positive number." << endl;
		cin >> distance;
	}

	cout << "Please enter the horizontal angle. (in degrees)" << endl;
	cin >> hozAngle;
	while (hozAngle < 0 && hozAngle <= 360)
	{
		cout << "Please input an angle between 0 and 360." << endl;
		cin >> hozAngle;
	}
}

int random(int max, int min) {
	srand(time(NULL));
	return rand() % (max - min + 1) + min;

}