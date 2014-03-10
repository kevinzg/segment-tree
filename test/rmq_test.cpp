#include <iostream>
#include <limits>
#include <algorithm>
#include "../segment_tree/segment_tree.hpp"

template <typename T>
struct rmq_specification
{
    static inline const T& get_identity()
    {
        static const T IDENTITY = std::numeric_limits<T>::min();
        return IDENTITY;
    }

    static inline const T& fn(const T & a, const T & b)
    {
        return std::min(a, b);
    }
};

typedef fx::segment_tree<int, rmq_specification<int> > segment_tree_rmq;

int main()
{
    size_t array_size = 10;
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    segment_tree_rmq st(array, array+array_size);

    std::cout << (st.query(0, 10) == 0) << std::endl;

    return 0;
}
