#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// 1. Mobile Phone Structure
struct Mobile {
    string id;
    string brand;
    string version;
    string seriesId;
    int year;
    int capacity; // GB
    double cost;  // Price

    void input() {
        cout << "Enter Mobile ID: "; cin >> id;
        cin.ignore();
        cout << "Enter Brand: "; getline(cin, brand);
        cout << "Enter Version/Model: "; getline(cin, version);
        cout << "Enter Series ID: "; getline(cin, seriesId);
        cout << "Enter Manufacturing Year: "; cin >> year;
        cout << "Enter Capacity (GB): "; cin >> capacity;
        cout << "Enter Cost: "; cin >> cost;
    }

    void display() const {
        cout << left << setw(10) << id 
             << setw(15) << brand 
             << setw(20) << version 
             << setw(12) << seriesId 
             << setw(10) << year 
             << setw(10) << capacity 
             << fixed << setprecision(2) << cost << endl;
    }
};

// 2. Order Structure
struct Order {
    string idOrder;
    string idCustomer;
    string address;
    vector<Mobile> items;
    string date; // Format: YYYY-MM (e.g., 2026-09)
    bool paymentStatus; // true: Paid, false: Unpaid

    double getTotalAmount() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.cost;
        }
        return total;
    }

    void display() const {
        cout << "--------------------------------------------------\n";
        cout << "Order ID: " << idOrder << " | Customer ID: " << idCustomer << endl;
        cout << "Address: " << address << endl;
        cout << "Date (YYYY-MM): " << date << endl;
        cout << "Payment Status: " << (paymentStatus ? "Paid" : "Unpaid") << endl;
        cout << "Ordered Items:\n";
        for (const auto& phone : items) {
            cout << "  + " << phone.brand << " " << phone.version << " - $" << phone.cost << endl;
        }
        cout << "TOTAL AMOUNT: $" << fixed << setprecision(2) << getTotalAmount() << endl;
        cout << "--------------------------------------------------\n";
    }
};

// 3. Shop Management Structure
struct Shop {
    string shopName;
    string shopAddress;
    vector<Mobile> mobiles; // Inventory array
    vector<Order> orders;   // Orders array

    // Function 1: Add a new mobile phone
    void addMobile() {
        cout << "\n=== ADD NEW MOBILE ===\n";
        Mobile m;
        m.input();
        mobiles.push_back(m);
        cout << "-> Mobile added successfully!\n";
    }

    // Function 2: Delete a mobile phone by ID
    void deleteMobile() {
        cout << "\n=== DELETE MOBILE ===\n";
        string id;
        cout << "Enter Mobile ID to delete: ";
        cin >> id;

        for (auto it = mobiles.begin(); it != mobiles.end(); ++it) {
            if (it->id == id) {
                mobiles.erase(it);
                cout << "-> Deleted mobile with ID: " << id << endl;
                return;
            }
        }
        cout << "-> Mobile ID not found: " << id << endl;
    }

    // Function 3: Create a new Order
    void createOrder() {
        cout << "\n=== CREATE NEW ORDER ===\n";
        if (mobiles.empty()) {
            cout << "No mobiles currently available in the shop inventory!\n";
            return;
        }

        Order ord;
        cout << "Enter Order ID: "; cin >> ord.idOrder;
        cout << "Enter Customer ID: "; cin >> ord.idCustomer;
        cin.ignore();
        cout << "Enter Delivery Address: "; getline(cin, ord.address);
        cout << "Enter Order Month/Year (YYYY-MM): "; cin >> ord.date;
        cout << "Payment Status (1: Paid, 0: Unpaid): ";
        cin >> ord.paymentStatus;

        int n;
        cout << "Enter total quantity of phones in this order: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            string mId;
            cout << " Enter Mobile ID #" << i + 1 << ": ";
            cin >> mId;
            
            bool found = false;
            for (const auto& m : mobiles) {
                if (m.id == mId) {
                    ord.items.push_back(m);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << " Mobile ID not found in shop inventory! Skipped.\n";
            }
        }

        orders.push_back(ord);
        cout << "-> Order created successfully!\n";
    }

    // Function 4: Edit Order Information
    void editOrder() {
        cout << "\n=== EDIT ORDER ===\n";
        string oId;
        cout << "Enter Order ID to edit: ";
        cin >> oId;

        for (auto& ord : orders) {
            if (ord.idOrder == oId) {
                cout << "Order found. Enter new details:\n";
                cin.ignore();
                cout << "Enter New Address: "; getline(cin, ord.address);
                cout << "Enter New Date (YYYY-MM): "; cin >> ord.date;
                cout << "Enter New Payment Status (1: Paid, 0: Unpaid): ";
                cin >> ord.paymentStatus;
                cout << "-> Order updated successfully!\n";
                return;
            }
        }
        cout << "-> Order ID not found: " << oId << endl;
    }

    // Function 5: Monthly Order Statistics
    void statOrdersByMonth() {
        cout << "\n=== MONTHLY ORDER STATISTICS ===\n";
        string targetMonth;
        cout << "Enter target month/year (Format YYYY-MM, e.g., 2026-09): ";
        cin >> targetMonth;

        int count = 0;
        double totalRevenue = 0;

        cout << "\n--- ORDERS FOR MONTH " << targetMonth << " ---\n";
        for (const auto& ord : orders) {
            if (ord.date == targetMonth) {
                ord.display();
                count++;
                totalRevenue += ord.getTotalAmount();
            }
        }

        if (count == 0) {
            cout << "No orders found for this month.\n";
        } else {
            cout << "=> Total Orders: " << count << endl;
            cout << "=> Total Revenue for the month: $" << fixed << setprecision(2) << totalRevenue << endl;
        }
    }

    // Display Inventory
    void displayMobiles() const {
        cout << "\n=== SHOP INVENTORY ===\n";
        if (mobiles.empty()) {
            cout << "Inventory is empty!\n";
            return;
        }
        cout << left << setw(10) << "ID" 
             << setw(15) << "Brand" 
             << setw(20) << "Version" 
             << setw(12) << "Series ID" 
             << setw(10) << "Year" 
             << setw(10) << "Capacity" 
             << "Cost" << endl;
        cout << string(85, '-') << endl;
        for (const auto& m : mobiles) {
            m.display();
        }
    }
};

int main() {
    Shop myShop;
    myShop.shopName = "Mobile City Shop";
    myShop.shopAddress = "123 Main Street, City";

    int choice;
    do {
        cout << "\n================ SHOP MANAGEMENT MENU ================\n";
        cout << "1. Add new mobile\n";
        cout << "2. Delete discontinued mobile\n";
        cout << "3. Create a new order\n";
        cout << "4. Edit order information\n";
        cout << "5. Monthly order statistics\n";
        cout << "6. Display shop inventory\n";
        cout << "0. Exit\n";
        cout << "======================================================\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: myShop.addMobile(); break;
            case 2: myShop.deleteMobile(); break;
            case 3: myShop.createOrder(); break;
            case 4: myShop.editOrder(); break;
            case 5: myShop.statOrdersByMonth(); break;
            case 6: myShop.displayMobiles(); break;
            case 0: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}