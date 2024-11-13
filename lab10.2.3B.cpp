#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // ��� �������� ��������

using namespace std;

enum Speciality { ComputerScience, Informatics, MathAndEconomics, PhysicsAndInformatics, LaborEducation };
string specialityStr[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

union ExtraGrade {
    int programmingGrade;
    int numericalMethodsGrade;
    int pedagogyGrade;
};

struct Student {
    string surname;
    int course;
    Speciality speciality;
    int physicsGrade;
    int mathGrade;
    ExtraGrade extraGrade;
    double halfbal;
};

void Create(Student* s, const int N);
void Print(const Student* s, const int N);
double CalculateAverage(const Student& s);
void SortByCourse(Student* s, const int N);
void SortBySurname(Student* s, const int N);
void SortByAverage(Student* s, const int N);
void SortForBinSearch(Student* s, const int N); 
int BinSearch(const Student* s, const int N, const string& surname, const int course, const double halfbal); // ������ �������� ������� BinSearch

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 

    int N;
    cout << "������ ������� �������� N: ";
    cin >> N;

    Student* s = new Student[N];
    int menuItem;

    do {
        cout << "\n\n������� ��:\n";
        cout << " [1] - �������� ����� ��������\n";
        cout << " [2] - ���� ����� �� �����\n";
        cout << " [3] - ������� �����\n"; 
        cout << " [0] - �����\n";
        cout << "������ ��������: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
       
        case 3: { 
            SortForBinSearch(s, N);  
            string surname;
            int course;
            double halfbal;
            cout << "������ ������� ��� ������: ";
            cin >> surname;
            cout << "������ ���� ��� ������: ";
            cin >> course;
            cout << "������ ������� ��� ��� ������: ";
            cin >> halfbal;
            int result = BinSearch(s, N, surname, course, halfbal);
            if (result != -1) 
            {
                cout << "�������� �������� �� ������� " << result + 1  << ".\n";  
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "������� ����! ������ ����� � ����.\n";
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}


void Create(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "������� #" << i + 1 << ":\n";
        cout << " �������: ";
        cin >> s[i].surname;
        cout << " ����: ";
        cin >> s[i].course;
        cout << " ������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        int spec;
        cin >> spec;
        s[i].speciality = static_cast<Speciality>(spec);     
        cout << " ������ � ������: ";
        cin >> s[i].physicsGrade;
        cout << " ������ � ����������: ";
        cin >> s[i].mathGrade;

        // �������� ������ ������ ������� �� ������������
        switch (s[i].speciality) {
        case ComputerScience:
            cout << " ������ � �������������: ";
            cin >> s[i].extraGrade.programmingGrade;
            break;
        case Informatics:
            cout << " ������ � ��������� ������: ";
            cin >> s[i].extraGrade.numericalMethodsGrade;
            break;
        default:
            cout << " ������ � ���������: ";
            cin >> s[i].extraGrade.pedagogyGrade;
            break;
        }

        s[i].halfbal = CalculateAverage(s[i]);
    }
}

void Print(const Student* s, const int N)  
{
    cout << "================================================================================================================================================\n";
    cout << "| �  | �������       | ���� | ������������             |  Գ���� | ���������� | ������������� | ������� ������  | ��������� | ������� ��� |\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << i + 1 << " | "
            << setw(16) << left << s[i].surname << "| "
            << setw(4) << s[i].course << " | "
            << setw(26) << left << specialityStr[s[i].speciality] << "| "
            << setw(7) << s[i].physicsGrade << " | "
            << setw(10) << s[i].mathGrade << " | ";

        if (s[i].speciality == ComputerScience) {
            cout << setw(13) << s[i].extraGrade.programmingGrade << " | "
                << setw(16) << "-" << " | "
                << setw(10) << "-" << " |";
        }
        else if (s[i].speciality == Informatics) {
            cout << setw(13) << "-" << " | "
                << setw(16) << s[i].extraGrade.numericalMethodsGrade << " | "
                << setw(10) << "-" << " |";
        } 
        else 
        {
            cout << setw(13) << "-" << " | "
                << setw(16) << "-" << " | "
                << setw(10) << s[i].extraGrade.pedagogyGrade << " |";
        }
        cout << " " << setw(12) << fixed << setprecision(2) << s[i].halfbal << " |\n";
    }
    cout << "================================================================================================================================================\n";
}

double CalculateAverage(const Student& s) {
    return (s.physicsGrade + s.mathGrade + s.extraGrade.programmingGrade) / 3.0; 
}

void SortByCourse(Student* s, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (s[j].course > s[j + 1].course) {
                swap(s[j], s[j + 1]);
            }
        }
    }
}

void SortBySurname(Student* s, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (s[j].surname > s[j + 1].surname) {
                swap(s[j], s[j + 1]);
            }
        }
    }
}

void SortByAverage(Student* s, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (s[j].halfbal > s[j + 1].halfbal) {
                swap(s[j], s[j + 1]);
            }
        }
    }
}

int BinSearch(const Student* s, const int N, const string& surname, const int course, const double halfbal) 
{
    int L = 0, R = N - 1, m;

    do {
        m = (L + R) / 2;

        if (s[m].surname == surname && s[m].course == course && s[m].halfbal == halfbal) 
            return m;

        if ((s[m].course < course) ||
            (s[m].course == course && s[m].surname < surname) ||
            (s[m].course == course && s[m].surname == surname && s[m].halfbal < halfbal))
        {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } while (L <= R);

    return -1;
}

void SortForBinSearch(Student* s, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if ((s[j].course > s[j + 1].course) ||
                (s[j].course == s[j + 1].course && s[j].surname > s[j + 1].surname) ||
                (s[j].course == s[j + 1].course && s[j].surname == s[j + 1].surname && s[j].halfbal > s[j + 1].halfbal)) {
                swap(s[j], s[j + 1]);
            }
        }
    }
}