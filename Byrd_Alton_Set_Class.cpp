//Program Name: Set Class
//Programmer: Alton byrd
//Date: 11/19/2024
//Desc: This class makes a list of numbers but doesnt allow repeates and uses the set class to do so.
#include <cstdlib>      
#include <algorithm>   
#include <cassert>      
#include <iostream>  
using namespace std;

namespace doe_john_1234
{
    class set
    { 
    public:        
        // typedefs and member constants
        typedef int value_type;
        typedef size_t size_type;
        static const size_type CAPACITY = 30;
        
        // constructor
        set( ) { used = 0; }         
        
        // member functions
        void add_element(const value_type& entry);
        void operator +=(const set& addend);        
        bool contains(const value_type& entry) const;
        void remove(const value_type& target);
        void print();
        
        size_type size( ) const {return used;}
        
    private:
        value_type data[CAPACITY]; 
        size_type used;            
    };

    // NON-MEMBER FUNCTIONS
    set operator +(const set& s1, const set& s2);
}

// ****************************************************************************
//                 C L A S S   I M P L E M E N T A T I O N
// ****************************************************************************

namespace doe_john_1234
{
    const set::size_type set::CAPACITY;
    
    // ################### M E M B E R   F U N C T I O N S ####################
    
	// ************************************************************************
	// remove: removes all occurrences of target from the set. 
	// ************************************************************************
	void set::remove(const value_type& target)
	{
		
		int c = 0;
		while (c < used && data[c] != target)
		c++;
		if (c == used)
			cout << target << "was not found in the set\n";
		else
		{
		data[c] = data[used - 1];
		used--;
		}
	}

	// ************************************************************************
	// print: displays final array
	// ************************************************************************
	void set::print()
	{
		for (int i = 0; i < used; i++)
		cout << data[i] << " ";
		cout << endl;
	}
	
	// ************************************************************************
	// contains: removes the first occurrence of target from the set. 
	// ************************************************************************
	bool set::contains(const value_type& entry) const
	{
		int c = 0;
		while(c < used && data[c] != entry)
			c++;
			if (data[c] != entry)
			{
				return false;	
			}
			else
				return true;

	
	}
	// ************************************************************************
	// add_element: inserts entry into the set. 
	// ************************************************************************
    void set::add_element(const value_type& entry)
    {
	    if ((contains(entry) == true))
	    {
	   	cout << entry <<" is already in list \n";
		}
		else if ((contains(entry) == false))
		{
			assert(size( ) < CAPACITY);
			data[used] = entry;
			used++;
		}
	}
	
	// ************************************************************************
	// operator +=: overloads the += operator for the set class. 
	// ************************************************************************
    void set::operator +=(const set& addend)
    {	
		assert(size() + addend.size() <= CAPACITY);
		for (int i = 0; i < addend.used; ++i) 
		{
            int ii;
            for (ii = 0; ii < used; ++ii) 
			{
                if (data[ii] == addend.data[i]) 
				{ii = used;}
            }
            if (ii == used) 
			{
                data[used++] = addend.data[i];
            }
        }
    }

    // ############### N O N - M E M B E R   F U N C T I O N S ################
	
	// ************************************************************************
	// operator +: overloads the + operator for the set class. 
	// ************************************************************************
	set operator +(const set& s1, const set& s2)
    {
        set answer;
		
        assert(s1.size( ) + s2.size( ) <= set::CAPACITY);

        answer += s1; 
        answer += s2;
        return answer;
    }
}
using namespace doe_john_1234;
int main( )
{	
	system("color f0");
	set set1;
	set1.add_element(5);
	set1.add_element(3);
	set1.add_element(5);
	set1.add_element(4);
	set1.add_element(3);
	set1.add_element(1);
	set1.add_element(7);
	
	set set2;
	set2.add_element(7);
	set2.add_element(3);
	set2.add_element(6);
	set2.add_element(15);
	set2.add_element(30);
	set2.add_element(30);
	set2.remove(15);
	
	set1 += set2;
	
	set2.add_element(12);
	set2.add_element(18);	
	
	set set3;
	set3 = set1 + set2;	
	set3.remove(3);

	cout << "\nSet 3 contains the following elements: \n";
	set3.print();
	cout << endl;
	
	system("pause");
	
    return EXIT_SUCCESS;  
}
