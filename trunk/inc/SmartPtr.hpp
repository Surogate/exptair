/* 
 * File:   SmartPtr.hpp
 * Author: Errata
 *
 * Created on 30 janvier 2011, 17:50
 */

#ifndef SMARTPTR_HPP
#define	SMARTPTR_HPP

#include <iostream>
#include "PtrContainer.hpp"

class ReferenceCounter {
public:

    ReferenceCounter() : _count(0) {
    }

    ReferenceCounter(const ReferenceCounter& orig) : _count(orig._count) {
    }

    ~ReferenceCounter() {
    }

    ReferenceCounter & operator=(const ReferenceCounter& orig) {
        if (this != &orig) {
            _count = orig._count;
        }
        return *this;
    }

    void addRef(void) {
        ++_count;
    }

    void delRef(void) {
        --_count;
    }

    unsigned long getRef(void) const {
        return _count;
    }

    bool isNull(void) const {
        return (_count == 0);
    }

private:
    unsigned long _count;
};

template <class T, typename Container = SafeContainer<T> >
class SmartPtr : public IPtrContainer<T> {
public:

    SmartPtr() : _ptr(0), _count(0) {
        _count = new ReferenceCounter;
        _count->addRef();
    }

    SmartPtr(T* ptr) : _count(0) {
        _ptr = new Container(ptr);
        _count = new ReferenceCounter;
        _count->addRef();
    }

    SmartPtr(const SmartPtr& orig) : _count(orig._count), _ptr(orig._ptr) {
        _count->addRef();
    }

    virtual ~SmartPtr() {
        _count->delRef();
        if (_count->isNull()) {
            if (_ptr) {
                delete _ptr;
                _ptr = 0;
            }
            delete _count;
        }
    }

    T * operator*() {
        return _ptr->getPtr();
    }

    const T * operator*() const {
        return _ptr->getPtr();
    }

    T * operator-> () {
        return _ptr->getPtr();
    }

    const T * operator-> () const {
        return _ptr->getPtr();
    }

    T* getPtr() {
        return _ptr->getPtr();
    }
    
    const T* getPtr() const{
        return _ptr->getPtr();
    }

    SmartPtr & operator=(const SmartPtr& orig) {
        if (this != &orig) {
            _count->delRef();
            if (!_count->isNull()) {
                if (_ptr) {
                    delete _ptr;
                    _ptr = 0;
                }
                delete _count;
            }
            _ptr = orig._ptr;
            _count = orig._count;
            _count->addRef();
        }
        return *this;
    }

    IPtrContainer<T>* clone() const{
        return new SmartPtr(*this);
    }

private:
    ReferenceCounter* _count;
    Container* _ptr;
};

#endif	/* SMARTPTR_HPP */

