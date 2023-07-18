#pragma once
#include "../Include/AudioComponent.h"
/**
@brief �����, ���������� �� ���������� ��������������� �����������
@detailed ����������� �� ������ juce::Component. � ������ ����������� ����������� ���������/������������� ���������������,
���������� � ���������/���������� ���������� �� ������� ���������������. ����� ����������� ����������� �������� ����� ���,
����� ����� ������ � ���������� � ������ �������� ����������
*/
static int fadeTime;
static int currentPosNumber;
static int lastPosNumber;
static int scrollBarThickness;
static int queueComponentXOffset;

class PlayerComponent : public Component,
    public Button::Listener,
    public Slider::Listener,
    public Timer
{
    class MyLabel : public Label
    {
    public:
        MyLabel(const String& componentName, const String& labelText, PlayerComponent* _playerComp)
            :Label(componentName, labelText)
        {
            this->playerComp = _playerComp;
        }
        PlayerComponent* playerComp;
        void mouseDown(const MouseEvent& event) override;
    };
public:
    /**
@brief �����������
@param _audioComponent ����� ����������
*/
    PlayerComponent(AudioComponent* _audioComponent);
    /**
@brief ����������
*/
    ~PlayerComponent(void) override;
    /**
@brief ������� ���������
*/
    void paint(Graphics&) override;
    /**
@brief ������� ��������� �������
*/
    void resized() override;
    /**
@brief ������� ������������ ������� ������
@param button ������� ������
*/
    void buttonClicked(Button* button)  override;
    /**
@brief ������� ������������ ��������� ��������� ��������
@param slider �������, ���������� ���������
*/
    void sliderValueChanged(Slider* slider) override;
    /**
@brief ������� ���������� ����� � ������� ���������������
@param _file ���� ��� ���������� � �������
*/
    void addToQueue(File _file);
    /**
@brief ������� ��������� �������� ��������� ��� ������������� �������
*/
    void timerCallback() override;
    /**
@brief ������� ��� ����������� ����������� �������, ��������������� � ��������
@param timeInSeconds ����� � ��������
@return �������� ����������� ������� � �������
*/
    String secondsToStringTime(double timeInSeconds);
    void mouseDown(const MouseEvent& event) override;
    void fadeOutQueueComponent();
    //
    //std::vector<juce::File> fileQueue;
private:
    //
    class QueueComponent : public Component,
        public Button::Listener
    {
    public:
        QueueComponent();
        ~QueueComponent(void);
        void paint(Graphics& g) override;
        void resized() override;
        void buttonClicked(Button* button)  override;
        Path* internalPath;
        //
        void pushBack(File _file);
        File at(uint32 _index);
        int size();
    private:
        class QueueElement : public Component
        {
            class MyLabel : public Label
            {
            public:
                MyLabel(const String& componentName, const String& labelText, int *_queuePos) 
                    :Label(componentName, labelText)
                {
                    this->queuePos = _queuePos;
                }
                int* queuePos;
                void mouseDown(const MouseEvent& event) override;
            };
        public:
            QueueElement(String _name, int _queuePos);
            ~QueueElement(void);
            void paint(Graphics& g) override;
            void resized() override;
            ScopedPointer<MyLabel> songName;
            Path* internalPath;
        private:
            int queuePos;
            void mouseDown(const MouseEvent& event) override;
            //ScopedPointer<Label> songName;
        };
        //
        class QueueWindow : public Component
        {
        public:
            QueueWindow();
            ~QueueWindow();
            void paint(Graphics& g) override;
            void resized() override;
            std::vector<juce::File> fileQueue;
            OwnedArray<QueueElement> queueElements;
            Path* internalPath;
            //
            void pushBack(File _file);
            File at(uint32 _index);
            int size();
            void refresh();
        };
        //
        QueueWindow* queueWindow;
        Viewport* queueViewport;
        ScopedPointer <ImageButton> queueButton;
        ComponentAnimator animator;
        //
        File parentDirecory = File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory();
        String iconsFilePath = parentDirecory.getFullPathName() + "\\Resources\\Icons\\";
        Image queueButtonImage = ImageCache::getFromFile(File(iconsFilePath + "barsIcon.png"));
        //
        void queueButtonClicked();
    };
    //
    ComponentAnimator animator;
    DropShadower *dropShadowerPlayer, *dropShadowerQueueComponent;
    AudioComponent* audioComponent;
    QueueComponent queueComponent;
    std::unique_ptr<juce::FileChooser> chooser;
    AudioFormatManager formatManager;
    PositionableAudioSource* positionableSource;
    Slider durationSlider;
    Label  durationLabel;
    bool isMinimized;
    File currentFile;
    //
    int songCoverWidth, songCoverHeight;
    int coverX, coverY;
    ScopedPointer<Label> currentPositionLabel, totalLengthLabel;
    TextButton stopButton, chooseButton;
    ScopedPointer <ImageButton> playButton, nextButton, prevButton, upDownButton, queueButton;
    ScopedPointer<Label> playingSongName;
    ScopedPointer<Label> playingSongArtist;
    //
    void playButtonClicked();
    void nextButtonClicked();
    void prevButtonClicked();
    void minimizeButtonClicked();
    void queueButtonClicked();
    //
    void setCurrentFile(juce::File _file);
    void changeButtonIcons();
    void setNextTrack();
    void setCurrentTrack();
    //
    File parentDirecory = File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory();
    String iconsFilePath = parentDirecory.getFullPathName() + "\\Resources\\Icons\\";
    //
    Image playButtonImage = ImageCache::getFromFile(File(iconsFilePath + "playButton.png"));
    Image pauseButtonImage = ImageCache::getFromFile(File(iconsFilePath + "pauseButton.png"));
    Image browseButtonImage = ImageCache::getFromFile(File(iconsFilePath + "browseButton.png"));
    Image prevButtonImage = ImageCache::getFromFile(File(iconsFilePath + "prevButton.png"));
    Image nextButtonImage = ImageCache::getFromFile(File(iconsFilePath + "nextButton.png"));
    Image downButtonImage = ImageCache::getFromFile(File(iconsFilePath + "homeIcon.png"));
    Image upButtonImage = ImageCache::getFromFile(File(iconsFilePath + "upIcon.png"));
    Image queueButtonImage = ImageCache::getFromFile(File(iconsFilePath + "barsIcon.png"));
    //Image songCoverPlaceholder = ImageCache::getFromFile(File(iconsFilePath + "songCoverPlaceholder.png"));
    Image songCoverPlaceholder = ImageCache::getFromFile(File(iconsFilePath + "comingToTerms.png"));
    //
    Path internalPath1;
    //
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerComponent)
};