#include "pch.h"
#include <gtest/gtest.h>
#include "../lltoolkit/LLToolkit.h"

using namespace LinkedList;
//================================================
// Test fixture for LLToolkit
//================================================
class LLToolkitTest : public ::testing::Test
{
protected:
	LLToolkitTest()
	{
		valToInsert = 2;// In some tests, explicitly declared value to insert
		//	pointer is necessary due to strict typing in templates

		emptyList = nullptr;	
		singleElementList = new Node<int>(valToInsert);

		n3 = new Node<int>(3);
		n2 = new Node<int>(2, n3);
		n1 = new Node<int>(1, n2);
	}

	~LLToolkitTest()
	{
	}


	// Test members
	Node<int>* emptyList;
	Node<int>* singleElementList;
	int valToInsert;


	Node<int>* n1;
	Node<int>* n2;
	Node<int>* n3;
};

TEST_F(LLToolkitTest, HeadInsert_EmptyList_HeadValueIsCorrect)
{
	Node<int>* head = nullptr;

	headInsert(head, valToInsert);
	EXPECT_EQ(head->info, valToInsert);
}

TEST_F(LLToolkitTest, HeadInsert_NonEmptyList_HeadValueIsCorrect)
{
	headInsert(n1, valToInsert);
	EXPECT_EQ(n1->info, valToInsert);
}


TEST_F(LLToolkitTest, HeadInsert_NonEmptyList_HeadNextCorrect)
{
	Node<int>* oldN1 = n1;
	headInsert(n1, valToInsert);
	EXPECT_EQ(n1->next, oldN1);
}

TEST_F(LLToolkitTest, HeadRemove_Called_NewHeadCorrect)
{
	headRemove(n1);
	EXPECT_EQ(n1, n2);
}

TEST_F(LLToolkitTest, HeadRemove_ListEmpty_NoError)
{
	headRemove(emptyList);
}


TEST_F(LLToolkitTest, Insert_PrevPtrnullptr_NoError)
{
	insert(emptyList, valToInsert);
}


TEST_F(LLToolkitTest, Insert_MiddleOfList_InsertedValCorrect)
{
	insert(n1, valToInsert);
	EXPECT_EQ(n1->next->info, valToInsert);
}


TEST_F(LLToolkitTest, Insert_MiddleOfList_ListReconnected)
{
	insert(n1, valToInsert);

	EXPECT_EQ(n1->next->next, n2);
}

TEST_F(LLToolkitTest, Insert_EndOfList_InsertedValCorrect)
{
	insert(n3, valToInsert);
	EXPECT_EQ(n3->next->info, valToInsert);
}

TEST_F(LLToolkitTest, Insert_EndOfList_ListReconnedted)
{
	insert(n3, valToInsert);
	EXPECT_EQ(n3->next->next, nullptr);
}


TEST_F(LLToolkitTest, Remove_PrevPtrNull_NoError)
{
	remove(emptyList);
}


TEST_F(LLToolkitTest, Remove_MiddleOfList_ListReconnected)
{
	remove(n1);
	EXPECT_EQ(n1->next, n3);
}

TEST_F(LLToolkitTest, Remove_EndOfList_NoError)
{
	remove(n3);
	//EXPECT_EQ(n2->next, n3);
}

TEST_F(LLToolkitTest, Copy_EmptyList_NoError)
{
	Node<int>* result = copy(emptyList);
	EXPECT_EQ(result, emptyList);
}

TEST_F(LLToolkitTest, Copy_NonEmptyList_ResultIsCopyOfSource)
{
	Node<int>* result = copy(n1);

	bool testResult = (
		(result->info == n1->info) &&
		(result->next->info == n2->info) &&
		(result->next->next->info == n3->info));

	EXPECT_TRUE(testResult);
}

TEST_F(LLToolkitTest, Copy_NonEmptyList_ResultIsDeepCopyOfSource)
{
	Node<int>* result = copy(n1);
	n1->info = 4;
	n1->next->info = 5;
	n1->next->next->info = 6;

	bool testResult = (
		(result->info == 1) &&
		(result->next->info == 2) &&
		(result->next->next->info == 3));

	EXPECT_TRUE(testResult);
}


TEST_F(LLToolkitTest, Clear_EmptyList_NoError)
{
	clear(emptyList);
}

TEST_F(LLToolkitTest, Clear_NonEmptyList_ListIsEmpty)
{
	clear(n1);
	EXPECT_EQ(n1, nullptr);
}


