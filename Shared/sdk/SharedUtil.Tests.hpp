/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        SharedUtil.Tests.hpp
 *  PURPOSE:
 *
 *
 *
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

// Fwd decl
void SString_Tests();
void SharedUtil_File_Tests();
void SharedUtil_ClassIdent_Tests();
void SharedUtil_WildcardMatch_Tests();
void SharedUtil_Collection_Tests();
void SharedUtil_String_Tests();
void SharedUtil_Hash_Tests();

///////////////////////////////////////////////////////////////
//
// Run tests entry point
//
//
//
///////////////////////////////////////////////////////////////
void SharedUtil_Tests()
{
    SString_Tests();
    SharedUtil_File_Tests();
    SharedUtil_ClassIdent_Tests();
    SharedUtil_WildcardMatch_Tests();
    SharedUtil_Collection_Tests();
    SharedUtil_String_Tests();
    SharedUtil_Hash_Tests();
}

///////////////////////////////////////////////////////////////
//
// Helper macros
//
//
//
///////////////////////////////////////////////////////////////
#define TEST_FUNCTION \
        struct testStruct { \
            void Test(int testIndex) \
            { \
                testStruct dataCopy = *this;    // Info when debugging

#define TEST_VARS \
            }

#define TEST_DATA \
        } testData[]

#define TEST_END \
        for (uint i = 0 ; i < NUMELMS(testData) ; i++) \
            testData[i].Test(i);

///////////////////////////////////////////////////////////////
//
// SString_Tests
//
// Tests for functions from SString.hpp
//
///////////////////////////////////////////////////////////////
void SString_Tests()
{
    // vFormat
    {
        TEST_FUNCTION
        assert(SString(a, b, c) == result);
        TEST_VARS
        const char* a;
        const char* b;
        int         c;
        const char* result;
        TEST_DATA = {
            {"XX%sAA%dBB", "la", 0, "XXlaAA0BB"},
            {"XX%sAA%dBB", "laQWE", 2000, "XXlaQWEAA2000BB"},
        };
        TEST_END
    }

    // Split
    {
        TEST_FUNCTION
        SString strLeft, strRight;
        assert(source.Split(delim, &strLeft, &strRight, index) == result);
        assert(strLeft == resultLeft);
        assert(strRight == resultRight);
        TEST_VARS
        SString     source;
        const char* delim;
        int         index;
        bool        result;
        const char* resultLeft;
        const char* resultRight;
        TEST_DATA = {
            {"a.b.c.d.e", ".", 1, true, "a", "b.c.d.e"},
            {"a.b.c.d.e", ".", 2, true, "a.b", "c.d.e"},
            {"a.b.c.d.e", ".", -2, true, "a.b.c", "d.e"},
        };
        TEST_END
    }

    // Split
    {
        TEST_FUNCTION
        std::vector<SString> parts;
        source.Split(delim, parts, maxAmmount, minAmmount);
        assert(parts.front() == resultFirst);
        assert(parts.back() == resultLast);
        assert(parts.size() == resultCount);
        TEST_VARS
        SString     source;
        const char* delim;
        uint        maxAmmount;
        uint        minAmmount;
        const char* resultFirst;
        const char* resultLast;
        uint        resultCount;
        TEST_DATA = {
            {"hello", ".", 0, 0, "hello", "hello", 1},
            {"a.#b.#c.#d.#e", ".#", 0, 0, "a", "e", 5},
        };
        TEST_END
    }

    // SplitLeft
    // SplitRight

    // Replace
    {
        TEST_FUNCTION
        assert(source.Replace(needle, newneedle) == result);
        TEST_VARS
        SString     source;
        const char* needle;
        const char* newneedle;
        const char* result;
        TEST_DATA = {
            {"blah1234blah", "la", "QwE", "bQwEh1234bQwEh"},
            {"blah1234blah", "blah", "", "1234"},
            {"blahblah1234", "blah", "", "1234"},
            {"1234blahblah", "blah", "", "1234"},
            {"1234blAhblaH", "BLah", "", "1234blAhblaH"},
            {"blah1234blah", "LA", "QwE", "blah1234blah"},
            {"blah1234blah", "blAh", "", "blah1234blah"},
            {"blah////blah", "//", "/", "blah//blah"},
        };
        TEST_END
    }

    // Replace with option
    {
        TEST_FUNCTION
        assert(source.Replace(needle, newneedle, bSearchJustReplaced) == result);
        TEST_VARS
        SString     source;
        const char* needle;
        const char* newneedle;
        bool        bSearchJustReplaced;
        const char* result;
        TEST_DATA = {
            {"blah////blah", "//", "/", false, "blah//blah"},
            {"blah////blah", "//", "/", true, "blah/blah"},
        };
        TEST_END
    }

    // ReplaceI
    {
        TEST_FUNCTION
        assert(source.ReplaceI(needle, newneedle) == result);
        TEST_VARS
        SString     source;
        const char* needle;
        const char* newneedle;
        const char* result;
        TEST_DATA = {
            {"blah1234blah", "la", "QwE", "bQwEh1234bQwEh"},
            {"blah1234blah", "blah", "", "1234"},
            {"blahblah1234", "blAh", "", "1234"},
            {"1234blAhblaH", "BLah", "", "1234"},
            {"blah1234blah", "LA", "QwE", "bQwEh1234bQwEh"},
            {"blah1234blah", "blAh", "", "1234"},
        };
        TEST_END
    }

    // TrimStart
    // TrimEnd
    // ToLower
    // ToUpper
    // ConformLineEndings
    // Contains
    // ContainsI
    // SubStr
    // Left
    // Right
    // EndsWith
    // EndsWithI
    // BeginsWith
    // BeginsWithI

    // Join
    {
        TEST_FUNCTION
        std::vector<SString> parts;
        source.Split(",", parts);
        assert(SString::Join(delim, parts, first, count) == result);
        TEST_VARS
        SString source;
        SString delim;
        int     first;
        int     count;
        SString result;
        TEST_DATA = {
            {"", "/", 0, 999, ""},
            {"A", "/", 0, 999, "A"},
            {"A,B", "/", 0, 999, "A/B"},
            {"A,B,C,D,E", "/", 0, 999, "A/B/C/D/E"},
            {"A,B,C,D,E", "/", -5, 7, "A/B"},
            {"", "/", 0, 0, ""},
            {"A", "/", 0, 0, ""},
            {"A,B", "/", 0, 0, ""},
            {"A,B,C,D,E", "/", 0, 0, ""},
            {"", "/", 0, 1, ""},
            {"A", "/", 0, 1, "A"},
            {"A,B", "/", 0, 1, "A"},
            {"A,B,C,D,E", "/", 0, 1, "A"},
            {"", "/", 0, 2, ""},
            {"A", "/", 0, 2, "A"},
            {"A,B", "/", 0, 2, "A/B"},
            {"A,B,C,D,E", "/", 0, 2, "A/B"},
            {"", "/", 1, 2, ""},
            {"A", "/", 1, 2, ""},
            {"A,B", "/", 1, 2, "B"},
            {"A,B,C,D,E", "/", 1, 2, "B/C"},
            {"A,B,C,D,E", "/", 1, 4, "B/C/D/E"},
            {"A,B,C,D,E", "/", 1, 5, "B/C/D/E"},
        };
        TEST_END
    }
}

///////////////////////////////////////////////////////////////
//
// SharedUtil_File_Tests
//
// Tests for functions from SharedUtil.File.hpp
//
///////////////////////////////////////////////////////////////
void SharedUtil_File_Tests()
{
#ifdef WIN32

    // PathJoin 2 parts
    {
        TEST_FUNCTION
        assert(PathJoin(a, b) == result);
        TEST_VARS
        const char* a;
        const char* b;
        const char* result;
        TEST_DATA = {
            {"///\\\\\\/\\/\\/\\/blah/\\/\\/\\", "////\\\\/////\\/fleeb///\\\\///\\/\\", "\\\\blah\\fleeb\\"},
            {"blah/\\/\\/\\", "////\\\\/////\\/fleeb", "blah\\fleeb"},
            {"blah", "fleeb", "blah\\fleeb"},
        };
        TEST_END
    }

    // PathJoin 3 parts
    {
        TEST_FUNCTION
        assert(PathJoin(a, b, c) == result);
        TEST_VARS
        const char* a;
        const char* b;
        const char* c;
        const char* result;
        TEST_DATA = {
            {"/blah/", "/\\fl\\eeb/", "//fleeeb/", "\\blah\\fl\\eeb\\fleeeb\\"},
            {"blah/", "/fl//eeb", "\\fleeeb", "blah\\fl\\eeb\\fleeeb"},
            {"blah", "fleeb", "fleeb", "blah\\fleeb\\fleeb"},
        };
        TEST_END
    }

    // UNC type tests
    {
        TEST_FUNCTION
        assert(PathJoin(a, b) == result);
        TEST_VARS
        const char* a;
        const char* b;
        const char* result;
        TEST_DATA = {
            {"//blah/", "//fleeeb/", "\\\\blah\\fleeeb\\"},
            {"//?/blah/", "//fleeeb/", "\\\\?\\blah\\fleeeb\\"},
            {"//?/C:\blah/", "//fleeeb/", "\\\\?\\C:\blah\\fleeeb\\"},
            {"///?/C:\blah/", "//fleeeb/", "\\\\?\\C:\blah\\fleeeb\\"},
            {"file://blah/", "//fleeeb/", "file:\\\\blah\\fleeeb\\"},
            {"file:///blah\\/", "//fleeeb/", "file:\\\\blah\\fleeeb\\"},
            {"fil:e///blah\\/", "//fleeeb/", "fil:e\\blah\\fleeeb\\"},
            {"fi/le:///blah\\/", "//fleeeb/", "fi\\le:\\blah\\fleeeb\\"},
            {"c:///blah\\/", "//fleeeb/", "c:\\blah\\fleeeb\\"},
        };
        TEST_END
    }

#endif  // WIN32
}

