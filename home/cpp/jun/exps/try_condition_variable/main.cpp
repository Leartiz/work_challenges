#include <iostream>
#include <chrono>

#include <string>
#include <queue>

#include <thread>
#include <atomic>
#include <mutex>

class Logger final
{
public:
    struct Msg final
    {
        using SysClock = std::chrono::system_clock;
        using Datetime = std::chrono::time_point<SysClock>;

        enum Severenity {
            inf, wrn, err, crt
        };

        Msg(const Severenity sl, std::string str)
            : sevlvl{ sl }, text{ std::move(str) } {}

        Datetime datetime;
        Severenity sevlvl;
        std::string text;
    };

public:
    Logger()
    {

    }

    ~Logger()
    {

    }

    void add_one(const Msg::Severenity s, const std::string& str)
    {
        {
            std::lock_guard<std::mutex> _(mx);
            msgs.push({ s, str });
        }
        cv.notify_one();



    }

private:
    std::queue<Msg> msgs;
    std::condition_variable cv;
    std::atomic_bool run;
    std::mutex mx;
};

int main()
{

    return 0;
}
