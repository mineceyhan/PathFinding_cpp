

// Mine CEYHAN
// 1306190082
// Tarih: 16.05.2021
// Geliþtirme Ortamý: Visual Studio 2019


#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <functional>

using namespace std;


int main() {

	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string textline;
	vector<string> startedge; // A1->B1   A1 i alýr
	vector<string> endedge;   // A1->B1   B1 i alýr
	vector<string> path; 
	vector<vector<string>> dongu;

	int i = 0, s = 0, g = 0;
	while (getline(fin, textline)) {

		if (textline.find("->") != string::npos) {
			startedge.push_back(textline.substr(0, textline.find("->")));
			endedge.push_back(textline.substr(textline.find("->") + 2, textline.length()));
			string start = startedge[i];
			i++;
		}
		if (textline.find(":") == string::npos && textline.find(",") == string::npos && textline.find("->") == string::npos) {
			path.push_back(textline);
			g++;
		}
	}
	vector<string> temp;
	for (int d = 0; d < path.size(); d++) {
		int satiruzunlugu = path[d].size();
		for (int s = 0; s < path[d].length(); s++) {
			string pathparser = path[d].substr(s, 1);
			string pathparser1 = path[d].substr(s + 1, 1);
			for (int start = 0; start < startedge.size(); start++) {
				if (startedge[start].substr(0, 1) == pathparser) {
					if (endedge[start].substr(0, 1) == pathparser1) {
						string for_temple = startedge[start] + "=>" + endedge[start];
						temp.push_back(for_temple);
					}
				}
			}
			dongu.push_back(temp);
			temp.clear();
		}
		int gecicisayac = 0;
		for (int i = 0; i < dongu.size(); i++)
		{
			int sayac = 0;
			for (int j = 0; j < dongu[i].size(); j++)
			{
				for (int k = i + 1; k < dongu.size(); k++)
				{
					for (int l = 0; l < dongu[k].size(); l++)
					{
						if (k == i + 1) {
							string end = dongu[i][j].substr(dongu[i][j].find("=>") + 2, dongu[i][j].length());
							string begin = dongu[k][l].substr(0, dongu[k][l].find("=>"));
							if (end == begin && begin != "") {
								sayac++;
							}
						}
					}
				}
			} if (sayac >= 1) { gecicisayac++; }
		}

		if (path[d] != "") {
			fout << path[d] ; 
			if (gecicisayac + 2 == satiruzunlugu) {
				fout << " [YES]" << endl;;
			}
			else 
				fout << " [NO]" << endl;;
			dongu.clear();	
		}
	}

	fin.close();
	fout.close();

	return 0;
}
