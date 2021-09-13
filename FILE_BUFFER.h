#pragma once
class DATA;

class FILE_BUFFER {
public:
	FILE_BUFFER(const char* filename);
	~FILE_BUFFER();

	float readFloat();
	int readInt();

	const char* readString();
	void restart();
	//オーバーロード
	bool operator==(const char* str);
private:
	DATA** Data = 0;
	int Size = 0;
	char* Buffer = 0;
	const char* BufferPointer = 0;//ファイルバッファのポインタ
	char String[256];//取り出した文字列
};