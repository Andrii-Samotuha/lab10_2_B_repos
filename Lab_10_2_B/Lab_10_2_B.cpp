
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spec { ME, FI, TN, INF, KN };

struct Student
{
    string prizv;
    unsigned kurs;
    Spec spec;
    int fiz;
    int mat;

    union
    {
        int prog;
        int chys;
        int ped;
    };
};

void Create(Student* p, const int N)
{
    int spec;
    int kurs;

    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << "Прізвище: ";
        getline(cin, p[i].prizv);

        cout << "Курс: ";
        while (!(cin >> kurs) || kurs <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть курс повторно: ";
        }
        p[i].kurs = kurs;

        cout << "Спеціальність (0-ME, 1-FI, 2-TN, 3-INF, 4-KN): ";
        while (!(cin >> spec) || spec < 0 || spec > 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть число від 0 до 4: ";
        }
        p[i].spec = (Spec)spec;

        cout << "Фізика: ";
        while (!(cin >> p[i].fiz) || p[i].fiz < 1 || p[i].fiz > 5)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть оцінку від 1 до 5: ";
        }

        cout << "Математика: ";
        while (!(cin >> p[i].mat) || p[i].mat < 1 || p[i].mat > 5)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть оцінку від 1 до 5: ";
        }

        switch (p[i].spec)
        {
        case KN:
            cout << "Програмування: ";
            while (!(cin >> p[i].prog) || p[i].prog < 1 || p[i].prog > 5)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Помилка! Введіть оцінку від 1 до 5: ";
            }
            break;

        case INF:
            cout << "Чисельні методи: ";
            while (!(cin >> p[i].chys) || p[i].chys < 1 || p[i].chys > 5)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Помилка! Введіть оцінку від 1 до 5: ";
            }
            break;

        case ME:
        case FI:
        case TN:
            cout << "Педагогіка: ";
            while (!(cin >> p[i].ped) || p[i].ped < 1 || p[i].ped > 5)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Помилка! Введіть оцінку від 1 до 5: ";
            }
            break;
        }
    }
}

void Print(Student* p, const int N)
{
    string specStr[] = {
        "Математика та економіка",
        "Фізика та інформатика",
        "Трудове навчання",
        "Інформатика",
        "Комп'ютерні науки"
    };

    cout << "Масив студентів" << endl;
    cout << string(130, '=') << endl;

    cout << "| " << setw(3) << left << "№"
        << " | " << setw(15) << "Прізвище"
        << " | " << setw(5) << "Курс"
        << " | " << setw(24) << "Спеціальність"
        << " | " << setw(7) << "Фізика"
        << " | " << setw(10) << "Математика"
        << " | " << setw(14) << "Програмування"
        << " | " << setw(12) << "Чис. методи"
        << " | " << setw(12) << "Педагогіка"
        << " |" << endl;

    cout << string(130, '-') << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1
            << " | " << setw(15) << left << p[i].prizv
            << " | " << setw(5) << p[i].kurs
            << " | " << setw(24) << specStr[p[i].spec]
            << " | " << setw(7) << p[i].fiz
            << " | " << setw(10) << p[i].mat;

        switch (p[i].spec)
        {
        case KN:
            cout << " | " << setw(14) << p[i].prog
                << " | " << setw(12) << ""
                << " | " << setw(12) << "";
            break;

        case INF:
            cout << " | " << setw(14) << ""
                << " | " << setw(12) << p[i].chys
                << " | " << setw(12) << "";
            break;

        case ME:
        case FI:
        case TN:
            cout << " | " << setw(14) << ""
                << " | " << setw(12) << ""
                << " | " << setw(12) << p[i].ped;
            break;
        }

        cout << " |" << endl;
    }

    cout << string(130, '=') << endl;
}

void Sort(Student* p, const int N)
{
    int specOrder[] = { 2, 4, 3, 0, 1 };

    Student tmp;

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (specOrder[p[j].spec] > specOrder[p[j + 1].spec] ||
                (p[j].spec == p[j + 1].spec &&
                    p[j].mat > p[j + 1].mat) ||
                (p[j].spec == p[j + 1].spec &&
                    p[j].mat == p[j + 1].mat &&
                    p[j].prizv > p[j + 1].prizv))
            {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }
}

