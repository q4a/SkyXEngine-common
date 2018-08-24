
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#ifndef Array_H
#define Array_H

#include <new>
#include "sxtypes.h"

/*
	¬нимание:
		Ёлемент массива не имеет гарантированного расположени¤ в пам¤ти.
*/

/*#ifdef S4G
template <typename T, int BlockSize = 16>
class s4g_Stack;

#endif*/

template<typename T, int BlockSize=16>
class Array
{
public:
	Array():Size(0),AllocSize(0),Data(NULL)
	{
		Alloc();
	}

	Array(const Array & arr):Size(0), AllocSize(0), Data(NULL)
	{
		Alloc();
		//this->AllocSize = arr.AllocSize;
		//this->Size = arr.Size;
			for(int i = arr.Size - 1; i >= 0; i--)
			{
				(*this)[i] = arr[i];
			}
	}

	inline void swap(Array &arr)
	{
		UINT tmpS = Size;
		Size = arr.Size;
		arr.Size = tmpS;

		tmpS = AllocSize;
		AllocSize = arr.AllocSize;
		arr.AllocSize = tmpS;

		void * tmpD = Data;
		Data = arr.Data;
		arr.Data = (T*)tmpD;
	}

	inline void resize(UINT NewSize)
	{
		Realloc(NewSize);
		//ConstructInterval(this->Size, key);
			if(this->Size < NewSize)
			{
				ConstructInterval(this->Size, NewSize - 1);
			}
		this->Size = NewSize;
	}

	inline void reserve(UINT size)
	{
		Realloc(size);
	}

	inline UINT size() const
	{
		return(Size);
	}

	inline void push_back(const T & data)
	{
		(*this)[this->Size] = data;
	}

	inline void erase(UINT key)
	{
			/*if(key < 0)
			{
				_asm
				{
					int 3;
				};
			}*/

			if(key < this->Size)
			{
				(&this->Data[key])->~T();
				if(key < this->Size - 1)
				{
					memcpy(&this->Data[key], &this->Data[key + 1], sizeof(T)* (this->Size - key - 1));
				}
				this->Size--;
			}
			else
			{
				_asm
				{
					int 3;
				};
			}
	}

	//inline Array & operator=(T* arr)
	//{
		//this->AllocSize = arr.AllocSize;
		//this->Size = arr.Size;
			/*for(int i = arr.Size - 1; i >= 0; i--)
			{
				(*this)[i] = arr[i];
			}*/
	//	return(*this);
	//}

	inline Array & operator=(const Array<T, BlockSize> & arr)
	{
		//this->AllocSize = arr.AllocSize;
		//this->Size = arr.Size;
		if(arr.Size < this->Size)
		{
			DestructInterval(arr.Size, this->Size - 1);
			this->Size = arr.Size;
		}
		for(int i = arr.Size - 1; i >= 0; i--)
		{
			(*this)[i] = arr[i];
		}
		return(*this);
	}

	inline T & operator[](UINT key)
	{
		if(key > ((UINT)-1) - 128)
		{

		}
			if(key >= this->Size)
			{
					if(key >= this->AllocSize)
					{
						Realloc(max(this->AllocSize, key) + BlockSize);
					}
				ConstructInterval(this->Size, key);
				this->Size = key + 1;
			}
		return(Data[key]);
	}


	inline T & GetKeyOC(UINT key)
	{
		return(Data[key]);
	}

	inline void SetKeyOC(UINT key, T& val)
	{
		Data[key] = val;
	}

	inline const T & operator[](UINT key) const
	{
			if(key >= this->Size)
			{
				/*_asm
				{
					int 3;
				};*/
				//SkyXEngine::Core::InError("exit in array");
			}
		return(Data[key]);
	}
	

	~Array()
	{
			if(Size)
			{
				DestructInterval(0, Size - 1);
			}
		free(Data);
	}

	inline void clear()
	{
			if(Size)
			{
				DestructInterval(0, Size - 1);
			}
		free(Data);
		Size = 0;
		AllocSize = 0;
		Data = NULL;
		Alloc();
	}

	inline void clearFast()
	{
		if(Size)
		{
			DestructInterval(0, Size - 1);
		}
		Size = 0;
	}

	inline UINT GetAllocSize()
	{
		return AllocSize;
	}

	template <typename L>
	void quickSort(const L& CompareFunc)
	{
		//don't sort 0 or 1 elements
		if(size()>1)
		{
			quickSortInternal(CompareFunc, 0, size() - 1);
		}
	}


protected:
	/*
#ifdef S4G
	friend s4g_Stack<T, BlockSize>;
#endif*/
	inline void Alloc()
	{
		Realloc(BlockSize);
	}

	inline void Realloc(UINT NewSize)
	{
		T * tmpData = (T*)malloc(sizeof(T) * NewSize);
		memcpy(tmpData, this->Data, min(NewSize, this->Size) * sizeof(T));
			if(this->Size > NewSize)
			{
				DestructInterval(NewSize, this->Size - 1);
				this->Size = NewSize;
			}
		
		this->AllocSize = NewSize;
		T * tmpDel = this->Data;
		this->Data = tmpData;
		free(tmpDel);
	}

	inline void ConstructInterval(UINT start, UINT end)
	{
		//this->Data + start = new(this->Data + start) T[end - start + 1];
			for(UINT i = start; i <= end; i++)
			{
				new(&this->Data[i]) T;
			}
	}

	inline void DestructInterval(UINT start, UINT end)
	{
			for(UINT i = start; i <= end; i++)
			{
				(&this->Data[i])->~T();
			}
	}



	template <typename L>
	void quickSortInternal(const L& CompareFunc, int lo, int hi)
	{
		//  lo is the lower index, hi is the upper index
		//  of the region of array a that is to be sorted
		int i = lo, j = hi;
		T x = Data[(lo + hi) / 2];

		//  partition
		do
		{
			while(CompareFunc(Data[i], x))
				i++;
			while(CompareFunc(x, Data[j]))
				j--;
			if(i <= j)
			{
				swap(i, j);
				i++; j--;
			}
		}
		while(i <= j);

		//  recursion
		if(lo<j)
			quickSortInternal(CompareFunc, lo, j);
		if(i<hi)
			quickSortInternal(CompareFunc, i, hi);
	}
	void swap(int index0, int index1)
	{
		T temp = Data[index0];
		Data[index0] = Data[index1];
		Data[index1] = temp;
	}

	T * Data;

	UINT Size;
	UINT AllocSize;
};


#endif
