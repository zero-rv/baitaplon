#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <ctime>
#include <string>
#include <ctype.h>
#include <fstream>
using namespace std;
const string chucai = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
struct Baixe
{
    string biensoxe = "";
    time_t timein = 0;
    time_t timeout = 0;
    double tienxe = 0;
};
Baixe baixe1[3][4];
Baixe baixe2[3][4];
Baixe baixe3[3][4];

/*-------------------------------HAM SU DUNG------------------------------------*/
int Random(int min, int max);
string taoBiensoxe();
void inputCustomtime();
string customTime_char(int& hour, int& min, int& sec, int& day, int& month, int& year);
unsigned long long customTime_num(int& hour, int& min, int& sec, int& day, int& month, int& year);
bool isEmpty(Baixe baixe[3][4]);
void park_lot();
void nhapXe(Baixe baixe[3][4]);
void luuFile();
void khoiphuc();
void cleanFile();
void luu_Baocao();
void doc_Baocao();
void output_arr();
bool isHople(string car);
void timXe();
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
    string bienso;
    // reset o nho cua Random
    srand((unsigned int)time(NULL));
    // tao bien so 
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


/*---------------------------------------------------BAI DO XE-------------------------------------------------------------*/
bool isEmpty(Baixe baixe[3][4])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (baixe[i][j].biensoxe == "")
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
        nhapXe(baixe1);
        break;
    case 2:
        nhapXe(baixe2);
        break;
    case 3:
        nhapXe(baixe3);
        break;
    default:
        cout << "Khong co bai xe nay, hay chon lai!" << endl;
        goto retry;
    }
}

/* OPTION 1 */
void nhapXe(Baixe baixe[3][4])
{
    bool isParked = false;
    if (isEmpty(baixe))
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (baixe[i][j].biensoxe == "")
                {
                    baixe[i][j].biensoxe = taoBiensoxe();
                    baixe[i][j].timein = time(0);
                    cout << "Gui xe thanh cong!" << endl;
                    cout << "Bien so xe: " << baixe[i][j].biensoxe << endl;
                    cout << "Xe duoc gui vao vi tri " << (char)(i + 65) << j + 1 << endl;
                    cout << "Thoi gian gui xe: " << ctime(&baixe[i][j].timein) << endl;
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
/*----------------------------------------------------------------------------------------------------------------------------*/

void output_arr()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << baixe1[i][j].biensoxe << " ";
        }
        cout << endl;
    }
}

// TINH TIEN XE
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

/*--------------------------------LAY THOI GIAN NHAP VAO-------------------------------------*/
void inputCustomtime()
{
    int hour, min, sec, day, month, year;
    cout << "Nhap thoi gian xuat xe (gio, phut, giay, ngay, thang, nam): ";
    cin >> hour >> min >> sec >> day >> month >> year;
    customTime_char(hour, min, sec, day, month, year);
    customTime_num(hour, min, sec, day, month, year);
}

string customTime_char(int& hour, int& min, int& sec, int& day, int& month, int& year)
{
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

unsigned long long customTime_num(int& hour, int& min, int& sec, int& day, int& month, int& year)
{
    struct tm* customtime = new tm;
    customtime->tm_hour = hour;
    customtime->tm_min = min;
    customtime->tm_sec = sec;
    customtime->tm_mday = day;
    customtime->tm_mon = month - 1;
    customtime->tm_year = year - 1900;

    time_t custom = mktime(customtime);
    delete customtime;
    return custom;
}
/*---------------------------------------------------------------------------------------------*/

// BIEN SO XE HOP LE
bool isHople(string car)
{
    if (car.length() != 9)
    {
        cout << "Bien so xe khong hop le! Bien so xe phai co 9 ki tu \n";
        return false;
    }
    if (car[2] != '-')
    {
        cout << "Bien so xe khong hop le! Can 1 dau '-' o vi tri so 3 \n";
        return false;
    }
    if (!isupper(car[3]))
    {
        cout << "Bien so xe khong hop le! Can 1 chu cai in hoa o vi tri so 4 \n";
        return false;
    }
    return true;
}
/* OPTION 4 */
void timXe()
{
    bool isFound = false;
    string car;
retry:
    cout << "Nhap bien so xe muon tim: ";
    cin >> car;
    if (!isHople(car))
    {
        goto retry;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (baixe1[i][j].biensoxe == car)
            {
                cout << "Xe dang o bai xe so 1, vi tri " << (char)(i + 65) << j + 1 << endl;
                isFound = true;
                break;
            }

            if (baixe2[i][j].biensoxe == car)
            {
                cout << "Xe dang o bai xe so 2, vi tri " << (char)(i + 65) << j + 1 << endl;
                isFound = true;
                break;
            }

            if (baixe3[i][j].biensoxe == car)
            {
                cout << "Xe dang o bai xe so 3, vi tri " << (char)(i + 65) << j + 1 << endl;
                isFound = true;
                break;
            }
        }
        if (isFound)
        {
            break;
        }
    }
    if (!isFound)
    {
        cout << "Khong tim thay xe!" << endl;
    }
}

