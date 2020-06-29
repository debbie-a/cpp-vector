#include <iostream>
#include "test_vector.h"
#include "vector.h"

static const char* Bool[]={"false","true"};
void testVector()
{
	//test ctor
	try
	{
		Vector<int> vector(9999999999999999,10);
	}
	catch(std::bad_alloc& e)
	{
		std::cout<<e.what()<<std::endl;
	}
	Vector<int> vector1(5, 10);
	Vector<int> vector2(5, 4);
	//test copy ctor
	Vector<int> vector3(vector1);
	//test operator<<
	std::cout<<vector1<<std::endl;
	std::cout<<vector2<<std::endl;
	std::cout<<vector3<<std::endl;
	//test assignment operator=
	vector3=vector2;
	std::cout<<vector3<<std::endl;
	//test capacity
	std::cout<<vector1.capacity()<<std::endl;
	//test size
	std::cout<<vector2.size()<<std::endl;
	//test empty
	std::cout<<Bool[vector2.empty()]<<std::endl;
	//test push_back
	vector1.push_back(6);
	std::cout<<vector1<<std::endl;
	//test resize
	vector1.resize(20, 20);
	std::cout<<vector1<<std::endl;
	//test insert
	try
	{
		vector1.insert(7,4);
		vector1.insert(3,0);
		std::cout<<vector1<<std::endl;
		vector1.insert(3,99);
	}
	catch(const std::out_of_range& e)
	{
		std::cout<<e.what()<<std::endl;
	}
	//test pop_back
	try
	{
		std::cout<<vector1<<std::endl;
		Vector<long> emptyVector;
		emptyVector.pop_back();	
	}
	catch(const std::underflow_error& e)
	{
		std::cout<<e.what()<<std::endl;
	}
	//test erase
	vector1.erase(vector1.data());
	std::cout<<vector1<<std::endl;
	vector1.erase(vector1.data()+5);
	std::cout<<vector2[3]<<std::endl;
	std::cout<<vector1[4]<<std::endl;

	//test concatenate operators
	Vector<int> vector4 = vector1+vector2;
	vector4 += vector2;
	std::cout<<vector4<<std::endl;
	std::cout<<vector2<<std::endl;
}
