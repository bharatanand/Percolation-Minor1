// Importing Libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <dos.h>

// Importing Header files
// Percolation_VizAlgo.h for Algorithm behind Vizualiation of Percolation 
// PercolationStats.h for Showing the statistical values related to Percolation trials.

#include "Percolation_VizAlgo.h"
#include "Timer.h"
#include "PercolationStats.h"

// large-scale experiments show that the percolation threshold for large systems is around 0.593

using namespace std;

void front_page() {
	cout << ("\n Welcome to our Minor Project");
	cout << ("\n An Implementation of Percolation Problem");
	cout << ("\n\n GRID 1:");
	cout << ("\n 0 0 0 1 1 1 0 1\n 0 0 0 0 0 1 0 1\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 0 0 0\n 0 0 0 0 0 0 0 0\n 0 0 0 0 0 0 0 0");
	cout << ("\n The system will not Percolate");
	cout << ("\n\n GRID 2:");
	cout << ("\n 0 0 0 1 1 1 0 1\n 0 0 0 0 0 1 0 1\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 1 0 0\n 0 0 0 0 0 1 0 0");
	cout << ("\n The system will Percolate\n");
}

// For calculating Mean in visualization
//This function will calculate the mean of all the ratios
//of the open cells
//formula = (x_1 + x_2 +........+x_n)/n
void findMean(int trials, double* ratio, double& mean)
{
	double sum = 0;
	for (int i = 0; i < trials; i++)
	{
		sum = sum + ratio[i];
	}
	mean = sum / (double)trials;
}

//this function calculates the the variance of the ratios
//utilizing the mean from above function
//formula = sqrt(((x_1 - mean)^2 + (x_2 - mean)^2 +..........+(x_n - mean)^2)/(n-1))
void Variance(int trials, double* ratio, double mean, double& sampleVar)
{
	double sum = 0;

	for (int i = 0; i < trials; i++)
	{
		sum = sum + pow((ratio[i] - mean), 2);
	}
	sampleVar = sum / (double)(trials - 1);
	sampleVar = sqrt(sampleVar);
}

//At the beginning of the program this function will
//ask for the users value to be used in the process
void getUserinputs(int& dimension, int& trials, char& answer)
{
	cout << "::::::Enter the Details for Percolation Visualization:::::: " << endl;
	cout << "Enter the Dimension of the grid: " << endl;
	cin >> dimension;
	cout << endl;
	cout << "Enter No. of trials to perform: " << endl;
	cin >> trials;
	cout << endl;
	cout << "Create the Vizualied Grid (y/n): ";
	cin >> answer;
	cout << endl;
}

int main(int argc, char* argv)
{
	
	front_page(); // Calling the front page
	cout << ("\n");
	system("PAUSE"); // Pausing the system
	system("CLS"); // Clear screen


	// Driver Code for the first Part
	int n, trials, count = 0, openCount = 0;
	char answer;

	getUserinputs(n, trials, answer);

	double* ratio = new double[trials];
	double item = 0, sampleVar = 0, mean = 0,
		confiInterval1 = 0, confiInterval2 = 0;

	//initialize random number generator
	srand(time(NULL));
	percolation system(n);

	int row_val = 0, col_val = 0;

	//now we will loop the logic of finding
	//if a system percolates or not. This will
	//loop until the total number of trials
	while (count < trials)
	{
		row_val = rand() % n;
		col_val = rand() % n;

		system.open(row_val, col_val);

		//if the system percolates
		if (system.percolates())
		{
			openCount = system.getOpenCellCount();
			item = (double)openCount / (double)(n * n);
			ratio[count] = item;

			cout << "No. of Trial: " << count << " |||| ";
			cout << "Grid Size: " << n << " |||| ";
			cout << "Open sites: " << openCount << " |||| " << "Mean Value: ";
			cout << ratio[count] << endl;
			//we increment the count for the next iteration
			count++;

			//if the last iteration is done break out of the loop
			if (count == trials)
				break;

			//if not we reset the grid and the sets used in the percolation class
			//this is done by the class provided in the header file "percolation.h"
			else
				system.resetGrid();
		}
	}

	//we now call the function to calculate
	//the mean and sample variance
	findMean(trials, ratio, mean);
	Variance(trials, ratio, mean, sampleVar);


	//this is where the confidence interval is calculated
	confiInterval1 = mean - (1.96 * sampleVar) / sqrt((double)trials);
	confiInterval2 = mean + (1.96 * sampleVar) / sqrt((double)trials);

	cout << "\nThe confidence interval: " << '(' << confiInterval1;
	cout << ", " << confiInterval2 << ')' << endl;

	if (answer == 'y' || answer == 'Y') {
		system.showFinalVisualization();
	}

	//delete the pointer to an array as we are done using it
	delete[] ratio;

	cout << ("\n");


	unsigned int nn, trials2;
	cout << "\n ::::::Enter the size for a Large matrix to verify the Result:::::: ";
	cout << "\n Enter the size of matrix: ";
	cin >> (nn);
	cout << "\n Enter the number of trials: ";
	cin >> (trials2);

	cout << "\n Please Wait, while we Process the Calculations.....\n";

	if (argc == 3) {
		nn = argv[1];
		trials2 = argv[2];
	}

	{
		// Only needed to output the total time to run the current scope, can be removed

		// Calling the Header files 
		Timer timer;
		PercolationStats percStats(nn, trials2);

		cout << ("\n");
		cout << setw(30) << "Mean:" << '\t' << setprecision(10) << percStats.getMean() << '\n';
		cout << setw(30) << "Standard Deviation:" << '\t' << percStats.getStdDev() << '\n';
		cout << setw(30) << "Confidence Interval:" << '\t' <<
			'[' << percStats.getConfidenceLow() << ", " << percStats.getConfidenceHigh() << ']' << endl;
	}
}

