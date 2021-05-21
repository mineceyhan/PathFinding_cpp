#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <algorithm>

using namespace std;




void setup_durations(string s, vector<int>  temp, vector<vector<int>>& gecisler, vector<int>& kurulum)
{
	string del = ";";
	int i = 0;
	int start = 0;
	int end = s.find(del);
	while (end != -1) {
		string tok1 = s.substr(start, end - start);
		temp.push_back(stoi(tok1));
		start = end + del.size();
		end = s.find(del, start);
		i++;
	}
	gecisler.push_back(temp);
	temp.clear();
	string tok = s.substr(start, end - start);
	kurulum.push_back(stoi(tok));
}

void orders(string s, vector<int> temp, vector<vector<int>>& order_temp, vector<int>& son_teslim)
{
	string del = ";";
	int i = 0;
	int start = 0;
	int end = s.find(del);
	while (end != -1) {
		string tok1 = s.substr(start, end - start);
		temp.push_back(stoi(tok1));
		/*cout << tok1 << endl;*/
		start = end + del.size();
		end = s.find(del, start);
		i++;
	}
	order_temp.push_back(temp);
	temp.clear();
	string tok = s.substr(start, end - start);
	son_teslim.push_back(stoi(tok));

}

int main() {
	vector<int>  temp;
	vector<int>  kurulum;
	vector<vector<int>> gecisler;
	vector<vector<int>>  order_temp;
	vector<int> siparis_kodu;
	vector<int> is_uzunlugu;
	vector<int> islem_kodu;
	vector<int> son_teslim;
	vector<int> order_kurulum;
	order_kurulum.push_back(0); // BAÞLANGIÇ DA KURULUM SÜRESÝ YOKTUR.
	vector<int>  islemhizi;
	vector<int>  islemkodu;
	int toplamdak = 0;

	ifstream  operations("operations.txt");
	string textline;
	islemhizi.push_back(0);    //0. ÝNDÝSLERÝNE  HERHANGÝ BÝR DEÐER ATIYORUM. ÝÞLEM KODU  VE VECTOR ÝNDÝSÝNÝN AYNI SAYIYI TUTMASI ÝÇÝN
	islemkodu.push_back(0);
	while (getline(operations, textline)) {

		string kod = textline.substr(0, textline.find(";"));
		string hiz = textline.substr(textline.find(";") + 1, textline.length());
		islemkodu.push_back(stoi(kod));
		islemhizi.push_back(stoi(hiz));
	}

	ifstream  setup_duration("Setup Duration.txt");
	string textline1;
	while (getline(setup_duration, textline1)) {
		setup_durations(textline1, temp, gecisler, kurulum);
	}
	/*for (int k = 0; k < gecisler.size(); k++) {
		for (int l = 0; l < 2; l++)
		{
			cout << k << "-" << l << " " << gecisler[k][l] << "->" << kurulum[k] << endl << endl;
		}
	}*/
	ifstream  order("orders2.txt");
	string textline2;
	while (getline(order, textline2)) {
		orders(textline2, temp, order_temp, son_teslim);
	}
	for (unsigned int k = 0; k < order_temp.size(); k++) {
		siparis_kodu.push_back(order_temp[k][0]);
		is_uzunlugu.push_back(order_temp[k][1]);
		islem_kodu.push_back(order_temp[k][2]);
	}

	for (unsigned int i = 0; i < son_teslim.size(); i++)
	{
		for (unsigned int j = 0; j < son_teslim.size(); j++)
		{
			if (son_teslim[i] < son_teslim[j]) {

				int temp;
				int temp2;
				int temp3;
				int temp4;
				temp = son_teslim[j];
				temp2 = siparis_kodu[j];
				temp3 = is_uzunlugu[j];
				temp4 = islem_kodu[j];
				son_teslim[j] = son_teslim[i];
				siparis_kodu[j] = siparis_kodu[i];
				is_uzunlugu[j] = is_uzunlugu[i];
				islem_kodu[j] = islem_kodu[i];
				son_teslim[i] = temp;
				siparis_kodu[i] = temp2;
				is_uzunlugu[i] = temp3;
				islem_kodu[i] = temp4;
			}
		}
	}
	/*for (unsigned int k = 0; k < son_teslim.size(); k++) {

		cout << siparis_kodu[k] << "  " << is_uzunlugu[k] << " " << islem_kodu[k] << "  " << son_teslim[k] << endl;

	}*/
	for (unsigned int i = 0; i < siparis_kodu.size(); i++)
	{
		cout << i << " " << siparis_kodu[i] << ";" << is_uzunlugu[i] << ";" << islem_kodu[i] << ";" << son_teslim[i] << endl;
	}
	for (unsigned int i = 0; i < siparis_kodu.size(); i++)
	{
		for (unsigned int k = i + 1; k < siparis_kodu.size(); k++)
		{
			if (k == i + 1) {
				for (unsigned int b = 0; b < gecisler.size(); b++)
				{
					if (islem_kodu[i] == gecisler[b][0] && islem_kodu[k] == gecisler[b][1])
						order_kurulum.push_back(kurulum[b]);
					else if (islem_kodu[i] == gecisler[b][1] && islem_kodu[k] == gecisler[b][0])
						order_kurulum.push_back(kurulum[b]);
				}
				if (islem_kodu[i] == islem_kodu[k])
					order_kurulum.push_back(0);
			}
		}
		for (int j = 1; j < islemhizi.size(); j++)
		{
			if (islem_kodu[i] == islemkodu[j]) {
				toplamdak = is_uzunlugu[i] / islemhizi[j] ;
				cout << " islem kodu: " << islemkodu[j] << " islem hizi: " << islemhizi[j] ;
				cout << " Gecisi:  " << order_kurulum[i] << "  son teslim: " <<  son_teslim[i]<< "  DAKIKA:  " << toplamdak << endl;

			}
		}
	}

	/*for (int i = 0; i < order_kurulum.size(); i++)
	{
		cout << i << "KURULUM  " << order_kurulum[i] << endl;

	}*/


	return 0;
}