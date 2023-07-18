#include "Artist.h"

Artist::Artist() {
}
//
Artist::Artist(String _name, String _portraitImageFileName, String _bioFileName) {
	this->name = _name;
	this->portraitImageFileName = _portraitImageFileName;
	this->bioFileName = _bioFileName;
}
//
Artist::~Artist() {
}
//
void Artist::setName(String _name) {
	this->name = _name;
}
//
void Artist::setPortraitImageFileName(String _portraitImageFileName) {
	this->portraitImageFileName = _portraitImageFileName;
}
//
void Artist::setBioFileName(String _bioFileName) {
	this->bioFileName = _bioFileName;
}
//
String Artist::getName() {
	return this->name;
}
//
String Artist::getPortraitImageFileName() {
	return this->portraitImageFileName;
}
//
String Artist::getBioFileName() {
	return this->bioFileName;
}