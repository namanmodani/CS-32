CS32 Homework 4, Winter 2022

Winter 2022 CS 32

Homework 4
----------

**Time due: 11:00 PM Tuesday, March 1**

1.  The files [Map.h](Map.h) and [Map.cpp](Map.cpp) contain the definition and implementation of Map implemented using a doubly-linked list. A client who wants to use a Map has to change the type alias declarations in Map.h, and within one source file, cannot have two Maps containing different types.
    
    Eliminate the `using` statements defining the type aliases, and change Map to be a class template, so that a client can say
    
    	#include "Map.h"
    	#include <string>
    	using std::string;
    	...
    	Map<int, double> mid;
    	Map<string, int> msi;
    	mid.insert(42, -1.25);
    	msi.insert("Fred", 123);
    	...
    
    Also, change `merge` and `reassign` to be function templates.
    
    (Hint: Transforming the solution based on type aliases is a mechanical task that takes five minutes if you know what needs to be done. What makes this problem non-trivial for you is that you haven't done it before; the syntax for declaring templates is new to you, so you may not get it right the first time.)
    
    (Hint: Template typename parameters don't have to be named with single letters like `T`; they can be names of your choosing. You might find that by choosing the names `KeyType` and `ValueType`, you'll have many fewer changes to make.)
    
    (Hint: The Node class nested in the Map class can talk about the template parameters of the Map class; it should not itself be a template class.)
    
    The definitions _and_ implementations of your Map class template and the `merge` and `reassign` template functions must be in just one file, Map.h, which is all that you will turn in for this problem. Although the implementation of a non-template non-inline function should not be placed in a header file (because of linker problems if that header file were included in multiple source files), the implementation of a template function, whether or not it's declared inline, _can_ be in a header file without causing linker problems, and in fact the header file is the normal place to put it in most C++ environments.
    
    There's a pre-C++20 language technicality that relates to a type declared inside a class template, like `N` below:
    
    	template <typename T>
    	class M
    	{
    	  ...
    	  struct N
    	  {
    	    ...
    	  };
    	  N\* f();
    	  ...
    	};
    
    The technicality affects how we specify the return type of a function (such as `M<T>::f`) when that return type uses a type defined inside a template class (such as `M<T>::N`). If we attempt to implement `f` this way:
    
    	template <typename T>
    	M<T>::N\* M<T>::f()    // Error!  Won't compile in C++17 or earlier.
    	{
    	  ...
    	}
    
    the pre-C++20 technicality requires the compiler to not recognize `M<T>::N` as a type name; it must be announced as a type name this way:
    
    	template <typename T>
    	typename M<T>::N\* M<T>::f()    // OK in all C++ versions
    	{
    	  ...
    	}
    
    Giving g32 the `-std=c++20` option will cause it to use C++20. We will test your code with C++17, unless it doesn't compile, in which case we'll test it with C++20 instead.
    
    For you to not get a score of zero for this problem, this test program that we will try with your `Map.h` **must** build and execute successfully under both g32 and either Visual C++ or clang++, with no `Map.cpp` file on the command line (for g32) or as part of the project (for Visual C++ or Xcode):
    
    	#include "Map.h"
    	#include <iostream>
    	#include <string>
    	#include <cassert>
    
    	using namespace std;
    
    	void test()
    	{
    	    Map<int, double> mid;
    	    Map<string, int> msi;
    	    assert(msi.empty());
    	    assert(msi.size() == 0);
    	    assert(msi.insert("Hello", 10));
    	    assert(mid.insert(10, 3.5));
    	    assert(msi.update("Hello", 20));
    	    assert(mid.update(10, 4.75));
    	    assert(msi.insertOrUpdate("Goodbye", 30));
    	    assert(msi.erase("Goodbye"));
    	    assert(mid.contains(10));
    	    int k;
    	    assert(msi.get("Hello", k));
    	    string s;
    	    assert(msi.get(0, s, k));
    	    Map<string, int> msi2(msi);
    	    msi2.swap(msi);
    	    msi2 = msi;
    	    merge(msi,msi2,msi);
    	    merge(mid,mid,mid);
    	    reassign(msi,msi2);
    	    reassign(mid,mid);
    	}
    
    	int main()
    	{
    	    test();
    	    cout << "Passed all tests" << endl;
    	}
    
2.  Consider this program:
    
    	#include "Map.h"  // class template from problem 1
    
            class Coord
            {
              public:
                Coord(int r, int c) : m\_r(r), m\_c(c) {}
                Coord() : m\_r(0), m\_c(0) {}
                double r() const { return m\_r; }
                double c() const { return m\_c; }
              private:
                double m\_r;
                double m\_c;
            };
    
    	int main()
    	{
    	    Map<int, double> mid;
    	    mid.insert(42, -1.25);         // OK
    	    Map<Coord, int> mpi;
    	    mpi.insert(Coord(40,10), 32);  // error!
    	}
    
    Explain in a sentence or two why the call to `Map<Coord, int>::insert` causes at least one compilation error. (Notice that the call to `Map<int, double>::insert` is fine.) Don't just transcribe a compiler error message; your answer must indicate you understand the the ultimate root cause of the problem and why that is connected to the call to `Map<Coord, int>::insert`.
    
3.  We anticipate that many people working on Project 3 will spend a lot of time debugging something that arises from a common novice misunderstanding. To save you that time later, we'll give you a chance to make that mistake in a simpler context, so you can work out that issue and how it manifests itself. (It may turn out that you don't have that misunderstanding, so you won't have any issues doing this problem. Still, keep this problem in mind, because you may still make the mistake in Project 3.)
    
    Be sure to run your code for this problem under g32 to be sure there are no memory leaks.
    
    Material about vectors, lists, and iterators are in lecture09-updated.pptx in the [slides for lecture 1](http://careynachenberg.weebly.com/cs-slides.html) and the [STL lecture](https://bruinlearn.ucla.edu/courses/109755/modules/items/4752681) and [STL slides](../../l2/index.html) for lectures 2&3.
    
    1.  Implement the `removeOdd` function; you must use `list`'s `erase` member function; you must not use `lists`'s `remove` or `remove_if` member functions. Each int in the list must be examined for oddness no more than once.
        
        	#include <list>
        	#include <vector>
        	#include <algorithm>
        	#include <iostream>
        	#include <cassert>
        	using namespace std;
        
        	  // Remove the odd integers from li.
        	  // It is acceptable if the order of the remaining even integers is not
        	  // the same as in the original list.
        	void removeOdd(list<int>& li)
        	{
        	}
        
        	void test()
        	{
        	    int a\[8\] = { 2, 8, 5, 6, 7, 3, 4, 1 };
        	    list<int> x(a, a+8);  // construct x from the array
        	    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
        	    removeOdd(x);
        	    assert(x.size() == 4);
        	    vector<int> v(x.begin(), x.end());  // construct v from x
        	    sort(v.begin(), v.end());
        	    int expect\[4\] = { 2, 4, 6, 8 };
        	    for (int k = 0; k < 4; k++)
        	        assert(v\[k\] == expect\[k\]);
        	}
        
        	int main()
        	{
        	    test();
        	    cout << "Passed" << endl;
        	}
        
        For this problem, you will turn a file named `oddlist.cpp` with the body of the `removeOdd` function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.
        
    2.  Implement the `removeOdd` function; you must use `vector`'s `erase` member function. Each int in the vector must be examined for oddness no more than once.
        
        	#include <vector>
        	#include <algorithm>
        	#include <iostream>
        	#include <cassert>
        	using namespace std;
        
        	  // Remove the odd integers from v.
        	  // It is acceptable if the order of the remaining even integers is not
        	  // the same as in the original vector.
        	void removeOdd(vector<int>& v)
        	{
        	}
        
        	void test()
        	{
        	    int a\[8\] = { 2, 8, 5, 6, 7, 3, 4, 1 };
        	    vector<int> x(a, a+8);  // construct x from the array
        	    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
        	    removeOdd(x);
        	    assert(x.size() == 4);
        	    sort(x.begin(), x.end());
        	    int expect\[4\] = { 2, 4, 6, 8 };
        	    for (int k = 0; k < 4; k++)
        	        assert(x\[k\] == expect\[k\]);
        	}
        
        	int main()
        	{
        	    test();
        	    cout << "Passed" << endl;
        	}
        
        For this problem, you will turn a file named `oddvector.cpp` with the body of the `removeOdd` function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.
        
    3.  Implement the `removeBad` function; you must use `list`'s `erase` member function; you must not use `lists`'s `remove` or `remove_if` member functions. Each Movie in the list must have its rating examined no more than once.
        
        	#include <list>
        	#include <vector>
        	#include <algorithm>
        	#include <iostream>
        	#include <cassert>
        	using namespace std;
        
        	vector<int> destroyedOnes;
        
        	class Movie
        	{
        	  public:
        	    Movie(int r) : m\_rating(r) {}
        	    ~Movie() { destroyedOnes.push\_back(m\_rating); }
        	    int rating() const { return m\_rating; }
        	  private:
        	    int m\_rating;
        	};
        
        	  // Remove the movies in li with a rating below 50 and destroy them.
        	  // It is acceptable if the order of the remaining movies is not
        	  // the same as in the original list.
        	void removeBad(list<Movie\*>& li)
        	{
        	}
        
        	void test()
        	{
        	    int a\[8\] = { 85, 80, 30, 70, 20, 15, 90, 10 };
        	    list<Movie\*> x;
        	    for (int k = 0; k < 8; k++)
        	        x.push\_back(new Movie(a\[k\]));
        	    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
        	    removeBad(x);
        	    assert(x.size() == 4 && destroyedOnes.size() == 4);
        	    vector<int> v;
        	    for (list<Movie\*>::iterator p = x.begin(); p != x.end(); p++)
        	    {
        	        Movie\* mp = \*p;
        	        v.push\_back(mp->rating());
        	    }
        	      // Aside:  Since C++11, the above loop could be
        	      //     for (auto p = x.begin(); p != x.end(); p++)
        	      //     {
        	      //         Movie\* mp = \*p;
        	      //         v.push\_back(mp->rating());
        	      //     }
        	      // or    
        	      //     for (auto p = x.begin(); p != x.end(); p++)
        	      //     {
        	      //         auto mp = \*p;
        	      //         v.push\_back(mp->rating());
        	      //     }
        	      // or    
        	      //     for (Movie\* mp : x)
        	      //         v.push\_back(mp->rating());
        	      // or    
        	      //     for (auto mp : x)
        	      //         v.push\_back(mp->rating());
        	    sort(v.begin(), v.end());
        	    int expect\[4\] = { 70, 80, 85, 90 };
        	    for (int k = 0; k < 4; k++)
        	        assert(v\[k\] == expect\[k\]);
        	    sort(destroyedOnes.begin(), destroyedOnes.end());
        	    int expectGone\[4\] = { 10, 15, 20, 30 };
        	    for (int k = 0; k < 4; k++)
        	        assert(destroyedOnes\[k\] == expectGone\[k\]);
        	    for (list<Movie\*>::iterator p = x.begin(); p != x.end(); p++)
        	        delete \*p;
        	}
        
        	int main()
        	{
        	    test();
        	    cout << "Passed" << endl;
        	}
        
        For this problem, you will turn a file named `badlist.cpp` with the body of the `removeBad` function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.
        
    4.  Implement the `removeBad` function; you must use `vector`'s `erase` member function. Each Movie in the vector must have its rating examined no more than once.
        
        	#include <vector>
        	#include <algorithm>
        	#include <iostream>
        	#include <cassert>
        	using namespace std;
        
        	vector<int> destroyedOnes;
        
        	class Movie
        	{
        	  public:
        	    Movie(int r) : m\_rating(r) {}
        	    ~Movie() { destroyedOnes.push\_back(m\_rating); }
        	    int rating() const { return m\_rating; }
        	  private:
        	    int m\_rating;
        	};
        
        	  // Remove the movies in v with a rating below 50 and destroy them.
        	  // It is acceptable if the order of the remaining movies is not
        	  // the same as in the original vector.
        	void removeBad(vector<Movie\*>& v)
        	{
        	}
        
        	void test()
        	{
        	    int a\[8\] = { 85, 80, 30, 70, 20, 15, 90, 10 };
        	    vector<Movie\*> x;
        	    for (int k = 0; k < 8; k++)
        	        x.push\_back(new Movie(a\[k\]));
        	    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
        	    removeBad(x);
        	    assert(x.size() == 4 && destroyedOnes.size() == 4);
        	    vector<int> v;
        	    for (int k = 0; k < 4; k++)
        	        v.push\_back(x\[k\]->rating());
        	    sort(v.begin(), v.end());
        	    int expect\[4\] = { 70, 80, 85, 90 };
        	    for (int k = 0; k < 4; k++)
        	        assert(v\[k\] == expect\[k\]);
        	    sort(destroyedOnes.begin(), destroyedOnes.end());
        	    int expectGone\[4\] = { 10, 15, 20, 30 };
        	    for (int k = 0; k < 4; k++)
        	        assert(destroyedOnes\[k\] == expectGone\[k\]);
        	    for (vector<Movie\*>::iterator p = x.begin(); p != x.end(); p++)
        	        delete \*p;
        	}
        
        	int main()
        	{
        	    test();
        	    cout << "Passed" << endl;
        	}
        
        For this problem, you will turn a file named `badvector.cpp` with the body of the `removeBad` function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.
        
    5.  Make sure you understand why the code below passes the first two tests but fails the third. Draw pictures if necessary. Don't forget the lesson you learn from this problem when working on Project 3.
        
        #include <iostream>
        #include <vector>
        #include <list>
        using namespace std;
        
        const int MAGIC = 11223344;
        
        void test()
        {
            bool allValid = true;
        
            vector<int> v1(5, MAGIC);
            int k = 0;
            for ( ; k != v1.size(); k++)
            {
                if (v1\[k\] != MAGIC)
                {
                    cout << "v1\[" << k << "\] is " << v1\[k\] << ", not " << MAGIC <<"!" << endl;
                    allValid = false;
                }
                if (k == 2)
                {
                    for (int i = 0; i < 5; i++)
                        v1.push\_back(MAGIC);
                }
            }
            if (allValid  &&  k == 10)
                cout << "Passed test 1" << endl;
            else
                cout << "Failed test 1" << endl;
        
            allValid = true;
            list<int> l1(5, MAGIC);
            k = 0;
            for (list<int>::iterator p = l1.begin(); p != l1.end(); p++, k++)
            {
                if (\*p != MAGIC)
                {
                    cout << "Item# " << k << " is " << \*p << ", not " << MAGIC <<"!" << endl;
                    allValid = false;
                }
                if (k == 2)
                {
                    for (int i = 0; i < 5; i++)
                        l1.push\_back(MAGIC);
                }
            }
            if (allValid  &&  k == 10)
                cout << "Passed test 2" << endl;
            else
                cout << "Failed test 2" << endl;
        
            allValid = true;
            vector<int> v2(5, MAGIC);
            k = 0;
            for (vector<int>::iterator p = v2.begin(); p != v2.end(); p++, k++)
            {
                if (k >= 20)  // prevent infinite loop
                    break;
                if (\*p != MAGIC)
                {
                    cout << "Item# " << k << " is " << \*p << ", not " << MAGIC <<"!" << endl;
                    allValid = false;
                }
                if (k == 2)
                {
                    for (int i = 0; i < 5; i++)
                        v2.push\_back(MAGIC);
                }
            }
            if (allValid  &&  k == 10)
                cout << "Passed test 3" << endl;
            else
                cout << "Failed test 3" << endl;
        }
        
        int main()
        {
            test();
        }
        
        Explain in a sentence or two what happens during the execution of test case 3 that eventually leads to test case 3 failing?
        
4.  A class has a _name_ (e.g., `Actor`) and zero or more _subclasses_ (e.g., the class with name `Peach` or the class with name `Enemy`). The following program reflects this structure:
    
    #include <iostream>
    #include <string>
    #include <vector>
    
    using namespace std;
    
    class Class
    {
      public:
        Class(string nm) : m\_name(nm) {}
        string name() const { return m\_name; }
        const vector<Class\*>& subclasses() const { return m\_subclasses; }
        void add(Class\* d) { m\_subclasses.push\_back(d); }
        ~Class();
      private:
        string m\_name;
        vector<Class\*> m\_subclasses;
    };
    
    Class::~Class()
    {
        for (size\_t k = 0; k < m\_subclasses.size(); k++)
            delete m\_subclasses\[k\];
    }
    
    void listAll(string path, const Class\* c)  // two-parameter overload
    {
        _You will write this code._
    }
    
    void listAll(const Class\* c)  // one-parameter overload
    {
        if (c != nullptr)
            listAll("", c);
    }
    
    int main()
    {
        Class\* d1 = new Class("Koopa");
        listAll(d1);
        cout << "====" << endl;
    
        d1->add(new Class("SoopaKoopa"));
        Class\* d2 = new Class("Enemy");
        d2->add(new Class("Piranha"));
        d2->add(d1);
        Class\* d3 = new Class("Goodie");
        d3->add(new Class("Flower"));
        d3->add(new Class("Mushroom"));
        d3->add(new Class("Star"));
        listAll(d3);
        cout << "====" << endl;
    
        Class\* d4 = new Class("Actor");
        d4->add(d2);
        d4->add(new Class("Peach"));
        d4->add(d3);
        listAll(d4);
        delete d4;
    }
    
    This main routine should produce the following output (the first line written is `Koopa`, not an empty line):
    
    Koopa
    ====
    Goodie
    Goodie=>Flower
    Goodie=>Mushroom
    Goodie=>Star
    ====
    Actor
    Actor=>Enemy
    Actor=>Enemy=>Piranha
    Actor=>Enemy=>Koopa
    Actor=>Enemy=>Koopa=>SoopaKoopa
    Actor=>Peach
    Actor=>Goodie
    Actor=>Goodie=>Flower
    Actor=>Goodie=>Mushroom
    Actor=>Goodie=>Star
    
    Each call to the one-parameter overload of `listAll` produces a list, one per line, of the inheritance path to each class in the inheritance tree rooted at `listAll`'s argument. An inheritance path is a sequence of class names separated by "=>". There is no "=>" before the first name in the inheritance path.
    
    1.  You are to write the code for the two-parameter overload of `listAll` to make this happen. You must not use any additional container (such as a stack), and the two-parameter overload of `listAll` must be recursive. You must not use any global variables or variables declared with the keyword `static`, and you must not modify any of the code we have already written or add new functions. You may use a loop to traverse the vector; you must not use loops to avoid recursion.
        
        Here's a useful function to know: The standard library string class has a + operator that concatenates strings and/or characters. For example,
        
        	string s("Hello");
        	string t("there");
        	string u = s + ", " + t + '!';
        	// Now u has the value "Hello, there!"
        
        It's also useful to know that if you choose to traverse an STL container using some kind of iterator, then if the container is const, you must use a `const_iterator`:
        
        	void f(const list<int>& c)  // c is const
        	{
        	    for (list<int>::const\_iterator it = c.begin(); it != c.end(); it++)
        	        cout << \*it << endl;
        	}
        
        (Of course, a vector can be traversed either by using some kind of iterator, or by using operator\[\] with an integer argument).
        
        For this problem, you will turn a file named `list.cpp` with the body of the two-parameter overload of the `listAll` function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above.
        
    2.  We introduced the two-parameter overload of `listAll`. Why could you not solve this problem given the constraints in part a if we had only a one-parameter `listAll`, and you had to implement _it_ as the recursive function?
        
5.  1.  In order to help do contact tracing to control the spread of a virus, the local health department maintains, for N people numbered 0 through N-1, a two-dimensional array of bool `hasContacted` that records which people have been in close contact with others: `hasContacted[i][j]` is true if and only if person i and person j have been in close contact. If person i has been in close contact with person k, and person k has been in close contact with person j, we call person k a _direct intermediary_ between person i and person j.
        
        The department has an algorithm that, for every pair of people i and j, determines how many direct intermediaries they have between them. Here's the code:
        
        	const int N = _some value_;
        	bool hasContacted\[N\]\[N\];
        	...
        	int numIntermediaries\[N\]\[N\];
        	for (int i = 0; i < N; i++)
        	{
        	    numIntermediaries\[i\]\[i\] = -1;  // the concept of intermediary
        				           // makes no sense in this case
        	    for (int j = 0; j < N; j++)
        	    {
        	        if (i == j)
        	            continue;
        	        numIntermediaries\[i\]\[j\] = 0;
        	        for (int k = 0; k < N; k++)
        	        {
        	            if (k == i  ||  k == j)
        	                continue;
        		    if (hasContacted\[i\]\[k\]  &&  hasContacted\[k\]\[j\])
        	        	numIntermediaries\[i\]\[j\]++;
        	        }
        	    }
        	}
        
        What is the time complexity of this algorithm, in terms of the number of basic operations (e.g., additions, assignments, comparisons) performed: Is it O(N), O(N log N), or what? Why? (Note: In this homework, whenever we ask for the time complexity, we care only about the high order term, so don't give us answers like O(N3+4N2).)
        
    2.  The algorithm in part a doesn't take advantage of the symmetry of communication: for every pair of persons i and j, hasContacted\[i\]\[j\] == hasContacted\[j\]\[i\]. One can skip a lot of operations and compute the number of direct intermediaries more quickly with this algorithm:
        
        	const int N = _some value_;
        	bool hasContacted\[N\]\[N\];
        	...
        	int numIntermediaries\[N\]\[N\];
        	for (int i = 0; i < N; i++)
        	{
        	    numIntermediaries\[i\]\[i\] = -1;  // the concept of intermediary
        				           // makes no sense in this case
        	    for (int j = 0; j < **i**; j++)  **// loop limit is now i, not N**
        	    {
        	        numIntermediaries\[i\]\[j\] = 0;
        	        for (int k = 0; k < N; k++)
        	        {
        	            if (k == i  ||  k == j)
        	                continue;
        		    if (hasContacted\[i\]\[k\]  &&  hasContacted\[k\]\[j\])
        	        	numIntermediaries\[i\]\[j\]++;
        	        }
        	        **numIntermediaries\[j\]\[i\] = numIntermediaries\[i\]\[j\];**
        	    }
        	}
        
        What is the time complexity of this algorithm? Why?
        
6.  1.  Here again is the non-member `reassign` function for Map from [Map.cpp](Map.cpp):
        
        void reassign(const Map& m, Map& result)
        {
              // Guard against the case that result is an alias for m (i.e., that
              // result is a reference to the same map that m refers to) by building
              // the answer in a local variable res.  When done, swap res with result;
              // the old value of result (now in res) will be destroyed when res is
              // destroyed.
        
            Map res;
        
            if (!m.empty())
            {
                KeyType prevKey;
                ValueType value0;
        
                  // Get pair 0, which must succeed since m is not empty
        
                m.get(0, prevKey, value0);
        
                  // For each pair i after pair 0, insert into res a pair with
                  // pair i-1's key and pair i's value.  (This loop executes 0 times
                  // if m has only one pair.)
        
                for (int i = 1; i < m.size(); i++)
                {
                    KeyType k;
                    ValueType v;
                    m.get(i, k, v);
                    res.insert(prevKey, v);
                    prevKey = k;
                }
        
                  // Insert a final pair with last pair's key and pair 0's value.
        
                res.insert(prevKey, value0);
            }
        
            result.swap(res);
        }
        
        Assume that `m` and the old value of `result` each have N elements. In terms of the number of linked list nodes visited during the execution of this function, what is its time complexity? Why?
        
    2.  Here is an implementation of a related member function. The call
        
        m.reassign();
        
        has the same effect as calling the non-member function above as `reassign(m, m);`. The implementation is
        
        void Map::reassign()
        {
            Node\* p = m\_head->m\_next;
            if (p != m\_head)
            {
                ValueType value0 = p->m\_value;
        	for ( ; p->m\_next != m\_head; p = p->m\_next)
        	    p->m\_value = p->m\_next->m\_value;
                p->m\_value = value0;
            }
        }
        
        Assume that `*this` has N elements. In terms of the number of linked list nodes visited during the execution of this function, what is its time complexity? Why? Is it the same, better, or worse, than the implementation in part a?
        
7.  The file [sorts.cpp](sorts.cpp) contains an almost complete program that creates a randomly ordered array, sorts it in a few ways, and reports on the elapsed times. Your job is to complete it and experiment with it.
    
    You can run the program as is to get some results for the STL sort algorithm. You won't get any result for insertion sort, because the insertion sort function right now doesn't do anything. That's one thing for you to write.
    
    The objects in the array might not be cheap to copy (it depends on your processor), which might make a sort that does a lot of moving objects around expensive. Your other task will be to create a vector of _pointers_ to the objects, sort the pointers using the same criterion as was used to sort the objects, and then make one pass through the vector to put the objects in the proper order.
    
    Your two tasks are thus:
    
    1.  Implement the `insertion_sort` function. (Code is on pp. 332-333 in the Carrano book, and also [here](bookcode.html).)
        
    2.  Implement the `compareStorePtr` function and the code in `sortUsingPtrs` to create and sort the array of pointers.
        
    
    The places to make modifications are indicated by `TODO:` comments. You should not have to make modifications anywhere else. (Our solution doesn't.)
    
    When your program is correct, build an optimized version of it to do some timing experiments. On cs32.seas.ucla.edu, build the executable and run it this way:
    
    	g32fast -o sorts sorts.cpp
    	./sorts
    
    (You don't have to know this, but this command omits some of the runtime error checking compiler options that our g32 command supplies, and it adds the -O2 compiler option that causes the compiler to spend more time optimizing the machine language translation of your code so that it will run faster when you execute it.)
    
    Under Xcode, select Product / Scheme / Edit Scheme.... In the left panel, select Run, then in the right panel, select the Info tab. In the Build Configuration dropdown, select Release. For Visual C++, it's [a little trickier](vcreleasemode.html).
    
    Try the program with about 10000 items. Depending on the speed of your processor, this number may be too large or small to get meaningful timings in a reasonable amount of time. Experiment. Once you get insertion sort working, observe the O(N2) behavior by sorting, say, 10000, 20000, and 40000 items.
    
    To further observe the performance behavior of the STL sort algorithm, try sorting, say, 100000, 200000, and 400000 items, or even ten times as many. Since this would make the insertion sort tests take a long time, skip them by setting the TEST\_INSERTION\_SORT constant at the top of sorts.cpp to false.
    
    Notice that if you run the program more than once, you may not get exactly the same timings each time. This is partly because of not getting the same sequence of random numbers each time, but also because of factors like caching by the operating system.
    

### Turn it in

By Monday, February 28, there will be a link on the class webpage that will enable you to turn in this homework. Turn in one zip file that contains your solutions to the homework problems. The zip file must contain eight files:

*   `Map.h`, a C++ header file with your definition and implementation of the class and function templates for problem 1.
*   `oddlist.cpp`, a C++ source file with your solution to problem 3a.
*   `oddvector.cpp`, a C++ source file with your solution to problem 3b.
*   `badlist.cpp`, a C++ source file with your solution to problem 3c.
*   `badvector.cpp`, a C++ source file with your solution to problem 3d.
*   `list.cpp`, a C++ source file with the implementation of the two-parameter overload of the `listAll` function for problem 4a.
*   `sorts.cpp`, a C++ source file with your solution to problem 7 (the entire file).
*   `hw.docx`, `hw.doc`, or `hw.txt`, a Word document or a text file with your solutions to problems 2, 3e, 4b, 5a, 5b, 6a, and 6b.