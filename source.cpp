#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
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
string customTime();
bool isEmpty(string arr[3][3]);
void park_lot();
void nhapXe(string arr[3][3], string time_in[3][3], double time_in_num[3][3], int x);
void luuFile(string biensoxe, string time_in, double time_num, int x);
void docFile();
void khoiphucArr();
void output_arr();
void menu();
void select();
/*-----------------CTRL + Click DE NHAY TOI HAM DINH NGHIA----------------------*/


// GET RANDOM //
int Random(int min, int  max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

// BIEN SO XE //
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

// GET TIME //


// PARKING LOT //
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
        nhapXe(lot_1, time_in_char_1, time_in_num_1, x);
        break;
    case 2:
        nhapXe(lot_2, time_in_char_2, time_in_num_2, x);
        break;
    case 3:
        nhapXe(lot_3, time_in_char_3, time_in_num_3, x);
        break;
    default:
        cout << "Khong co bai xe nay, hay chon lai!" << endl;
        goto retry;
    }
}

void nhapXe(string arr[3][3], string time_in_char[3][3], double time_in_num[3][3], int x)
{
    bool isParked = false;
    if (isEmpty(arr))
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (arr[i][j] == "")
                {   
                    time_t now = time(0);
                    char* dt = ctime(&now);
                    string biensoxe = taoBiensoxe();
                    arr[i][j] = biensoxe;
                    time_in_char[i][j] = dt;
                    time_in_num[i][j] = now;
                    cout << "Gui xe thanh cong!" << endl;
                    cout << "Bien so xe: " << biensoxe << endl;
                    cout << "Xe duoc gui vao vi tri " << (char)(i + 65) << j + 1 << endl;
                    cout << "Thoi gian gui xe: " << dt << endl;
                    luuFile(biensoxe, dt, now, x);
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
            cout << time_in_num_1[i][j] << " ";
        }
        cout << endl;
    }
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
string customTime()
{
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
    char* custom_char = ctime(&custom);
    return custom_char;
    
}

/*----------------------File-------------------------*/
void taoFile()
{
    fstream create, create1, create2, create3;

    create.open("baocaohangngay.txt");
    if (!create.is_open())
    {
        create.open("baocaohangngay.txt", ios::out);
        create.close();
    }

    create1.open("khoiphucbaixe1.txt");
    if (!create1.is_open())
    {
        create1.open("khoiphucbaixe1.txt", ios::out);
        create1.close();
    }

    create2.open("khoiphucbaixe2.txt");
    if (!create2.is_open())
    {
        create2.open("khoiphucbaixe2.txt", ios::out);
        create2.close();
    }

    create3.open("khoiphucbaixe3.txt");
    if (!create3.is_open())
    {
        create3.open("khoiphucbaixe3.txt", ios::out);
        create3.close();
    }
}

void luuFile(string biensoxe, string time_in, double time_num, int x)
{
    ofstream save1, save2, save3;
    switch (x)
    {
    case 1:
        save1.open("khoiphucbaixe1.txt", ios::app);
        save1 << biensoxe << endl;
        save1 << time_in;
        save1 << time_num << endl;
        save1.close();
        break;
    case 2:
        save2.open("khoiphucbaixe2.txt", ios::app);
        save2 << biensoxe << endl;
        save2 << time_in;
        save2 << time_num << endl;
        save2.close();
        break;
    case 3:
        save3.open("khoiphucbaixe3.txt", ios::app);
        save3 << biensoxe << endl;
        save3 << time_in;
        save3 << time_num << endl;
        save3.close();
        break;
    }
}
void docFile()
{
    ifstream in;
    in.open("baocaohangngay.txt");
    if (in.is_open())
    {
        int total_line = 0, count = 0;
        string biensoxe, time_in, lines;
        while (!in.eof())
        {
            getline(in, lines);
            total_line++;
        }
        in.clear();
        in.seekg(0, ios::beg);
        while (!in.eof())
        {
            getline(in, biensoxe);
            getline(in, time_in);
            cout << biensoxe << "     " << time_in << endl;
            count += 2;
            if (count == total_line - 1)
            {
                break;
            }
        }

        in.close();
    }
    else
    {
        cout << "File chua duoc tao, vui long tao file baitaplon.txt \n";
    }
}

void khoiphucArr()
{
    string xe1, xe2, xe3, time1, time2, time3;
    double num1, num2, num3;
    ifstream recover1, recover2, recover3;
    recover1.open("khoiphucbaixe1.txt");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            getline(recover1, xe1);
            lot_1[i][j] = xe1;
            getline(recover1, time1);
            time_in_char_1[i][j] = time1;
            recover1 >> num1;
            time_in_num_1[i][j] = num1;
            recover1.ignore();
        }
    }
    recover1.close();

    recover2.open("khoiphucbaixe2.txt");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            getline(recover2, xe2);
            lot_2[i][j] = xe2;
            getline(recover2, time2);
            time_in_char_2[i][j] = time2;
            recover2 >> num2;
            time_in_num_2[i][j] = num2;
            recover2.ignore();
        }
    }
    recover2.close();

    recover3.open("khoiphucbaixe3.txt");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            getline(recover3, xe3);
            lot_3[i][j] = xe3;
            getline(recover3, time3);
            time_in_char_3[i][j] = time3;
            recover3 >> num3;
            time_in_num_3[i][j] = num3;
            recover3.ignore();
        }
    }
    recover3.close();
    
}

void cleanFile()
{
    fstream clean, clean1, clean2, clean3;
    clean.open("baocaohangngay.txt", ios::out);
    clean.close();
    clean1.open("khoiphucbaixe1.txt", ios::out);
    clean1.close();
    clean2.open("khoiphucbaixe2.txt", ios::out);
    clean2.close();
    clean3.open("khoiphucbaixe3.txt", ios::out);
    clean3.close();
}
/*---------------------------------------------------*/



int main()
{
    taoFile();
    khoiphucArr();
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
    cout << "                    QUAN LY 3 BAI XE (3 X 3)                      " << endl;
    cout << " *---------------------------------------------------------------*" << endl;
    cout << " | Option 1 : Gui xe vao bai                                     |" << endl;
    cout << " | Option 2 : Cho xe ra bai, tinh tien gui xe                    |" << endl;
    cout << " | Option 3 : In bao cao hang ngay                               |" << endl;
    cout << " | Option 4 : Tim vi tri cua xe                                  |" << endl;
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
    //case 2: //Xuat xe ra bai
    //    customTime();
    //    break;
    //case 3:
    //    docFile();
    //    break;
    case 4: //Kiem tra mang lot_1
        output_arr();
    case 5: //Xoa du lieu tat ca file
        cleanFile();
        break;
    default:
        cout << "Khong co option nay\n";
    }
}
