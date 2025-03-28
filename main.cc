#include "gtest/gtest.h"
#include "reg_test.h"
#include <cstdint>
#include "fifo_test.h"

#include <gtest/gtest.h>
#include <execinfo.h>
#include <execinfo.h>
#include <dlfcn.h>    // 用于 dladdr
#include <cxxabi.h>   // 用于反混淆符号

void PrintStackTrace() {
    void* buffer[100];
    int num_frames = backtrace(buffer, 100);
    char** symbols = backtrace_symbols(buffer, num_frames);

    std::cerr << "\nCall stack:" << std::endl;
    for (int i = 0; i < num_frames; i++) {
        Dl_info info;
        if (dladdr(buffer[i], &info) && info.dli_sname) {
            // 反混淆 C++ 符号
            int status = 0;
            char* demangled = abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, &status);
            const char* name = (status == 0) ? demangled : info.dli_sname;
            std::cerr << "#" << i << " " << buffer[i] << " : " << name << std::endl;
            free(demangled);
        } else {
            std::cerr << "#" << i << " " << symbols[i] << std::endl;
        }
    }
    free(symbols);
}

class StackTraceListener : public testing::EmptyTestEventListener {
    public:
        void OnTestPartResult(const testing::TestPartResult& result) override {
            if (result.failed()) {
                PrintStackTrace(); // 触发堆栈打印
            }
        }
    };
    

// unit test main
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


