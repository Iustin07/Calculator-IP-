#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const double INFINIT = 500000.0;
const double MINUS_INFINIT = -500000.0;
const double ZERO = 0.0000001;
const double  PI = 3.1415926;

bool eroare = 0;
char functii[20][15] = { "sin", "cos", "tan", "abs", "sqrt", "ln" };




struct nodexpresie
{
	bool tip;
	double variabila;
	char elem[11];
	nodexpresie* urm;
};

nodexpresie* pr, * ul;

struct nodoperator
{
	char s[15];
	nodoperator* pred;

};

nodoperator* operatori = NULL;

struct nodoperand
{
	double valoare;
	nodoperand* pred;
};

nodoperand* operanzi = NULL;

struct nodvariabila
{
	double valoare;
	char nume[10];
	nodvariabila* pred;
};

nodvariabila* variabile = NULL;

void intro(bool stare);

void pushVariabila(nodvariabila*& variabile, char nume[], double valoare)
{
	nodvariabila* q = new nodvariabila;

	strcpy(q->nume, nume);
	q->valoare = valoare;

	if (variabile != NULL)
	{
		q->pred = variabile;
		variabile = q;
	}

	else

	{
		q->pred = NULL;
		variabile = q;
	}
}

bool existaVariabila(nodvariabila*& variabile, nodexpresie* q, char nume[])
{
	nodvariabila* p = new nodvariabila;

	p = variabile;

	while (p != NULL)
	{
		if (strcmp(p->nume, nume) == 0)
		{
			q->variabila = p->valoare;

			return 1;

		}

		p = p->pred;
	}

	return 0;

}



int prioritate(char s[])
{
	if ((s[0] == '(') || (s[0] == ')'))

		return 0;

	if ((s[0] == '+') || (s[0] == '-'))

		return 1;

	if ((s[0] == '*') || (s[0] == '/') || (s[0]=='%'))

		return 2;

	if (s[0] == '^')

		return 3;

	if ((s[0] == '<') || (s[0] == '>') || (s[0] == '=') || (s[0] == '#'))

		return 4;

	return 5;


}

bool esteFunctie(char s[])
{
	for (int i = 0; i <= 19; i++)
		if (strcmp(functii[i], s) == 0)

			return 1;

	return 0;

}

double operatii(double a, double b, char s[])
{
	if ((a >= 0) && (a <= ZERO))
		a = 0;

	if ((b >= 0) && (b <= ZERO))
		b = 0;




	if (s[0] == '+')
	{
		if (((a >= INFINIT) && (b <= MINUS_INFINIT)) || ((a <= MINUS_INFINIT) && (b >= INFINIT)))
		{
			cout << "NEDETERMINARE"<<endl;

			intro(1);

		}

		if ((a >= INFINIT) || (b >= INFINIT))

			return INFINIT;

		if ((a <= MINUS_INFINIT) || (b <= MINUS_INFINIT))

			return MINUS_INFINIT;

		return a + b;

	}

	if (s[0] == '-')
	{
		if (((a >= INFINIT) && (b >= INFINIT)) || ((b <= MINUS_INFINIT) && (a <= MINUS_INFINIT)))
		{
			cout << "NEDETERMINARE" << endl;

			intro(1);
		}

		if (b >= INFINIT)

			return INFINIT;

		if (a >= INFINIT)

			return MINUS_INFINIT;

		return b - a;

	}

	if (s[0] == '*')
	{
		if (((a == 0) || (b == 0)) && ((a >= INFINIT) || (b >= INFINIT) || (b <= MINUS_INFINIT) || (a <= MINUS_INFINIT)))
		{
			cout << "NEDETERMINARE" << endl;

			intro(1);
		}
		if ((a >= INFINIT) || (b >= INFINIT))
		{
			if ((a >= 0) && (b >= 0))

				return INFINIT;

			return MINUS_INFINIT;

		}

		return a * b;

	}

	if (s[0] == '/')
	{
		if ((a == 0) && (b == 0))
		{
			cout << "NEDETERMINARE" << endl;

			intro(1);
		}

		if (((a >= INFINIT) || (a <= MINUS_INFINIT)) && ((b >= INFINIT) || (b <= MINUS_INFINIT)))
		{
			cout << "NEDETERMINARE" << endl;

			intro(1);
		}

		if (a == 0)

			return INFINIT;

		if ((a >= INFINIT) || (a <= MINUS_INFINIT))

			return 0;

		if (b >= INFINIT)
		{
			if (a <= 0)

				return MINUS_INFINIT;

			return INFINIT;

		}

		return b / a;

	}

	if (s[0] == '^')
	{
		if ((a == 0) && (b == 0))
		{
			cout << "NEDETERMINARE" << endl;

			intro(1);
		}

		if ((b == 1) && ((a >= INFINIT) || (a <= MINUS_INFINIT)))
		{
			cout << "NEDETERMINARE" << endl;

			intro(1);
		}

		if (a >= INFINIT)

			return INFINIT;

		if (a <= MINUS_INFINIT)

			return 0;

		return pow(b, a);

	}


	if ((s[0] == '<') && (s[1] == '='))

		return b <= a;

	if ((s[0] == '>') && (s[1] == '='))

		return b >= a;

	if (s[0] == '<')

		return b < a;

	if (s[0] == '>')

		return b > a;

	if (s[0] == '=')

		return a == b;

	if (s[0] == '#')

		return a != b;

	if (s[0] == '&' && s[1] == '&')
		return a && b;

	if (s[0] == '&')
		return (int)a & (int)b;

	if (s[0] == '|' && s[1] == '|')
		return a || b;

	if (s[0] == '|')
		return (int)a | int(b);

	if (s[0] == '%')

		return (int) b % (int) a;


}



