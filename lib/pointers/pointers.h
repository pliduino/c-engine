// Helper types only, Borrows shall not be freed, Owners shall always be freed

template <class T>
using Owner = T *;

template <class T>
using Borrow = T *;