
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class ParkingSlot {
public:
    int slotNumber;
    bool occupied;
    string vehicleNumber;
    string vehicleType;
    int parkingHours;

    ParkingSlot(int number) {
        slotNumber = number;
        occupied = false;
        vehicleNumber = "";
        vehicleType = "";
        parkingHours = 0;
    }

    double calculateFee() const {
        double rate;

        if (vehicleType == "Bike")
            rate = 10.0;
        else if (vehicleType == "Car")
            rate = 30.0;
        else
            rate = 50.0;

        return rate * parkingHours;
    }

    void display() const {
        cout << "\nSlot Number : " << slotNumber;
        cout << "\nStatus      : "
             << (occupied ? "Occupied" : "Available");

        if (occupied) {
            cout << "\nVehicle No. : " << vehicleNumber;
            cout << "\nVehicle Type: " << vehicleType;
            cout << "\nParking Fee : Rs. "
                 << fixed << setprecision(2)
                 << calculateFee();
        }

        cout << "\n---------------------------\n";
    }
};

class SmartParking {
private:
    vector<ParkingSlot> slots;

public:
    SmartParking(int totalSlots) {
        for (int i = 1; i <= totalSlots; i++) {
            slots.emplace_back(i);
        }
    }

    void parkVehicle() {
        string number, type;
        int hours;

        cout << "Enter vehicle number: ";
        cin >> number;

        for (const ParkingSlot& slot : slots) {
            if (slot.occupied &&
                slot.vehicleNumber == number) {
                cout << "Vehicle is already parked!\n";
                return;
            }
        }

        cout << "Enter vehicle type (Bike/Car/Bus): ";
        cin >> type;

        if (type != "Bike" && type != "Car" &&
            type != "Bus") {
            cout << "Invalid vehicle type!\n";
            return;
        }

        cout << "Enter parking duration in hours: ";
        cin >> hours;

        if (hours <= 0) {
            cout << "Invalid parking duration!\n";
            return;
        }

        for (ParkingSlot& slot : slots) {
            if (!slot.occupied) {
                slot.occupied = true;
                slot.vehicleNumber = number;
                slot.vehicleType = type;
                slot.parkingHours = hours;

                cout << "\nVehicle parked successfully!\n";
                cout << "Assigned slot: "
                     << slot.slotNumber << endl;
                return;
            }
        }

        cout << "Parking is full!\n";
    }

    void removeVehicle() {
        string number;

        cout << "Enter vehicle number to remove: ";
        cin >> number;

        for (ParkingSlot& slot : slots) {
            if (slot.occupied &&
                slot.vehicleNumber == number) {

                cout << "\nParking Fee: Rs. "
                     << fixed << setprecision(2)
                     << slot.calculateFee() << endl;

                slot.occupied = false;
                slot.vehicleNumber = "";
                slot.vehicleType = "";
                slot.parkingHours = 0;

                cout << "Vehicle removed successfully!\n";
                return;
            }
        }

        cout << "Vehicle not found!\n";
    }

    void displaySlots() const {
        cout << "\n===== PARKING SLOT STATUS =====\n";

        for (const ParkingSlot& slot : slots) {
            slot.display();
        }
    }

    void searchVehicle() const {
        string number;

        cout << "Enter vehicle number to search: ";
        cin >> number;

        for (const ParkingSlot& slot : slots) {
            if (slot.occupied &&
                slot.vehicleNumber == number) {
                cout << "Vehicle found!\n";
                slot.display();
                return;
            }
        }

        cout << "Vehicle not found in parking!\n";
    }

    void showSummary() const {
        int occupied = 0;

        for (const ParkingSlot& slot : slots) {
            if (slot.occupied)
                occupied++;
        }

        cout << "\n===== PARKING SUMMARY =====\n";
        cout << "Total slots     : " << slots.size() << endl;
        cout << "Occupied slots  : " << occupied << endl;
        cout << "Available slots : "
             << slots.size() - occupied << endl;
    }
};

int main() {
    SmartParking parking(5);
    int choice;

    do {
        cout << "\n===== SMART PARKING SYSTEM =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Display Parking Slots\n";
        cout << "4. Search Vehicle\n";
        cout << "5. Parking Summary\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            parking.parkVehicle();
            break;

        case 2:
            parking.removeVehicle();
            break;

        case 3:
            parking.displaySlots();
            break;

        case 4:
            parking.searchVehicle();
            break;

        case 5:
            parking.showSummary();
            break;

        case 6:
            cout << "Exiting Smart Parking System...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
