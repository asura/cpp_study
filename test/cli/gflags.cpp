#include <gflags/gflags.h>
#include <catch.hpp>
#include <vector>

DEFINE_string(option, "デフォルト値", "オプション引数");

TEST_CASE("gflags::ParseCommandLineFlagsの使い方", "[api][gflags]")
{
    FLAGS_option = "デフォルト値";  // テスト間の依存性をなくすため、フラグ値をデフォルトに戻す必要あり

    WHEN("引数が --option 文字列 であった場合")
    {
        std::vector<char*> args;
        {
            args.push_back(new char[256]);
            strcpy(args.back(), "exe_name");

            args.push_back(new char[256]);
            strcpy(args.back(), "--option");

            args.push_back(new char[256]);
            strcpy(args.back(), "value");
        }

        int argc = 3;
        char** argv = new char*[3];
        argv[0] = args[0];
        argv[1] = args[1];
        argv[2] = args[2];

        char** argv_saved = argv;

        AND_WHEN("ParseCommandLineFlagsの第3引数にtrueを指定")
        {
            gflags::ParseCommandLineFlags(&argc, &argv, true);

            THEN("argc・argv変数からはオプション分の情報が削除されている")
            {
                CHECK(argc == 1);
                CHECK(argv[0] == std::string("exe_name"));
                CHECK(argv_saved != argv);
                CHECK(argv_saved + 2 == argv);
                CHECK(argv_saved[0] == argv_saved[2]);

                AND_THEN("optionの値は指定値")
                {
                    CHECK(FLAGS_option == "value");
                }
            }
        }

        AND_WHEN("ParseCommandLineFlagsの第3引数にfalseを指定")
        {
            gflags::ParseCommandLineFlags(&argc, &argv, false);

            THEN("argc・argv変数は変わらず")
            {
                CHECK(argc == 3);
                CHECK(argv[0] == std::string("exe_name"));
                CHECK(argv[1] == std::string("--option"));
                CHECK(argv[2] == std::string("value"));
                CHECK(argv_saved == argv);

                AND_THEN("optionの値は指定値")
                {
                    CHECK(FLAGS_option == "value");
                }
            }
        }

        delete[] args[0];
        delete[] args[1];
        delete[] args[2];
        delete[] argv_saved;
    }

    WHEN("引数が無かった場合")
    {
        int argc = 1;
        char** argv = new char*[argc];
        argv[0] = new char[256];
        strcpy(argv[0], "exe_name");

        AND_WHEN("ParseCommandLineFlagsの第3引数にtrueを指定")
        {
            gflags::ParseCommandLineFlags(&argc, &argv, true);

            THEN("argc・argv変数は変わらず")
            {
                CHECK(argc == 1);
                CHECK(argv[0] == std::string("exe_name"));

                AND_THEN("optionの値はデフォルト値")
                {
                    CHECK(FLAGS_option == "デフォルト値");
                }
            }
        }

        delete[] argv[0];
        delete[] argv;
    }
}
