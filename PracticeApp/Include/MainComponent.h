#pragma once
//
#include "../Include/PlayerComponent.h"
#include "../Include/BrowserComponent.h"
/**
@brief Класс, отвечающий за содержание MainFrame
@detailed Унаследован от класса juce::Component. Главный класс, отвечающий за весь функционал приложения
*/
class MainComponent : public Component
{
public:
    /**
@brief Конструктор
*/
    MainComponent(void);
    /**
@brief Деструктор
*/
    ~MainComponent(void) override;
    /**
@brief Функция отрисовки
*/
    void paint(Graphics&) override;
    /**
@brief Функция изменения размера
*/
    void resized(void) override;
    //
private:
    AudioComponent* audioComponent;
    PlayerComponent* playerComponent;
    BrowserComponent* browserComponent;
    //
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};