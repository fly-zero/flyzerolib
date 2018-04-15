#include <cerrno>
#include <iostream>

#include "epoll.h"

namespace flyzero
{

    void epoll::run(std::size_t const size, int const timeout, void(*on_timeout)(void *), void * arg) const
    {
        auto const events = new epoll_event[size];

        while (true)
        {
            const auto nev = epoll_wait(epfd_.get(), events, size, timeout);

            if (nev == -1)
            {
                if (errno == EINTR)
                    continue;
                break;
            }

            if (nev == 0)
            {
                if (on_timeout)
                    on_timeout(arg);
                continue;
            }

            for (auto i = 0; i < nev; ++i)
            {
                auto p = static_cast<epoll_listener *>(events[i].data.ptr);

                if (events[i].events & EPOLLIN)
                    p->on_read();

                if (events[i].events & EPOLLOUT)
                    p->on_write();

                if (events[i].events & EPOLLRDHUP)
                    p->on_close();
            }
        }

        delete[] events;
    }

}
