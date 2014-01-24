#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Assignment1/bintree.h"
#include "../Assignment1/bintree.cpp"
#include "../Assignment1/nodedata.h"
#include "../Assignment1/nodedata.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		

		//testing overloaded operator<<
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			NodeData * a = new NodeData("a");
			NodeData * b = new NodeData("b");
			NodeData * c = new NodeData("c");

			std::ostringstream stringer;

			stringer << *a << *b << *c;

			std::string expected = "abc";
			std::string actual = stringer.str();

			Assert::AreEqual(expected, actual,L"Returns pass if strings are the same");

		}

	};
}