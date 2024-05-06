#pragma once

#include <aurora-engine/Assertion/Assertion.h>

template <typename T>
class TArray
{
private:
    T *Data;
    size_t Size;
    size_t Capacity;

public:
    TArray()
    {
        Capacity = 1;
        Size = 0;
        Data = new T[Capacity];
    };

    ~TArray()
    {
        delete[] Data;
    };

    void Add(T Value)
    {
        if (Size == Capacity)
        {
            GrowArray();
        }

        Data[Size++] = Value;
    }

    size_t GetSize()
    {
        return Size;
    }

    // Access Operators
    T &operator[](int index)
    {
        check(index > 0 && index < Size, "Tried accessing out of bounds, index: {}, size: {}", index, Size);
        return Data[index];
    }

    T operator[](int index) const
    {
        check(index > 0 && index < Size, "Tried accessing out of bounds, index: {}, size: {}", index, Size);
        return Data[index];
    }

    // Iterators
    T *begin() { return &Data[0]; }
    T *end() { return &Data[Size]; }
    const T *begin() const { return &Data[0]; }
    const T *end() const { return &Data[Size]; }

private:
    void GrowArray()
    {
        T *temp = new T[Capacity * 2];
        Capacity = Capacity * 2;
        for (size_t i = 0; i < Size; i++)
        {
            temp[i] = Data[i];
        }

        delete[] Data;

        Data = temp;
    }
};
