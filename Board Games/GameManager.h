#pragma once
#include <easyx.h>

enum GameState
{
    MainMenuState, SelectLevelState, AboutState, TheGameState, GameOverState, ExitGameState
};

class GameManager
{
public:

    static GameManager* Instance();

    /// <summary>
    /// 获取状态信息
    /// </summary>
    GameState GetState();

    // 在指定状态时更新游戏
    void UpdateMainMenu();
    void UpdateSelectLevel();
    void UpdateGame();
    void UpdateAbout();
    void FixedUpdateGame();
    void UpdateGameOver();

    GameManager();
private:

    //static GameManager* _instance;

    IMAGE _mainMenuImages[3]; // 主菜单中使用的选择不同按钮的贴图
    bool _mainMenuButtonIsPress = false; // 用于实现GetKeyDown
    int _mainMenuSelect = 0; // 主菜单中的功能选择

    IMAGE _selectLevelsImages[5];
    bool _selectLevelsButtonIsPress = false;
    int _selectLeverlSelect = 0;

    IMAGE _aboutBackground;
    bool _aboutButtonIsPress = false;

    IMAGE _gameOverImages[2];

    GameState _state = MainMenuState; // 游戏的状态

    // 当进入指定状态时执行
    void OnMainMenu();
    void OnSelectLevel();
    void OnAbout();
    void OnGame();
    /// 初始化游戏
    void OnGameOver(bool isWin);
    void OnExitGame();

    /// <summary>
    /// </summary>
    void InitGame();

    /// <summary>
    /// 初始化关卡场景
    /// </summary>
    void InitLevelScene();
};

