#include "Card.h"

Card::Card(Rank rank, Suit suit) :
  m_rank(rank),
  m_suit(suit)
{

}

Card::Card(const QString &abbreviation)
{
  QChar rank = abbreviation.at(0);
  QChar suit = abbreviation.at(1);

  if (rank == 'A')
  {
    m_rank = Ace;
  }
  else if (rank == 'K')
  {
    m_rank = King;
  }
  else if (rank == 'Q')
  {
    m_rank = Queen;
  }
  else if (rank == 'J')
  {
    m_rank = Jack;
  }
  else if (rank == 'T')
  {
    m_rank = Ten;
  }
  else if (rank == '9')
  {
    m_rank = Nine;
  }
  else if (rank == '8')
  {
    m_rank = Eight;
  }
  else if (rank == '7')
  {
    m_rank = Seven;
  }
  else if (rank == '6')
  {
    m_rank = Six;
  }
  else if (rank == '5')
  {
    m_rank = Five;
  }
  else if (rank == '4')
  {
    m_rank = Four;
  }
  else if (rank == '3')
  {
    m_rank = Three;
  }
  else if (rank == '2')
  {
    m_rank = Two;
  }
  else
  {
    m_rank = UndefinedRank;
  }

  if (suit == 'c')
  {
    m_suit = Clubs;
  }
  else if (suit == 'd')
  {
    m_suit = Diamonds;
  }
  else if (suit == 'h')
  {
    m_suit = Hearts;
  }
  else if (suit == 's')
  {
    m_suit = Spades;
  }
  else
  {
    m_suit = UndefinedSuit;
  }
}

Card::Rank Card::rank()
{
  return m_rank;
}

Card::Suit Card::suit()
{
  return m_suit;
}

QString Card::abbreviation()
{
  QString abbreviation;

  if (m_rank == UndefinedRank || m_suit == UndefinedSuit)
  {
    return abbreviation;
  }

  switch (m_rank)
  {
  case Ace:
    abbreviation.append('A');
    break;

  case King:
    abbreviation.append('K');
    break;

  case Queen:
    abbreviation.append('Q');
    break;

  case Jack:
    abbreviation.append('J');
    break;

  case Ten:
    abbreviation.append('T');
    break;

  case Nine:
    abbreviation.append('9');
    break;

  case Eight:
    abbreviation.append('8');
    break;

  case Seven:
    abbreviation.append('7');
    break;

  case Six:
    abbreviation.append('6');
    break;

  case Five:
    abbreviation.append('5');
    break;

  case Four:
    abbreviation.append('4');
    break;

  case Three:
    abbreviation.append('3');
    break;

  case Two:
    abbreviation.append('2');
    break;
  }

  switch (m_suit)
  {
  case Clubs:
    abbreviation.append('c');
    break;

  case Diamonds:
    abbreviation.append('d');
    break;

  case Hearts:
    abbreviation.append('h');
    break;

  case Spades:
    abbreviation.append('s');
    break;
  }

  return abbreviation;
}
