#ifndef WRITELICENSE_H
#define WRITELICENSE_H
void writeMITLicense(const int year, const char* owner, const char* filename);
void writeApache2License(const int year, const char* owner, const char* filename);
void writeBSD4License(const int year, const char* owner, const char* filename);
void writeBSD3License(const int year, const char* owner, const char* filename);
void writeBSD2License(const int year, const char* owner, const char* filename);
void writeGPLv3License(const char* filename);
void writeISCLicense(const int year, const char* owner, const char* filename);
#endif