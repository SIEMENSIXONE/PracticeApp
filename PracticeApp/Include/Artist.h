#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
/**
@brief �����, �������������� ����� ���������� ������ �����������
@detailed ������������ ��� �������� � �������� ����������, ����������� � ������� ����������� �� ������ ������������
*/
class Artist 
{
public:
    /**
@brief �����������
*/
    Artist();
    /**
@brief �����������
@param _name ��� �����������
@param _portraitImageFileName ������� �����������
@param _bioFileName ��������� �����������
*/
    Artist(String _name, String _portraitImageFileName, String _bioFileName);
    /**
@brief ����������
*/
    ~Artist(void);
    /**
@brief ������� ��������� ����� �����������
@param _name ����� ��� �����������
*/
    void setName(String _name);
    /**
@brief ������� ��������� �������� �����������
@param _portraitImageFileName ���� � ����� �� �����, ����������� ����������� �������� �����������
*/
    void setPortraitImageFileName(String _portraitImageFileName);
    /**
@brief ������� ��������� ��������� �����������
@param _bioFileName ���� � ����� �� �����, ����������� ���������� � ��������� �������
*/
    void setBioFileName(String _bioFileName);
    /**
@brief ������� ��� ��������� ����� �����������
@return ��� �����������
*/
    String getName();
    /**
@brief ������� ��� ��������� �������� �����������
@return ���� � ����� �� �����, ����������� ����������� �������� �����������
*/
    String getPortraitImageFileName();
    /**
@brief ������� ��� ��������� ��������� �����������
@return ���� � ����� �� �����, ����������� ���������� � ��������� �������
*/
    String getBioFileName();
private:
    String name = "Artist Name";
    String portraitImageFileName;
    String bioFileName;
};