
#include "pch.h"
#include "CppUnitTest.h"

#define main Lab102BMain
#include "../Lab_10_2_B/Lab_10_2_B.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab102B
{
    TEST_CLASS(UnitTestLab102B)
    {
    public:

        TEST_METHOD(TestIndexSort)
        {
            Student p[4] = {};

            p[0].prizv = "Petrenko";
            p[0].spec = KN;
            p[0].mat = 5;

            p[1].prizv = "Koval";
            p[1].spec = INF;
            p[1].mat = 4;

            p[2].prizv = "Ivanenko";
            p[2].spec = KN;
            p[2].mat = 3;

            p[3].prizv = "Bondar";
            p[3].spec = KN;
            p[3].mat = 3;

            int* I = IndexSort(p, 4);

            Assert::AreEqual(1, I[0]);
            Assert::AreEqual(3, I[1]);
            Assert::AreEqual(2, I[2]);
            Assert::AreEqual(0, I[3]);

            delete[] I;
        }
    };
}
