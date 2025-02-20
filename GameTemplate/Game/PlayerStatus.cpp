#include "stdafx.h"
#include "PlayerStatus.h"


using namespace std;

void PlayerStatus::Init()
{
	FILE* file = nullptr;

	string PlayerFile = "Assets/csv/PlayerParameter.csv";

	std::ifstream fileOpen(PlayerFile);
	if (!fileOpen.is_open()) {
		return;
	}
	
	string line;

	string buf;

	//最初の一行目を飛ばす
	getline(fileOpen, line);

	while (getline(fileOpen, line)) {
		PlayerStatusStruct playerStatesStruct;
		
		//1行ずつ文字列で読み込む
		istringstream stream(line);
		
		//HPを読みこむ
		getline(stream, buf, ',');
		playerStatesStruct.HP = stof(buf);
		
		getline(stream, buf, ',');
		playerStatesStruct.MeleeAttack = stoi(buf);

		getline(stream, buf, ',');
		playerStatesStruct.Defense = stoi(buf);

		playerStatusStructs.emplace_back(playerStatesStruct);

	}

	fileOpen.close();
}
