/**
 * @file main.cpp
 * @brief Entry point for the load balancer simulation.
 *
 * Loads configuration from config.txt, prompts the user for the initial
 * server count and run duration, then initializes and runs the LoadBalancer
 * simulation, writing all events to log.txt.
 */

#include "LoadBalancer.h"
#include "Config.h"
#include "LogFile.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Prompts the user for an integer within a valid range, retrying on bad input.
 * @param prompt Text displayed to the user before reading input.
 * @param minVal Minimum accepted value (inclusive).
 * @param maxVal Maximum accepted value (inclusive).
 * @return A valid integer entered by the user within [minVal, maxVal].
 */
int getValidInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter an integer." << endl;
        } else if (value < minVal || value > maxVal) {
            cout << "Value must be between " << minVal << " and " << maxVal << "." << endl;
        } else {
            return value;
        }
    }
}

/**
 * @brief Application entry point.
 *
 * Loads simulation settings from config.txt (falls back to defaults on failure),
 * accepts user overrides for server count and run time, then runs the full
 * LoadBalancer simulation and writes results to log.txt.
 *
 * @return 0 on successful completion.
 */
int main(){
    printf("=== Load Balancer Simulation ===\n");

    Config config;
    string configFile = "config.txt";

    cout << "Loading config from file: " << configFile << endl;

    if (config.loadFromFile(configFile)) {
        cout << "Loaded successfully." << endl;
    } else {
        cout << "Failed to load config. Using default config." << endl;
    }

    cout << endl;

    int numServers = getValidInt("Enter initial number of servers (1-100): ", 1, 100);
    int runTime = getValidInt("Enter total simulation time in clock cycles (100-1000000): ", 100, 1000000);

    config.setInitServers(numServers);
    config.setTotalRunTime(runTime);

    cout << endl;
    config.printConfig();

    LogFile logFile("log.txt", true);

    LoadBalancer loadBalancer(config, &logFile);

    loadBalancer.init();

    cout << endl << "Load balancer initialized. Starting simulation..." << endl;

    loadBalancer.run();

    logFile.close();

    cout << endl << "Simulation complete. Log written to log.txt" << endl;

    return 0;

}
