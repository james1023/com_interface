/*
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//       Copyright(c) 2003-2009 Intel Corporation. All Rights Reserved.
//
*/
/*
 * VM 64-bits buffered file operations library
 *       common implementation
 */
#include "vm_file.h"
#if defined(LINUX32) || defined(OSX)
# define SLASH '/'
#else
# define SLASH '\\'
# if _MSC_VER >= 1400
#   pragma warning( disable:4996 )
# endif
#endif
/*
 * file name manipulations */
/*
 * return only path of file name */
void vm_file_getpath(vm_char *filename, vm_char *path, int nchars) {
	/* go to end of line and then move up until first SLASH will be found */
	size_t len;
	path[0] = '\0';
	len = vm_string_strlen(filename);
	while(len && (filename[len--] != SLASH));
	if (len) {
		memcpy((void *)path, (const void *)filename, (len <= (size_t)nchars) ? len+1 : nchars);
		path[len+1] = '\0';
	}
}

/*
 * return base file name free of path and all suffixes
 */
void vm_file_getbasename(vm_char *filename, vm_char *base, int nchars) {
  Ipp32s chrs = 0;
  vm_char *p, *q0, *q1, *s;
  base[0] = '\0';
  q0 = q1 = NULL;
  p = vm_string_strchr(filename, '.'); // first invocation of .
  s = filename;
  do {
    q0 = vm_string_strchr(s, SLASH);
    if (q0 != NULL) {
      q1 = q0;
      s = q0+1;
      }
    } while( q0 != NULL );
  if (p == NULL)
    p = &filename[vm_string_strlen(filename)];
  if ( q1 == NULL )
    q1 = filename;
  chrs = (Ipp32s)(p - q1);
  if (chrs) {
    if (q1[0] == SLASH) {
      ++q1;
      --chrs;
      }
    if (chrs > nchars)
      chrs = nchars-1;
    memcpy((void *)base, (const void *)q1, chrs);
    base[chrs] = '\0';
    }
  }
/*
 * return full file suffix or nchars of suffix if nchars is to small to fit the suffix
 * !!! if more then one suffix applied then only first from the end of filename will be found
 */
void vm_file_getsuffix(vm_char *filename, vm_char *suffix, int nchars) {
  /* go to end of line and then go up until we will meet the suffix sign . or
   * to beginning of line if no suffix found */
  size_t len, i = 0;
  len = vm_string_strlen(filename);
  suffix[0] = '\0';
  while(len && (filename[len--] != '.'));
  if (len) {
    len += 2;
    for( ; filename[len]; ++len) {
      suffix[i] = filename[len];
      if (++i >= (size_t)nchars)
        break;
      }
    suffix[i] = '\0';
    }
  }

#define ADDPARM(A)                    \
  if ((Ipp32u)nchars > (Ipp32u)vm_string_strlen(A)) {   \
    vm_string_strcat(filename, A);              \
    offs = (Ipp32u)vm_string_strlen(filename);          \
    nchars -= offs;                   \
    if (nchars)                       \
      filename[offs] = SLASH;         \
    ++offs;                           \
    --nchars;                         \
    filename[offs] = '\0';            \
    }
/*
 * prepare complex file name according with OS rules:
 *    / delimiter for unix and \ delimiter for Windows */
void vm_file_makefilename(vm_char *path, vm_char *base, vm_char *suffix, vm_char *filename, int nchars) {
  Ipp32u offs = 0;
  filename[0] = '\0';
  if ((path != NULL) && (vm_string_strlen(path) < (size_t)nchars))
    ADDPARM(path)
  if (nchars && (base != NULL))
    ADDPARM(base)
    if (nchars && (suffix != NULL)) {
      if (offs == 0) {
        filename[offs++] = '.';
        filename[offs] = '\0';
        --nchars;
        }
      else
        if (filename[offs-1] == SLASH)
          filename[offs-1] = '.';
      ADDPARM(suffix)
      }
    /* remove SLASH if exist */
    if (filename[offs-1] == SLASH)
      filename[offs-1] = '\0';
  }

// james: add vm_dir_peek.
int vm_dir_peek(vm_char *file_path, vm_char *peek_case, _listPeekFile &listFile)
{
	int ret = 0;
	vm_dir *pDirEntry = NULL;
	Ipp32u file_attr = 0;
	char *pchTemp;
	string file_case;
	int last = 0;

	do 
	{
		pchTemp = (char *)malloc(MAX_PATH);

		file_case = file_path;
		if (peek_case)
			file_case += peek_case;
		//DEBUG_TRACE(AVC_DBG, ("#%d vm_dir_peek: file_case=%s. \n", __LINE__, file_case.c_str()));
		ret = vm_dir_open(&pDirEntry, (vm_char *)file_case.c_str(), pchTemp);
		if (0 == ret) {
			break;
		}
		//DEBUG_TRACE(AVC_DBG, ("#%d vm_dir_peek: pchTemp=%s. \n", __LINE__, pchTemp));
#if defined(_WIN32)
		vm_file_getinfo(pchTemp, NULL, &file_attr);
		last = strlen(pchTemp);
		if (last < 3)
			break;
		if (pchTemp[last-1] != '.' && pchTemp[last-2] != '.') {
			if (file_attr&VM_FILE_ATTR_DIRECTORY) {
				strcat(pchTemp, "\\");
				vm_dir_peek(pchTemp, peek_case, listFile);
			}
			else {
				listFile.push_back(pchTemp);
			}
		}
#endif

		while(1 == (ret=vm_dir_read(pDirEntry, pchTemp, MAX_PATH))) {
			file_attr = 0;
			vm_file_getinfo(pchTemp, NULL, &file_attr);
			//DEBUG_TRACE(AVC_DBG, ("#%d vm_dir_peek: vm_dir_read, pchTemp=%s, file_attr=%d. \n", __LINE__, pchTemp, file_attr));
#if defined(_WIN32)
			last = strlen(pchTemp);
			if (last < 3)
				break;
			if (pchTemp[last-1] != '.' && pchTemp[last-2] != '.') {
				if (file_attr&VM_FILE_ATTR_DIRECTORY) {
					strcat(pchTemp, "\\");
					vm_dir_peek(pchTemp, peek_case, listFile);
				}
				else {
					listFile.push_back(pchTemp);
				}
			}
#else
			if (NULL == strstr(pchTemp, "/.") && NULL == strstr(pchTemp, "/..")) {
				if (file_attr&VM_FILE_ATTR_DIRECTORY) {
					strcat(pchTemp, "/");
					vm_dir_peek(pchTemp, peek_case, listFile);
				}
				else {
					listFile.push_back(pchTemp);
				}
			}
#endif
		}
	} while (0);
	vm_dir_close(pDirEntry);
	if (pchTemp) { free(pchTemp); pchTemp = NULL; }

	return ret;
}

