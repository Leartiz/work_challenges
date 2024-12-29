#ifndef SERVICES_H
#define SERVICES_H

#include <service/math_service.h>

namespace lez::service
{
    using namespace contract;

    struct Services final // pointer set!
    {
        Sp_math_service math_service;
        //...
    };
}

#endif // SERVICES_H
