// B1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"


int main(int argc, _TCHAR* argv[])
{
		setlocale(LC_ALL, "rus");
		int num = 0;
		bool flag = false;

		cout << "������� �����, ��������� ��������, ���� �� ����� ��� ��������� ������ ��������\n";
		cin >> num;

		flag = isSimple(num);

		if (flag) cout << "YES\n";
		else cout << "NO\n";
		//system("")
		return 0;
		
}

