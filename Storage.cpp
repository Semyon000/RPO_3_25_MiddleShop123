#include "Storage.hpp"

size_t sizeSt = 0;
size_t* idArr = nullptr;
std::wstring* nameArr = nullptr;
size_t* countArr = nullptr;
double* priceArr = nullptr;

bool isStorageCreated = false;

size_t maxStorageSize = 300;
size_t currentStorageSize = 0;

void CreateStorage(int mode)
{
    if (mode == 0)
    {
        const size_t staticSize = 10;

        size_t idArrStatic[staticSize]{ 1,2,3,4,5,6,7,8,9,10 };
        std::wstring nameArrStatic[staticSize]
        {
            L"Букет \"101 роза\"", L"Тюльпаны белые (15 шт.)",
            L"Пионы розовые (7 шт.)", L"Хризантема кустовая", L"Эустома в букете",
            L"Орхидея фаленопсис в горшке", L"Гербера микс (10 шт.)",
            L"Подсолнухи (5 шт.)", L"Лилия белая ароматная",
            L"Композиция \"Лепесток\" в шляпной коробке"
        };
        size_t countArrStatic[staticSize]{ 14,30,9,18,23,7,22,40,10,3 };
        double priceArrStatic[staticSize]{ 7990.0, 1450.0, 3200.0, 390.0, 1250.0, 2400.0,
            980.0, 750.0, 520.0, 4900.0 };

        sizeSt = staticSize;
        idArr = new size_t[sizeSt];
        nameArr = new std::wstring[sizeSt];
        countArr = new size_t[sizeSt];
        priceArr = new double[sizeSt];

        FillArray(idArrStatic, idArr, sizeSt);
        FillArray(nameArrStatic, nameArr, sizeSt);
        FillArray(countArrStatic, countArr, sizeSt);
        FillArray(priceArrStatic, priceArr, sizeSt);

        currentStorageSize = 0;
        for (size_t i = 0; i < sizeSt; i++)
        {
            currentStorageSize += countArr[i];
        }

        isStorageCreated = true;
    }
}

void ShowStorage(int mode)
{
    // mode 0 - просто показать склад (с паузой)
    // mode 1 - показать склад без паузы (для операций, например AddProduct)
    system("cls");

    std::wcout << L"\n\n\t\t\tТовары \"Лепесток\"\n\n";

    std::wcout << L"ID\t" << std::left << std::setw(40) << L"Название товара" << L"\t\t"
        << L"Кол-во\t" << L"Цена\n\n";
    for (size_t i = 0; i < sizeSt; i++)
    {
        std::wcout << idArr[i] << L"\t" << std::left << std::setw(40) << nameArr[i]
            << L"\t\t" << countArr[i] << L"\t" << priceArr[i] << L"\n";
    }
    std::wcout << L"\n\n";

    if (mode == 0)
    {
        system("pause");
    }
}

void AddProduct()
{
    std::wstring chooseId, chooseCount, choose;

    while (true)
    {
        ShowStorage(1);

        std::wcout << L"Введите ID товара или \"exit\" для выхода: ";
        Getline(chooseId);

        if (chooseId == L"exit" || chooseId == L"Exit")
        {
            std::wcout << L"Завершение операции пополнения товара\n\n";
            Sleep(1500);
            return;
        }
        else if (IsNumber(chooseId))
        {
            int id = std::stoi(chooseId) - 1;
            if (id < 0 || static_cast<size_t>(id) > sizeSt - 1)
            {
                Err();
            }
            else
            {
                std::wcout << L"Введите кол-во товара для пополнения: ";
                Getline(chooseCount);
                if (IsNumber(chooseCount))
                {
                    size_t count = std::stoull(chooseCount);
                    if (count == 0 || count > maxStorageSize - currentStorageSize)
                    {
                        std::wcout << L"Некорректное кол-во! На складе осталось "
                            << maxStorageSize - currentStorageSize << L" свободных мест\n\n";
                        Sleep(2000);
                    }
                    else
                    {
                        while (true)
                        {
                            system("cls");
                            std::wcout << nameArr[id] << L"\t" << countArr[id] << L" -----> "
                                << countArr[id] + count << L"\n\n";
                            std::wcout << L"Подтвердить?\n1 - Да\n2 - Нет\n\nВвод: ";
                            Getline(choose);

                            if (choose == L"1")
                            {
                                std::wcout << L"Товар успешно пополнен\n\n";
                                countArr[id] += count;
                                currentStorageSize += count;
                                Sleep(1500);
                                break;
                            }
                            else if (choose == L"2")
                            {
                                std::wcout << L"Отмена пополнения " << nameArr[id] << L"\n";
                                Sleep(1500);
                                break;
                            }
                            else
                            {
                                Err();
                            }
                        }
                    }
                }
            }
        }
    }
}
