#include <gtest/gtest.h>
#include "../src/Card.h"
#include "../src/Deck.h"


// testing test suite integration
TEST(MainTestSuite, TestingTests) {
    ASSERT_EQ(2 + 2, 4);
}

// test the creation of a new card
TEST(CardTestSuite, CardCreation) {
    Card newCard("Front", "Back");
    EXPECT_EQ(newCard.getFront(), "Front") << "Front value is incorrect";
    EXPECT_EQ(newCard.getBack(), "Back") << "Back value is incorrect";
}

// test for empty card creation
TEST(CardTestSuite, EmptyStrings) {
    Card emptyCard("", "");
    EXPECT_EQ(emptyCard.getFront(), "");
    EXPECT_EQ(emptyCard.getBack(), "");
}

// test for whitespace handling when creating cards
TEST(CardTestSuite, WhitespaceHandling) {
    Card cardWithSpaces("  Front  ", "  Back  ");
    EXPECT_EQ(cardWithSpaces.getFront(), "  Front  ") << "Front value does not handle whitespace";
    EXPECT_EQ(cardWithSpaces.getBack(), "  Back  ") << "Back value does not handle whitespace";
}

// test for equality between two cards
TEST(CardTestSuite, EqualityCheck) {
    Card card1("Front", "Back");
    Card card2("Front", "Back");
    EXPECT_EQ(card1.getFront(), card2.getFront()) << "Two equal cards do not match";
    EXPECT_EQ(card1.getBack(), card2.getBack()) << "Two equal cards do not match";
}



// test for deck creation
TEST(DeckTest, AddCard) {
    Deck deck;
    Card card("Front", "Back");
    deck.addCard(card);
    
    vector<Card> cards = deck.getCards();
    ASSERT_EQ(cards.size(), 1);
    ASSERT_EQ(cards[0].getFront(), "Front");
    ASSERT_EQ(cards[0].getBack(), "Back");
}

// test for empty deck
TEST(DeckTest, GetCardsEmptyDeck) {
    Deck deck;
    vector<Card> cards = deck.getCards();
    ASSERT_TRUE(cards.empty());
}

// test for integration with text file
TEST(DeckIntegrationTest, ReadCardsFromFile) {
    Deck deck("test_txt_files/prompt_iteration_test.txt");
    vector<Card> cards = deck.getCards();
    ASSERT_FALSE(cards.empty()) << "Deck array is empty";

    ASSERT_EQ(cards[0].getFront(), "Card front 1") << "Card front 1 does not match text file";
    ASSERT_EQ(cards[0].getBack(), "Card back 1") << "Card back 1 does not match text file";

    ASSERT_EQ(cards[1].getFront(), "Card front 2") << "Card front 2 does not match text file";
    ASSERT_EQ(cards[1].getBack(), "Card back 2") << "Card back 2 does not match text file";

    ASSERT_EQ(cards[2].getFront(), "Card front 3") << "Card front 3 does not match text file";
    ASSERT_EQ(cards[2].getBack(), "Card back 3") << "Card back 3 does not match text file";
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}