## Problem Statement

Imagine you have a phone book, but it's not a regular one. It's a special phone book where you can save contact information like names, organizations, and phone numbers.

- **Saving Contacts**: You can add people's names, their organizations (like their workplace or school), and one or more phone numbers associated with them.
- **Finding Contacts**: You can search for people's names or parts of their names (such as first name, middle name, last name) to find their contact information.
- **Removing Contacts** : You can also delete someone's contact information if you don't need it anymore.

Implement a `PhoneBook` utilizing chaining scheme for hashing with collision handling using a chaining scheme. You can use the linked list implementation that you have developed in your second lab exercise.

## Problem Description

### PhoneRecord Class

- **Description**: Represents an individual contact or phone record.

- **Attributes**:
  - `name` (string): The name of the contact, which may include the first name, middle name, and last name.
  - `organisation` (string): The organization associated with the contact (e.g., workplace or school).
  - `phoneNumbers` (vector<string>): A vector of phone numbers associated with the contact. Some contacts may have one or more phone numbers.

- **Public Methods**:
  - `getName() const`: Returns the full name of the contact.
  - `getOrganisation() const`: Returns the organization associated with the contact.
  - `getPhoneNumbers() const`: Returns a vector of phone numbers associated with the contact.

### HashTableRecord Class

- **Description**: Represents a record stored in a hash table. It acts as a node in the chaining scheme for hash tables. The HashTableRecord object is designed to be used with the chaining-based collision handling scheme

- **Attributes**:
  - `key` (an int): A unique key or hash ID corresponding to the contact's name.
  - `element` (PhoneRecord): A reference to a `PhoneRecord` object that holds the contact's information.
  - `next` (HashTableRecord*): A pointer to the next `HashTableRecord` in the linked list. This is used to handle collisions when multiple records hash to the same key.

- **Public Methods**:
  - `getKey() const`: Returns the key associated with the record.
  - `getRecord() const`: Returns the `PhoneRecord` object associated with the record.
  - `getNext() const`: Returns a pointer to the next `HashTableRecord` in the linked list.
  - `setNext(HashTableRecord* nxt)`: Sets the next `HashTableRecord` in the linked list.

### PhoneBook Class

- **Description**: Represents the phone book application itself. It manages the storage, search and retrieval of contact information.

- **Attributes**:
  - `hashTable` (array of HashTableRecord pointers): A hash table is used to store contact records. Each slot in the array may contain a linked list of `HashTableRecord` nodes, allowing for chaining to handle hash collisions.
  - M: number of slots in the hashTable 

- **Public Methods**:
  - `PhoneBook()`: The constructor initializes the `hashTable` array, setting all slots to nullptr.
  - `computeHash()`: Function to compute the hash value for a given string
  - `addContact(const PhoneRecord* record)`: Adds a new contact record to the phone book. It computes the hash of the contact's name to determine the slot in the hash table. If the name of a person has multiple words (such as first name, last name, middle name, or more) then each word is treated as a separate key to be hashed. For example, the first name is used as key1, the middle name (if it is there) is used as key2, and the last name (if it is there) is used as key3.  Separate HashTableRecord objects will be instantiated. Each record will get one of the keys. So, if a full name gets mapped to 3 keys — key1, key2, key3, then 3 objects of class HashTableRecord will be created. Each object gets one key, and its element will point to the PhoneRecord of the contact. All these 3 HashTableRecord objects will point to the same PhoneRecord object. All these HashTableRecord objects will then be inserted  (using their respective keys) into the HashTable maintained by the PhoneBook class.  Notice that the number of HashTable record objects for a given contact (PhoneRecord object) will be equal to the number of words in the name of the person. Also notice that the HashTable may have multiple records that correspond to a given key.
  - bool `deleteContact(const string* searchName)`: Deletes a contact record from the phone book based on the contact's name. This will require retrieving the PhoneRecords that match with the searchName (or a word in it). You can use the fetchContacts(query) member function of the PhoneBook class. If there are multiple PhoneRecords retrieved, the first one in the list will be chosen for deletion. Let’s call this one as the selected PhoneRecord object. To perform deletion in the hashTable, we need to find the HashTableRecord objects that have their elements point to the selected PhoneRecord object. Note that there can be multiple such HashTableRecord objects. All of these HashTableRecord objects need to be deleted. Deletion will involve modifying the corresponding linked list with the hash table slot. This function will return True if one of the HashTableRecord objects gets deleted. It will return False if no contact was deleted because the searchName is not found in the PhoneBook.
  - `vector<PhoneRecord*> fetchContacts(const string* query)`: Retrieves contact records based on a search query. The given query will be split into words. Each word would serve as a key. Records (objects of class HashTableRecord) corresponding to each key will be retrieved. Some of these records (HashTableRecord objects) will point to a common PhoneRecord object. A vector of the retrieved PhoneRecord objects is prepared such that those PhoneRecord objects that are shared by more than one HashTableRecord objects will be listed first. For example, a PhoneRecord that is pointed by, say, 3 HashTableRecord objects will be listed first, followed by those pointed by 2 HashTableRecord objects, and so on. 
  
