#include <bits/stdc++.h>
using namespace std;
using std::vector;

class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

class Node{
	private:
		Node* next=NULL;
		StudentRecord* element;
	public:
	    Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }
	    void set_next(Node* value){
	    	next = value;
	    }
	    void set_element(StudentRecord* student){
	    	element = student;
	    }
};

class Entity {
private:
    string name;
    Node* iterator=NULL;

public:
    string get_name() {
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() {
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};

vector<StudentRecord> students;
int scan_index;

class LinkedList : public Entity {
    public:
        void add_student(StudentRecord student){
            students.push_back(student);

            Node *n = this->get_iterator();
            Node* new_node=new Node;
            (*new_node).set_element(&students.at(students.size()-1));

            while(n->get_next()!=NULL){
                n=(*n).get_next();
            }
            (*n).set_next(new_node);
            return;
        }

        void delete_student(string studentName){
            Node* n = this->get_iterator();

            if(n->get_element()->get_studentName()==studentName){
                this->set_iterator(this->get_iterator()->get_next());
            }

            while(n!=NULL){
                if(studentName == n->get_next()->get_element()->get_studentName()){
                    n->set_next(n->get_next()->get_next());
                    break;
                }

                else{
                    n=(*n).get_next();
                }
            }
            return;
        }
};

vector<LinkedList> EntityArray;
bool resize=0;

void read_input_file(string file_path){
    fstream input;
    string line,word;

    students.reserve(1000);

    input.open(file_path,ios::in);

    if(!input){
        cout<< "failed to open file"<<endl;
    }

    else{
        while(getline(input,line)){
            StudentRecord s;
            stringstream str(line);

            getline(str,word,',');
            s.set_studentName(word);
            // cout<<s.get_studentName()<<' ';

            getline(str,word,',');
            s.set_rollNumber(word);
            // cout<<s.get_rollNumber()<<endl;
            students.push_back(s);

            bool flag=0;
            while(getline(str,word,',')){
                if(word.at(0)=='['){
                    word.erase(word.begin()+0);
                }
                if(word.at(word.size()-1)==']'){
                    word.erase(word.size()-1);
                }

                for(scan_index=0;scan_index<EntityArray.size();scan_index++)
                {
                    if(EntityArray.at(scan_index).get_name()==word)
                    {
                        // EntityArray.at(scan_index).add_student(&(students.at(students.size()-1)), &(EntityArray.at(scan_index)));

                        StudentRecord* student=&(students.at(students.size()-1));
                        LinkedList* list=&(EntityArray.at(scan_index));
                        Node* new_node=new Node;
                        (*new_node).set_element(student);
                        
                        if((*list).get_iterator()==NULL){
                            (*list).set_iterator(new_node);
                            // cout<<(*(*new_node).get_element()).get_studentName()<<' '<<(*list).get_name()<<endl;
                            break;
                        }

                        Node* check=(*list).get_iterator();
                        while((*check).get_next()!=NULL){
                            check=(*check).get_next();
                        }
                        (*check).set_next(new_node);
                        // cout<<(*(*new_node).get_element()).get_studentName()<<' '<<(*list).get_name()<<endl;

                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    LinkedList newLL;
                    newLL.set_name(word);
                    EntityArray.push_back(newLL);
                    // newLL.add_student(&(students.at(students.size()-1)), &(EntityArray.at(scan_index)));

                    StudentRecord* student=&(students.at(students.size()-1));
                    LinkedList* list=&(EntityArray.at(scan_index));

                    Node* new_node=new Node;
                    (*new_node).set_element(student);
                    
                    bool boo=0;
                    if((*list).get_iterator()==NULL){
                        (*list).set_iterator(new_node);
                        // cout<<(*(*new_node).get_element()).get_studentName()<<' '<<(*list).get_name()<<endl;
                        boo = 1;
                    }

                    if(boo==0){
                        Node* check=(*list).get_iterator();
                        while((*check).get_next()!=NULL){
                        check=(*check).get_next();
                    }
                    (*check).set_next(new_node);
                    // cout<<(*(*new_node).get_element()).get_studentName()<<' '<<(*list).get_name()<<endl;

                    flag=1;
                    }
                }
                flag=0;
            }
        }
    }
}