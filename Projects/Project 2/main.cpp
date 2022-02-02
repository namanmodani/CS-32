#include "Map.h";
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    // default constructor
    Map m1;
    // For an empty map:

    assert(m1.empty()); // test that an empty map should return true when calling empty()
    assert(m1.size() == 0); // test that an empty map's size is 0
    assert(!m1.update("A", 0)); // test that update returns false and does nothing for an empty map (because there is nothing to update)
    assert(!m1.erase("A"));  // test that erase returns false for an empty map (because there are no nodes to erase)
    assert(!m1.contains("B")); // test that contains returns false for an empty map (because an empty map contains nothing)

    KeyType k1 = "TEST1";
    ValueType v1 = 0;
    assert(!m1.get(k1, v1) && v1 == 0); // test that get (two parameters) returns false for an empty map and that v1 is unchanged
    assert(!m1.get(0, k1, v1) && k1 == "TEST1" && v1 == 0); // test that get (three parameters) returns false for an empty map and that k1 and v1 are still unchanged

    // copy constructor
    Map m2(m1);
    // Now, we will confirm that all of the above test cases work for an empty map made using the copy constructor

    assert(m2.empty()); // test that an empty map should return true when calling empty()
    assert(m2.size() == 0); // test that an empty map's size is 0
    assert(!m2.update("A", 0)); // test that update returns false and does nothing for an empty map (because there is nothing to update)
    assert(!m2.erase("A")); // test that erase returns false for an empty map (because there are no nodes to erase)
    assert(!m2.contains("B")); // test that contains returns false for an empty map (because an empty map contains nothing)

    KeyType k2 = "TEST2";
    ValueType v2 = 1;
    assert(!m2.get(k2, v2) && v2 == 1); // test that get (two parameters) returns false for an empty map and that v2 is unchanged
    assert(!m2.get(0, k2, v2) && k2 == "TEST2" && v2 == 1); // test that get (three parameters) returns false for an empty map and that k2 and v2 are still unchanged

    // Now, we will test most of our functions for non-empty linkedlists

    assert(m1.insert("C", 3.3)); // test that insert() returns true when inserting a node with key "C" and value 1.1 into an empty map
    assert(!m1.empty()); // test that empty() returns false because m1 now contains a node
    assert(m1.size() == 1); // test that size() correctly returns m1's size of 1
    assert(m1.update("C", 4.4)); // test that update() returns true when updating key "C"s value to 4.4
    assert(!m1.update("P", 4.4)); // test that update() returns false because linkedlist is not empty but still does not contain key "P"
    assert(m1.contains("C")); // test that contains() returns true because m1 contains key "C"

    KeyType k3 = "C";
    ValueType v3 = 2;
    assert(m1.get(k3, v3) && v3 == 4.4); // test that get (two parameters) returns true and v3 is changed to 4.4 when passing "C" as the key
    k3 = "DONOTCHANGE";
    v3 = 100;

    assert(m1.get(0, k3, v3) && k3 == "C" && v3 == 4.4); // test that get (three parameters) returns true and that k3 and v3 are changed back to "C" and 4.4 despite just being manually changed
    assert(m1.insert("M", 7.7)); // test that insert() returns true when adding to the very end of the linkedlist
    assert(m1.size() == 2); // test that size correctly incremented to 2
    assert(m1.insert("B", 1.1)); // test that insert() returns true when adding to the very front of the linkedlist
    assert(m1.size() == 3); // test that size correctly incremented to 3
    assert(m1.insert("F", 5.5)); // test that insert() returns true when adding to the middle of the linkedlist
    assert(m1.size() == 4); // test that size correctly incremented to 4
    assert(m1.insertOrUpdate("A", 100)); // test that insertOrUpdate() returns true when adding to the very front of the linkedlist
    assert(m1.size() == 5); // test that size correctly incremented to 5
    assert(m1.insertOrUpdate("Z", 8.8)); // test that insertOrUpdate() returns true when adding to the very back of the linkedlist
    assert(m1.size() == 6); // test that size correctly incremented to 6
    assert(m1.insertOrUpdate("K", 6.6)); // test that insertOrUpdate() returns true when adding to the middle of the linkedlist
    assert(m1.size() == 7); // test that size correctly incremented to 7
    assert(m1.insertOrUpdate("A", 1.1)); // test that insertOrUpdate() returns true when updating a node in the linkedlist
    assert(m1.size() == 7); // test that size remained at 7 (because we did not insert anything this time!)

    assert(!m1.erase("Apple Pie")); // test that erase() returns false because our linkedlist does not contain a node with key "Apple Pie"
    Map m5(m1);
    assert(m5.erase("B")); // test that erase() correctly erases the second first node
    assert(m5.erase("M") && m5.size() == 5); // test that erase() correctly erases the second last node
    assert(m1.erase("A")); // test that erase() returns true after erasing our head node
    assert(m1.size() == 6); // test that size correctly decremented to 6 after erasing
    assert(m1.erase("Z")); // test that erase() returns true after erasing our tail node
    assert(m1.size() == 5); // test that size correctly decremented to 5 after erasing
    assert(m1.erase("F")); // test that erase() returns true after erasing a node in the middle of our linkedlist
    assert(m1.size() == 4); // test that size correctly decremented to 4 after erasing

    KeyType k4 = "B";
    ValueType v4 = 0;
    assert(m1.get(k4, v4) && v4 == 1.1); // we already tested this before, but we want to ensure that the value corresponding to key "B" is 1.1 before we start updating. this also checks that it works for our head node.
    assert(m1.update(k4, 2.2)); // we already tested this before, but it confirms that update() works for our head node
    assert(m1.get(k4, v4) && v4 == 2.2); // test that update() correctly changes the value corresponding to key "B" to 2.2, and test that get() correctly reflects this change
    assert(m1.insertOrUpdate(k4, 3.3));
    assert(m1.get(k4, v4) && v4 == 3.3); // test that insertOrUpdate() correctly changes the value corresponding to key "B" to 3.3, and test that get() correctly reflects this change
    k4 = "DONOTCHANGE";
    v4 = 100;
    assert(m1.get(0, k4, v4) && k4 == "B" && v4 == 3.3); // test that get (three parameters) correctly works for our head node
    assert(m1.get(2, k4, v4) && k4 == "K" && v4 == 6.6); // test that get (three parameters) correctly works for nodes in the middle of our linkedlist
    assert(m1.get(3, k4, v4) && k4 == "M" && v4 == 7.7); // test that get (three parameters) correctly works for our tail node
    assert(!m1.get(4, k4, v4) && k4 == "M" && v4 == 7.7); // test that get (three parameters) correctly returns false and does not change k4 or v4 when i >= size of our linkedlist.
    assert(!m1.get("Apple Pie", v4) && v4 == 7.7); // test that get (two parameters) correctly returns false and does not change v4 for invalid keys in a non-empty linkedlist
    assert(m1.get("K", v4) && v4 == 6.6); // test that get (two parameters) correctly works for nodes in the middle of our linkedlist
    assert(m1.get("M", v4) && v4 == 7.7); // test that get (two parameters) correctly works for our tail node
    assert(m1.update("K", 7.7)); // test that update() works for nodes in the middle of our linkedlists
    assert(m1.update("M", 8.8)); // test that update() works for our tail node
    assert(m1.insertOrUpdate("K", 5.5)); // test that insertOrUpdate() works for nodes in the middle of our linkedlists
    assert(m1.insertOrUpdate("M", 6.6)); // test that insertOrUpdate() works for our tail node
    assert(m1.contains("B")); // test that contains() works for our head node
    assert(m1.contains("K")); // test that contains() works for nodes in the middle of our linkedlists
    assert(m1.contains("M")); // test that contains() works for our tail node


    // Now, we will test to make sure our copy constructor works correctly
    Map m3(m1);
    assert(m1.size() == m3.size()); // test that the copy constructor makes the two maps have the same size
    k1 = "MAP1";
    v1 = -1;
    k3 = "MAP3";
    v3 = 1;

    // We need to make sure that both maps have exactly four elements and that their nodes have the exact same key and values
    assert(m1.get(0, k1, v1) && m3.get(0, k3, v3) && k1 == k3 && v1 == v3); // Makes sure the head node for both maps are identical
    assert(m1.get(1, k1, v1) && m3.get(1, k3, v3) && k1 == k3 && v1 == v3); // Makes sure the second node for both maps are identical
    assert(m1.get(2, k1, v1) && m3.get(2, k3, v3) && k1 == k3 && v1 == v3); // Makes sure the third node for both maps are identical
    assert(m1.get(3, k1, v1) && m3.get(3, k3, v3) && k1 == k3 && v1 == v3); // Makes sure the tail node for both maps are identical
    assert(!m1.get(4, k1, v1) && !m3.get(4, k3, v3)); // Makes sure that both maps do not have more than 4 elements


    // Now, we will test to make sure our assignment operator works correctly
    // *m2 is still an empty linkedlist
    m2.insert("Apple", 100);
    m2.insert("Banana", 200);
    m2.insert("Carrot", 300);
    assert(m1.size() != m2.size()); // Obvious test but just meant to remind us that m1 and m2 are different maps.
    m2 = m1; // This should clear whatever is in m2 and replace it with m1's nodes.
    assert(m1.size() == m2.size()); // test that the assignment operator makes the two maps have the same size

    // Now, we simply need to repeat the exact same cases as above but between m1 and m2
    k1 = "MAP1";
    v1 = -1;
    k2 = "MAP2";
    v2 = 1;

    assert(m1.get(0, k1, v1) && m2.get(0, k2, v2) && k1 == k2 && v1 == v2); // Makes sure the head node for both maps are identical
    assert(m1.get(1, k1, v1) && m2.get(1, k2, v2) && k1 == k2 && v1 == v2); // Makes sure the second node for both maps are identical
    assert(m1.get(2, k1, v1) && m2.get(2, k2, v2) && k1 == k2 && v1 == v2); // Makes sure the third node for both maps are identical
    assert(m1.get(3, k1, v1) && m2.get(3, k2, v2) && k1 == k2 && v1 == v2); // Makes sure the tail node for both maps are identical
    assert(!m1.get(4, k1, v1) && !m2.get(4, k2, v2)); // Makes sure that both maps do not have more than 4 elements

    Map empty;
    Map empty1(m1);
    Map empty2(m2);
    Map empty3(m3);
    empty1 = empty2 = empty3 = empty;
    assert(empty1.empty() && empty2.empty() && empty3.empty()); // test that multiple assignments at once work (here, we copy construct m1, m2, and m3, but they should all become empty when assigned to Map empty)

    // Now, we will test to make sure that our swap function works correctly
    Map m4;
    m4.insert("Apple", 1);
    m4.insert("Banana", 2);
    m4.insert("Cucumber", 3);
    m1.swap(m4);

    assert(m1.size() == 3); // test that m1 now has three nodes (because m4 had three nodes before they were swapped)
    assert(m1.contains("Apple") && m1.contains("Banana") && m1.contains("Cucumber")); // test that m1 contains all of the nodes that m4 contained before the swap
    assert(m4.size() == 4); // test that m4 now has four nodes (because m1 had four nodes before they were swapped)
    assert(m4.contains("B") && m4.contains("C") && m4.contains("M") && m4.contains("K")); // test that m4 contains all of the nodes that m1 contained before the swap

    // Now, we will test to make sure our merge function works properly.
    Map a;
    a.insert("A", 1);
    a.insert("B", 2);
    a.insert("C", 3);
    a.insert("D", 4);
    a.insert("E", 5);

    Map b;
    b.insert("A", 1);
    b.insert("B", 2);
    b.insert("C", 3);
    b.insert("D", 4);
    b.insert("E", 5);

    Map c;

    assert(merge(a, b, c) && c.size() == 5); // test that the empty map correctly contains the five matching elements in a and b after merge() is called
    assert(merge(a, b, c) && c.size() == 5); // test that merge works for a nonempty result map and the size will still be at 5
    b.update("A", 2);
    b.update("E", 2);
    assert(!merge(a, b, c) && c.size() == 3); // test that after updating the values in b, merge should return false and only include 3 elements in result (since some values don't match now)
    assert(merge(a, a, c) && c.size() == 5); // test that merge works like an assignment operator when m1 and m2 are the same map

    Map d;
    Map e;

    assert(merge(d, e, c) && c.empty()); // test that merge works when m1 and m2 are empty
    d.insert("Z", 1);
    assert(merge(d, e, c) && c.contains("Z") && c.size() == 1); // test that merge works with m2 empty and m1 having one node
    assert(merge(e, d, c) && c.contains("Z") && c.size() == 1); // test that merge works with m1 empty and m2 having one node
    c.erase("Z");
    e.insert("Z", 1);
    assert(merge(d, e, c) && c.contains("Z") && c.size() == 1); // test that merge works with two linked lists that both only have one node
    assert(merge(c, a, c) && c.size() == 6); // test that merge works when m1 and result are the same map
    assert(merge(a, d, d) && d.size() == 6); // test that merge works when m2 and result are the same map
    assert(merge(d, d, d) && d.size() == 6); // test that merge works when m1, m2, and result all are the same map

    c = a;
    c.insert("F", 1);
    c.insert("G", 2);
    c.insert("H", 3);
    assert(merge(a, c, d) && d.size() == 8); // test that merge works when m2 contains everything in m1 and more
    assert(merge(c, a, d) && d.size() == 8); // test that merge works when m1 contains everything in m2 and more
    a = b;
    a.update("A", 100);
    a.update("B", 100);
    a.update("C", 100);
    a.update("D", 100);
    a.update("E", 100);
    assert(!merge(a, b, c) && c.empty()); // test that merge works when m1 and m2 have the exact same keys but all different values (so result should be empty)

    Map f;
    f.insert("A", 1);
    f.insert("B", 1);
    f.insert("C", 1);
    Map g;
    g.insert("D", 1);
    g.insert("E", 1);
    g.insert("F", 1);
    assert(merge(f, g, a) && a.size() == 6); // test that merge works when m1 and m2 do not share any keys

    Map x;
    Map y;
    x.insert("A", 1);
    x.insert("B", 2);
    y.insert("C", 3);
    y.insert("D", 4);
    assert(merge(x, y, x) && x.size() == 4); // another test to check that merge works when m1 and result are the same, for two maps without any shared keys

    // Finally, we need to test our reassign function
    Map reassign1;
    Map reassign2;

    reassign1.insert("Ethel", 123);
    reassign1.insert("Fred", 456);
    reassign1.insert("Lucy", 789);
    reassign1.insert("Ricky", 321);

    reassign(reassign1, reassign2);
    assert(reassign1.size() == reassign2.size()); // test that reassign2 now has four keys like reassign1

    // since all of the values were reassigned, we can use our merge function to confirm that reassign1 is now empty
    // if reassign correctly did its job, all of the keys should correspond but none of the values should match (meaning result should end up being empty)
    assert(!merge(reassign1, reassign2, reassign1) && reassign1.empty());

    Map reassign3;
    reassign(reassign3, reassign2);
    assert(reassign2.empty()); // test that using reassign with m being an empty map sets result to be an empty map as well
    reassign3.insert("A", 999);
    reassign(reassign3, reassign2);
    assert(reassign2.get("A", v1) && reassign3.get("A", v2) && reassign2.size() == 1 && reassign3.size() == 1 && v1 == 999 && v2 == 999); // test that both reassign2 and reassign have the same single key/value pair

    Map reassign4;
    reassign4.insert("Ethel", 456);
    reassign4.insert("Fred", 123);
    reassign4.insert("Lucy", 456);
    reassign(reassign4, reassign4); // test that reassign works when m and result are the same map.

    // test that all of the values were correctly reassigned
    assert(reassign4.get("Ethel", v1) && v1 == 456);
    assert(reassign4.get("Fred", v1) && v1 == 456);
    assert(reassign4.get("Lucy", v1) && v1 == 123);

    cerr << "All tests passed!" << endl;
}