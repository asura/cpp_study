#include "thread_safe_queue.h"
#include <algorithm>
#include <cassert>
#include <thread>
#include "catch.hpp"
#include "plog/Log.h"


SCENARIO("構築した時点ではemptyがtrueを返す", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<int> sut;
    REQUIRE(sut.empty());
}

SCENARIO("pushするとemptyはfalseを返す", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<int> sut;
    sut.push(1);
    REQUIRE(!sut.empty());
}

SCENARIO("pushした値はfrontで取得できる", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<int> sut;
    sut.push(1);
    auto value = sut.front();
    REQUIRE(value == 1);
}

SCENARIO("pushするとsizeで取得できる値が+1になる", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<int> sut;
    REQUIRE(sut.size() == 0);

    sut.push(1);
    REQUIRE(sut.size() == 1);

    sut.push(2);
    REQUIRE(sut.size() == 2);
}

SCENARIO("構築直後にpopすると例外発生", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<int> sut;
    REQUIRE_THROWS(sut.pop());
}

SCENARIO("push→popによりsizeが減少", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<int> sut;

    sut.push(1);
    sut.pop();
    REQUIRE(sut.size() == 0);
}

struct Foo
{
    static std::vector<std::string> log;

    Foo()
    {
        log.push_back("constructor");
    }

    Foo(const std::string&)
    {
        log.push_back("constructor with string");
    }

    Foo(const Foo&)
    {
        log.push_back("copy constructor");
    }

    Foo(Foo&&)
    {
        log.push_back("move constructor");
    }

    Foo& operator=(const Foo&)
    {
        log.push_back("copy operator");
    }

    Foo& operator=(Foo&&)
    {
        log.push_back("move operator");
    }
};

std::vector<std::string> Foo::log;

TEST_CASE("通常のpushはコピーコンストラクタが動く", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<Foo> sut;
    Foo::log.clear();

    Foo foo;
    sut.push(foo);

    REQUIRE(Foo::log.size() == 2);
    CHECK(Foo::log[0] == "constructor");
    CHECK(Foo::log[1] == "copy constructor");
}

TEST_CASE("ムーブ版のpushはムーブコンストラクタが動く", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<Foo> sut;
    Foo::log.clear();

    sut.push(Foo());

    REQUIRE(Foo::log.size() == 2);
    CHECK(Foo::log[0] == "constructor");
    CHECK(Foo::log[1] == "move constructor");
}

TEST_CASE("emplaceはコピーされない", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<Foo> sut;
    Foo::log.clear();

    sut.emplace(std::string("abc"));

    REQUIRE(Foo::log.size() == 1);
    CHECK(Foo::log[0] == "constructor with string");
}

std::mutex mtx;

void produce(std::deque<int>& inputs, ThreadSafeQueue<int>& queue)
{
    while (true)
    {
        if (inputs.empty())
        {
            break;
        }
        assert(!inputs.empty());
        const size_t n = inputs.size();
        int value = inputs.front();
        assert(inputs.size() == n);
        inputs.pop_front();
        assert(inputs.size() == n - 1);

        std::lock_guard<std::mutex> lock(mtx);
        queue.push(value);
    }
}

void consume(int i, ThreadSafeQueue<int>& queue, std::vector<int>& outputs, int n_data, bool& running)
{
    int count = 0;
    while (running)
    {
        while (running)
        {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!queue.empty())
                {
                    const int value = queue.front();
                    if (value == n_data - 1)
                    {
                        running = false;
                    }
                    outputs.push_back(value);
                    queue.pop();
                    ++count;
                    break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    LOGI << i << "," << count;
}

TEST_CASE("multi-producer, multi-consumer", "[unit][ThreadSafeQueue]")
{
    ThreadSafeQueue<int> sut;

    // データ数
    const int n_data = 1000 * 1000;

    // 入力スレッド数
    const int n_producer = 100;

    // 出力スレッド数
    const int n_consumer = 100;

    // 入力データ(スレッド分を用意)
    auto inputs = new std::deque<int>[n_producer];
    for (int i = 0; i < n_data; ++i)
    {
        inputs[i % n_producer].push_back(i);
    }

    // 出力データ
    auto outputs = new std::vector<int>[n_consumer];

    // 出力用のmutex
    std::mutex mtx_outputs;

    std::vector<std::thread> threads;

    // 入力側スレッド群
    for (int i = 0; i < n_producer; ++i)
    {
        threads.emplace_back(
            std::bind(&produce, std::ref(inputs[i]), std::ref(sut)));
    }
    REQUIRE(threads.size() == n_producer);

    // 出力側スレッド群
    bool running = true;
    for (int i = 0; i < n_consumer; ++i)
    {
        threads.emplace_back(
            std::bind(&consume, i, std::ref(sut), std::ref(outputs[i]), n_data, std::ref(running)));
    }
    REQUIRE(threads.size() == n_producer + n_consumer);

    // スレッド終了待機
    for (auto& thread : threads)
    {
        thread.join();
    }

    LOGI << "sut.size()=" << sut.size();
    REQUIRE(sut.empty());

    std::vector<int> result;
    for (int i = 0; i < n_consumer; ++i)
    {
        for (const auto& j : outputs[i])
        {
            result.push_back(j);
        }
    }

    REQUIRE(result.size() == n_data);

    std::sort(result.begin(), result.end());
    CHECK(result[0] == 0);
    for (int i = 1; i < result.size(); ++i)
    {
        CHECK(result[i - 1] + 1 == result[i]);
    }

    delete[] inputs;
    delete[] outputs;
}
