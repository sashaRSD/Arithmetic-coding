#include <iostream>
#include <locale.h>
#include <string>
#include <conio.h>

double ver[6];
double ver2[6];

double loww[10];
double highh[10];

char slovo[10];
double deslovo[10];

double code = 0.0;
double low = 0.0;
double high = 1.0;
char alf[] = { 'q','w','e','r','t','y' };

void encode_symbol(int znak, int symbol)
{
	double range = high - low;
	high = low + range * ver[symbol];
	low = low + range * ver[symbol - 1];

	highh[znak] = high;
	loww[znak] = low;

	printf("%c: ", alf[symbol]);
	printf("%f - %f \n", low, high);
}

void decode_symbol(int symbol, int kolvo, int sim)
{
	if (symbol == 0)
	{

		code = loww[kolvo - 1];
		deslovo[symbol] = ver[sim - 1];
		printf("%f : %f - %f\n", ver[sim - 1], ver[sim - 1], ver[sim]);
		code = ((code - ver[sim - 1]) / (ver[sim] - ver[sim - 1]));
	}
	else
	{
		deslovo[symbol] = code;
		printf("%f : %f - %f\n", code, ver[sim - 1], ver[sim]);
		code = ((code - ver[sim - 1]) / (ver[sim] - ver[sim - 1]) + 0.000001);

	}

}


char InputBuf(char* buf)
{
	int z = 0;
	char ch;
	do
	{
		ch = _getch();
		if ((strchr(alf, ch)) && (ch != NULL))
		{
			putchar(ch);
			buf[z] = ch;
			z++;
		}


	} while (z < 10);
	return *buf;
}

void viviodvero(double* ver, double* ver2, char* alf)
{
	for (int i = 0; i < 6; i++)
	{
		if (ver[i] == 0)
		{

			printf("\n Буква %c: Интервал отсутсвует", alf[i]);
		}
		else
		{
			if ((i > 0))
			{

				printf("\n Буква %c:  Вероятность %f  - Интервал от %f до %f", alf[i], ver2[i], ver[i - 1], ver[i]);
			}
			else
				printf("\n Буква %c:  Вероятность %f  - Интервал от 0 до %f", alf[i], ver2[i], ver[i]);
		}

	}
}

void vero(double* ver, char* slovo)
{
	for (int i = 0; i < 6; i++)
	{
		double h = 0;
		for (int j = 0; j < 10; j++)
		{
			if (alf[i] == slovo[j]) h++;

			ver2[i] = h / 10;

			if ((i > 0) && (h != 0))
				ver[i] = ver[i - 1] + (h / 10);
			else
				ver[i] = h / 10;

		}
	}
}

void decod(char* alf, double* deslovo)
{
	printf(" \n Нажмите любую клавишу, чтобы декодировать...\n\n");
	_getch();

	std::string z1 = alf;
	std::string s1 = slovo;
	for (int i = 0; i < s1.length(); i++)
	{
		for (int j = 0; j < z1.length(); j++)
			if (s1[i] == alf[j])
			{
				decode_symbol(i, s1.length(), j);
			}
	}

	printf(" \n Введенный текст: ");
	for (int i = 0; i < s1.length(); i++)
	{
		for (int j = 0; j < z1.length(); j++)
		{
			if ((ver[j - 1] <= deslovo[i]) && (deslovo[i] < ver[j]))
				printf("%c", alf[j]);
		}

	}
}

int main()
{
	setlocale(LC_ALL, "RUS");

	printf("Введите 10 символов (q,w,e,r,t,y): \n");
	InputBuf(slovo);
	printf(" \n\n Текст введен успешно. Нажмите любую клавишу, чтобы продолжить...\n"); _getch(); 

	vero(ver, slovo);
	printf("\n Диапозон от %f до %f ", low, high);
	viviodvero(ver, ver2, alf);
	printf(" \n\n Нажмите любую клавишу, чтобы закодировать...\n\n"); _getch(); 

	std::string s = slovo;
	std::string z = alf;
	for (int i = 0; i < s.length(); i++)
	{
		for (int j = 0; j < z.length(); j++)
			if (s[i] == alf[j]) encode_symbol(i, j);
	}
	decod(alf, deslovo);

	printf("\n\n");

	system("pause");
}