To check if the two HashTableRecord objects point to the same PhoneRecord objects, you need to compare the memory addresses of the PhoneRecord objects.

You should work out an O(n) algorithm for this method, where  is the number of HashTableRecord objects stored in the hashTable.


<!-- ## Problem Description

- `PhoneBook` is a linked list of `HashTableRecord`. 
- `HashTableRecord` consists of (key, value) pair, where `key` is unique HashID
corresponding to the input `Name`, and value is a pointer to list of `PhoneRecord`.
- Each `PhoneRecord` consists of `Name`, `Organisation` and `Phone Numbers`.
- `Name` may consist `first name`, `middle name` and/or `last name`.
- Some contacts can have one phone number and some contacts can have two phone numbers. 
- The hashing should be done separately for the `first name`, `middle name` and `last name`.
- For a given query, it should be broken down into words, each word hashed to a key, and the separate lists of records should be retrieved for each key. 
- If there are common records in the retrieved lists, the common ones should be listed first. 

What it means is that with chaining, the entire linked list for a hash table slot should be checked for a given key. The search cannot terminate with the first match, since there can be several elements with the same key.  -->

## Hash Function

**Polynomial hash function**
$$h(s) = \left( \sum_{i=0}^{|s|-1} s[i] * x^{i} mod [p] \right) mod [m] $$

where s[i] is the ASCII code of the i-th symbol of S, p = 1000000007, and x = 263, m = 263. 

Note: you might need to use various modulo operations.


## Input Format

The input format is a Details.txt file which contains **Name**, **phone number**, **organisation**, use the same I/O functions as defined in previous lab.

## Query Format

- `add` string
- `del` string
- `fetch` string

> Sample Input

```console
add Venkatesh Kumar, 93030842810, 391308812324, IITJ.  
add Avadhut Eknath Kabadi, 391308812324, IITJ.
fetch Avadhut
```

> Output

```console
vector<PhoneRecord> Corresponding to Avadhut
```
    
## Interface

<details>

<summary> CPP </summary>


```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getters and setters for name, organisation, and phoneNumbers

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
    PhoneRecord* element;
    HashTableRecord* next;

public:
    HashTableRecord(int k, const PhoneRecord& rec)
        : key(k), record(rec), next(nullptr) {}

    // Getters and setters for key, record, and next

    int getKey() const {
        return key;
    }

    PhoneRecord getRecord() const {
        return record;
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
    static const int HASH_TABLE_SIZE = 263; // Fixed size of the hash table
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    PhoneBook() {
        // Initialize the hash table slots to nullptr
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Function to compute the hash value for a given string
    long long computeHash(const string& str) {
        // Implement a hash function for strings
    }

    // Implement methods for adding, deleting, and fetching contacts

    void addContact(const PhoneRecord* record) {
        // Implement adding a contact to the phone book
    }

    bool deleteContact(const string* searchName) {
        // Implement deleting a contact from the phone book
    }

    vector<PhoneRecord> fetchContacts(const string* query) {
        // Implement fetching contacts based on the query
        // You may need to split the query into words and hash them separately
        // Then, retrieve and merge the records from the appropriate hash table slots
        // Sort and return the merged records
        vector<PhoneRecord> result;
        return result;
    }
};
```

