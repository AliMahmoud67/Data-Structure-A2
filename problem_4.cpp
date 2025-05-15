#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct patient {
    string name;
    int severity;
    int arrivalTime;
};

class MaxHeap {
private:
    patient heap[100];
    int size;

public:
    MaxHeap() {
        size = 0;
    }

    void insert(patient p) {
        heap[size] = p;
        int current = size;
        size++;

        while (current > 0) {
            int top = (current - 1) / 2;

            bool higherPriority = 0;
            if (heap[current].severity > heap[top].severity) {
                higherPriority = 1;
            } else if (heap[current].severity == heap[top].severity &&
                       heap[current].arrivalTime < heap[top].arrivalTime) {
                higherPriority = 1;
            }

            if (higherPriority) {
                swap(heap[current], heap[top]);
                current = top;
            } else {
                break;
            }
        }
    }

    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size) {
            if (heap[left].severity > heap[largest].severity ||
                (heap[left].severity == heap[largest].severity &&
                 heap[left].arrivalTime < heap[largest].arrivalTime)) {
                largest = left;
            }
        }

        if (right < size) {
            if (heap[right].severity > heap[largest].severity ||
                (heap[right].severity == heap[largest].severity &&
                 heap[right].arrivalTime < heap[largest].arrivalTime)) {
                largest = right;
            }
        }

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

    void extract_max() {
        if (size == 0) {
            cout << "No patients to treat.\n";
            return;
        }
        patient higherPriority_Patient = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        cout << "Treating patient: " << higherPriority_Patient.name << endl;
    }

    void peek() {
        if (size == 0) {
            cout << "No patients available.\n";
            return;
        }
        cout << "Next patient to be treated: " << heap[0].name << endl;
    }

    void print_heap() {
        MaxHeap print = *this;

        cout << "Patients in order: ";
        while (print.size > 0) {
            cout << print.heap[0].name << " ";
            print.heap[0] = print.heap[print.size - 1];
            print.size--;
            print.heapify(0);
        }
        cout << endl;
    }

};

int main() {
    string fileName;
    cout << "Enter the name of the file (.txt): ";
    cin >> fileName;

    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Error opening file!\n";
        return 1;
    }

    int testCaseNum = 1;
    while (!inFile.eof()) {
        int numPatients;
        inFile >> numPatients;
        if (inFile.fail()) break;

        cout << "\n=== Test Case " << testCaseNum++ << " ===\n";
        MaxHeap heap;

        for (int i = 0; i < numPatients; ++i) {
            string name;
            int severity, arrivalTime;
            inFile >> name >> severity >> arrivalTime;
            if (inFile.fail()) break;

            patient p = {name, severity, arrivalTime};
            heap.insert(p);
        }

        int choice;
        do {
            cout << "\n========== MENU ==========\n";
            cout << "1. Treat patient (Extract)\n";
            cout << "2. Peek next patient\n";
            cout << "3. Show all patients\n";
            cout << "4. Next Test Case / Exit\n";
            cout << "Enter your choice (1-4): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    heap.extract_max();
                    break;
                case 2:
                    heap.peek();
                    break;
                case 3:
                    heap.print_heap();
                    break;
                case 4:
                    cout << "Moving on...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 4);
    }

    inFile.close();
    cout << "All test cases processed.\n";
    return 0;
}




