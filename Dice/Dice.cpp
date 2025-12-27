// Dice.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

vector<string> split_str(string str, char sep = ' ') {
    vector<string> result;
    int start = 0;
    int end = str.find(sep);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(sep, start);
    }
    result.push_back(str.substr(start));
    return result;
}

struct Dice_specs {
    int amount_;
    int type_;
    int mods_ = 0;

    Dice_specs(int a, int t, int m = 0) : amount_{ a }, type_{ t }, mods_{ m } {
    };
};

Dice_specs str_to_dice_specs(string str) {
    int start = 0;
    int end = str.find('d');
    int amount, type, mods;
    amount = stoi(str.substr(start, end));
    start = end + 1;
    if (str.find('+') == string::npos) {
        if (str.find('-') == string::npos) {
            type = stoi(str.substr(start));
        }
        else {
            end = str.find('-');
            type = stoi(str.substr(start, end - start));
            mods = -1 * stoi(str.substr(end + 1));
        }
    }
    else {
        end = str.find('+');
        type = stoi(str.substr(start, end - start));
        mods = stoi(str.substr(end + 1));
    }
    type = stoi(str.substr(start, end - start));
    return Dice_specs(amount, type, mods);
};

string dice_speecs_to_str(Dice_specs d) {
    string str = to_string(d.amount_) + "d" + to_string(d.type_);
    if (d.mods_ > 0)
        str += "+" + to_string(d.mods_);
    else if (d.mods_ < 0)
        str += "-" + to_string(-1 * d.mods_);
    return str;
}

int dice(vector<Dice_specs> dices) {
    int result = 0;
    for (Dice_specs d : dices) {
        for (int i = 0; i < d.amount_; i++)
            result += rand() % d.type_ + 1;
        result += d.mods_;
    }
    return result;
}

int dice(string dices) {
    int result = 0;
    for (string d_str : split_str(dices, ',')) {
        Dice_specs d = str_to_dice_specs(d_str);
        for (int i = 0; i < d.amount_; i++)
            result += rand() % d.type_ + 1;
        result += d.mods_;
    }
    return result;
}

 template <typename T> void distribution(T rolling_dices, int rolls) {
     vector<int> dist;
     for (int i = 0; i < rolls; i++)
     {
         int roll = dice(rolling_dices);
         if (roll > dist.size())
             dist.resize(roll, 0);
         dist[roll-1]++;
     }
     for (int num : dist)
         cout << num << '\n';
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    distribution("3d10", 10000);

    system("pause");
    return 0;
}
