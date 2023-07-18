#include "../Include/AudioComponent.h"
#include "Album.h"
//
AudioComponent::AudioComponent(void)
    : state(Stopped)
{
    transportSource.addChangeListener(this);
    setAudioChannels(0, 2);
}
//
AudioComponent::~AudioComponent(void)
{
    transportSource.removeChangeListener(this);
    shutdownAudio();
    releaseResources();
}
//
void AudioComponent::paint(Graphics& g)
{}
//
void AudioComponent::resized(void)
{}
//
void AudioComponent::changeState(TransportState newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
        case Stopped:
            transportSource.setPosition(0.0);
            break;
            //
        case Starting:
            transportSource.start();
            break;
            //
        case Playing: 
            break;
            //
        case Pausing:
            transportSource.stop();
            break;
            //
        case Paused:
            break;
            //
        case Stopping:
            transportSource.stop();
            break;
        }
    }
}
//
void AudioComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState(Playing);
        else if ((state == Stopping) || (state == Playing))
            changeState(Stopped);
        else if (Pausing == state)
            changeState(Paused);
    }
}
//
void AudioComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    transportSource.getNextAudioBlock(bufferToFill);

}
//
void AudioComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
//
void AudioComponent::releaseResources()
{
    transportSource.releaseResources();
}
//
void AudioComponent::transportStop() {
    transportSource.stop();
}
//
void AudioComponent::transportStart() {
    transportSource.start();
}
//
void AudioComponent::transportSetGain(float _gain) {
    transportSource.setGain(_gain);
}
//
double AudioComponent::transportGetCurrentPosition() {
    return transportSource.getCurrentPosition();
}
//
AudioComponent::TransportState AudioComponent::getState() {
    return state;
}
//
void AudioComponent::transportSetPosition(double position) {
    transportSource.setPosition(position);
}
//
void AudioComponent::transportSetSource(PositionableAudioSource* _positionableSource, double _sampleRate) {
    transportSource.setSource(_positionableSource, 0, nullptr, _sampleRate);
}
//
void AudioComponent::readerSourceReset(AudioFormatReaderSource* _newSource) {
    readerSource.reset(_newSource);
}
//
double AudioComponent::transportGetLengthInSeconds() {
    return transportSource.getLengthInSeconds();
}
//
bool AudioComponent::getTransportSourceFinishStatus() {
    if (transportSource.getTotalLength() != 0) {
        if (transportSource.getCurrentPosition() >= transportSource.getLengthInSeconds() - 0.1) return true;
    }
    return false;
}
