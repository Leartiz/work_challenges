#include "request_handler.h"

namespace lez::adapters::interfaces::tcp
{

Request_handler::Request_handler(Math_service& math_service)
    : m_math_service{ math_service }
{

}

}
