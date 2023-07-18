#include "Song.h"

Song::Song() {}
//
Song::Song(String _name, std::vector<Artist> _artists, std::vector<Artist> _guestArtists, String _audioFileName, String _lyricsFileName) {
    this->name = _name;
    this->artists = _artists;
    this->guestArtists = _guestArtists;
    this->audioFileName = _audioFileName;
    this->lyricsFileName = _lyricsFileName;
}
//
Song::~Song() {
}
//
void Song::setName(String _name) {
    this->name = _name;
}
//
void Song::setAudioFileName(String _audioFileName) {
    this->audioFileName = _audioFileName;
}
//
void Song::setLyricsFileName(String _lyricsFileName) {
    this->lyricsFileName = _lyricsFileName;
}
//
void Song::setArtists(std::vector<Artist> _artists) {
    this->artists = _artists;
}
//
void Song::setGuestArtists(std::vector<Artist> _guestArtists) {
    this->guestArtists = _guestArtists;
}
//
String Song::getName() {
    return this->name;
}
//
String Song::getAudioFileName() {
    return this->audioFileName;
}
//
String Song::getLyricsFileName() {
    return this->lyricsFileName;
}
//
std::vector<Artist> Song::getArtists() {
    return this->artists;
}
//
std::vector<Artist> Song::getGuestArtists() {
    return this->guestArtists;
}
//
void Song::addArtist(Artist _artist) {
    this->artists.push_back(_artist);
}
//
void Song::addGuestArtist(Artist _guestArtist) {
    this->guestArtists.push_back(_guestArtist);
}