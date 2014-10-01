#ifndef _SDAL_H_
#define _SDAL_H_

#include <iostream>

namespace cop3530 {

    template <typename T>
    class SDAL {
    private:
        T* data_list;
        std::size_t count;
        std::size_t max_size;

        void check_size()
        {
            if ( count == max_size )
            {
                T *dtmp = data_list;
                std::size_t new_size = max_size*1.5;
                data_list = new T[new_size];
                for (int i=0; i != max_size; ++i)
                {
                    *(data_list+i) = *(dtmp+i);
                }
                max_size = new_size;
            }
            else if ( max_size >= 100 && count < max_size/2 )
            {
                T *dtmp = data_list;
                max_size = max_size * 0.5;
                data_list = new T[max_size];
                for (int i=0; i != max_size; ++i)
                {
                    *(data_list+i) = *(dtmp + i);
                }
            }
        }
    public:
    class SDAL_Iter //: public std::iterator<std::forward_iterator_tag, T>
     {
     public:
       // inheriting from std::iterator<std::forward_iterator_tag, T>
       // automagically sets up these typedefs...
       typedef std::size_t size_t;
       typedef T value_type;
       typedef std::ptrdiff_t difference_type;
       typedef T& reference;
       typedef T* pointer;
       typedef std::forward_iterator_tag iterator_category;

       // but not these typedefs...
       typedef SDAL_Iter self_type;
       typedef SDAL_Iter& self_reference;

     private:
       int here;
       T* data_list;

     public:
       explicit SDAL_Iter( int start = 0, T* data = NULL ) {
           here = start;
           data_list = data;
       }
       SDAL_Iter( const SDAL_Iter& src ) {
            here = src.here;
            data_list = src.data_list;
        }

       reference operator*() const {
           return *(data_list+here);}
       pointer operator->() const {
           return data_list+here;}

       self_reference operator=( const SDAL_Iter& src ){
           here = src.here;
           data_list = src.data_list;
           return *this;
        }

       self_reference operator++() {
            ++here;
            return *this;} // preincrement
       self_type operator++(int) {
            self_type results( *this );
            ++here;
            return results;
            } // postincrement

       bool operator==(const SDAL_Iter& rhs) const {
        return (data_list == rhs.data_list && here == rhs.here);}
       bool operator!=(const SDAL_Iter& rhs) const {
        return !(data_list == rhs.data_list && here == rhs.here);}
     }; // end SDAL_Iter
    class SDAL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
     {
     public:
       // inheriting from std::iterator<std::forward_iterator_tag, T>
       // automagically sets up these typedefs...
       typedef T value_type;
       typedef std::ptrdiff_t difference_type;
       typedef const T& reference;
       typedef const T* pointer;
       typedef std::forward_iterator_tag iterator_category;

       // but not these typedefs...
       typedef SDAL_Const_Iter self_type;
       typedef SDAL_Const_Iter& self_reference;

     private:
       int here;
       const T* data_list;

     public:
       explicit SDAL_Const_Iter( int start = 0, T* data = NULL ) {
           here = start;
           data_list = data;
       }
       SDAL_Const_Iter( const SDAL_Const_Iter& src ) {
            here = src.here;
            data_list = src.data_list;
            }

       reference operator*() const {
           return *(data_list+here);}
       pointer operator->() const {
           return data_list+here;}

       self_reference operator=( const SDAL_Const_Iter& src ){
           here = src.here;
           data_list = src.data_list;
           return *this;
           }

       self_reference operator++() {
            ++here;
            return *this;} // preincrement
       self_type operator++(int) {
            self_type results( *this );
            ++here;
            return results;
            } // postincrement

       bool operator==(const SDAL_Const_Iter& rhs) const {
        return ( data_list == rhs.data_list && here == rhs.here ); }
       bool operator!=(const SDAL_Const_Iter& rhs) const {
        return !( data_list == rhs.data_list && here == rhs.here );}
     };  // end SDAL_Const_Iter
    //--------------------------------------------------
    // types
    //--------------------------------------------------
    typedef std::size_t size_t;
    typedef T value_type;
    typedef SDAL_Iter iterator;
    typedef SDAL_Const_Iter const_iterator;
    iterator begin() { return SDAL_Iter( 0, data_list ); }
    iterator end() { return SDAL_Iter( size(), data_list ); }

