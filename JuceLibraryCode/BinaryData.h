/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   SONGS_ModalInterchange_wav;
    const int            SONGS_ModalInterchange_wavSize = 4233644;

    extern const char*   SONGS_ModalInterchange_json;
    const int            SONGS_ModalInterchange_jsonSize = 1117;

    extern const char*   SONGS_VariousChordTypes_wav;
    const int            SONGS_VariousChordTypes_wavSize = 2721644;

    extern const char*   SONGS_VariousChordTypes_json;
    const int            SONGS_VariousChordTypes_jsonSize = 675;

    extern const char*   SONGS_1625_json;
    const int            SONGS_1625_jsonSize = 1028;

    extern const char*   AUDIO_Stick_Count_wav;
    const int            AUDIO_Stick_Count_wavSize = 45630;

    extern const char*   SONGS_1625_wav;
    const int            SONGS_1625_wavSize = 2822444;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

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