///////////////////////////////////////////////////////////////
//
// SharedUtil_ClassIdent_Tests
//
// Tests for macros in SharedUtil.ClassIdent.h
//
///////////////////////////////////////////////////////////////
void SharedUtil_ClassIdent_Tests()
{
#if WIN32
    // Setup
    enum eTestClassTypes
    {
        CLASS_SPlant,
        CLASS_STree,
        CLASS_SFlower,
        CLASS_SBlueBell,
        CLASS_SDaffodil,
    };

    struct SPlant
    {
        DECLARE_BASE_CLASS(SPlant)
        SPlant() : ClassInit(this) {}
    };

    struct STree : SPlant
    {
        DECLARE_CLASS(STree, SPlant)
        STree() : ClassInit(this) {}
    };

    struct SFlower : SPlant
    {
        DECLARE_CLASS(SFlower, SPlant)
        SFlower() : ClassInit(this) {}
    };

    struct SBlueBell : SFlower
    {
        DECLARE_CLASS(SBlueBell, SFlower)
        SBlueBell() : ClassInit(this) {}
    };

    struct SDaffodil : SFlower
    {
        DECLARE_CLASS(SDaffodil, SFlower)
        SDaffodil() : ClassInit(this) {}
    };

    // Create test data
    SPlant*    pPlant = new SPlant();
    STree*     pTree = new STree();
    SFlower*   pFlower = new SFlower();
    SBlueBell* pBlueBell = new SBlueBell();
    SDaffodil* pDaffodil = new SDaffodil();

    // Tests
    assert(DynamicCast<SPlant>(pPlant));
    assert(DynamicCast<SPlant>(pTree));
    assert(DynamicCast<SPlant>(pFlower));
    assert(DynamicCast<SPlant>(pBlueBell));
    assert(DynamicCast<SPlant>(pDaffodil));

    assert(!DynamicCast<STree>(pPlant));
    assert(DynamicCast<STree>(pTree));

    assert(!DynamicCast<SFlower>(pPlant));
    assert(DynamicCast<SFlower>(pFlower));
    assert(DynamicCast<SFlower>(pBlueBell));
    assert(DynamicCast<SFlower>(pDaffodil));

    assert(!DynamicCast<SBlueBell>(pPlant));
    assert(!DynamicCast<SBlueBell>(pFlower));
    assert(DynamicCast<SBlueBell>(pBlueBell));

    assert(!DynamicCast<SDaffodil>(pPlant));
    assert(!DynamicCast<SDaffodil>(pFlower));
    assert(DynamicCast<SDaffodil>(pDaffodil));

    // Create test data
    SPlant*  pPlantTree = pTree;
    SPlant*  pPlantFlower = pFlower;
    SPlant*  pPlantBlueBell = pBlueBell;
    SPlant*  pPlantDaffodil = pDaffodil;
    SFlower* pFlowerBlueBell = pBlueBell;
    SFlower* pFlowerDaffodil = pDaffodil;

    // Tests
    assert(DynamicCast<SPlant>(pPlantTree));
    assert(DynamicCast<SPlant>(pPlantFlower));
    assert(DynamicCast<SPlant>(pPlantBlueBell));
    assert(DynamicCast<SPlant>(pPlantDaffodil));
    assert(DynamicCast<SPlant>(pFlowerBlueBell));
    assert(DynamicCast<SPlant>(pFlowerDaffodil));

    assert(DynamicCast<STree>(pPlantTree));
    assert(!DynamicCast<STree>(pPlantFlower));
    assert(!DynamicCast<STree>(pPlantBlueBell));
    assert(!DynamicCast<STree>(pPlantDaffodil));

    assert(!DynamicCast<SFlower>(pPlantTree));
    assert(DynamicCast<SFlower>(pPlantFlower));
    assert(DynamicCast<SFlower>(pPlantBlueBell));
    assert(DynamicCast<SFlower>(pPlantDaffodil));
    assert(DynamicCast<SFlower>(pFlowerBlueBell));
    assert(DynamicCast<SFlower>(pFlowerDaffodil));

    assert(!DynamicCast<SBlueBell>(pPlantTree));
    assert(!DynamicCast<SBlueBell>(pPlantFlower));
    assert(DynamicCast<SBlueBell>(pPlantBlueBell));
    assert(!DynamicCast<SBlueBell>(pPlantDaffodil));
    assert(DynamicCast<SBlueBell>(pFlowerBlueBell));
    assert(!DynamicCast<SBlueBell>(pFlowerDaffodil));

    assert(!DynamicCast<SDaffodil>(pPlantTree));
    assert(!DynamicCast<SDaffodil>(pPlantFlower));
    assert(!DynamicCast<SDaffodil>(pPlantBlueBell));
    assert(DynamicCast<SDaffodil>(pPlantDaffodil));
    assert(!DynamicCast<SDaffodil>(pFlowerBlueBell));
    assert(DynamicCast<SDaffodil>(pFlowerDaffodil));

    // Check ClassBits type is at least 64 bits
    assert(sizeof(ClassBits) * 8 >= 64);

    // Cleanup
    delete pPlant;
    delete pTree;
    delete pFlower;
    delete pBlueBell;
    delete pDaffodil;
#endif
}

///////////////////////////////////////////////////////////////
//
// SharedUtil_WildcardMatch_Tests
//
// Tests for WildcardMatch
//
///////////////////////////////////////////////////////////////
void SharedUtil_WildcardMatch_Tests()
{
    // WildcardMatch
    {
        TEST_FUNCTION
        assert(WildcardMatch(a, b) == result);
        TEST_VARS
        const char* a;
        const char* b;
        bool        result;
        TEST_DATA = {
            {"*bd*", "abcbde", true},
            {"*bd?f*", "abcbdef_bdgh", true},
            {"*bd?h*", "abcbdef_bdgh", true},
            {"*bd?g*", "abcbdef_bdgh", false},
            {"scr*w?d", "screeeewywxd", true},
            {"A*B", "A_B_B", true},
            {"", "", true},
            {"*", "", true},
            {"*", "A", true},
            {"", "A", false},
            {"A*", "", false},
            {"A*", "AAB", true},
            {"A*", "BAA", false},
            {"A*", "A", true},
            {"A*B", "", false},
            {"A*B", "AAB", true},
            {"A*B", "AB", true},
            {"A*B", "AABA", false},
            {"A*B", "ABAB", true},
            {"A*B", "ABBBB", true},
            {"A*B*C", "", false},
            {"A*B*C", "ABC", true},
            {"A*B*C", "ABCC", true},
            {"A*B*C", "ABBBC", true},
            {"A*B*C", "ABBBBCCCC", true},
            {"A*B*C", "ABCBBBCBCCCBCBCCCC", true},
            {"A*B*", "AB", true},
            {"A*B*", "AABA", true},
            {"A*B*", "ABAB", true},
            {"A*B*", "ABBBB", true},
            {"A*B*C*", "", false},
            {"A*B*C*", "ABC", true},
            {"A*B*C*", "ABCC", true},
            {"A*B*C*", "ABBBC", true},
            {"A*B*C*", "ABBBBCCCC", true},
            {"A*B*C*", "ABCBBBCBCCCBCBCCCC", true},
            {"A?", "AAB", false},
            {"A?B", "AAB", true},
            {"A?*", "A", false},
            {"A?*", "ABBCC", true},
            {"A?*", "BAA", false},
        };
        TEST_END
    }
}

///////////////////////////////////////////////////////////////
//
// SharedUtil_Collection_Tests
//
// Test behaviour of iterators and such
//
///////////////////////////////////////////////////////////////
void SharedUtil_Collection_Tests()
{
    // std::map
    {
        std::map<uint, SString> testMap;
        MapSet(testMap, 10, "10");
        MapSet(testMap, 20, "20");
        MapSet(testMap, 30, "30");
        MapSet(testMap, 40, "40");

        std::map<uint, SString>::iterator iter = testMap.begin();
        assert(iter->first == 10);
        iter++;
        assert(iter->first == 20);
        iter++;
        testMap.erase(iter++);
        assert(iter->first == 40);
        iter++;
        assert(iter == testMap.end());
    }

    // std::set
    {
        std::set<uint> testMap;
        MapInsert(testMap, 10);
        MapInsert(testMap, 20);
        MapInsert(testMap, 30);
        MapInsert(testMap, 40);

        std::set<uint>::iterator iter = testMap.begin();
        assert(*iter == 10);
        iter++;
        assert(*iter == 20);
        iter++;
        testMap.erase(iter++);
        assert(*iter == 40);
        iter++;
        assert(iter == testMap.end());
    }

    // std::list
    {
        std::list<uint> testList;
        testList.push_back(10);
        testList.push_back(20);
        testList.push_back(30);
        testList.push_back(40);

        std::list<uint>::iterator iter = testList.begin();
        assert(*iter == 10);
        iter++;
        assert(*iter == 20);
        iter++;
        iter = testList.erase(iter);
        assert(*iter == 40);
        iter++;
        assert(iter == testList.end());
    }

    // std::vector
    {
        std::vector<uint> testList;
        testList.push_back(10);
        testList.push_back(20);
        testList.push_back(30);
        testList.push_back(40);

        std::vector<uint>::iterator iter = testList.begin();
        assert(*iter == 10);
        iter++;
        assert(*iter == 20);
        iter++;
        iter = testList.erase(iter);
        assert(*iter == 40);
        iter++;
        assert(iter == testList.end());
    }
}

