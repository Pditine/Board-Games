#pragma once
#include <easyx.h>

enum GameState
{
    MainMenuState, SelectLevelState, AboutState, theGameState, GameOverState, ExitGameState
};

class GameManager
{
public:

    //static GameManager* Instance();

    /// <summary>
    /// ��ȡ״̬��Ϣ
    /// </summary>
    GameState GetState();

    // ��ָ��״̬ʱ������Ϸ
    void UpdateMainMenu();
    void UpdateSelectLevel();
    void UpdateGame();
    void UpdateAbout();
    void FixedUpdateGame();
    void UpdateGameOver();

    GameManager();
private:

    //static GameManager* _instance;

    IMAGE _mainMenuImages[3]; // ���˵���ʹ�õ�ѡ��ͬ��ť����ͼ
    bool _mainMenuButtonIsPress = false; // ����ʵ��GetKeyDown
    int _mainMenuSelect = 0; // ���˵��еĹ���ѡ��

    IMAGE _selectLevelsImages[5];
    bool _selectLevelsButtonIsPress = false;
    int _selectLeverlSelect = 0;

    IMAGE _aboutBackground;
    bool _aboutButtonIsPress = false;

    IMAGE _gameOverImages[2];

    GameState _state = MainMenuState; // ��Ϸ��״̬

    // ������ָ��״̬ʱִ��
    void OnMainMenu();
    void OnSelectLevel();
    void OnAbout();
    void OnGame();
    void OnGameOver(bool isWin);
    void OnExitGame();

    /// <summary>
    /// ��ʼ����Ϸ
    /// </summary>
    void InitGame();

    /// <summary>
    /// ��ʼ���ؿ�����
    /// </summary>
    void InitLevelScene();
};

