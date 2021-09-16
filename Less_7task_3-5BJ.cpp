#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Card
{
public:
    enum Suit { Spades, Hearts, Diamonds, Clubs, Trump };
    enum Value { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

    Card(Value val = Ace, Suit su = Trump, bool staopen = true) : value(val), suit(su), stateopen(staopen) {}
    void Flip() { stateopen = !(stateopen);}
    int GetValue() const
    {
        int va = 0;
        if (stateopen)
        {
            va = value;
            if (va > 10)
                va = 10;
        }
        return va;
    }
protected:
    Value value;
    Suit suit;
    bool stateopen;

    friend ostream& operator << (ostream& out, const Card& acard);
};

class Hand
{
protected:
    vector<Card*> m_Cards;
public:
    Hand() { m_Cards.reserve(7); }
    virtual ~Hand()
    {
        Clear();
    }
    void Add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }
    void Clear()
    {
        vector<Card*>::iterator iter = m_Cards.begin();
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            delete* iter;
            *iter = 0;
        }
        m_Cards.clear();
    }
    int GetTotal() const
    {
        if (m_Cards.empty())
            return 0;

        if (m_Cards[0]->GetValue() == 0)
            return 0;

        int sum = 0;
        vector<Card*>::const_iterator iter;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
            sum += (*iter)->GetValue();

        bool ifAce = false;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            if ((*iter)->GetValue() == Card::Ace)
                ifAce = true;
        }

        if (ifAce && sum <= 11)
            sum += 10;

        return sum;
    }
};

class GenericPlayer : public Hand
{
protected:
    string m_name;
public:
    GenericPlayer(const string& name = " ") : m_name(name) { }
    virtual ~GenericPlayer() {}
    virtual bool IsHitting() const = 0;

    bool Is_Busted() const
    {
        return (GetTotal() > 21);
    }
    void Bust() const
    {
        cout << "A player  " << m_name << " Bust!" << endl;
    }

    friend ostream& operator<<(ostream& out, const Card& acard)
    {
        const string suit_name[] = { " Spades", " Hearts", " Diamonds", " Clubs", " Trump" };
        const string value_name[] = { "0", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
        if (acard.stateopen)
            out << value_name[acard.value] << suit_name[acard.suit];
        else
            out << "XX";

        return out;
    };

    friend ostream& operator<<(ostream& out, const GenericPlayer& aGenericPlayer)
    {
        out << aGenericPlayer.m_name << ":\t";

        vector<Card*>::const_iterator pCard;
        if (!aGenericPlayer.m_Cards.empty())
        {
        for (pCard = aGenericPlayer.m_Cards.begin();
            pCard != aGenericPlayer.m_Cards.end();
            ++pCard)

                out << *(*pCard) << "\t";

            if (aGenericPlayer.GetTotal() != 0)
                cout << "(" << aGenericPlayer.GetTotal() << " points)";
        }
        else
            out << "<empty>";

        return out;
    }
};

class Player : public GenericPlayer
{
public:
    Player(const string& name = "") : GenericPlayer(name) {}

    virtual ~Player() {}

    virtual bool IsHitting() const
    {
        char response;
        cout << m_name << ", would you like another card? (Y/N): ";
        cin >> response;
        return (response == 'y' || response == 'Y');
    }
    void Win() const
    {
        cout << m_name << " Wins.\n";
    }
    void Lose() const
    {
        cout << m_name << " Loses.\n";
    }
    void Push() const
    {
        cout << m_name << " Pushes.\n";
    }
};

class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) { }
    virtual ~House() {}
    virtual bool IsHitting() const
    {
        return (GetTotal() <= 16);
    }
    void FlipFirstCard()
    {
        if (!(m_Cards.empty()))
            m_Cards[0]->Flip();
        else
            cout << "No card to flip!\n";
    }
};
//==========================================================================================================================//
//PART-3.Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода: //
//vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.                                    //
//void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle              //
//vold Deal(Hand& aHand) - метод, который раздает в руку одну карту                                                     //
//void AddltionalCards(GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может  //
//и хочет их получать.                                                                                                //
//===================================================================================================================//
class Deck : public Hand
{
public:
    Deck()
    {
        m_Cards.reserve(52);
        Populate();
    }
    virtual ~Deck() {}

    void Populate()
    {
        Clear();
        for (int a = Card::Spades; a <= Card::Trump; ++a)
        {
            for (int i = Card::Ace; i <= Card::King; ++i)
                Add(new Card(static_cast<Card::Value>(i), static_cast<Card::Suit>(a)));
        }
    }
    void Shuffle()
    {
        random_shuffle(m_Cards.begin(), m_Cards.end());
    }
    void Deal(Hand& aHand)
    {
        if (!m_Cards.empty())
        {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else
            cout << "Out of cards. Unable to deal.";
    }
    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        cout << endl;
        while (!(aGenericPlayer.Is_Busted()) && aGenericPlayer.IsHitting())
        {
            Deal(aGenericPlayer);
            cout << aGenericPlayer << endl;

            if (aGenericPlayer.Is_Busted())
                aGenericPlayer.Bust();
        }
    }
};
//======================================================================================================================//
//PART-4. Реализовать класс Game, который представляет собой основной процесс игры. У этого класса будет 3 поля:
// колода карт
// рука дилера
// вектор игроков.
//Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков.В конструкторе 
//создается колода карт и затем перемешивается...
//=====================================================================================================================//

class Game
{
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;

public:
    Game(const vector<string>& names)
    {
        vector<string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName)
        {
            m_Players.push_back(Player(*pName));
        }

        srand(static_cast<unsigned int>(time(0)));
        m_Deck.Populate();
        m_Deck.Shuffle();
    }

    ~Game() {}

    //Также класс имеет один метод play(). 
    void Play()
    {
        vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i)
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                m_Deck.Deal(*pPlayer);

            m_Deck.Deal(m_House);
        }

        m_House.FlipFirstCard();

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            cout << *pPlayer << endl;

        cout << m_House << endl;

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            m_Deck.AdditionalCards(*pPlayer);

        m_House.FlipFirstCard();
        cout << endl << m_House;
        m_Deck.AdditionalCards(m_House);

        if (m_House.Is_Busted())
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->Is_Busted()))
                    pPlayer->Win();
            }
        }
        else
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->Is_Busted()))
                {
                    if (pPlayer->GetTotal() > m_House.GetTotal())
                        pPlayer->Win();
                    else if (pPlayer->GetTotal() < m_House.GetTotal())
                        pPlayer->Lose();
                    else
                        pPlayer->Push();
                }
            }
        }
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            pPlayer->Clear();

        m_House.Clear();
    }
};

//===============================================================================================================//
//PART-5. Написать функцию для ввода имен игроков. Создается объект класса Game и запускается игровой процесс.  //
//Предусмотреть возможность повторной игры.                                                                    //
//============================================================================================================//

void part_5()
{
    cout << "\t\tLet's play Blackjack!\n\n";

    int PlayersValue = 0;
    while (PlayersValue < 1 || PlayersValue > 7)
    {
        cout << "How many players will there be? (1 - 7): ";
        cin >> PlayersValue;
    }

    vector<string> Players_N;
    string name;
    for (int i = 0; i < PlayersValue; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        Players_N.push_back(name);
    }
    cout << endl;

    //Предусмотреть возможность повторной игры.
    Game rep_Game(Players_N);
    char replay = 'y';
    while (replay != 'n' && replay != 'N')
    {
        rep_Game.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> replay;
    }
}

int main()
{
cout << endl << "PART3-5.\n=====================================================" << endl << endl;
{
	part_5();
}

	return 0;
}