/*----------------------File-------------------------*/
void luuFile()
{
    ofstream save1, save2, save3;
    save1.open("khoiphucbaixe1.txt");
    save2.open("khoiphucbaixe2.txt");
    save3.open("khoiphucbaixe3.txt");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //Baixe1
            save1 << baixe1[i][j].biensoxe << endl;
            save1 << baixe1[i][j].timein << endl;
            //Baixe2
            save2 << baixe2[i][j].biensoxe << endl;
            save2 << baixe2[i][j].timein << endl;
            //Baixe3
            save3 << baixe3[i][j].biensoxe << endl;
            save3 << baixe3[i][j].timein << endl;
        }
    }
    save1.close();
    save2.close();
    save3.close();
}

void khoiphuc()
{
    int total = 0, count = 0;
    string xe;
    time_t time;
    ifstream recover1, recover2, recover3;
    recover1.open("khoiphucbaixe1.txt");
    recover2.open("khoiphucbaixe2.txt");
    recover3.open("khoiphucbaixe3.txt");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //Baixe1
            getline(recover1, xe);
            baixe1[i][j].biensoxe = xe;
            recover1 >> time;
            baixe1[i][j].timein = time;
            recover1.ignore();
            //Baixe2
            getline(recover2, xe);
            baixe2[i][j].biensoxe = xe;
            recover2 >> time;
            baixe2[i][j].timein = time;
            recover2.ignore();
            //Baixe3
            getline(recover3, xe);
            baixe3[i][j].biensoxe = xe;
            recover3 >> time;
            baixe3[i][j].timein = time;
            recover3.ignore();
        }
    }
    recover1.close();
    recover2.close();
    recover3.close();
}

void luu_Baocao()
{
    ofstream out;
    out.open("baocaohangngay.txt");

}

void doc_Baocao()
{
    ifstream in;
    in.open("baocaohangngay.txt");
    int total_line = 0, count = 0;
    string biensoxe, time_in, time_out, fee, lines;
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
        getline(in, time_out);
        getline(in, fee);
        cout << biensoxe << "     " << time_in << "     " << time_out << "     " << fee << "VND" << endl;
        count += 4;
        if (count == total_line - 3)
        {
            break;
        }
    }
    in.close();
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
    khoiphuc();
    while (true)
    {
        int n;
        cout << endl << "Ban co muon tiep tuc khong? (1/0): ";
        cin >> n;
        if (n == 1)
        {
            system("cls");
            menu();
            select();
        }
        else
        {
            luuFile();
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
    case 1:
        park_lot();
        break;
        //case 2: //Xuat xe ra bai
        //    customTime();
        //    break;
        //case 3:
        //    docFile();
        //    break;
    case 4:
        timXe();
        break;
    case 5: // In mang de kiem tra
        output_arr();
        break;
    //case 6: // Xoa du lieu tat ca file
    //    cleanFile();
    //    break;
    default:
        cout << "Khong co option nay!" << endl;
    }
}

