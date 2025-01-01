#ifndef MESSAGE_CREATOR_H
#define MESSAGE_CREATOR_H

#include "dto/response.h"

namespace lez::adapters::interfaces::tcp
{

class Message_creator final
{
public:
    Message_creator();
    std::string create(dto::Sp_response response) const;
};

}

#endif // MESSAGE_CREATOR_H
