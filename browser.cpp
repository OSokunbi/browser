#include <iostream>
#include <vector>

using namespace std;

struct Website{
    string val;
    Website* next = NULL;
    Website* prev = NULL;
};

class Tab {
public:
    Website* curr = NULL;
    Tab(string homepage) {
        curr = new Website();
        curr->val = homepage;
    }

    void visit(string url) {
        Website* temp = new Website();
        temp->val = url;
        curr->next = temp;
        temp->prev = curr;
        curr = temp;
        return;
    }

    string back(int steps) {
        while(curr->prev && steps > 0){
            curr = curr->prev;
            steps--;
        }
        return curr->val;
    }

    string forward(int steps) {
        while(curr->next && steps > 0){
            curr = curr->next;
            steps--;
        }
        return curr->val;
    }

    friend ostream& operator<<(ostream& os, Tab& tab){
        os << tab.curr->val;
        return os;
    }
    ~Tab() {
        Website* current = curr;
        while (current != nullptr) {
            Website* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class Browser{
private:
    string name;
public:
    vector<Tab*> tabs;
    Browser(string name) : name(name){
        this->add_tab();
    }

    void add_tab(){
        string content;
        cout << "Enter content/site link: ";
        cin >> content;
        cout << endl;
        Tab* newTab = new Tab(content);
        tabs.push_back(newTab);
        this->open_tab(tabs.size() - 1);
    }

    void close_browser(){
        cerr << "Browser Closed" << endl;
        std::exit(1);
    }

    void close_tab(int index){
        if (index >= 0 && index < tabs.size()) {
            delete tabs[index];
            tabs.erase(tabs.begin() + index);
        }
        else {
            cout << "ERRROR: Invalid tab index" << endl;
        }
        if(tabs.empty()){
            close_browser();
        }
    }

    void open_tab(int index){
        if (index >= 0 && index < tabs.size()) {
            Tab* openedTab = tabs[index];
            cout << "Browser Instructions:\nType 'close' to close this tab 'add' to add a new tab or 'open' to open a new tab" << endl;
            cout << "Tab instructions:\nType 'forward' or 'back'to go to further or backwards in the histroy of the tab by a certian amount of steps";
            cout << "\nType 'visit to visit a new link in the tab" << endl;
            string input;
            cin >> input;
            if(input == "close") close_tab(index);
            while(input != "close"){
                if(input == "add"){
                    add_tab();
                }
                else if(input == "open"){
                    cout << *this;
                    int index;
                    cout << "Enter index of tab to open: ";
                    cin >> index;
                    cout << endl;
                    open_tab(index);
                    cout << "Enter command: ";
                    cin >> input;
                }
                else if(input == "forward"){
                    int steps;
                    cout << "How many steps forward would you like to go: ";
                    cin >> steps;
                    cout << endl;
                    cout << openedTab->forward(steps) << endl;
                    cout << "Enter command: ";
                    cin >> input;
                }
                else if(input == "back"){
                    int steps;
                    cout << "How many steps backward would you like to go: ";
                    cin >> steps;
                    cout << endl;
                    cout << openedTab->back(steps) << endl;
                    cout << "Enter command: ";
                    cin >> input;
                }
                else if(input == "visit"){
                    string content;
                    cout << "Enter content/site link: ";
                    cin >> content;
                    cout << endl;
                    openedTab->visit(content);
                    cout << "Enter command: ";
                    cin >> input;
                }
            }
        }
        else {
            cout << "ERRROR: Invalid tab index" << endl;
        }
    }

    friend ostream& operator<<(ostream& os, Browser& browser){
        for(Tab* tab : browser.tabs){
            os << *tab << " ";
        }
        os << endl;
        return os;
    }

    ~Browser() {
        for (Tab* tab : tabs) {
            delete tab;
        }
        tabs.clear();
    }
};

int main(){
    Browser safari("safari");
}