TEST_F(LLToolkitTest, Reverse_EmptyList_NoError)
{
	reverse(emptyList);
}

TEST_F(LLToolkitTest, Reverse_SingleElement_InfoOK)
{

	reverse(singleElementList);

	EXPECT_EQ(singleElementList->info, valToInsert);
}

TEST_F(LLToolkitTest, Reverse_SingleElement_NextOK)
{
	reverse(singleElementList);
	Node<int>* expected = 0;

	EXPECT_EQ(singleElementList->next, expected);
}


TEST_F(LLToolkitTest, Reverse_TwoElements_InfoOK)
{
	Node<int>* n2 = new Node<int>(2);
	Node<int>* n1 = new Node<int>(1, n2);
	reverse(n1);

	EXPECT_EQ(n1->info, 2);
}


TEST_F(LLToolkitTest, Reverse_TwoElements_NextOK)
{
	Node<int>* n2 = new Node<int>(2);
	Node<int>* n1 = new Node<int>(1, n2);
	reverse(n1);

	EXPECT_EQ(n1->next->info, 1);
}



TEST_F(LLToolkitTest, Reverse_ThreeElements_ResultReversed)
{
	reverse(n1);

	bool result = (
		(n1->info == 3) &&
		(n1->next->info == 2) &&
		(n1->next->next->info == 1));

	EXPECT_TRUE(result);
}


TEST_F(LLToolkitTest, Split_EmptyList_NoError)
{
	Node<int>* s = split(emptyList);
}


TEST_F(LLToolkitTest, Split_SplitAtBeginning_ResultOK)
{
	Node<int>* s = split(n1);
	EXPECT_EQ(s, n2);
}

TEST_F(LLToolkitTest, Split_SplitAtBeginning_SourceNextIsNull)
{
	Node<int>* s = split(n1);
	EXPECT_EQ(n1->next, emptyList);
}


TEST_F(LLToolkitTest, Join_List1IsEmpty_ResultIsCorrect)
{
	Node<int>* list1 = nullptr;
	join(list1, n1);

	EXPECT_EQ(list1, n1);
}


TEST_F(LLToolkitTest, Join_List2IsEmpty_ResultIsCorrect)
{
	Node<int>* list2 = nullptr;
	join(n1, list2);

	EXPECT_EQ(n3->next, nullptr);
}

TEST_F(LLToolkitTest, Join_NonEmptyLists_ResultIsCorrect)
{
	Node<int>* n23 = new Node<int>(23);
	Node<int>* n22 = new Node<int>(22, n23);
	Node<int>* n21 = new Node<int>(21, n22);

	join(n1, n21);

	EXPECT_EQ(n3->next, n21);
}


TEST_F(LLToolkitTest, RotateLeft_EmptyList_NoError)
{
	rotateLeft(emptyList);
}


TEST_F(LLToolkitTest, RotateLeft_SingleElementInList_ResultIsCorrect)
{
	rotateLeft(singleElementList);
	EXPECT_EQ(singleElementList->info, valToInsert);
}


TEST_F(LLToolkitTest, RotateLeft_ThreeElementInList_ListReconnected)
{
	rotateLeft(n1);
	bool result = (
		(n1->info == 2) &&
		(n1->next->info == 3) && 
		(n1->next->next->info == 1)
		);

	EXPECT_TRUE(result);
}

TEST_F(LLToolkitTest, RotateLeft_ThreeElementInList_ListEndsCorrectly)
{
	rotateLeft(n1);
	EXPECT_EQ(n1->next->next->next, nullptr);
}

TEST_F(LLToolkitTest, RotateRight_EmptyList_NoError)
{
	rotateLeft(emptyList);
}


TEST_F(LLToolkitTest, RotateRight_SingleElementInList_ResultIsCorrect)
{
	rotateRight(singleElementList);
	EXPECT_EQ(singleElementList->info, valToInsert);
}


TEST_F(LLToolkitTest, RotateRight_ThreeElementInList_ListReconnected)
{
	rotateRight(n1);
	bool result = (
		(n1->info == 3) &&
		(n1->next->info == 1) &&
		(n1->next->next->info == 2)
		);

	EXPECT_TRUE(result);
}


TEST_F(LLToolkitTest, RotateRight_ThreeElementInList_ListEndsCorrectly)
{
	rotateRight(n1);
	EXPECT_EQ(n1->next->next->next, nullptr);
}