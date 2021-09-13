#include<stdio.h>
#include"common.h"
#include"DATA.h"
#include"FILE_BUFFER.h"
#include"memLeakPlace_Start.h"

FILE_BUFFER::FILE_BUFFER(const char* filename) {
	FILE* fp;
	fopen_s(&fp, filename, "rb");
	WARNING(!fp, "data��ǂݍ��߂܂���", filename);
    //�t�@�C���T�C�Y�𒲂ׂ�
    fseek(fp, 0L, SEEK_END);//�t�@�C���|�C���^���t�@�C���̍Ō�܂Ői�߂�
    Size = ftell(fp);//�t�@�C���T�C�Y���擾
    rewind(fp);//�t�@�C���|�C���^���ŏ��ɖ߂�
    //�o�b�t�@���m�ۂ��Ĉ�C�ɓǂݍ���
    Buffer = new char[Size + 1];
    fread(Buffer, 1, Size, fp);
    fclose(fp);
    Buffer[Size] = 0;
    //�擪�A�h���X�����Ă���
    BufferPointer = Buffer;
    String[0] = 0;
}

FILE_BUFFER::~FILE_BUFFER(){
    SAFE_DELETE_ARRAY(Buffer);
}

const char* FILE_BUFFER::readString() {
    //��؂蕶����ǂݔ�΂�
    const char*& bp = BufferPointer; //�ϐ�����Z������
    if (bp - Buffer >= Size) {
        return 0;
    }
    while (bp - Buffer < Size && strchr(" \t\r\n,;\"/", *bp)) {
        //��؂蕶����ǂݔ�΂�
        while (bp - Buffer < Size && strchr(" \t\r\n,;\"", *bp)) {
            bp++;
        }
        //�R�����g�ǂݔ�΂�
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

    //�������String�֎��o��
    char* sp = String;

    //// '{'�̌� �܂��� '}'�̑O�ɋ�؂蕶�����Ȃ��Ă�String�֎��o��
    //if( *bp == '{' || *bp == '}' ) {
    //    *sp++ = *bp++;
    //}
    //else{
    //    while ( bp - Buffer < Size && !strchr( " \t\r\n,;\"{}", *bp ) ){
    //        //�s���R�����g�Ȃ�break
    //        if ( *bp == '/' && *(bp + 1) == '/'){
    //            break;
    //        }
    //        else{
    //            *sp++ = *bp++;
    //        }
    //    }
    //}

    while (bp - Buffer < Size && !strchr(" \t\r\n,;\"", *bp)) {
        //�s���R�����g�Ȃ�break
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