#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Artist.h"
/**
@brief �����, �������������� ����� ���������� ������ �����
@detailed ������������ ��� �������� � �������� ����������, ����������� � ���������� � ���������� �����
*/
class Song 
{
public:
    /**
@brief �����������
*/
    Song();
    /**
@brief �����������
@param _name �������� �����
@param _artists �������� ������������
@param _guestArtists �������� ������������-������
@param _audioFileName ���� � ����������
@param _lyricsFileName ���� � ����� � ������� �����
*/
    Song(String _name, std::vector<Artist> _artists, std::vector<Artist> _guestArtists, String _audioFileName, String _lyricsFileName);
    /**
@brief ����������
*/
    ~Song(void);
    /**
@brief ������� ��������� �������� �����
@param _name �������� �����
*/
    void setName(String _name);
    /**
@brief ������� ��������� ����������
@param _audioFileName ���� � ����������
*/
    void setAudioFileName(String _audioFileName);
    /**
@brief ������� ��������� ����� � ������� �����
@param _lyricsFileName ���� � ����� � ������� �����
*/
    void setLyricsFileName(String _lyricsFileName);
    /**
@brief ������� ��������� ������� ������������
@param _artists �������� ������������
*/
    void setArtists(std::vector<Artist> _artists);
    /**
@brief ������� ��������� ������� ������������-������
@param _guestArtists �������� ������������-������
*/
    void setGuestArtists(std::vector<Artist> _guestArtists);
    /**
@brief ������� ��������� �������� �����
@return �������� �����
*/
    String getName();
    /**
@brief ������� ��������� ����� �����
@return ���� � ����������
*/
    String getAudioFileName();
    /**
@brief ������� ��������� ����� � ������� �����
@return ���� � ����� � ������� �����
*/
    String getLyricsFileName();
    /**
@brief ������� ��������� ������� ������������
@return �������� ������������
*/
    std::vector<Artist> getArtists();
    /**
@brief ������� ��������� ������� ������������-������
@return �������� ������������-������
*/
    std::vector<Artist> getGuestArtists();
    /**
@brief ������� ���������� ����������� � �������� ������������
@param _artist ����� �����������
*/
    void addArtist(Artist _artist);
    /**
@brief ������� ���������� �����������-����� � �������� ������������-������
@param _guestArtist ����� �����������-�����
*/
    void addGuestArtist(Artist _guestArtist);
private:
    String name;
    std::vector<Artist> artists;
    std::vector<Artist> guestArtists;
    String audioFileName;
    String lyricsFileName;
    int albumId;
};