double aplicaFunctie(double a, char elem[])
{
	if (strcmp(elem, "sin") == 0)
	{
		if (a == INFINIT)
			return INFINIT;

		else if (a == MINUS_INFINIT)
			return MINUS_INFINIT;
		else
			return sin(a);
	}

	if (strcmp(elem, "cos") == 0)

	{
		if (a == INFINIT)
			return INFINIT;

		else if (a == MINUS_INFINIT)
			return INFINIT;
		else
			return cos(a);
	}

	if (strcmp(elem, "tan") == 0)
		return tan(a);

	if (strcmp(elem, "abs") == 0)

		return fabs(a);

	if (strcmp(elem, "sqrt") == 0)
	{
		if (a < 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Eroare: radical negativ";
			SetConsoleTextAttribute(hConsole, 15);

			intro(1);
		}

		return sqrt(a);

	}

	if (strcmp(elem, "ln") == 0)
	{
		if (a <= 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Eroare: logaritm negativ";
			SetConsoleTextAttribute(hConsole, 15);

			intro(1);
		}

		if (a == 0)
			return MINUS_INFINIT;
		else if (a >= INFINIT)
			return INFINIT;
		else
			return log(a);
	}
}


void afisare()
{
	while (pr != NULL)
	{
		if (pr->tip == 1)
			cout << pr->elem << ' ';
		else

			cout << pr->variabila << ' ';

		pr = pr->urm;
	}

	cout << eroare;
}



void pushOperator(nodoperator*& S, char elem[])
{
	nodoperator* q = new nodoperator;

	strcpy(q->s, elem);

	if (S != NULL)
	{
		q->pred = S;
		S = q;
	}

	else

	{
		S = q;
		S->pred = NULL;
	}



}

void popOperator(nodoperator*& S)
{
	if (S != NULL)
	{
		nodoperator* q = new nodoperator;
		q = S;
		S = S->pred;

		delete(q);

	}

}

void topOperator(nodoperator*& S, char s[])
{
	strcpy(s, S->s);
}

void pushOperand(nodoperand*& S, double x)
{
	nodoperand* q = new nodoperand;

	q->valoare = x;

	if (S != NULL)
	{
		q->pred = S;
		S = q;
	}

	else

	{
		S = q;
		S->pred = NULL;

	}

}

void popOperand(nodoperand*& S)
{
	nodoperand* q = new nodoperand;

	q = S;
	S = S->pred;

	delete(q);

}

double topOperand(nodoperand*& S)
{

	return S->valoare;

}

