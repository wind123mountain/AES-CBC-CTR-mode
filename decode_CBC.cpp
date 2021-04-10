#include <bits/stdc++.h>
#include "decode.h"

using namespace std;

#define N_block 5000000
unsigned char input[N_block<<4];
unsigned char output[N_block<<4];
unsigned char IV[16] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
unsigned char key[16] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
unsigned char expandedKey[176];

void readKey(char * input_name){
	//lay key
	string str;
	ifstream infile;
	infile.open("keyfile", ios::in | ios::binary);
	if (infile.is_open()){
		getline(infile, str);
		infile.close();
	}
	else cout << "Open keyfile error!";

	istringstream hex_chars_stream(str);
	int i = 0;
	unsigned int c;
	while (hex_chars_stream >> hex >> c){
		key[i] = c;
		i++;
	}
	
	//expandedKey
	KeyExpansion(key, expandedKey);
}

int main(int argc, char **argv){
	clock_t s = clock();
	
    unsigned long long dung_luong = 0;
    fstream fin, fout;
	char *input_file = "e_inp.txt", *output_file = "cipher.txt";
	if(argc > 1){
		input_file = argv[1];
	}
	// tinh dung luong
    FILE *fp;
    fp = fopen(input_file, "rb");
    fseek(fp, 0, SEEK_END);
    dung_luong = ftell(fp);
    fclose(fp);
    fin.open(input_file, ios::in | ios::binary);
    fout.open(output_file, ios::out | ios::binary);
    
    //mo rong khoa
    readKey(input_file);
    // lay IV
    for(int i = 0; i != 16; i++){
        char c;
        fin.get(c);
        IV[i] = c;
    }
    
    int n = dung_luong - 16;//16 byte IV
    unsigned char *inIV = IV;
    unsigned char outASE[16];
    bool endFile = false;
    while(!fin.eof()){
    	fin.read((char*)input, sizeof(input));
    	int len = 0;
        if(n > N_block<<4){
            len = N_block;
            n = n - N_block<<4;
        }
        else{
            len = n/16;
            endFile = true;
        }
        
        for(int i = 0; i != len; i++){
        	unsigned char *temp = output + (i<<4);
        	AESDecrypt(input + (i<<4), expandedKey, outASE);
        	for(int j = 0; j != 16; j++){
        		temp[j] = outASE[j] ^ inIV[j];
			}
        	inIV = input + (i<<4);
		}
		
		//padding
		if(!endFile){
			fout.write((char*)output, len<<4);
		}
		else{
			int n_pad = output[(len<<4) - 1];
			fout.write((char*)output, (len<<4) - n_pad);
		}
	}
	
	clock_t e = clock();
	fin.close();
	fout.close();
	cout<<"\nDung luong file giai ma: "<<dung_luong<<" bytes\n";
	cout<<"Thoi gian giai ma: "<<(double)(e-s)/CLOCKS_PER_SEC<< " second (s)\n";
	return 0;
}
