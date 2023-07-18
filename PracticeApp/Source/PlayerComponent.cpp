#include "../Include/PlayerComponent.h"
//
PlayerComponent::PlayerComponent(AudioComponent*_audioComponent)
{
    queueComponentXOffset = 10;
    scrollBarThickness = 6;
    fadeTime = 250;
    isMinimized = false;
    audioComponent = _audioComponent;
    currentPosNumber = 0;
    addAndMakeVisible(playingSongName = new MyLabel("SongName", String((std::wstring(L"Название")).c_str()), this));
    playingSongName->setFont(Font(24.00f, Font::bold));
    playingSongName->setJustificationType(Justification::left);
    playingSongName->setEditable(false, false, false);
    playingSongName->setColour(Label::textColourId, Colours::white);
    playingSongName->setColour(TextEditor::textColourId, Colours::white);
    playingSongName->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    playingSongName->setMinimumHorizontalScale(1);
    //
    addAndMakeVisible(playingSongArtist = new MyLabel("SongArtist", String((std::wstring(L"Исполнитель")).c_str()), this));
    playingSongArtist->setFont(Font(12.00f, Font::plain));
    playingSongArtist->setJustificationType(Justification::left);
    playingSongArtist->setEditable(false, false, false);
    playingSongArtist->setColour(Label::textColourId, Colours::white);
    playingSongArtist->setColour(TextEditor::textColourId, Colours::white);
    playingSongArtist->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    playingSongArtist->setMinimumHorizontalScale(1);
    //
    addAndMakeVisible(totalLengthLabel = new MyLabel("TotalLength", "00:00", this));
    totalLengthLabel->setFont(Font(10.00f, Font::bold));
    totalLengthLabel->setJustificationType(Justification::centred);
    totalLengthLabel->setEditable(false, false, false);
    totalLengthLabel->setColour(Label::textColourId, Colours::white);
    totalLengthLabel->setColour(TextEditor::textColourId, Colours::white);
    totalLengthLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    totalLengthLabel->setMinimumHorizontalScale(1);
    //
    addAndMakeVisible(currentPositionLabel = new MyLabel("CurrentPosition", "00:00", this));
    currentPositionLabel->setFont(Font(10.00f, Font::bold));
    currentPositionLabel->setJustificationType(Justification::centred);
    currentPositionLabel->setEditable(false, false, false);
    currentPositionLabel->setColour(Label::textColourId, Colours::white);
    currentPositionLabel->setColour(TextEditor::textColourId, Colours::white);
    currentPositionLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    currentPositionLabel->setMinimumHorizontalScale(1);
    //
    playButton = new ImageButton();
    playButton->setImages(false, true, true, playButtonImage, 1, Colours::transparentWhite, playButtonImage, 0.2, Colours::transparentWhite, playButtonImage, 1, Colours::white);
    addAndMakeVisible(playButton);
    playButton->addListener(this);
    //
    queueButton = new ImageButton();
    queueButton->setImages(false, true, true, queueButtonImage, 1, Colours::transparentWhite, queueButtonImage, 0.2, Colours::transparentWhite, queueButtonImage, 1, Colours::white);
    addAndMakeVisible(queueButton);
    queueButton->addListener(this);
    //
    nextButton = new ImageButton();
    nextButton->setImages(false, true, true, nextButtonImage, 1, Colours::transparentWhite, nextButtonImage, 0.2, Colours::transparentWhite, nextButtonImage, 1, Colours::white);
    addAndMakeVisible(nextButton);
    nextButton->addListener(this);
    //
    prevButton = new ImageButton();
    prevButton->setImages(false, true, true, prevButtonImage, 1, Colours::transparentWhite, prevButtonImage, 0.2, Colours::transparentWhite, prevButtonImage, 1, Colours::white);
    addAndMakeVisible(prevButton);
    prevButton->addListener(this);
    //
    upDownButton = new ImageButton();
    upDownButton->setImages(false, true, true, downButtonImage, 1, Colours::transparentWhite, downButtonImage, 0.2, Colours::transparentWhite, downButtonImage, 1, Colours::white);
    addAndMakeVisible(upDownButton);
    upDownButton->addListener(this);
    //
    playButton->setEnabled(false);
    nextButton->setEnabled(false);
    prevButton->setEnabled(false);
    queueButton->setEnabled(true);
    //
    setOpaque(true);
    setSize(400, 600);
    //
    addAndMakeVisible(durationSlider);
    durationSlider.setSliderSnapsToMousePosition(true);
    durationSlider.onDragStart = [this] {
        audioComponent->transportSetGain(0.0f);
    };
    durationSlider.onDragEnd = [this] {
        audioComponent->transportSetGain(1.0f);
    };
    durationSlider.addListener(this);
    durationSlider.setDoubleClickReturnValue(false, 0);
    durationSlider.setSliderSnapsToMousePosition(true);
    formatManager.registerBasicFormats();
    //
    addAndMakeVisible(queueComponent);
    queueComponent.setVisible(false);
    queueComponent.internalPath = &internalPath1;
    //
    DropShadow dropShadowPlayer(Colours::black, 105, Point(0,0));
    dropShadowerPlayer = new DropShadower(dropShadowPlayer);
    dropShadowerPlayer->setOwner(this);
    //
    DropShadow dropShadowQueueComponent(Colours::black, 30, Point(0, 0));
    dropShadowerQueueComponent = new DropShadower(dropShadowQueueComponent);
    dropShadowerQueueComponent->setOwner(&queueComponent);
}
//
PlayerComponent::~PlayerComponent(void)
{
    playButton->removeListener(this);
    nextButton->removeListener(this);
    prevButton->removeListener(this);
    upDownButton->removeListener(this);
    queueButton->removeListener(this);
    durationSlider.removeListener(this);
    delete(dropShadowerPlayer);
    delete(dropShadowerQueueComponent);
}
//
void PlayerComponent::paint(Graphics& g)
{
    int borderSize = 4;
    int borderSizeMinimized = 2;
    if (isMinimized == false) {
        Colour colour1(0, 0, 0);
        Colour colour2(73, 46, 83);
        ColourGradient gradient(colour1, 0, 0, colour2, getWidth(), getHeight(), false);
        g.setGradientFill(gradient);
        g.fillAll();
        g.setColour(Colours::white);
        g.fillPath(internalPath1);
        g.setColour(Colour(0xff6f6f6f));
        g.strokePath(internalPath1, PathStrokeType(5.200f));
        //
        currentPositionLabel->setText(secondsToStringTime(audioComponent->transportGetCurrentPosition()), dontSendNotification);
        //
        durationSlider.setValue(audioComponent->transportGetCurrentPosition(), dontSendNotification);
        Colour sliderBackgroundColour(133, 127, 135);
        Colour sliderThumbColour(217, 217, 217);
        Colour sliderTrackColour(255, 255, 255);
        durationSlider.setColour(Slider::ColourIds::backgroundColourId, sliderBackgroundColour);
        durationSlider.setColour(Slider::ColourIds::thumbColourId, sliderThumbColour);
        durationSlider.setColour(Slider::ColourIds::trackColourId, sliderTrackColour);
        //
        Colour colour1_(146, 118, 156);
        Colour colour2_(133, 127, 135);
        ColourGradient gradient_(colour1_, (coverX + songCoverWidth) / 2, coverY, colour2_, (coverX + songCoverWidth) / 2, coverY + songCoverHeight, false);
        g.setGradientFill(gradient_);
        g.fillRoundedRectangle(coverX - borderSize, coverY - borderSize, (songCoverWidth + borderSize * 2), (songCoverHeight + borderSize * 2), getHeight() / 100.0f);
        g.drawImageAt(songCoverPlaceholder.rescaled(songCoverWidth, songCoverHeight), coverX, coverY);
    }
    else {
        Colour colour1(89, 66, 97);
        Colour colour2(89, 66, 97);
        ColourGradient gradient(colour1, 0, 0, colour2, 400, 600, false);
        g.setGradientFill(gradient);
        g.fillAll();
        g.setColour(Colours::white);
        g.fillPath(internalPath1);
        g.setColour(Colour(0xff6f6f6f));
        g.strokePath(internalPath1, PathStrokeType(5.200f));
        durationSlider.setValue(audioComponent->transportGetCurrentPosition(), dontSendNotification);
        Colour sliderBackgroundColour(133, 127, 135);
        Colour sliderThumbColour(217, 217, 217);
        Colour sliderTrackColour(255, 255, 255);
        durationSlider.setColour(Slider::ColourIds::backgroundColourId, sliderBackgroundColour);
        durationSlider.setColour(Slider::ColourIds::thumbColourId, sliderThumbColour);
        durationSlider.setColour(Slider::ColourIds::trackColourId, sliderTrackColour);
        //
        Colour colour1_(146, 118, 156);
        Colour colour2_(133, 127, 135);
        ColourGradient gradient_(colour1_, (coverX + songCoverWidth) / 2, coverY, colour2_, (coverX + songCoverWidth) / 2, coverY + songCoverHeight, false);
        g.setGradientFill(gradient_);
        g.fillRoundedRectangle(coverX - borderSizeMinimized, coverY - borderSizeMinimized, (songCoverWidth + borderSizeMinimized * 2), (songCoverHeight + borderSizeMinimized * 2), getHeight() / 100.0f);
        g.drawImageAt(songCoverPlaceholder.rescaled(songCoverWidth, songCoverHeight), coverX, coverY);
    }
}
//
void PlayerComponent::resized() {
    if (isMinimized == false) {

        setBounds(0, 0, getParentWidth(), getParentHeight());
        auto area = getLocalBounds();
        int playButtonWidth = 40;
        int playButtonHeight = 40;
        int nextButtonWidth = 30;
        int nextButtonHeight = 30;
        int nextPrevButtonsDistance = 55;
        int bottomSpace = 100;
        int buttonSpacing = 20;
        int sliderHeight = 10;
        int playerButtonsWidth = 30, playerButtonsHeight = 30;
        int areaWidth = area.getWidth();
        int areaHeight = area.getHeight();
        int areaHalfWidth = areaWidth / 2;
        //
        Rectangle playButtonArea(playButtonWidth, playButtonHeight);
        playButtonArea.setX(areaHalfWidth - (playButtonArea.getWidth() / 2));
        playButtonArea.setY(area.getBottom() - bottomSpace);
        playButton->setBounds(playButtonArea);
        internalPath1.clear();
        //
        Rectangle nextButtonArea(nextButtonWidth, nextButtonHeight);
        int NextButtonAreaHalfHeight = nextButtonArea.getHeight() / 2;
        nextButtonArea.setX(area.getCentreX() + nextPrevButtonsDistance);
        nextButtonArea.setY(playButtonArea.getCentreY() - NextButtonAreaHalfHeight);
        nextButton->setBounds(nextButtonArea);
        internalPath1.clear();
        //
        Rectangle prevButtonArea(nextButtonWidth, nextButtonHeight);
        prevButtonArea.setX(area.getCentreX() - nextPrevButtonsDistance - prevButtonArea.getWidth());
        prevButtonArea.setY(playButtonArea.getCentreY() - NextButtonAreaHalfHeight);
        prevButton->setBounds(prevButtonArea);
        internalPath1.clear();
        //
        int sliderWidth = (area.getWidth() * 95) / 100;
        Rectangle sliderArea(sliderWidth, sliderHeight);
        sliderArea.setX(areaHalfWidth - (sliderArea.getWidth() / 2));
        sliderArea.setY(area.getBottom() - bottomSpace - playButtonArea.getHeight());
        durationSlider.setBounds(sliderArea);
        durationSlider.setTextBoxStyle(Slider::TextEntryBoxPosition(), true, 0, 0);
        internalPath1.clear();
        int sliderAreaCentreY = sliderArea.getCentreY();
        //
        int titleSpacing = areaHeight / 24;
        int songArtistWidth = sliderWidth;
        int songArtistHeight = areaHeight / 40;
        Rectangle songArtistArea(songArtistWidth, songArtistHeight);
        songArtistArea.setX(areaHalfWidth - (songArtistArea.getWidth() / 2));
        songArtistArea.setY(sliderAreaCentreY - sliderArea.getHeight() / 2 - titleSpacing);
        playingSongArtist->setBounds(songArtistArea);
        playingSongArtist->setFont(Font((areaHeight / 25) / 2, Font::bold));
        //
        int songNameWidth = sliderWidth;
        int songNameHeight = areaHeight / 25;
        Rectangle songNameArea(songNameWidth, songNameHeight);
        songNameArea.setX(areaHalfWidth - (songNameArea.getWidth() / 2));
        songNameArea.setY(songArtistArea.getCentreY() - songArtistArea.getHeight() - titleSpacing);
        playingSongName->setBounds(songNameArea);
        playingSongName->setFont(Font(areaHeight / 25, Font::bold));
        //
        songCoverWidth = songCoverHeight = areaHeight / 2.3;
        coverX = areaHalfWidth - (songCoverWidth / 2);
        coverY = area.getCentreY() - songCoverHeight / 2 - (songNameArea.getHeight() + songNameArea.getHeight() + titleSpacing);
        //
        int timerWidth = area.getWidth() / 10;
        int timerHeight = areaHeight / 50;
        Rectangle totalTimeArea(timerWidth, timerHeight);
        totalTimeArea.setX(area.getCentreX() + areaHalfWidth - totalTimeArea.getWidth() - (area.getWidth() - sliderArea.getWidth()) / 2);
        totalTimeArea.setY(sliderAreaCentreY + 10);
        //
        Rectangle progressTimeArea(timerWidth, timerHeight);
        progressTimeArea.setX(area.getCentreX() - areaHalfWidth + (area.getWidth() - sliderArea.getWidth()) / 2);
        progressTimeArea.setY(sliderAreaCentreY + 10);
        //
        totalLengthLabel->setBounds(totalTimeArea);
        totalLengthLabel->setFont(Font(areaHeight / 50, Font::plain));
        internalPath1.clear();
        //
        currentPositionLabel->setBounds(progressTimeArea);
        currentPositionLabel->setFont(Font(areaHeight / 50, Font::plain));
        internalPath1.clear();
        //
        Rectangle queueButtonArea(playerButtonsWidth, playerButtonsHeight);
        queueButtonArea.setX(area.getRight() - queueButtonArea.getWidth() - buttonSpacing);
        queueButtonArea.setY(buttonSpacing);
        queueButton->setBounds(queueButtonArea);
        internalPath1.clear();
        //
        Rectangle minimizeButtonArea(playerButtonsWidth, playerButtonsHeight);
        minimizeButtonArea.setX(playerButtonsWidth);
        minimizeButtonArea.setY(buttonSpacing);
        upDownButton->setBounds(minimizeButtonArea);
        internalPath1.clear();
        //
        queueComponent.setSize(getWidth() / 1.5, getHeight() / 1.4);
    }
    else {
        int blindHeight = 71;
        setSize(getWidth(), blindHeight);
        setTopLeftPosition(0, getParentHeight() - getHeight());
        auto area = getLocalBounds();
        int playButtonWidth = 21;
        int playButtonHeight = 21;
        int nextButtonWidth = 25;
        int nextButtonHeight = 18;
        int nextPrevButtonsDistance = 55;
        int bottomSpace = 0;
        int buttonSpacing = 20;
        int sliderHeight = 10;
        int areaHalfWidth = area.getWidth() / 2;
        int areaHeight = area.getHeight();
        //
        Rectangle nextButtonArea(nextButtonWidth, nextButtonHeight);
        int nextButtonAreaHalfHeight = nextButtonHeight / 2;
        nextButtonArea.setX(area.getRight() - nextButtonWidth - buttonSpacing);
        nextButtonArea.setY(area.getCentreY() - nextButtonAreaHalfHeight);
        nextButton->setBounds(nextButtonArea);
        internalPath1.clear();
        //
        Rectangle playButtonArea(playButtonWidth, playButtonHeight);
        playButtonArea.setX(nextButtonArea.getCentreX() - nextPrevButtonsDistance);
        playButtonArea.setY(area.getCentreY() - playButtonHeight / 2);
        playButton->setBounds(playButtonArea);
        internalPath1.clear();
        //
        Rectangle prevButtonArea(nextButtonWidth, nextButtonHeight);
        prevButtonArea.setX(playButtonArea.getCentreX() - nextPrevButtonsDistance);
        prevButtonArea.setY(area.getCentreY() - nextButtonAreaHalfHeight);
        prevButton->setBounds(prevButtonArea);
        internalPath1.clear();
        //
        int sliderWidth = area.getWidth() + 6;
        Rectangle sliderArea(sliderWidth, sliderHeight);
        sliderArea.setX(areaHalfWidth - (sliderArea.getWidth() / 2));
        sliderArea.setY(area.getBottom() - area.getHeight() - sliderArea.getHeight() / 2 + 1);
        durationSlider.setBounds(sliderArea);
        durationSlider.setTextBoxStyle(Slider::TextEntryBoxPosition(), true, 0, 0);
        internalPath1.clear();
        int sliderAreaCentreY = sliderArea.getCentreY();
        //
        int titleSpacing = 0;
        int songArtistWidth = prevButtonArea.getX() - (coverX + songCoverWidth);
        int songArtistHeight = areaHeight / 7;
        Rectangle songArtistArea(songArtistWidth, songArtistHeight);
        songArtistArea.setX(coverX + songCoverWidth);
        songArtistArea.setY(area.getCentreY());
        playingSongArtist->setBounds(songArtistArea);
        playingSongArtist->setFont(Font(areaHeight / 7, Font::bold));
        //
        int songNameWidth = songArtistWidth;
        int songNameHeight = areaHeight / 3;
        Rectangle songNameArea(songNameWidth, songNameHeight);
        songNameArea.setX(coverX + songCoverWidth);
        songNameArea.setY(area.getCentreY() - songNameHeight);
        playingSongName->setBounds(songNameArea);
        playingSongName->setFont(Font(areaHeight/5, Font::bold));
        //
        songCoverWidth = songCoverHeight = areaHeight / 1.2;
        coverX = (areaHeight - (areaHeight / 1.2)) / 2;
        coverY = area.getCentreY() - songCoverHeight / 2;
        //
        int timerWidth = area.getWidth() / 10;
        int timerHeight = areaHeight / 50;
        Rectangle totalTimeArea(timerWidth, timerHeight);
        totalTimeArea.setX(area.getCentreX() + areaHalfWidth - totalTimeArea.getWidth() - (area.getWidth() - sliderArea.getWidth()) / 2);
        totalTimeArea.setY(sliderAreaCentreY + 10);
        //
        Rectangle progressTimeArea(timerWidth, timerHeight);
        progressTimeArea.setX(area.getCentreX() - areaHalfWidth + (area.getWidth() - sliderArea.getWidth()) / 2);
        progressTimeArea.setY(sliderAreaCentreY + 10);
        //
        Rectangle maximizeButtonArea(playButtonWidth, playButtonHeight);
        maximizeButtonArea.setX(prevButtonArea.getCentreX() - nextPrevButtonsDistance);
        maximizeButtonArea.setY(area.getCentreY() - playButtonHeight / 2);
        upDownButton->setBounds(maximizeButtonArea);
        internalPath1.clear();
    }
}
//
void PlayerComponent::addToQueue(File _file)
{
    queueComponent.pushBack(_file);
    if (queueComponent.size() == 1) {
        setCurrentFile(_file);
    }
}
//
void PlayerComponent::setCurrentFile(File _file) {
    audioComponent->changeState(AudioComponent::TransportState::Stopped);
    auto file = _file;
    if (file != File{})
    {
        AudioFormatReader* reader = formatManager.createReaderFor(file);

        if (reader != nullptr)
        {
            std::unique_ptr<AudioFormatReaderSource> newSource = std::make_unique<AudioFormatReaderSource>(reader, true);
            positionableSource = newSource.get();
            audioComponent->transportSetSource(positionableSource, reader->sampleRate);
            audioComponent->readerSourceReset(newSource.release());
            durationSlider.setRange(0, audioComponent->transportGetLengthInSeconds());
            totalLengthLabel->setText(secondsToStringTime(audioComponent->transportGetLengthInSeconds()), dontSendNotification);
            audioComponent->changeState(AudioComponent::TransportState::Starting);
            playingSongName->setText(file.getFileName(), dontSendNotification);
            playButton->setEnabled(true);
            nextButton->setEnabled(true);
            prevButton->setEnabled(true);
        }
    }
}
//
void PlayerComponent::playButtonClicked()
{
    if ((audioComponent->getState() == AudioComponent::TransportState::Stopped) || (audioComponent->getState() == AudioComponent::TransportState::Paused)) {
        audioComponent->changeState(AudioComponent::TransportState::Starting);
    }
    else if (audioComponent->getState() == AudioComponent::TransportState::Playing) {
        audioComponent->changeState(AudioComponent::TransportState::Pausing);
    }
}
//
void PlayerComponent::prevButtonClicked()
{
    if (audioComponent->transportGetCurrentPosition() > 1.0) {
        audioComponent->transportSetPosition(0);
    }
    else {
        if ((currentPosNumber - 1) >= 0) {
            currentPosNumber--;
            setCurrentFile(queueComponent.at(currentPosNumber));
        }
        else {
            audioComponent->transportSetPosition(0);
        }
    }
}
//
void PlayerComponent::nextButtonClicked()
{ 
    setNextTrack();
}
//
void PlayerComponent::minimizeButtonClicked()
{
    if (isMinimized == false) {
        isMinimized = true;
        resized();
        queueButton->setEnabled(false);
        queueButton->setVisible(false);
        upDownButton->setVisible(false);
    }
    else {
        isMinimized = false;
        queueButton->setEnabled(true);
        queueButton->setVisible(true);
        upDownButton->setVisible(true);
        upDownButton->setImages(false, true, true, downButtonImage, 1, Colours::transparentWhite, downButtonImage, 0.2, Colours::transparentWhite, downButtonImage, 1, Colours::white);
        resized();
    }
}
//
void PlayerComponent::mouseDown(const MouseEvent& event) {
    fadeOutQueueComponent();

    if (isMinimized == true) {
        isMinimized = false;
        queueButton->setEnabled(true);
        queueButton->setVisible(true);
        upDownButton->setVisible(true);
        upDownButton->setImages(false, true, true, downButtonImage, 1, Colours::transparentWhite, downButtonImage, 0.2, Colours::transparentWhite, downButtonImage, 1, Colours::white);
        resized();
    }

}
//
void PlayerComponent::MyLabel::mouseDown(const MouseEvent& event) {
    playerComp->mouseDown(event);
}
//
void PlayerComponent::queueButtonClicked() {
    animator.fadeIn(&queueComponent, fadeTime);
}
//
void PlayerComponent::buttonClicked(Button* button)
{
    if (button == playButton)
    {
        fadeOutQueueComponent();
        playButtonClicked();
    }

    if (button == queueButton)
    {
        fadeOutQueueComponent();
        queueButtonClicked();
    }

    if (button == nextButton)
    {
        fadeOutQueueComponent();
        nextButtonClicked();
    }

    if (button == prevButton)
    {
        fadeOutQueueComponent();
        prevButtonClicked();
    }

    if (button == upDownButton)
    {
        fadeOutQueueComponent();
        minimizeButtonClicked();
    }
}
//
void PlayerComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &durationSlider){
        audioComponent->transportSetPosition(slider->getValue());
    }
}
//
String PlayerComponent::secondsToStringTime(double timeInSeconds) {
    int minutes, seconds;
    minutes = ((int)timeInSeconds) / 60;
    seconds = ((int)timeInSeconds) - minutes * 60;
    String minutesString(minutes);
    String secondsString(seconds);
    //
    if (minutes <= 9) {
        minutesString = "0" + minutesString;
    }
    if (seconds <= 9) {
        secondsString = "0" + secondsString;
    }
    //
    String result = minutesString + ":" + secondsString;
    return result;
}
//
void PlayerComponent::timerCallback() {
    if (audioComponent->getTransportSourceFinishStatus() == true) {
        setNextTrack();
    }
    setCurrentTrack();
    changeButtonIcons();
    queueComponent.repaint();
}
//
void PlayerComponent::changeButtonIcons() {
    if (audioComponent->getState() == AudioComponent::TransportState::Playing) {
        playButton->setImages(false, true, true, pauseButtonImage, 1, Colours::transparentWhite, pauseButtonImage, 0.2, Colours::transparentWhite, pauseButtonImage, 1, Colours::white);
    }
    else {
        playButton->setImages(false, true, true, playButtonImage, 1, Colours::transparentWhite, playButtonImage, 0.2, Colours::transparentWhite, playButtonImage, 1, Colours::white);
    }
    if ((currentPosNumber + 1) >= (queueComponent.size())) nextButton->setEnabled(false);
    else nextButton->setEnabled(true);
}
//
void PlayerComponent::setNextTrack() {
    if ((currentPosNumber + 1) < (queueComponent.size())) {
        currentPosNumber++;
        setCurrentFile(queueComponent.at(currentPosNumber));
        lastPosNumber = currentPosNumber;
    }
}
//
void PlayerComponent::setCurrentTrack() {
    if (currentPosNumber != lastPosNumber) {
        lastPosNumber = currentPosNumber;
        setCurrentFile(queueComponent.at(currentPosNumber));
    }
}
//
void PlayerComponent::fadeOutQueueComponent() {
    animator.fadeOut(&queueComponent, fadeTime);
}
//
PlayerComponent::QueueComponent::QueueComponent() {
    setOpaque(true);
    queueButton = new ImageButton();
    queueButton->setImages(false, true, true, queueButtonImage, 1, Colours::transparentWhite, queueButtonImage, 0.2, Colours::transparentWhite, queueButtonImage, 1, Colours::white);
    addAndMakeVisible(queueButton);
    queueButton->addListener(this);
    //
    queueWindow = new QueueWindow();
    addAndMakeVisible(queueWindow);
    queueWindow->setBounds(0, 0, getWidth(), getHeight());
    queueWindow->internalPath = internalPath;
    //
queueViewport = new Viewport("queueViewport");
queueViewport->setViewedComponent(queueWindow, false);
queueViewport->setScrollBarsShown(true, false);
queueViewport->getVerticalScrollBar().setColour(ScrollBar::ColourIds::thumbColourId, Colours::white);
queueViewport->setScrollBarThickness(scrollBarThickness);
addAndMakeVisible(queueViewport);
}
PlayerComponent::QueueComponent::~QueueComponent(void) {
    delete(queueWindow);
    delete(queueViewport);
}
void PlayerComponent::QueueComponent::paint(Graphics& g) {
    Colour colour1_1(0, 0, 0);
    Colour colour1_2(73, 46, 83);
    ColourGradient gradient1(colour1_1, 0, 0, colour1_2, getParentWidth(), getParentHeight(), false);
    g.setColour(Colours::transparentWhite);
    g.fillAll();
    Colour colour2_1(89, 66, 97);
    Colour colour2_2(89, 66, 97);
    ColourGradient gradient2(colour2_1, 0, 0, colour2_2, getWidth(), getHeight(), false);
    g.setGradientFill(gradient2);
    g.fillRoundedRectangle(getParentWidth() - getWidth() * 1.5, getY(), getWidth(), getHeight(), getHeight() / 50.0f);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(getParentWidth() - getWidth() * 1.5, getY(), getWidth(), getHeight(), getHeight() / 50.0f, getHeight()/700.0f);
    g.setColour(Colours::white);
    g.fillPath(*internalPath);
    g.setColour(Colour(0xff6f6f6f));
    g.strokePath(*internalPath, PathStrokeType(5.200f));
}
void PlayerComponent::QueueComponent::resized() {
    int width = getWidth();
    int height = getHeight();
    setTopRightPosition(width * 1.5 - queueComponentXOffset, 0);
    auto area = getLocalBounds();
    //
    int playerButtonsWidth = 30, playerButtonsHeight = 30;
    int buttonSpacing = 20;
    Rectangle queueButtonArea(playerButtonsWidth, playerButtonsHeight);
    queueButtonArea.setX(area.getRight() - queueButtonArea.getWidth() - buttonSpacing + queueComponentXOffset);
    queueButtonArea.setY(buttonSpacing);
    queueButton->setBounds(queueButtonArea);
    //
    int leftOffset = 10;
    int bottomOffset = 5;
    queueViewport->setBounds(leftOffset, queueButtonArea.getBottom() + bottomOffset, (area.getRight() - 2 * leftOffset) / 1.05, area.getHeight() - bottomOffset - (queueButtonArea.getBottom() + bottomOffset));
    //
    if (queueViewport->isVerticalScrollBarShown()) {

    }
    else {

    }
    queueWindow->setSize(queueViewport->getWidth() - scrollBarThickness * 1.35, area.getHeight());
}
//
void PlayerComponent::QueueComponent::buttonClicked(Button* button) {
    if (button == queueButton)
    {
        queueButtonClicked();
    }
}
//
void PlayerComponent::QueueComponent::queueButtonClicked() {
    animator.fadeOut(this, fadeTime);
}
//
void PlayerComponent::QueueComponent::pushBack(File _file) {
    queueWindow->pushBack(_file);
}
//
File PlayerComponent::QueueComponent::at(uint32 _index) {
    return queueWindow->at(_index);
}
//
int PlayerComponent::QueueComponent::size() {
    return queueWindow->size();
}
//
PlayerComponent::QueueComponent::QueueWindow::QueueWindow() {
    setOpaque(true);
    setSize(100, 100);
    refresh();
}
//
PlayerComponent::QueueComponent::QueueWindow::~QueueWindow() {
    queueElements.clear();
}
//
void PlayerComponent::QueueComponent::QueueWindow::paint(Graphics& g) {
    Colour colour1(0, 0, 0);
    Colour colour2(73, 46, 83);
    ColourGradient gradient(colour1, 0, 0, colour2, 400, 600, false);
    g.setGradientFill(gradient);
    g.fillAll();
}
//
void PlayerComponent::QueueComponent::QueueWindow::resized() {
    int minHeight = getParentHeight() / 17;
    setSize(getWidth(), minHeight * (queueElements.size()));
    //
    FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;
    //
    for (int i = 0; i < queueElements.size(); i++) {
        fb.items.add(FlexItem(*queueElements[i]).withMinWidth(getWidth()).withMinHeight(minHeight));
        queueElements[i]->setSize(getWidth(), minHeight);
        queueElements[i]->songName->setSize(getWidth() / 1.1, minHeight);
        queueElements[i]->songName->setFont(Font(getParentHeight() / 30, Font::bold));
    }
    //
    fb.performLayout(getLocalBounds());
}
//
void PlayerComponent::QueueComponent::QueueWindow::pushBack(File _file) {
    fileQueue.push_back(_file);
    refresh();
}
//
File PlayerComponent::QueueComponent::QueueWindow::at(uint32 _index) {
    return fileQueue.at(_index);
}
//
int PlayerComponent::QueueComponent::QueueWindow::size() {
    return fileQueue.size();
}
//
void PlayerComponent::QueueComponent::QueueWindow::refresh() {
queueElements.clear();
int size = fileQueue.size();
for (int i = 0; i < size; i++) {
    QueueElement* tmp = new QueueElement(fileQueue[i].getFileName() , i);
    addAndMakeVisible(tmp);
    queueElements.add(tmp);
}
resized();
}
//
PlayerComponent::QueueComponent::QueueElement::QueueElement(String _name, int _queuePos) {
    setOpaque(true);
    setSize(getParentWidth(), getParentHeight()/60);
    //
    addAndMakeVisible(songName = new MyLabel("SongName", _name, &queuePos));
    songName->setFont(Font(getHeight() / 2, Font::bold));
    songName->setJustificationType(Justification::left);
    songName->setEditable(false, false, false);
    songName->setColour(MyLabel::textColourId, Colours::white);
    songName->setColour(TextEditor::textColourId, Colours::white);
    songName->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    songName->setMinimumHorizontalScale(1);
    queuePos = _queuePos;
}
//
PlayerComponent::QueueComponent::QueueElement::~QueueElement() {
}
//
void PlayerComponent::QueueComponent::QueueElement::paint(Graphics& g) {
    Colour colour2_1(89, 66, 97);
    Colour colour2_2(89, 66, 97);
    ColourGradient gradient2(colour2_1, 0, 0, colour2_2, getWidth(), getHeight(), false);
    g.setGradientFill(gradient2);
    g.fillAll();
    if (queuePos == currentPosNumber) {
        songName->setColour(Label::textColourId, Colours::white);
        g.setColour(Colours::white);
        g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5.5f, 2.5f);
    }
    else {
        songName->setColour(Label::textColourId, Colours::grey);
    }
}
//
void PlayerComponent::QueueComponent::QueueElement::resized() {}
//
void PlayerComponent::QueueComponent::QueueElement::mouseDown(const MouseEvent& event) {
    currentPosNumber = queuePos;
}
//
void PlayerComponent::QueueComponent::QueueElement::MyLabel::mouseDown(const MouseEvent& event) {
    currentPosNumber = *queuePos;
}