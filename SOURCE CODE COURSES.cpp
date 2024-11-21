#include <iostream>
#include <string>

using namespace std;

const int MAX_EXECUTIVES = 100; // Maximum number of executives
struct Executive {
    int executive_id;
    int program_id;
    string executive_code;
    string executive_name;
    string executive_category;
    string executive_type;
    string pre_requisite;
    string co_requisite;
    string progressive;
    string pls; // Program Learning Statement
};

// Array to store executives
Executive executives[MAX_EXECUTIVES];
int executive_count = 0; // Current number of executives

// Function prototypes
void create_executives();
void retrieve_executives();
void delete_executives();
void merge_sort_executives(int low, int high);
void binary_search_executives();
void merge_executives(int low, int mid, int high);

// Function to create a new executive
void create_executives() {
    if (executive_count >= MAX_EXECUTIVES) {
        cout << "Cannot add more executives. Maximum limit reached.\n";
        return;
    }

    Executive new_executive;
    cout << "Enter Executive ID: ";
    cin >> new_executive.executive_id;
    cout << "Enter Program ID: ";
    cin >> new_executive.program_id;
    cout << "Enter Executive Code: ";
    cin >> new_executive.executive_code;
    cout << "Enter Executive Name: ";
    cin.ignore();
    getline(cin, new_executive.executive_name);
    cout << "Enter Executive Category: ";
    getline(cin, new_executive.executive_category);
    cout << "Enter Executive Type: ";
    getline(cin, new_executive.executive_type);
    cout << "Enter Pre-requisites: ";
    getline(cin, new_executive.pre_requisite);
    cout << "Enter Co-requisites: ";
    getline(cin, new_executive.co_requisite);
    cout << "Enter Executive Progression: ";
    getline(cin, new_executive.progressive);
    cout << "Enter PLS (Program Learning Statement): ";
    getline(cin, new_executive.pls);

    executives[executive_count++] = new_executive;
    cout << "Executive created successfully.\n";
}

// Function to retrieve all executives
void retrieve_executives() {
    for (int i = 0; i < executive_count; i++) {
        Executive& e = executives[i];
        cout << "ID: " << e.executive_id << ", Program ID: " << e.program_id << ", Code: " << e.executive_code
             << ", Name: " << e.executive_name << ", Category: " << e.executive_category
             << ", Type: " << e.executive_type << ", Pre-requisite: " << e.pre_requisite
             << ", Co-requisite: " << e.co_requisite << ", Progression: " << e.progressive
             << ", PLS: " << e.pls << endl;
    }
}

// Merge function
void merge_executives(int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    Executive left[n1], right[n2];
    for (int i = 0; i < n1; i++)
        left[i] = executives[low + i];
    for (int i = 0; i < n2; i++)
        right[i] = executives[mid + 1 + i];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i].executive_code <= right[j].executive_code) {
            executives[k++] = left[i++];
        } else {
            executives[k++] = right[j++];
        }
    }
    while (i < n1) {
        executives[k++] = left[i++];
    }
    while (j < n2) {
        executives[k++] = right[j++];
    }
}

// Merge Sort function
void merge_sort_executives(int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort_executives(low, mid);
        merge_sort_executives(mid + 1, high);
        merge_executives(low, mid, high);
    }
}

// Binary Search function
void binary_search_executives() {
    string code;
    cout << "Enter executive code to search: ";
    cin >> code;

    int low = 0, high = executive_count - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (executives[mid].executive_code == code) {
            cout << "Executive Found:\n"
                 << "ID: " << executives[mid].executive_id << ", Program ID: " << executives[mid].program_id
                 << ", Code: " << executives[mid].executive_code << ", Name: " << executives[mid].executive_name
                 << ", Category: " << executives[mid].executive_category << ", Type: " << executives[mid].executive_type
                 << ", Pre-requisite: " << executives[mid].pre_requisite << ", Co-requisite: " << executives[mid].co_requisite
                 << ", Progression: " << executives[mid].progressive << ", PLS: " << executives[mid].pls << endl;
            found = true;
            break;
        } else if (executives[mid].executive_code < code) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Executive with code " << code << " not found.\n";
    }
}

// Function to delete an executive
void delete_executives() {
    int executive_id;
    cout << "Enter executive ID to delete: ";
    cin >> executive_id;

    bool found = false;
    for (int i = 0; i < executive_count; i++) {
        if (executives[i].executive_id == executive_id) {
            for (int j = i; j < executive_count - 1; j++) {
                executives[j] = executives[j + 1];
            }
            executive_count--;
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Executive deleted successfully.\n";
    } else {
        cout << "Executive with ID " << executive_id << " not found.\n";
    }
}

// Main function
int main() {
    int choice;

    do {
        cout << "\nExecutive Management System:\n";
        cout << "1. Create Executive\n";
        cout << "2. Retrieve All Executives\n";
        cout << "3. Search Executive by Code\n";
        cout << "4. Delete Executive\n";
        cout << "5. Sort Executives by Code\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                create_executives();
                break;
            case 2:
                retrieve_executives();
                break;
            case 3:
                merge_sort_executives(0, executive_count - 1); // Ensure the list is sorted before binary search
                binary_search_executives();
                break;
            case 4:
                delete_executives();
                break;
            case 5:
                merge_sort_executives(0, executive_count - 1);
                cout << "Executives sorted by code.\n";
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

