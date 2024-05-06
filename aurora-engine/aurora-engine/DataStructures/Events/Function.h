#pragma once

template <typename Return, typename... Args>
class TFunction
{

public:
    Return (*FunctionPointer)(Args...) = nullptr;

    TFunction(){};
    TFunction(Return (*func)(Args...)) : FunctionPointer{func} {}

    virtual Return operator()(Args... args)
    {
        return FunctionPointer(args...);
    }
};

template <class C, typename Return, typename... Args>
class TBoundFunction : public TFunction<Return, Args...>
{
    Return (C::*FunctionPointer)(Args...) = nullptr;
    C *BoundObject = nullptr;

public:
    TBoundFunction(){};
    TBoundFunction(C *Object, Return (C::*func)(Args...)) : FunctionPointer{func}, BoundObject{Object} {}

    void test(){};

    virtual Return operator()(Args... args) override
    {
        return (BoundObject->*FunctionPointer)(args...);
    }
};