double calcul(nodoperand*& operanzi, nodoperator*& operatori, nodexpresie*& pr)
{
	int prioritateant = -1;
	double val1 = 0, val2 = 0;

	while ((pr != NULL) || (operatori != NULL))
	{
		if ((operatori != NULL) && (pr->elem[0] == ')') && (operatori->s[0] == '(') && (operatori->s[1] == '-'))
		{
			popOperator(operatori);

			prioritateant = prioritate(operatori->s);

			operanzi->valoare = (-1) * operanzi->valoare;
		}

		else

		{

			if (pr->tip == 0)
				pushOperand(operanzi, pr->variabila);


			else

			{
				if ((prioritate(pr->elem) > prioritateant) || (pr->elem[0] == '('))
				{
					pushOperator(operatori, pr->elem);

					prioritateant = prioritate(operatori->s);

				}


				else

				{
					while ((prioritate(pr->elem) <= prioritateant) && (operatori->s[0] != '('))
					{
						if (esteFunctie(operatori->s))
						{
							val1 = topOperand(operanzi);
							popOperand(operanzi);

							pushOperand(operanzi, aplicaFunctie(val1, operatori->s));
						}

						else

						{

							val1 = topOperand(operanzi);
							popOperand(operanzi);


							val2 = topOperand(operanzi);
							popOperand(operanzi);

							pushOperand(operanzi, operatii(val1, val2, operatori->s));

						}

						popOperator(operatori);

						if (operatori != NULL)
							prioritateant = prioritate(operatori->s);

					}


					if (pr->elem[0] != ')')
						pushOperator(operatori, pr->elem);

					if (operatori != NULL)
						if ((operatori->s[0] == '(') && (pr->elem[0] == ')'))
							popOperator(operatori);




					if (operatori != NULL)
						prioritateant = prioritate(operatori->s);
				}

			}

		}

		pr = pr->urm;
	}


	return operanzi->valoare;

}

int esteSimbol(char s)
{
	if (s == '+' || s == '-' || s == '*' || s == '/' || s == '%' || s == '#')
		return 1;
	if (s == '|' || s == '&')
		return 2;
	if (s == ')')
		return 3;
	if (s == '(')
		return 4;
	if (s == '<' || s == '>')
		return 5;
	if (s == '^')
		return 6;
	if (s == '=')
		return 7;
	return 0;
}

