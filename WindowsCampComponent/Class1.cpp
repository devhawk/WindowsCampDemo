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
    //get the temp filename
    auto tempFolder = ApplicationData::Current->TemporaryFolder;

    wstring tempFolderPath(tempFolder->Path->Data());
    string folderPath(begin(tempFolderPath), end(tempFolderPath));

    auto filePath = folderPath.append("\\plasma.bmp");

    //create the image object
    bitmap_image image(width, height);
    image.clear();

    double c1 = 0.9;
    double c2 = 0.5;
    double c3 = 0.3;
    double c4 = 0.7;

    ::srand(0xA5AA5AA5);

    //generate plasma image
    plasma(image,0,0,image.width(),image.height(),c1,c2,c3,c4,3.0,jet_colormap);

    //Save the image to the file
    image.save_image(filePath);

    //reopen the image file using WinRT
    task<StorageFile^> getFileTask(tempFolder->GetFileAsync(ref new String(L"plasma.bmp")));

    return create_async(
        [getFileTask]() -> task<IRandomAccessStream^> {
            return getFileTask.then([](StorageFile^ storageFile) {
                return storageFile->OpenAsync(FileAccessMode::Read);
            });
    });
}


