#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class TransportService {
public:
    TransportService(std::string name = "0", BinaryTreeNode* BSThead= nullptr)
        : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip){
        if(BSThead->getTripNodePtr()==NULL){
            BSThead->setDepartureTime(key);
            BSThead->setTripNodePtr(trip);
            return;
        }

        if(BSThead->getDepartureTime()==key){
            return;
        }

        BinaryTreeNode* check = BSThead;
        while(1){
            if(check->getDepartureTime()==key){
                cout<<key<<" already exists"<<endl;
                return;
            }
            else if(check->getDepartureTime()>key){
                if(check->getLeftPtr()==NULL){
                    break;
                }
                else
                check = check->getLeftPtr();
            }
            else{
                if(check->getRightPtr()==NULL){
                    break;
                }
                check = check->getRightPtr();
            }
        }
        // cout<<"prevkey: "<<check->getDepartureTime()<<endl;

        BinaryTreeNode* newnode = new BinaryTreeNode;
        newnode->setDepartureTime(key);
        newnode->setParentPtr(check);
        newnode->setTripNodePtr(trip);
        if(check->getDepartureTime()>key){
            check->setLeftPtr(newnode);
            // cout<<"left"<<" "<<trip->getDepartureTime()<<" "<<trip->getPickUpLocation()<<endl;
        }
        else{
            check->setRightPtr(newnode);
            // cout<<"right"<<" "<<trip->getDepartureTime()<<" "<<trip->getPickUpLocation()<<endl;
        }
        return;
    }

private:
    std::string name;
    BinaryTreeNode* BSThead;
};

