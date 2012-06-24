// Class1.cpp
#include "pch.h"
#include "Class1.h"

#define _SCL_SECURE_NO_WARNINGS
#include "bitmap_image.hpp"
#include <string>
#include <ppltasks.h>

using namespace WindowsCampComponent;
using namespace std;
using namespace concurrency;
using namespace Windows::Storage;

Class1::Class1()
{
}

IAsyncOperation<IRandomAccessStream^>^ Class1::GetPlasmaImageAsync(unsigned int width, unsigned int height)
{
    auto createImageTask = create_task([width, height]() {
            const auto FILENAME = L"plasma.bmp";

            //create the image object
            bitmap_image image(width, height);
            image.clear();

            ::srand(0xA5AA5AA5);

            //generate plasma image
            plasma(image, 0, 0, image.width(), image.height(),
                0.9, 0.5, 0.3, 0.7, 3.0, jet_colormap);

            //get the temp filename
            auto tempFilePath = wstring(ApplicationData::Current->TemporaryFolder->Path->Data())
                .append(L"\\").append(FILENAME);

            //Save the image to the file
            image.save_image(string(begin(tempFilePath), end(tempFilePath)));

            return ref new String(FILENAME);
        }).then([](String^ filename) {
            return ApplicationData::Current->TemporaryFolder->GetFileAsync(filename);
        }).then([](StorageFile^ file) {
            return file->OpenAsync(FileAccessMode::Read);
        });

    return create_async([createImageTask]() { return createImageTask; });
}


