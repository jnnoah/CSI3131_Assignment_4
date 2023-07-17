// Group 62 
// ---------
// Names: Nadege Uwurukundo Mpore ; SI: 300088681
// Names: Noah Ndahirwa;  SI:300152285

#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // Check if the number of arguments is insufficient
        std::cout << "Usage: producer <number_of_catalan_numbers>\n";
        return 1;
    }

    // Retrieve the number of Catalan numbers from command line argument
    int numCatalan = std::stoi(argv[1]);

    // Create a shared memory object
    HANDLE sharedMemory = CreateFileMapping(
        INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(int) * (numCatalan + 1), "SharedMemory");

    if (sharedMemory == nullptr) {
        // Error handling if shared memory creation fails
        std::cout << "Error creating shared memory: " << GetLastError() << std::endl;
        return 1;
    }

    // Map the shared memory to a pointer
    int* sharedMemoryData = static_cast<int*>(MapViewOfFile(
        sharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) * (numCatalan + 1)));

    if (sharedMemoryData == nullptr) {
        // Error handling if mapping shared memory fails
        std::cout << "Error mapping shared memory: " << GetLastError() << std::endl;
        CloseHandle(sharedMemory);
        return 1;
    }

    // Store the number of Catalan numbers in shared memory
    sharedMemoryData[0] = numCatalan;

    // Generate Catalan numbers
    sharedMemoryData[1] = 1;
    for (int i = 1; i < numCatalan; i++) {
        sharedMemoryData[i + 1] = (sharedMemoryData[i] * 2 * (2 * i + 1)) / (i + 2);
    }

    // Release the shared memory and clean up resources
    UnmapViewOfFile(sharedMemoryData);
    CloseHandle(sharedMemory);

    return 0;
}