class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    vector<Trip*> getTrips(){
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) {
        bool check=0;
        for(int i=0;i<serviceptrs.size();i++){
            if(serviceptrs.at(i)->getName() == droplocation){
                check=1;
                return serviceptrs.at(i);
            }
        }
        if(check==0){
            TransportService* ts = new TransportService();
            BinaryTreeNode* bsthead = new BinaryTreeNode;
            ts->setName(droplocation);
            ts->setBSTHead(bsthead);
            serviceptrs.push_back(ts);
            return ts;
        }
        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        return nullptr;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    vector<TransportService*> getAllServiceptrs(){
        return serviceptrs;
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const {
        if(root == nullptr || root->getLeftPtr() == nullptr && root->getRightPtr() == nullptr){
            return 0;
        }

        queue<BinaryTreeNode*> q;
        q.push(root);
        int levelcount = 0;

        while(!q.empty()){
            levelcount++ ;
            int nodecount = q.size();

            for(int i=0; i<nodecount;i++){
                BinaryTreeNode* temp = q.front();
                q.pop();
                if(temp->getLeftPtr() != nullptr){
                    q.push(temp->getLeftPtr());
                }

                if(temp->getRightPtr() != nullptr){
                    q.push(temp->getRightPtr());
                }
            }
        }

        return levelcount;
    }

    int getNumberOfNodes() const {
        // Implement this function to return the number of nodes in the tree
        queue<BinaryTreeNode*> q;
        int nodecount = 0;
        q.push(root);
        while(!q.empty()){
            BinaryTreeNode* temp = q.front();
            q.pop();
            nodecount++;
            if(temp->getLeftPtr() != nullptr){
                q.push(temp->getLeftPtr());
            }
            if(temp->getRightPtr() != nullptr){
                q.push(temp->getRightPtr());
            }
        }
        return nodecount;
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
        BinaryTreeNode*min=root;
        while(min->getLeftPtr()!=NULL){
            min=min->getLeftPtr();
        }
        return min;
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        BinaryTreeNode* max=root;
        while(max->getRightPtr()!=NULL){
            max=max->getRightPtr();
        }
        return max;
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        BinaryTreeNode* search=root;
        cout<<"to search "<<key<<endl;
        while(search!=nullptr){
            if(search->getDepartureTime() > key){
                cout<<"left "<<search->getDepartureTime()<<endl;
                search=search->getLeftPtr();
            }
            else if(search->getDepartureTime() < key){
                cout<<"right "<<search->getDepartureTime()<<endl;
                search=search->getRightPtr();
            }
            else if(search->getDepartureTime() == key){
                cout<<"same "<<search->getDepartureTime()<<endl;
                break;
            }
        }
        cout<<search<<endl;
        return search;
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const{
        BinaryTreeNode* succ = node->getParentPtr();
        if(node->getRightPtr() != nullptr){
            succ = node->getRightPtr();
            while(succ->getLeftPtr() != nullptr){
                succ = succ->getLeftPtr();
            }
            return succ;
        }
        return succ;
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        BinaryTreeNode* node = searchNodeWithKey(key);
        return getSuccessorNode(node);
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        BinaryTreeNode* pred = node->getParentPtr();
        if(node->getLeftPtr() != nullptr){
            pred = node->getLeftPtr();
            while(pred->getRightPtr() != nullptr){
                pred = pred->getRightPtr();
            }
            return pred;
        }
        return pred;
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        BinaryTreeNode* node = searchNodeWithKey(key);
        return getPredecessorNode(node);
    }
};

class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        //finding/creating concerned vehicle object
        Vehicle* veh;
        bool check=0;
        for(int i=0;i<vehicles.size();i++){
            if(vehicles.at(i)->getVehicleNumber() == vehicle_number){
                veh = vehicles.at(i);
                check = 1;
                break;
            }
        }
        if(check == 0){
            Vehicle* v = new Vehicle(vehicle_number, seating_capacity);
            veh = v;
            vehicles.push_back(veh);
        }
    
        //finding/creating concerned location object
        TransportService* ts = new TransportService();
        Location* loc;
        check = 0;
        for(int i=0;i<locations.size();i++){
            if(locations.at(i)->getName() == pick_up_location){
                loc = locations.at(i);
                ts = loc->getServicePtr(drop_location);
                check = 1;
                // cout<<"found location:"<<loc->getName()<<endl;
                break;
            }
        }
        if(check == 0){
            Location* l = new Location(pick_up_location);
            loc = l;
            locations.push_back(loc);
            ts = loc->getServicePtr(drop_location);
            // cout<<"newlocation: "<<loc->getName()<<" "<<departure_time<<endl;
        }

        //creating trip object
        Trip* trip=new Trip(veh, pick_up_location, drop_location, departure_time);

        //adding trip object to vehicle object
        veh->addTrip(trip);
        //adding trip object to location object
        loc->addTrip(trip);
        //adding trip object to bst
        ts->addTrip(departure_time,trip);

        return;
    }

    vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        vector<Trip*> show;
        Location* loc = getLocation(pick_up_location);
        if(loc == nullptr){
            return {};
        }
        vector<TransportService*> serviceptrs = loc->getAllServiceptrs();
        for(int i=0;i<serviceptrs.size();i++){
            BinaryTreeNode* node = serviceptrs.at(i)->getBSTHead();
            stack<BinaryTreeNode*> trips;
            while(!trips.empty() || node!=NULL){
                if (node != NULL){
                trips.push(node);
                node = node->getLeftPtr();
                }
                else{
                    node = trips.top();
                    if(trips.top()->getDepartureTime() < before_time && trips.top()->getDepartureTime() > after_time){
                        show.push_back(trips.top()->getTripNodePtr());
                    }
                    trips.pop();
                    node = node->getRightPtr(); 
                }
            }
        }
        return show;
    }

    vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        Location* loc = getLocation(pick_up_location);
        if(loc == nullptr){
            return {};
        }
        vector<TransportService*> serviceptrs = loc->getAllServiceptrs();
        TransportService* ts;
        for(int i=0;i<serviceptrs.size();i++){
            if(serviceptrs.at(i)->getName()==destination){
                ts = serviceptrs.at(i);
            }
        }

        vector<Trip*> show;
        stack<BinaryTreeNode*> trips;
        BinaryTreeNode* node = ts->getBSTHead();
        while(!trips.empty() || node!=NULL){
            if (node != NULL){
			trips.push(node);
			node = node->getLeftPtr();
		    }
            else{
                node = trips.top();
                if(trips.top()->getDepartureTime() < before_time && trips.top()->getDepartureTime() > after_time){
                    show.push_back(trips.top()->getTripNodePtr());
                }
                trips.pop();
                node = node->getRightPtr(); 
		    }
        }
        return show;
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        //finding binary tree for pickup drop of locations
        BinaryTreeNode* bsthead;
        bool check = 0;
        for(int i=0; i<getLocation(pick_up_location)->getAllServiceptrs().size(); i++){
            if(getLocation(pick_up_location)->getAllServiceptrs().at(i)->getName() == drop_location){
                bsthead = getLocation(pick_up_location)->getAllServiceptrs().at(i)->getBSTHead();
                check=1;
                break;
            }
        }
        if(check==0){
            return nullptr;
        }

        //finding required node
        BinaryTreeNode* booking = bsthead;
        while(1){
            if(booking->getDepartureTime()==departure_time){
                break;
            }
            else if(booking->getDepartureTime()>departure_time){
                booking = booking->getLeftPtr();
            }
            else{
                booking = booking->getRightPtr();
            }
        }
        //getting the trip ptr
        Trip* trip = booking->getTripNodePtr();

        //booking a seat
        if(booking->getTripNodePtr()->getBookedSeats() == booking->getTripNodePtr()->getVehicle()->getSeatingCapacity()){
            return nullptr;
        }
        booking->getTripNodePtr()->setBookedSeats(booking->getTripNodePtr()->getBookedSeats()+1);

        //remove node from tree
        // if(booking->getTripNodePtr()->getBookedSeats() == booking->getTripNodePtr()->getVehicle()->getSeatingCapacity()){

        //     //case1: it's a leaf node
        //     if(booking->getLeftPtr()==NULL && booking->getRightPtr()==NULL){
        //         BinaryTreeNode* parent = booking->getParentPtr();
        //         if(parent->getDepartureTime()<booking->getDepartureTime()){
        //             booking->setRightPtr(NULL);
        //         }
        //         else{
        //             booking->setLeftPtr(NULL);
        //         }

        //         delete booking;
        //     }

        //     //case2: node has one child
        //     else if(booking->getLeftPtr()==NULL || booking->getRightPtr()==NULL){
        //         BinaryTreeNode* parent=booking->getParentPtr();
        //         BinaryTreeNode* child;
        //         if(booking->getLeftPtr()!=nullptr)
        //             child=booking->getLeftPtr();
        //         else
        //             child=booking->getRightPtr();

        //         if(parent->getDepartureTime() > child->getDepartureTime())
        //             parent->setLeftPtr(child);
        //         else
        //             parent->setRightPtr(child);

        //         delete booking;
        //     }

        //     //case3: node has 2 children
        //     else{
                
        //     }
        // }
        return trip;
    }
    Location* getLocation(std::string location){
        for(int i=0;i<locations.size();i++){
            if(locations.at(i)->getName() == location){
                return locations.at(i);
            }
        }

        //Location* l = new Location(location);
        //locations.push_back(l);

        return nullptr;
    }
    void readinputfile(string filename){
        fstream input;
        string line;

        input.open(filename,ios::in);

        if(!input){
            cout<< "failed to open file"<<endl;
        }

        else{
            while(getline(input,line)){
                string query, vehiclenumber, pickup, dropoff;
                string seats, time,time2;

                stringstream str(line);
                getline(str,query,' ');

                if(query=="ADDTRIP"){
                    getline(str,vehiclenumber,' ');
                    getline(str,seats,' ');
                    getline(str,pickup,' ');
                    getline(str,dropoff,' ');
                    getline(str,time,' ');
                    time.erase(time.begin()+2);

                    addTrip(vehiclenumber, stoi(seats), pickup, dropoff, stoi(time));
                }

                else if(query=="SHOWTRIPS"){
                    getline(str,pickup,' ');
                    getline(str,time,' ');
                    getline(str,time2,' ');
                    time.erase(time.begin()+2);
                    time2.erase(time2.begin()+2);

                    showTrips(pickup,stoi(time2),stoi(time));
                }

                else if(query=="BOOKTRIP"){
                    getline(str,pickup,' ');
                    getline(str,dropoff,' ');
                    getline(str,vehiclenumber,' ');
                    getline(str,time,' ');
                    time.erase(time.begin()+2);

                    bookTrip(pickup, dropoff, vehiclenumber, stoi(time));
                }
            }
        }
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};

// int main(){
//     string filename;
//     cout<<"enter file name:";
//     cin>>filename;
//     TravelDesk travels;
//     travels.readinputfile(filename);
// }