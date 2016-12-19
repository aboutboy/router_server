/*
 * =============================================================================
 *
 *       Filename:  scan_task.h
 *
 *    Description:  handle scanning disk.
 *
 *        Version:  1.0
 *        Created:  2015/9/24 15:08:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Oliver ()
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef _SEARCH_TASK_H_
#define _SEARCH_TASK_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <pthread.h>
#include "base.h"

#define SEARCH_TASK_TCP

#define SEND_LIST_INFO_MIN		10
#define SEND_LIST_INFO_MAX 		20
#define SEND_ERROR_TIMES_MAX 	100	
#define SEND_LIST_INFO_TIME		3 	//s

typedef struct file_search_info{
	struct conn *c;
	int sock;
    int cmd;
	char *search_path;
    char *search_string;
    char session[32];
    unsigned int *flags;
    unsigned seq;
	unsigned search_seq;
	char ip[32];
	int port;
	char disk_uuid[64];
	int client_fd;
	struct sockaddr_in clientAddr;
	long cur_time;
	long record_time;
	int status;
	int statusCode;
	int recvStatusCode;
	unsigned nfiles;
	unsigned cur_nfiles;//��ǰ���������ļ�����
	unsigned list_nfiles;//��ǰ�ļ�������ļ�����
	unsigned send_nfiles;//�����ļ�������ļ�����
	int currentOnly;
}file_search_info_t;


//data collection of file list querying
typedef struct{
	struct dl_list head; //list head for result
	uint32_t listCount;    //list count
	pthread_mutex_t mutex;
}search_manage_list_t;

typedef struct{
	struct dl_list head; //list head for result
	unsigned seq;
	int client_fd;
	struct sockaddr_in clientAddr;
	char ip[32];
	int port;
	int searchStatus;
	int statusCode;
	int recvStatusCode;
	unsigned curNfiles;//��ǰ���������ļ�����
	unsigned listNfiles;//��ǰ�ļ�������ļ�����
	struct dl_list next;
}search_manage_info_t;


#define MAX_MIME_TYPE_SIZE     32

typedef struct{
	off_t file_size;//�ļ���С
	unsigned create_time;//����ʱ��
	unsigned modify_time;//�޸�ʱ��
	unsigned access_time;
	char isFolder;//�Ƿ���Ŀ¼�ļ�
	char *name;	//�ļ���
	char *dir;
	char *path;   //name
	char *path_escape;
	char mime_type[MAX_MIME_TYPE_SIZE];
	int  file_type;		   // see file_type_t
	uint8_t  file_state;
	char file_uuid[64];
	uint32_t file_count;
	struct dl_list next;
}search_file_info_t;

void search_inotify_func(void *self);

void search_manage_task_func();


#ifdef __cplusplus
}
#endif


#endif
