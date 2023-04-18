#include "application.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string_view>

int main()
{
    try
    {
        auto application{std::make_unique<glforge::Application>(1024, 768, "App Demo")};
        application->run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
    }

    return 0;
}