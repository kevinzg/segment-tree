#include <iostream>
#include <limits>
#include <algorithm>
#include <cassert>
#include "../segment_tree/segment_tree.hpp"

template <typename T>
struct rmq_specification
{
    static inline const T& get_identity()
    {
        static const T IDENTITY = std::numeric_limits<T>::max();
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

    assert(st.query(0, 10) == 0);
    assert(st.query(8, 10) == 8);
    assert(st.query(9, 10) == 9);
    assert(st.query(5, 7) == 5);
    assert(st.query(2, 8) == 2);
    assert(st.query(0, 1) == 0);
    assert(st.query(3, 9) == 3);

    st.update(0, 100);
    assert(st.query(0, 10) == 1);
    assert(st.query(0, 1) == 100);

    st.update(9, -100);
    assert(st.query(0, 10) == -100);
    assert(st.query(9, 10) == -100);

    st.update(5, -200);
    assert(st.query(0, 10) == -200);
    assert(st.query(9, 10) == -100);

    st.update(3, 1000);
    assert(st.query(3, 4) == 1000);
    st.update(5, 999);
    assert(st.query(3, 6) == 4);
    st.update(4, 998);
    assert(st.query(3, 6) == 998);

    return 0;
}
