#include<stdio.h>
#include"common.h"
#include"DATA.h"
#include"FILE_BUFFER.h"
#include"memLeakPlace_Start.h"

FILE_BUFFER::FILE_BUFFER(const char* filename) {
	FILE* fp;
	fopen_s(&fp, filename, "rb");
	WARNING(!fp, "dataを読み込めません", filename);
    //ファイルサイズを調べる
    fseek(fp, 0L, SEEK_END);//ファイルポインタをファイルの最後まで進める
    Size = ftell(fp);//ファイルサイズを取得
    rewind(fp);//ファイルポインタを最初に戻す
    //バッファを確保して一気に読み込む
    Buffer = new char[Size + 1];
    fread(Buffer, 1, Size, fp);
    fclose(fp);
    Buffer[Size] = 0;
    //先頭アドレスを入れておく
    BufferPointer = Buffer;
    String[0] = 0;
}

FILE_BUFFER::~FILE_BUFFER(){
    SAFE_DELETE_ARRAY(Buffer);
}

const char* FILE_BUFFER::readString() {
    //区切り文字を読み飛ばす
    const char*& bp = BufferPointer; //変数名を短くする
    if (bp - Buffer >= Size) {
        return 0;
    }
    while (bp - Buffer < Size && strchr(" \t\r\n,;\"/", *bp)) {
        //区切り文字を読み飛ばす
        while (bp - Buffer < Size && strchr(" \t\r\n,;\"", *bp)) {
            bp++;
        }
        //コメント読み飛ばし
        if (*bp == '/') {
            if (*(bp + 1) == '/') {
                while (bp - Buffer < Size && !strchr("\r\n", *bp)) {
                    bp++;
                }
            }
            else {
                break;
            }
        }
    }

    //文字列をStringへ取り出す
    char* sp = String;

    //// '{'の後 または '}'の前に区切り文字がなくてもStringへ取り出す
    //if( *bp == '{' || *bp == '}' ) {
    //    *sp++ = *bp++;
    //}
    //else{
    //    while ( bp - Buffer < Size && !strchr( " \t\r\n,;\"{}", *bp ) ){
    //        //行中コメントならbreak
    //        if ( *bp == '/' && *(bp + 1) == '/'){
    //            break;
    //        }
    //        else{
    //            *sp++ = *bp++;
    //        }
    //    }
    //}

    while (bp - Buffer < Size && !strchr(" \t\r\n,;\"", *bp)) {
        //行中コメントならbreak
        if (*bp == '/' && *(bp + 1) == '/') {
            break;
        }
        else {
            *sp++ = *bp++;
        }
    }

    *sp = 0;
    if (String[0] == 0) {
        return 0;
    }
    return String;
}

float FILE_BUFFER::readFloat() {
    readString();
    return (float)atof(String);
}

int FILE_BUFFER::readInt() {
    readString();
    return atoi(String);
}

void FILE_BUFFER::restart() {
    BufferPointer = Buffer;
}

bool FILE_BUFFER::operator==(const char* str) {
    return strcmp(String, str) == 0;
}

#include"memLeakPlace_End.h"