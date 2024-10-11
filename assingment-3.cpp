#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
#include <climits>

int main() {
    const int size = 20;
    int arr[size];
    int minParent = INT_MAX, minChild = INT_MAX;

    // Seed the random number generator
    srand(time(0));

    // Fill the array with random numbers
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;  // Random numbers between 0 and 99
    }

    // Display the generated array
    std::cout << "Generated Array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        std::cerr << "Fork failed." << std::endl;
        return 1;
    } else if (pid == 0) {
        // Child process: Find the minimum in the second half of the array
        for (int i = size / 2; i < size; ++i) {
            if (arr[i] < minChild) {
                minChild = arr[i];
            }
        }
        std::cout << "Child Process ID: " << getpid() << ", Minimum in Second Half: " << minChild << std::endl;
    } else {
        // Parent process: Find the minimum in the first half of the array
        for (int i = 0; i < size / 2; ++i) {
            if (arr[i] < minParent) {
                minParent = arr[i];
            }
        }
        // Wait for child process to complete
        wait(NULL);

        std::cout << "Parent Process ID: " << getpid() << ", Minimum in First Half: " << minParent << std::endl;

        // Calculate the overall minimum of the array
        int overallMin = (minParent < minChild) ? minParent : minChild;
        std::cout << "Overall Minimum: " << overallMin << std::endl;
    }

    return 0;
}