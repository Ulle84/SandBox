#ifndef CARD_H
#define CARD_H

#include <QString>

class Card
{
public:

  enum Rank {
    UndefinedRank = 0,
    Ace,
    King,
    Queen,
    Jack,
    Ten,
    Nine,
    Eight,
    Seven,
    Six,
    Five,
    Four,
    Three,
    Two
  };

  enum Suit {
    UndefinedSuit = 0,
    Clubs,
    Diamonds,
    Hearts,
    Spades
  };

  Card(Rank rank, Suit suit);
  Card(const QString& abbreviation);

  Rank rank();
  Suit suit();

  QString abbreviation();

private:
  Rank m_rank;
  Suit m_suit;
};

#endif // CARD_H
