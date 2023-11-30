#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
#include <fstream>
using namespace std;

/*-------------------------------HAM SU DUNG------------------------------------*/
int Random(int min, int max);
string taoBiensoxe();
bool isEmpty(string arr[3][3]);
void park_lot();
void nhapXe(string arr[3][3], string time_in[3][3], double tim_in_num[3][3]);
void time();
void ghiFile(string biensoxe, string time_in);
void docFile();
void output_arr();
void menu();
void select();
/*-------------------------------------------------------------------------------*/


int Random(int min, int  max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
//Chia Khu
string lot_1[3][3], lot_2[3][3], lot_3[3][3];
string time_in_char_1[3][3], time_in_char_2[3][3], time_in_char_3[3][3];
double time_in_num_1[3][3], time_in_num_2[3][3], time_in_num_3[3][3];
bool isEmpty(string arr[3][3])
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

void park_lot()
{
    int x;
    retry:
    cout << "Chon bai xe muon gui (1/2/3): ";
    cin >> x;
    switch (x)
    {
    case 1:
        nhapXe(lot_1, time_in_char_1, time_in_num_1);
        break;
    case 2:
        nhapXe(lot_2, time_in_char_2, time_in_num_2);
        break;
    case 3:
        nhapXe(lot_3, time_in_char_3, time_in_num_3);
        break;
    default:
        cout << "Khong co bai xe nay, hay chon lai!";
        goto retry;
    }
}

void nhapXe(string arr[3][3], string time_in_char[3][3], double time_in_num[3][3])
{
    bool isParked = false;
    time_t now = time(0);
    char* dt = ctime(&now);
    if (isEmpty(arr))
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (arr[i][j] == "")
                {   
                    string biensoxe = taoBiensoxe();
                    cout << biensoxe << endl;
                    arr[i][j] = biensoxe;
                    time_in_char[i][j] = dt;
                    time_in_num[i][j] = now;
                    cout << "Gui xe thanh cong!" << endl;
                    cout << "Thoi gian gui xe: " << dt << endl;
                    ghiFile(biensoxe, dt);
                    isParked = true;
                    break;
                }
            }
            if (isParked == true)
            {
                break;
            }
        }
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
            cout << lot_1[i][j] << " ";
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
    const string chucai = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    string bienso;
    //thay đổi giá trị ngẫu nhiên của hàm random
    srand((unsigned int)time(NULL));
    //tạo giá trị cho chuỗi 
    for (int i = 0; i < 9; i++)
    {
        if (i == 2)
        {
            bienso += '-';
            continue;
        }
          
        if (i == 3)
            bienso += chucai[Random(0, 25)];
        else 
            bienso += chucai[Random(26, 35)];
   
    }

    return bienso;
}

void time()// tra ve date/time hien tai dua tren system hien tai
{
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << dt;
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

//Thoi gian xuat xe
void timeXuatxe()
{
    
}

// Chenh lech //
void diffTime()
{
    time_t now = time(0);
    int hour, min, sec, day, month, year;
    cout << "Nhap thoi gian xuat xe (gio, phut, giay, ngay, thang, nam): ";
    cin >> hour >> min >> sec >> day >> month >> year;

    struct tm* customtime = new tm;
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

// File //
void ghiFile(string biensoxe, string time_in)
{
    ofstream out;
    out.open("baitaplon.txt", ios::app);
    out << biensoxe << endl;
    out << time_in;
    out.close();
}
void docFile()
{
    string lines;
    ifstream in;
    in.open("baitaplon.txt");
    while (!in.eof())
    {
        getline(in, lines);
        cout << lines << endl;
    }

    in.close();
}
void cleanFile()
{
    fstream clean;
    clean.open("baitaplon.txt", ios::out);
    clean.close();
}

int main()
{
    while (true)
    {
        int n;
        cout << "Ban co muon tiep tuc ko? (1/0): ";
        cin >> n;
        if (n == 1)
        {
            system("cls");
            menu();
            select();
        }
        else
        {
            cout << "Ket thuc!" << endl;
            break;
        }
    }

    return 0;
}

void menu()
{
    cout << " *---------------------------------------------------------------*" << endl;
    cout << " | option 1 : gui xe vao bai, chia vi tri, lay thoi gian xe vao  |" << endl;
    cout << " | option 2 : cho xe e ra , lay thoi gian xe ra, tinh tien gui xe|" << endl;
    cout << " | option 3 : mo danh sach xe gui da luu                         |" << endl;
    cout << " | option 4 : tra cuu vi tri de xe                               |" << endl;
    cout << " *---------------------------------------------------------------*" << endl;
}

void select()
{
    int choice;
    cout << "Moi chon option: ";
    cin >> choice;
    switch (choice)
    {
    case 1: //Nhap xe vao bai
        park_lot();
        break;
    case 2: //Xuat xe ra bai
        diffTime();
        break;
    case 3:
        docFile();
        break;
    case 4:
        output_arr();
    case 5: //Xoa du lieu trong file
        cleanFile();
        break;
    default:
        cout << "Khong co option nay\n";
    }
}
