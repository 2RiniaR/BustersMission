#pragma once

//----------------------------------------------------------
// ÉQÅ[ÉÄÇÃê›íË
//----------------------------------------------------------
class GAME_CONFIG {

private:
	int BGMvolume;
	int SEvolume;

public:
	GAME_CONFIG();
	int GetBGMVolume() { return BGMvolume; };
	int GetSEVolume() { return SEvolume; };
	void ChangeBGMVolume(int BGMVol) { BGMvolume = BGMVol; };
	void ChangeSEVolume(int SEVol) { SEvolume = SEVol; };

};
