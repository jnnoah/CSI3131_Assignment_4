// Group 62 
// ---------
// Names: Nadege Uwurukundo Mpore ; SI: 300088681
// Names: Noah Ndahirwa;  SI:300152285

#include <iostream>
#include <Windows.h>

int main() {
    // Open the shared memory
    HANDLE sharedMemory = OpenFileMapping(FILE_MAP_READ, FALSE, "SharedMemory");

    if (sharedMemory == nullptr) {
        // Error handling if shared memory fails to open
        std::cout << "Error opening shared memory: " << GetLastError() << std::endl;
        return 1;
    }

    // Map the shared memory to a pointer
    int* sharedMemoryData = static_cast<int*>(MapViewOfFile(sharedMemory, FILE_MAP_READ, 0, 0, 0));

    if (sharedMemoryData == nullptr) {
        // Error handling if mapping shared memory fails
        std::cout << "Error mapping shared memory: " << GetLastError() << std::endl;
        CloseHandle(sharedMemory);
        return 1;
    }

    // Retrieve the number of Catalan numbers stored in shared memory
    int numCatalan = sharedMemoryData[0];

    // Print the Catalan numbers
    std::cout << "Catalan numbers: ";
    for (int i = 0; i < numCatalan; i++) {
        std::cout << sharedMemoryData[i + 1] << " ";
    }
    std::cout << std::endl;

    // Release the shared memory and clean up resources
    UnmapViewOfFile(sharedMemoryData);
    CloseHandle(sharedMemory);

    return 0;
}

