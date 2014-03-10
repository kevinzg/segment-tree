#ifndef FX_SEGMENT_TREE_HPP
#define FX_SEGMENT_TREE_HPP

#include <vector>
#include <utility>

namespace fx {

template <typename T, typename Specification, typename Container=std::vector<T> >
class segment_tree
{
protected:
    // Types
    typedef T value_type;
    typedef Container container;
    typedef typename Container::size_type size_type;
    typedef std::pair<size_type, size_type> size_type_pair;
    
public:
    // Constructors
    segment_tree() :
        cont_(),
        tree_cont_()
    {
    }
    
    segment_tree(size_type n, const value_type& val = value_type()) :
        cont_(n, val),
        tree_cont_()
    {
        build();
    }
    
    template<typename InputIterator>
    segment_tree(InputIterator first, InputIterator last) :
        cont_(first, last),
        tree_cont_()
    {
        build();
    }

    segment_tree(const container& cont) :
        cont_(cont),
        tree_cont_()
    {
        build();
    }
    
    // Public methods
    void built();
    
    void query(size_type start, size_type last);
    
    void update(size_type index);


protected:
    // Data members    
    container tree_cont_;
    container cont_;
    
    // Util functions
    size_type best_size(size_type size);
};

} // namespace fx

#endif // FX_SEGMENT_TREE_HPP

