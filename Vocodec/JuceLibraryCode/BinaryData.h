/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   EuphemiaCAS_ttf;
    const int            EuphemiaCAS_ttfSize = 534712;

    extern const char*   gear_svg;
    const int            gear_svgSize = 811;

    extern const char*   logo_large_svg;
    const int            logo_large_svgSize = 5256;

    extern const char*   panel_svg;
    const int            panel_svgSize = 51239;

    extern const char*   snyderphonicswhitelogo_svg;
    const int            snyderphonicswhitelogo_svgSize = 9291;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
