/*
 * Copyright (C) 2010 Codership Oy <info@codership.com>
 */

#ifndef GCOMM_ASIO_PROTONET_HPP
#define GCOMM_ASIO_PROTONET_HPP

#include "gcomm/protonet.hpp"
#include "socket.hpp"

#include "gu_monitor.hpp"

#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <asio.hpp>

#include <vector>
#include <deque>
#include <list>

namespace gcomm
{
    class AsioProtonet;
}


class gcomm::AsioProtonet : public gcomm::Protonet
{
public:

    AsioProtonet(gu::Config& conf, int version = 0);
    ~AsioProtonet();
    void event_loop(const gu::datetime::Period& p);
    void dispatch(const SocketId&,
                  const gu::Datagram&,
                  const ProtoUpMeta&);
    void interrupt();
    SocketPtr socket(const gu::URI&);
    gcomm::Acceptor* acceptor(const gu::URI&);
    void enter();
    void leave();
    size_t get_mtu() const { return mtu_; }

private:

    friend class AsioTcpSocket;
    friend class AsioTcpAcceptor;
    friend class AsioUdpSocket;
    AsioProtonet(const AsioProtonet&);

    void handle_wait(const asio::error_code& ec);

    gu::RecursiveMutex          mutex_;
    gu::datetime::Date          poll_until_;
    asio::io_service            io_service_;
    asio::deadline_timer        timer_;

    size_t                      mtu_;
    bool                        checksum_;
};

#endif // GCOMM_ASIO_PROTONET_HPP
