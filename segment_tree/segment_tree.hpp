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
        tree_cont_(),
        identity_(specification::get_identity())
    {
    }
    
    segment_tree(size_type n, const value_type& val = value_type()) :
        cont_(n, val),
        tree_cont_(),
        identity_(specification::get_identity())
    {
        build();
    }
    
    template<typename InputIterator>
    segment_tree(InputIterator first, InputIterator last) :
        cont_(first, last),
        tree_cont_(),
        identity_(specification::get_identity())
    {
        build();
    }

    segment_tree(const container& cont) :
        cont_(cont),
        tree_cont_(),
        identity_(specification::get_identity())
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
    
    const T& query(size_type start, size_type last) const
    {
        // check start < last <= cont_.size()
        return query_recursive(0, size_type_pair(0, size_), size_type_pair(start, last));
    }
    
    void update(size_type index, const value_type& val)
    {
        // check index < cont_.size()
        update_recursive(0, size_type_pair(0, size_), index, val);
    }


protected:
    // Data members    
    container cont_;
    container tree_cont_;
    size_type height_;
    size_type size_;
    value_type identity_;

    // Query and update methods
    const T& query_recursive(size_type node, size_type_pair node_range, size_type_pair query_range) const
    {
        if (node_range.first >= query_range.first && node_range.second <= query_range.second)
            if (node_range.first + 1 == node_range.second)
                return get_element(node_range.first);
            else
                return tree_cont_[node];

        if (node_range.second <= query_range.first || query_range.second <= node_range.first)
            return identity_;

        size_type mid = mid_point(node_range.first, node_range.second);

        const T * left_val = & query_recursive((node<<1)+1, size_type_pair(node_range.first, mid),
            query_range);

        const T * right_val = & query_recursive((node<<1)+2, size_type_pair(mid, node_range.second),
            query_range);

        return specification::fn(*left_val, *right_val);
    }

    const T& update_recursive(size_type node, size_type_pair node_range, size_type index, const T& val)
    {
        if (node_range.first + 1 == node_range.second && index == node_range.first)
            return cont_[index] = val; // index must always be less than cont_.size()

        if (index < node_range.first || node_range.second <= index)
            if (node_range.first + 1 == node_range.second)
                return get_element(node_range.first);
            else
                return tree_cont_[node];

        size_type mid = mid_point(node_range.first, node_range.second);

        const T * left_val = & update_recursive((node<<1)+1, size_type_pair(node_range.first, mid),
            index, val);

        const T * right_val = & update_recursive((node<<1)+2, size_type_pair(mid, node_range.second),
            index, val);

        return tree_cont_[node] = specification::fn(*left_val, *right_val);
    }

    // Util functions
    size_type_pair tree_size(size_type n) const
    {
        size_type height = 0;
        size_type size = 1;

        while (size < n) ++height, size <<= 1;
        
        return size_type_pair(size - 1, height);
    }

    inline size_type_pair range_for_depth(size_type depth) const
    {
        return size_type_pair((1<<depth)-1, (1<<(depth+1))-1);
    }

    inline const value_type& get_element(size_type index) const
    {
        return index < cont_.size() ? cont_[index] : identity_;
    }

    inline size_type mid_point(size_type a, size_type b) const
    {
        // check b > a
        return a + ((b - a) >> 1);
    }
}; // class segment_tree

} // namespace fx

#endif // FX_SEGMENT_TREE_HPP

