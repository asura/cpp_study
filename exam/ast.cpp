#include <clang-c/Index.h>
#include <catch2/catch.hpp>
#include <iostream>
#include "config.h"

SCENARIO(
    "libclangのAST解析機能を使う",
    "[ast]")
{
    GIVEN("indexを作っておく")
    {
        CXIndex index = clang_createIndex(
            0,  // excludeDeclarationsFromPCH = 0 => all declarations will be enumerated
            0   // displayDiagnostics
        );

        WHEN("C++ファイルをパースする")
        {
            CXTranslationUnit unit = clang_parseTranslationUnit(
                index,
                PROJECT_SOURCE_BASE_DIR "/exam/header.hpp",  // source_filename
                nullptr,                                     // command_line_args
                0,                                           // num_command_line_args
                nullptr,                                     // unsaved_files
                0,                                           // num_unsaved_files
                CXTranslationUnit_None                       // options
            );

            THEN("正常終了する")
            {
                REQUIRE(unit != nullptr);

                AND_WHEN("カーソルを取得")
                {
                    auto cursor = clang_getTranslationUnitCursor(unit);

                    THEN("カーソルが指す先はTranslationUnit")
                    {
                        CHECK(cursor.kind == CXCursor_TranslationUnit);

                        clang_visitChildren(
                            cursor,
                            [](CXCursor c, CXCursor parent, CXClientData client_data) {
                                std::cout << "Cursor '"
                                          << (const char*)(clang_getCursorSpelling(c).data)
                                          << "' of kind '"
                                          << (const char*)(clang_getCursorKindSpelling(clang_getCursorKind(c)).data)
                                          << "'\n";
                                return CXChildVisit_Recurse;
                            },
                            nullptr);
                        //CXCursor_StructDecl
                    }
                }
            }

            clang_disposeTranslationUnit(unit);
        }

        clang_disposeIndex(index);
    }
}