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

	//Å‰‚Ìˆês–Ú‚ğ”ò‚Î‚·
	getline(fileOpen, line);

	while (getline(fileOpen, line)) {
		PlayerStatusStruct playerStatesStruct;
		
		//1s‚¸‚Â•¶š—ñ‚Å“Ç‚İ‚Ş
		istringstream stream(line);
		
		//HP‚ğ“Ç‚İ‚±‚Ş
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
