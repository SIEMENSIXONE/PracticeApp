#pragma once
//
#include "../JuceLibraryCode/JuceHeader.h"
/**
@brief �����, ���������� ��������������� �� ������ � �����������
@detailed ����������� �� ������ juce::Component. ����� ��������� � �� ����� ������������ �������������
*/
class AudioComponent : public AudioAppComponent,
    public ChangeListener
{
public:
/**
@brief ��������� ��������� ���������������
*/
    enum TransportState
    {
        Stopped,    /**< ��������������� ����������� */
        Starting,   /**< ������ ��������������� */
        Playing,    /**< ��������������� */
        Pausing,    /**< ������ ���������� ��������������� �� ����� */
        Paused,     /**< ��������������� ���������� �� ����� */
        Stopping    /**< ������ ��������� ��������������� */
    };
    /**
@brief �����������
*/
    AudioComponent(void);
    /**
@brief ����������
*/
    ~AudioComponent(void) override;
    /**
@brief ������� ���������
*/
    void paint(Graphics&) override;
    /**
@brief ������� ��������� �������
*/
    void resized(void) override;
    /**
@brief ���������������� ������� changeListenerCallback(ChangeBroadcaster* source) �� ChangeListener
*/
    void changeListenerCallback(ChangeBroadcaster* source) override;
    /**
@brief ���������������� ������� getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) �� AudioAppComponent
*/
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    /**
@brief ���������������� ������� prepareToPlay(int samplesPerBlockExpected, double sampleRate) �� AudioAppComponent
*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    /**
@brief ���������������� ������� releaseResources() �� AudioAppComponent
*/
    void releaseResources() override;
    //
        /**
@brief ������� ��� ��������� �������� ������� ��������� ���������������
@return ������� ������ ��������� ���������������
*/
    TransportState getState();
    /**
@brief ������� ��� ��������� �������� ������� ��������� ���������������
@param newState ����� ������
*/
    void changeState(TransportState newState);
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ���������������
*/
    void transportStop();
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ������ ���������������
*/
    void transportStart();
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ���������
*/
    void transportSetGain(float _gain);
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ������� ������� �� ������������
@return ������� ������� ��������������� � ��������
*/
    double transportGetCurrentPosition();
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ������� ��������������� �� ������������
@param position ����� ������� � ��������
*/
    void transportSetPosition(double position);
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ��������� ���������������
@param _positionableSource ��������
@param _sampleRate ���������
*/
    void transportSetSource(PositionableAudioSource* _positionableSource, double _sampleRate);
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ����� ����� ������������
@return ����� ������������ � ��������
*/
    double transportGetLengthInSeconds();
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ������� ��������� ��������������� �� ������� ����� ����������
@return ����������� �� ��������������� ����������
*/
    bool getTransportSourceFinishStatus();
    /**
@brief ������� ��� ������� ��������������� � AudioTransportSource �����. ��������� ��������� ����������
@param _newSource ����� �������� ��� ������
*/
    void readerSourceReset(AudioFormatReaderSource* _newSource);
    //
private:
    TransportState state;
    //
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    PositionableAudioSource* positionableSource;
    //
    Path internalPath1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioComponent)
};