#include <iostream>
#include <string>
#include "share.pb.h"
#include "st_share_proto.h"

using namespace peersafe::share;

namespace share
{

share_dec_proto::share_dec_proto(const std::string &dir):
    download_dirrent(dir) {}
share_dec_proto::~share_dec_proto() {}


void share_dec_proto::set_dirrent(const std::string &dir)
{
    download_dirrent = dir;
}

int share_dec_proto::dec_proto_file(const std::string &data)
{
    if (file.empty()) {
        return -1;
    }

    ShareFile sf;
    if (!sf.ParseFromString(data)) {
        return -1;
    }

    switch (sf.file_type()) {
    case ShareFile::FILE_TYPE_SHARE_LIST: {
        dec_list_file(sf.file_data());
        break;
    }
    case ShareFile::FILE_TYPE_SHARE_CONTENT: {
        dec_content(sf.file_data());
        break;
    }
    case ShareFile::FILE_TYPE_SHARE_COMMENT: {
        dec_comment(sf.file_data());
        break;
    }
    default:
        break;
    }
    return 0;
}


int share_dec_proto::dec_list_file(const std::string &list_data)
{
    if (list_data.empty()) {
        return -1;
    }

    ShareList sl;
    if (!sl.ParseFromString(list_data)) {
        return -1;
    }


}

int share_dec_proto::dec_content(const std::string &content_data)
{
    if (content_data.empty()) {
        return -1;
    }

}


int share_dec_proto::dec_comment(const std::string &comment_data)
{
    if (comment_data.empty()) {
        return -1;
    }


}



share_enc_proto::share_enc_proto(const std::string &dir)
{


}
share_enc_proto::~share_enc_proto()
{


}

void share_enc_proto::set_dirrent(const std::string &dir)
{


}
int share_enc_proto::enc_proto_file(const std::string &xml, const std::string &dir)
{


}

int share_enc_proto::enc_list_file(const std::string &list_data)
{


}
int share_enc_proto::enc_content(const std::string &content_data)
{


}
int share_enc_proto::enc_comment(const std::string &comment_data)
{


}

}// namespace share
