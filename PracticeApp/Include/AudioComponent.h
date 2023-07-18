#pragma once
//
#include "../JuceLibraryCode/JuceHeader.h"
/**
@brief Класс, отвечающий непосредственно за работу с аудиофайлом
@detailed Унаследован от класса juce::Component. Класс служебный и не имеет графического представления
*/
class AudioComponent : public AudioAppComponent,
    public ChangeListener
{
public:
/**
@brief Состояния источника воспроизведения
*/
    enum TransportState
    {
        Stopped,    /**< Воспроизведение остановлено */
        Starting,   /**< Начало воспроизведения */
        Playing,    /**< Воспроизведение */
        Pausing,    /**< Начало постановки воспроизведения на паузу */
        Paused,     /**< Воспроизведение поставлено на паузу */
        Stopping    /**< Начало остановки воспроизведения */
    };
    /**
@brief Конструктор
*/
    AudioComponent(void);
    /**
@brief Деструктор
*/
    ~AudioComponent(void) override;
    /**
@brief Функция отрисовки
*/
    void paint(Graphics&) override;
    /**
@brief Функция изменения размера
*/
    void resized(void) override;
    /**
@brief Переопределенная функция changeListenerCallback(ChangeBroadcaster* source) из ChangeListener
*/
    void changeListenerCallback(ChangeBroadcaster* source) override;
    /**
@brief Переопределенная функция getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) из AudioAppComponent
*/
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    /**
@brief Переопределенная функция prepareToPlay(int samplesPerBlockExpected, double sampleRate) из AudioAppComponent
*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    /**
@brief Переопределенная функция releaseResources() из AudioAppComponent
*/
    void releaseResources() override;
    //
        /**
@brief Функция для получения текущего статуса источника воспроизведения
@return Текущий статус источника воспроизведения
*/
    TransportState getState();
    /**
@brief Функция для изменения текущего статуса источника воспроизведения
@param newState Новый статус
*/
    void changeState(TransportState newState);
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Остановка воспроизведения
*/
    void transportStop();
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Начало воспроизведения
*/
    void transportStart();
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Установка громкости
*/
    void transportSetGain(float _gain);
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Получение текущей позиции на аудиодорожке
@return Текущая позиция воспроизведения в секундах
*/
    double transportGetCurrentPosition();
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Установка позиции воспроизведения на аудиодорожке
@param position Новая позиция в секундах
*/
    void transportSetPosition(double position);
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Установка источника воспроизведения
@param _positionableSource Источник
@param _sampleRate сэмплрейт
*/
    void transportSetSource(PositionableAudioSource* _positionableSource, double _sampleRate);
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Получение общей длины аудиодорожки
@return Длина аудиодорожки в секундах
*/
    double transportGetLengthInSeconds();
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Получение статуса окончания воспроизведения по причине конца аудиофайла
@return Закончилось ли воспроизведение аудиофайла
*/
    bool getTransportSourceFinishStatus();
    /**
@brief Функция для доступа непосредственно к AudioTransportSource извне. Установка источника считывания
@param _newSource Новый источник для чтения
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