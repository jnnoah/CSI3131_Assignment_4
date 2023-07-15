#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: producer <number_of_catalan_numbers>\n";
        return 1;
    }

    int numCatalan = std::stoi(argv[1]);

    HANDLE sharedMemory = CreateFileMapping(
        INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(int) * (numCatalan + 1), "SharedMemory");

    if (sharedMemory == nullptr) {
        std::cout << "Error creating shared memory: " << GetLastError() << std::endl;
        return 1;
    }

    int* sharedMemoryData = static_cast<int*>(MapViewOfFile(
        sharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) * (numCatalan + 1)));

    if (sharedMemoryData == nullptr) {
        std::cout << "Error mapping shared memory: " << GetLastError() << std::endl;
        CloseHandle(sharedMemory);
        return 1;
    }

    sharedMemoryData[0] = numCatalan;

    // Generate Catalan numbers
    sharedMemoryData[1] = 1;
    for (int i = 1; i < numCatalan; i++) {
        sharedMemoryData[i + 1] = (sharedMemoryData[i] * 2 * (2 * i + 1)) / (i + 2);
    }

    UnmapViewOfFile(sharedMemoryData);
    CloseHandle(sharedMemory);

    return 0;
}
