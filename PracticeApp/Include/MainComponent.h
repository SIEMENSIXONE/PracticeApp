#pragma once
//
#include "../Include/PlayerComponent.h"
#include "../Include/BrowserComponent.h"
/**
@brief �����, ���������� �� ���������� MainFrame
@detailed ����������� �� ������ juce::Component. ������� �����, ���������� �� ���� ���������� ����������
*/
class MainComponent : public Component
{
public:
    /**
@brief �����������
*/
    MainComponent(void);
    /**
@brief ����������
*/
    ~MainComponent(void) override;
    /**
@brief ������� ���������
*/
    void paint(Graphics&) override;
    /**
@brief ������� ��������� �������
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