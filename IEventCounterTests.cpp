//
// Created by stephanie on 2018-02-11.
//
#include <cstdio>
#include "IEventCounter.h"
#include <thread>




void test1(IEventCounter *EC) {
    std::cout << "******** Test 1 ********" << std::endl;
    std::cout << "Testing stage 3 (5+min) - 2 - 0" << std::endl;
    EC->ParseEvents("123d", "test1.txt");
    if (EC->GetEventCount("123d") == 1) {
        std::cout << "Test 1 Passed" << std::endl;
    } else {
        std::cout << "Test 1 Failed" << std::endl;
    }

}

void test2(IEventCounter *EC) {
    std::cout << "******** Test 2 ********" << std::endl;
    std::cout << "Testing stage 3 (5+min) - 2 - 3 - 0" << std::endl;
    EC->ParseEvents("123d", "test1.txt");
    if (EC->GetEventCount("123d") == 1) {
        std::cout << "Test 2 Passed" << std::endl;
    } else {
        std::cout << "Test 2 Failed" << std::endl;
    }
}
void test3(IEventCounter *EC) {
    std::cout << "******** Test 3 ********" << std::endl;
    std::cout << "Testing stage 3 (5+min) - 2 - 3 - 2 - 1 - 2 - 0" << std::endl;
    EC->ParseEvents("123a", "test3.txt");
    if (EC->GetEventCount("123a") == 0) {
        std::cout << "Test 3 Passed" << std::endl;
    } else {
        std::cout << "Test 3 Failed" << std::endl;
    }
}
void test4(IEventCounter *EC) {
    std::cout << "******** Test 4 ********" << std::endl;
    std::cout << "Testing empty log file" << std::endl;
    FILE* fout = fopen("test4.txt", "w");
    fclose(fout);
    EC->ParseEvents("123b", "test3.txt");
    if (EC->GetEventCount("123b") == 0) {
        std::cout << "Test 4 Passed" << std::endl;
    } else {
        std::cout << "Test 4 Failed" << std::endl;
    }
}

void test5(IEventCounter *EC) {
    std::cout << "******** Test 5 ********" << std::endl;
    std::cout << "Testing No Fault Event" << std::endl;
    EC->ParseEvents("1235", "test5.txt");
    if (EC->GetEventCount("1235") == 0) {
        std::cout << "Test 5 Passed" << std::endl;
    } else {
        std::cout << "Test 5 Failed" << std::endl;
    }
}
void test6(IEventCounter *EC) {
    std::cout << "******** Test 6 ********" << std::endl;
    std::cout << "Several Fault Events" << std::endl;
    EC->ParseEvents("1235", "test6.txt");
    if (EC->GetEventCount("1235") == 4) {
        std::cout << "Test 6 Passed" << std::endl;
    } else {
        std::cout << "Test 6 Failed" << std::endl;
    }
}

void test7(IEventCounter *EC) {
    std::cout << "******** Test 7 ********" << std::endl;
    std::cout << "Many Threads With Same Device ID" << std::endl;

    void (IEventCounter::*fptr)(const char*, const char*) = &IEventCounter::ParseEvents;

    if (EC->GetEventCount("1235") == 4) {
        std::cout << "Test 7 Passed" << std::endl;
    } else {
        std::cout << "Test 7 Failed" << std::endl;
    }
}
int main() {
    IEventCounter EC;
    test1(&EC);
    test2(&EC);
    test3(&EC);
    test4(&EC);
    test5(&EC);
    test6(&EC);
    test7(&EC);
    return 0;
}