bool esteCifra(char c)
{
	if ((c >= '0') && (c <= '9'))

		return 1;

	return 0;
}
bool esteCaracter(char c)
{
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
		return 1;
	return 0;
}
double cereVariabila(char s[])
{
	double variabila = 0;
	cout << "Dati valoarea variabilei ";
	cout << s << "=";
	cin >> variabila;
	return variabila;
}
double construiesteNumar(char s[])
{
	int l, k = 0;
	double nr = 0, p = 1;
	l = strlen(s);
	for (int i = 0; i < l; i++)
		if (s[i] == '.')
		{
			k = i;
			break;
		}
	if (k == 0)
		k = l;
	for (int i = 0; i < k; i++)
		nr = nr * 10 + (s[i] - '0');
	for (int i = k + 1; i < l; i++)
	{
		p = p / 10;
		nr = nr + p * (s[i] - '0');
	}
	return nr;

}
void prelucrareSir(nodexpresie*& pr, nodexpresie*& ul, char s[])///despart sirul in cuvinte
{
	int l, k = 0;
	char temp[256];
	bool amcaracter = 0;
	bool amcifra = 0;
	l = strlen(s);
	nodexpresie* p = new nodexpresie;
	p->elem[0] = '(';
	p->elem[1] = NULL;
	p->tip = 1;
	pr = p;
	ul = p;
	for (int i = 0; i < l; i++)
	{
		k = 0;
		amcaracter = 0;
		amcifra = 0;
		nodexpresie* q = new nodexpresie;
		if (s[i] == '@')
		{
			q->variabila = INFINIT;
			q->tip = 0;
		}
		else
		{
			if ((s[i] == 'P') && (s[i + 1] == 'I'))
			{
				q->variabila = PI;
				q->tip = 0;
				i = i + 1;
			}
			else
			{


				if (!esteSimbol(s[i]))
				{
					while (esteCaracter(s[i]) || esteCifra(s[i]) || (s[i] == '.'))
					{
						if (esteCaracter(s[i]))
							amcaracter = 1;
						if (esteCifra(s[i]))
							amcifra = 1;
						temp[k] = s[i];
						k = k + 1;
						i = i + 1;
					}
					temp[k] = NULL;
					strcpy(q->elem, temp);
					if (esteFunctie(temp))
						q->tip = 1;
					else
					{
						q->tip = 0;

						if ((amcaracter == 1) && (!existaVariabila(variabile, q, temp)))
						{
							q->variabila = cereVariabila(temp);
							pushVariabila(variabile, temp, q->variabila);
						}

					}
					if ((esteCifra(temp[0])) && (amcaracter == 1))
						eroare = 1;
					if ((amcifra == 1) && (amcaracter == 0))
						q->variabila = construiesteNumar(temp);

				}
				else
				{
					while (esteSimbol(s[i]))
					{
						temp[k] = s[i];
						k = k + 1;
						i = i + 1;
						if ((s[i] == '(') || (s[i - 1] == ')'))
							break;
					}
					temp[k] = NULL;
					strcpy(q->elem, temp);
					q->tip = 1;
					if ((k != 1) && (((temp[0] != '>') || (temp[0] != '<')) && (temp[1] != '=')))
						eroare = 1;
				}
				i = i - 1;
			}

		}

			ul->urm = q;
			ul = q;
			ul->urm = NULL;


	}

	nodexpresie* q = new nodexpresie;
	q->elem[0] = ')';
	q->elem[1] = NULL;
	q->tip = 1;
	ul->urm = q;
	ul = q;
	ul->urm = NULL;


}
void afisareErori(int poz_eroare[], int tip_eroare[], int n)///afisez un mesaj specific pentru fiecare tip de eroare
{
	int i;
	for (i = 1; i <= n; i++)
	{
		if (tip_eroare[i] == 1)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Eroare";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "-operatori consecutivi la pozitia: " << poz_eroare[i] << ".Expresia nu are sens." << endl;
		}
		if (tip_eroare[i] == 2)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Eroare";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "-variabila scrisa gresit la pozitia: " << poz_eroare[i] << endl;
		}
		if (tip_eroare[i] == 3)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Eroare";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "-Expresia se termina brusc la pozitia: " << poz_eroare[i] << endl;
		}
		if (tip_eroare[i] == 4)
		{

			SetConsoleTextAttribute(hConsole, 12);
			cout << "Eroare. ";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Te rugam sa scrii numarul/variabila negativ de la inceputul expresiei intre paranteze." << endl;

		}
		    if(tip_eroare[i]==5)
        {
            SetConsoleTextAttribute(hConsole,12);
            cout<<"Eroare. ";
            SetConsoleTextAttribute(hConsole, 15);
            cout<<"Operator invalid la inceputul expresiei. Pozitia:"<<poz_eroare[i]<<endl;
        }
	}
}
int verificareParanteze(char s[]) ///erori in functie de inchiderea parantezelor
{
	int i = 0, nrparanteze = 0, l;
	l = strlen(s);
	while (i < l)
	{
		if (nrparanteze < 0) /// paranteza inchisa in fata uneia deschise-eroare
		{
			return 0;
		}
		if (esteSimbol(s[i]) == 4)
		{
			if (esteSimbol(s[i + 1]) == 3) ///nu am element intre paranteze-eroare
			{
				return 0;
			}
			nrparanteze++;
		}
		else if (esteSimbol(s[i]) == 3)
		{
			if (esteSimbol(s[i + 1]) == 4) /// nu am operator intre paranteze-eroare
			{
				return 0;
			}
			nrparanteze--;
		}
		else if ((esteSimbol(s[i]) == 1 || esteSimbol(s[i]) == 2 || esteSimbol(s[i]) == 5 || esteSimbol(s[i]) == 6 || esteSimbol(s[i]) == 7) && s[i + 1] == ')') ///verific daca dupa un simbol este )-eroare
			nrparanteze = 0;
		i++;
	}
	if (nrparanteze == 0)
	{
		return 1;
	}
	else
		return 0;

}
void eroriSir(char s[], int& corect)///determin erorile sirului
{
	int poz_eroare[50], tip_eroare[50];
	int l = strlen(s);
	bool gas = 0, amcaracter = 0;
	char temp[51];
	int c = 0, facut = 0, k = 0;
	if((s[0]=='-'||s[0]=='+')&&(esteCaracter(s[1])||esteCifra(s[1])||(s[1]=='(')))
    {
        poz_eroare[++c]=0;
        tip_eroare[c]=4;
        gas=1;
    }
    else
		if (s[0] == '*' || s[0] == '/' || s[0] == '=' || s[0] == '^' || s[0] == '%' || s[0] == '|' || s[0] == '&' || s[0] == '<' || s[0] == '>' || s[0] == '#')
		{
			poz_eroare[++c] = 0;
			tip_eroare[c] = 5;
			gas = 1;
		}
		else
if(s[0]=='('&&(s[1]=='<'||s[1]=='>'||s[1]=='='||s[1]=='&'||s[1]=='^'||s[1]=='#'||s[1]=='|'||s[1]=='*'||s[1]=='/')&&s[2]=='(')
{
    poz_eroare[++c] = 1;
			tip_eroare[c] = 5;
			gas = 1;
}
else
if(s[0]=='('&&((s[1]=='<'&&s[2]=='=')||(s[1]=='='||s[2]=='>')||(s[1]=='|'||s[2]=='|')||(s[1]=='&'&&s[2]=='&'))&&s[3]=='(')
                {poz_eroare[++c] =2;
			tip_eroare[c] = 5;
			gas = 1;
}
	for (int i = 0; i < l; i++)
	{

		if (esteSimbol(s[i]) == 1 && (esteSimbol(s[i + 1]) == 1 || esteSimbol(s[i + 1]) == 2 || esteSimbol(s[i + 1]) == 5 || esteSimbol(s[i + 1]) == 6 || esteSimbol(s[i + 1]) == 7))///in cadrul expresie pot fi unele combinatii de operatori imposibile cum ar fi:+*, /= etc
		{
			poz_eroare[++c] = i + 1;
			tip_eroare[c] = 1;
			gas = 1;
		}

		if (esteSimbol(s[i]) == 2 && (esteSimbol(s[i + 1]) == 1 || esteSimbol(s[i + 1]) == 5 || esteSimbol(s[i + 1]) == 6 || esteSimbol(s[i + 1]) == 7))
		{
			poz_eroare[++c] = i + 1;
			tip_eroare[c] = 1;
			gas = 1;
		}
		if (esteSimbol(s[i]) == 7 && esteSimbol(s[i + 1]) == 7)
		{

			poz_eroare[++c] = i + 1;
			tip_eroare[c] = 1;
			gas = 1;
		}
		if (esteSimbol(s[i]) == 5 && esteSimbol(s[i + 1]) == 5)
		{
			poz_eroare[++c] = i + 1;
			tip_eroare[c] = 1;
			gas = 1;

		}
		if ((esteSimbol(s[i]) == 1 || esteSimbol(s[i]) == 2 || esteSimbol(s[i]) == 5 || esteSimbol(s[i]) == 6 || esteSimbol(s[i]) == 7) && s[i + 1] == '\0')///verific daca dupa un simbol (in afara de paranteze) se termina sirul
		{
			poz_eroare[++c] = i + 1;
			tip_eroare[c] = 3;
			gas = 1;
		}
		if (esteCaracter(s[i]) || esteCifra(s[i]))
		{
			k = 0, amcaracter = 0;
			while (esteCaracter(s[i]) || esteCifra(s[i]))///formez cuvintele  sirului,despartite de operatori
			{
				if (esteCaracter(s[i]))
					amcaracter = 1;

				temp[k] = s[i];
				k++;
				i++;
			}
			temp[k] = '\0';
			facut = 1;
			if (esteCifra(temp[0]) && amcaracter == 1)///verific eroarea in cazul in care este o variabila de tipul 2x1
			{
				poz_eroare[++c] = i - k;
				tip_eroare[c] = 2;
				gas = 1;
			}
			if (esteFunctie(temp))
			{
				if (s[i] == NULL)//verific daca dupa o functie sirul se termina brusc
				{
					poz_eroare[++c] = i - 1;
					tip_eroare[c] = 3;
					gas = 1;
					facut = 2;
				}
			}
		}

		if (facut != 2)
		{
			if (facut == 1)
			{
				i--;
				facut = 0;
			}
		}
	}
	if (gas == 1)
	{
		afisareErori(poz_eroare, tip_eroare, c);
		corect = 0;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Expresia este corecta sintactic";
		SetConsoleTextAttribute(hConsole, 15);
		corect = 1;
		cout << endl;
	}
}

