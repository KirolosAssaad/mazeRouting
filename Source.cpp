#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include <cstdlib>
#include <cstdint>
#include<iomanip>
#include<bitset>
#include<vector>
#include<array>
#include<cmath>
using namespace std;
#define ROW 800
#define COL 800
struct pin
{
	int layer;
	int X;
	int Y;
};

struct cell
{
	int CT; // total cost = C1 + C2
	int C1; // heuristic cost (cost from current cell to destination)
	int C2; // cost from source to other cell on grid
};

vector<pair<string, vector<pin>>> read_nets(ifstream& file_name, vector<pair<string, vector<pin>>>PINS)
{
	string net;
	string temp;
	int val;
	string pin_name;
	vector<pin>points;
	pair<string, vector<pin>>N;
	int count = 0;
	if (!file_name.is_open())
		cout << "Can't open file" << endl;
	else
	{
		cout << "successfully opened file" << endl;
		while (getline(file_name, net))
		{
			//data.clear();
			vector<string>data;
			data.resize(1);
			count++;
			//PINS.resize(count);
			int idx = 0;
			
			for (int i = 0; i < net.length(); i++)
			{
				if ((net[i] != ',') && (net[i] != ' ') && (net[i] != '(') && (net[i] != ')'))
					temp.push_back(net[i]);
				if (net[i] == ' ')
				{
					pin_name = temp;
					temp = "";
					break;
				}
			}
			string L = net.substr(net.find(pin_name) + pin_name.length() + 1, net.length() - 1);
			for (int i = 0; i < L.length(); i++)
			{
				if ((L[i] != ',') && (L[i] != ' ') && (L[i] != '(') && (L[i] != ')'))
					temp.push_back(L[i]);
				if ((L[i] == ',') || (L[i] == ')'))
				{
					data[idx] = temp;
					temp = "";
					idx++;
					data.resize(idx + 1);
				}
			}
			int C = 0;
			for (int i = 0; i < (data.size() - 1)/3; i++)
			{
				points.resize(i + 1);
				points[i].layer = stoi(data[C]);
				points[i].X = stoi(data[C+1]);
				points[i].Y = stoi(data[C+2]);
				C = C + 3;
			}
			N.first = pin_name;
			N.second = points;
			PINS.push_back(N);
			//PINS[pin_name] = points;
			
		}
	}
	return PINS;
}

bool within_grid(int X, int Y)
{
	if ((X < COL) && (X >= 0) && (Y >= 0) && (Y < ROW))
		return true;
	else
		return false;
}

bool is_available(int X, int Y, int Grid[][COL])
{
	if (Grid[X][Y]==0)
		return true;
	else
		return false;
}

bool target_reached(int x, int y, pin dest)
{
	if ((x == dest.X) && (y == dest.Y))
		return true;
	else
		return false;
}

/*double cal_euclidean_dist(int x, int y, pin dest)
{
	double E = sqrt((pow((x - dest.X), 2)) + (pow((y - dest.Y), 2)));
	return E;
}*/

void save_path()
{

}

void Lee_algorithm(int Grid[][COL], pin Src, pin Dest)
{
	if (!within_grid(Src.X, Src.Y))
		cout << "Source is outside the grid";
	if (!within_grid(Dest.X, Dest.Y))
		cout << "Destination is outside the grid";
	if (!is_available(Src.X, Src.Y, Grid))
		cout << "Source Pin is already connected";
	if (!is_available(Dest.X, Dest.Y, Grid))
		cout << "Destination Pin is already connected";
	if ((Src.layer == Dest.layer) && (Src.X == Dest.X) && (Src.Y == Dest.Y))
		cout << "Already reached Destination";



}

int main()
{
	ifstream file_name("Testcase_3.txt");
	int Grid[80][80] = { 0 };
	vector<pair<string, vector<pin>>>PINS;
	PINS = read_nets(file_name, PINS);

	return 0;
}