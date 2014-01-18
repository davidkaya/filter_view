#ifndef filter_view_hpp
#define filter_view_hpp
#include <iterator>

using namespace std;

/**
 * @brief Filter view on container
 * @tparam Container type
 * @tparam Predicate
 */
template <class CONTAINER, class PREDICATE>
class filter_view{
    const CONTAINER& cont;
    PREDICATE pred;

public:
    typedef typename CONTAINER::value_type value_type;
    typedef CONTAINER container_type;
    typedef PREDICATE predicate_type;
    typedef allocator<typename CONTAINER::value_type> allocator_type;
    
    /**
     * @brief The const_iterator class
     */
    class const_iterator:public iterator<forward_iterator_tag, value_type>{
    public:
        typedef typename filter_view::value_type value_type;
        typedef value_type& reference;
        typedef value_type* pointer;
        typedef ptrdiff_t difference_type;
        typedef forward_iterator_tag iterator_category;

        const_iterator ():cont(NULL){}
        /**
         * @brief Copy constructor
         * @param ptr - iterator
         */
        const_iterator (const const_iterator& ptr){
            this->ptr_=ptr.ptr_;
            this->pred=ptr.pred;
            this->cont=ptr.cont;
        }
        /**
         * @brief operator =
         * @param ptr - iterator
         * @return reference to const_iterator
         */
        const_iterator& operator=(const const_iterator& ptr){
            this->ptr_=ptr.ptr_;
            this->pred=ptr.pred;
            this->cont=ptr.cont;
            return *this;
        }
        /**
         * @brief operator == compares two iterators
         * @param ptr - iterator
         * @return true if same, false if not
         */
        bool operator==(const const_iterator& ptr) const { return ptr_ == ptr.ptr_; }
        /**
         * @brief operator == compares two iterators
         * @param ptr - iterator
         * @return false if same, true if not
         */
        bool operator!=(const const_iterator& ptr) const { return ptr_ != ptr.ptr_; }
        /**
         * @brief operator ++ prefix
         * @return reference to const_iterator
         */
        const_iterator & operator++ () {
            ptr_ = find_if(++ptr_, cont->end(),pred);
            return *this;
        }
        /**
         * @brief operator ++ sufix
         * @return const_iterator
         */
        const_iterator operator++(int) {
            const_iterator ptr(*this);
            operator++();
            return ptr;
        }
        /**
         * @brief operator *
         * @return value
         */
        const value_type& operator*() const { return *ptr_; }
        /**
         * @brief operator -> pointer to value
         * @return pointer to value
         */
        const value_type* operator->() const { return &(*ptr_); }
    private:
        friend class filter_view;

        PREDICATE pred;
        typename CONTAINER::const_iterator ptr_;
        const CONTAINER* cont;

        const_iterator (typename CONTAINER::const_iterator ptr,const CONTAINER* c,PREDICATE p):pred(p),ptr_(ptr),cont(c){}
    };
    
    /**
     * @brief Class constructor
     * @param c - container
     * @param p - predicate
     */
    filter_view(const CONTAINER & c, const PREDICATE & p):cont(c),pred(p){}
    /**
     * @brief Returns iterator to first element that matches predicate
     * @return iterator to first element
     */
    const_iterator begin() const{
        typename CONTAINER::const_iterator it=find_if(cont.begin(),cont.end(),pred);
        return const_iterator(it,&cont,pred);
    }
    /**
     * @brief Returns iterator to past-the-back() element
     * @return past-the-back() element
     */
    const_iterator end() const{
        typename CONTAINER::const_iterator it=find_if(cont.rbegin(), cont.rend(), pred).base();
        return const_iterator(it,&cont,pred);
    }
    /**
     * @brief Checks if container is empty
     * @return true-empty, false - not empty
     */
    bool empty() const{
        return (find_if(cont.begin(),cont.end(),pred)==cont.end());
    }
    /**
     * @brief Returns size of filtered container
     * @return size
     */
    size_t size() const{
        return count_if(cont.begin(),cont.end(), pred);
    }
    /**
     * @brief Returns first element that matches predicate
     * @return first element that matches predicate
     */
    const value_type& front() const{
        return *(find_if(cont.begin(),cont.end(),pred));
    }
    /**
     * @brief Returns last element that mathces predicate
     * @return last element that matches predicate
     */
    const value_type & back() const {
        return *(find_if(cont.rbegin(),cont.rend(),pred));
    }
    /**
     * @brief Returns predicate
     * @return Predicate
     */
    const PREDICATE & get_predicate() const{
        return pred;
    }
};

#endif
