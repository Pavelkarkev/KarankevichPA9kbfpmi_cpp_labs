#include "forward_list_impl.h"

bool ForwardList::ForwardListIterator::operator==(const ForwardListIterator& other) const {
    return position_ == other.position_;
}

bool ForwardList::ForwardListIterator::operator!=(const ForwardListIterator& other) const {
    return !(*this == other);
}

int32_t& ForwardList::ForwardListIterator::operator*() const {
    return position_->value_;
}

int32_t* ForwardList::ForwardListIterator::operator->() {
    return &position_->value_;
}

ForwardList::ForwardListIterator& ForwardList::ForwardListIterator::operator++() {
    if (position_)
        position_ = position_->next_;
    return *this;
}

ForwardList::ForwardListIterator ForwardList::ForwardListIterator::operator++(int) {
    ForwardListIterator tmp = *this;
    ++(*this);
    return tmp;
}

ForwardList::ForwardList() : front_(nullptr), size_(0) {
}

ForwardList::ForwardListIterator ForwardList::begin() {
    return ForwardListIterator(front_);
}
ForwardList::ForwardListIterator ForwardList::end() {
    return ForwardListIterator(nullptr);
}
ForwardList::ForwardListIterator ForwardList::begin() const {
    return ForwardListIterator(front_);
}
ForwardList::ForwardListIterator ForwardList::end() const {
    return ForwardListIterator(nullptr);
}

int32_t ForwardList::Front() const {
    if (front_)
        return front_->value_;
    return 0;
}

size_t ForwardList::Size() const {
    return size_;
}

void ForwardList::PushFront(int32_t value) {
    Node* newNode = new Node(value);
    newNode->next_ = front_;
    front_ = newNode;
    size_++;
}

void ForwardList::PopFront() {
    if (!front_)
        return;
    Node* temp = front_->next_;
    delete front_;
    front_ = temp;
    size_--;
}

void ForwardList::Clear() {
    while (front_)
        PopFront();
}

ForwardList::~ForwardList() {
    Clear();
}

ForwardList::ForwardList(size_t count, int32_t value) : front_(nullptr), size_(0) {
    if (count == 0)
        return;
    front_ = new Node(value);
    size_++;
    Node* tail = front_;
    for (size_t i = 1; i < count; ++i) {
        tail->next_ = new Node(value);
        tail = tail->next_;
        size_++;
    }
}

ForwardList::ForwardList(const ForwardList& rhs) : front_(nullptr), size_(0) {
    if (!rhs.front_)
        return;
    front_ = new Node(rhs.front_->value_);
    size_++;
    Node* tail = front_;
    Node* currentRhs = rhs.front_->next_;
    while (currentRhs) {
        tail->next_ = new Node(currentRhs->value_);
        tail = tail->next_;
        currentRhs = currentRhs->next_;
        size_++;
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) : front_(nullptr), size_(0) {
    if (init.size() == 0)
        return;
    const int32_t* it = init.begin();
    front_ = new Node(*it);
    size_++;
    Node* tail = front_;
    for (++it; it != init.end(); ++it) {
        tail->next_ = new Node(*it);
        tail = tail->next_;
        size_++;
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this != &rhs) {
        ForwardList tmp(rhs);
        std::swap(front_, tmp.front_);
        std::swap(size_, tmp.size_);
    }
    return *this;
}

void ForwardList::Remove(int32_t value) {
    while (front_ && front_->value_ == value)
        PopFront();
    Node* curr = front_;
    while (curr && curr->next_) {
        if (curr->next_->value_ == value) {
            Node* toDelete = curr->next_;
            curr->next_ = toDelete->next_;
            delete toDelete;
            size_--;
        } else {
            curr = curr->next_;
        }
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* curr = front_;
    while (curr) {
        if (curr->value_ == value)
            return true;
        curr = curr->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* curr = front_;
    while (curr) {
        out << curr->value_;
        if (curr->next_)
            out << " ";
        curr = curr->next_;
    }
}
