#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Contact{
    string name; // full name
    string phone;
    string email;
};

template <typename T>
class Vector{
private:
    T* arr;
    int length;
    int capacity;

    void resize(){
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < length; i++){
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
public:
    Vector(){
        length = 0;
        capacity = 1;
        arr = new T[capacity];
    }

    //copy constructor
    Vector (const Vector& other){
        arr = new T[other.capacity];
        length = other.length;
        capacity = other.capacity;
    
        for (int i = 0; i < length; ++i)
            arr[i] = other.arr[i];
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] arr;
            capacity = other.capacity;
            length   = other.length;
            arr = new T[capacity];
            for (int i = 0; i < length; ++i)
                arr[i] = other.arr[i];
        }
        return *this;
    }

    void push_back(T val) {
        if (length == capacity) {
            resize();
        }
        arr[length++] = val;
    }
    bool empty(){
        return length == 0;
    }
    int size() const {
        return length;
    }
    ~Vector(){
        delete[] arr;
    }
    
    T& operator[](int index) {
        return arr[index];
    }

};


struct AVLNode{
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    Contact* contactInfo;
    int key;
    int height = 1;
    AVLNode(int key, Contact* con){
        contactInfo = con;
        this->key = key;
    }
};

class AdressBook{
private:
    AVLNode* root;
    int n;

    void DisplayAllContacts(AVLNode* node){
        if(node != nullptr){ // In-Order Traverse Sorts the data automatically
            DisplayAllContacts(node->left);
            cout << "ID: "<< (node->key) << ", Name: " << (node->contactInfo->name) << ", Phone: " << (node->contactInfo->phone) << ", Email: " << (node->contactInfo->email) << "\n";
            DisplayAllContacts(node->right); 
        }   
    }
    void outputFile(AVLNode* node, ofstream& file){
        if(node != nullptr){ 
            outputFile(node->left, file);
            file << node->key << "\n";
            file << node->contactInfo->name << "\n";
            file << node->contactInfo->phone << "\n";
            file << node->contactInfo->email << "\n";
            outputFile(node->right, file); 
        }   
    }
   
