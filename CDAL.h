#ifndef _CDAL_H_
#define _CDAL_H_

#include <iostream>

namespace cop3530 {

    template <typename T>
    class CDAL {
    private:
        struct Node {
            Node *next;
            T *data_list;
            std::size_t size;
            Node() : next(NULL), size(0)
            {
                data_list = new T[50];
            }
            ~Node(){
                //delete[] data_list;
                next = NULL;}
            bool insert( const T& element, int position )
            {
                if ( size < 50 )
                {
                    ++size;
                    T data = element;
                    for (int i=position; i!=size; ++i)
                    {
                        T tmp = *(data_list+i);
                        *(data_list+i) = data;
                        data = tmp;
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            T remove( int position )
            {
                if ( size != 0 )
                {
                    --size;
                }
                T data = *(data_list+position);
                for (int i=position; i<size; ++i)
                {
                    *(data_list+i) = *(data_list+i+1);
                }
                return data;
            }
            T replace( const T& element, int position ) {
                T data = *(data_list+position);
                *(data_list+position) = element;
                return data;
            }
            bool contains( const T& element, bool equals( const T& a, const T& b  ) ) const
            {
                for ( int i=0; i != size; ++i )
                {
                    if ( equals( *(data_list+i), element ) )
                    {
                        return true;
                    }
                }
                return false;
            }
    }; // end struct Node
    void check_size()
    {
        int usedNodes = length/50;
        if ( length%50 != 0 || usedNodes == 0 )
            ++usedNodes;
        int totalNodes = max_length/50;
        int halfTotal = totalNodes/2 + totalNodes%2;

        if ( usedNodes < halfTotal )
        {
            Node *current = head;
            for (int i=1; i != usedNodes; ++i)
            {
                current = current->next;
            }
            Node *tmp = current->next;
            current->next = NULL;
            current = tmp;
            while ( current != NULL )
            {
                Node *tmp = current->next;
                delete current;
                current = tmp;
            }
        }
    }
    void clear_all() {
        Node *current = head;
        while ( current != NULL )
        {
            Node *tmp = current->next;
            delete current;
            current = tmp;
        }
        head = NULL;
        length = 0;
        max_length=0;
    }
        Node *head;
        std::size_t length;
        std::size_t max_length;

    public:
    class CDAL_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
       typedef CDAL_Iter self_type;
       typedef CDAL_Iter& self_reference;

     private:
       Node *here;
       int position;

     public:
       explicit CDAL_Iter( Node* start = NULL, int pos = 0 ) : here( start ), position( pos ) {}
       CDAL_Iter( const CDAL_Iter& src ) : here( src.here ), position( src.position ) {}

       reference operator*() const {
           return *(here->data_list + position);}
       pointer operator->() const {
           return here->data_list+position;}

       self_reference operator=( const CDAL_Iter& src ){
           here = src.here;
           position = src.position;
           return *this;
        }

       self_reference operator++() {
            ++position;
            if ( position == 50 )
            {
                here = here->next;
                position = 0;
            }
            return *this;} // preincrement
       self_type operator++(int) {
            self_type results( *this );
            ++position;
            if ( position == 50 )
            {
                here = here->next;
                position = 0;
            }
            return results;
            } // postincrement

       bool operator==(const CDAL_Iter& rhs) const {
        return (here == rhs.here && position == rhs.position);}
       bool operator!=(const CDAL_Iter& rhs) const {
        return !((here == rhs.here && position == rhs.position));}
     }; // end CDAL_Iter
    class CDAL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
     {
     public:
       // inheriting from std::iterator<std::forward_iterator_tag, T>
       // automagically sets up these typedefs...
       typedef std::size_t size_t;
       typedef T value_type;
       typedef std::ptrdiff_t difference_type;
       typedef const T& reference;
       typedef const T* pointer;
       typedef std::forward_iterator_tag iterator_category;

       // but not these typedefs...
       typedef CDAL_Const_Iter self_type;
       typedef CDAL_Const_Iter& self_reference;

     private:
       Node *here;
       int position;

     public:
       explicit CDAL_Const_Iter( Node* start = NULL, int pos = 0 ) : here( start ), position( pos ) {}
       CDAL_Const_Iter( const CDAL_Const_Iter& src ) : here( src.here ), position( src.position ) {}

       reference operator*() const {
           return *(here->data_list + position);}
       pointer operator->() const {
           return here->data_list+position;}

       self_reference operator=( const CDAL_Const_Iter& src ){
           here = src.here;
           position = src.position;
           return *this;
        }

       self_reference operator++() {
            ++position;
            if ( position == 50 )
            {
                here = here->next;
                position = 0;
            }
            return *this;} // preincrement
       self_type operator++(int) {
            self_type results( *this );
            ++position;
            if ( position == 50 )
            {
                here = here->next;
                position = 0;
            }
            return results;
            } // postincrement

       bool operator==(const CDAL_Const_Iter& rhs) const {
        return (here == rhs.here && position == rhs.position);}
       bool operator!=(const CDAL_Const_Iter& rhs) const {
        return !((here == rhs.here && position == rhs.position));}
     };  // end CDAL_Const_Iter
    //--------------------------------------------------
    // types
    //--------------------------------------------------
    typedef std::size_t size_t;
    typedef T value_type;
    typedef CDAL_Iter iterator;
    typedef CDAL_Const_Iter const_iterator;
    iterator begin() { return CDAL_Iter( head, 0 ); }
    iterator end() {
        Node *current = head;
        while ( current->next != NULL )
            current = current->next;
        return current->size == 50 ? CDAL_Iter( NULL, 0 ) : CDAL_Iter( current, current->size ); }

    const_iterator begin() const { return CDAL_Const_Iter( head, 0 ); }
    const_iterator end() const {
        Node *current = head;
        while ( current->next != NULL )
            current = current->next;
        return current->size == 50 ? CDAL_Const_Iter( NULL, 0 ) : CDAL_Const_Iter( current, current->size ); }
    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    CDAL(){
        head = new Node;
        length = 0;
        max_length = 50;
    }
    //--------------------------------------------------
    CDAL( const CDAL& src ) {
        head = NULL;
        *this = src;}

    //--------------------------------------------------
    ~CDAL() {
        Node *current = head;
        head = NULL;
        while (current != NULL)
        {
            Node *tmp = current->next;
            delete current;
            current = tmp;
        }
    }

    //--------------------------------------------------
    CDAL& operator=( const CDAL& src ) {
        if ( &src == this ) // check for self-assignment
            return *this;     // do nothing
        else
        {
            // safely dispose of this CDAL's contents
            clear_all();
            // populate this CDAL with copies of the other CDAL's contents
            Node *current = src.head;
            Node *tmp = NULL;
            while (current != NULL)
            {
                Node *newNode = new Node;
                for ( int i=0; i != current->size; ++i )
                {
                    *(newNode->data_list+i) = *(current->data_list+i);
                }
                newNode->size = current->size;
                if (head == NULL)
                {
                    head = newNode;
                    tmp = head;
                }
                else
                {
                    tmp->next = newNode;
                    tmp = newNode;
                }
                current = current->next;
            }
            length = src.length;
            max_length = src.max_length;
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
        Node *current = head;
        for (int j=0; j!= i/50; ++j)
        {
            current = current->next;
        }
        return *(current->data_list + i%50);
    }
    T const& operator[](int i) const
    {
        if ( i >= size() || i < 0 )
        {
            throw "Exception: Accessing Index Out of Bounds";
        }
        Node *current = head;
        for (int j=0; j!= i/50; ++j)
        {
            current = current->next;
        }
        return *(current->data_list + i%50);
    }
    T replace( const T& element, int position ) {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Replacing Out of Bounds";
        }
        Node *current = head;
        for (int i=0; i != position/50; ++i)
        {
            current = current->next;
        }
        return current->replace( element, position%50 );
    }

    //--------------------------------------------------
    void insert( const T& element, int position ) {
        if ( position > size() || position < 0 )
        {
            throw "Exception: Inserting Out of Bounds";
        }
        Node *current = head;
        ++length;
        for (int i=0; i != position/50; ++i)
        {
            current = current->next;
        }
        if ( !( current->insert( element, position%50 ) ) )
        {
            if ( length > max_length )
            {
                Node *newNode = new Node;
                max_length += 50;
                Node *iter = head;
                while ( iter->next != NULL )
                {
                    iter = iter->next;
                }
                iter->next = newNode;
            }
            T data = current->remove(49);
            current->insert( element, position%50 );
            while ( current->next != NULL )
            {
                current = current->next;
                if ( current->size == 50 )
                {
                    T tmp = current->remove(49);
                    current->insert( data, 0 );
                    data = tmp;
                }
                else
                {
                    current->insert( data, 0 );
                    break;
                }
            }
        }
        check_size();
    }

    //--------------------------------------------------
    void push_front( const T& element ) {
        insert( element, 0 );
    }

    //--------------------------------------------------
    void push_back( const T& element ) {
        Node *current = head;
        while ( current->next != NULL )
        {
            current = current->next;
        }
        if ( !( current->insert( element, current->size ) ) )
        {
            Node *newNode = new Node;
            max_length += 50;
            current->next = newNode;
            newNode->insert( element, 0 );
        }
        ++length;
        check_size();
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
        Node *current = head;
        --length;
        for (int i=0; i != position/50; ++i)
        {
            current = current->next;
        }
        T ret_data = current->remove( position%50 );
        Node *prev = NULL;
        T data;
        while ( current->next != NULL )
        {
            prev = current;
            current = current->next;
            if ( current->size != 0 )
            {
                data = current->remove(0);
                prev->insert( data, 49 );
            }
            else
            {
                break;
            }
        }
        check_size();
        return ret_data;
    }

    //--------------------------------------------------
    T item_at( int position ) const {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Accessing Index Out of Bounds";
        }
        Node *current = head;
        for (int i=0; i!= position/50; ++i)
        {
            current = current->next;
        }
        return *(current->data_list + position%50);
    }

    //--------------------------------------------------
    bool is_empty() const {
        return size() == 0;}

    //--------------------------------------------------
    size_t size() const {
        return length;
    }

    //--------------------------------------------------
    void clear() {
        Node *current = head;
        while ( current != NULL )
        {
            Node *tmp = current->next;
            delete current;
            current = tmp;
        }
        head = new Node;
        length = 0;
        max_length=50;
    }

    //--------------------------------------------------
    bool contains( const T& element,
                   bool equals( const T& a, const T& b  ) ) const
    {
        Node *current = head;
        while (current != NULL)
        {
            if ( current->contains( element, equals ) )
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    //--------------------------------------------------
    std::ostream& print( std::ostream& out ) const {
        int pos = 0;
        if (size() == 0)
        {
            out << "<empty list>";
        }
        else
        {
            out << '[';
            Node *current = head;
            while ( current != NULL )
            {
                for ( int i=0; i!=current->size; ++i )
                {
                    out << *(current->data_list+i);
                    if ( pos != size() - 1 )
                        out << ", ";
                    ++pos;
                }
                current = current->next;
            }
            out << ']';
        }
        return out;
    }
}; //end class CDAL
} // end namespace cop3530
#endif // _CDAL_H_
