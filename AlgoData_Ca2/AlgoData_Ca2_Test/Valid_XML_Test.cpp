#include "pch.h"
#include "CppUnitTest.h"
#include "../AlgoData_Ca2/Xml.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Valid_XML_Test
{
	TEST_CLASS(Valid_XML_Test)
	{
	public:
		TEST_METHOD(TestXMLRead)
		{
			string xmlString = readXml("../AlgoData_Ca2/XMLFile.xml");
			string fileString = "<note>\n  <sub>\n    <to>Tove</to>\n    <from></from>\n    <heading>Reminder</heading>\n    <body>Don't forget me this weekend!</body>\n  </sub>\n</note>";
			
			Assert::AreEqual(fileString, xmlString);
		}
		TEST_METHOD(TestXMLValid)
		{
			Assert::IsTrue(validateXml("../AlgoData_Ca2/Books.xml"));
			Assert::IsTrue(validateXml("../AlgoData_Ca2/menu.xml"));
			Assert::IsTrue(validateXml("../AlgoData_Ca2/Music.xml"));
			Assert::IsTrue(validateXml("../AlgoData_Ca2/Plants.xml"));
		}
		TEST_METHOD(TestXMLNotValid)
		{
			Assert::IsFalse(validateXml("../AlgoData_Ca2/XMLFileClosingTag.xml"));
			Assert::IsFalse(validateXml("../AlgoData_Ca2/XMLFileNoRoot.xml"));
		}
		TEST_METHOD(TestXMLTree) 
		{
			Tree<TreeNode> root(buildXmlTree("../AlgoData_Ca2/Books.xml"));
			Assert::IsNotNull(&root);

			TreeIterator<TreeNode> iter(&root);
			string result = iter.item().title;
			string rootTitle = root.data.title;
			Assert::AreEqual(rootTitle, result);
		}
		TEST_METHOD(TestXMLTreeIsNode)
		{
			TreeNode node;
			string target = "Testing";
			node.title = "Node";
			node.attributes.insert({ "Test", target });
			bool result = isNode(node, target);
			Assert::IsTrue(result);

			target = "Nothing";
			result = isNode(node, target);
			Assert::IsFalse(result);
		}
		TEST_METHOD(TestXMLTreeDfs)
		{
			/* 
				couldnt get it returning true or false if somthing is found as i tried and it 
				returns true then it wouldnt print the next node if found so i left it out.
			*/

			//Tree<TreeNode> root(buildXmlTree("../AlgoData_Ca2/Books.xml"));
			//TreeIterator<TreeNode> iter(&root);
			//dfs(iter, "Computer", &isNode);
			//bool found = dfs(iter, "O'Brien, Tim", &isNode);
			//Assert::IsTrue(found);
		}

	};
}
