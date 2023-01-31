#include "pch.h"
#include "CppUnitTest.h"
#include "../Item.h"
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventureGameTests
{
	TEST_CLASS(ItemTests)
	{
	public:

		TEST_CLASS_INITIALIZE(SetUp) {
			auto path = std::filesystem::current_path(); //getting path
			std::filesystem::current_path(path.append("../../..")); //setting path
		}

		TEST_METHOD(SwordTest)
		{
			Item item("item/sword.txt");

			Assert::AreEqual(std::string("Sword"), item.getName());
		}
	};
}
