#include <iostream>
#include <fstream>
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
    virtual void displayDetails() {
        cout << "Model Name: " << modelName << endl;
        cout << "Engine Capacity: " << engineCapacity << " cc" << endl;
        cout << "Price: $" << price << endl;
        cout << "Availability: " << (availability ? "Available" : "Sold") << endl;
        cout << "Color: " << color << endl;
    }

    // Function to sell the vehicle
    virtual void sell() {
        if (availability) {
            availability = false;
        } else {
            cout << "Vehicle is already sold." << endl;
        }
    }

    // Function to update vehicle details
    virtual void updateDetails() {
        // Code to update vehicle details
    }

    // Function to get model name
    string getModelName() const {
        return modelName;
    }

    // Function to check availability status
    bool isAvailable() const {
        return availability;
    }
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
        Vehicle::displayDetails();
    }

    // Function to get brand name
    string getBrand() const {
        return brand;
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
    void displayAllBrands() {
        cout << "Available Car Brands:" << endl;
        for (Vehicle* vehicle : vehicleList) {
            if (Car* car = dynamic_cast<Car*>(vehicle)) {
                cout << car->getBrand() << endl;
            }
        }
    }

    // Function to display models under a car brand and count the number of vehicles
    void displayModelsAndCount(const string& brand) {
        int count = 0;
        cout << "Models under " << brand << ":" << endl;
        for (Vehicle* vehicle : vehicleList) {
            if (Car* car = dynamic_cast<Car*>(vehicle)) {
                if (car->getBrand() == brand) {
                    cout << car->getModelName() << endl;
                    count++;
                }
            }
        }
        cout << "Total vehicles available: " << count << endl;
    }

    // Function to display details of a specific model
    void displayModelDetails(const string& modelName) {
        for (Vehicle* vehicle : vehicleList) {
            if (vehicle->getModelName() == modelName) {
                vehicle->displayDetails();
                break;
            }
        }
    }

    // Function to sell a vehicle
    void sellVehicle(const string& modelName) {
        for (Vehicle* vehicle : vehicleList) {
            if (vehicle->getModelName() == modelName) {
                vehicle->sell();
                break;
            }
        }
    }

    // Function to update details of a vehicle
    void updateVehicleDetails(const string& modelName) {
        for (Vehicle* vehicle : vehicleList) {
            if (vehicle->getModelName() == modelName) {
                vehicle->updateDetails();
                break;
            }
        }
    }
};

int main() {
    // Create a VehicleManager object
    VehicleManager manager;

    // Add some vehicles to the list
    manager.addVehicle(new Car("Brand1", "Model1", 1500, 20000, true, "Red"));
    manager.addVehicle(new Car("Brand1", "Model2", 1800, 25000, true, "Blue"));
    manager.addVehicle(new Car("Brand2", "Model3", 1700, 22000, true, "Black"));

    // Step 1: Display all car brands
    manager.displayAllBrands();

    // Step 2: Take input for car brand and display models and number of vehicles
    string brand;
    cout << "Enter a car brand: ";
    cin >> brand;
    manager.displayModelsAndCount(brand);

    // Step 3: Take input for model name and display details
    string modelName;
    cout << "Enter a model name: ";
    cin >> modelName;
    manager.displayModelDetails(modelName);

    // Step 4: Sell the vehicle
    manager.sellVehicle(modelName);

    // Step 5: Update the existing vehicle details
    manager.updateVehicleDetails(modelName);

    return 0;
}

