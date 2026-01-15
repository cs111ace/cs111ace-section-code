/*
 * cs111ace-section-code/1-welcome-and-filesystems/cs111_inode.cpp
 *
 * Definition of the Unix V6 inode structure used in CS111 at Stanford University.
 *
 * Date: 01/2026
 */

#include <stdint.h>

struct inode {
    uint16_t    i_mode;     // bit vector of file type and permission
    uint8_t     i_nlink;    //number of references to file
    uint8_t     i_uid;      // owner
    uint8_t     i_gid;      // group of owner
    uint16_t    i_size0;    // most significant byte of size

    uint16_t    i_size1;    // lower two bytes of size
                            //(size is encoded in a three-byte number)


    uint16_t    i_addr[8];  // device addresses
                            // constituting file
    uint16_t    i_atime[2]; // access time
    uint16_t    i_mtime[2]; // modify time

};
