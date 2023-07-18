#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Song.h"
/**
@brief �����, �������������� ����� ���������� ������ ������
@detailed ������������ ��� �������� � �������� ����������, ����������� � ����������� � ���������� ����������� �������
*/
class Album 
{
    /**
@brief ��������� ����������� �����
*/
    enum Genre
    {
        HipHop,          /**< ���-��� */
        Pop,             /**< ��� */
        Rock,            /**< ��� */
        Alternative,     /**< ������������ */
        Electronic,      /**< ����������� */
        Jazz             /**< ���� */
    };
    //
public:
    /**
@brief �����������
*/
    Album();
    /**
@brief �����������
@param _name �������� �������
@param _artists �������� ������������
@param _releaseDate ���� ������� �������
@param _coverImageFileName �������
@param _genre ����
@param _songs �������� �����
*/
    Album(String _name, std::vector<Artist> _artists, String _releaseDate, String _coverImageFileName, Genre _genre, std::vector<Song> _songs);
    /**
@brief ����������
*/
    ~Album(void);
    /**
@brief ������� ��������� �������� �������
@param _name ����� �������� �������
*/
    void setName(String _name);
    /**
@brief ������� ��������� ������� ������������
@param _artists ����� �������� ������������
*/
    void setArtists(std::vector<Artist> _artists);
    /**
@brief ������� ��������� ���� ������� ������������ �������
@param _releaseDate ����� ���� ������� �������
*/
    void setReleaseDate(String _releaseDate);
    /**
@brief ������� ��������� ������� �������
@param _coverImageFileName ���� � ����� �� �����, ����������� ����������� �������
*/
    void setCoverImageFileName(String _coverImageFileName);
    /**
@brief ������� ��������� ����� �������
@param _genre ����� ���� �������
*/
    void setGenre(Genre _genre);
    /**
@brief ������� ��������� ������� �����, �������� � ������ ������������ �������
@param _songs ����� �������� �����
*/
    void setSongs(std::vector<Song> _songs);
            /**
@brief ������� ��� ��������� �������� �������
@return �������� �������
*/
    String getName();
    /**
@brief ������� ��� ��������� ������� ������������
@return �������� ������������
*/
    std::vector<Artist> getArtists();
    /**
@brief ������� ��� ��������� ���� ������� ������������ �������
@return ���� ������� �������
*/
    String getReleaseDate();
    /**
@brief ������� ��� ��������� ������� �������
@return ����� � ����� �� �����, ����������� ����������� �������
*/
    String getCoverImageFileName();
    /**
@brief ������� ��� ��������� ����� �������
@return ���� ������������ �������
*/
    Genre getGenre();
    /**
@brief ������� ��� ��������� ������� �����, �������� � ������
@return �������� �����
*/
    std::vector<Song> getSongs();
private:
    String name;
    std::vector<Artist> artists;
    String releaseDate; //!!!
    String coverImageFileName;
    Genre genre;
    std::vector<Song> songs;
    int albumId;
};