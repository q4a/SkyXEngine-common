#ifndef LIST_H
#define LIST_H

#include <initializer_list>

template <typename Type>
class List final
{
private:
    struct chunk
    {
        Type obj;
        chunk* next = nullptr;
        chunk* prev = nullptr;
    };

    chunk* pLast;
    chunk* pHead;
    int size;

    void fillHead(chunk* iterator)
    {
        pLast = iterator;

        while (iterator->next)
        {
            iterator = iterator->next;
        }

        pHead = iterator;
    }

public:
    //Создает пустой список
    explicit List() : size(0), pHead(nullptr), pLast(nullptr)
    { }

    explicit List(const std::initializer_list<Type> & list) : size(list.size())
    {
        chunk* iterator = nullptr;

        for (const auto &x : list)
        {
            chunk* newObj = new chunk;

            if (iterator)
            {
                iterator->prev = newObj;
                newObj->next = iterator;
            }
            newObj->obj = x;
            iterator = newObj;
        }

        fillHead(iterator);
    }

    List(const List& other) : size(other.size)
    {
        if (other.size != 0)
        {
            chunk* otherLast = other.pLast;
            chunk* iterator = nullptr;

            while (otherLast)
            {
                chunk* newObj = new chunk;
                newObj->obj = otherLast->obj;

                if (iterator)
                {
                    iterator->prev = newObj;
                    newObj->next = iterator;
                }
                iterator = newObj;

                otherLast = otherLast->next;
            }

            fillHead(iterator);
        }
    }

    List(List&& other)
        : pLast(other.pLast), pHead(other.pHead), size(other.size)
    {
        other.pLast = nullptr;
        other.pHead = nullptr;
        other.size = 0;
    }

    //!true если в list пустой
    bool empty() const
    {
        return size == 0;
    }

    int size() const
    {
        return size;
    }

    void clear()
    {
        if (!pHead)
        {
            return;
        }

        chunk *iterator = nullptr;

        while (pHead->prev)
        {
            iterator = pHead;
            pHead = pHead->prev;
            delete iterator;
        }

        delete pHead;

        pHead = nullptr;
        pLast = nullptr;
        size = 0;
    }

    void push_front(Type & obj)
    {
        chunk* newObj = new chunk();
        newObj->obj = obj;
        newObj->prev = pHead;
        pHead->next = newObj;
        pHead = newObj;
    }

    void push_back(Type & obj)
    {
        chunk* newObj = new chunk();
        newObj->obj = obj;
        newObj->next = pLast;
        pLast->prev = newObj;
        plast = newObj;
    }
};

#endif
