#include <iostream>
#include <fstream>
using namespace std;

struct node{
    string val;
    node* next;
    node(string url): val(url), next(nullptr){}
};

class Stack{
private:
    int no_urls;
    node* tail;
    node* head;
public:
    Stack();
    string top();
    string pop();
    void push(string url);
    void display();
    void clear();
    bool isEmpty();
    int size();
};

Stack::Stack(): head(nullptr), no_urls(0), tail(nullptr) {}

int Stack::size() {
    return no_urls;
}

void Stack::display() {
    node* curr = head;
    cout<<"[ ";
    while(curr!= nullptr){
        cout<< curr->val;
        curr = curr->next;
        if(curr!= nullptr){
            cout<<", ";
        }else{
            cout<< ' ';
        }
    }
    cout<<"]"<<endl;
}

void Stack::clear() {
    node* curr = head;
    while(curr!= nullptr){
        node* prev = curr;
        curr = curr->next;
        delete prev;
    }
    head = nullptr;
    no_urls=0;
}

bool Stack::isEmpty() {
    if(head == nullptr){
        return true;
    }
    return false;
}

void Stack::push(string url) {
   if(head == nullptr){
       head = new node(url);
       tail = head;
   }else{
       node* newNode = new node(url);
       newNode->next = head;
       head = newNode;
   }
   no_urls++;
}

string Stack:: top(){
    return head->val;
}

string Stack:: pop(){
    if(head == nullptr){
        throw runtime_error("Stack is empty");
    }
    node* temp = head;
    string removedUrl = temp->val;
    head = head->next;
    delete temp;
    if(head == nullptr){
        tail = nullptr;
    }
    no_urls--;
    return removedUrl;
}

class BrowserHistory{
private:
    Stack BackStack;
    Stack ForwardStack;
    string currentUrl;
public:
    BrowserHistory();
    void visit(string url);
    void goBack();
    void goForward();
    void displayStatus();
    ~BrowserHistory();
};

BrowserHistory ::BrowserHistory(): currentUrl("") {}

void BrowserHistory::visit(string url) {
    cout<<"Visiting "<<url<<endl;
    if(!ForwardStack.isEmpty()){
        ForwardStack.clear();
    }
    BackStack.push(url);
    currentUrl = url;
    displayStatus();
}

void BrowserHistory::goBack() {
    if(BackStack.size()>1){
        cout<<"Went back"<<endl;
        string leftPageUrl = BackStack.pop();
        ForwardStack.push(leftPageUrl);
        currentUrl = BackStack.top();
    }else{
        cout<< "Going back is not possible!" << endl;
    }
    displayStatus();
}

void BrowserHistory::goForward() {
    if(ForwardStack.size()>0){
        cout<<"Went forward"<<endl;
        string leftPageUrl = ForwardStack.pop();
        BackStack.push(leftPageUrl);
        currentUrl = BackStack.top();
    }else{
        cout<< "Going Forward is not possible!" << endl;
    }
    displayStatus();
}

void BrowserHistory::displayStatus() {
    cout<<"Back Stack: "<<BackStack.size()<<' ';
    BackStack.display();
    cout<<"Forward Stack: "<<ForwardStack.size()<<' ';
    ForwardStack.display();
    cout<<"Current Url: "<<currentUrl<<endl;
    cout<<endl;
}

BrowserHistory::~BrowserHistory(){
    BackStack.clear();
    ForwardStack.clear();
}

int main() {
    ifstream file("Problem1.txt");
    int no_test_cases;
    file>>no_test_cases;
    for(int i=0; i< no_test_cases; i++){
        int no_lines;
        file>>no_lines;
        BrowserHistory b;
        cout<<"Test case "<<i+1<<endl;
        for (int j = 0; j < no_lines; ++j) {
            string key;
            string URL;
            file>>key;
            if(key == "Visit"){
                file>>URL;
                b.visit(URL);
            }else if(key == "Back"){
                b.goBack();
            }else if(key == "Forward"){
                b.goForward();
            }
        }
        cout<<"/////////////////////////////////////////////////////////";
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }
    return 0;
}
