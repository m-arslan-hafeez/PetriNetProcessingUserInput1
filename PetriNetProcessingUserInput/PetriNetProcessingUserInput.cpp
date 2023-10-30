#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

// Function to generate a random 2-digit number
int generateRandom2DigitNumber(int routeNumber) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(10, 99); // 2-digit range
	return (routeNumber * 100) + dist(gen);
}

int main() {
	int totalInRoutes, totalOutRoutes;

	// Ask the user for the total number of "in" routes
	cout << "Enter the total number of 'in' routes: ";
	cin >> totalInRoutes;

	// Ask the user for the total number of "out" routes
	cout << "Enter the total number of 'out' routes: ";
	cin >> totalOutRoutes;

	cout << endl;

	// Create vectors to store the number of vehicles for "in" and "out" routes
	vector<int> vehiclesInPerRoute;
	vector<vector<int>> vehiclesOutPerRoute(totalOutRoutes);

	// Input the number of vehicles for "in" routes
	for (int i = 1; i <= totalInRoutes; i++) {
		int numVehicles;
		cout << "Enter the number of vehicles for 'in' Route " << i << ": ";
		cin >> numVehicles;
		vehiclesInPerRoute.push_back(numVehicles);
	}

	cout << endl;

	// Display the entered data for "in" routes
	cout << "Entered data for 'in' routes:" << endl;
	for (int i = 0; i < totalInRoutes; i++) {
		cout << "'in' Route " << (i + 1) << ": " << vehiclesInPerRoute[i] << " vehicles" << endl;
	}

	// Generate random 2-digit numbers for vehicles in "in" routes
	vector<vector<int>> inRouteVehicles;
	for (int inRoute = 0; inRoute < totalInRoutes; inRoute++) {
		vector<int> vehicles;
		for (int i = 0; i < vehiclesInPerRoute[inRoute]; i++) {
			int vehicleNumber = generateRandom2DigitNumber(inRoute + 1);
			vehicles.push_back(vehicleNumber);
		}
		inRouteVehicles.push_back(vehicles);
	}

	cout << endl;

	// Display the resulting data for "in" routes
	cout << "Generated 2-digit numbers for 'in' routes:" << endl;
	for (int inRoute = 0; inRoute < totalInRoutes; inRoute++) {
		cout << "'in' Route " << (inRoute + 1) << " Vehicles: ";
		for (int i = 0; i < vehiclesInPerRoute[inRoute]; i++) {
			cout << inRouteVehicles[inRoute][i] << " ";
		}
		cout << endl;
	}

	// Pass vehicles from "in" routes to "out" routes and count them
	vector<int> vehiclesPassedCount(totalOutRoutes, 0);
	for (int inRoute = 0; inRoute < totalInRoutes; inRoute++) {
		vector<int>& vehiclesOut = vehiclesOutPerRoute[inRoute % totalOutRoutes];
		vehiclesOut.insert(vehiclesOut.end(), inRouteVehicles[inRoute].begin(), inRouteVehicles[inRoute].end());
		vehiclesPassedCount[inRoute % totalOutRoutes] += inRouteVehicles[inRoute].size();
	}

	cout << endl;

	// Display the resulting data for "out" routes
	cout << "Vehicles passed from 'out' routes:" << endl;
	for (int outRoute = 0; outRoute < totalOutRoutes; outRoute++) {
		cout << "\n'out' Route " << (outRoute + 1) << " Vehicles: \n";
		for (int i = 0; i < vehiclesOutPerRoute[outRoute].size(); i++) {
			cout << vehiclesOutPerRoute[outRoute][i] << " ";
		}
		cout << "\nNumber of vehicles passed through 'out' Route " << (outRoute + 1) << ": " << vehiclesPassedCount[outRoute] << endl;
		cout << endl;
	}

	cout << endl;

	// Calculate the total number of vehicles in "in" routes
	int totalVehiclesIn = 0;
	for (int inRoute = 0; inRoute < totalInRoutes; inRoute++) {
		totalVehiclesIn += vehiclesInPerRoute[inRoute];
	}

	// Calculate the total number of vehicles passed through "out" routes
	int totalVehiclesOut = 0;
	for (int outRoute = 0; outRoute < totalOutRoutes; outRoute++) {
		totalVehiclesOut += vehiclesOutPerRoute[outRoute].size();
	}

	// Display the totals
	cout << "Total number of vehicles in 'in' routes: " << totalVehiclesIn << endl;
	cout << "Total number of vehicles passed through 'out' routes: " << totalVehiclesOut << endl;

	cout << endl;

	return 0;
}
