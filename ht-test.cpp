#include "ht.h"
#include "hash.h"
#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <functional>
#include <cassert>
#include <vector>
using namespace std;

// NEW FILE 5 - WHAT IS WRONG ALL MY TESTS PASS
//  Test function for inserting elements and triggering resizing
void testInsertResize()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.5, dh);

    // Insert elements to exceed the load factor threshold
    for (int i = 0; i < 15; ++i)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    size_t size_before_resize = ht.size();
    // Insert an item to trigger resizing
    ht.insert({"trigger_resize", 100});

    size_t size_after_resize = ht.size();
    assert(size_after_resize > size_before_resize); // Should resize correctly

    cout << "Insert and Resize Test passed!" << endl;
}

// Test function to check if the load factor triggers resizing correctly
void testLoadFactorResize()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.7, dh);

    // Insert enough elements to be just below the load factor
    for (int i = 0; i < 7; ++i)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    size_t initial_size = ht.size();

    // Insert to exceed the load factor and trigger resizing
    ht.insert({"trigger_resize", 100});

    size_t new_size = ht.size();
    assert(new_size > initial_size); // Should have resized

    cout << "Load Factor Resize Test passed!" << endl;
}

// Test function to check for stress insertion and resizing
void testStressInsertResize()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.5, dh);

    // Stress test by inserting a large number of elements
    for (int i = 0; i < 50; ++i)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    // Check if all elements are present and table resized correctly
    for (int i = 0; i < 50; ++i)
    {
        std::stringstream ss;
        ss << "key" << i;
        assert(ht.find(ss.str()) != nullptr); // Should find all inserted elements
    }

    cout << "Stress Insert and Resize Test passed!" << endl;
}

// test function to check probing logic and handling of deletions
void testProbingAndDeletions()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.7, dh);

    // Iinsert some elements
    ht.insert({"key1", 1});
    ht.insert({"key2", 2});
    ht.insert({"key3", 3});

    // test deletion
    ht.remove("key2");
    assert(ht.find("key2") == nullptr); // should be deleted

    // re-insert to check probing logic
    ht.insert({"key2", 22});
    assert(ht["key2"] == 22); // should find the re-inserted value

    cout << "Probing and Deletions Test passed!" << endl;
}

// test function to check memory issues and detect potential leaks
void testMemoryManagement()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.5, dh);

    // insert and remove to check for memory leaks
    ht.insert({"key1", 1});
    ht.remove("key1");

    ht.insert({"key2", 2});
    ht.remove("key2");

    cout << "Memory Management Test passed!" << endl;
}

int main()
{
    // Run the test functions
    testInsertResize();
    testLoadFactorResize();
    testStressInsertResize();
    testProbingAndDeletions();
    testMemoryManagement();

    cout << "All tests completed successfully!" << endl;
    return 0;
}

