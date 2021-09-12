#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#define MAX_FRAMES  6000

// Codes for LED:
// 101-199: info messages
#define INF_FILE_SUCCESSFUL_WRITTEN 101
#define INF_END_OF_FILE             102
// 201-299: error messages
#define ERR_SD_FAILED             201
#define ERR_READING_FILE          202
#define ERR_WRITING_FILE          203   // error while receiving data
#define ERR_OPEN_FILE_FOR_WRITING 204   // error while receiving data
#define ERR_UNDEFINED             255


#endif