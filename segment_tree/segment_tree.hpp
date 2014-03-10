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
    void build()
    
    void query(size_type start, size_type last);
    
    void update(size_type index);


protected:
    // Data members    
    container cont_;
    container tree_cont_;
    size_type height_;

    // Util functions
    size_type_pair tree_size(size_type n)
    {
        size_type height = 0;
        size_type size = 1;

        while (size < n) ++height, size <<= 1;
        
        return size_type_pair(size - 1, height);
    }

    inline size_type_pair range_for_depth(size_type depth)
    {
        return index < cont_.size() ? cont_[index] : S::get_identity();
    }
    
    inline const value_type& get_element(size_type index)
    {
        return index < cont_.size() ? cont_[index] : S::get_identity();
    }
}; // class segment_tree

} // namespace fx

#endif // FX_SEGMENT_TREE_HPP

