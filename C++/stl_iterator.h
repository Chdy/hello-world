//
// Created by 邓岩 on 2018/9/12.
//

#ifndef C_STL_ITERATOR_H
#define C_STL_ITERATOR_H
template <class T>
struct MyIter {
    typedef T value_type;
    T * ptr;
    MyIter(T * p = 0) : ptr(p) {}
    T &operator*() const { return *ptr; }
};

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category,class T,class Distance = ptrdiff_t,class Pointer = T*,class Reference = T&>
struct iterator {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

template <class I> //特性萃取机
struct iterator_traits {
    typedef typename I::value_type value_type;
    typedef typename I::difference_type difference_type;
    typedef typename I::pointer pointer;
    typedef typename I::reference reference;
    typedef typename I::iterator_category iterator_category;
};

template <class I> //针对原生指针的偏特化
struct iterator_traits<I *> {
    typedef I value_type;
    typedef ptrdiff_t difference_type;
    typedef I* pointer;
    typedef I& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class I> //针对原生常量指针的偏特化
struct iterator_traits<const I *> {
    typedef I value_type;
    typedef ptrdiff_t difference_type;
    typedef I* pointer;
    typedef I& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category //这里本来可以直接使用Iterator::iterator_category，使用萃取机可以使用偏特化以处理原生指针
iterator_category(const Iterator&)
{
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type *
distance_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
}

template <class Iterator>
inline iterator_traits<Iterator>::value_type *
value_type(const Iterator&)
{
    return static_cast<typename Iterator<Iterator>::value_type *>(0);
}

template <class I>
typename iterator_traits<I>::value_type
func(I ite)
{
    return *ite;
}

struct __true_type {};
struct __false_type {};

template <class type>
struct __true_type {
    typedef __true_type this_dummy_member_must_be_first;
    typedef __false_type has_trival_default_
    typedef __false_type has_trival_default
    typedef __false_type has_trival_default
    typedef __false_type is_POD_type;
};
#endif //C_STL_ITERATOR_H
