#include "pch.h"
#include "CppUnitTest.h"
#include "../Item.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventureGameTests
{
	TEST_CLASS(ItemTests)
	{
	public:
		
		TEST_METHOD(SwordTest)
		{
			Item item("../../../item/sword.txt");

			Assert::AreEqual(std::string("Sword"), item.getName());
		}
	};
}
