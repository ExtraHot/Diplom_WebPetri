#include <Windows.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>

#define PATH "D:/������� ����/����/4-������ ����� 2/������/ConfigPetri.txt"

void FindActiveTransistions();
void PrintActiveTransistions();
void Manually();
void PrintToFile();
long int oper;
const int N = 500, M = 500;
//���������� ��������
int cond, tran;
//���������� ��������� � ���������
int Sost[N];
int ch[N];
//������ ���������
int mx1[N][M];
//������� ������������� 1
int mx2[M][N];
//������� ������������� 2
int buf[M];
//����� ��� ��������� ������ ������ �������� ���������
bool fl = true;
std::ofstream fout(PATH);

int main(int argc, char** argv) {
    int chs=2;
    setlocale(LC_ALL, "Russian");
    //std::ofstream fout(PATH);
    std::cout << "���������� ���������: ";

    while (1) {
        std::cin >> oper;
        if (oper <= 0)
            std::cout << "\n������� ����� ������ ����." << std::endl;
        else
            break;
    }
   
    switch (chs) {
        std::cout << "\n2.������ ������ �������\n\n�������� �����: ";
        std::cin >> chs;
        chs++;

    case 2: {

        std::cout << "��������� " << std::endl;
        std::cin >> cond;
        std::cout << "�������� " << std::endl;
        std::cin >> tran;
        std::cout << "������� (���������: ���������->��������� ��� ������� ��������) "
            << std::endl;
        fout << "������� ������� ���������\n";
        for (int i = 0; i < cond; i++)
        {
            
            for (int j = 0; j < tran; j++)
            {
                std::cin >> mx1[i][j];
                fout << mx1[i][j]<<" ";
            }
            fout << "\n";
        }
        fout << "\n";
        fout << "������� ��������� ����� ������������ ��������\n";
        std::cout << "������� (���������: �������->������� ������ ���������) " <<
            std::endl;
        for (int i = 0; i < tran; i++)
        {
            for (int j = 0; j < cond; j++)
            {
                std::cin >> mx2[i][j];
                fout << mx2[i][j] << " ";
            }
            fout << "\n";
        }
        fout << "\n";
        std::cout << "��������� ��������� " << std::endl;
        for (int i = 0; i < cond; i++)
            std::cin >> Sost[i];
        fout << "������������������ ����������� �����\n";
        FindActiveTransistions();
        Manually();

    }
          break;
    default:
        break;
    }
}
    void FindActiveTransistions() // ����� �������� ���������
    {
        for (int i = 0; i < tran; i++)
            ch[i] = 0;
        for (int i = 0; i < cond; i++)
        {
            if (Sost[i] >= 1)
            {
                for (int j = 0; j < tran; j++)
                {
                    if (Sost[i] <= mx1[i][j])
                    {
                        ch[j] = 1;
                    }
                }

            }
        }
    }
    void PrintActiveTransistions() // ����� �������� ���������
    {
        int cnt = 0;
        std::cout << "\n\n�������� ��������: " << std::endl;
        for (int i = 0; i < tran; i++) {
            if (ch[i] == 1)
                std::cout << i + 1 << " ";
            else
                cnt++;
        }
        fl = true;
        if (cnt == tran) {
            std::cout << "\n�������� ��������� ���!" << std::endl;
            fl = false;
        }
    }

    void Manually() // ����� �������� 
    {
        std::cout << "������� ����������: ";
        for (int i = 0; i < cond; i++)
            std::cout << Sost[i] << " ";
        PrintToFile();
        int per;
        FindActiveTransistions();
        for (int i = 0; i < oper; i++) {
            
                PrintActiveTransistions();
                if (!fl)
                    break;
                std::cout << "\n�������� �������� �������: ";
                while (1) {
                    std::cin >> per;
                    per--;
                    if (ch[per] == 0)
                        std::cout << "\n������� �� ������� ��� ��� �� ����������, �������� ������ �������: " << std::endl;
                    else
                        break;
                }
            
            for (int i = 0; i < cond; i++) {
                Sost[i] -= mx1[i][per];
                Sost[i] += mx2[per][i];
            }
            
                std::cout << "������� ����������: ";
                for (int i = 0; i < cond; i++)
                    std::cout << Sost[i] << " ";
                PrintToFile();
            FindActiveTransistions();
        }
    }
    void PrintToFile() // ������ � ���� ������������ 
    {
        fout << "->";
        for (int i = 0; i < cond; i++)
            fout<< Sost[i] << " ";

        fout << "->\n";
    }