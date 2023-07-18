#include "Album.h"

Album::Album() {}
//
Album::Album(String _name, std::vector<Artist> _artists, String _releaseDate, String _coverImageFileName, Genre _genre, std::vector<Song> _songs) {
	this->name = _name;
	this->artists = _artists;
	this->releaseDate = _releaseDate;
	this->coverImageFileName = _coverImageFileName;
	this->genre = _genre;
	this->songs = _songs;
}
//
Album::~Album() {
}
//
void Album::setName(String _name) {
	this->name = _name;
}
//
void Album::setArtists(std::vector<Artist> _artists) {
	this->artists = _artists;
}
//
void Album::setReleaseDate(String _releaseDate) {
	this->releaseDate = _releaseDate;
}
//
void Album::setCoverImageFileName(String _coverImageFileName) {
	this->coverImageFileName = _coverImageFileName;
}
//
void Album::setGenre(Genre _genre) {
	this->genre = _genre;
}
//
void Album::setSongs(std::vector<Song> _songs) {
	this->songs = _songs;
}
//
String Album::getName() {
	return this->name;
}
//
std::vector<Artist> Album::getArtists() {
	return this->artists;
}
//
String Album::getReleaseDate() {
	return this->releaseDate;
}
//
String Album::getCoverImageFileName() {
	return this->coverImageFileName;
}
//
Album::Genre Album::getGenre() {
	return this->genre;
}
//
std::vector<Song> Album::getSongs() {
	return this->songs;
}