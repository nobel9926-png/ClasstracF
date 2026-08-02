//-------------------------------storage.c

#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//---------------------------------------------------------------------------------------
void Storage_Init(void) {
    if (!DirectoryExists(RECORDS_DIR)) {
        MakeDirectory(RECORDS_DIR);
    }
    // records folder xa ki nai check garxa , xaina vane banaidinxa
}
//-------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// yo function le current attendance lai CSV report file ma save garxa
bool Storage_SaveAttendance(const char *subjectName, Student *students, int studentCount) {
    char safeSubject[32];
    // subject name lai safe filename banauna temporary variable banako 

    strncpy(safeSubject, subjectName, sizeof(safeSubject) - 1);
    // subject name copy garxa

    safeSubject[sizeof(safeSubject) - 1] = '\0';
    // string lai  properly end garxa

    for (int i = 0; safeSubject[i] != '\0'; i++) {
        //yesle subject name ko harek character check garxa

        if (safeSubject[i] == ' ')
            safeSubject[i] = '_';
        // subject name ma space xa vane underscore ma replace garxa jastai ICT_101
    }

    time_t now = time(NULL);
    // current system time linxa, csv file name ma halna 

    struct tm *t = localtime(&now);
    // current time lai year, month, date, hour jasta parts ma split garxa

    char filename[256];
    // final CSV filename store garna variable banako yo 

    snprintf(filename, sizeof(filename), "%s/%s_%04d-%02d-%02d_%02d-%02d-%02d.csv",
             RECORDS_DIR, safeSubject,
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);
    // subject name ra current date/time use garera unique filename banaunxa

    FILE *f = fopen(filename, "w");
    // write mode ma naya CSV file create/open garxa

    if (f == NULL) return false;
    // file open garna milena vane false return garxa yesle 

    fprintf(f, "Roll No,Name,Status\n");
    // CSV ko first header line lekhxa

    for (int i = 0; i < studentCount; i++) {
        // sabai students euta euta gari process garxa loop le

        const char *statusText = "None";
        // default attendance status None rakhxa

        if (students[i].status == ST_PRESENT)
            statusText = "Present";
        // student present xa vane Present set garxa

        else if (students[i].status == ST_ABSENT)
            statusText = "Absent";
        // likewise student absent xa vane Absent set garxa

        else if (students[i].status == ST_LATE)
            statusText = "Late";
        // student late xa vane Late set garxa

        fprintf(f, "%s,%s,%s\n",
                students[i].rollNo,
                students[i].name,
                statusText);
        // student ko Roll No, Name ra Status CSV file ma save garxa
    }

    fclose(f);
    // file save garera close gardinxa

    return true;
    // attendance successfully save vayo vanera true return garxa last ma 
}
//-------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// yo function le filenames lai newest bata oldest order ma sort garna compare garxa
static int CompareNewestFirst(const void *a, const void *b) {

    const char *fileA = (const char *)a;
    // first filename lai char pointer ma convert garxa

    const char *fileB = (const char *)b;
    // ani second filename lai char pointer ma convert garxa

    return strcmp(fileB, fileA);
    // reverse order ma compare garera newest filename lai agadi rakhdinxa
}
//----------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// yo function le records folder vitra vako sabai CSV reports ko naam read garxa
int Storage_ListReports(char files[][256], int maxFiles) {

    FilePathList list = LoadDirectoryFiles(RECORDS_DIR);
    // records folder vitra vako sabai files ko list load garxa paila 
     int count = 0;
    // ahile samma kati ota CSV files vetiyo vanera count garxa

    for (unsigned int i = 0; i < list.count && count < maxFiles; i++) {
        // folder vitra ko harek file euta euta gari check garxa

        const char *path = list.paths[i];
        // current file ko full path linxa
        int len = strlen(path);
        // current filename ko length calculate garxa

        if (len > 4 && strcmp(path + len - 4, ".csv") == 0) {
            // file ko extension .csv ho ki haina check garxa

            strncpy(files[count], GetFileName(path), 255);
            // filename matra files array ma copy garxa

            files[count][255] = '\0';
            // string properly end garxa

            count++;
            // CSV file count badhaunxa
        }
    }
    UnloadDirectoryFiles(list);
    // load gareko file list ko memory free garxa ani 

    qsort(files, count, 256, CompareNewestFirst);
    // filenames lai newest bata oldest order ma sort garxa
    return count;
    // last ma total kati ota CSV reports vetiyo tyo return garxa
}
//-------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// aba yo function le selected report file records folder bata delete garxa
bool Storage_DeleteReport(const char *filename) {

    char fullPath[300];
    // report file ko full path store garna variable ho yo 

    snprintf(fullPath, sizeof(fullPath), "%s/%s", RECORDS_DIR, filename);
    // records folder ra filename milaera full path banaunxa

    return remove(fullPath) == 0;
    // file delete garxa, ani successful vayo vane true return garxa
}
//---------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// yo function le selected CSV report read garera sabai lines array ma save garxa
int Storage_ReadReport(const char *filename, char lines[][256], int maxLines) {
    char fullPath[300];
    // report file ko full path store garna variable
    snprintf(fullPath, sizeof(fullPath), "%s/%s", RECORDS_DIR, filename);
    // records folder ra filename milaera full path banaunxa

    FILE *f = fopen(fullPath, "r");
    // report file read mode ma open garxa

    if (f == NULL) return 0;
    // file open garna milena vane 0 return gardinxa

    int count = 0;
    // kati ota lines read vayo vanera count garni vayo 
    while (count < maxLines && fgets(lines[count], 256, f) != NULL) {
        // file ko harek line read garera array ma save garxa

        int len = strlen(lines[count]);
        // current line ko length calculate garxa

        if (len > 0 && lines[count][len - 1] == '\n')
            lines[count][len - 1] = '\0';
        // fgets le rakheko newline character hatauxa

        count++;
        // line count badhaunxa
    }
    fclose(f);
    // file close garxa
    return count;
    // total kati lines read vayo tyo return garxa
}
//---------------------------------------------------------------------------------------