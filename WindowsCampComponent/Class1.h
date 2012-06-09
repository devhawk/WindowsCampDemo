#pragma once

using namespace Platform;

namespace WindowsCampComponent
{
    public ref class Class1 sealed
    {
    public:
        Class1();

        String^ SayHello(String^ name) {
            return String::Concat(
                ref new String(L"Hello there "),
                name);
        };
    };
}