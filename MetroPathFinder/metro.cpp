#include <bits/stdc++.h>
using namespace std;
// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);
    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    MetroStop* n = node;
    int count=0;
    while(n!=NULL){
        count++;
        n = n->getNextStop();
    }
    return count;
}

void MetroLine::populateLine(std::string filename) {
    //reading file
    fstream input;
    string line;
    input.open(filename,ios::in);
    MetroStop* prevnode = NULL;

    if(!input){
        cout<< "failed to open file"<<endl;
    }

    else{
        while(getline(input,line)){
            //getting stop name and fare
            string stop,fare="";
            int find = line.find_last_of(' ');
            for(int i=find;i<line.size()-1;i++){
                fare.push_back(line.at(i));
            }
            line.erase(line.begin()+find, line.end());
            stop=line;

            //creating metrostop object
            MetroStop* metrostop = new MetroStop(stop,this,stoi(fare));

            //incase of first node
            // if(node == NULL){
            //     node = metrostop;
            //     continue;
            // }
            
            //adding object to linked list
            if(prevnode == NULL){
                this->setNode(metrostop);
                prevnode = metrostop;
            }
            else{
                metrostop->setPrevStop(prevnode);
                prevnode->setNextStop(metrostop);
                prevnode = metrostop;
            }
            // cout<<metrostop->getPrevStop()<<endl;
        }
    }
}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    vector<MetroStop*> getStops();
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

vector<MetroStop*> AVLNode::getStops(){
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
private:
    AVLNode* root;

public:
    AVLTree();

    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLTree::AVLTree(){
    root = nullptr;
}

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node == NULL){
        return 0;
    }
    else{
        // cout<< "in height "<<node->getStopName()<<endl;
        return 1 + max(height(node->getLeft()),height(node->getRight()));
    }
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    AVLNode* left = node->getLeft();
    AVLNode* right = node->getRight();
    return height(left)-height(right);
}

AVLNode* AVLTree::rotateLeft(AVLNode* node) {
    AVLNode* y = node->getRight();
    AVLNode* x = y->getLeft();
    if(node == this->getRoot()){
        this->setRoot(y);
    }
    y->setParent(node->getParent());

    if(node->getParent()!=nullptr){
        if(node->getParent()->getLeft() == node ){
            node->getParent()->setLeft(y);
        }
        else{
            node->getParent()->setRight(y);
        }
    }

    if(x != nullptr){
        x->setParent(node);
    }
    
    node->setRight(x);
    node->setParent(y);
    y->setLeft(node);
    return y->getParent();
}

AVLNode* AVLTree::rotateRight(AVLNode* node) {
    AVLNode* y = node->getLeft();
    AVLNode* x = y->getRight();
    if(node == this->getRoot()){
        this->setRoot(y);
    }
    y->setParent(node->getParent());

    if(node->getParent()!=nullptr){
    if(node->getParent()->getLeft() == node){
        node->getParent()->setLeft(y);
    }
    else{
        node->getParent()->setRight(y);
    }
    }

    if(x != nullptr){
        x->setParent(node);
    }

    node->setLeft(x);
    y->setRight(node);
    node->setParent(y);

    return y->getParent();    
}

void AVLTree::balance(AVLNode* node) {
    AVLNode* x = node;
    AVLNode* y;
    if(x != root){
        y=x->getParent();
    }
    else{
        return;
    }

    AVLNode* z;
    if( y != root){
        z = y->getParent();
    }
    else{
        return;
    }

    int bf = balanceFactor(z);
    if(bf == -1 || bf == 1 || bf == 0){
        balance(y);
    }
    else if(bf>1){
        //left left case
        if(y->getLeft() == x){
            AVLNode* next = rotateRight(z);
            if(next!=nullptr)
            balance(next);
        }
        //left right case
        else{
            rotateLeft(y);
            AVLNode* next = rotateRight(z);
            if(next!=nullptr)
            balance(next);
        }
    }
    else if(bf<-1){
        //right right case
        if(y->getRight() == x){
            AVLNode* next = rotateLeft(z);
            if(next!=nullptr)
            balance(next);
        }
        //right left case
        else{
            rotateRight(y);
            AVLNode* next = rotateLeft(z);
            if(next!=nullptr)
            balance(next);
        }
    }
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    AVLNode* head = this->getRoot();
    char check;
    while(1){
        if(stringCompare(head->getStopName(),metroStop->getStopName()) > 0){
            //lesser
            if(head->getLeft()==NULL){
                check='l';
                break;
            }
            else
            head = head->getLeft();
        }
        else if(stringCompare(head->getStopName(),metroStop->getStopName()) < 0){
            //greater
            if(head->getRight()==NULL){
                check = 'r';
                break;
            }
            else
            head = head->getRight();
        }
        else if(stringCompare(head->getStopName(),metroStop->getStopName()) == 0){
            //both stop names are equal
            head->addMetroStop(metroStop);
            delete node;
            return;
        }
    }

    //inserting in tree
    node->setParent(head);
    if(check == 'l'){
        head->setLeft(node);
        // cout<<"left"<<endl;
    }
    else if(check == 'r'){
        head->setRight(node);
        // cout<<"right"<<endl;
    }
    //balance tree
    balance(node);
}

