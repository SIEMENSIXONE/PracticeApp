#include "../Include/BrowserComponent.h"
//
BrowserComponent::BrowserComponent(PlayerComponent* _playerComponent)
{
    playerComponent = _playerComponent;
    browseButton = new ImageButton();
    browseButton->setImages(false, true, true, browseButtonImage, 1, Colours::transparentWhite, browseButtonImage, 0.2, Colours::transparentWhite, browseButtonImage, 1, Colours::white);
    addAndMakeVisible(browseButton);
    browseButton->addListener(this);
    formatManager.registerBasicFormats();
    //
    setOpaque(true);
    setSize(400, 600);
}
//
BrowserComponent::~BrowserComponent(void)
{
    browseButton->removeListener(this);
}
//
void BrowserComponent::paint(Graphics& g)
{
        Colour colour1(0, 0, 0);
        Colour colour2(73, 46, 83);
        ColourGradient gradient(colour1, 0, 0, colour2, 400, 600, false);
        g.setGradientFill(gradient);
        g.fillAll();
        g.setColour(Colours::white);
        g.fillPath(internalPath1);
        g.setColour(Colour(0xff6f6f6f));
        g.strokePath(internalPath1, PathStrokeType(5.200f));
        //temp labels
        int labelWidth = 350;
        int labelHeight = labelWidth;
        Rectangle area = getLocalBounds();
        int smallLabelWidth = 200;
        int smallLabelHeight = smallLabelWidth / 2;
        g.drawImageAt(futureLibraryLabel.rescaled(labelWidth, labelHeight), area.getCentreX() - labelWidth/2, area.getCentreY() - labelHeight/2);
        g.drawImageAt(addFileToQueueLabel.rescaled(smallLabelWidth, smallLabelHeight), area.getWidth() - smallLabelWidth - 25, 50);
}
//
void BrowserComponent::buttonClicked(Button* button)
{
    if (button == browseButton)
    {
        openButtonClicked();
    }
}
//
void BrowserComponent::openButtonClicked() {
    chooser = std::make_unique<FileChooser>(String((std::wstring(L"Выберите аудиофайл...")).c_str()), File(audioFilePath), "*.wav;*.mp3");
    auto chooserFlags = FileBrowserComponent::openMode
        | FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != File{})
            {
                playerComponent->addToQueue(file);
            }
        });
}
//
void BrowserComponent::resized() {
        int buttonSpacing = 20;
        int playerButtonsWidth = 30, playerButtonsHeight = 30;
        setBounds(0, 0, getParentWidth(), getParentHeight());
        auto area = getLocalBounds();
        Rectangle browseButtonArea(playerButtonsWidth, playerButtonsHeight);
        browseButtonArea.setX(area.getRight() - browseButtonArea.getWidth() - buttonSpacing);
        browseButtonArea.setY(buttonSpacing);
        browseButton->setBounds(browseButtonArea);
        internalPath1.clear();
}
//
void BrowserComponent::BrowserElement::paint(Graphics& g) {
    g.setColour(Colours::whitesmoke);
    g.fillAll();
    g.setColour(Colours::lightpink);
    g.drawRect(getLocalBounds(), 1.0f);
    g.setColour(Colours::white);
    g.fillPath(*internalPath);
    g.setColour(Colour(0xff6f6f6f));
    g.strokePath(*internalPath, PathStrokeType(5.200f));
}
//
void BrowserComponent::BrowserElement::resized() {

}