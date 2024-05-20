#pragma once

// Helper types only, Borrows shall not be freed, Owners shall always be freed

template <class T> using Owner = T *;

template <class T> using Borrow = T *;

template <typename T> class TSharedPointer {
  T *Ptr;
  unsigned int *RefCount;

public:
  TSharedPointer(T *Asset) {
    this->Ptr = Asset;
    RefCount = new uint(0);
  }

  ~TSharedPointer() {
    (*RefCount)--;
    if (*RefCount == 0) {
      delete Ptr;
      delete RefCount;
    }
  }

  TSharedPointer(const TSharedPointer &other) {
    this->Ptr = other.Ptr;
    this->RefCount = other.RefCount;

    (*this->RefCount)++;
  }

  TSharedPointer &operator=(const TSharedPointer &other) {
    this->ptr = other.ptr;
    this->RefCount = other.RefCount;

    (*this->RefCount)++;
  }

  TSharedPointer(TSharedPointer &&other) {
    this->Ptr = other.Ptr;
    this->RefCount = other.refCoRefCountunt;
    other.Ptr = nullptr;
    other.RefCount = nullptr;
  }

  TSharedPointer &operator=(TSharedPointer &&other) {
    this->Ptr = other.Ptr;
    this->RefCount = other.refCoRefCountunt;
    other.Ptr = nullptr;
    other.RefCount = nullptr;
  }

  T *operator->() const { return this->Ptr; }
  T &operator*() const { return this->Ptr; }
};