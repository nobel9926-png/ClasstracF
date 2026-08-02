
#ifndef STORAGE_H
#define STORAGE_H

#include "classtrac.h"


void Storage_Init(void);
//yo function le program start huda records/ folder xa ki xaina check garxa
// folder xaina vane naya records folder create garxa


bool Storage_SaveAttendance(const char *subjectName, Student *students, int studentCount);
// yo function le current attendance lai CSV file ma save garxa
// filename subject, date ra time use garera banaunxa
// save successful vayo vane true return garxa


int Storage_ListReports(char files[][256], int maxFiles);
// this function records folder vitra vako sabai CSV reports ko naam read garxa
// report names files array ma save garxa ra total file count return garxa


int Storage_ReadReport(const char *filename, char lines[][256], int maxLines);
// yo function le selected CSV report file read garera sabai lines array ma save garxa
// total kati lines read vayo tyo return garxa


bool Storage_DeleteReport(const char *filename);
// selected report file records folder bata delete garxa
// delete successful vayo vane true return garxa


#endif 