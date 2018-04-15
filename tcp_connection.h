#pragma once

#include "file_descriptor.h"
#include "epoll.h"

namespace flyzero
{

    class tcp_connection
        : public epoll_listener
    {
    public:
        constexpr tcp_connection() = default;

        explicit tcp_connection(const file_descriptor & sock) noexcept
            : sock_(sock)
        {
        }

        explicit tcp_connection(file_descriptor && sock) noexcept
            : sock_(std::move(sock))
        {
        }

        tcp_connection(const tcp_connection &) = default;

        tcp_connection(tcp_connection &&) = default;

        virtual ~tcp_connection() = default;

        int get_fd() const noexcept override
        {
            return sock_.get();
        }

        bool operator<(const tcp_connection & other) const noexcept
        {
            return sock_ < other.sock_;
        }

    private:
        file_descriptor sock_;
    };

}
