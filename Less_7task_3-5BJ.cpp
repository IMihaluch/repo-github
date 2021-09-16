#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

enum Suit { Spades, Hearts, Diamonds, Clubs, Trump };
enum Value { Zero, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card
{
protected:
    Value value;
    Suit suit;
    bool stateopen;
public:
    Card(Value val, Suit su, bool staopen = true) : value(val), suit(su), stateopen(staopen) { }
    void Flip() { stateopen = !stateopen; }
    int GetValue() const
    {
        if (stateopen)
            return value;
        else
            return 0;
    }
    friend ostream& operator << (ostream& out, const Card& acard);
    ~Card() { }
};

class Hand
{
protected:
    vector<Card*>m_Cards;
public:
    Hand() { }
    virtual ~Hand()
    {
        Clear();
    }
    void add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }
    void Clear()
    {
        if (m_Cards.empty())
            return;
        else
        {
            for (int index = 0; index < m_Cards.size(); index++)
            {
                delete m_Cards[index];
                m_Cards[index] = nullptr;
            }
            m_Cards.resize(0);
        }
    }
    int GetTotal() const
    {
        int verify = 0;
        int sum = 0;
        for (int index = 0; index < m_Cards.size(); index++)
        {
            if (m_Cards[index]->GetValue() > 10) {

            sum += 10;
        } 
          else
          {
            sum += m_Cards[index]->GetValue();
          }
            if (m_Cards[index]->GetValue() == Ace)
                verify++;
        }
        while (verify > 0)
        {
            if (sum + 10 <= 21 && verify == 1)
            {
                sum += 10;
            }
            verify--;
        }
        return sum;
    }
};

class GenericPlayer : public Hand
{
protected:
    string m_name;
public:
    GenericPlayer(string name = " ") : m_name(name) { };
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
    friend ostream& operator<< (ostream& out, const GenericPlayer& aGenericPlayer);
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
