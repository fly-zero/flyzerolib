#pragma once

#include <arpa/inet.h>

#include <memory>
#include <cassert>
#include <functional>

#include "file_descriptor.h"
#include "event_base.h"

namespace flyzero
{

    class tcp_server
        : public event_listener
    {
    public:
        tcp_server(void) = default;

        tcp_server(const tcp_server &) = default;

        tcp_server(tcp_server &&) = default;

        virtual ~tcp_server(void) = default;

        tcp_server & operator=(const tcp_server &) = default;

        tcp_server & operator=(tcp_server &&) = default;

        // listen on 0.0.0.0:port
        bool listen(const unsigned short port);

        file_descriptor accept(sockaddr_storage & addr, socklen_t & addrlen) const
        {
            assert(sizeof addr == addrlen);

            return file_descriptor(::accept4(sock_.Get(), reinterpret_cast<sockaddr *>(&addr), &addrlen, SOCK_NONBLOCK));
        }

        void close(void) { sock_.Close(); }

        virtual void on_accept(file_descriptor && sock, const sockaddr_storage & addr, socklen_t addrlen) = 0;

        bool on_read(void) override final;

        bool on_write(void) override final { return true; }

        void on_close(void) override final { }

        int get_fd(void) const override final { return sock_.Get(); }

    private:
        file_descriptor sock_;
    };

}
