template<typename T>
class VectorIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;

    VectorIterator(std::vector<T>& vec, std::size_t index)
        : vec_(vec), index_(index)
    {
    }

    reference operator*() const
    {
        return vec_[index_];
    }

    pointer operator->() const
    {
        return &vec_[index_];
    }

    VectorIterator& operator++()
    {
        ++index_;
        return *this;
    }

    VectorIterator operator++(int)
    {
        VectorIterator tmp(*this);
        ++index_;
        return tmp;
    }

    bool operator==(const VectorIterator& other) const
    {
        return &vec_ == &other.vec_ && index_ == other.index_;
    }

    bool operator!=(const VectorIterator& other) const
    {
        return !(*this == other);
    }

private:
    std::vector<T>& vec_;
    std::size_t index_;
};
