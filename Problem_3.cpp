#include <iostream>
#include <fstream>
using namespace std;

bool check(int*arr,int size){
    for (int i=0;i<size;i++){
        if(arr[i]==0){
        return false;
        }
 }
 return true;
}
int flip(int*arr,int size,int k){
    int counter=0;
    for (int i=0;i<=size-k;i++){
           if(arr[i]==0 ){
            for(int p=0;p<k;p++){

                arr[i+p]=1-arr[i+p];
                
            }
            counter++;
           }
    }

    if(check(arr,size)){
        return counter;
    }
    else{
        return -1;
    }
           
}
int main() {
    ifstream inFile("input_problem3.txt");
    ofstream outFile("output.txt");

    while (true) {
        int k;
        if (!(inFile >> k)) break;

       
    
 inFile.ignore();
       
        int temp[1000];
        int size = 0;
        int value;

        while (inFile >> value) {
            temp[size++] = value;
            char next = inFile.peek();
            if (next == '\n' || next == '\r'||  next == EOF) break;
        }

        
        int* arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = temp[i];
        }

        int result = flip(arr, size, k);
        outFile << result << endl;

        delete[] arr;  
    }

    inFile.close();
    outFile.close();
    return 0;

    
    

   
}