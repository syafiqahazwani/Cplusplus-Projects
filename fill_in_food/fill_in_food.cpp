#include <iostream>
#include <string>

int main() {
    std::string foods[5];
    int size = sizeof(foods) / sizeof(foods[0]);
    std::string temp;
    int count = 0;

    // Input loop for foods
    for (int i = 0; i < size; i++) {
        std::cout << "Enter a food you like or 'q' to quit #" << i + 1 << ": ";
        std::getline(std::cin, temp);
        
        if (temp == "q") {
            break;
        } else {
            foods[i] = temp;
            count++;
        }
    }

    // Output loop for foods
    std::cout << "You like the following food:\n";

    for (int i = 0; i < count; i++) {
        std::cout << foods[i] << '\n';
    }

    return 0;
}
