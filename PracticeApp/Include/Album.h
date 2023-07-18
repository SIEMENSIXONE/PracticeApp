#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Song.h"
/**
@brief Класс, представляющий собой абстракцию обекта альбом
@detailed Используется для хранения и передачи информации, относящейся к хранящемуся в библиотеке музыкальном альбоме
*/
class Album 
{
    /**
@brief Возможные музыкальные жанры
*/
    enum Genre
    {
        HipHop,          /**< Хип-Хоп */
        Pop,             /**< Поп */
        Rock,            /**< Рок */
        Alternative,     /**< Альтернатива */
        Electronic,      /**< Электронная */
        Jazz             /**< Джаз */
    };
    //
public:
    /**
@brief Конструктор
*/
    Album();
    /**
@brief Конструктор
@param _name Название альбома
@param _artists Перечень исполнителей
@param _releaseDate Дата выпуска альбома
@param _coverImageFileName Обложка
@param _genre Жанр
@param _songs Перечень песен
*/
    Album(String _name, std::vector<Artist> _artists, String _releaseDate, String _coverImageFileName, Genre _genre, std::vector<Song> _songs);
    /**
@brief Деструктор
*/
    ~Album(void);
    /**
@brief Функция установки названия альбома
@param _name Новое название альбома
*/
    void setName(String _name);
    /**
@brief Функция установки перечня исполнителей
@param _artists Новый перечень исполнителей
*/
    void setArtists(std::vector<Artist> _artists);
    /**
@brief Функция установки даты выпуска музыкального альбома
@param _releaseDate Новая дата выпуска альбома
*/
    void setReleaseDate(String _releaseDate);
    /**
@brief Функция установки обложки альбома
@param _coverImageFileName путь к файлу на диске, содержащего изображение обложки
*/
    void setCoverImageFileName(String _coverImageFileName);
    /**
@brief Функция установки жанра альбома
@param _genre Новый жанр альбома
*/
    void setGenre(Genre _genre);
    /**
@brief Функция установки перечня песен, входящих в состав музыкального альбома
@param _songs Новый перечень песен
*/
    void setSongs(std::vector<Song> _songs);
            /**
@brief Функция для получения названия альбома
@return Название альбома
*/
    String getName();
    /**
@brief Функция для получения перечня исполнителей
@return Перечень исполнителей
*/
    std::vector<Artist> getArtists();
    /**
@brief Функция для получения даты выпуска музыкального альбома
@return Дата выпуска альбома
*/
    String getReleaseDate();
    /**
@brief Функция для получения обложки альбома
@return Пусть к файлу на диске, содержащего изображения обложки
*/
    String getCoverImageFileName();
    /**
@brief Функция для получения жанра альбома
@return Жанр музыкального альбома
*/
    Genre getGenre();
    /**
@brief Функция для получения перечня песен, входящих в альбом
@return Перечень песен
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