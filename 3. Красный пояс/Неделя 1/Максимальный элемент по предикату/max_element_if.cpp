template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    auto current = find_if(first, last, pred);
    for (ForwardIterator i = current; i != last; ++i) {
        if (i != current && pred(*i) && *current < *i) {
            current = i;
        }
    }
    return current;
}
