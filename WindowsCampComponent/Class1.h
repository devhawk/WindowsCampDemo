#pragma once

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;

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

        IAsyncOperation<IRandomAccessStream^>^ GetPlasmaImageAsync(unsigned int width, unsigned int height);
    };
}