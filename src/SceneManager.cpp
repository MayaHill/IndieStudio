/*
** EPITECH PROJECT, 2021
** project
** File description:
** SceneManager.cpp
*/

#include "SceneManager.hpp"

namespace Indie {
    SceneManager::SceneManager()
    {
        this->scenes[Indie::Scenes::SPLASH] = std::make_unique<Indie::Scenes::SplashScene>();
        this->scenes[Indie::Scenes::MENU] = std::make_unique<Indie::Scenes::MenuScene>();
        this->scenes[Indie::Scenes::GAME] = std::make_unique<Indie::Scenes::GameScene>();
        this->scenes[Indie::Scenes::LOBBY] = std::make_unique<Indie::Scenes::LobbyScene>();
        this->scenes[Indie::Scenes::LEVEL] = std::make_unique<Indie::Scenes::LevelScene>();
        this->scenes[Indie::Scenes::SETTING] = std::make_unique<Indie::Scenes::SettingScene>();
        this->scenes[Indie::Scenes::PAUSE] = std::make_unique<Indie::Scenes::PauseScene>();
        this->isRunning = true;
    }

    void SceneManager::init()
    {
        this->scenes[this->currScene]->init();
    }

    void SceneManager::update()
    {
        enum Indie::Scenes::Scenes scene = this->scenes[this->currScene]->getChangingScene();
        if (scene != Indie::Scenes::UKNOWN) {
            if (scene == Indie::Scenes::QUIT)
                this->isRunning = false;
            else {
                this->scenes[scene]->setLoadSave(this->scenes[this->currScene]->getLoadSave());
                if (this->currScene == Indie::Scenes::PAUSE && scene == Indie::Scenes::SETTING) {
                    this->scenes[Indie::Scenes::SETTING]->changeBackScene(Indie::Scenes::PAUSE);
                } else {
                    this->scenes[Indie::Scenes::SETTING]->changeBackScene(Indie::Scenes::MENU);
                }
                if (this->currScene == Indie::Scenes::PAUSE && scene == Indie::Scenes::GAME) {
                    this->currScene = scene;
                    this->scenes[this->currScene]->update();
                    return;
                }
                this->currScene = scene;
                if (scene == Indie::Scenes::GAME)
                    this->scenes[scene]->setPlayerInfo(this->scenes[Indie::Scenes::LOBBY]->getPlayerInfo());
                this->init();
            }
        }
        this->scenes[this->currScene]->update();
    }

    void SceneManager::drawUnder2D()
    {
        this->scenes[this->currScene]->drawUnder2D();
    }

    void SceneManager::draw3D()
    {
        this->scenes[this->currScene]->draw3D();
    }

    void SceneManager::drawOver2D()
    {
        this->scenes[this->currScene]->drawOver2D();
    }

    bool SceneManager::getisRunning()
    {
        return this->isRunning;
    }
};