</details>
    
    
    
<details>

<summary> Python </summary>


```python
class PhoneRecord:
    def __init__(self, name, organisation, phone_numbers):
        self.name = name
        self.organisation = organisation
        self.phone_numbers = phone_numbers

    def get_name(self):
        return self.name

    def get_organisation(self):
        return self.organisation

    def get_phone_numbers(self):
        return self.phone_numbers


class HashTableRecord:
    def __init__(self, key, record):
        self.key = key
        self.record = record
        self.next = None

    def get_key(self):
        return self.key

    def get_record(self):
        return self.record

    def get_next(self):
        return self.next

    def set_next(self, nxt):
        self.next = nxt


class PhoneBook:
    HASH_TABLE_SIZE = 263

    def __init__(self):
        self.hash_table = [None] * PhoneBook.HASH_TABLE_SIZE

    def compute_hash(self, string):
        # Implement a hash function for strings
        # You can use Python's built-in hash function or implement a custom one

    def add_contact(self, record):
        # Implement adding a contact to the phone book
        # You need to compute the hash for the record's name and insert it into the hash table

    def delete_contact(self, name):
        # Implement deleting a contact from the phone book
        # You need to find the record with the given name and remove it from the hash table

    def fetch_contacts(self, query):
        # Implement fetching contacts based on the query
        # You may need to split the query into words and hash them separately
        # Then, retrieve and merge the records from the appropriate hash table slots
        # Sort and return the merged records
        result = []
        return result

```

</details>
    

    
<details>

<summary> Java </summary>

    
```java
import java.util.ArrayList;
import java.util.List;

class PhoneRecord {
    private String name;
    private String organisation;
    private List<String> phoneNumbers;

    public PhoneRecord(String name, String organisation, List<String> phoneNumbers) {
        this.name = name;
        this.organisation = organisation;
        this.phoneNumbers = phoneNumbers;
    }

    public String getName() {
        return name;
    }

    public String getOrganisation() {
        return organisation;
    }

    public List<String> getPhoneNumbers() {
        return phoneNumbers;
    }
}

class HashTableRecord {
    private int key;
    private PhoneRecord record;
    private HashTableRecord next;

    public HashTableRecord(int key, PhoneRecord record) {
        this.key = key;
        this.record = record;
        this.next = null;
    }

    public int getKey() {
        return key;
    }

    public PhoneRecord getRecord() {
        return record;
    }

    public HashTableRecord getNext() {
        return next;
    }

    public void setNext(HashTableRecord next) {
        this.next = next;
    }
}

class PhoneBook {
    private static final int HASH_TABLE_SIZE = 263; // Fixed size of the hash table
    private HashTableRecord[] hashTable;

    public PhoneBook() {
        // Initialize the hash table slots to null
        hashTable = new HashTableRecord[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = null;
        }
    }

    // Function to compute the hash value for a given string
    public long computeHash(String str) {
        // Implement a hash function for strings
        // You can use Java's hashCode method or implement a custom one
        // Be sure to return a long value for a meaningful hash function
        return 0; // Placeholder, implement your hash function here
    }

    // Implement methods for adding, deleting, and fetching contacts

    public void addContact(PhoneRecord record) {
        // Implement adding a contact to the phone book
        // You need to compute the hash for the record's name and insert it into the hash table
    }

    public boolean deleteContact(String name) {
        // Implement deleting a contact from the phone book
        // You need to find the record with the given name and remove it from the hash table
    }

    public List<PhoneRecord> fetchContacts(String query) {
        // Implement fetching contacts based on the query
        // You may need to split the query into words and hash them separately
        // Then, retrieve and merge the records from the appropriate hash table slots
        // Sort and return the merged records
        List<PhoneRecord> result = new ArrayList<>();
        return result;
    }
}
```


</details>
