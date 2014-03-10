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
    typedef Specification specification;
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
    {
        size_type_pair tree_size_height = tree_size(cont_.size());

        size_ = tree_size_height.first+1;
        height_ = tree_size_height.second;

        tree_cont_.resize(size_-1);

        if (!height_) return;

        size_type_pair range = range_for_depth(height_-1);
        size_type& start = range.first;
        size_type& end = range.second;

        // tree base level
        for (size_type k = 0; start+k < end; ++k)
            tree_cont_[start+k] = specification::fn(get_element(k<<1), get_element((k<<1)+1));

        // other levels
        for (size_type h = 1, depth = height_-2; h < height_; ++h, --depth)
        {
            range = range_for_depth(depth);
            size_type& start = range.first;
            size_type& end = range.second;

            for (size_type k = start; k < end; ++k)
                tree_cont_[k] = specification::fn(tree_cont_[(k<<1)+1], tree_cont_[(k<<1)+2]);
        }
    }
    
    const T& query(size_type start, size_type last);
    
    void update(size_type index, const T& val);


protected:
    // Data members    
    container cont_;
    container tree_cont_;
    size_type height_;
    size_type size_;

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
        return size_type_pair((1<<depth)-1, (1<<(depth+1))-1);
    }
    
    inline const value_type& get_element(size_type index)
    {
        return index < cont_.size() ? cont_[index] : specification::get_identity();
    }
}; // class segment_tree

} // namespace fx

#endif // FX_SEGMENT_TREE_HPP

