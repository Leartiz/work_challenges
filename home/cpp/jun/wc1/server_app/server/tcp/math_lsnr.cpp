#include <iostream>

#include <boost/bind.hpp>

#include "math_lsnr.h"

namespace lez
{
    namespace server
    {
        namespace tcp
        {
            using namespace std;

            namespace
            {
                math_lsnr::endpoint make_ep(const uint16_t port)
                {
                    return math_lsnr::endpoint(boost::asio::ip::tcp::v4(), port);
                }

                math_lsnr::endpoint make_ep(const std::string ipStr, const uint16_t port)
                {
                    const auto ip = boost::asio::ip::address::from_string(ipStr);
                    return math_lsnr::endpoint(ip, port);
                }
            } // impl

            // -------------------------------------------------------------------

            math_lsnr::math_lsnr(boost::asio::io_context& ioc, handler& h,
                const uint16_t port)
                : m_ioc{ ioc }, m_acr{ ioc, make_ep(port) }, m_hr{ h }
            {
                reg_accept();
            };

            math_lsnr::math_lsnr(io_context& ioc, handler& h,
                const str& ip, const uint16_t port)
                : m_ioc{ ioc }, m_acr{ ioc, make_ep(ip, port) }, m_hr{ h }
            {
                reg_accept();
            };

            math_lsnr::math_lsnr(io_context& ioc, handler& h, const endpoint& ep)
                : m_ioc{ ioc }, m_acr{ ioc, ep }, m_hr{ h }
            {
                reg_accept();
            };

            // -------------------------------------------------------------------

            void math_lsnr::reg_accept()
            {
                auto new_ccon = client_con::create(m_ioc, m_hr);
                m_acr.async_accept(new_ccon->sock(),
                    boost::bind(&math_lsnr::handle_accept, this, new_ccon,
                        boost::asio::placeholders::error));
            }

            void math_lsnr::handle_accept(client_con::ptr new_ccon,
                const boost::system::error_code& err)
            {
                if (err) {
                    std::cerr << "math_server, handle_accept, err: "
                        << err.message() << std::endl;
                }
                new_ccon->start();
                reg_accept();
            }
        }
    }
}