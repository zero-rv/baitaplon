#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// Cac ham su dung //
int Random(int min, int max);
string taobiensoxe();
int tien_xe(int secs);
void input_time();

// Main //
int main()
{
    cout << taobiensoxe() << endl;
    input_time();
    return 0;
}

// Functions
int Random(int min, int  max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

string taobiensoxe()
{
    // tao chuoi trung gian 
    const string chucai = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    string bienso;
    // reset o nho cua chuoi
    srand((unsigned int)time(NULL));
    // tao chuoi
    for (int i = 0; i < 8; i++)
    {
        if (i != 2)
        {
            bienso += chucai[Random(26, 35)];
        }
        else
        {
            bienso += chucai[Random(0, 25)];
        }
    }
    return bienso;
}


// Tinh tien xe //
int sum = 50000, dem = -1;
int tien_xe(int secs)
{
    if (secs > 0)
    {
        dem++;
        return tien_xe(secs - 1800);
    }
    sum += dem * 30000;
    return sum;
}

// Chenh lech thoi gian //
void input_time()
{   
    time_t now = time(0);
    int hour, min, sec, date, month, year;
    cout << "Nhap thoi gian xuat xe (gio, phut, giay, ngay, thang, nam)  ";
    cin >> hour >> min >> sec >> date >> month >> year;

    tm *customtime; //luu thoi gian bat ky
    customtime->tm_hour = hour;
    customtime->tm_min = min;
    customtime->tm_sec = sec;
    customtime->tm_mday = date;
    customtime->tm_mon = month - 1; // 0 -> 11 nen phai lay month - 1
    customtime->tm_year = year - 1900;

    time_t custom; //chuyen thoi gian bat ky ve so giay
    custom = mktime(customtime);
    int chenh_lech = custom - now;
    cout << "So tien phai tra: " << tien_xe(chenh_lech);
}
