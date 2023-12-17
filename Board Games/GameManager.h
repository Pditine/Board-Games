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
    /// ��ȡ״̬��Ϣ
    /// </summary>
    GameState GetState();

    std::vector<BoardGame*>& GetGames();

    // ��ָ��״̬ʱ������Ϸ
    void UpdateMainMenu();
    void UpdateSelectGame();
    void UpdateGame();
    void UpdateAbout();
    void FixedUpdateGame();
    void UpdateGameOver();

private:

    //static GameManager* _instance;
    GameManager();

    IMAGE _mainMenuImages[3]; // ���˵���ʹ�õ�ѡ��ͬ��ť����ͼ
    bool _mainMenuButtonIsPress = false; // ����ʵ��GetKeyDown
    int _mainMenuSelect = 0; // ���˵��еĹ���ѡ��

    IMAGE* _selectGameBackground = new IMAGE;
    bool _selectLevelsButtonIsPress = false;
    int _selectLeverlSelect = 0;

    IMAGE _aboutBackground;
    bool _aboutButtonIsPress = false;

    IMAGE _gameOverImages[2];

    GameState _state = MainMenuState; // ��Ϸ��״̬

    std::vector<BoardGame*> _games;

    // ������ָ��״̬ʱִ��
    void OnMainMenu();
    void OnSelectGame();
    void OnAbout();
    void OnGame();
    void OnGameOver(bool isWin);
    void OnExitGame();

    void InitGame();

    ///// <summary>
    ///// ��ʼ���ؿ�����
    ///// </summary>
    //void InitLevelScene();
};

