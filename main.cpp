#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "CDAL.h"
bool same_char( const char& a, const char& b ) { // argument for contains()
  return (a == b);
}
void in_list( const cop3530::CDAL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
  list.print( out );
  out << std::endl;
}
TEST_CASE( "List can be created,,modified, and indexed using all functions", "[list]" ) {

    cop3530::CDAL<char> l;

    REQUIRE( l.size() == 0 );
    REQUIRE( l.is_empty() == true );

    SECTION( "Inserting/Removing/Replacing into the List, Retrieving from the List, Printing" ) {
        l.print( std::cout ); //<empty list>
        std::cout << std::endl;
        l.insert( 'D', 0 );
        l.insert( 'B', 0 );
        l.insert( 'C', 1 );
        REQUIRE ( l.size() == 3 );
        REQUIRE ( l.item_at(1) == 'C' );
        char temp = l[2];
        REQUIRE ( temp == 'D' );
        in_list( l, 'b', std::cout ); // b is not in
        in_list( l, 'B', std::cout ); // B is in [B, C, D]
        l.remove( 1 );
        l.replace( 'X', 1 );    //[B, X]
        l.insert( 'Y', 2 );
        REQUIRE ( l.item_at(1) == 'X' );
        REQUIRE ( l.item_at(2) == 'Y' );
    }
    SECTION( "push_back, push_front, pop_front, and pop_back, clear, equals assignment" ) {
        l.push_back( 'Z' );
        l.push_front( 'A' );
        REQUIRE( l.size() == 2 );
        REQUIRE( l.pop_front() == 'A' );
        REQUIRE( l.pop_back() == 'Z' );
        REQUIRE( l.size() == 0 );
        l.push_back( 'E' );
        l.push_front( 'F' );
        REQUIRE( l.pop_front() == 'F' );
        REQUIRE( l.pop_back() == 'E' );
        for ( int i = 0; i != 25; ++i )
        {
            l.insert( 'A', i );
        }
        cop3530::CDAL<char> l2;
        l2 = l;
        l2.print( std::cout );
        std::cout << std::endl;
        l.clear();
        REQUIRE ( l.size() == 0 );

    }
    SECTION( "Iterators" ) {
        l.push_front( 'Z' );
        l.push_front( 'Y' );
        l.push_front( 'X' );
        const cop3530::CDAL<char> const_list = l;
        cop3530::CDAL<char>::const_iterator const_iter = const_list.begin();
        std::cout << *const_iter;        // prints an X
        const_iter++;
        std::cout << *const_iter;// prints a Y
        ++const_iter;
        std::cout << *const_iter;// prints a Z
        std::cout << std::endl;

        cop3530::CDAL<char>::iterator iter = l.begin();
        std::cout << *iter;        // prints an X
        iter++;
        std::cout << *iter;// prints a Y
        ++iter;
        std::cout << *iter;// prints a Z
        *iter = 'A';
        std::cout << *iter; //prints an A
        std::cout << std::endl;
        cop3530::CDAL<char>::iterator iter2 = iter;
        REQUIRE ( (iter2 == iter) == true );
        ++iter;
        REQUIRE ( (iter2 == iter) == false );
        for (iter = l.begin(); iter != l.end(); ++iter )
        {
            std::cout << *iter; //X,Y,A
        }
        std::cout << std::endl;
    }
    SECTION( "Operating Past the Bounds" ) {
        try
        {
            l.pop_front();
        }
        catch ( const char* msg )
        {
            std::cerr << msg << std::endl;
        }
        try
        {
            l.insert( 'A', 1 );
        }
        catch ( const char* msg )
        {
            std::cerr << msg << std::endl;
        }
        l.push_front( 'A' );
        l.push_back( 'B' );
        try
        {
            l.remove( 3 );
        }
        catch ( const char* msg )
        {
            std::cerr << msg << std::endl;
        }
        try
        {
            l.replace( 'A', 3 );
        }
        catch ( const char* msg )
        {
            std::cerr << msg << std::endl;
        }
        try
        {
            l.remove( -1 );
        }
        catch ( const char* msg )
        {
            std::cerr << msg << std::endl;
        }
    }

}

TEST_CASE( "List can resize to accommodate data", "[list]" ) {
    cop3530::CDAL<int> l;
    SECTION( "List of 200 Sequential Integers, Combining Pushes and Inserts" )
    {
        for (int i=0; i!=200; ++i)
        {
            l.push_back(i);
        }
        REQUIRE ( l.size() == 200 );
        cop3530::CDAL<int>::iterator iter;
        int i = 0;
        for (iter = l.begin(); iter != l.end(); ++iter )
        {
            int value = *iter;
            REQUIRE( value == i );
            ++i;
        }
        l.insert( 5, 102 );
        REQUIRE ( l.item_at( 102 ) == 5 );
        int x = l[102];
        REQUIRE ( x == 5 );
        l.remove(102);
        for (int i=0; i!=75;++i)
        {
            l.pop_back();
        }
        l.remove(120);
        l.print( std::cout );
        std::cout << std::endl;
        REQUIRE ( l.size() == 124 );
        for (int i=0; i!=75;++i)
        {
            l.push_front(0);
        }
        l.print( std::cout );
        std::cout << std::endl;
        REQUIRE ( l.size() == 199 );
    }
}