    AVLNode* insert(AVLNode* node, int key, Contact* con, bool & inserted) {
        if (node == nullptr) {
            inserted = true;
            return new AVLNode(key, con);
        }

        if (key < node->key)
            node->left = insert(node->left, key, con, inserted);
        else if (key > node->key)
            node->right = insert(node->right, key, con, inserted);
        else {// inserted key
            inserted = false;
            return node; 
        }

            
        // Update height
        node->height = 1 + max(getheight(node->left), getheight(node->right));

        int balance = getheight(node->left) - getheight(node->right);

        // Balance cases
        if (balance > 1 && key < node->left->key)  // Left Left
            return rotateRight(node);

        if (balance < -1 && key > node->right->key)  // Right Right
            return rotateLeft(node);

        if (balance > 1 && key > node->left->key) {  // Left Right
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {  // Right Left
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
}
public:
    AdressBook(){
        root = nullptr;
        n = 0;
    }

    bool insertContact(int key, Contact* con){
            bool inserted = false;
            root = insert(root, key, con, inserted);
            if (inserted){
                n++;
            }
            
            return inserted;
    }

    Contact* search(int k){
        AVLNode* temp = root;

        while(temp != nullptr){
            if (k == temp->key){
                return temp->contactInfo;
            }else if(k < temp->key){
                temp = temp->left;
            }else{
                temp = temp->right;
            }
        }  
        return nullptr;      
    }

    int getheight(AVLNode* node){
        if (node == nullptr){
            return 0;
        }else{
            return node->height;
        }
        
    }

    AVLNode* rotateRight(AVLNode *n){
        AVLNode *leftChild = n->left;
        AVLNode *leftRightGrandChild = leftChild->right;

        leftChild->right = n;
        n->left = leftRightGrandChild;

        n->height = max(getheight(n->left), getheight(n->right)) + 1;
        leftChild->height = max(getheight(leftChild->left), getheight(leftChild->right)) + 1;

        return leftChild;
}

    AVLNode* rotateLeft(AVLNode *n){
        AVLNode *rightChild = n->right;
        AVLNode *rightLeftGrandChild = rightChild->left;

        rightChild->left = n;
        n->right = rightLeftGrandChild;

       n->height = max(getheight(n->left), getheight(n->right)) + 1;
        rightChild->height = max(getheight(rightChild->left), getheight(rightChild->right)) + 1;

        return rightChild;
}

    void output_to_file(ofstream& file){
        outputFile(root, file);
    }
    void Display(){
    cout << "Contacts in Address Book (sorted by ID):\n";
    DisplayAllContacts(root);
}
    
Vector<string> buildTree(AVLNode* root, int currDepth = 0, bool isLeft = false) {
        if (root == nullptr){
            Vector<string> re;
            return re;
        }
            

        string NodeValue = to_string(root->key);

        if (root->left == nullptr && root->right == nullptr){
            Vector<string> re;
            re.push_back(NodeValue);
            return re;
        }
            

        Vector<string> leftLines  = buildTree(root->left, currDepth + 1, true);
        Vector<string> rightLines = buildTree(root->right, currDepth + 1, false);

        int leftWidth,rightWidth;
        if (leftLines.empty()) {
            leftWidth = 0;
        } 
        else {
            leftWidth = leftLines[0].size();
        }
        if (rightLines.empty()) {
            rightWidth = 0;
        } 
        else {
            rightWidth = rightLines[0].size();
        }
        int labelWidth = NodeValue.size();

        int firstLineWidth = leftWidth + labelWidth + rightWidth;
        stringstream line1, line2;
        if (leftWidth > 0) {
            line1 << string(leftWidth, ' ');
        }
        line1 << NodeValue;
        if (rightWidth > 0) {
            line1 << string(rightWidth, ' ');
        }
        if (leftWidth > 0) {
            line2 << string(leftWidth - 1, ' ') << "/";
        }
        line2 << string(labelWidth, ' ');
        if (rightWidth > 0) {
            line2 << "\\" << string(rightWidth - 1, ' ');
        }

        // Merge lines
        Vector<string> result;
        result.push_back(line1.str());
        result.push_back(line2.str());

        int maxHeight = max(leftLines.size(), rightLines.size());
        for (int i = 0; i < maxHeight; ++i) {
            string leftLine;
            if (i < leftLines.size()) {
                leftLine = leftLines[i];
            } 
            else {
                leftLine = string(leftWidth, ' ');
            }
            string rightLine;
            if (i < rightLines.size()) {
                rightLine = rightLines[i];
            } 
            else {
                rightLine = string(rightWidth, ' ');
            }
            string Merged = leftLine + string(labelWidth, ' ') + rightLine;
            result.push_back(Merged);

        }

        return result;
    }

    void displayTree() {
        if (root == nullptr) {
            cout << "The tree is empty" << endl;
            return;
        }

        Vector<string> lines = buildTree(root);
        for (int i = 0;i < lines.size(); i++) {
            cout << lines[i] << endl;
        }
    }

};



string input(string ms) 
{
    string d;
    cout << ms;
    getline(cin >> ws, d); 
    return d;
}

string isValidChoice(string Msg, int n){ 
    while (true)
    {
        bool isVal = false;
        for (int i = 1; i <= n; i++){
            if (Msg == to_string(i)){
                isVal = true;
            }
        }
        
        if(isVal)
            return Msg;
        else{
            cout << "Please choose a valid choice: ";
            getline(cin >> ws, Msg); // enter the message again
        }
    }
    
}

string isValidChoiceYN(string Msg){
    while (true)
    {   
        if(Msg == "Y" || Msg == "y" || Msg == "N" || Msg == "n")
            return Msg;
        else{
            cout << "Please choose a valid choice (y/n): ";
            getline(cin >> ws, Msg); // enter the message again
        }
    }
}

int isVaildInt(string Msg){
    int a;
    while (true){
        bool first_check = true; //this var makes me able to continue and start the next iteration of the while loop

        for (int i = 0; i < Msg.length(); i++){ // check if msg only contain digits
            if(isdigit(Msg[i])){
                continue;
            }else{
            first_check = false;
            cout << "Not an Integer Please enter again: ";
            getline(cin >> ws, Msg);
            break;
            }
        }
        
        if(first_check == false){
        continue; // to return to the while loop again
        }
        a = stoi(Msg);
        return a;
    }
}

int main(){
    cout << "---Welcome to Adress Book Application---\n";
    AdressBook adress;
    while (true){
        cout << "------------------------ \n1. Add Contacts Directly From a File\n2. Add New Contact Manualy\n3. Search for Contact \n4. List All Contacts (Sorted by ID) \n5. Display Current Tree Structure\n6- Output Contacts In a file\n ------------------------\n";
        string choice = isValidChoice(input("Enter operation (1-6): "), 6);
        if (choice == "1"){
            ifstream contactFile;
            contactFile.open("Contacts Data.txt");
            if (!contactFile.is_open()){
                cout << "Error Opening Contact Info File\n";
                continue;
            }    
            string line; // takes value of each line
            int duplicateIter = 0;
            int duplicatedIDs[10]; // put duplicated ids here, assume user won't duplicate more than 10 ids since i can't use a vector to expad the array size dynamically
            for (int i = 0; i < 10; i++){
                duplicatedIDs[i] = -1; // a mark that this number isn't a duplicated id
            }
            while (!contactFile.eof()){
                //----Seperate File into 4-line Chunks each chunk represents a Contact
                int id;
                Contact* con = new Contact;
                getline(contactFile, line);//take First line in the file that should be the ID of the Contact
                id = stoi(line);
                getline(contactFile, line);//take second line in the file that should be the Name of the Contact
                con->name = line;
                getline(contactFile, line);//take third line in the file that should be the Phone of the Contact
                con->phone = line;
                getline(contactFile, line);//take Fourth line in the file that should be the Email of the Contact
                con->email = line;

                //-- Inserting the contacts
                
                bool isInsrted = adress.insertContact(id, con);
                if (!isInsrted){ 
                    duplicatedIDs[duplicateIter] = id;
                    duplicateIter++;
                }
            } 
            contactFile.close(); 
            if (duplicatedIDs[0] != -1){ // Duplicate found
                cout << "there is Duplicated IDs: [";
                for (int i = 0; i < 10; i++){
                   if (duplicatedIDs[i] != -1){
                        cout << duplicatedIDs[i] << ", ";
                   }
                }
                cout << "]\n";
            }
            // adress.Display();
                      
        }else if(choice == "2"){
            int id;
            Contact* con = new Contact;
            cout << "Enter unique ID (integer): ";
            // ensuring user inputs an integer
            string tempID;
            getline(cin, tempID);
            id = isVaildInt(tempID);
            
            cout << "Enter Name: ";
            getline(cin, con->name);
            cout << "Enter Phone: ";
            getline(cin, con->phone);
            cout << "Enter Email: ";
            getline(cin, con->email);

            bool isInserted = adress.insertContact(id, con);
            if (isInserted){
                cout << "Contact added successfully.\n";
            }else{
                cout << "Error: Contact with ID " << id << " already exists\n";
            }
        }else if(choice == "3"){
            int id;
            Contact* con = new Contact;
            cout << "Enter ID to search: ";
            // ensuring user inputs an integer
            string tempID;
            getline(cin, tempID);
            id = isVaildInt(tempID);

            con = adress.search(id);
            if (con != nullptr){
                cout << "Contact Found:\nID: " << id;
                cout << "\nName: " << con->name;
                cout << "\nPhone: " << con->phone;   
                cout << "\nEmail: " << con->email << "\n";   
            }else{
                cout << "Contact not found.\n";
            }
            
        }else if(choice == "4"){
            adress.Display();
        }else if(choice == "5"){
            adress.displayTree();
        }else if(choice == "6"){
            ofstream outputFile;
            string filename;
            cout << "Enter Desired name for the file: ";
            getline(cin, filename);
            if (filename.find('.') == string::npos) {
                filename += ".txt";  // Append .txt if no extension was provided
            }

            outputFile.open(filename);
            if (outputFile.is_open()){
                adress.output_to_file(outputFile);
                cout << "Conacts saved to a File Succesfuly.\n";
            }
            
        }
        
        choice = input("\nDo you want to make another operation (y/n): ");
        choice = isValidChoiceYN(choice);
        if (tolower(choice[0]) == 'n'){
            cout << "Thank you for using Adress Book Application! Goodbye!";
            break;
        }
    }

    // Vector<string> A;
    // A.push_back("Ali");
    // A.push_back("BA");
    // for (int i = 0; i < A.size(); i++){
    //     cout << A[i];
    // }
    
    
   

}