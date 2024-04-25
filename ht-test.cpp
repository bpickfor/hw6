#include "ht.h"
#include "hash.h"
#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <functional>
using namespace std;

// NEW FILE
int main()
{
    // double hash, 0.7 loading fact
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.7, dh);

    // put in key val pairs
    for (int i = 0; i < 10; i++)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    // see if key exists
    if (ht.find("key1") != nullptr)
    {
        std::cout << "Found key1" << std::endl;
    }

    // test updat eval
    if (ht.find("key2") != nullptr)
    {
        ht["key2"] = 22;
        std::cout << "Updated key2's value to: " << ht["key2"] << std::endl;
    }

    // test delete
    ht.remove("key3");
    if (ht.find("key3") == nullptr)
    {
        std::cout << "Deleted key3 successfully" << std::endl;
    }

    // test resive by load fact
    for (int i = 10; i < 30; i++)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    // check size and if exceed capac
    std::cout << "Hash table size after resizing: " << ht.size() << std::endl;

    return 0;
}

// ORIGINAL FILE
/*int main()
{
    DoubleHashProber<std::string, MyStringHash > dh;
    HashTable<
        std::string,
        int,
        DoubleHashProber<std::string, MyStringHash >,
        std::hash<std::string>,
        std::equal_to<std::string> > ht(0.7, dh);

    // This is just arbitrary code. Change it to test whatever you like about your
    // hash table implementation.
    for(size_t i = 0; i < 10; i++){
        std::stringstream ss;
        ss << "hi" << i;
        ht.insert({ss.str(), i});
    }
    if( ht.find("hi1") != nullptr ){
        cout << "Found hi1" << endl;
        ht["hi1"] += 1;
        cout << "Incremented hi1's value to: " << ht["hi1"] << endl;
    }
    if( ht.find("doesnotexist") == nullptr ){
        cout << "Did not find: doesnotexist" << endl;
    }
    cout << "HT size: " << ht.size() << endl;
    ht.remove("hi7");
    ht.remove("hi9");
    cout << "HT size: " << ht.size() << endl;
    if( ht.find("hi9") != nullptr ){
        cout << "Found hi9" << endl;
    }
    else {
        cout << "Did not find hi9" << endl;
    }
    ht.insert({"hi7",17});
    cout << "size: " << ht.size() << endl;
    return 0;
}
*/