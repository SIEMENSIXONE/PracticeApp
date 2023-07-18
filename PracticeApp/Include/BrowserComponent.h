#pragma once
#include "../Include/PlayerComponent.h"
/**
@brief Класс, отвечающий за отображение и функционирование библиотеки песен, альбомов, исполнителей
@detailed Унаследован от класса juce::Component. В библиотеке пользователь может выбрать интересующие его композиции и добавить их в очередь воспроизведения
*/
class BrowserComponent : public Component,
    public Button::Listener
{
public:
    /**
@brief Конструктор
@param _playerComponent Компонента плеера
*/
    BrowserComponent(PlayerComponent* _playerComponent);
    /**
@brief Деструктор
*/
    ~BrowserComponent(void) override;
    /**
@brief Функция отрисовки
*/
    void paint(Graphics&) override;
    /**
@brief Функция изменения размера
*/
    void resized() override;
    //
private:
    //
    class BrowserElement : public Component
    {
    public:
        BrowserElement();
        BrowserElement(String _name, String _artist, String _audioFilepath, String _coverFilepath);
        ~BrowserElement(void);
        void paint(Graphics& g) override;
        void resized() override;
        Path* internalPath;
    };
    //
    std::unique_ptr<juce::FileChooser> chooser;
    AudioFormatManager formatManager;
    PlayerComponent* playerComponent;
    //
    void buttonClicked(Button* button);
    void openButtonClicked();
    //
    File parentDirecory = File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory();
    String iconsFilePath = parentDirecory.getFullPathName() + "\\Resources\\Icons\\";
    String audioFilePath = parentDirecory.getFullPathName() + "\\Resources\\Audio\\";
    //
    Image browseButtonImage = ImageCache::getFromFile(File(iconsFilePath + "browseButton.png"));
    Image futureLibraryLabel = ImageCache::getFromFile(File(iconsFilePath + "futureLibraryLabel.png"));
    Image addFileToQueueLabel = ImageCache::getFromFile(File(iconsFilePath + "addFileToQueueLabel.png"));
    ScopedPointer <ImageButton> browseButton;
    Path internalPath1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserComponent)
};