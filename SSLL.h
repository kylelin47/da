#ifndef _SSLL_H_
#define _SSLL_H_

// SSLL.H
//
// Singly-linked list (non-polymorphic)
//
// by Dave Small
// for COP 3530
// 201409.16 - created

#include <iostream>

namespace cop3530 {

    template <typename T>
    class SSLL {
    private:
        struct Node {
            Node *next;
            T data;
            Node() : next(NULL)
            {
            }
            ~Node(){
                next = NULL;};
        }; // end struct Node
        Node *head;

    public:
    class SSLL_Iter //: public std::iterator<std::forward_iterator_tag, T>
     {
     public:
       // inheriting from std::iterator<std::forward_iterator_tag, T>
       // automagically sets up these typedefs...
       typedef T value_type;
       typedef std::ptrdiff_t difference_type;
       typedef T& reference;
       typedef T* pointer;
       typedef std::forward_iterator_tag iterator_category;

       // but not these typedefs...
       typedef SSLL_Iter self_type;
       typedef SSLL_Iter& self_reference;

     private:
       Node* here;

     public:
       explicit SSLL_Iter( Node* start = NULL ) : here( start ) {}
       SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {}

       reference operator*() const {
           return here->data;}
       pointer operator->() const {
           return &(here->data);}

       self_reference operator=( const SSLL_Iter& src ){
       here = src.here;
       return *this;}

       self_reference operator++() {
            here = here->next;
            return *this;} // preincrement
       self_type operator++(int) {
            self_type results( *this );
            here = here->next;
            return results;
            } // postincrement

       bool operator==(const SSLL_Iter& rhs) const {
        return here == rhs.here;}
       bool operator!=(const SSLL_Iter& rhs) const {
        return !(here == rhs.here);}
     }; // end SSLL_Iter
    class SSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
       typedef SSLL_Const_Iter self_type;
       typedef SSLL_Const_Iter& self_reference;

     private:
       const Node* here;

     public:
       explicit SSLL_Const_Iter( Node* start = NULL ) : here( start ) {}
       SSLL_Const_Iter( const SSLL_Const_Iter& src ) : here( src.here ) {}

       reference operator*() const { return here->data; }
       pointer operator->() const { return &(here->data); }

       self_reference operator=( const SSLL_Const_Iter& src ) {
       here = src.here;
       return *this;}

       self_reference operator++() {
            here = here->next;
            return *this;} // preincrement
       self_type operator++(int) {
            self_type results( *this );
            here = here->next;
            return results;
            } // postincrement

       bool operator==(const SSLL_Const_Iter& rhs) const {
            return here == rhs.here; }
       bool operator!=(const SSLL_Const_Iter& rhs) const {
            return !(here == rhs.here); }
     }; // end SSLL_Const_Iter
    //--------------------------------------------------
    // types
    //--------------------------------------------------
    typedef std::size_t size_t;
    typedef T value_type;
    typedef SSLL_Iter iterator;
    typedef SSLL_Const_Iter const_iterator;
    iterator begin() { return SSLL_Iter( head ); }
    iterator end() { return SSLL_Iter(); }

    const_iterator begin() const { return SSLL_Const_Iter( head ); }
    const_iterator end() const { return SSLL_Const_Iter(); }
    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    SSLL() {
        head = NULL;
    }

    //--------------------------------------------------
    SSLL( const SSLL& src ) {
        head = NULL;
        *this = src;}

