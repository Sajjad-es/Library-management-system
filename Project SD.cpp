#include <iostream>
using namespace std;

class Node;

class Event {
private:
    int id;
    int timestamp;
    string category;
    string description;
    Node *root;
    int comparisonCount;
    void calculateDepthSum(Node*, int, int&, int&);
    void inorder(Node*);
    int height(Node*);
    void countCategoriesHelper(Node*, int, int, string[], int [] , int&, int&);

public:
    Event();
    Event(int, int, string, string);
    void Insert(Event);
    void Delete(int);
    void search(int);
    void InOrder();
    int Height();
    void getEventsBetween(int, int);
    void findClosestEvent(int);
    void countCategories(int, int);
    int AverageDepthOfNodes();
    int Max(int, int);
    void resetComparisons();
    int getComparisons();
};

class Node {
public:
    Event data;
    Node* left;
    Node* right;
    Node(Event);
};

Node::Node(Event e) {
    data = e;
    left = nullptr;
    right = nullptr;
}

Event::Event() {
    id = 0;
    timestamp = 0;
    category = "";
    description = "";
    root = NULL;
    comparisonCount = 0;
}

Event::Event(int i, int t, string c, string d) {
    id = i;
    timestamp = t;
    category = c;
    description = d;
    root = NULL;
    comparisonCount = 0;
}

void Event::resetComparisons() {
    comparisonCount = 0;
}

