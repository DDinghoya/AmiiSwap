#pragma once

#include <pu/Plutonium>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <stdlib.h>
#include <filesystem>
#include "nfpemu.h"

class AmiiboFile {
	public:
		AmiiboFile(std::string Name, std::string BinPath);
		std::string GetName();
		std::string GetPath();
	private:
		std::string Name;
		std::string BinPath;
};

class AmiiboGame {
	public:
		AmiiboGame(std::string Name, std::string FolderPath);
		std::string GetName();
		std::string GetPath();
		std::vector<AmiiboFile*> GetBinFiles();
		void AddAmiiboFile(AmiiboFile*);
		void SetAmiiboFiles(std::vector<AmiiboFile*> amiiboFiles);
	private:
		std::string Name;
		std::string FolderPath;
		std::vector<AmiiboFile*> amiiboFiles;
};

static inline char* getExtension(const char* str)
{
	const char* p;
	for (p = str+strlen(str); p >= str && *p != '.'; p--);
	return (char*)p;
}

std::vector<AmiiboGame> SearchAmiibos();

class MainLayout : public pu::Layout
{
    public:
        MainLayout();
		void item_Click(AmiiboFile *menuItem);
		void category_Click(AmiiboGame *game);
		void GetFolders();
		std::vector<AmiiboFile*> GetEmuiibo();
		pu::element::Menu *MainLayout::GetGamesMenu();
		pu::element::Menu *MainLayout::GetAmiiboMenu();
    private:
        pu::element::TextBlock *titleText;
        pu::element::Menu *gamesMenu;
        pu::element::Menu *amiiboMenu;
		std::vector<AmiiboGame*> amiiboGames;
		std::vector<AmiiboFile*> files;
		std::vector<pu::element::MenuItem*> gameItems;
		bool waitInput;
		bool isEmuuibo;
};

class MainApplication : public pu::Application
{
    public:
        MainApplication();
		void SetWaitBack(bool state);
    private:
        MainLayout *mainLayout;
		bool waitBack = false;
};

void SetMainApplication(MainApplication *MainApp);
