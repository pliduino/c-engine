template <typename T>
class TArray
{
private:
    T *Data = nullptr;
    size_t Size = 0;
    size_t Capacity = 0;

public:
    TArray(/* args */)
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

    // Access Operators
    T &operator[](int index)
    {
        return Data[index];
    }

    T operator[](int index) const
    {
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