///////////////////////////////////////////////////////////////
//
// SharedUtil_String_Tests
//
// Test behaviour of strings
//
///////////////////////////////////////////////////////////////
void SharedUtil_String_Tests()
{
    // Formatting
    {
        SString strTemp1("name:" PRSinS, "dave");
        SString strTemp2("name:" PRWinS, L"dave");
        WString wstrTemp3(L"name:" PRSinW, "dave");
        WString wstrTemp4(L"name:" PRWinW, L"dave");

        assert(strTemp1 == "name:dave");
        assert(strTemp2 == "name:dave");
        assert(wstrTemp3 == L"name:dave");
        assert(wstrTemp4 == L"name:dave");
    }

    // To/From Ansi
    {
        SString strTemp1 = "abcABC 123";
        WString wstrTemp2 = "defDEF 456";
        WString wstrTemp3 = L"ghiGHI 789";

        assert(wstrTemp2 == L"defDEF 456");

        SString strTemp2 = wstrTemp2.ToAnsi();
        SString strTemp3 = wstrTemp3.ToAnsi();

        assert(strTemp2 == "defDEF 456");
        assert(strTemp3 == "ghiGHI 789");
    }

    // Escaping URL arguments
    {
        TEST_FUNCTION
        SStringX strInputA((const char*)a, sizeof(a));
        SString  strEscaped = EscapeURLArgument(strInputA);
        SString  strUnescaped = UnescapeString(strEscaped, '%');
        assert(strEscaped == result);
        assert(strInputA == strUnescaped);
        TEST_VARS
        const uchar a[5];
        const char* result;
        TEST_DATA = {
            {{0x00, 0x10, 0x20, 0x21, 0x22}, "%00%10%20%21%22"},
            {{0x7F, 0x80, 0x81, 0xFE, 0xFF}, "%7F%80%81%FE%FF"},
        };
        TEST_END
    }

    {
        TEST_FUNCTION
        SStringX strInputA(a);
        SString  strEscaped = EscapeURLArgument(strInputA);
        SString  strUnescaped = UnescapeString(strEscaped, '%');
        assert(strEscaped == result);
        assert(strInputA == strUnescaped);
        TEST_VARS
        const char* a;
        const char* result;
        TEST_DATA = {
            {"!*'();:@", "%21%2A%27%28%29%3B%3A%40"},
            {"&=+$,/?#", "%26%3D%2B%24%2C%2F%3F%23"},
            {"[] \"%<>\\", "%5B%5D%20%22%25%3C%3E%5C"},
            {"^`{|}", "%5E%60%7B%7C%7D"},
            {"AZaz09-_.~", "AZaz09-_.~"},
        };
        TEST_END
    }

    // RemoveColorCodes
    {
        TEST_FUNCTION
        SString strRemoved = RemoveColorCodes(a);
        assert(strRemoved == result);
        TEST_VARS
        const char* a;
        const char* result;
        TEST_DATA = {
            {"aa #0f0F34 bb", "aa  bb"},
            {"aa #0f0F34#AABBBB bb", "aa  bb"},
            {"aa #0f0F3G#AABBBB bb", "aa #0f0F3G bb"},
            {"aa #0f0F34#AABBB bb", "aa #AABBB bb"},
            {"#0f0F34#AABBB1", ""},
            {"#0f0F34 x #AABBB1", " x "},
            {"#0f0F34#0f0F34 x #AABBB1#AABBB1", " x "},
            {"#123456#12345G#123456#12345G", "#12345G#12345G"},
            {"#123456#12345#123456#125G", "#12345#125G"},
            {"##123456#125G##123456#12345", "##125G##12345"},
        };
        TEST_END
    }

    // RemoveColorCodesInPlaceW
    {
        TEST_FUNCTION
        WString wstrString = a;
        RemoveColorCodesInPlaceW(wstrString);
        assert(wstrString == result);
        TEST_VARS
        const wchar_t* a;
        const wchar_t* result;
        TEST_DATA = {
            {L"aa #0f0F34 bb", L"aa  bb"},
            {L"aa #0f0F34#AABBBB bb", L"aa  bb"},
            {L"aa #0f0F3G#AABBBB bb", L"aa #0f0F3G bb"},
            {L"aa #0f0F34#AABBB bb", L"aa #AABBB bb"},
            {L"#0f0F34#AABBB1", L""},
            {L"#0f0F34 x #AABBB1", L" x "},
            {L"#0f0F34#0f0F34 x #AABBB1#AABBB1", L" x "},
            {L"#123456#12345G#123456#12345G", L"#12345G#12345G"},
            {L"#123456#12345#123456#125G", L"#12345#125G"},
            {L"##123456#125G##123456#12345", L"##125G##12345"},
        };
        TEST_END
    }
}

