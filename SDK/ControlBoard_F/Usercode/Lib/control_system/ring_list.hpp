/**
 * @file ring_list.hpp
 * @author X. Y.
 * @brief 环形链表
 * @version 0.1
 * @date 2023-07-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <cstddef>

namespace control_system
{

template <typename T>
class RingList
{
private:
    typedef struct Node {
        T data;
        Node *next;
    } node_t;

    node_t *head;

    void Construct(size_t length)
    {
        if (length == 0) {
            length = 1;
        }

        head      = new node_t;
        Node *ptr = head;

        for (size_t i = length - 1; i > 0; i--) {
            ptr->next = new node_t;
            ptr       = ptr->next;
        }

        ptr->next = head;
    }

    void DeleteAll()
    {
        Node *ptr  = head;
        Node *next = ptr->next;

        while (next != head) {
            delete ptr;
            ptr  = next;
            next = ptr->next;
        }

        delete ptr;
        head = nullptr;
    }

public:
    /**
     * @brief Construct a new Ring List
     *
     * @param length 链表长度
     */
    RingList(size_t length = 1)
    {
        Construct(length);
    }

    /**
     * @brief head 指针往后移动一格（就像环形链表旋转一格）
     *
     * @return T& 移动后 head 所指的元素
     */
    T &spin()
    {
        head = head->next;
        return head->data;
    }

    /**
     * @brief 获取 head 所指的元素
     *
     */
    T &get()
    {
        return head->data;
    }

    /**
     * @brief 重设链表长度
     * @note 这会清除链表中已有的所有内容
     * @param size 新的长度
     */
    void resize(size_t size)
    {
        DeleteAll();
        Construct(size);
    }

    /**
     * @brief 把环形链表用 data 填满
     *
     */
    void fill(const T &data)
    {
        auto ptr = head;
        do {
            ptr->data = data;
            ptr       = ptr->next;
        } while (ptr != head);
    }

    ~RingList()
    {
        DeleteAll();
    }
};

} // namespace control_system
