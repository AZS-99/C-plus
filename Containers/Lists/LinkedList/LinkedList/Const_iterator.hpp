//
//  Const_iterator.hpp
//  LinkedList
//
//  Created by Adam Saher on 01/02/2019.
//  Copyright © 2019 Adam Saher. All rights reserved.
//

#ifndef Const_iterator_h
#define Const_iterator_h

namespace Container {
    template <typename T>
    class LinkedList;
    
    template <typename T>
    class Const_iterator {
        Node<T>* current_;
        const LinkedList<T>* linked_lst_;
        friend LinkedList<T>;
        
    protected:
        Const_iterator(Node<T>*, const LinkedList<T>*);
        
    public:
        const T& operator*() const;
        Const_iterator& operator-(int);
        Const_iterator& operator++();     // ++x
        Const_iterator& operator++(int);  // x++
        Const_iterator& operator--();
        bool operator==(const Const_iterator& other) const;
        bool operator!=(const Const_iterator& other) const;
    };
    
    
    template <typename T>
    Const_iterator<T>::Const_iterator(Node<T>* current, const LinkedList<T>* linked_lst) : linked_lst_(linked_lst){
        current_= current;
    }
    
    
    template <typename T>
    Const_iterator<T>& Const_iterator<T>::operator++(int) {
        //Remember that x++ returns the old value
        Const_iterator old = *this;
        current_ = current_->nxt_;
        return old;
    }
    
    
    template <typename T>
    Const_iterator<T>& Const_iterator<T>::operator++() {
        if (current_)
            current_ = current_->nxt_;
        else
            current_ = linked_lst_->head_;
        return *this;
    }
    
    
    template <typename T>
    Const_iterator<T>& Const_iterator<T>::operator--() {
        //Remember that x-- returns the old value
        if (current_)
            current_ = current_->prev_;
        else
            current_ = linked_lst_->tail_;
        return *this;
    }
    
    
    template <typename T>
    const T& Const_iterator<T>::operator*() const {
        return current_->data_;
    }
    
    
    template <typename T>
    Const_iterator<T>& Const_iterator<T>::operator-(int x) {
        if (current_)
            current_ = current_->prev_;
        else
            current_ = linked_lst_->tail_;
        return *this;
    }
    
    
    template <typename T>
    bool Const_iterator<T>::operator==(const Const_iterator& other) const {
        return (current_ == other.current_);
    }
    
    
    template <typename T>
    bool Const_iterator<T>::operator!=(const Const_iterator& other) const {
        return (current_ != other.current_);
    }
}


#endif /* Const_iterator_h */
