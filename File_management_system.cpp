#include <iostream>
#include <string>
using namespace std;

#define TOTAL_FILES 5
#define TOTAL_BLOCKS 10

// Inode structure
struct Inode {
    bool used;
    int blockIndex;
    int fileSize;
};

// Global structures
Inode inode[TOTAL_FILES];
string dataBlock[TOTAL_BLOCKS];
bool freeBlock[TOTAL_BLOCKS];

// Initialize file system
void initialize() {
    for (int i = 0; i < TOTAL_FILES; i++) {
        inode[i].used = false;
    }
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        freeBlock[i] = true;
    }
}

// Create file
void createFile(int id) {
    if (inode[id].used) {
        cout << "File already exists.\n";
        return;
    }

    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        if (freeBlock[i]) {
            inode[id].used = true;
            inode[id].blockIndex = i;
            inode[id].fileSize = 0;
            freeBlock[i] = false;
            cout << "File created successfully.\n";
            return;
        }
    }
    cout << "No free block available.\n";
}

// Write file
void writeFile(int id) {
    if (!inode[id].used) {
        cout << "File does not exist.\n";
        return;
    }

    cout << "Enter data: ";
    cin.ignore();
    getline(cin, dataBlock[inode[id].blockIndex]);

    inode[id].fileSize = dataBlock[inode[id].blockIndex].length();
    cout << "Data written successfully.\n";
}

// Read file
void readFile(int id) {
    if (!inode[id].used) {
        cout << "File does not exist.\n";
        return;
    }

    cout << "File Data: " << dataBlock[inode[id].blockIndex] << endl;
}

// Delete file
void deleteFile(int id) {
    if (!inode[id].used) {
        cout << "File does not exist.\n";
        return;
    }

    freeBlock[inode[id].blockIndex] = true;
    inode[id].used = false;
    cout << "File deleted successfully.\n";
}

// Main function
int main() {
    int choice, id;
    initialize();

    do {
        cout << "\n--- Simple File System ---\n";
        cout << "1. Create File\n";
        cout << "2. Write File\n";
        cout << "3. Read File\n";
        cout << "4. Delete File\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            cout << "Enter File ID (0-4): ";
            cin >> id;
        }

        switch (choice) {
            case 1: createFile(id); break;
            case 2: writeFile(id); break;
            case 3: readFile(id); break;
            case 4: deleteFile(id); break;
            case 5: cout << "Program terminated.\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
