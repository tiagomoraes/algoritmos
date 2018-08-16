#include <iostream>
#define endl '\n'

using namespace std;

int convertDate(int date);

int main() {
    int date;
    cin >> date;

    int result;
    result = convertDate(date);

    cout << result << endl;

    return 0;
}

int convertDate(int date) {
    int result;

    if(date == 0) {
        result = 12;
    } else if(date <= 12) {
        result = date;
    } else {
        result = (date - 12);
    }

    return result;
}