bool existaErori(char s[])
{
	int corect = 0;

	if (verificareParanteze(s) == 0)///verific eroarile de parantetizare a expresiei
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Expresia este parantetizata gresit!";
		SetConsoleTextAttribute(hConsole, 15);

		return 1;

	}
	else
	{
		eroriSir(s, corect);
		if(corect==0)

			return 1;

	}

	return 0;

}

void interpretare()
{
	double x;

	x = calcul(operanzi, operatori, pr);

	if (x <= ZERO)
		x = 0;

	if (x>=INFINIT)///aici am modificat
		cout << (char)(236);

	else

	{
		if (x<=MINUS_INFINIT)//a/aici am modificat
		{
			cout << '-';
			cout << (char)(236);
		}

		else

		{
			cout << fixed << setprecision(7) << x;
		}


	}
}

void citire()
{
	char s[256];
	cin >> s;

	if (!existaErori(s))
	{
		prelucrareSir(pr, ul, s);

		interpretare();
	}

}


void intro(bool stare)
{
	char raspuns[3];

	operanzi = NULL;
	operatori = NULL;
	pr = NULL;
	ul = NULL;
	variabile = NULL;

	if (stare == 0)
	{
		SetConsoleTextAttribute(hConsole, 9);
		cout << "Introdu expresia:" << endl;
		SetConsoleTextAttribute(hConsole, 15);

		citire();

	}



		cout << endl;
		SetConsoleTextAttribute(hConsole, 11);
		cout << "Doriti sa introduceti o noua expresie? DA/NU" << ' ';
		SetConsoleTextAttribute(hConsole, 15);
		SetConsoleTextAttribute(hConsole, 13);
		cin >> raspuns;
		SetConsoleTextAttribute(hConsole, 15);

		cout << endl;

		while (strcmp(raspuns, "DA") == 0)
		{
			operanzi = NULL;
			operatori = NULL;
			pr = NULL;
			ul = NULL;
			variabile = NULL;

			SetConsoleTextAttribute(hConsole, 9);
			cout << "Introdu expresia:" << endl;
			SetConsoleTextAttribute(hConsole, 15);

			citire();

			cout << endl;
			SetConsoleTextAttribute(hConsole, 11);
			cout << "Doriti sa introduceti o noua expresie? DA/NU" << ' ';
			SetConsoleTextAttribute(hConsole, 15);
			SetConsoleTextAttribute(hConsole, 13);
			cin >> raspuns;
			SetConsoleTextAttribute(hConsole, 15);
			cout << endl;

		}


}

int main()
{

	cout << "\t\t\t\t EVALUATOR EXPRESIE MATEMATICA";
	cout << "\n\n";
	cout << "/*Pentru o functionaliate cat mai buna a programului te rugam sa introduci pantezele corect.*/" << '\n';
	cout << "/*Pentru numere/variabile negative, te rugam sa introduci paranteze in jurul lor altfel se vor afisa mesaje de eroare.*/" << '\n';
	cout << "/*Pentru a introduce infinitul se foloseste simbolul @.*/" << '\n';
	cout << "/*Pentru a introduce simbolul diferit in expreasie foloseste: #*/" << '\n';
	cout << "/*Atentie operatiile realizate pe biti se vor realiza doar pe numere intregi.Daca numarul nu este intreg se va converti" << '\n' << "automat, la intreg.*/";
	cout << "/*Pentru a introduce pi scrieti 'PI'*/" << '\n',
		cout << endl;


	intro(0);



	return 0;

}