    const_iterator begin() const { return SDAL_Const_Iter( 0, data_list ); }
    const_iterator end() const { return SDAL_Const_Iter( size(), data_list ); }
    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    SDAL(int size=50){
        count = 0;
        max_size = size;
        data_list = new T[size];
    }
    //--------------------------------------------------
    SDAL( const SDAL& src ) {
        *this = src;}

    //--------------------------------------------------
    ~SDAL() {
        delete[] data_list;
    }

    //--------------------------------------------------
    SDAL& operator=( const SDAL& src ) {
        if ( &src == this ) // check for self-assignment
            return *this;     // do nothing
        else
        {
            // safely dispose of this SDAL's contents
            clear();
            // populate this SDAL with copies of the other SDAL's contents
            max_size = src.max_size;
            count = src.count;
            data_list = new T[max_size];
            for (int i=0; i!=size(); ++i)
            {
                *(data_list+i) = *(src.data_list+i);
            }
            return *this;
        }
    }

    //--------------------------------------------------
    // member functions
    //--------------------------------------------------
    T& operator[](int i)
    {
        if ( i >= size() || i < 0 )
        {
            throw "Exception: Accessing Index Out of Bounds";
        }
        return data_list[i];
    }
    T const& operator[](int i) const
    {
        if ( i >= size() || i < 0 )
        {
            throw "Exception: Accessing Index Out of Bounds";
        }
        return data_list[i];
    }
    T replace( const T& element, int position ) {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Replacing Out of Bounds";
        }
        T data = *(data_list+position);
        *(data_list+position) = element;
        return data;
    }

    //--------------------------------------------------
    void insert( const T& element, int position ) {
        if ( position > size() || position < 0 )
        {
            throw "Exception: Inserting Out of Bounds";
        }
        ++count;
        check_size();
        T data = element;
        for (int i=position; i!=size(); ++i)
        {
            T tmp = *(data_list+i);
            *(data_list+i) = data;
            data = tmp;
        }
    }

    //--------------------------------------------------
    void push_front( const T& element ) {
        insert( element, 0 );
    }

    //--------------------------------------------------
    void push_back( const T& element ) {
        insert( element, size() );
    }

    //--------------------------------------------------
    T pop_front() {
        if ( size() == 0 )
        {
            throw "Exception: Popping from Empty List";
        }
        return remove( 0 );
    }

    //--------------------------------------------------
    T pop_back() {
        if ( size() == 0 )
        {
            throw "Exception: Popping from Empty List";
        }
        return remove( size() - 1 );
    }

    //--------------------------------------------------
    T remove( int position ) {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Removing Out of Bounds";
        }
        T data = *(data_list+position);
        for (int i=position; i!=size()-1; ++i)
        {
            *(data_list+i) = *(data_list+i+1);
        }
        --count;
        check_size();
        return data;
    }

    //--------------------------------------------------
    T item_at( int position ) const {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Accessing Index Out of Bounds";
        }
        return *(data_list+position);
    }

    //--------------------------------------------------
    bool is_empty() const {
        return size() == 0;}

    //--------------------------------------------------
    size_t size() const {
        return count;
    }

    //--------------------------------------------------
    void clear() {
        count = 0;
        delete[] data_list;
        if (max_size >= 100)
            max_size=50;
        data_list = new T[max_size];
    }

    //--------------------------------------------------
    bool contains( const T& element,
                   bool equals( const T& a, const T& b  ) ) const
    {
        for ( int i=0; i != size(); ++i )
        {
            if ( equals( *(data_list+i), element ) )
            {
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------
    std::ostream& print( std::ostream& out ) const {
        if (size() == 0)
        {
            out << "<empty list>";
        }
        else
        {
            out << '[';
            for ( int i=0; i != size(); ++i )
            {
                out << *(data_list+i);
                if ( i+1 != size() )
                    out << ", ";
            }
            out << ']';
        }
        return out;
    }
}; //end class SDAL
} // end namespace cop3530
#endif // _SDAL_H_
