#pragma once
#include <easyx.h>
#include <vector>

class BoardGame;

enum GameState
{
    MainMenuState, SelectGameState, AboutState, TheGameState, GameOverState, ExitGameState
};

class GameManager
{
public:

    static GameManager* Instance();
    /// <summary>
    /// 获取状态信息
    /// </summary>
    GameState GetState();

    std::vector<BoardGame*>& GetGames();

    // 在指定状态时更新游戏
    void UpdateMainMenu();
    void UpdateSelectGame();
    void UpdateGame();
    void UpdateAbout();
    void FixedUpdateGame();
    void UpdateGameOver();

    HWND GetGameWindow() const;

private:

    //static GameManager* _instance;

    IMAGE _mainMenuImages[3]; // 主菜单中使用的选择不同按钮的贴图
    bool _mainMenuButtonIsPress = false; // 用于实现GetKeyDown
    int _mainMenuSelect = 0; // 主菜单中的功能选择

    IMAGE* _selectGameBackground = new IMAGE;
    bool _selectLevelsButtonIsPress = false;
    int _GameIndex = 0;

    IMAGE _aboutBackground;
    bool _aboutButtonIsPress = false;

    IMAGE _gameOverImages[2];

    GameState _state = MainMenuState; // 游戏的状态

    std::vector<BoardGame*> _games;

    BoardGame* currentGame;

    HWND _theGameWindow;

    GameManager();
    // 当进入指定状态时执行
    void OnMainMenu();
    void OnSelectGame();
    void OnAbout();
    void OnServerGame();
    void OnClientGame();
    void OnGameOver(bool isWin);
    void OnExitGame();

    void InitGame();

    ///// <summary>
    ///// 初始化关卡场景
    ///// </summary>
    //void InitLevelScene();
};

