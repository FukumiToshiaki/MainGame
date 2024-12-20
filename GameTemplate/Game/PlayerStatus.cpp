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

	//�ŏ��̈�s�ڂ��΂�
	getline(fileOpen, line);

	while (getline(fileOpen, line)) {
		PlayerStatusStruct playerStatesStruct;
		
		//1�s��������œǂݍ���
		istringstream stream(line);
		
		//HP��ǂ݂���
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
