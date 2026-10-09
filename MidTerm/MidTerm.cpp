#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Fish {
private:
    int id;
    string name;
    string color;
    string characteristic;

public:
    // Constructor with all attributes
    Fish(int id, string name, string color, string characteristic)
        : id(id),
          name(move(name)),
          color(move(color)),
          characteristic(move(characteristic)) {}

    // Constructors with fewer parameters
    Fish(int id, string name, string color)
        : Fish(id, move(name), move(color), "Unknown") {}

    Fish(int id, string name)
        : Fish(id, move(name), "Unknown", "Unknown") {}

    explicit Fish(int id)
        : Fish(id, "Unknown", "Unknown", "Unknown") {}

    // Default constructor
    Fish()
        : Fish(0, "Unknown", "Unknown", "Unknown") {}

    // Getters
    int getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

    const string& getColor() const {
        return color;
    }

    const string& getCharacteristic() const {
        return characteristic;
    }

    // Setters
    void setId(int newId) {
        id = newId;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setColor(const string& newColor) {
        color = newColor;
    }

    void setCharacteristic(const string& newCharacteristic) {
        characteristic = newCharacteristic;
    }

    // Display fish information
    void displayFishInfo() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Color: " << color
             << " | Characteristic: " << characteristic
             << '\n';
    }
};

int main() {
    // Create five fish using different constructors
    Fish fish1;
    Fish fish2(101);
    Fish fish3(102, "Betta");
    Fish fish4(103, "Guppy", "Blue");
    Fish fish5(104, "Arowana", "Gold", "Symbol of luck");

    cout << "=== Fish Information ===\n";

    fish1.displayFishInfo();
    fish2.displayFishInfo();
    fish3.displayFishInfo();
    fish4.displayFishInfo();
    fish5.displayFishInfo();

    // Update fish1
    cout << "\n=== Updating Fish 1 ===\n";

    fish1.setId(100);
    fish1.setName("Koi");
    fish1.setColor("Orange and White");
    fish1.setCharacteristic("Lives in outdoor ponds");

    // Display the updated information using getters
    cout << "\n=== Updated Fish Information ===\n";

    cout << "ID: " << fish1.getId() << '\n';
    cout << "Name: " << fish1.getName() << '\n';
    cout << "Color: " << fish1.getColor() << '\n';
    cout << "Characteristic: " << fish1.getCharacteristic() << '\n';

    // Verify the changes
    cout << "\n=== Verification ===\n";
    fish1.displayFishInfo();

    return 0;
}
