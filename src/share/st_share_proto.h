#ifndef __ST_SHARE_PROTO_H__
#define __ST_SHARE_PROTO_H__

#include <iostream>
#include <string>

namespace share
{

// dec = decapsulation
class share_dec_proto
{
    std::string download_dirrent;

public:
    share_dec_proto(const std::string &dir);
    ~share_dec_proto();

    void set_dirrent(const std::string &dir);
    int dec_proto_file(const std::string &file);
    int dec_list_file(const std::string &list_data);
    int dec_content(const std::string &content_data);
    int dec_comment(const std::string &comment_data);
};


// enc = encapsulation
class share_enc_proto
{
    std::string upload_dirrent;

public:
    share_enc_proto(const std::string &dir);
    ~share_enc_proto();

    void set_dirrent(const std::string &dir);
    int enc_proto_file(const std::string &xml, const std::string &dir);
    int enc_list_file(const std::string &list_data);
    int enc_content(const std::string &content_data);
    int enc_comment(const std::string &comment_data);
};



}
#endif //__ST_SHARE_PROTO_H__
