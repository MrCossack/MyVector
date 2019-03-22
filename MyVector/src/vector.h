namespace petz
{
	template<class T>
	class vector
	{
	public:

		/*
		* default constructor
		*/
		vector()
		{
			m_vcapacity = 1;
			ptr_memArray = static_cast<T*>(malloc(m_vcapacity * sizeof(T)));
			m_vsize = 0;
		}

		/* 
		* constructor
		* @param - size of the vector
		*/
		vector(int size)
		{
			m_vcapacity = size;
			ptr_memArray = static_cast<T*>(malloc(m_vcapacity * sizeof(T)));
			m_vsize = size;

			for (int i = 0; i < m_vsize; i++)
			{
				new(&ptr_memArray[i]) T();
			}
		}

		/*
		* constructor
		* @param - size of the vector
		* @param - 
		*/
		vector(int size, const T& element)
		{
			m_vcapacity = size;
			m_vsize = size;
			ptr_memArray = static_cast<T*>(malloc(m_vcapacity * sizeof(T)));

			for (unsigned int i = 0; i < m_vsize; i++)
			{
				new(&ptr_memArray[i]) T(element);
			}
		}

		/*
		* copy constructor
		* @param - vector to copy
		*/ 
		vector(const T& v)
		{
			m_vcapacity = v.vcapacity;
			m_vsize = v.vsize;
			ptr_memArray = static_cast<T*>(malloc(m_vcapacity * sizeof(T)));
			for (int i = 0; i < v.vsize; i++)
			{
				new(&ptr_memArray[i]) T(v.memArray[i]);
			}
		}

		/*
		* destruktor
		*/
		~vector()
		{
			for (unsigned int i = 0; i < m_vsize; i++)
			{
				ptr_memArray[i].~T();
			}
			free(ptr_memArray);
		}

		/*
		* insert an element to the last position of the vector
		* @param - reference of the element to insert
		*/
		void push_back(const T& element)
		{
			// is there enough space in our vector
			if (m_vsize + 1 > m_vcapacity)
			{
				// increase the vector, if necessary
				alloc_new();
			}
			// insert new item
			new(&ptr_memArray[m_vsize]) T(element);
			m_vsize++;
		}

		/*
		* removes the last element in the vector
		*/
		void pop_back()
		{
			// is there an element in our vector
			if (m_vsize > 0)
			{
				// call desturctor
				ptr_memArray[m_vsize - 1].~T();
				m_vsize--;
			}
			else {
				printf("Vector is empty\n");
			}
		}

		/*
		*returns the size of the vektor.
		*/
		const size_t size() const
		{
			return m_vsize;
		}

		/* 
		* capacity of the allocted memory
		*/
		const size_t capacity() const
		{
			return m_vcapacity;
		}

		/*
		* delete desired element 
		*
		* @param - item position
		*/
		void erase(size_t position)
		{
			// check the position is valid
			if (position < m_vsize)
			{
				// delete the element and reorganize the vector
				// every element higher than the deleted once will be decreased by one position
				for (size_t i = position; i < m_vsize - 1; i++)
				{
					ptr_memArray[i].~T();
					new(&ptr_memArray[i]) T(ptr_memArray[i + 1]);
				}
				// delete last element
				pop_back();
			}
			else {
				printf("Warning array position: %ui\n", position);
			}
		}

		/*
		* removes a range of elements
		*
		* @params - where to begin and end the procedure
		*/
		void erase(size_t begin, size_t end)
		{
			if ( 0 <= begin && begin < end && end < m_vsize )
			{
				for (size_t i = begin; i < end; i++)
				{
					erase(begin);
				}
			}
			else {
				printf("Warning Erase(beginn, end) range");
			}
		}

		/*
		* remove an element and copy the last element of the vector to this postion.
		*
		* @param - position of the element to remove
		*/
		void erase_by_swap(size_t position)
		{
			if (position < m_vsize)
			{
				ptr_memArray[position].~T();
				new(&ptr_memArray[position]) T(ptr_memArray[m_vsize - 1]);
				pop_back();
			}
		}

		/*
		* if size is smaller than the current container size, the content is reduced to iths first n elements, removing those beyond
		* if size is greater than the current container size, the content is expanded by inserting at the end as many elements as needed with dummy elements
		*
		* @param - new size of the vector
		*/
		void resize(size_t size)
		{
			if (size > m_vsize)
			{
				while (m_vcapacity < size)
				{
					alloc_new();
				}

				for (size_t i = m_vsize; i < size; i++)
				{
					new(&ptr_memArray[i]) T();
				}
				m_vsize = size;
			}
			else if (size < m_vsize && size > 0)
			{
				for (size_t i = size; i < m_vsize; i++)
				{
					ptr_memArray[i].~T();
				}
				m_vsize = size;
			}
		}

		/*
		* if size is smaller than the current container size, the content is reduced to iths first n elements, removing those beyond (val param will be ignored)
		* if size is greater than the current container size, the content is expanded by inserting at the end as many elements as needed with val param elemntens
		*
		* @param - new size of the vector
		* @param - val are the elements to add
		*/
		void resize(size_t size, const T& val) 
		{
			if (size > m_vsize)
			{
				while (m_vcapacity < size)
				{
					alloc_new();
				}

				for (size_t i = m_vsize; i < size; i++)
				{
					new(&ptr_memArray[i]) T(val);
				}
				m_vsize = size;
			}
			else if (size < m_vsize && size > 0)
			{
				for (size_t i = size; i < m_vsize; i++)
				{
					ptr_memArray[i].~T();
				}
				m_vsize = size;
			}
		}

		/*
		* if the new capacity is greater than the current vector capacity, the function causes the container to reallocate its
		* storage increasing its capacity
		* 
		* @param - minimum capactiy for the vector
		*/
		void reserve(size_t capacity)
		{
			while (m_vcapacity < capacity)
			{
				alloc_new();
			}
		}

		/*
		* returns a reference to the element at position i in the vector
		*
		* @params - i is the position to return
		*/
		T& at(size_t i)
		{
			if (i < m_vsize)
			{
				return ptr_memArray[i];
			}
			throw 10;
		}

		/*
		* returns a reference to the element at position i in the vector
		*
		* @params - i is the position to return
		*/
		const T& at(size_t i) const
		{
			if (i < m_vsize)
			{
				return ptr_memArray[i];
			}
			throw 10;
		}

		/*
		* returns a reference to the element at position n in the vector container.
		*
		* a similar member function, vector::at, has the same behavior as this operator function,
		* except that vector::at is bound-checked and signals if the requested position is out of range
		* by throwing an out_of_range exception. 
		*
		* @params - i is the position to return
		*/
		T& operator[](size_t i)
		{
			return ptr_memArray[i];
		}

		/*
		* returns a reference to the element at position n in the vector container.
		*
		* a similar member function, vector::at, has the same behavior as this operator function,
		* except that vector::at is bound-checked and signals if the requested position is out of range
		* by throwing an out_of_range exception.
		*
		* @params - i is the position to return
		*/
		const T& operator[](size_t i) const
		{
			return ptr_memArray[i];
		}

		/*
		* return a pointer to the start of the vector
		*/
		T* as_array()
		{
			return ptr_memArray;
		}

		/*
		* return a pointer to the start of the vector
		*/
		const T* as_array() const
		{
			return ptr_memArray;
		}


	private:
		// current count of the elements in the vector. If an element will be added, the m_vsize increase by one.
		size_t m_vsize;
		// current allocated memory for the vector
		size_t m_vcapacity;
		// pointer to the start position of the vektor
		T* ptr_memArray;

		/*
		* generates a new vector and copy the elements of the old vector in the new one and
		* redirects the pointer to the new position in the memory
		*/
		void alloc_new()
		{

			// the vector increases with the power of two
			// thr std::vector has another behave
			m_vcapacity = m_vcapacity * 2;

			// allocate a new object with new capacity
			// the temporary pointer is needed in the next step
			T* ptr_tmp = static_cast<T*>(malloc(m_vcapacity * sizeof(T)));

			// copy the elements from the old array to the new array
			for (size_t i = 0; i < m_vsize; i++)
			{
				new(&ptr_tmp[i]) T(ptr_memArray[i]);
				ptr_memArray[i].~T();
			}
			// free the memory of the old array
			free(ptr_memArray);
			// set the pointer of the array to the new array
			ptr_memArray = ptr_tmp;
		}

	};
}