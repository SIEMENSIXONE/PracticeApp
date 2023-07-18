#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Artist.h"
/**
@brief Класс, представляющий собой абстракцию обекта песня
@detailed Используется для хранения и передачи информации, относящейся к хранящейся в библиотеке песне
*/
class Song 
{
public:
    /**
@brief Конструктор
*/
    Song();
    /**
@brief Конструктор
@param _name Название песни
@param _artists Перечень исполнителей
@param _guestArtists Перечень исполнителей-гостей
@param _audioFileName Путь к аудиофайлу
@param _lyricsFileName Путь к файлу с текстом песни
*/
    Song(String _name, std::vector<Artist> _artists, std::vector<Artist> _guestArtists, String _audioFileName, String _lyricsFileName);
    /**
@brief Деструктор
*/
    ~Song(void);
    /**
@brief Функция установки названия песни
@param _name Название песни
*/
    void setName(String _name);
    /**
@brief Функция установки аудиофайла
@param _audioFileName Путь к аудиофайлу
*/
    void setAudioFileName(String _audioFileName);
    /**
@brief Функция установки файла с текстом песни
@param _lyricsFileName Путь к файлу с текстом песни
*/
    void setLyricsFileName(String _lyricsFileName);
    /**
@brief Функция установки перечня исполнителей
@param _artists Перечень исполнителей
*/
    void setArtists(std::vector<Artist> _artists);
    /**
@brief Функция установки перечня исполнителей-гостей
@param _guestArtists Перечень исполнителей-гостей
*/
    void setGuestArtists(std::vector<Artist> _guestArtists);
    /**
@brief Функция получения названия песни
@return Название песни
*/
    String getName();
    /**
@brief Функция получения аудио файла
@return Путь к аудиофайлу
*/
    String getAudioFileName();
    /**
@brief Функция получения файла с текстом песни
@return Путь к файлу с текстом песни
*/
    String getLyricsFileName();
    /**
@brief Функция получения перечня исполнителей
@return Перечень исполнителей
*/
    std::vector<Artist> getArtists();
    /**
@brief Функция получения перечня исполнителей-гостей
@return Перечень исполнителей-гостей
*/
    std::vector<Artist> getGuestArtists();
    /**
@brief Функция добавления исполнителя в перечень исполнителей
@param _artist Новый исполнитель
*/
    void addArtist(Artist _artist);
    /**
@brief Функция добавления исполнителя-гостя в перечень исполнителей-гостей
@param _guestArtist Новый исполнитель-гость
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