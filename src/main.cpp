#include "LoadBalancer.h"
#include "Config.h"
#include "LogFile.h"
#include <iostream>
#include <string>

using namespace std;

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