///////////////////////////////////////////////////////////////
//
// SharedUtil_Hash_Tests
//
// Test behaviour of hashing/crypt related functions
//
///////////////////////////////////////////////////////////////
void SharedUtil_Hash_Tests()
{
    // ConvertHexStringToData/ConvertDataToHexString
    {
        TEST_FUNCTION
        char buffer[256];
        uint length = a.length() / 2;
        ConvertHexStringToData(a, buffer, length);
        SString strResult = ConvertDataToHexString(buffer, length);
        assert(strResult == b);
        TEST_VARS
        const SString a;
        const char*   b;
        TEST_DATA = {
            {"66B9139D8C424BE2BCF224706B48FEB8", "66B9139D8C424BE2BCF224706B48FEB8"},
            {"E7C7253C74275F2DC2DC8C6828816C18301636949369F3bad87666C81E71B309", "E7C7253C74275F2DC2DC8C6828816C18301636949369F3BAD87666C81E71B309"},
            {"61", "61"},
            {"\x01"
             "A"
             "\x1F\x80"
             "BC"
             "\xFE\xFF",
             "0A00BC00"},
        };
        TEST_END
    }

    // TeaEncode/TeaDecode
    {
        TEST_FUNCTION
        SString strEncoded;
        TeaEncode(a, b, &strEncoded);
        if (!result.empty())
            assert(strEncoded == result);
        SString strDecoded;
        TeaDecode(strEncoded, b, &strDecoded);
        assert(a == *strDecoded);
        TEST_VARS
        const SString a;
        const SString b;
        const SString result;
        TEST_DATA = {
            {"1234", "AB12£$_ ", "\xD2\xB4\x75\x5C\xDC\x15\x54\xC9"},
            {"Hello thereHello there", "78111E998C42243285635E39AFDD614B\0 AB12£$_ ", ""},
            {"78111E998C42243285635E39AFD\0D614B AB12£$_ ", "Hello thereHello there", ""},
        };
        TEST_END
    }

    // RSA keypair generation and encryption test
    {
        TEST_FUNCTION
        auto keyPair = GenerateRsaKeyPair(keysize);
        assert(!keyPair.privateKey.empty());
        assert(!keyPair.publicKey.empty());
        SString encryptedData = RsaEncode(data, keyPair.publicKey);
        assert(!encryptedData.empty());
        SString decryptedData = RsaDecode(encryptedData, keyPair.privateKey);
        assert(!decryptedData.empty());
        assert(data == decryptedData);
        TEST_VARS
        const SString data;
        const int     keysize;
        TEST_DATA = {
            {"Hello world", 1024},
            {"!@#$%^&*()_+|:<>", 2048},
            {"Hello there", 4096},
        };
        TEST_END
    }

    // RSA decryption test
    {
        TEST_FUNCTION
        SString decryptedData = RsaDecode(encryptedData, privateKey);
        assert(!decryptedData.empty());
        assert(exptectedData == decryptedData);
        TEST_VARS
        const SString exptectedData;
        const SString encryptedData;
        const SString privateKey;
        TEST_DATA = {
            {"Hello world",
             "\xC3\x27\xC6\x2A\x80\xF6\x4C\xBA\xAC\x43\xD0\x6E\xFA\x60\x9A\x32\xDC\x77\x37\x0A\x93\x5E\xFD\x6C\x2C\xCD\x47\xEC\xD0\x86\x26\xF9\x1B\xF5\xE6\x89"
             "\x4B\xBF\x76\x0E\x96\x80\xFA\xD4\xDE\x45\x8A\x3C\xF7\x82\xA5\xB2\x8D\xD9\x30\x9B\x5C\x4B\x9F\xA7\x7A\x07\x6C\xC0\x45\x97\x2A\x7D\x29\x5F\xD3\x56"
             "\xE2\xEC\x6C\x50\xC2\x79\xDF\xD3\x13\xB7\x59\xD9\x4C\xE4\x35\x7A\xCE\x46\x47\xB5\x7B\x2C\x47\x95\xA7\x8E\xE8\xCD\xD8\x5E\xE1\x6F\x8D\x86\x6F\x1D"
             "\xCC\x53\x1A\xB9\xEA\x76\xB8\x63\x48\x41\xC6\x69\x1D\x00\xED\x2A\x8F\x6A\xD2\xF8",
             "\x30\x82\x02\x74\x02\x01\x00\x30\x0D\x06\x09\x2A\x86\x48\x86\xF7\x0D\x01\x01\x01\x05\x00\x04\x82\x02\x5E\x30\x82\x02\x5A\x02\x01\x00\x02\x81\x81"
             "\x00\xEB\xAF\x92\x6C\x06\x34\xE1\x22\x18\xCA\x1D\xE6\x33\x43\x94\x2F\x65\x20\x1C\x2F\x48\xDD\x8F\xC1\x3E\x11\xBD\x52\xB6\xFE\x6D\x71\x90\xA3\x42"
             "\x97\x68\x4D\xA7\x14\xFB\xF9\x74\xF5\x8B\x5F\xEE\x8C\x7E\x80\xCC\x69\x45\x2A\x8E\xCB\x70\x88\x31\xCD\xFC\x0F\xE8\xD9\xFC\x9C\x5E\x71\x1B\x6A\xE1"
             "\x69\xA3\x33\xBE\xC2\x5D\xB4\x99\x8A\xAF\x10\xFB\xF4\x64\x1A\x8E\xE5\x3E\x86\x3E\xE4\x92\x32\x85\x85\x1B\x78\x70\x79\x7A\xC9\x87\x28\xC6\xEF\x7F"
             "\x35\xF2\x3B\xA4\x39\x53\x17\xDB\x79\x0B\x7B\x9E\xCB\x10\xB5\xC1\x25\x19\x26\x5C\x9B\x02\x01\x11\x02\x81\x80\x53\x2E\xE8\x62\x5C\x8B\x22\x48\x44"
             "\xFC\x0A\x8D\x7B\x81\x43\x5C\x05\x92\xDC\xC5\x65\x02\xE7\x71\x61\x33\x6F\xFF\x13\x68\xDB\x55\x42\x1B\x80\xEA\x24\xD0\x1C\xDA\x3A\xD0\x83\xA1\xF4"
             "\xF4\xAE\x8B\xF0\x69\xB1\x8E\x90\xE1\xD8\x0B\x91\x21\x02\x84\xEF\x8D\x25\x00\xF7\x01\x75\xEE\x0A\xD8\xC5\x04\x06\x4D\xBF\x18\x83\x03\x84\x4F\xA9"
             "\x44\xF6\x45\xCD\x14\xE4\xEA\x48\x3B\x38\x5D\x05\x53\xD5\xBA\xCB\x5F\xD9\xB6\x68\x62\x66\xE3\x80\x6F\xA0\x5B\x2F\xC0\xF6\x46\xFA\x00\x7B\x2A\x77"
             "\x7C\xE6\xB1\xDC\x06\x9C\xB7\x45\x32\xF6\x31\x02\x41\x00\xFC\x05\xB0\x03\xFC\x2E\xE1\xF7\xD3\x6E\x60\x9C\x3F\x96\xDF\xAC\x1B\xE0\x41\x54\x0C\x8D"
             "\xB5\x11\xA4\xD2\x13\xB2\xBB\x18\x5D\x37\x16\x1A\x2E\x9D\x6C\xF2\xB0\xB3\xB3\x16\x29\x5B\x87\x98\xE3\xD2\x5F\x09\x63\xD8\x1C\x37\x0B\x33\xB0\x15"
             "\xBC\x3A\x34\xC8\x91\x0B\x02\x41\x00\xEF\x67\xE0\x4A\xAB\x2B\x26\x91\x13\x3E\x6B\x60\xAA\xE9\x18\x52\x33\x98\x00\xDA\x92\x7C\x51\x3B\xCD\x0C\x60"
             "\xD4\xF2\xAC\xA0\x12\x1A\x79\x59\x01\xE6\x15\x5D\x9B\x27\xF2\x64\xD8\x0E\x00\x06\x9D\xDA\x62\x6F\xFD\xF2\x0D\x5B\x4A\x1B\xE2\x9E\x38\xF5\xA2\xBC"
             "\xB1\x02\x41\x00\x85\x6C\x6C\x3E\x58\x55\x0E\x37\xE8\x67\x9C\x8E\xF4\x7D\x0D\x00\xC3\x76\xB9\x2C\x7F\x1D\xD8\x54\xA2\x8D\x55\xB8\xF9\xA3\x7C\xA4"
             "\xB1\x59\x27\xBC\xC1\x35\x30\x5F\x22\x93\x43\x12\x56\xD8\x78\x9C\x8C\xAA\x9E\x45\x3C\x1D\x24\x0C\x4E\x29\x9F\xE2\x94\x6A\x2E\xAB\x02\x40\x46\x69"
             "\xD8\x8E\x6E\x94\x38\x85\x05\xA8\xF2\x67\xB9\xCC\x16\x36\x4B\x68\xF1\x31\x3A\x24\x90\x5C\xE1\xF4\x94\xF3\x56\x6F\x01\xE7\x34\xF6\x83\x97\x25\x8D"
             "\xD0\x3C\xB1\x65\x68\xF4\x40\x5A\x5C\x4C\x8B\x86\x5D\x2C\x92\x7C\x66\x24\xDB\x06\x6A\xC5\x75\x6C\x19\x61\x02\x40\x2D\xB2\x72\xA7\x10\x03\x24\x9D"
             "\xEF\x3C\x64\x07\x4B\xC7\xB0\x6C\x55\xDF\xF8\x93\xF7\xFE\x6B\x2A\x3A\x19\xC8\xA1\x7E\x08\x6E\x89\x18\x9D\x86\x2A\x5C\x95\x54\x99\x9F\xF1\x86\xA0"
             "\xC8\xFA\xC6\x32\x38\xB9\x73\xDF\xE4\xAE\xE3\xB8\x72\x63\x32\x5F\xD3\x2B\x57\x72"},
            {"!@#$%^&*()_+|:<>",
             "\x80\x5E\xFE\x2C\x89\x0E\x9A\x94\x92\x81\x01\xA5\xF0\xD0\x26\x7A\x96\x10\xB0\xA0\x37\x47\x78\xCE\xE0\x1E\x4E\x12\x8C\x8E\x08\xCA\x30\x61\xD8\xC6"
             "\xC1\x20\x2A\xB5\x80\x0C\x7C\xDB\x11\x9D\x07\x55\x00\x95\xB6\x29\x86\x72\x63\xCE\x3C\x78\xEA\x97\xD5\xE4\xEB\x47\xBD\x78\xC1\x40\xA3\x65\xA3\x5A"
             "\xAB\x59\x95\x42\x4C\x50\xBA\x6E\x78\xA7\xCB\xD2\x21\x28\xD9\x65\x6C\x29\x21\xCF\xEC\x96\xD4\x7F\xFA\x3D\x32\x51\x3D\x9E\x91\xBA\x08\xFE\xFF\x54"
             "\x6D\xC9\x8D\x77\x84\x35\x39\x32\x52\x7A\x7D\xE0\x92\xC1\x02\x81\xAC\x18\xD2\xA4\x02\xB9\x67\x3B\x10\x93\x26\x6D\xDC\x3B\x9C\xFA\x2E\xA9\x31\xC9"
             "\xB7\x76\xEB\xF9\x0C\x05\x7E\xAA\x10\xB3\x10\xFF\xFC\xAA\x65\x10\x2E\x87\x0E\xE0\x89\x32\x05\xEA\x6F\x21\x59\xB5\xE1\xCC\xBE\x9D\x21\xC0\xC8\x4A"
             "\xAF\xAF\xA3\x0E\xAB\x55\xFB\x5D\x49\x61\x03\x5D\x5E\x69\x23\xDA\x6A\x38\x2F\xEF\x66\xAB\x0F\x30\xE7\x0D\x93\xD7\xED\x02\x7A\xA8\x60\xD0\x42\xEA"
             "\xFF\x91\xDB\x5F\x98\x76\xEF\x74\xF0\x9E\x43\x16\xBD\x07\xCB\xC9\xB4\xD4\xA8\xDA\xB8\x14\xEA\x45\xC4\x1D\x6E\xFC\x3F\x63\x1A\x68\xB8\x3D\xCF\x80"
             "\xA2\xED\x1B\x9E",
             "\x30\x82\x04\xBA\x02\x01\x00\x30\x0D\x06\x09\x2A\x86\x48\x86\xF7\x0D\x01\x01\x01\x05\x00\x04\x82\x04\xA4\x30\x82\x04\xA0\x02\x01\x00\x02\x82\x01"
             "\x01\x00\xA6\xCD\x6E\x4A\x58\xBA\x48\x86\xAC\x00\x73\x19\x77\xD6\x12\x4C\x21\x6C\xD1\x6C\xB2\xDA\xB8\xD3\x1A\x0B\x23\x9D\x53\x55\x8C\x9D\xC3\x2B"
             "\x75\xFA\x02\x11\x5C\x9B\x5A\xE0\x34\xEB\x79\x65\x53\x7D\xD1\x1E\xB4\xF4\xC4\xB5\x19\x0D\xE0\xC9\x87\xD1\x20\x53\x79\xF0\xD8\x1F\xA5\xBA\x3D\x46"
             "\x1D\xA7\x37\x12\x8C\x67\x52\x26\x92\xFE\x68\xF1\x99\x80\x66\x9C\x85\xDA\x90\xA2\x02\x8E\x3B\x80\x2C\x16\xD3\xC9\xEC\xB3\xF4\xAF\xEE\xAC\x85\x1F"
             "\xCD\x2A\x78\x13\x90\xF3\x66\x10\xF9\xD4\x48\x5B\x02\xB8\x91\x94\xDD\xA5\xEE\xB1\x8A\x08\x4A\xBE\x96\x54\x47\x3D\x43\xE5\x2E\xDF\xDE\x55\x4D\xC9"
             "\x0E\x3D\xCE\xD1\x86\x9B\x8B\x1F\xE9\xB7\xE8\x29\x3D\x27\xEC\x50\x95\x22\x59\x2D\xF4\x61\x88\x0F\xBE\xEF\xCD\x07\x2A\xBC\x49\xB4\x3B\xD4\x67\x86"
             "\x56\x3B\xA8\xB8\x31\x7A\x41\x8D\xF5\x66\x9B\xE9\x87\x97\xF7\xF0\xA5\xFB\xF6\x37\x9A\xA0\x7C\xE7\xCD\x02\xD8\xD8\x21\xC0\x66\xCD\x5A\x09\xAA\x33"
             "\x06\x17\xC9\x16\xC3\x47\xE4\xBE\x2C\xA9\x67\x66\x5C\x65\x66\x7C\x09\xF8\x34\x7C\x24\xF7\xE8\x6F\x2C\x3C\xBE\x6A\xED\xDC\x14\xF5\xFB\xC0\x34\x8B"
             "\x7C\x70\xB2\x31\xA0\xEB\x02\x01\x11\x02\x82\x01\x00\x1D\x6F\x8B\xEF\x00\x99\x58\x17\xC4\x00\x14\x4F\xC9\xDA\x7B\xB3\x14\xF5\x15\xE6\x01\x71\xE4"
             "\x61\x7D\x11\x06\x48\xF0\x96\xA0\x58\x13\x62\x05\xC2\xB5\x12\x1F\x66\xB5\xAF\x18\x65\xCA\x20\xF0\x9D\xBB\x7D\xE3\xB2\xB9\x4D\x22\x89\xFA\x7D\xEA"
             "\xCA\x8D\x3B\xE8\x57\xAD\xAB\x3B\x5D\x19\xDF\x32\x68\xCD\x7B\xBE\x6C\x96\x06\xCE\xA5\x5D\xD0\x48\x43\xD5\xDF\x62\xEA\x55\xC2\x3C\xAF\xB0\x25\xAD"
             "\x6D\x70\xAB\x29\xC5\x67\x6A\x57\x4B\x9F\x05\x9C\xAD\x24\x3F\xB0\x2A\xF3\xE4\xE0\xCB\x1B\xD3\xD3\x4D\xBF\x56\x81\x77\xA2\x97\xCD\x10\x3C\x8B\x5C"
             "\x8F\x52\xEC\x29\x07\xBC\x24\x6A\xAA\xA6\x6E\xF4\xDD\x5F\x2F\x42\x24\xAE\x93\xC1\xD1\x9A\x6E\xDE\x50\xB9\xE3\x3D\x46\xFA\x39\xFC\xFA\x2C\xF3\x7A"
             "\xF9\x40\xC8\x08\x45\xFA\xC0\x06\xEB\xB3\x32\xC7\x6E\x9B\xDD\x69\x62\x59\xD8\xC7\xA5\xB0\x25\x68\xF3\x93\xF6\x86\x76\x67\xE4\x39\xE3\xDF\x78\xB5"
             "\x90\xC6\x93\x33\xE1\xEC\x23\x32\xEA\x22\xD9\x1B\x13\xEE\x6D\x78\xA0\xA9\xC8\x83\x2D\xC0\x04\x92\xC8\x80\x12\x6F\xF3\xAC\x7E\x6E\xA2\x29\xEA\xB3"
             "\xFF\x49\x24\x39\x8C\xBC\xDC\x97\xA9\x1E\x00\x71\xD0\x24\x42\x4C\x61\x02\x81\x81\x00\xC0\x7E\xCF\xDC\xC9\x63\xA3\x8A\x55\x3C\x07\x17\xAF\xAF\x9A"
             "\xD9\x76\x4F\x13\x40\xA5\x5C\x8C\x38\x34\x32\x12\x8D\x9A\xE8\xDD\xFC\x69\xC3\xBD\xC8\xCE\xCC\x21\xA3\xDE\x76\x7E\x15\x39\x0C\x39\xB4\xFD\x83\x3C"
             "\xF9\x5E\x4C\x89\xC9\xC8\xAB\x03\x9E\x59\xF0\xB1\xD5\x6E\x90\xA7\x0D\x5E\x95\xD2\xE5\xBC\xBC\x8F\x6D\x88\x5C\xEE\x93\x4F\xCE\x90\x5B\xFC\x57\xF1"
             "\x6F\x1E\xAD\x39\x76\xE5\x82\x66\xC2\xD3\xC2\xF1\x6A\x0B\x60\x23\x80\x98\x37\x98\xFC\xAF\x65\x86\x7F\x98\x7C\xDD\x9D\x4C\x41\x9B\x0A\x9C\x08\x3F"
             "\xCB\xB7\x16\x34\x73\x02\x81\x81\x00\xDD\xD4\xB9\xF5\xFD\x4A\x0D\x2F\x04\xD5\x7A\xCB\xEE\xFA\x07\xD3\x3D\x21\x51\xE0\x5D\xD3\x68\x86\x9E\x2D\x94"
             "\x26\x34\x0A\xB1\x3E\x65\x76\xF2\x64\x65\x35\x39\xC7\x7F\x78\x7D\xC5\x2E\x67\xDA\xE7\xC7\xE3\x59\xCF\x81\xDA\x52\x83\x26\x6B\xDB\xC8\x06\x7A\x2D"
             "\xB3\x98\x40\x5A\x4F\xA0\x3F\x2A\x5A\x23\x29\xE3\x60\xEB\x39\x0D\x2C\xDC\xE1\xFE\x7E\xE8\x62\x25\xE2\x63\x52\x88\xED\x3D\x20\xDE\x8D\xFE\x34\x2B"
             "\x35\xDA\xB3\x6C\x12\xCA\xCD\x6E\x64\x4B\x82\x54\x6B\xDC\xCB\x74\xCB\xEF\xD2\x5A\xA1\xEE\x80\xB7\xB4\x2D\xA3\xBB\xA9\x02\x81\x80\x43\xF0\x85\x99"
             "\x38\x05\x0C\x8B\x2D\x24\x3E\xBD\x10\xD4\x91\x01\x75\x0C\xD9\x9E\x58\x7B\x04\x50\x12\x6C\x06\x8C\x54\xCA\xA8\xB3\x70\x9F\x70\x28\xC1\x75\x39\x0C"
             "\xA8\xDE\x86\xDA\x50\x5E\xAA\xF4\x95\xB5\xD9\x48\xF4\x1B\x03\x74\x64\xF1\x10\x56\x01\xA0\x3E\xC3\xCC\xAB\x86\x40\xF4\x34\xE1\x05\xCA\x24\x6E\xDB"
             "\x5D\x4D\xF9\xD9\xA3\xB2\x51\x11\x68\x1F\x09\xEA\xFB\xC4\xAA\xDE\xAB\x5B\x33\x53\xD2\x44\xCD\xAC\xF4\xF4\xC1\x3C\x71\xF5\x81\x4A\x1F\xC9\x7A\xC3"
             "\x9F\x3B\x21\x0A\x57\x26\x36\xB8\x73\x4E\x34\xA2\x40\x9E\x6C\xDD\x02\x81\x80\x68\x64\x1B\x46\x95\x50\x06\x34\x3E\x82\x94\x23\xBB\xC0\xF4\x9F\xA4"
             "\x4B\xEA\x4B\x77\x72\x8B\x8A\xA4\xCA\x27\x99\x81\xE6\xE9\xFF\x3E\xCE\x90\x2F\x3E\xAF\xA2\xB8\x3B\xFC\x77\x6B\xD9\x9A\x48\xE5\x8B\x3D\xCF\xE9\x2E"
             "\x0C\x63\x10\x8A\x8D\x1C\x21\xE4\xEE\x33\x9F\xCF\x2D\x57\xAD\x00\x1D\xB9\x93\xD4\x4F\xF2\x87\xF6\x38\xF7\x24\x2B\xB5\xA4\xF0\x6D\x5B\x5D\x1F\x3D"
             "\xCC\x7C\xAB\xE0\x87\xF0\x42\xD1\xFA\x6E\xAF\xEE\x72\x8D\x36\x05\x15\x61\x20\x23\x88\xA0\x32\xC2\x41\xA0\x5F\xF8\x62\xFD\x79\x61\x2D\x83\xA0\x15"
             "\x7A\x3A\x31\x02\x81\x80\x69\xBF\x31\x7B\x42\xB9\xFE\x8C\xF4\x35\x4F\x08\xD4\x26\x6C\x30\x6E\x7B\x60\x7D\x36\xC5\xA7\x1B\xF2\x12\xED\x3E\x8A\x41"
             "\x44\xA2\x0B\xE9\x39\x53\x17\x7D\x0D\x64\xB4\x95\x97\x5F\x05\xB6\x49\xF1\x53\x82\xC4\xD8\x47\xB0\x29\x79\x0B\x69\x54\x04\x2C\x3D\xB5\x35\x7B\x31"
             "\xCD\x1C\x18\x4F\xDA\x50\xE3\xD3\x83\x8B\xB8\xF2\x4E\x2B\xD0\xBD\xF9\xFC\x42\xD0\xBC\x3B\x4C\xF2\xBE\x60\xC0\x8E\x36\x2F\x13\x6E\x66\xED\x20\x9E"
             "\x97\x7D\xFD\x32\x20\x78\xB5\xE1\xC2\x54\x40\xBE\xBF\x0C\x39\x1C\x32\x60\x2E\x5C\xFB\x6D\xE8\x6A\xBB\xD4"},
            {"Hecker there",
             "\x59\xCE\x09\x28\xEE\x11\xBB\xCE\x9A\x3E\x60\x24\x16\x2B\xA0\x71\x33\x10\x3E\xD1\x2D\x05\xF9\xF7\x97\x40\xCE\x9F\xEF\x93\xA6\xBB\x54\xA0\x0A\xB9"
             "\x90\x3E\x05\x61\x82\x77\x58\x2C\xA6\x90\xC3\xDE\x4D\x0C\x57\xDC\xD2\xDD\x85\x89\x60\x45\x96\xF0\xD0\x52\x01\x2F\x60\xA3\xB8\xB1\x79\x76\x57\x8E"
             "\x33\xB2\x41\x07\xC6\x8F\xE5\x0C\x0B\x65\x3C\x9F\xE9\x7F\x85\x52\x73\x28\xFA\xF7\x0A\xB4\x8C\x3A\x39\x4D\x59\xE1\xFC\x04\x0B\xCA\x79\xA0\xCF\x59"
             "\x1A\x9C\x42\x39\xA9\x9C\xC2\x0D\x08\xF8\xE8\xC9\xF8\x9C\x5F\x90\xA3\x97\x8C\xA1\x50\xD0\x84\xA6\x7B\xE6\x6D\x6E\x1D\xAD\x7D\xBE\xB9\x4A\x72\xD1"
             "\x35\xCF\x12\x63\x2C\x35\xFC\x29\x6E\x76\xB9\x40\x02\xE8\x9A\x1A\x61\x1C\x9B\x02\xE0\x66\x8C\xAD\x5D\xFB\x64\x6A\x66\xE5\xF2\x19\x8C\xC5\x5A\xCB"
             "\x42\xB8\x08\x26\x0D\x1B\xD1\xBB\x04\xD2\x3B\x82\xF2\xC4\x27\x9D\x39\xCB\xAF\x59\x76\x52\x3F\x3C\xA1\x9C\x02\xFB\xF9\xF1\x6E\x07\x5F\xAD\x7D\x9C"
             "\xCE\x66\xC9\x24\xEA\xF3\x18\x7A\x0A\x03\x09\x13\xB0\xCF\x1D\x2A\xDE\xDE\x3F\x77\xB5\xC0\x70\x51\x0A\x66\x30\x98\x67\x43\x2E\x6B\x23\x12\x03\x91"
             "\x42\x5B\x55\x20\x9F\xE7\x6A\x38\x00\x90\xFB\xD8\x1C\x09\xBD\x8D\x50\xC8\xA1\xEE\xEE\x40\xFA\x37\x19\x71\xAF\x5B\x2D\xB5\xC6\xE1\x69\xEF\x5A\x23"
             "\x06\xC8\xBC\x57\x13\x21\x3E\x9D\x4E\xBC\xEF\xD3\x1F\x17\xF9\x89\x86\xF0\xF1\x46\x17\x7F\xE9\x7E\x2A\xA3\xB6\x2A\x1C\x23\x33\x87\xF8\x17\x6E\x13"
             "\x6A\xDA\x08\xBD\x8F\xFA\x90\x29\x93\x65\xF5\x52\xCF\x96\x46\xF9\x43\x0A\x32\x6A\x8C\x90\x19\xD2\x24\x0F\x93\xED\x5F\x4C\x93\x3E\xC8\xFB\x08\x0D"
             "\xEC\x65\x8A\x85\x0F\x47\xE7\x46\x0C\x52\x77\x1B\x1D\xDE\xA6\x22\xCF\x6F\x03\xCA\x5B\x64\x52\xC0\xFC\x50\x83\x60\x51\x11\xDA\x27\x67\x16\x27\x0B"
             "\xB7\xC4\x95\x04\x5E\x75\x35\x3D\xC4\x64\xDB\xD0\xE6\xB4\xAD\xD9\x43\x44\x15\x64\x41\xAE\xF7\x4E\x06\x91\x5E\x8A\x25\x1E\x49\x03\x8D\x76\x80\xA6"
             "\xC3\x5C\xB3\x62\x9A\x48\x0A\xF7\x97\x10\x2D\xC2\x69\xB7\x96\xF4\xF8\x29\x3E\x0A\x71\x03\x6E\x54\x4A\x2E\x4F\xA2\xCC\x68\x33\x45\x55\xA0\xC5\x74"
             "\xB9\xA1\xC6\x77\xDA\x9C\x85\x55\x95\x53\xC2\x21\x5A\x2B\x8B\xA2\x54\x8E\xA2\x23\xC7\xE3\xE6\xC3\x31\x74\x9F\x39\x8D\x12\x72\x14\xB2\x8A\x39\x2A"
             "\x23\xA8\x51\xFE\xD5\x48\x1B\xEF",
             "\x30\x82\x09\x41\x02\x01\x00\x30\x0D\x06\x09\x2A\x86\x48\x86\xF7\x0D\x01\x01\x01\x05\x00\x04\x82\x09\x2B\x30\x82\x09\x27\x02\x01\x00\x02\x82\x02"
             "\x01\x00\xCF\x13\x00\xE9\x59\x75\x3A\x7C\x0F\xA0\x89\x19\xD0\x26\x81\x88\x70\xF4\xD4\xA4\x57\x30\xC6\xC4\xCD\xA4\x63\x6D\xEA\x2F\x26\xFB\x72\xDA"
             "\x21\x74\x5A\x69\xE1\x1C\x1D\x18\x39\x89\x6F\xBB\x6E\x8E\xD3\xEC\xA2\xB5\x96\x53\x2D\xE0\x1F\x4D\x9F\x77\x52\x77\x1D\xB6\x53\xC0\x54\x59\xE9\xB6"
             "\xC2\xCD\x4A\x14\xE6\xA6\xF8\x61\x83\x24\xD9\x22\x47\xF0\x19\x0D\xFA\x42\x25\x3F\xD3\x62\xB0\xCF\x52\x01\x82\xE9\x1B\xC8\x6E\xC8\xAC\xD9\xAD\x25"
             "\x27\xE6\xBA\x92\xA8\xE7\xC8\xE6\xF2\x30\xB3\x31\x2D\x54\xA4\x0F\xFE\xF4\xC4\x38\xB7\xB9\xB9\x0A\x77\xA5\xAA\xDB\xFD\x69\xC1\x6D\xB5\x93\xBB\xC8"
             "\xF0\x04\x81\x99\x9C\x26\x6F\x99\x92\x24\xE0\x0D\xD3\x56\x6C\xE5\xCB\xEE\x5F\xA5\x55\xFB\xAD\x3B\x11\x44\xE6\xA5\x63\x03\xBC\x67\xD4\x75\x5D\xD2"
             "\xC8\xCB\x8C\x9D\x1D\xBA\x98\x2B\xDE\x62\x5C\x6A\x32\x44\xC9\xD9\x76\x8D\xEB\xBB\x9F\x65\x6F\x99\x88\xE6\x72\xD7\xA6\x95\xCA\x7D\x4B\xAB\x25\xC7"
             "\xAD\x93\x38\xCA\x41\x66\x5B\x19\x9F\x61\xDC\x99\x8F\x0F\x5B\x26\x05\xB0\x47\xCD\x88\xBC\x29\x3B\xAA\x81\x0F\xC8\x21\xF6\x09\x79\x2D\xF8\xA1\xB0"
             "\xD2\x34\xB1\x98\xA4\x07\xBD\x8D\x03\xAE\xBA\xFF\x50\xD7\x7E\x3D\x22\xBE\x6B\xF4\x0B\xBE\xA8\xF6\x45\x86\x09\x0D\x05\x49\x4B\xCA\xF6\xFE\x46\x3E"
             "\x3C\x6C\x0F\xDF\x99\x1F\xB5\x99\x49\x40\xED\x48\xC5\x95\x1B\x77\xC6\xD7\xA8\xE6\x4E\xCE\x49\x85\x07\xBE\x16\x5D\xA2\xDA\xD5\x12\xF0\x6B\x99\x78"
             "\x0D\x8B\x58\xF1\xB9\x07\xB2\xB7\x9C\x84\x1D\x1E\x5E\x95\x55\xFC\xF9\xF9\xDE\x11\x74\xB9\x8A\x15\xF5\x74\x13\x12\x30\xF0\xC1\x0C\xAF\xAE\x1F\xF9"
             "\x78\x8A\x7C\x50\x93\xE6\xF8\x47\xB0\xA4\xB9\xD6\x4B\x53\x62\x81\x87\xAA\x8B\xB3\xFF\x4B\x27\x70\x62\x01\x4D\xFE\xB0\x0D\x00\xED\x93\x00\x32\x18"
             "\x0E\x77\x5E\x04\x01\x71\x5D\xF7\x5D\x7E\xDC\xB7\x37\xA8\x7C\x4A\x09\x40\xDF\xE9\x12\x4A\x68\xCB\x8C\x54\x78\xD8\x16\xCB\x9E\x8C\xA5\xB9\xCA\xF2"
             "\x8D\x22\xF7\x86\xFB\xC6\x43\x31\xCC\x14\xC4\x0E\xA3\x72\xD6\x14\xF1\x81\x7E\x26\x0F\xCC\x32\xF4\x2E\x32\x12\x41\x9B\xC6\xFB\x1F\x6D\x7D\x71\x7B"
             "\xAE\xE7\xE0\x1B\x48\xE3\xFC\x05\x12\xF7\x15\x5D\xA5\x7E\xE4\x0B\x4A\x50\xC0\x46\xD8\x82\xBE\x38\xFF\xC7\x07\xA5\x2D\x1F\xD9\xA6\x39\xF1\xAC\x85"
             "\x0A\x54\x11\x5B\xE1\x9A\x7C\xB0\xBD\x91\x02\x01\x11\x02\x82\x02\x00\x0A\x26\x94\x1F\x84\x62\x9B\xF7\x05\xC9\x1F\xD1\x94\x3E\x1F\x72\x9C\x20\x14"
             "\x76\x7C\xBE\xA0\x54\xF0\xFB\x82\x5D\x3B\x2A\x77\xDF\x26\x41\xE8\x8A\xB9\x23\x4E\xCC\xAC\x17\xC6\x95\xCB\xC0\x67\x4D\x46\x9F\xAD\x9F\x7D\x54\x64"
             "\x21\x93\x1A\x64\xAE\x01\x88\x59\x4C\xB3\xCA\xAE\xCD\x31\x1A\x87\x0A\x10\x2E\x33\x76\x9D\xBE\x81\x68\xB5\x4F\x7B\xFF\x38\x71\xA0\x58\x93\x65\x02"
             "\xD5\x26\xC8\xE8\x69\x7C\x60\xC2\x9D\xE7\x50\x1C\x8D\x2E\x22\x72\xE5\xA9\xC5\xEF\x2E\x7F\xCF\x15\xE9\x4A\x09\xF0\xA7\x49\x4C\x14\x06\xFA\x8F\x54"
             "\x4C\xDE\x67\x6A\x41\xD8\xB0\x6E\x4D\xF7\xE9\xC5\x22\xD9\x84\xD4\x8C\xC5\x19\x19\x39\x19\x8C\x8C\x2E\xFB\xEC\x99\x6B\x23\x74\xAD\x22\x45\xF1\x84"
             "\x37\x00\xF6\x58\xB0\x8D\xD0\xE4\x39\xE8\x9B\xAD\x8D\x48\x5D\x27\xF5\xE6\x43\xEF\xE3\x7F\xEE\x12\x6E\x3B\xBE\xEE\x62\xBE\x99\xB8\x01\xEF\xF2\x9B"
             "\xE4\x58\x4B\x4A\x79\xBA\x55\xDD\x7F\xD0\x33\x51\x83\x5E\xB6\xF6\xF0\xA0\xE6\xC6\xF8\x77\xEA\xAA\xF3\x3A\x7F\xFF\x7B\xBB\xAF\x0A\x51\x6C\xEE\x77"
             "\xA4\xD4\xD8\x42\x15\x62\xA7\xED\x96\x19\x8F\xFA\xB9\x5D\x42\x64\xA8\x3A\xE6\xDA\xDD\x27\x62\x6F\x07\x15\xBE\xE1\xE1\xED\x53\x97\x88\xDE\x9E\xF6"
             "\x82\x43\xC6\x19\x8D\xD4\xC6\x81\x0E\xDE\xAD\x9B\xCE\x69\x40\xF5\x47\x7C\x82\xF3\xB5\x3D\xFA\xE2\x07\x91\x00\xE2\xBF\xCE\x1A\x12\x1D\x49\xF9\x95"
             "\x79\x31\x7C\x72\x22\xAB\x70\x38\x0C\x62\x13\x57\xD0\x84\x2C\x2D\xB5\x8A\xD8\x8C\xA8\x92\xA7\xCE\x5F\x06\xDD\x94\xD3\x5E\xCB\x7F\xE8\xA6\x9A\x62"
             "\xEA\x4C\xE6\x5E\x5A\x87\x5F\xCF\xB3\xCE\x67\x84\x6D\x19\x3D\xD5\x93\x45\xDC\x1E\xD0\x41\x65\x93\xF8\x98\x2A\x80\x5F\x31\x58\xBE\xF2\xCB\xEF\xA1"
             "\x65\x93\x59\x55\xD1\xBA\x3A\x86\xEB\xAE\xEF\xCD\xBC\xEE\xA2\x8E\x48\x98\x89\x6D\xCA\xE2\x05\x97\x60\x7F\x2B\x6D\x4E\x63\x3C\x5F\x89\x5D\x79\xE3"
             "\xF8\xD2\x9B\x92\xF8\x09\xB8\x6E\xD3\x4E\xAD\xF6\xDA\x11\xD5\x32\x23\x8A\x8C\x4A\xF4\xDB\x7D\x05\x33\xF2\xB6\x94\xB1\x4F\xC9\x72\x9A\xA3\xDB\x29"
             "\x69\x79\xFB\xDC\x2A\x9F\x5F\xF5\x04\xF5\x24\xDF\xD6\x4F\xA1\x0D\x26\x56\x89\xD4\xDE\x79\x23\x4E\x29\xD4\x0E\x67\x15\x3D\x18\xC2\x0C\x70\xD6\xEE"
             "\xC1\x21\x43\x96\x4D\x3B\xF8\x46\xA5\xBA\x6B\x16\xBC\xA1\x2E\xC8\x7F\xFD\xBF\xCE\x5F\x6E\xA2\x03\xA7\x02\x82\x01\x01\x00\xD8\xDE\x77\x54\x9A\xB6"
             "\x5E\x73\x46\x08\xB4\x82\x05\x08\xEE\xB4\x7F\x2B\x67\x7A\x84\x55\x79\x85\x73\xE4\x47\xA8\x26\x9B\x3B\x62\xF9\x22\x15\xE8\xAA\x4F\xBD\x44\x41\x43"
             "\x6C\x91\x37\xA9\xAA\xBC\x85\xEC\x08\x96\xDD\xE1\x7F\x42\xEC\xEF\x8E\xA5\xC3\x51\x18\xE0\xDD\x50\x09\x70\x05\x96\x09\xE3\xB2\x53\xE2\x17\x21\x58"
             "\xB1\x03\x68\x07\x97\xAA\xEF\x87\xB0\x32\x27\xCA\x39\x55\x06\x17\x7C\xD9\x5D\x58\xBA\x65\x56\x4F\x5C\x32\x7F\xD2\xBC\x5A\xF4\x4D\x7E\x9C\xCE\xF1"
             "\x09\xEA\xE0\xBA\x56\xDA\xF6\xA1\x40\x95\x8A\xC7\x5F\xA9\x41\x40\xE3\x01\x19\xB4\xB1\x22\x89\xF9\x80\xE8\x4D\xD0\x00\x60\x63\xFB\x30\x1F\x01\xFF"
             "\x66\xBF\xDE\xEB\xD3\x99\x7C\x17\x68\xFF\xA5\x07\x69\xF5\x3E\xBC\xF0\x6E\x9D\x5D\x35\x8E\xF5\x55\x5D\xA5\x57\xE5\xAB\xF7\x9A\xB5\x44\xFF\xA5\x8B"
             "\xE8\x8D\x55\x4C\x18\x49\xC3\x6B\x84\xB2\x8E\xC6\xAF\x9A\x55\x9F\xC1\xD0\xB9\x9D\x35\x59\xF9\xD0\x6E\x20\xE1\x6E\x05\xCF\xF7\x7B\x2C\xF5\xC2\x36"
             "\x2B\x60\x7C\xA3\xDA\xAC\x5D\x2A\x2D\xA8\x9C\x69\x17\x7D\xA8\xCB\xEE\x5D\x8F\x8A\x09\x4A\x3A\x56\x44\x7D\x5F\xD2\xC8\xBF\x27\xFF\x89\x43\x02\x82"
             "\x01\x01\x00\xF4\x70\x19\xC9\x97\xDF\xBF\x30\x1B\x8B\x27\xBA\xA9\x73\x78\x42\x5C\xCE\x6E\x57\xC3\x4C\x76\x2E\x19\x44\x44\xE3\x56\x0F\x75\x56\xC4"
             "\x4E\x17\x92\x81\x4B\x88\xFB\xEA\xC0\x14\x21\x77\x53\xDD\xC5\xA4\x49\xF6\x8F\x13\xB8\xD6\x84\xB3\x49\x9C\xD2\x0D\xD0\xD8\x20\x33\xD5\xF9\x3D\x76"
             "\x1A\x13\x4E\xB7\x04\x7B\xA7\x3C\x83\xD1\x86\xC6\x8A\xCA\x91\xA7\xD5\xE2\xA8\x74\xBD\x04\x1B\x76\x8B\x5A\x29\xBD\xDA\x9A\xFD\x93\x89\x7D\xCE\xD1"
             "\xC0\x2F\xC0\x67\x7B\x9A\x9E\xFD\xE8\xA0\x38\xF9\x81\x93\x10\x21\x93\xE2\x37\x11\xF0\xF8\x6E\x68\xE0\xA6\x43\xF6\x83\x49\x9C\x3D\x90\xD0\x92\xE8"
             "\x73\xA7\xB2\xF7\x23\xB6\xE2\x85\x41\xE7\xDC\xB4\xF4\xFF\x1B\x8A\x81\x7E\xA9\xFB\x5E\x6C\x34\xDA\x35\x84\xB9\x88\xEC\x2A\xCA\x36\x9F\xFD\x75\x62"
             "\x0C\xF0\x4B\x91\x52\xE9\xBE\x2D\x8F\xAE\x5D\xF1\xEE\x84\x18\x45\xAA\x0B\x18\x52\x1B\x8C\xCB\xD6\x2F\x86\xC4\x52\x2B\x95\x0F\x85\xA2\x9A\xEC\x19"
             "\x4B\x19\x59\x90\x86\x78\x45\xA0\x68\x10\x06\xBC\x3B\x2C\x40\x31\xFC\x0A\xA9\x7B\x39\xEE\x21\xCA\xAA\x03\xF3\xD5\x93\x94\x05\xCD\x41\x32\x0A\x12"
             "\xA6\xA6\xDA\x1D\x61\xB6\x9B\x02\x82\x01\x00\x33\x07\x2B\x22\xF7\x39\xF8\x1B\x1F\x89\x93\xE2\x5B\x89\xA1\x93\xE1\xAF\xDC\x1C\xD3\xD7\xE0\x5B\xA2"
             "\xCC\x4D\x18\x81\x8D\xEF\xDB\x0D\x71\x6E\x91\x19\x03\xB4\x10\x0F\x5B\x28\x9A\xA3\xAF\x73\x77\xA7\x0A\x5C\x5F\xBB\xBC\x96\x6A\x19\xA1\xC7\x36\x0F"
             "\xD6\xD8\xAD\x61\x40\x02\x38\x79\xC8\xF3\x44\xA2\x6E\x17\x14\x80\x51\x1A\x97\x63\xC5\x8D\x19\x29\x4D\x1A\x66\x27\x7A\xE0\x50\x3D\xAB\x2C\x6F\x61"
             "\x42\x0D\xBD\x7D\xB8\x51\xED\xC3\xB9\x1D\x42\x93\xD5\xFF\xAC\x6C\xED\x6B\xBE\xCB\x77\x23\x7E\xD0\x9E\x69\x8C\x99\x1F\xDA\x45\xF1\x3C\x71\xA5\xE7"
             "\xEE\x47\xCB\xE4\x3A\xB4\xEB\x5D\x9A\x5A\x71\x08\x77\x56\x9D\xE2\x5A\x36\x4B\x43\x82\xC8\x60\x59\x6E\xEB\x87\x72\x1F\xDC\xB2\x2C\xE1\x29\x83\x70"
             "\x52\x2A\xB8\x39\xB9\xBB\xAE\x6F\x08\xDD\x2B\x33\x75\xF2\x1E\x08\xD5\xA0\x21\x41\x3F\x14\xC6\x0F\xDD\x10\x2A\x03\x7A\x0B\x33\x5F\x70\xE2\x4F\x3A"
             "\xBB\x94\x15\x2B\xB8\x92\x62\x16\xEC\xB6\x12\xD0\xD1\xB0\x39\xD3\x58\x0A\x34\xD2\x08\x6F\xB0\x15\xEB\xCE\x82\x06\xAF\x50\xD2\x45\xD5\xA1\x7F\x6D"
             "\x11\x6B\x98\xFE\xAA\xE2\xF0\x52\xC8\x2F\x3C\x09\x69\x4D\x79\x02\x82\x01\x01\x00\x81\x68\x86\x1F\x6E\x85\x83\x55\xB4\x3A\x9C\x8F\xFF\x5B\x3F\xAA"
             "\xA9\x9A\x76\xA6\xEE\xEC\x3E\x90\xE0\x33\x33\x87\x69\xCB\xF2\xD3\x95\x1A\x48\xB6\xF9\x27\xFD\x3A\x12\xDE\x28\xC6\x6C\x59\x93\x86\xC0\x63\x64\x69"
             "\xDD\x43\xBC\xDC\xD7\x63\x34\xE7\xAC\xF6\x18\x11\x0C\x62\x38\xA8\x11\x59\x19\x47\xCA\x4D\xAA\xE0\x10\xFA\x7D\xFC\x0E\xC1\xF2\xC5\x95\x16\xE1\x68"
             "\x3D\xCD\x7A\xA5\x20\xA4\x20\xAC\xAF\xCE\x15\xD1\x8A\x57\xD9\x31\x41\xDE\x37\x65\xDC\x6E\x9D\x26\xFE\xE4\x91\x0F\x1A\xAE\x02\x90\x11\xC6\xC3\x0E"
             "\x18\x8E\xA1\xA3\xDD\x2B\xA3\x51\x28\x27\x63\x34\x99\x10\x6E\x6B\xE4\x79\x76\xE6\x46\x9A\x6F\xE1\x55\x9B\x5C\xA2\x05\x72\xA5\x2C\xB2\xBD\x06\xD2"
             "\x76\x04\xCF\xDF\xBE\xD1\x0A\x07\xDF\x13\x9E\x2E\xD1\x9F\xFE\xA7\x8E\x43\x15\xCD\xA7\x4A\x03\x46\x90\x97\x5C\x4F\xDA\x6F\x36\xDF\xAC\x69\x14\xEE"
             "\xC2\x0E\x95\xD5\x53\x46\x56\x67\xEF\x44\x3F\xDB\x0A\x83\x42\xF5\x76\xCD\x67\xC6\x01\x38\x21\x8E\x45\xDC\xBD\x30\xBE\x01\x35\x8B\x65\xC1\xAB\x4A"
             "\xAA\xA6\x32\xC6\x98\x78\x20\x35\xCB\x6C\x3F\x4E\x5D\x9A\xFC\x5F\xAF\x85\x67\x64\x69\xE8\x6F\xBB\x02\x82\x01\x01\x00\xA7\xA2\xD3\x22\x74\xCE\x04"
             "\xFE\xC0\xC5\x59\x47\x30\xF9\xFC\x98\xAB\x66\x33\xA4\x16\xD7\x0E\x5E\x13\xCE\xC7\x2D\xD3\xD0\x5A\x31\x41\xE8\x32\x3D\x09\x25\x70\x5A\x89\xBC\xE9"
             "\xA6\xA0\x16\x4D\x78\xDE\x2F\xAC\xC0\x21\xD0\x60\xFE\x08\xFE\xC2\xE3\x96\xAD\x7E\xEE\x62\x9A\x93\x0B\xA3\x32\x8D\x25\x56\x54\xED\xD4\x70\xCE\x7C"
             "\xF5\x05\x83\xD6\x97\x2F\x31\x8E\xDB\xE9\x8E\xE6\x5E\x12\xB4\x76\x80\xAC\x6B\x1B\x6F\x3E\xDA\x65\x09\x15\xDA\xB9\x56\x20\x94\xC9\x5D\x8D\x30\x62"
             "\x56\xD0\xDB\xF9\xEB\x20\xA3\x25\xD3\x47\xC5\xE7\xE9\xC7\x56\x77\x82\x44\xC5\x86\xCD\x14\x6F\x9C\x54\x73\xA0\x8E\x6C\x83\x94\xAF\xFC\x16\xF9\xF0"
             "\x5D\xBE\x4A\x1F\xB2\xB6\x2A\x0B\xA3\x31\xFA\xA8\x6C\x21\x9A\x66\x7D\x03\x80\x8D\xF7\x91\x6F\xB8\x2E\xF2\x31\x9D\x5C\x1D\x71\x9E\x39\x40\x47\xC5"
             "\x97\xDA\x0B\xDA\x81\x55\x27\xF4\x57\x00\x30\xEB\x19\x96\xAA\x4C\xDD\xBC\xD6\xFC\xEB\xE2\xA8\x60\x2D\x57\xA0\x5B\x55\xD2\x03\x21\xCA\x6F\x08\xB2"
             "\x39\x4E\x02\x5C\x2F\x12\x48\x90\xE6\x06\xC8\x2A\xB2\xD2\x0B\x93\x2F\x6E\x55\x50\xEB\x95\x03\x61\xEE\xC3\x47\xE4\xCF\xEA\x31\x2F\x1F"},
        };
        TEST_END
    }

    // Aes128encode/Aes128decode
    {
        TEST_FUNCTION
        std::pair<std::string, std::string> res = Aes128encode(data, key);
        assert(!res.first.empty());
        assert(!res.second.empty());
        SString strDecoded = Aes128decode(res.first, key, res.second);
        assert(data == strDecoded);
        TEST_VARS
        const SString key;
        const SString data;
        TEST_DATA = {
            {"5347123412340000", "AB12£$_ "},
            {"gHtySkGerYnhDxAs", "78111E998C42243285635E39AFDD614B\0 AB12£$_ "},
            {"!@#$%^&*()_+|:<>", "Hello thereHello there"},
        };
        TEST_END
    }

    #define szTempFilename "hash_""\xD0""\x98""_test"

    // MD5
    {
        TEST_FUNCTION
        SString strResult = CMD5Hasher::CalculateHexString(a.c_str(), a.length());
        assert(strResult == result);

        strResult = GenerateHashHexString(EHashFunction::MD5, a);
        assert(strResult == result);

        FileSave(szTempFilename, a);
        strResult = GenerateHashHexStringFromFile(EHashFunction::MD5, szTempFilename);
        assert(strResult == result);
        TEST_VARS
        const SString a;
        const char*   result;
        TEST_DATA = {
            {"", "D41D8CD98F00B204E9800998ECF8427E"},
            {"Hello there", "E8EA7A8D1E93E8764A84A0F3DF4644DE"},
            {"AB12£$_\0 ", "78111E998C42243285635E39AFDD614B"},
        };
        TEST_END
    }

    // SHA256
    {
        TEST_FUNCTION
        SString strResult = GenerateSha256HexString(a);
        assert(strResult == result);

        FileSave(szTempFilename, a);
        strResult = GenerateHashHexStringFromFile(EHashFunction::SHA256, szTempFilename);
        assert(strResult == result);
        TEST_VARS
        const SString a;
        const char*   result;
        TEST_DATA = {
            {"", "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855"},
            {"Hello there", "4E47826698BB4630FB4451010062FADBF85D61427CBDFAED7AD0F23F239BED89"},
            {"AB12£$_\0 ", "A427AEDD32E652FED23901406BCC49BF78B906E69699A68932638502E8C1138B"},
        };
        TEST_END
    }

    // SHA1
    {
        TEST_FUNCTION
        SString strResult = GenerateHashHexString(EHashFunction::SHA1, a);
        assert(strResult == result);

        FileSave(szTempFilename, a);
        strResult = GenerateHashHexStringFromFile(EHashFunction::SHA1, szTempFilename);
        assert(strResult == result);
        TEST_VARS
        const SString a;
        const char*   result;
        TEST_DATA = {
            {"", "DA39A3EE5E6B4B0D3255BFEF95601890AFD80709"},
            {"Hello there", "726C76553E1A3FDEA29134F36E6AF2EA05EC5CCE"},
            {"AB12£$_\0 ", "CA7B95DF48B83232FCA0FE3FAE7A787784F54225"},
        };
        TEST_END
    }

    // SHA224
    {
        TEST_FUNCTION
        SString strResult = GenerateHashHexString(EHashFunction::SHA224, a);
        assert(strResult == result);

        FileSave(szTempFilename, a);
        strResult = GenerateHashHexStringFromFile(EHashFunction::SHA224, szTempFilename);
        assert(strResult == result);
        TEST_VARS
        const SString a;
        const char*   result;
        TEST_DATA = {
            {"", "D14A028C2A3A2BC9476102BB288234C415A2B01F828EA62AC5B3E42F"},
            {"Hello there", "40AACC4967ECA7730A1A069539D78AE7782480802E481F1ECC26927D"},
            {"AB12£$_\0 ", "73420F2E80A236DD7C836C68177E282BC8E86CD8BB497E5F443F1FAE"},
        };
        TEST_END
    }

    // SHA384
    {
        TEST_FUNCTION
        SString strResult = GenerateHashHexString(EHashFunction::SHA384, a);
        assert(strResult == result);

        FileSave(szTempFilename, a);
        strResult = GenerateHashHexStringFromFile(EHashFunction::SHA384, szTempFilename);
        assert(strResult == result);
        TEST_VARS
        const SString a;
        const char*   result;
        TEST_DATA = {
            {"", "38B060A751AC96384CD9327EB1B1E36A21FDB71114BE07434C0CC7BF63F6E1DA274EDEBFE76F65FBD51AD2F14898B95B"},
            {"Hello there", "7438E0294C534D6CA6CC2EFB04A60DB488C86B66C4CBD3C00D11D58C8020274AB0A2A720C88986968D894F26B16C461F"},
            {"AB12£$_\0 ", "DFCAF84C21F93CC88DE6CB54D838FEE5ACF592DCF392883708BAD1CFF7B847DEA9A175C5E87014D5829E66E17571F7E6"},
        };
        TEST_END
    }

    // SHA512
    {
        TEST_FUNCTION
        SString strResult = GenerateHashHexString(EHashFunction::SHA512, a);
        assert(strResult == result);

        FileSave(szTempFilename, a);
        strResult = GenerateHashHexStringFromFile(EHashFunction::SHA512, szTempFilename);
        assert(strResult == result);
        TEST_VARS
        const SString a;
        const char*   result;
        TEST_DATA = {
            {"", "CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E"},
            {"Hello there", "567683DDBA1F5A576B68EC26F41FFBCC7E718D646839AC6C2EF746FE952CEF4CBE6DEA635BC2F098B92B65CAACF482333BB9D1D9A3089BC4F01CB86F7A2FBC18"},
            {"AB12£$_\0 ", "EE57E02866026848F988E793E9B099931CBCA8773B13EA5055ABA462885E8B044CE5C72CB528712CE2A442707F2BC25A52CC91F8C09DD1C6A6A5C9A63D52F320"},
        };
        TEST_END
    }

    FileDelete(szTempFilename);
}
