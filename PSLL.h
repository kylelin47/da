#ifndef _PSLL_H_
#define _PSLL_H_

// PSLL.H
#include <iostream>

namespace cop3530 {

    template <typename T>
    class PSLL {
    private:
        struct Node {
            Node *next;
            T data;
            Node() : next(NULL)
            {
            }
            ~Node(){
                next = NULL;
            };
        }; // end struct Node
        Node *head;
        Node *free;
        std::size_t pool_size;
        std::size_t list_size;
        void add_pool( Node *n )
        {
            Node *tmp = free;
            free = n;
            free->next = tmp;
            --list_size;
            ++pool_size;
            if (list_size >= 100 && pool_size > list_size/2)
            {
                deallocate_pool();
            }
        }
        Node *make_node()
        {
            Node *newNode;
            ++list_size;
            if ( free != NULL )
            {
                --pool_size;
                newNode = free;
                newNode->next = NULL;
                free = free->next;
                if (list_size >= 100 && pool_size > list_size/2)
                {
                    deallocate_pool();
                }
            }
            else
            {
                newNode = new Node;
            }
            return newNode;
        }
        void deallocate_pool()
        {
            int half_size = pool_size/2;
            for (int i=0; i != half_size; ++i)
            {
                Node *current = free;
                free = free->next;
                delete current;
                --pool_size;
            }
        }

    public:
    class PSLL_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
       typedef PSLL_Iter self_type;
       typedef PSLL_Iter& self_reference;

     private:
       Node* here;

     public:
       explicit PSLL_Iter( Node* start = NULL ) : here( start ) {}
       PSLL_Iter( const PSLL_Iter& src ) : here( src.here ) {}

       reference operator*() const {
           return here->data;}
       pointer operator->() const {
           return &(here->data);}

       self_reference operator=( const PSLL_Iter& src ){
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

       bool operator==(const PSLL_Iter& rhs) const {
        return here == rhs.here;}
       bool operator!=(const PSLL_Iter& rhs) const {
        return !(here == rhs.here);}
     }; // end PSLL_Iter
    class PSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
       typedef PSLL_Const_Iter self_type;
       typedef PSLL_Const_Iter& self_reference;

     private:
       const Node* here;

     public:
       explicit PSLL_Const_Iter( Node* start = NULL ) : here( start ) {}
       PSLL_Const_Iter( const PSLL_Const_Iter& src ) : here( src.here ) {}

       reference operator*() const { return here->data; }
       pointer operator->() const { return &(here->data); }

       self_reference operator=( const PSLL_Const_Iter& src ) {
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

       bool operator==(const PSLL_Const_Iter& rhs) const {
            return here == rhs.here; }
       bool operator!=(const PSLL_Const_Iter& rhs) const {
            return !(here == rhs.here); }
     }; // end PSLL_Const_Iter
    //--------------------------------------------------
    // types
    //--------------------------------------------------
    typedef T value_type;
    typedef PSLL_Iter iterator;
    typedef PSLL_Const_Iter const_iterator;
    iterator begin() { return PSLL_Iter( head ); }
    iterator end() { return PSLL_Iter(); }

    const_iterator begin() const { return PSLL_Const_Iter( head ); }
    const_iterator end() const { return PSLL_Const_Iter(); }
    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    PSLL() {
        head = NULL;
        free = NULL;
        pool_size = 0;
        list_size = 0;
    }

    //--------------------------------------------------
    PSLL( const PSLL& src ) {
        head = NULL;
        free = NULL;
        pool_size = 0;
        list_size = 0;
        *this = src;}

    //--------------------------------------------------
    ~PSLL() {
      // safely dispose of this PSLL's contents
        Node *current = head;
        head = NULL;
        while (current != NULL)
        {
            Node *tmp = current->next;
            delete current;
            current = tmp;
        }
        current = free;
        free = NULL;
        while (current != NULL)
        {
            Node *tmp = current->next;
            delete current;
            current = tmp;
        }

    }

    //--------------------------------------------------
    PSLL& operator=( const PSLL& src ) {
        if ( &src == this ) // check for self-assignment
            return *this;     // do nothing
        else
        {
            // safely dispose of this PSLL's contents
            clear();
            // populate this PSLL with copies of the other PSLL's contents
            if (src.head == NULL)
            {
                head = NULL;
                return *this;
            }
            else
            {
                head = NULL;
                list_size = src.list_size;
                Node *current = src.head;
                Node *tmp = NULL;
                while (current != NULL)
                {
                    Node *newNode = make_node();
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
        Node *newNode = make_node();
        newNode->data = element;
        if (position == 0)
        {
            newNode->next = head->next;
            T data = head->data;
            add_pool( head );
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
            add_pool( current );
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
            Node *newNode = make_node();
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
        Node *newNode = make_node();
        newNode->data = element;
        newNode->next = head;
        head = newNode;
    }

    //--------------------------------------------------
    void push_back( const T& element ) {
        Node *newNode = make_node();
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

        add_pool( head );
        head = tmp;
        return data;
    }

    //--------------------------------------------------
    T pop_back() {
        if (head == NULL)
        {
            throw "Exception: Popping from Empty List";
        }
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
        add_pool( current );
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
            add_pool( head );
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
        add_pool( current );
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
        return list_size;
    }

    //--------------------------------------------------
    void clear() {
        Node *current = head;
        head = NULL;
        while ( current != NULL )
        {
            Node *tmp = current->next;
            add_pool( current );
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
}; //end class PSLL

} // end namespace cop3530
#endif // _PSLL_H_