int Event::getComparisons() {
    return comparisonCount;
}
void Event::Insert(Event e) {
    comparisonCount = 0;
    if (!root) {
        root = new Node(e);
    } else {
        Node* ptr = root;
        Node* pre = NULL;
        while(ptr) {
            comparisonCount++;
            pre = ptr;
            if(e.timestamp <= ptr->data.timestamp)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        ptr = new Node(e);
        if(e.timestamp <= pre->data.timestamp)
            pre->left = ptr;
        else
            pre->right = ptr;
    }
    cout << "...Event added..."<<endl;
    cout << ".........................." << endl;
    cout << "tedade moghaese: " << comparisonCount << endl;
    cout << ".........................." << endl;
}

void Event::Delete(int t) {
    comparisonCount = 0;
    if (!root){
    cout << "we have not any event"<<endl;
        return;}
    
    Node* ptr = root;
    Node* pre = NULL;
    
    while (ptr && ptr->data.timestamp != t) {
        comparisonCount++;
        pre = ptr;
        if(ptr->data.timestamp > t)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    
    if(!ptr){
     cout << "Event not found" << endl;
        return;
    }
    
    if(!ptr->left && !ptr->right) {
        if(pre) {
            if(pre->left == ptr)
                pre->left = NULL;
            else
                pre->right = NULL;
        }
         else {
            root = NULL;
         }
        delete ptr;
    }
    else if(!ptr->left && ptr->right) {
        if(pre) {
            if(pre->left == ptr)
                pre->left = ptr->right;
            else
                pre->right = ptr->right;
        } else {
            root = ptr->right;
        }
        delete ptr;
    }
    else if(ptr->left && !ptr->right) {
        if(pre) {
            if(pre->left == ptr)
                pre->left = ptr->left;
            else
                pre->right = ptr->left;
        } else {
            root = ptr->left;
        }
        delete ptr;
    }
    else {
        Node* successorParent = ptr;
        Node* successor = ptr->right;
        
        while(successor->left) {
            successorParent = successor;
            successor = successor->left;
        }
        
        ptr->data = successor->data;
        
        if(successorParent == ptr)
            successorParent->right = successor->right;
        else
            successorParent->left = successor->right;
        
        delete successor;
    }
    cout << "...Event Deleted..." << endl;
    cout << ".........................." << endl;
    cout << "tedade moghaese: " << comparisonCount << endl;
    cout << ".........................." << endl;
}

void Event::search(int t) {
     comparisonCount = 0;
     if (!root){
    cout << "we have not any event"<<endl;
        return;
    }
    Node* ptr = root;
    while(ptr) {
        comparisonCount++;
        if(ptr->data.timestamp == t) {
            cout << "Event found: " << endl 
                 << "Event ID: " << ptr->data.id << endl
                 << "Timestamp: " << ptr->data.timestamp << endl
                 << "Category: " << ptr->data.category << endl
                 << "Description: " << ptr->data.description << endl;
                 cout << ".........................." << endl;
                 cout << "tedade moghaese: " << comparisonCount << endl;
                 cout << ".........................." << endl;
            return;
        }
        if(ptr->data.timestamp > t)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    cout << "Event not found" << endl;
    cout << ".........................." << endl;
    cout << "tedade moghaese: " << comparisonCount << endl;
    cout << ".........................." << endl;
}

void Event::InOrder() {
    inorder(root);
}

void Event::inorder(Node* r) {
    if(r) {
        inorder(r->left);
        cout << "Event ID: " << r->data.id << endl
             << "Timestamp: " << r->data.timestamp << endl
             << "Category: " << r->data.category << endl
             << "Description: " << r->data.description << endl
             << ".........................." << endl;
        inorder(r->right);
    }
}

int Event::Height() {
    return height(root);
}

int Event::height(Node* r) {
    if(!r)
        return 0;
    return 1 + Max(height(r->left), height(r->right));
}

void Event::getEventsBetween(int t1, int t2) {
    comparisonCount = 0;
    int max, min;
    max = Max(t1, t2);
    min = (t1 == max) ? t2 : t1;
    
    cout << "Events between " << min << " and " << max << ":" << endl;
    
    for (int i = min; i <= max; ++i) {
        Node* ptr = root;
        bool found = false;
        
        while(ptr) {
            comparisonCount++;
            if(ptr->data.timestamp == i) {
                cout << "Event at timestamp " << i << ":" << endl
                     << "Event ID: " << ptr->data.id << endl
                     << "Category: " << ptr->data.category << endl
                     << "Description: " << ptr->data.description << endl
                     << ".........................." << endl;
                found = true;
                break;
            }
            if(ptr->data.timestamp > i)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        
        if(!found) {
            cout << "Event at timestamp " << i << ": not available" << endl;
        }
    }
    cout << ".........................." << endl;
    cout << "tedade moghaese: " << comparisonCount << endl;
    cout << ".........................." << endl;
}

void Event::findClosestEvent(int t) {
    if (!root){
    cout << "we have not any event"<<endl;
        return;
    }
    
    comparisonCount = 0;
    int up = t + 1;
    int down = t - 1;
    
    while(true) {
        Node* ptr = root;
        while(ptr) {
            comparisonCount++;
            if(ptr->data.timestamp == up) {
                cout << "Closest Event:" << endl
                     << "Timestamp: " << ptr->data.timestamp << endl
                     << "Event ID: " << ptr->data.id << endl
                     << "Category: " << ptr->data.category << endl
                     << "Description: " << ptr->data.description << endl;
                     cout << ".........................." << endl;
                     cout << "tedade moghaese: " << comparisonCount << endl;
                     cout << ".........................." << endl;
                return;
            }
            if(ptr->data.timestamp > up)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        
        Node* pre = root;
        while(pre) {
            comparisonCount++;
            if(pre->data.timestamp == down) {
                cout << "Closest Event:" << endl
                     << "Timestamp: " << pre->data.timestamp << endl
                     << "Event ID: " << pre->data.id << endl
                     << "Category: " << pre->data.category << endl
                     << "Description: " << pre->data.description << endl;
                     cout << ".........................." << endl;
                     cout << "tedade moghaese: " << comparisonCount << endl;
                     cout << ".........................." << endl;
                return;
            }
            if(pre->data.timestamp > down)
                pre = pre->left;
            else
                pre = pre->right;
        }
        up++;
        down--;
    }
}

void Event::countCategories(int t1, int t2) {
    comparisonCount = 0;
    int max = Max(t1, t2);
    int min;
    if(t1==max)
    min=t2;
    else
    min=t1;
    string categories[100];
    int counts[100];
    int categorySize = 0;
     for(int i = 0; i < 100; i++) {
        categories[i] = "";
        counts[i] = 0;
    }
    
    countCategoriesHelper(root, min, max, categories, counts,categorySize, comparisonCount);
    
    cout << "Count of events in same category from range [" 
         << min << ", " << max << "]:" << endl;
    
    if (categorySize == 0) {
        cout << "No events found in this range." << endl;
    } else {
        for (int i = 0; i < categorySize; i++) {
            cout << "Number of events in (" << categories[i] 
                 << ") category: " << counts[i] << endl;
        }
    }
    
    cout << ".........................." << endl
         << "tedade moghaese: " << comparisonCount<< endl;
         cout << ".........................." << endl;
}
void Event::countCategoriesHelper(Node* r, int min, int max, string categories[], int counts[], int& categorySize, int& comparisons) {
    if (!r)
        return;
    
        comparisons++;    
    if (r->data.timestamp > min) {
        countCategoriesHelper(r->left, min, max, categories, counts, categorySize, comparisons);
    }
        comparisons+=2;
    if (r->data.timestamp >= min && r->data.timestamp <= max) {
        bool found = false;
        for (int i = 0; i < categorySize; i++) {
            comparisons++;  
            if (categories[i] == r->data.category) {
                counts[i]++;
                found = true;
                break;
            }
        }
        if (!found) {
            categories[categorySize] = r->data.category;
            counts[categorySize] = 1;
            categorySize++;
        }
    }
    comparisons++;
    if (r->data.timestamp < max) {
        countCategoriesHelper(r->right, min, max, categories, counts, categorySize, comparisons);
    }
}

void Event::calculateDepthSum(Node* r, int depth, int& sum, int& count) {
    if (!r)
        return;
    
    sum += depth;
    count++;
    
    calculateDepthSum(r->left, depth + 1, sum, count);
    calculateDepthSum(r->right, depth + 1, sum, count);
}

int Event::AverageDepthOfNodes() {
    if (!root) {
        cout << "Tree is empty" << endl;
        return 0;
    }
    
    int sum = 0;
    int count = 0;
    
    calculateDepthSum(root, 0, sum, count);
    
    int average = sum / count;
    return average;
}

int Event::Max(int a, int b) {
    if (a>=b)
        return a;
    else
        return b;
}

int main() {
    cout << "Welcome to Event System" << endl << ".........................." << endl;
    Event eventSystem;
    int choice = 0;
    
    while(choice != 8) {
        cout << "Press 1 for Insert an event" << endl
             << "Press 2 for Delete an event" << endl
             << "Press 3 for Search an event" << endl
             << "Press 4 for Show events in time range" << endl
             << "Press 5 for Find closest event" << endl
             << "Press 6 for count Categories" << endl
             << "Press 7 for Show tree statistics" << endl
             << "Press 8 for Exit" << endl;
        cin >> choice;
        cout << ".........................." << endl;
        
        if (choice == 1) {
            int i, t;
            string c, d;
            cout << "Please insert the event id (Number):" << endl;
            cin >> i;
            cout << "Please insert the event timestamp (Number):" << endl;
            cin >> t;
            cout << "Please insert the event category (String):" << endl;
            cin >> c;
            cout << "Please insert the event description (String):" << endl;
            cin >> d;
            Event e(i, t, c, d);
            eventSystem.Insert(e);
        }
        else if (choice == 2) {
            cout << "Please insert a timestamp for Delete" << endl;
            int ti;
            cin >> ti;
            eventSystem.Delete(ti);
        }
        else if (choice == 3) {
            cout << "Please insert a timestamp to Search an event" << endl;
            int ts;
            cin >> ts;
            eventSystem.search(ts);
        }
        else if (choice == 4) {
            cout << "Please insert two timestamps for Show events in time range" << endl;
            int t1, t2;
            cin >> t1 >> t2;
            eventSystem.getEventsBetween(t1, t2);
        }
        else if (choice == 5) {
            cout << "Please insert a timestamp to Find closest event" << endl;
            int tc;
            cin >> tc;
            eventSystem.findClosestEvent(tc);
        }
        else if (choice == 6) {
            cout << "Please insert two timestamp to show count of categories in a range of timestamp" << endl;
            int tt1, tt2;
            cin >> tt1 >> tt2;
            eventSystem.countCategories(tt1, tt2);
        }
        else if (choice == 7) {
            cout << "Press 1 for tree Height, 2 for InOrder, 3 for Average Depth of Nodes" << endl;
            int choice2;
            cin >> choice2;
            
            if(choice2 == 1) {
                cout << "Height of tree: " << eventSystem.Height() << endl;
            }
            else if(choice2 == 2) {
                cout << "Peymayesh in order:" << endl;
                eventSystem.InOrder();
            }
            else if(choice2 == 3) {
                int avgDepth = eventSystem.AverageDepthOfNodes();
                cout << "Average Depth of Nodes: " << avgDepth << endl;
            }
        }
        else if (choice == 8) {
            cout << "...Exiting..." << endl;
        }
    }
    return 0;
}