#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include "types.h"

template <typename Type>
class List final
{
private:
    struct chunk
    {
        Type m_obj;
        chunk *m_next = nullptr;
        chunk *m_prev = nullptr;
    };

    chunk *m_pLast = nullptr;
    chunk *m_pHead = nullptr;
    unsigned int m_size = 0;

    void fillHead(chunk *iterator)
    {
        m_pLast = iterator;

        while (iterator->m_next)
        {
            iterator = iterator->m_next;
        }

        m_pHead = iterator;
    }

public:
    //Создает пустой список
    List() = default;

    explicit List(const std::initializer_list<Type> &list) : m_size(list.size())
    {
        chunk *iterator = nullptr;

        for (const auto &x : list)
        {
            chunk *newObj = new chunk;

            if (iterator)
            {
                iterator->m_prev = newObj;
                newObj->m_next = iterator;
            }
            newObj->m_obj = x;
            iterator = newObj;
        }

        fillHead(iterator);
    }

    List(const List &other)
    {
        operator=(other);
    }

    List(List &&other)
    {
        operator=((List&&)other);
    }

    const List &operator=(const List &other)
    {
        m_size = other.m_size;

        if (other.m_size != 0)
        {
            chunk *otherLast = other.m_pLast;
            chunk *iterator = nullptr;

            while (otherLast)
            {
                chunk *newObj = new chunk;
                newObj->m_obj = otherLast->m_obj;

                if (iterator)
                {
                    iterator->m_prev = newObj;
                    newObj->m_next = iterator;
                }
                iterator = newObj;

                otherLast = otherLast->m_next;
            }

            fillHead(iterator);
        }
        return *this;
    }

    const List &operator=(List &&other)
    {
        m_pLast = other.m_pLast;
        m_pHead = other.m_pHead;
        m_size = other.m_size;

        other.m_pLast = nullptr;
        other.m_pHead = nullptr;
        other.m_size = 0;

        return *this;
    }

    //!true если list пустой
    bool empty() const
    {
        return m_size == 0;
    }

    int size() const
    {
        return m_size;
    }

    void clear()
    {
        if (!m_pHead)
        {
            return;
        }

        chunk *iterator = nullptr;

        while (m_pHead->m_prev)
        {
            iterator = m_pHead;
            m_pHead = m_pHead->m_prev;
            mem_delete(iterator);
        }

        mem_delete(m_pHead);

        m_pHead = nullptr;
        m_pLast = nullptr;
        m_size = 0;
    }

    void push_front(const Type &m_obj)
    {
        chunk *newObj = new chunk();
        newObj->m_obj = m_obj;
        newObj->m_prev = m_pHead;
        m_pHead->m_next = newObj;
        m_pHead = newObj;
    }

    void push_back(const Type &m_obj)
    {
        chunk *newObj = new chunk();
        newObj->m_obj = m_obj;
        newObj->m_next = m_pLast;
        m_pLast->m_prev = newObj;
        m_pLast = newObj;
    }

    ~List()
    {
        clear();
    }
};

#endif
