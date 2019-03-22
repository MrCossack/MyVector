#include <iostream>
#include <vector>

#include "vector.h"

// 0 use std::vektor
// 1 use petz::vektor
#define PETZ 1

// 0 std::vektor and petz::vektor test use cases
// 1 petz::vektor additional test for erase_by_swap and as_Array
#define SPEZIAL 0

// used in MyClass
int id = 0;

// dummy struct
struct MyStruct
{
	MyStruct()
	{
		m_id = id;
	}
	int m_id;
	float m_float; // = 1.0f;
};

// dummy class
class MyClass
{
private:
	int m_id;
	float m_float; // = 1.0f;

public:

	MyClass()
	{
		m_id = id;
	}

	void setId(int id)
	{
		m_id = id;
	}

	int getId()
	{
		return m_id;
	}
};

int main()
{
#if PETZ

	/////////////////////////////////////////////////////////
	///////////---- create different vectors ---////////////
	///////////////////////////////////////////////////////
	petz::vector<int> test_int;
	petz::vector<MyStruct> test_MyStruct;
	petz::vector<MyClass> test_MyClass;

	petz::vector<int>* test_ptr_int = new petz::vector<int>;
	petz::vector<MyStruct>* test_ptr_MyStruct = new petz::vector<MyStruct>;
	petz::vector<MyClass>* test_ptr_MyClass = new petz::vector<MyClass>;

	petz::vector<petz::vector<int>>* vector_ptr_2d = new petz::vector<petz::vector<int>>;

#else
	std::vector<int> test_int;
	std::vector<MyStruct> test_MyStruct;
	std::vector<MyClass> test_MyClass;

	std::vector<int>* test_ptr_int = new std::vector<int>;
	std::vector<MyStruct>* test_ptr_MyStruct = new std::vector<MyStruct>;
	std::vector<MyClass>* test_ptr_MyClass = new std::vector<MyClass>;

#endif

	/////////////////////////////////////////////////////////
	/////////----- Test - reserve und resize ----///////////
	///////////////////////////////////////////////////////

	// integer vector
	test_int.reserve(5);
	test_int.resize(4);

	// struct vector
	test_MyStruct.reserve(5);
	test_MyStruct.resize(5);

	// MyClass vector
	test_MyClass.reserve(5);
	test_MyClass.resize(4);

	// ptr Integer
	test_ptr_int->reserve(5);
	test_ptr_int->resize(4);

	// ptr MyStruct
	test_ptr_MyStruct->reserve(5);
	test_ptr_MyStruct->resize(4);

	// ptr MyClass
	test_ptr_MyClass->reserve(5);
	test_ptr_MyClass->resize(4);

	/////////////////////////////////////////////////////////
	////////---- Test - increase dynamically ----///////////
	///////////////////////////////////////////////////////
	for (size_t i = 0; i < 20; i++)
	{
		test_int.push_back(i);
		test_MyStruct.push_back(MyStruct());
		test_MyClass.push_back(MyClass());

		test_ptr_int->push_back(i);
		test_ptr_MyStruct->push_back(MyStruct());
		test_ptr_MyClass->push_back(MyClass());

		id++;
	}

	/////////////////////////////////////////////////////////
	////---- Test - resize and decrease the vector ---//////
	///////////////////////////////////////////////////////

	test_int.resize(18);
	test_MyStruct.resize(18);
	test_MyClass.resize(18);

	test_ptr_int->resize(18);
	test_ptr_MyStruct->resize(18);
	test_ptr_MyClass->resize(18);

#if PETZ

	/////////////////////////////////////////////////////////
	///////////---- Test - erase functionen ----////////////
	///////////////////////////////////////////////////////

	// integer erase
	test_int.erase(2);
	test_int.erase(6, 8);

	// MyStruct erase
	test_MyStruct.erase(2);
	test_MyStruct.erase(6, 8);

	// MyClass erase
	test_MyClass.erase(2);
	test_MyClass.erase(6, 8);

	// pointer integer
	test_ptr_int->erase(2);
	test_ptr_int->erase(6, 8);

	// pointer MyStruct
	test_ptr_MyStruct->erase(2);
	test_ptr_MyStruct->erase(6, 8);

	// pointer MyClass
	test_ptr_MyClass->erase(2);
	test_ptr_MyClass->erase(6, 8);

	/////////////////////////////////////////////////////////
	////////---- as_Array and erase_by_swap -----///////////
	///////////////////////////////////////////////////////
#if SPEZIAL
	test_int.erase_by_swap(3);
	test_int.erase_by_swap(test_int.size() - 1);

	test_MyStruct.erase_by_swap(3);
	test_MyStruct.erase_by_swap(test_MyStruct.size() - 1);

	test_MyClass.erase_by_swap(3);
	test_MyClass.erase_by_swap(test_MyClass.size() - 1);

	test_ptr_int->erase_by_swap(3);
	test_ptr_int->erase_by_swap(test_ptr_int->size() - 1);

	test_ptr_MyStruct->erase_by_swap(3);
	test_ptr_MyStruct->erase_by_swap(test_ptr_MyStruct->size() - 1);

	test_ptr_MyClass->erase_by_swap(3);
	test_ptr_MyClass->erase_by_swap(test_ptr_MyClass->size() - 1);

	// vector changes in all three cases, not a usual use case
	int* ptr_int = test_int.as_array();
	*ptr_int = 4;

	MyStruct* ptr_MyStruct = test_MyStruct.as_array();
	ptr_MyStruct->m_id = 4;

	MyClass* ptr_MyClass = test_MyClass.as_array();
	ptr_MyClass->setId(4);

#endif
#else
	test_int.erase(test_int.begin() + 2);
	test_int.erase(test_int.begin() + 6, test_int.begin() + 8);

	test_MyStruct.erase(test_MyStruct.begin() + 2);
	test_MyStruct.erase(test_MyStruct.begin() + 6, test_MyStruct.begin() + 8);

	test_MyClass.erase(test_MyClass.begin() + 2);
	test_MyClass.erase(test_MyClass.begin() + 6, test_MyClass.begin() + 8);

	test_ptr_int->erase(test_ptr_int->begin() + 2);
	test_ptr_int->erase(test_ptr_int->begin() + 6, test_ptr_int->begin() + 8);

	test_ptr_MyStruct->erase(test_ptr_MyStruct->begin() + 2);
	test_ptr_MyStruct->erase(test_ptr_MyStruct->begin() + 6, test_ptr_MyStruct->begin() + 8);

	test_ptr_MyClass->erase(test_ptr_MyClass->begin() + 2);
	test_ptr_MyClass->erase(test_ptr_MyClass->begin() + 6, test_ptr_MyClass->begin() + 8);

#endif

	/////////////////////////////////////////////////////////
	/////////---- Test - resize with val -----//////////////
	///////////////////////////////////////////////////////

	test_int.resize(16, 9);
	test_MyStruct.resize(16, MyStruct());
	test_MyClass.resize(16, MyClass());

	test_ptr_int->resize(16, 9);
	test_ptr_MyStruct->resize(16, MyStruct());
	test_ptr_MyClass->resize(16, MyClass());

	/////////////////////////////////////////////////////////
	/////////////////---- Output -----//////////////////////
	///////////////////////////////////////////////////////

	// integer
	for (size_t i = 0; i < test_int.size(); i++)
	{
		printf("Integer vector 1: %i\n", test_int.at(i));
	}
	printf("\n");

	printf("Integer vector size: %i\n", test_int.size());
	printf("Integer vector capacity: %i\n\n", test_int.capacity());

	// MyStruct
	for (size_t i = 0; i < test_MyStruct.size(); i++)
	{
		printf("Struct vector 1: %i\n", test_MyStruct.at(i).m_id);
	}
	printf("\n");

	printf("Struct vector size: %i\n", test_MyStruct.size());
	printf("Struct vector capacity: %i\n\n", test_MyStruct.capacity());

	// MyClass
	for (size_t i = 0; i < test_MyClass.size(); i++)
	{
		printf("MyClass vector 1: %i\n", test_MyClass.at(i).getId());
	}
	printf("\n");

	printf("MyClass vector size: %i\n", test_MyClass.size());
	printf("MyClass vector capacity: %i\n\n", test_MyClass.capacity());

	// pointer Integer
	for (size_t i = 0; i < test_ptr_int->size(); i++)
	{
		printf("Integer ptr 1: %i\n", test_ptr_int->at(i));
	}
	printf("\n");

	printf("Integer ptr size: %i\n", test_ptr_int->size());
	printf("Integer ptr capacity: %i\n\n", test_ptr_int->capacity());

	// pointer MyStruct
	for (size_t i = 0; i < test_ptr_MyStruct->size(); i++)
	{
		printf("MyStruct ptr 1: %i\n", test_ptr_MyStruct->at(i));
	}
	printf("\n");

	printf("MyStruct ptr size: %i\n", test_ptr_MyStruct->size());
	printf("MyStruct ptr capacity: %i\n\n", test_ptr_MyStruct->capacity());

	// pointer MyClass
	for (size_t i = 0; i < test_ptr_MyClass->size(); i++)
	{
		printf("MyClass ptr 1: %i\n", test_ptr_MyClass->at(i));
	}
	printf("\n");

	printf("MyClass ptr size: %i\n", test_ptr_MyClass->size());
	printf("MyClass ptr capacity: %i\n\n", test_ptr_MyClass->capacity());

#if PETZ
	/////////////////////////////////////////////////////////
	//////////----- delete to much elements ------//////////
	///////////////////////////////////////////////////////

	for (size_t i = 0; i < 20; i++)
	{
		test_int.pop_back();
		test_MyStruct.pop_back();
		test_MyClass.pop_back();

		test_ptr_int->pop_back();
		test_ptr_MyStruct->pop_back();
		test_ptr_MyClass->pop_back();
	}
#endif

	/////////////////////////////////////////////////////////
	/////////////////----- clean up ------//////////////////
	///////////////////////////////////////////////////////

	free(test_ptr_int);
	free(test_ptr_MyStruct);
	free(test_ptr_MyClass);

	return 0;
}