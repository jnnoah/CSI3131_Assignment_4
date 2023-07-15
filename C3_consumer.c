#include <iostream>
#include <Windows.h>

int main() {
    HANDLE sharedMemory = OpenFileMapping(FILE_MAP_READ, FALSE, "SharedMemory");

    if (sharedMemory == nullptr) {
        std::cout << "Error opening shared memory: " << GetLastError() << std::endl;
        return 1;
    }

    int* sharedMemoryData = static_cast<int*>(MapViewOfFile(
        sharedMemory, FILE_MAP_READ, 0, 0, 0));

    if (sharedMemoryData == nullptr) {
        std::cout << "Error mapping shared memory: " << GetLastError() << std::endl;
        CloseHandle(sharedMemory);
        return 1;
    }

    int numCatalan = sharedMemoryData[0];

    std::cout << "Catalan numbers: ";
    for (int i = 0; i < numCatalan; i++) {
        std::cout << sharedMemoryData[i + 1] << " ";
    }
    std::cout << std::endl;

    UnmapViewOfFile(sharedMemoryData);
    CloseHandle(sharedMemory);

    return 0;
}
