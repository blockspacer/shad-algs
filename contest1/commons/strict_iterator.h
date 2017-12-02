#pragma once

#include <iterator>
#include <type_traits>

template<class Iterator>
class StrictIterator: public std::iterator<std::bidirectional_iterator_tag,
                                           typename std::iterator_traits<Iterator>::value_type> {
public:
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using reference = typename std::iterator_traits<Iterator>::reference;

    StrictIterator(Iterator first, Iterator current, Iterator last):
        first_(first), current_(current), last_(last) {}

    StrictIterator& operator++() {
        if (current_ == last_)
            throw std::range_error("out of range (right)");
        ++current_;
        return *this;
    }

    StrictIterator operator++(int) {
        StrictIterator old(*this);
        this->operator++();
        return old;
    }

    StrictIterator& operator--() {
        if (current_ == first_)
            throw std::range_error("out of range (left)");
        --current_;
        return *this;
    }

    StrictIterator operator--(int) {
        StrictIterator old(*this);
        this->operator--();
        return old;
    }

    reference operator*() {
        if (current_ == last_)
            throw std::range_error("dereferencing end of sequence");
        return *current_;
    }

    const reference operator*() const {
        if (current_ == last_)
            throw std::range_error("dereferencing end of sequence");
        return *current_;
    }

    auto operator->() {
        return &(this->operator*());
    }

    auto operator->() const {
        return &(this->operator*());
    }

    bool operator==(const StrictIterator& r) const {
        return current_ == r.current_;
    }

    bool operator!=(const StrictIterator& r) const {
        return !(current_ == r.current_);
    }
private:
    Iterator first_, current_, last_;
};

template<class Iterator>
StrictIterator<Iterator> MakeStrict(Iterator first, Iterator current, Iterator last) {
    return StrictIterator<Iterator>(first, current, last);
}
