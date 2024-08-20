#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>

using namespace std;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next=NULL;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    long long computeHash(const string& str){
        long long key=0;
        for(int i=0;i<str.length();i++){
            key= key + (long long)((long long int)((long long)str.at(i)*pow(263,i))%(1000000007));
        }
        key=key%263;
        if(key<0)
        return key+263;
        else
        return key;
    }

    void addContact(const PhoneRecord* record){
        PhoneRecord* rec = new PhoneRecord(record->getName(),record->getOrganisation(),record->getPhoneNumbers());
        // PhoneRecord* rec = (PhoneRecord*)record;
        istringstream s(rec->getName());
        string name;
        while(s>>name){
            //computing key
            int key = this->computeHash(name);
            cout<<key<<endl;

            //creating HashTableRecord with computed key and PhoneRecord* p
            HashTableRecord* hash_record = new HashTableRecord(key,rec);

            //checking if record already exists
            HashTableRecord* check = hashTable[key];
            while(check!=nullptr){
                if(check->getRecord()->getName() == rec->getName()){
                    cout<<"contact already exists"<<endl;
                    return;
                }
                check = check->getNext();
            }

            //adding HashTableRecord created to the hash table
            if(hashTable[key]==nullptr){
                hashTable[key]=hash_record;
                continue;
            }

            else{
                HashTableRecord* add = hashTable[key];
                while(add->getNext()!=NULL){
                    add=add->getNext();
                }
                add->setNext(hash_record);
            }
        }
    }

    bool deleteContact(const string* searchName){
        cout<<"you want to delete"<<endl;
        istringstream ss(*searchName);
        string name;
        int i=0,b=0;
        while(ss>>name){
            cout<<name<<endl;
            i++;
            int key = computeHash(name);

            if(hashTable[key] == nullptr){
                cout<<i<<b<<endl;
                continue;
            }

            if((hashTable[key]->getRecord()->getName()).find(*searchName) != string::npos){
                cout<<i<<endl;
                hashTable[key]=hashTable[key]->getNext();
                b++;
            }

            else{
                HashTableRecord* check = hashTable[key];
                while(check->getNext() != NULL){
                    cout<<i<<b<<endl;
                    cout<<check<<endl;
                    if((check->getNext()->getRecord()->getName()).find(*searchName) != string::npos){
                        // cout<<check->getNext()->getRecord()->getName()<<endl;
                        check->setNext(check->getNext()->getNext());
                        // cout<<check->getNext()<<endl;
                        b++;
                        break;
                    }
                    else{
                        check = check->getNext();
                    }
                }
            }
            cout<<i<<b<<endl;
        }
        if(i==b)
        return 1;
        else
        return 0;
    }

    vector<PhoneRecord*> fetchContacts(const string* query){
        string que = *query;
        istringstream ss(*query);
        string name;
        vector<PhoneRecord*> fetch;

        while(ss>>name){
            int key = computeHash(name);
            HashTableRecord* check = hashTable[key];

            if(hashTable[key] == nullptr){
                continue;
            }

            while(check!=NULL){
                cout<<check->getRecord()->getName()<<endl;
                cout<<que<<endl;
                if((check->getRecord()->getName()).find(name) != string::npos){
                    fetch.push_back(check->getRecord());
                    cout<<check->getRecord()->getName()<<" fetxh size: "<<fetch.size()<<endl;
                }
                check = check->getNext();
            }
        }
        sort(fetch.begin(),fetch.end());

        int arr[fetch.size()][2]={0};
        int x=0;
        for(int i=0;i<fetch.size();i++){
            if(i==0){
                arr[x][0]=i;
                arr[x][1]++;
            }

            else if(fetch.at(i)==fetch.at(i-1)){
                arr[x][1]++;
            }

            else{
                x++;
                arr[x][0]=i;
                arr[x][1]++;
            }
        }

        int temp1, temp2;
        for(int i=0; i<=x; i++){
            for(int j=0; j<x-i; j++){
                if(arr[j][1]<arr[j+1][1]){
                    temp1=arr[j+1][0];
                    temp2=arr[j+1][1];
                    arr[j+1][0]=arr[j][0];
                    arr[j+1][1]=arr[j][1];
                    arr[j][0]=temp1;
                    arr[j][1]=temp2;
                }
            }
        }

        vector<PhoneRecord*> sorted_fetch;
        for(int i=0;i<=x;i++){
            for(int j=0;j<arr[i][1];j++){
                sorted_fetch.push_back(fetch.at(arr[i][0]));
            }
        }

        return sorted_fetch;
    }

    int countRecordsPointingTo(const PhoneRecord* record) const{
        istringstream ss(record->getName());
        string name;
        int count=0;
        while(ss>>name){
            int key = ((PhoneBook*)(this))->computeHash(name);

            if(hashTable[key]->getRecord()->getName() == record->getName()){
                count++;
            }

            HashTableRecord* check = hashTable[key];
            while(check!=NULL){
                if(check->getNext()->getRecord()->getName() == record->getName()){
                    count++;
                }
                else{
                    check = check->getNext();
                }
            }
        }
        return count;
    }

    void readRecordsFromFile(const string& filename){
        fstream input;
        string line;
        
        input.open(filename,ios::in);

        if(!input){
            cout<< "failed to open file"<<endl;
        }

        else{
            while(getline(input,line)){
                string n,org,word;
                vector<string> numbers;
            
                //getting name
                stringstream str(line);
                getline(str,n,',');

                //getting phone numbers and organisation
                bool i=1;
                do
                {
                    getline(str,word,',');
                    
                    if(word.at(0)>=48 && word.at(0)<=57){
                        numbers.push_back(word);
                    }
                    else{
                        i=0;
                        org=word;
                    }
                    
                } while (i);

                //storing as PhoneRecord object in heap
                PhoneRecord* p=new PhoneRecord(n,org,numbers);

                cout<<n<<endl;

                //adding record in hashTable
                addContact(p);
            }
        }
    }

    // Destructor
    ~PhoneBook(){
        // for(int k=0;k<263;k++){
        //     HashTableRecord* del = hashTable[k];
        //     HashTableRecord* next = hashTable[k]->getNext();
        //     delete del->getRecord();
        //     delete del;

        //     while(next!=NULL){
        //         del = next;
        //         next = next->getNext();
        //         delete del->getRecord();
        //         delete del;
        //     }
        // }
    }
};


// int main(){
//     cout<<"enter file name: ";
//     string inputfile;
//     cin>>inputfile;

//     PhoneBook();
//     PhoneBook book;
//     book.readRecordsFromFile(inputfile);
// }