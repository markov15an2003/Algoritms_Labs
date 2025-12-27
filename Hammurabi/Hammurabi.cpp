// Hammurabi.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Hammurabi
{
private:
    fstream save;

    bool game_loaded = false;

    int turn = 1;
    int people = 100;
    float wheat = 2800;
    int acre = 100;

    int const wheat_per_year = 20;
    int const acre_per_people = 10;
    float const wheat_sow_per_acre = 0.5;
    int const plague_percent_chance = 15;
    int const final_turn = 10;

    int price;
    int collected;
    int wheat_multiplier;
    int eaten;
    int died;
    int arrived;
    bool plague;

    float died_in_total = 0;
    bool riot = false;

    int buy;
    int eat;
    int sow;

    void load_game() {
        save >> turn >> people >> wheat >> acre >> price >> collected >> wheat_multiplier >> eaten >> died >>
            arrived >> plague >> died_in_total >> riot;
        game_loaded = true;
    };

    void save_game() {
        save.open("save.txt");
        save << turn << " " << people << " " << wheat << " " << acre << " " << price << " " << collected <<
            " " << wheat_multiplier << " " << eaten << " " << died << " " << arrived << " " << plague << " " <<
            died_in_total << " " << riot;
        save.close();
    };

    bool lose_conditions_check() {
        if (people <= 0)
        {
            cout << "Мой повелитель, всё ваше население погибло!\n";
            return true;
        }
        if (riot)
        {
            cout << "Мой повелитель, более 45% населения погибло с голоду! Народ поднял восстание!\n";
            return true;
        }
        return false;
    };

    bool turn_conditions_check() {
        if ((buy > 0 && (buy * price) > wheat) || (buy < 0 && -buy > acre))
            return false;
        if ((wheat - buy * price) < eat)
            return false;
        if ((wheat - buy * price - eat) < (sow * wheat_sow_per_acre) || (acre + buy) < sow || sow / acre_per_people > people)
            return false;
        return true;
    };

    void next_turn() {
        if (lose_conditions_check()) {
            cout << "---GAME OVER---\n\n";
            save.open("save.txt", ofstream::out | ofstream::trunc);
            save.close();
            return;
        }

        if (turn > 1 && !game_loaded) {
            char answ = ' ';
            while (answ != 'y' && answ != 'n') {
                cout << "Мой повелитель, если вы устали, мы можем сохранить сессию и завершить игру.\n";
                cout << "Продолжить игру? (y/n) ";
                cin >> answ;
                if (answ == 'n') {
                    save_game();
                    return;
                }
            }
        }

        game_loaded = false;

        if (turn > 1) {
            cout << "Мой повелитель, соизволь поведать тебе\n\tв году " << turn - 1 << " твоего высочайшего правления\n\t" <<
                died << " человек умерли с голоду, и " << arrived << " человек прибыли в наш великий город;\n";
            if (plague)
                cout << "\tЧума уничтожила половину населения;\n";
        }
        else {
            cout << "Мой повелитель, соизволь поведать тебе о начале твоего правления\n";
            price = rand() % 10 + 17;
        }
        cout << "\tНаселение города сейчас составляет " << people << " человек;\n";
        if (turn > 1) {
            cout << "\tМы собрали " << collected << " бушелей пшеницы, по " << wheat_multiplier <<
                " бушеля с акра;\n\tКрысы истребили " << eaten << " бушелей пшеницы, оставив " << wheat << " бушеля в амбарах;\n";
        }
        else
            cout << "\tВ амбарах у нас " << wheat << " бушелей пшеницы;\n";
        cout << "\tГород сейчас занимает " << acre << " акров;\n\t1 акр земли стоит сейчас " << price << " бушелей.\n";
        turn++;
        if (turn < final_turn)
            turn_process();
        else
            victory();
    };

    void turn_process() {
        buy = -acre - 1;
        while (!turn_conditions_check()) {
            cout << "Что пожелаешь, повелитель?\nСколько акров земли повелеваешь купить? ";
            cin >> buy;
            if (buy == 0) {
                cout << "Сколько акров земли повелеваешь продать? ";
                cin >> buy;
                buy *= -1;
            }
            cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
            cin >> eat;
            cout << "Сколько акров земли повелеваешь засеять? ";
            cin >> sow;
            if (!turn_conditions_check())
                cout << "О, повелитель, пощади нас! У нас только " << people << " человек, " << wheat <<
                " бушелей пшеницы и " << acre << " акров земли!\n";
        }
        wheat -= buy * price;
        acre += buy;
        wheat -= eat;
        died = people - eat / 20;
        if (died > people * 0.45)
            riot = true;
        died_in_total += (float)died / people * 100;
        people -= died;
        wheat -= sow * wheat_sow_per_acre;
        wheat_multiplier = (rand() % 6 + 1);
        collected = wheat_multiplier * sow;
        wheat += collected;
        eaten = 0.07*(rand() % (int)(wheat + 1));
        wheat -= eaten;
        arrived = (int)((died / 2) + (5 - wheat_multiplier) * wheat / 600 + 1);
        if (arrived < 0)
            arrived = 0;
        else if (arrived > 50)
            arrived = 50;
        people += arrived;
        if (rand() / 100 < plague_percent_chance)
        {
            plague = true;
            people /= 2;
        }
        else
            plague = false;
        price = rand() % 10 + 17;
        cout << "---ПРОШЁЛ ГОД---\n";
        next_turn();
    };

    void victory() {
        cout << "---ИГРА ОКОНЧЕНА---\n";
        if (died_in_total / final_turn > 33 && (float)acre / people < 7)
            cout << "Из-за вашей некомпетентности в\nуправлении, народ устроил бунт, и изгнал вас их города. Теперь вы\nвынуждены влачить жалкое существование в изгнании\n";
        else if (died_in_total / final_turn > 10 && (float)acre / people < 9)
            cout << "Вы правили железной\nрукой, подобно Нерону и Ивану Грозному.Народ вздохнул с\nоблегчением, и никто больше не желает видеть вас правителем\n";
        else if (died_in_total / final_turn > 3 && (float)acre / people < 10)
            cout << "Вы справились вполне неплохо, у вас,\nконечно, есть недоброжелатели, но многие хотели бы увидеть вас во\nглаве города снова\n";
        else
            cout << "Фантастика! Карл Великий,\nДизраэли и Джефферсон вместе не справились бы лучше\n";
        cout << "---ИГРА ОКОНЧЕНА---\n";
    };

public:
    void start_game() {
        char answ = ' ';

        save.open("save.txt");
        if (save.tellg() != 0 || save.peek() != ifstream::traits_type::eof())
            while (answ != 'y' && answ != 'n') {
                cout << "Мой повелитель, у вас имеется незавершённая сессия.\n Желаете ли вы её продолжить? (y/n) ";
                cin >> answ;
                if (answ == 'y')
                    load_game();
                else if (answ == 'n') {
                    save.close();
                    save.open("save.txt", ofstream::out | ofstream::trunc);
                }
                    
            }
        save.close();
        next_turn();
    };
};

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    Hammurabi play_session;
    play_session.start_game();

    system("pause");
    return 0;
}
