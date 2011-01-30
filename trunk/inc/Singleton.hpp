/* 
 * File:   Singleton.hpp
 * Author: Errata
 *
 * Created on 19 janvier 2011, 23:34
 */

#ifndef SINGLETON_HPP
#define	SINGLETON_HPP

template <typename T>
class Singleton {
public:

    static T& Instance() {
        static T instance;
        return instance;
    }

protected:

    Singleton() {
    }

    ~Singleton() {
    }
};

#define SINGLETON_CLASS(CLASS) friend class Singleton<CLASS>

#endif	/* SINGLETON_HPP */

