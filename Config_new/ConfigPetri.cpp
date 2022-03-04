#include <Windows.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>

#define PATH "D:/Рабочий стол/ГУАП/4-ыйКурс Часть 2/Диплом/ConfigPetri.txt"

void FindActiveTransistions();
void PrintActiveTransistions();
void Manually();
void PrintToFile();
long int oper;
const int N = 500, M = 500;
//количество операций
int cond, tran;
//количество состояний и переходов
int Sost[N];
int ch[N];
//массив состояний
int mx1[N][M];
//матрица инцидентности 1
int mx2[M][N];
//матрица инцидентности 2
int buf[M];
//буфер для обработки данных поиска активных переходов
bool fl = true;
std::ofstream fout(PATH);

int main(int argc, char** argv) {
    int chs=2;
    setlocale(LC_ALL, "Russian");
    //std::ofstream fout(PATH);
    std::cout << "Количество переходов: ";

    while (1) {
        std::cin >> oper;
        if (oper <= 0)
            std::cout << "\nВведите число больше нуля." << std::endl;
        else
            break;
    }
   
    switch (chs) {
        std::cout << "\n2.Ввести данные вручную\n\nВыберите режим: ";
        std::cin >> chs;
        chs++;

    case 2: {

        std::cout << "Состояния " << std::endl;
        std::cin >> cond;
        std::cout << "Переходы " << std::endl;
        std::cin >> tran;
        std::cout << "Матрица (построчно: состояние->требуется для каждого перехода) "
            << std::endl;
        fout << "Матрица Доступа Переходов\n";
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
        fout << "Матрица состояний после срабатывания перехода\n";
        std::cout << "Матрица (построчно: переход->получит каждое состояние) " <<
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
        std::cout << "Начальное состояние " << std::endl;
        for (int i = 0; i < cond; i++)
            std::cin >> Sost[i];
        fout << "Последовательность перемещения фишек\n";
        FindActiveTransistions();
        Manually();

    }
          break;
    default:
        break;
    }
}
    void FindActiveTransistions() // Поиск активных переходов
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
    void PrintActiveTransistions() // Вывод активных переходов
    {
        int cnt = 0;
        std::cout << "\n\nАктивные переходы: " << std::endl;
        for (int i = 0; i < tran; i++) {
            if (ch[i] == 1)
                std::cout << i + 1 << " ";
            else
                cnt++;
        }
        fl = true;
        if (cnt == tran) {
            std::cout << "\nАктивных переходов нет!" << std::endl;
            fl = false;
        }
    }

    void Manually() // Выбор перехода 
    {
        std::cout << "Текущая маркировка: ";
        for (int i = 0; i < cond; i++)
            std::cout << Sost[i] << " ";
        PrintToFile();
        int per;
        FindActiveTransistions();
        for (int i = 0; i < oper; i++) {
            
                PrintActiveTransistions();
                if (!fl)
                    break;
                std::cout << "\nВыберите активный переход: ";
                while (1) {
                    std::cin >> per;
                    per--;
                    if (ch[per] == 0)
                        std::cout << "\nПереход не активен или его не существует, выберите другой переход: " << std::endl;
                    else
                        break;
                }
            
            for (int i = 0; i < cond; i++) {
                Sost[i] -= mx1[i][per];
                Sost[i] += mx2[per][i];
            }
            
                std::cout << "Текущая маркировка: ";
                for (int i = 0; i < cond; i++)
                    std::cout << Sost[i] << " ";
                PrintToFile();
            FindActiveTransistions();
        }
    }
    void PrintToFile() // Запись в файл конфигурации 
    {
        fout << "->";
        for (int i = 0; i < cond; i++)
            fout<< Sost[i] << " ";

        fout << "->\n";
    }