void AVLTree::populateTree(MetroLine* metroLine) {
    MetroStop* head = metroLine->getNode();
    if(head->getStopName() == "Dwarka Sec-21"){
        head = head->getNextStop();
    }
    while(head!=NULL){
        AVLNode* avl = new AVLNode(head->getStopName());
        // cout<<root->getStopName()<<endl;
        avl->addMetroStop(head);
        insert(avl,head);
        head = head->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode* tree = this->getRoot();
    while(tree->getStopName() != stopName){
        if(stringCompare(tree->getStopName(),stopName) > 0){
            tree = tree->getLeft();
        }
        else if(stringCompare(tree->getStopName(),stopName) < 0){
            tree = tree->getRight();
        }
    }
    return tree;
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, vector<MetroLine*> metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, vector<MetroLine*> metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    AVLNode* avl = new AVLNode(lines.at(0)->getNode()->getStopName());
    avl->addMetroStop(lines.at(0)->getNode());
    tree->setRoot(avl);
    for(int i=0;i<lines.size();i++){
        tree->populateTree(lines.at(i));
    }
}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    AVLTree* t = this->getTree();
    AVLNode* start = t->searchStop(origin);

    cout<<"total nodes "<<t->getTotalNodes(t->getRoot())<<endl;

    vector<MetroStop*> line = start->getStops();
    vector<Exploration*> exps;
    for(int i=0; i<line.size(); i++){
        Trip* trip = new Trip(line.at(i), nullptr);
        Exploration* exp = new Exploration();
        exp->enqueue(trip);
        exps.push_back(exp);
    }

    //forward direction
    for(int i=0; i<exps.size(); i++){
        while(1){
            Trip* prev = exps.at(i)->getTrips().back(); //prev trip
            MetroStop* stop = prev->getNode()->getNextStop(); //next stop
            Trip* trip = new Trip(stop, prev); //new trip object
            exps.at(i)->enqueue(trip); //add new trip to exps.at(i)

            AVLNode* junctioncheck = t->searchStop(trip->getNode()->getStopName()); //get avl node for this stop

            if(stop->getStopName() == destination){
                Path* path = new Path();
                vector<MetroStop*> route;
                while(!exps.at(i)->isEmpty()){
                    route.push_back(exps.at(i)->dequeue()->getNode());
                }

                for(int j=route.size()-1;j>=0;j--){
                    path->addStop(route.at(j));
                }
                path->setTotalFare(path->getStops().at(0)->getFare() - path->getStops().at(path->getStops().size()-1)->getFare());
                return path;
            }
            else if (stop == nullptr){
                break;
            }
            else if(junctioncheck->getStops().size()>1){
                for(int i=0; i<junctioncheck->getStops().size(); i++){
                    if(stop != junctioncheck->getStops().at(i)){
                        cout<<junctioncheck->getStops().at(i)->getLine()<<endl;
                        MetroStop* ms = junctioncheck->getStops().at(i)->getNextStop();
                        Trip* tr = new Trip(ms, trip);
                        Exploration* newroute = new Exploration();
                        queue<Trip*> prevtrips = exps.at(i)->getTrips();

                        while(!prevtrips.empty()){
                            newroute->enqueue(prevtrips.front());
                        }
                        newroute->enqueue(tr);
                        exps.push_back(newroute);
                    }
                }
            }
            cout<<"sdfghjkl"<<endl;
        }
    }
    // // reverse direction
    // for(int i=0; i<exps.size(); i++){
    //     Trip* prev = exps.at(i)->getTrips().back(); //prev trip
    //     MetroStop* stop = prev->getNode()->getNextStop(); //next stop
    //     Trip* trip = new Trip(stop, prev); //new trip object
    //     exps.at(i)->enqueue(trip); //add new trip to exps.at(i)
    //     cout<<exps.at(i)->getTrips().back()->getNode()->getStopName()<<endl;

    //     AVLNode* junctioncheck = t->searchStop(trip->getNode()->getStopName()); //get avl node for this stop

    //     if(stop->getStopName() == destination){
    //         Path* path = new Path();
    //         while(!exps.at(i)->isEmpty()){
    //             path->addStop(exps.at(i)->dequeue()->getNode());
    //             path->setTotalFare(path->getTotalFare() + path->getStops().back()->getFare());
    //             cout<<path->getTotalFare()<<endl;
    //         }
    //         cout<<path->getTotalFare();
    //         return path;
    //     }
    //     else if (stop == nullptr){
    //         break;
    //     }
    //     else if(junctioncheck->getStops().size()>1){
    //         for(int i=0; i<junctioncheck->getStops().size(); i++){
    //             if(stop != junctioncheck->getStops().at(i)){
    //                 MetroStop* ms = junctioncheck->getStops().at(i)->getNextStop();
    //                 Trip* tr = new Trip(ms, trip);
    //                 Exploration* newroute = new Exploration();
    //                 queue<Trip*> prevtrips = exps.at(i)->getTrips();

    //                 while(!prevtrips.empty()){
    //                     newroute->enqueue(prevtrips.front());
    //                 }
    //                 newroute->enqueue(tr);
    //                 exps.push_back(newroute);
    //             }
    //         }
    //     }
    // }
}

// int main(){
//     vector<string> lines_list = {"blue.txt","green.txt",
//     "magenta.txt","orange.txt","red.txt","violet.txt","yellow.txt"};
    
//     for(int i=0;i<lines_list.size(); i++){
//         //creating metro line for this file
//         string colour = lines_list.at(i);
//         colour.erase(colour.end()-4,colour.end());
//         MetroLine* metroline = new MetroLine(colour);
//         metroline->populateLine(lines_list.at(i));
//         metroline->printLine();
//     }
// }