int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    int specOrder[] = { 2, 4, 3, 0, 1 };

    int i, j, value;

    for (i = 1; i < N; i++)
    {
        value = I[i];

        for (j = i - 1;
            j >= 0 &&
            (specOrder[p[I[j]].spec] > specOrder[p[value].spec] ||
                (p[I[j]].spec == p[value].spec &&
                    p[I[j]].mat > p[value].mat) ||
                (p[I[j]].spec == p[value].spec &&
                    p[I[j]].mat == p[value].mat &&
                    p[I[j]].prizv > p[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }

        I[j + 1] = value;
    }

    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
    string specStr[] = {
        "Математика та економіка",
        "Фізика та інформатика",
        "Трудове навчання",
        "Інформатика",
        "Комп'ютерні науки"
    };

    cout << "Індексно впорядкований масив студентів" << endl;
    cout << string(130, '=') << endl;

    cout << "| " << setw(3) << left << "№"
        << " | " << setw(15) << "Прізвище"
        << " | " << setw(5) << "Курс"
        << " | " << setw(24) << "Спеціальність"
        << " | " << setw(7) << "Фізика"
        << " | " << setw(10) << "Математика"
        << " | " << setw(14) << "Програмування"
        << " | " << setw(12) << "Чис. методи"
        << " | " << setw(12) << "Педагогіка"
        << " |" << endl;

    cout << string(130, '-') << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1
            << " | " << setw(15) << left << p[I[i]].prizv
            << " | " << setw(5) << p[I[i]].kurs
            << " | " << setw(24) << specStr[p[I[i]].spec]
            << " | " << setw(7) << p[I[i]].fiz
            << " | " << setw(10) << p[I[i]].mat;

        switch (p[I[i]].spec)
        {
        case KN:
            cout << " | " << setw(14) << p[I[i]].prog
                << " | " << setw(12) << ""
                << " | " << setw(12) << "";
            break;

        case INF:
            cout << " | " << setw(14) << ""
                << " | " << setw(12) << p[I[i]].chys
                << " | " << setw(12) << "";
            break;

        case ME:
        case FI:
        case TN:
            cout << " | " << setw(14) << ""
                << " | " << setw(12) << ""
                << " | " << setw(12) << p[I[i]].ped;
            break;
        }

        cout << " |" << endl;
    }

    cout << string(130, '=') << endl;
}

int BinSearch(Student* p, const int N, const string prizv,
    const Spec spec, const int mat)
{
    int L = 0, R = N - 1, m;
    int specOrder[] = { 2, 4, 3, 0, 1 };

    do
    {
        m = (L + R) / 2;

        if (p[m].prizv == prizv &&
            p[m].spec == spec &&
            p[m].mat == mat)
            return m;

        if (specOrder[p[m].spec] < specOrder[spec] ||
            (p[m].spec == spec && p[m].mat < mat) ||
            (p[m].spec == spec &&
                p[m].mat == mat &&
                p[m].prizv < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }

    } while (L <= R);

    return -1;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N: ";

    while (!(cin >> N) || N <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка! Введіть додатне число: ";
    }

    Student* p = new Student[N];

    int ispec, mat, found;
    Spec spec;
    string prizv;
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: ";
        while (!(cin >> menuItem) || menuItem < 0 || menuItem > 5)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть число від 0 до 5: ";
        }
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            break;
        case 4:
        {
            int* I = IndexSort(p, N);
            PrintIndexSorted(p, I, N);
            delete[] I;
            break;
        }
        case 5:
            cout << "Введіть ключі пошуку:" << endl;
            cout << "     спеціальність (0 - ME, 1 - FI, 2 - TN, 3 - INF, 4 - KN): ";
            cin >> ispec;
            spec = (Spec)ispec;

            cout << "     оцінка з математики: ";
            cin >> mat;

            cin.get();
            cin.sync();

            cout << "     прізвище: ";
            getline(cin, prizv);
            cout << endl;

            if ((found = BinSearch(p, N, prizv, spec, mat)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення!" << endl;
        }
    } while (menuItem != 0);

    delete[] p;

    return 0;
}
