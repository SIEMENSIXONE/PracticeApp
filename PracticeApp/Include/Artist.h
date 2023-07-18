#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
/**
@brief Класс, представляющий собой абстракцию обекта исполнитель
@detailed Используется для хранения и передачи информации, относящейся к каждому исполнителю из списка исполнителей
*/
class Artist 
{
public:
    /**
@brief Конструктор
*/
    Artist();
    /**
@brief Конструктор
@param _name Имя исполнителя
@param _portraitImageFileName Портрет исполнителя
@param _bioFileName Биография исполнителя
*/
    Artist(String _name, String _portraitImageFileName, String _bioFileName);
    /**
@brief Деструктор
*/
    ~Artist(void);
    /**
@brief Функция установки имени исполнителя
@param _name Новое имя исполнителя
*/
    void setName(String _name);
    /**
@brief Функция установки портрета исполнителя
@param _portraitImageFileName Путь к файлу на диске, содержащему изображение портрета исполнителя
*/
    void setPortraitImageFileName(String _portraitImageFileName);
    /**
@brief Функция установки биографии исполнителя
@param _bioFileName Путь к файлу на диске, содержащему информацию о биографии артиста
*/
    void setBioFileName(String _bioFileName);
    /**
@brief Функция для получения имени исполнителя
@return Имя исполнителя
*/
    String getName();
    /**
@brief Функция для получения портрета исполнителя
@return Путь к файлу на диске, содержащему изображение портрета исполнителя
*/
    String getPortraitImageFileName();
    /**
@brief Функция для получения биографии исполнителя
@return Путь к файлу на диске, содержащему информацию о биографии артиста
*/
    String getBioFileName();
private:
    String name = "Artist Name";
    String portraitImageFileName;
    String bioFileName;
};