#include "forward_list_impl.h"

bool ForwardList::ForwardListIterator::operator==(const ForwardListIterator& other) const {
    return this->position_ == other.position_;
}

bool ForwardList::ForwardListIterator::operator!=(const ForwardListIterator& other) const {
    return !(*this == other);
}

int32_t& ForwardList::ForwardListIterator::operator*() const {
    return position_->value_;
}

int* ForwardList::ForwardListIterator::operator->() {
    return &position_->value_;
}

ForwardList::ForwardListIterator& ForwardList::ForwardListIterator::operator++() {
    if (position_ != nullptr) {
        position_ = position_->next_;
    }
    return *this;
}

ForwardList::ForwardListIterator ForwardList::ForwardListIterator::operator++(int) {
    ForwardListIterator retval = *this;
    ++(*this);
    return retval;
}

ForwardList::ForwardList() {
    front = nullptr;
    size = 0;
}

ForwardList::ForwardListIterator ForwardList::begin() {
    return ForwardListIterator(front);
}

ForwardList::ForwardListIterator ForwardList::end() {
    return ForwardListIterator(nullptr);
}

ForwardList::ForwardListIterator ForwardList::begin() const {
    return ForwardListIterator(front);
}

ForwardList::ForwardListIterator ForwardList::end() const {
    return ForwardListIterator(nullptr);
}

void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = this->front;
    this->front = new_node;
    ++this->size;
}

void ForwardList::PopFront() {
    if (this->front == nullptr) {
        return;
    }
    Node* temp = this->front->next_;
    delete this->front;
    this->front = temp;
    --this->size;
}

ForwardList::ForwardList(size_t count, int32_t value) : front(nullptr), size(0) {
    if (count == 0)
        return;
    this->front = new Node(value);
    this->size++;
    Node* tail = this->front;
    for (size_t i = 1; i < count; ++i) {
        tail->next_ = new Node(value);
        tail = tail->next_;
        this->size++;
    }
}

ForwardList::ForwardList(const ForwardList& rhs) : front(nullptr), size(0) {
    if (rhs.front == nullptr)
        return;
    this->front = new Node(rhs.front->value_);
    this->size++;
    Node* tail = this->front;
    Node* currentRhs = rhs.front->next_;
    while (currentRhs != nullptr) {
        tail->next_ = new Node(currentRhs->value_);
        tail = tail->next_;
        currentRhs = currentRhs->next_;
        this->size++;
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) : front(nullptr), size(0) {
    if (init.size() == 0)
        return;
    const int32_t* it = init.begin();
    this->front = new Node(*it);
    this->size++;
    Node* tail = this->front;
    ++it;
    while (it != init.end()) {
        tail->next_ = new Node(*it);
        tail = tail->next_;
        this->size++;
        ++it;
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs)
        return *this;
    ForwardList t(rhs);
    std::swap(this->front, t.front);
    std::swap(this->size, t.size);
    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::Remove(int32_t value) {
    while (front != nullptr && front->value_ == value) {
        PopFront();
    }
    Node* current = front;
    while (current != nullptr && current->next_ != nullptr) {
        if (current->next_->value_ == value) {
            Node* toDelete = current->next_;
            current->next_ = toDelete->next_;
            delete toDelete;
            this->size--;
        } else {
            current = current->next_;
        }
    }
}

void ForwardList::Clear() {
    while (front != nullptr) {
        PopFront();
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = front;
    while (current != nullptr) {
        if (current->value_ == value)
            return true;
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = front;
    while (current != nullptr) {
        out << current->value_;
        if (current->next_ != nullptr)
            out << " ";
        current = current->next_;
    }
}

int32_t ForwardList::Front() const {
    if (this->front != nullptr)
        return this->front->value_;
    return 0;
}

size_t ForwardList::Size() const {
    return this->size;
}
