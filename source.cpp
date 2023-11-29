#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
#include <fstream>
using namespace std;
//Ham su dung
int Random(int min, int max);
string taoBiensoxe();
bool isEmpty();
void auto_input_arr();
void time();
void ghiFile();
void docFile();

//Struct 

int Random(int min, int  max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
//Chia Khu
string arr[3][3];
bool isEmpty()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == "")
                return true;
        }
    }
    return false;
}
void auto_input_arr()
{
    int i, j;
    retry:
    i = Random(0, 2);
    j = Random(0, 2);
    if (isEmpty())
    {
        if (arr[i][j] == "")
        {
            string biensoxe = taoBiensoxe();
            cout << biensoxe << endl;
            arr[i][j] = biensoxe;
            cout << "Gui xe thanh cong tai hang " << i << ", cot " << j << endl;
        }
        else goto retry;
    }
    else
    {
        cout << "Bai xe da day, khong the gui! \n";
    }
}


void output_arr()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
// for (int i =0, i< n , i++)
// pair < string n , int m > xe i = < taobiensoxe() , chia khu ()> 
// string n :
//{
//  if string == xe i . first 
// cout xe i . second 

string taoBiensoxe()
{
    // tạo chuỗi   trung gian 
    const string chucai = "-QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    string bienso;
    //thay đổi giá trị ngẫu nhiên của hàm random
    srand((unsigned int)time(NULL));
    //tạo giá trị cho chuỗi 
    for (int i = 0; i < 9; i++)
    {
        if (i == 2)
        {
            bienso += chucai[0];
            continue;
        }
          
        if (i == 3)
        {
            bienso += chucai[Random(1, 26)];
            continue;
        }
           
        bienso += chucai[Random(27, 36)];
    }
    return bienso;
}

void time()
{
    // tra ve date/time hien tai dua tren system hien tai
    time_t hientai = time(0);
    // chuyen doi hientai thanh dang chuoi
    char* dt = ctime(&hientai);
    cout << dt << endl;
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
void ghiFile()
{
    fstream btl;
    btl.open("baitaplon.txt", ios::app);
    btl << taoBiensoxe() << endl;
    btl.close();
}

// Chenh lech //
void diffTime()
{
    time_t now = time(0);
    int hour, min, sec, day, month, year;
    cout << "Nhap thoi gian xuat xe (gio, phut, giay, ngay, thang, nam): ";
    cin >> hour >> min >> sec >> day >> month >> year;

    struct tm *customtime = new tm;
    customtime->tm_hour = hour;
    customtime->tm_min = min;
    customtime->tm_sec = sec;
    customtime->tm_mday = day;
    customtime->tm_mon = month - 1;
    customtime->tm_year = year - 1900;
    
    time_t custom = mktime(customtime);
    delete customtime;
    int diff = custom - now;
    cout << "So tien phai tra: " << tien_xe(diff);
    
}

void docFile()
{
    string bienso, time;
    fstream btl;
    btl.open("baitaplon.txt");

    btl >> bienso;
    btl.ignore();
    getline(btl, time);
    cout << bienso << endl;
    cout << time;

    btl.close();
}

int main()
{

    int key, choice;
    do
    {
        system("cls");
        std::cout << "Moi chon option: ";
        cin >> key;
        switch (key)
        {
        case 1: // Nhap xe
            auto_input_arr();
            
            
            break;
        case 2:
            output_arr();
            
            
            break;
        default:
            cout << "Khong co option nay\n";
        }
        cout << "Tiep tuc? (1/0): ";
        cin >> choice;
        if (!choice)
        {
            cout << "Bye Bye!";
            break;
        }
    } while (key != 0);
    return 0;
}
// option 1: lấy thời gian tạo biển số , chia khu , sau đó ghi vô file để lưu ,option 2 : lấy thời gian ghi vô file tính tiền ghi tiêrnf vô file , option 3 đọc file 
