/* 
 * File:   PtrContainer.hpp
 * Author: Errata
 *
 * Created on 30 janvier 2011, 18:36
 */

#ifndef PTRCONTAINER_HPP
#define	PTRCONTAINER_HPP

template <typename T>
class IPtrContainer {
public:

    virtual ~IPtrContainer() {
    }
    virtual T * operator*() = 0;
    virtual T * operator-> () = 0;
    virtual const T * operator*() const = 0;
    virtual const T * operator-> () const = 0;
    virtual T* getPtr() = 0;
    virtual const T* getPtr() const = 0;
    virtual IPtrContainer* clone() const = 0;
};

//this container clean his pointer when remplacing it or is delete

template <typename T>
class SafeContainer : IPtrContainer<T> {
public:

    SafeContainer() : _ptr(0) {
    }

    ~SafeContainer() {
        if (_ptr)
            delete _ptr;
    }

    SafeContainer(T* ptr) : _ptr(ptr) {
    }

    SafeContainer(const SafeContainer& orig) {
        if (_ptr && _ptr != orig._ptr) {
            delete _ptr;
        }
        _ptr = orig._ptr;
    }

    SafeContainer & operator=(const SafeContainer& orig) {
        if (this != &orig) {
            if (_ptr && _ptr != orig._ptr) {
                delete _ptr;
            }
            _ptr = orig._ptr;
        }
        return *this;
    }

    T* getPtr() {
        return _ptr;
    }

    const T* getPtr() const {
        return _ptr;
    }

    T * operator*() {
        return _ptr;
    }

    T * operator-> () {
        return _ptr;
    }

    const T * operator*() const {
        return _ptr;
    }

    const T * operator-> () const {
        return _ptr;
    }

    IPtrContainer<T>* clone() const{
        return new SafeContainer(*this);
    }

private:
    T* _ptr;
};

//this container do not delete his pointer, so he can store stack allocated pointer

template <typename T>
class UnsafeContainer : IPtrContainer<T> {
public:

    UnsafeContainer() : _ptr(0) {
    }

    ~UnsafeContainer() {
    }

    UnsafeContainer(T* ptr) : _ptr(ptr) {
    }

    UnsafeContainer(const UnsafeContainer& orig) {
        _ptr = orig._ptr;
    }

    UnsafeContainer & operator=(const UnsafeContainer& orig) {
        if (this != &orig) {
            _ptr = orig._ptr;
        }
        return *this;
    }

    T* getPtr() {
        return _ptr;
    }

    const T* getPtr() const {
        return _ptr;
    }

    T * operator*() {
        return _ptr;
    }

    T * operator-> () {
        return _ptr;
    }

    const T * operator*() const {
        return _ptr;
    }

    const T * operator-> () const {
        return _ptr;
    }

    IPtrContainer<T>* clone() const{
        return new UnsafeContainer(*this);
    }

private:
    T* _ptr;
};

#endif	/* PTRCONTAINER_HPP */