    //--------------------------------------------------
    ~SSLL() {
      // safely dispose of this SSLL's contents
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
    SSLL& operator=( const SSLL& src ) {
        if ( &src == this ) // check for self-assignment
            return *this;     // do nothing
        else
        {
            // safely dispose of this SSLL's contents
            clear();
            // populate this SSLL with copies of the other SSLL's contents
            if (src.head == NULL)
            {
                head = NULL;
                return *this;
            }
            else
            {
                Node *current = src.head;
                Node *tmp = NULL;
                while (current != NULL)
                {
                    Node *newNode = new Node;
                    newNode->data = current->data;
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
                return *this;
            }

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
        for (int j=0; j<i; ++j)
        {
            current = current->next;
        }
        return current->data;
    }
    T const& operator[](int i) const
    {
        if ( i >= size() || i < 0 )
        {
            throw "Exception: Accessing Index Out of Bounds";
        }
        Node *current = head;
        for (int j=0; j<i; ++j)
        {
            current = current->next;
        }
        return current->data;
    }
    T replace( const T& element, int position ) {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Replacing Out of Bounds";
        }
        Node *newNode = new Node;
        newNode->data = element;
        if (position == 0)
        {
            newNode->next = head->next;
            T data = head->data;
            delete head;
            head = newNode;
            return data;
        }
        else
        {
            Node *current = head;
            Node *prev = NULL;
            for (int i=0; i<position; ++i)
            {
                prev = current;
                current = current->next;
            }
            prev->next = newNode;
            newNode->next = current->next;
            T data = current->data;
            delete current;
            return data;
        }
    }

    //--------------------------------------------------
    void insert( const T& element, int position ) {
        if ( position > size() || position < 0 )
        {
            throw "Exception: Inserting Out of Bounds";
        }
        if (position == 0)
        {
            push_front(element);
        }
        else
        {
            Node *newNode = new Node;
            newNode->data = element;
            Node *current = head;
            for (int i=0; i < position-1;++i)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    //--------------------------------------------------
    void push_front( const T& element ) {
        Node *newNode = new Node;
        newNode->data = element;
        newNode->next = head;
        head = newNode;
    }

    //--------------------------------------------------
    void push_back( const T& element ) {
        Node *newNode = new Node;
        newNode->data = element;
        newNode->next = NULL;
        if ( head == NULL )
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    //--------------------------------------------------
    T pop_front() {
        if (head == NULL)
        {
            throw "Exception: Popping from Empty List";
        }
        T data = head->data;
        Node *tmp = head->next;
        delete head;
        head = tmp;
        return data;
    }

    //--------------------------------------------------
    T pop_back() {
        if (head == NULL)
            throw "Exception: Popping from Empty List";
        Node *current = head;
        Node *prev = NULL;
        while (current->next != NULL)
        {
            prev = current;
            current = current->next;
        }
        if ( prev != NULL )
            prev->next = NULL;
        else
            head = NULL;
        T data = current->data;
        delete current;
        return data;
    }

    //--------------------------------------------------
    T remove( int position ) {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Removing Out of Bounds";
        }
        if ( position == 0 )
        {
            T data = head->data;
            Node *tmp = head->next;
            head->next = NULL;
            head = tmp;
            return data;
        }
        Node *current = head;
        Node *prev = NULL;
        for (int i=0; i<position; ++i)
        {
            prev = current;
            current = current->next;
        }
        if ( prev != NULL )
            prev->next = current->next;
        T data = current->data;
        delete current;
        return data;
    }

    //--------------------------------------------------
    T item_at( int position ) const {
        if ( position >= size() || position < 0 )
        {
            throw "Exception: Accessing Index Out of Bounds";
        }
        Node *current = head;
        for (int i=0; i<position; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    //--------------------------------------------------
    bool is_empty() const {
        return head == NULL;}

    //--------------------------------------------------
    size_t size() const {
        Node *current = head;
        size_t count = 0;
        while (current != NULL)
        {
            current = current->next;
            ++count;
        }
        return count;
    }

    //--------------------------------------------------
    void clear() {
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
    bool contains( const T& element,
                   bool equals( const T& a, const T& b  ) ) const
    {
        Node *current = head;
        while (current != NULL)
        {
            if ( equals( current->data, element ) )
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    //--------------------------------------------------
    std::ostream& print( std::ostream& out ) const {
        if (head == NULL)
        {
            out << "<empty list>";
        }
        else
        {
            out << '[';
            Node *current = head;
            while (current != NULL)
            {
                out << current->data;
                if (current->next != NULL)
                    out << ", ";
                current = current->next;
            }
            out << ']';
        }
        return out;
    }
}; //end class SSLL
} // end namespace cop3530
#endif // _SSLL_H_
