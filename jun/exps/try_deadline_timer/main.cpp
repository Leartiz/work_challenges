#include <QDebug>
#include <QString>

#include <vector>
#include <string>
#include <iostream>

#include <ctime>
#include <cstdlib>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace
{

char rnd_char() {
    static const char avb[] = "0123456789_abcdefghijklmnopqrstuvwxyz";
    const auto i = static_cast<size_t>(std::rand() % (sizeof(avb) - 1));
    return avb[i];
}

std::string rnd_str(const size_t sz = 10) {
    std::string res; res.reserve(sz);
    for (size_t i = 0; i < sz; ++i)
        res.push_back(rnd_char());
    return res;
}

const size_t dtim_secs = 3;

}

// -----------------------------------------------------------------------

struct Srv
{
    using ioc = boost::asio::io_context;

    using acr = boost::asio::ip::tcp::acceptor;
    using ep = boost::asio::ip::tcp::endpoint;
    using addr = boost::asio::ip::address;

    using sock = boost::asio::ip::tcp::socket;
    using ptr_sock = boost::shared_ptr<sock>;
    using dtim = boost::asio::deadline_timer;
    using ptr_dtim = boost::shared_ptr<dtim>;

    using err_code = boost::system::error_code;

    using str = std::string;
    using ptr_str = boost::shared_ptr<str>;

public:
    explicit Srv(ioc& ioc)
        : m_ioc{ ioc }, m_acr{ ioc, ep(addr::from_string("127.0.0.1"), 24446) } {}
    void start_reg() {
        ptr_sock s{ new sock{ m_ioc } };
        m_acr.async_accept(*s,
                           boost::bind(&Srv::handle_accept, this, s,
                                       boost::asio::placeholders::error)
                           );
    }

private:
    void reg_read(ptr_sock s) {
        using namespace boost::asio::placeholders;

        const ptr_dtim t{ new dtim{ m_ioc } };
        t->expires_from_now(boost::posix_time::seconds(dtim_secs));
        t->async_wait(boost::bind(&Srv::handle_wait, this,
                                     error, t, s)
                         );

        // ***

        const ptr_str msg{ new str(1024, 0) };
        s->async_read_some(boost::asio::buffer(*msg),
                           boost::bind(&Srv::handle_read, this,
                                       error, bytes_transferred, s, msg, t)
                           );
    }

    void reg_writ(ptr_sock s, ptr_str msg) {
        using namespace boost::asio::placeholders;

        const ptr_dtim t{ new dtim{ m_ioc } };
        t->expires_from_now(boost::posix_time::seconds(dtim_secs));
        t->async_wait(boost::bind(&Srv::handle_wait, this,
                                  error, t, s)
                      );

        // ***

        s->async_write_some(boost::asio::buffer(*msg),
                            boost::bind(&Srv::handle_writ, this,
                                        error, bytes_transferred, s, msg, t)
                            );
    }

private:
    void handle_accept(ptr_sock s, const err_code& err) {
        if (err) {
            std::cerr << "Srv, handle_accept, err: "
                      << err.message() << std::endl;
        }
        start_reg();

        // ***

        reg_read(s);
    }

    void handle_writ(const err_code& err, size_t, ptr_sock s, ptr_str, ptr_dtim t) {
        t->cancel();
        if (err) {
            std::cerr << "Srv, handle_writ, err: "
                      << err.message() << std::endl;
            return;
        }

        reg_read(s);
    }

    void handle_read(const err_code& err, size_t, ptr_sock s, ptr_str msg, ptr_dtim t) {
        t->cancel();
        if (err) {
            std::cerr << "Srv, handle_read, err: "
                      << err.message() << std::endl;
            return;
        }

        // unsafe conversion.
        qDebug() << QString(msg->c_str());

        const ptr_str msg_to_send{ new str{ rnd_str() } };
        qDebug() << QString::fromStdString(*msg_to_send);
        reg_writ(s, msg_to_send);
    }

    void handle_wait(const err_code& err, ptr_dtim, ptr_sock s) {
        if (err) {
            //std::cerr << "Srv, handle_wait, err: " << err.message() << std::endl;
            return;
        }

        qDebug() << "Timeout expired...";
        s->close();
    }

private:
    ioc& m_ioc;
    acr m_acr;
};

int main()
{
    std::srand(time(nullptr));
    Srv::ioc ioc;

    auto s = Srv(ioc);
    s.start_reg();

    qDebug() << "Server started...";

    ioc.run();
    return 0;
}
