
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class for vehicle
class Vehicle {
protected:
    string modelName;
    int engineCapacity;
    double price;
    bool availability;
    string color;

public:
    // Constructor
    Vehicle(string modelName, int engineCapacity, double price, bool availability, string color)
        : modelName(modelName), engineCapacity(engineCapacity), price(price), availability(availability), color(color) {}

    // Virtual destructor
    virtual ~Vehicle() {}

    // Function to display vehicle details
    virtual void displayDetails() = 0;

    // Function to update vehicle details
    virtual void updateDetails() = 0;

    // Function to sell the vehicle
    virtual void sell() = 0;
};

// Derived class for Car
class Car : public Vehicle {
private:
    string brand;

public:
    Car(string brand, string modelName, int engineCapacity, double price, bool availability, string color)
        : Vehicle(modelName, engineCapacity, price, availability, color), brand(brand) {}

    // Display car details
    void displayDetails() override {
        cout << "Brand: " << brand << endl;
        cout << "Model Name: " << modelName << endl;
        cout << "Engine Capacity: " << engineCapacity << " cc" << endl;
        cout << "Price: $" << price << endl;
        cout << "Availability: " << (availability ? "Available" : "Sold") << endl;
        cout << "Color: " << color << endl;
    }

    // Update car details
    void updateDetails() override {
        // Code to update car details
    }

    // Sell the car
    void sell() override {
        if (availability) {
            availability = false;
            // Reduce total number of cars available for the brand
        } else {
            cout << "Car is already sold." << endl;
        }
    }
};

// Class to manage vehicle list
class VehicleManager {
private:
    vector<Vehicle*> vehicleList;

public:
    // Function to add a vehicle to the list
    void addVehicle(Vehicle* vehicle) {
        vehicleList.push_back(vehicle);
    }

    // Function to display details of all vehicles
    void displayAllDetails() {
        for (Vehicle* vehicle : vehicleList) {
            vehicle->displayDetails();
        }
    }

    // Function to sell a vehicle
    void sellVehicle(int index) {
        if (index >= 0 && index < vehicleList.size()) {
            vehicleList[index]->sell();
        } else {
            cout << "Invalid index." << endl;
        }
    }
};

int main() {
    // Create a VehicleManager object
    VehicleManager manager;

    // Add some vehicles to the list
    manager.addVehicle(new Car("Brand1", "Model1", 1500, 20000, true, "Red"));
    manager.addVehicle(new Car("Brand2", "Model2", 1800, 25000, true, "Blue"));

    // Display details of all vehicles
    manager.displayAllDetails();

    // Sell a vehicle
    manager.sellVehicle(0);

    // Display updated details
    manager.displayAllDetails();

    return 0;
}
