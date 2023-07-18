#include "../Include/MainComponent.h"
//
MainComponent::MainComponent(void)
{
    setOpaque(true);
    audioComponent = new AudioComponent();
    playerComponent = new PlayerComponent(audioComponent);
    browserComponent = new BrowserComponent(playerComponent);
    addAndMakeVisible(browserComponent);
    addAndMakeVisible(audioComponent);
    addAndMakeVisible(playerComponent);
    //
    setSize(400, 600);
    playerComponent->startTimer(100);
}
//
MainComponent::~MainComponent(void)
{
    delete(audioComponent);
    delete(playerComponent);
    delete(browserComponent);
}
//
void MainComponent::paint(Graphics& g)
{}
//
void MainComponent::resized(void)
{
    auto area = getLocalBounds();
    playerComponent->setSize(area.getWidth(), area.getHeight());
    browserComponent->setSize(area.getWidth(), area.getHeight());
}