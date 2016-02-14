
#include "stdafx.h"
#include <memory>
#include <iostream>

struct ICloneBase {
private:
	virtual ICloneBase* doClone() const = 0;
};

template <typename T, typename Base = ICloneBase>
struct Cloneable : public Base {
public:
	T* clone() const { return static_cast<T*>(this->doClone()); }
private:
	virtual ICloneBase* doClone() const { return new T(static_cast<const T&>(*this)); }
};


struct A : public Cloneable<A> {
public: 
	virtual void tell() { std::cout << "A" << std::endl; }
};
struct B : public Cloneable<B, A> {
public:
	virtual void tell() { std::cout << "B" << std::endl; }
};
struct C : public Cloneable<C, B> {
public:
	virtual void tell() { std::cout << "C" << std::endl; }
};

int main()
{
	A a;
	B b;
	C c;
	std::shared_ptr<A> ca1(a.clone());
	std::shared_ptr<A> cb1(b.clone());
	std::shared_ptr<A> cc1(c.clone());
	ca1->tell();
	cb1->tell();
	cc1->tell();
	std::shared_ptr<A> ca2(ca1->clone());
	std::shared_ptr<A> cb2(cb1->clone());
	std::shared_ptr<A> cc2(cc1->clone());
	ca2->tell();
	cb2->tell();
	cc2->tell();
	return 0;
}

