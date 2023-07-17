// Group 62 
// ---------
// Names: Nadege Uwurukundo Mpore ; SI: 300088681
// Names: Noah Ndahirwa;  SI:300152285

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FRAMES 7
#define PAGE_RANGE 10

// Function to generate a random page-reference string
void generatePageReferences(int pageReferences[], int numReferences) {
    srand(time(NULL));
    for (int i = 0; i < numReferences; i++) {
        pageReferences[i] = rand() % PAGE_RANGE;
    }
}

// Function to check if a page exists in the page frame
bool isPageExists(int pageFrame[], int numFrames, int pageNumber) {
    for (int i = 0; i < numFrames; i++) {
        if (pageFrame[i] == pageNumber) {
            return true;
        }
    }
    return false;
}

// Function to find the index of the page to be replaced using FIFO algorithm
int getFIFOReplacementIndex(int pageFrame[], int numFrames, int currentIndex) {
    return (currentIndex + 1) % numFrames;
}

// Function to find the index of the page to be replaced using LRU algorithm
int getLRUReplacementIndex(int pageFrame[], int numFrames, int pageReferences[], int currentIndex) {
    int lruIndex = 0;
    int lruCounter = currentIndex;
    for (int i = 0; i < numFrames; i++) {
        int j = currentIndex;
        while (j >= 0) {
            if (pageReferences[j] == pageFrame[i]) {
                if (j < lruCounter) {
                    lruCounter = j;
                    lruIndex = i;
                }
                break;
            }
            j--;
        }
        if (j == -1) {
            return i;
        }
    }
    return lruIndex;
}

// Function to simulate the FIFO page-replacement algorithm
int simulateFIFO(int pageReferences[], int numReferences, int numFrames) {
    int pageFaults = 0;
    int currentIndex = 0;
    int pageFrame[MAX_FRAMES] = {0};

    for (int i = 0; i < numReferences; i++) {
        int pageNumber = pageReferences[i];
        if (!isPageExists(pageFrame, numFrames, pageNumber)) {
            pageFaults++;
            int replaceIndex = getFIFOReplacementIndex(pageFrame, numFrames, currentIndex);
            pageFrame[replaceIndex] = pageNumber;
            currentIndex = replaceIndex;
        }
        currentIndex = (currentIndex + 1) % numFrames;
    }
    return pageFaults;
}

// Function to simulate the LRU page-replacement algorithm
int simulateLRU(int pageReferences[], int numReferences, int numFrames) {
    int pageFaults = 0;
    int currentIndex = 0;
    int pageFrame[MAX_FRAMES] = {0};

    for (int i = 0; i < numReferences; i++) {
        int pageNumber = pageReferences[i];
        if (!isPageExists(pageFrame, numFrames, pageNumber)) {
            pageFaults++;
            int replaceIndex = getLRUReplacementIndex(pageFrame, numFrames, pageReferences, currentIndex);
            pageFrame[replaceIndex] = pageNumber;
            currentIndex = replaceIndex;
        }
        currentIndex = (currentIndex + 1) % numFrames;
    }
    return pageFaults;
}

int main() {
    int numReferences = 100;  // Number of page references to generate

    int pageReferences[numReferences];
    generatePageReferences(pageReferences, numReferences);

    printf("Number of page frames\tFIFO Page Faults\tLRU Page Faults\n");
    for (int numFrames = 1; numFrames <= MAX_FRAMES; numFrames++) {
        int fifoPageFaults = simulateFIFO(pageReferences, numReferences, numFrames);
        int lruPageFaults = simulateLRU(pageReferences, numReferences, numFrames);
        printf("%d\t\t\t%d\t\t%d\n", numFrames, fifoPageFaults, lruPageFaults);
    }

    return 0;
}
