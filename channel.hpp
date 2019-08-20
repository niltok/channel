#pragma once
#include <memory>

template <class T>
class channel {
    struct node {
        std::shared_ptr<node> next;
        std::unique_ptr<T> data;
    };
    std::shared_ptr<node> head;

   public:
    class listener {
        std::shared_ptr<node> ptr;
        const std::shared_ptr<node> &head;
        // 确保完全写入
        bool isBusy() { return head == ptr || ptr->next == nullptr; }

       public:
        listener(const std::shared_ptr<node> &p) : ptr(p), head(p) {}
        listener &operator>>(T &data) {
            while (isBusy())
                ;
            data = *(ptr->data);
            ptr = ptr->next;
            return *this;
        }
        T operator()() {
            while (isBusy())
                ;
            T data = *(ptr->data);
            ptr = ptr->next;
            return data;
        }
        std::unique_ptr<T> get() {
            if (isBusy()) return nullptr;
            std::unique_ptr<T> p {new T(*(ptr->data))};
            ptr = ptr->next;
            return std::move(p);
        }
    };
    channel() : head(std::make_shared<node>()) {}
    channel(const channel &) = delete;
    void operator=(const channel &) = delete;
    listener operator()() { return listener(head); }
    channel &operator<<(const T &data) {
        head->data = std::move(std::unique_ptr<T>(new T(data)));
        head->next = std::make_shared<node>();
        head = head->next;
        return *this;
    }
};