// NEW FILE 4
/*
// function to print all items in the hash table
void reportAllItems(const HashTable<string, int> &ht)
{
    ht.reportAll(std::cout);
}

// test function to check resizing behavior
void testResizeBehavior()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.5, dh);

    size_t initial_size = ht.size();
    cout << "Initial size: " << initial_size << endl;

    // insert items to trigger resizing
    for (int i = 0; i < 30; ++i)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    size_t new_size = ht.size();
    cout << "Size after insertion and possible resizing: " << new_size << endl;

    // ensure table resize properly
    assert(new_size > initial_size);
    cout << "Resize behavior test passed!" << endl;
}

// test function to check correct insertion and updating of items
void testInsertAndUpdate()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.7, dh);

    ht.insert({"key1", 1});
    ht.insert({"key2", 2});

    assert(ht.find("key1") != nullptr);
    assert(ht.find("key2") != nullptr);

    // update existing key
    ht["key1"] = 11;
    assert(ht["key1"] == 11);

    cout << "Insert and update test passed!" << endl;
}

// test function check deletion behavior
void testDeletion()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.7, dh);

    ht.insert({"key1", 1});
    ht.insert({"key2", 2});

    ht.remove("key1");
    assert(ht.find("key1") == nullptr); // should be deleted

    ht.remove("key2");
    assert(ht.find("key2") == nullptr); // should be deleted

    cout << "Deletion test passed!" << endl;
}

// test function to check rehashing and table resizing
void testRehashing()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.5, dh);

    for (int i = 0; i < 15; ++i)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    size_t size_before_resize = ht.size();

    // trigger resizing
    ht.insert({"key15", 15});

    size_t size_after_resize = ht.size();

    assert(size_after_resize > size_before_resize); // table should have resized
    cout << "Rehashing and resizing test passed!" << endl;
}

// test function to check stress insertion and memory handling
void testStressInsertion()
{
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.8, dh);

    for (int i = 0; i < 1000; ++i)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    assert(ht.size() == 1000); // ensure all items inserted successfully
    cout << "Stress insertion test passed!" << endl;
}

int main()
{
    // run test functions
    testResizeBehavior();
    testInsertAndUpdate();
    testDeletion();
    testRehashing();
    testStressInsertion();

    cout << "All tests passed!" << endl;
    return 0;
}

// NEW FILE 3
/*
#include "ht.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    //test linear probe
    HashTable<string, int, LinearProber<string>> ht_linear(0.4);
    //insert init key val pairs
    ht_linear.insert({"key1", 100});
    ht_linear.insert({"key2", 200});
    ht_linear.insert({"key3", 300});

    //test find key
    auto item = ht_linear.find("key1");
    if (item != nullptr)
    {
        cout << "Found key1 with value: " << item->second << endl;
    }
    else
    {
        cout << "Key1 not found!" << endl;
    }

    //test update
    ht_linear["key2"] = 250;
    cout << "Updated key2's value to: " << ht_linear["key2"] << endl;

    //test resize with insert
    ht_linear.insert({"key4", 400});
    ht_linear.insert({"key5", 500});

    cout << "HashTable size after inserts and resizing: " << ht_linear.size() << endl;

    // test delete
    ht_linear.remove("key3");
    if (ht_linear.find("key3") == nullptr)
    {
        cout << "Deleted key3 successfully" << endl;
    }
    else
    {
        cout << "Failed to delete key3" << endl;
    }

    // test with double hash
    DoubleHashProber<string, MyStringHash> dh;
    HashTable<string, int, DoubleHashProber<string, MyStringHash>> ht_double(0.7, dh);

    ht_double.insert({"dkey1", 10});
    ht_double.insert({"dkey2", 20});

    if (ht_double.find("dkey1") != nullptr)
    {
        cout << "Found dkey1 with value: " << ht_double["dkey1"] << endl;
    }
    else
    {
        cout << "Failed to find dkey1" << endl;
    }

    ht_double["dkey2"] = 25;
    cout << "Updated dkey2's value to: " << ht_double["dkey2"] << endl;

    // test collisions by inserting similar keys
    ht_double.insert({"dkey3", 30});
    ht_double.insert({"dkey4", 40});

    cout << "HashTable size after double hash inserts: " << ht_double.size() << endl;

    return 0;
}

// NEW FILE 2 TEST RESIZE
/*
void test_resize()
{
    // hash table with a low load factor to trigger resizing quickly
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash>> ht(0.4, dh);

    // insert enough elements to trigger resizing
    for (int i = 0; i < 20; i++)
    {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), i});
    }

    // check if table has resized to the expected new capacity
    assert(ht.size() == 20);

    // check if all keys are still accessible after resizing
    for (int i = 0; i < 20; i++)
    {
        std::stringstream ss;
        ss << "key" << i;
        auto item = ht.find(ss.str());
        assert(item != nullptr);
        assert(item->second == i);
    }

    // test deletion and rehashing after resize
    ht.remove("key3");
    assert(ht.find("key3") == nullptr); // Should not be found
}

// main function to run the test case
int main()
{
    test_resize();
    std::cout << "Resize test passed!" << std::endl; //passing currently
    return 0;
}

// NEW FILE 1
/*
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